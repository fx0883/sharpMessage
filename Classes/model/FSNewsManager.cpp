//
//  FSNewsManager.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#include "FSNewsManager.h"
#include "newsInfo.h"
#include "PublicHeader.h"
#include "ChapterInfo.h"

#define MaxGreatNews 6

bool FSNewsManager::init()
{
    
    bool bRet = true;
    loadNewsList();
    //loadNewsListOrderbyReadTimes();
    return bRet;
}

FSNewsManager::~FSNewsManager()
{
    CCLog("~FSNewsManager");
    for(int i=arynewsList.count()-1;i>=0;i--)
    {
        CAObject *itemObj = arynewsList.objectAtIndex(i);
        itemObj->release();
        arynewsList.removeObjectAtIndex(i);
    }
}

void FSNewsManager::loadCurChapterInfo(int newsID)
{
    int chapterNumber = getCurChapterID(newsID);
    loadCurChapterInfo(newsID, chapterNumber);
}

void FSNewsManager::loadCurChapterInfo(int newsID,int chapterNubmer)
{
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    
    this->loadChapterDic(newsID);
    
    CAObject *obj = dicChapterInfo.objectForKey(strNewsID);
    if (obj==NULL) {
        return;
    }
    CCArray* aryChapterInfo = (CCArray*)obj;
    
//    CC_SAFE_RELEASE(curChapterInfo);
//    CC_SAFE_RETAIN(curChapterInfo);

    ChapterInfo* chapterInfo = NULL;
    for (int i=0; i<aryChapterInfo->count(); i++) {
        chapterInfo=(ChapterInfo*)aryChapterInfo->objectAtIndex(i);
        if (chapterInfo->getChapterID() == chapterNubmer) {
            break;
        }
    }
    
    if (chapterInfo==NULL) {
        chapterInfo=(ChapterInfo*)aryChapterInfo->objectAtIndex(chapterNubmer);
    }

    
    
    this->setCurChapterInfo(chapterInfo);
//    curChapterInfo->retain();
    
}

void FSNewsManager::updateNewsReadTimes()
{
    for (int i=0; i<arynewsList.count(); i++) {
        NewsInfo* itemNewsInfo = (NewsInfo*)arynewsList.objectAtIndex(i);
        updateNewsInfo(itemNewsInfo);
    }
    
}


bool FSNewsManager::updateNewsInfo(NewsInfo *newsinfo)
{
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    sqlite3_stmt *_sqlite_stmt_updatenewsinfo;
    // INSERT
    
    //    bookmarkID,newsID,chapterID,markProgress
    const char *sql_update = "update newslist SET readTimes = ? where newsID = ?;";
    ret |= sqlite3_prepare_v2(_sqlite3, sql_update, -1, &_sqlite_stmt_updatenewsinfo, NULL);
    
    CCLog("debug 2===========>");
    
    int ok = sqlite3_bind_int(_sqlite_stmt_updatenewsinfo, 1, newsinfo->getReadTimes());
    ok = sqlite3_bind_int(_sqlite_stmt_updatenewsinfo, 2, newsinfo->getNewsID());
//    ok |= sqlite3_bind_int(_sqlite_stmt_insertbookmark, 2, bookmarkinfo->getChapterID());
//    ok |= sqlite3_bind_text(_sqlite_stmt_insertbookmark, 3, bookmarkinfo->getMarkProgress().c_str(), -1, SQLITE_TRANSIENT);
//    ok |= sqlite3_bind_text(_sqlite_stmt_insertbookmark, 4,bookmarkinfo->getMarkDigest().c_str(), -1, SQLITE_TRANSIENT);
    
    ok |= sqlite3_step(_sqlite_stmt_updatenewsinfo);
    ok |= sqlite3_reset(_sqlite_stmt_updatenewsinfo);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
    {
        ok |= sqlite3_finalize(_sqlite_stmt_updatenewsinfo);
        sqlite3_close(_sqlite3);
        printf("Error in Newlist._saved()\n");
        return false;
    }
    ok |= sqlite3_finalize(_sqlite_stmt_updatenewsinfo);
    sqlite3_close(_sqlite3);
    return true;
    
}









CCArray* FSNewsManager::getChapterInfoAry(int newsID)
{
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    
    this->loadChapterDic(newsID);
    
    CAObject *obj = dicChapterInfo.objectForKey(strNewsID);
    if (obj==NULL) {
        return NULL;
    }
    CCArray* aryChapterInfo = (CCArray*)obj;
    return aryChapterInfo;
}


