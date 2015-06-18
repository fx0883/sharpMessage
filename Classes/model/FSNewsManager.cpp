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

bool FSNewsManager::init()
{
    
    bool bRet = true;
    loadNewsList();
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
    curChapterInfo=(ChapterInfo*)aryChapterInfo->objectAtIndex(chapterNubmer);
    
    
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
        
        
//        newsInfo->setNewsID(newsId);
//        newsInfo->setNewsTitle(re[i*c+1]);
//        newsInfo->setImageSrc(re[i*c+2]);
//        newsInfo->setAuthor(re[i*c+3]);
//        
//        int status = atoi(re[i*c+3]);
//        newsInfo->setStatus(status);
//        
//        arynewsList.addObject(newsInfo);
        
        aryChapterInfo->addObject(chapterinfo);
    }
    

    dicChapterInfo.setObject(aryChapterInfo, strNewsID);
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);

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
    CAObject *obj = dicChapterInfo.objectForKey(strNewsID);
    if (obj!= NULL) {
        return (CCArray*)obj;
    }
    
    dicChapterInfo.removeAllObjects();
    
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    //查询结果
    char **re;
    //行、列
    int r,c;
    
    char sql[256];
    snprintf( sql , 256 , "select bookmarkID,newsID,chapterID,markProgress from bookmarklist WHERE newsID='%d' ORDER by bookmarkID" , newsID );
    
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
        
        
        float markProgress = atof(re[i*c+3]);
        bookmarkinfo->setMarkProgress(markProgress);
        bookmarkinfo->setNewsID(newsID);
        bookmarkinfo->setChapterID(chapterID);
        bookmarkinfo->setBookMarkID(bookmarkID);
        
        aryBookMarkInfo->addObject(bookmarkinfo);
    }
    
    
    dicBookMarkInfo.setObject(aryBookMarkInfo, strNewsID);
    
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);

    return aryBookMarkInfo;
}









bool FSNewsManager::insertbookmarkToDB(BookMarkInfo*& bookmarkinfo)
{
    int ret = 0;
    
    ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
    
    sqlite3_stmt *_sqlite_stmt_insertbookmark;
    // INSERT
    
//    bookmarkID,newsID,chapterID,markProgress
    const char *sql_insert = "INSERT INTO bookmarklist (bookmarkID,newsID,chapterID, markProgress) VALUES (NULL,?,?,?);";
    ret |= sqlite3_prepare_v2(_sqlite3, sql_insert, -1, &_sqlite_stmt_insertbookmark, NULL);
    
    CCLog("debug 2===========>");
    
    int ok = sqlite3_bind_int(_sqlite_stmt_insertbookmark, 1, bookmarkinfo->getNewsID());
    ok |= sqlite3_bind_int(_sqlite_stmt_insertbookmark, 1, bookmarkinfo->getChapterID());
    ok |= sqlite3_bind_double(_sqlite_stmt_insertbookmark, 1, bookmarkinfo->getMarkProgress());

    
    ok |= sqlite3_step(_sqlite_stmt_insertbookmark);
    ok |= sqlite3_reset(_sqlite_stmt_insertbookmark);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in Newlist._saved()\n");
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
        if (item==bookmarkinfo) {
            return bret;
        }
        
        
    }
    
    this->insertbookmarkToDB(bookmarkinfo);
    
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