void FSNewsManager::loadChapterDic(int newsID)
{
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    CAObject *obj = dicChapterInfo.objectForKey(strNewsID);
    if (obj!=NULL) {
        return;
    }
    dicChapterInfo.removeAllObjects();
    
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char sql[256];
    snprintf( sql , 256 , "select chapterID,newsID,chapterTitle,imageSrc,chapterContent,href from chapterlist WHERE newsID='%d' ORDER by chapterID" , newsID );
    
//    string strSql = "select * from chapterlist WHERE newsID='%d' ORDER by chapterID desc"
    
    //查询数据
    sqlite3_get_table(_sqlite3,sql,&re,&r,&c,NULL);
    //    CCLog("row is %d,column is %d",r,c);
    //将查询出的数据通过log输出
    
    CCArray *aryChapterInfo = CCArray::create();
    for(int i=1;i<=r;i++)
    {
        ChapterInfo *chapterinfo = new ChapterInfo();
        
        int chapterID = atoi(re[i*c+0]);
        int newsID = atoi(re[i*c+1]);
        
        chapterinfo->setChapterID(chapterID);
        chapterinfo->setNewsID(newsID);
        
        chapterinfo->setChapterTitle(re[i*c+2]);
        chapterinfo->setImageSrc(re[i*c+3]);
        chapterinfo->setChapterContent(re[i*c+4]);
        chapterinfo->setHref(re[i*c+5]);
        
        
        aryChapterInfo->addObject(chapterinfo);
    }
    

    dicChapterInfo.setObject(aryChapterInfo, strNewsID);
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);

}

CCArray* FSNewsManager::loadNewsListOrderbyReadTimes2()
{
//    aryNewsListOrderbyReadTimes.removeAllObjects();
//    for (int i=0; i<arynewsList.count(); i++) {
//        aryNewsListOrderbyReadTimes.addObject(arynewsList.objectAtIndex(i));
//    }
    
    vector<NewsInfo*> vec;
    aryNewsListOrderbyReadTimes.removeAllObjects();
    for (int i=0; i<arynewsList.count(); i++) {
        //aryNewsListOrderbyReadTimes.addObject(arynewsList.objectAtIndex(i));
        
        vec.push_back((NewsInfo*)arynewsList.objectAtIndex(i));
    }
    
    sort(vec.begin(), vec.end(),greaterNews)   ;   //降序排序
    
    aryNewsListOrderbyReadTimes.removeAllObjects();
    
    
    int count = MIN((int)vec.size(), MaxGreatNews);
    
    
    for (int i=0; i<count; i++) {
        aryNewsListOrderbyReadTimes.addObject(vec[i]);
    }
    
    return &aryNewsListOrderbyReadTimes;
}


bool   FSNewsManager::greaterNews( NewsInfo*  const s1, NewsInfo*  const s2)
{
    return   s1->getReadTimes()   >   s2->getReadTimes();
}

CCArray* FSNewsManager::loadNewsListOrderbyReadTimes()
{
    int ret = 0;
    //    CCLog("fullPath = %s",DBPATH);
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    //查询结果
    char **re;
    //行、列
    int r,c;
    //查询数据
    sqlite3_get_table(_sqlite3,"select * from newslist order by readTimes desc limit 0,6;",&re,&r,&c,NULL);

    //将查询出的数据通过log输出
    //CCArray *aryNewsList = CCArray::create();
    for(int i=1;i<=r;i++)
    {
        NewsInfo *newsInfo = new NewsInfo();
        
        int newsId = atoi(re[i*c+0]);
        newsInfo->setNewsID(newsId);
        newsInfo->setNewsTitle(re[i*c+1]);
        newsInfo->setImageSrc(re[i*c+2]);
        newsInfo->setAuthor(re[i*c+3]);
        
        int status = atoi(re[i*c+4]);
        newsInfo->setStatus(status);
        int readTimes = atoi(re[i*c+5]);
        newsInfo->setReadTimes(readTimes);
        
        aryNewsListOrderbyReadTimes.addObject(newsInfo);
    }
    
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
    
    return &aryNewsListOrderbyReadTimes;
}




void FSNewsManager::loadNewsList()
{
    
    int ret = 0;
//    CCLog("fullPath = %s",DBPATH);
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    //查询结果
    char **re;
    //行、列
    int r,c;
    //查询数据
    sqlite3_get_table(_sqlite3,"select * from newslist",&re,&r,&c,NULL);
//    CCLog("row is %d,column is %d",r,c);
    //将查询出的数据通过log输出
    for(int i=1;i<=r;i++)
    {
        NewsInfo *newsInfo = new NewsInfo();
        
        int newsId = atoi(re[i*c+0]);
        newsInfo->setNewsID(newsId);
        newsInfo->setNewsTitle(re[i*c+1]);
        newsInfo->setImageSrc(re[i*c+2]);
        newsInfo->setAuthor(re[i*c+3]);
        
        int status = atoi(re[i*c+4]);
        newsInfo->setStatus(status);
        int readTimes = atoi(re[i*c+5]);
        newsInfo->setReadTimes(readTimes);
        
        arynewsList.addObject(newsInfo);
    }
    

    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
}



NewsInfo* FSNewsManager::getNewsInfoByNewsId(int newsId)
{
//        CCArray& ary = FSDataManager::GetInstance().getNewsManager()->getArynewsList();
    
    for (int i=0; i<arynewsList.count(); i++) {
        NewsInfo *newsinfo = (NewsInfo*)arynewsList.objectAtIndex(i);
        if(newsinfo->getNewsID() == newsId)
        {
            return newsinfo;
        }
    }
    return NULL;
}

CCArray* FSNewsManager::loadBookMarkInfo(int newsID)
{
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    CAObject *obj = dicBookMarkInfo.objectForKey(strNewsID);
    if (obj!= NULL) {
        return (CCArray*)obj;
    }
    
    //dicBookMarkInfo.removeAllObjects();
    
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char sql[256];
    snprintf( sql , 256 , "select bookmarkID,newsID,chapterID,markProgress,markDigest from bookmarklist WHERE newsID='%d' ORDER by bookmarkID" , newsID );
    
    //    string strSql = "select * from chapterlist WHERE newsID='%d' ORDER by chapterID desc"
    
    //查询数据
    sqlite3_get_table(_sqlite3,sql,&re,&r,&c,NULL);
    //    CCLog("row is %d,column is %d",r,c);
    //将查询出的数据通过log输出
    
    CCArray *aryBookMarkInfo = CCArray::create();
    for(int i=1;i<=r;i++)
    {
        BookMarkInfo *bookmarkinfo = new BookMarkInfo();
        
        int bookmarkID = atoi(re[i*c+0]);
        int newsID = atoi(re[i*c+1]);
        int chapterID= atoi(re[i*c+2]);
        
        
        //float markProgress = atof(re[i*c+3]);
        bookmarkinfo->setMarkProgress(re[i*c+3]);
        bookmarkinfo->setNewsID(newsID);
        bookmarkinfo->setChapterID(chapterID);
        bookmarkinfo->setBookMarkID(bookmarkID);
        
        bookmarkinfo->setMarkDigest(re[i*c+4]);
        
        aryBookMarkInfo->addObject(bookmarkinfo);
    }
    
    
    dicBookMarkInfo.setObject(aryBookMarkInfo, strNewsID);
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);

    return aryBookMarkInfo;
}

ChapterInfo* FSNewsManager::getChapterInfoOrientation(ChapterInfo* chapterinfo,bool bIsNext)
{
    CCArray* ary = getChapterInfoAry(chapterinfo->getNewsID());
    
    int index=0;
    for (int i=0; i<ary->count(); i++) {
        
        ChapterInfo *itemChapterinfo = (ChapterInfo*)ary->objectAtIndex(i);
        
        if (chapterinfo->getChapterID() == itemChapterinfo->getChapterID()) {
            index = i;
            break;
        }
    }
    
    ChapterInfo *retChapterInfo=NULL;
    if (bIsNext)
    {
        index++;
        if (index<ary->count()) {
            retChapterInfo = (ChapterInfo*)ary->objectAtIndex(index);
        }
    }
    else
    {
        index--;
        if (index>=0) {
            retChapterInfo = (ChapterInfo*)ary->objectAtIndex(index);
        }

    }
    return retChapterInfo;
    
}
ChapterInfo* FSNewsManager::getNextChapterInfo(ChapterInfo* chapterinfo)
{
    return getChapterInfoOrientation(chapterinfo, true);
}
ChapterInfo* FSNewsManager::getPreChapterInfo(ChapterInfo* chapterinfo)
{
    return getChapterInfoOrientation(chapterinfo, false);
}



bool FSNewsManager::deleteBookmarkInDB(int newsID)
{
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    

    
    sqlite3_stmt *_sqlite_stmt_deletebookmark;
    // INSERT
    
    //    bookmarkID,newsID,chapterID,markProgress
    const char *sql_delete = "delete from bookmarklist where newsID = ?";
    ret |= sqlite3_prepare_v2(_sqlite3, sql_delete, -1, &_sqlite_stmt_deletebookmark, NULL);
    
    CCLog("debug 2===========>");
    
    int ok = sqlite3_bind_int(_sqlite_stmt_deletebookmark, 1,newsID);

    
    ok |= sqlite3_step(_sqlite_stmt_deletebookmark);
    ok |= sqlite3_reset(_sqlite_stmt_deletebookmark);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
    {
        ok |= sqlite3_finalize(_sqlite_stmt_deletebookmark);
        sqlite3_close(_sqlite3);
        printf("Error in Newlist._saved()\n");
        return false;
    }
    ok |= sqlite3_finalize(_sqlite_stmt_deletebookmark);
    sqlite3_close(_sqlite3);
    
    return true;

}


SqliteCursor *FSNewsManager::SqliteQurey( sqlite3 *pSql , std::string sql )
{
    char *errMsg = NULL;
    SqliteCursor *pCursor = new SqliteCursor();
    int result = sqlite3_exec( pSql, sql.c_str() , QueryResult, pCursor , &errMsg );
    if ( result != SQLITE_OK && errMsg != NULL )
    {
        delete pCursor;
        return NULL;
    }
    if ( pCursor->GetRowCount() == 0 )
    {
        delete pCursor;
        return NULL;
    }
    return pCursor;
}


bool FSNewsManager::insertbookmarkToDB(BookMarkInfo*& bookmarkinfo)
{
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    sqlite3_stmt *_sqlite_stmt_insertbookmark;
    // INSERT
    
//    bookmarkID,newsID,chapterID,markProgress
    const char *sql_insert = "INSERT INTO bookmarklist (bookmarkID,newsID,chapterID, markProgress,markDigest) VALUES (NULL,?,?,?,?);";
    ret |= sqlite3_prepare_v2(_sqlite3, sql_insert, -1, &_sqlite_stmt_insertbookmark, NULL);
    
    CCLog("debug 2===========>");
    
    int ok = sqlite3_bind_int(_sqlite_stmt_insertbookmark, 1, bookmarkinfo->getNewsID());
    ok |= sqlite3_bind_int(_sqlite_stmt_insertbookmark, 2, bookmarkinfo->getChapterID());
    ok |= sqlite3_bind_text(_sqlite_stmt_insertbookmark, 3, bookmarkinfo->getMarkProgress().c_str(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertbookmark, 4,bookmarkinfo->getMarkDigest().c_str(), -1, SQLITE_TRANSIENT);
    
    ok |= sqlite3_step(_sqlite_stmt_insertbookmark);
    ok |= sqlite3_reset(_sqlite_stmt_insertbookmark);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
    {
        ok |= sqlite3_finalize(_sqlite_stmt_insertbookmark);
        sqlite3_close(_sqlite3);
        printf("Error in Newlist._saved()\n");
        return false;
    }
    ok |= sqlite3_finalize(_sqlite_stmt_insertbookmark);
    sqlite3_close(_sqlite3);
    return true;
}

bool FSNewsManager::removeBookMarkForNewsId(int newsID)
{
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    CAObject *obj = dicBookMarkInfo.objectForKey(strNewsID);
    if (obj) {
        
        if(deleteBookmarkInDB(newsID))
        {
            CCArray *ary = (CCArray*)obj;
            ary->removeAllObjects();
            dicBookMarkInfo.removeObjectForKey(strNewsID);
        }
        
        else
        {
            return false;
        }
        
    }
    return true;
}






bool FSNewsManager::addBookMarkInfo(BookMarkInfo*& bookmarkinfo)
{
    bool bret = false;
    
    //查看有没有bookinfo
    if (bookmarkinfo==NULL) {
        return bret;
    }
    

    CCArray *aryBookMarkInfo = this->loadBookMarkInfo(bookmarkinfo->getNewsID());
    
    for (int i=0; i<aryBookMarkInfo->count(); i++) {
        
        BookMarkInfo* item = (BookMarkInfo*)aryBookMarkInfo->objectAtIndex(i);
        if (*item==*bookmarkinfo) {
            return bret;
        }
        
        
    }
    
    this->insertbookmarkToDB(bookmarkinfo);
    
    aryBookMarkInfo->addObject(bookmarkinfo);
    
    bret = true;
    return bret;

}


int FSNewsManager::getCurChapterID(int newsID)
{
    int ret = -1;
    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    
    ret = CAUserDefault::sharedUserDefault()->getIntegerForKey(strNewsID,0);
    return ret;
}
void FSNewsManager::setCurChapterID(int newsID,int chapterID)
{

    char strNewsID[50];
    sprintf(strNewsID, "%d", newsID);
    
    CAUserDefault::sharedUserDefault()->setIntegerForKey(strNewsID,chapterID);

}


void FSNewsManager::setPageProgress(int chapterID,string progress)
{
    char strChapterID[50];
    sprintf(strChapterID, "%d", chapterID);
    
    CAUserDefault::sharedUserDefault()->setStringForKey(strChapterID, progress);
}

float FSNewsManager::getPageProgress(int chapterID)
{
    char strChapterID[50];
    sprintf(strChapterID, "%d", chapterID);
    string strProgress = CAUserDefault::sharedUserDefault()->getStringForKey(strChapterID);
    float progress = 0;
    if (strProgress.length()>0) {
        progress = atof(strProgress.c_str());
    }
    return progress;
}



