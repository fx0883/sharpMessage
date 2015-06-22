//
//  FSloadRes.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/29.
//
//

#include "FSloadRes.h"
#include "PublicHeader.h"
#include "FSContext.h"
#include "FSDataManager.h"


void FSloadRes::loadNewsList()
{
   // loadLanguagePath();
    loadData();
}


void FSloadRes::loadReadSetting()
{
    string readSettingPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("config/readSetting.plist");
    CCLog("fileTestPath = %s",readSettingPath.c_str());
    
    
    
    
    CCArray *settingAry = CCArray::createWithContentsOfFile(readSettingPath.c_str());
    settingAry->retain();
    FSDataManager::GetInstance().setAryReadSettingList(settingAry);
    CCLog("settingAry Count = %d",settingAry->count());
    
    
    CCArray *readSettingAry = FSDataManager::GetInstance().getAryReadSettingList();
     CCLog("readSettingAry Count = %d",readSettingAry->count());
}


void FSloadRes::loadLanguagePath()
{
    std::vector<std::string> searchPath;
    
    LanguageType langtype = CCApplication::sharedApplication()->getCurrentLanguage();
    
    std::string strResourceFolder="cn";
    switch (langtype) {
        case kLanguageChinese:
            strResourceFolder="cn";
            break;
        case kLanguageEnglish:
            strResourceFolder="en";
            break;
            
            
    }
    
    CCLog("strResourceFolder = %s",strResourceFolder.c_str());
    
    searchPath.push_back(strResourceFolder);
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
}

//DMDownloadInfoManager::DMDownloadInfoManager()
//{
//    int ret = 0;
//    
//    std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "brief.db";
//    
//    ret = sqlite3_open(fullPath.c_str(), &_sqlite3);
//    
//    
//    const char *sql_createtable = "CREATE TABLE IF NOT EXISTS downloadInfo(bookID VARCHAR(64) PRIMARY KEY, bookTitle VARCHAR(256), imageUrl VARCHAR(256), alreadyCache VARCHAR(128), notCache VARCHAR(128), sizeExplain VARCHAR(128));";
//    sqlite3_stmt *stmt;
//    int ok=sqlite3_prepare_v2(_sqlite3, sql_createtable, -1, &stmt, NULL);
//    ok |= sqlite3_step(stmt);
//    ok |= sqlite3_finalize(stmt);
//    
//    if( ok != SQLITE_OK && ok != SQLITE_DONE)
//    {
//        CCLog("Error in CREATE downloadInfo\n");
//    }
//    
//    
//    // INSERT
//    const char *sql_insert = "INSERT INTO downloadInfo (bookID, bookTitle, imageUrl, alreadyCache, notCache, sizeExplain) VALUES (?,?,?,?,?,?);";
//    ret |= sqlite3_prepare_v2(_sqlite3, sql_insert, -1, &_sqlite_stmt_insert, NULL);
//    
//    // DELETE
//    const char *sql_remove = "DELETE FROM downloadInfo WHERE bookID=?;";
//    ret |= sqlite3_prepare_v2(_sqlite3, sql_remove, -1, &_sqlite_stmt_remove, NULL);
//    
//    // SELECT
//    const char *sql_select = "SELECT bookTitle, imageUrl, alreadyCache, notCache, sizeExplain FROM downloadInfo WHERE bookID=?;";
//    ret |= sqlite3_prepare_v2(_sqlite3, sql_select, -1, &_sqlite_stmt_select, NULL);
//    
//    // UPDATE
//    const char *sql_update = "UPDATE downloadInfo set alreadyCache=?, notCache=?, sizeExplain=? where bookID=?;";
//    ret |= sqlite3_prepare_v2(_sqlite3, sql_update, -1, &_sqlite_stmt_update, NULL);
//}



void FSloadRes::loadData()
{
    
    bool isFirst = CAUserDefault::sharedUserDefault()->getBoolForKey("bIsFirst", true);
    if (isFirst)
    {
 
        int ret = 0;
        
        //std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + getDBName();
        
        
        //CCLog("fullPath = %s",);
        
    //    ret = sqlite3_open(fullPath.c_str(), &_sqlite3);
        ret = sqlite3_open(FSContext::GetInstance().getFullDbPath().c_str(), &_sqlite3);
        
        CCLog("sqlite3_open 1===========>");
        
        const char *sql_createNewslistTable = "CREATE TABLE IF NOT EXISTS newslist(newsID INTEGER PRIMARY KEY, newsTitle VARCHAR(256), imageSrc VARCHAR(256), author VARCHAR(128), status INTEGER);";
        sqlite3_stmt *stmt;
        int ok=sqlite3_prepare_v2(_sqlite3, sql_createNewslistTable, -1, &stmt, NULL);
        ok |= sqlite3_step(stmt);
        ok |= sqlite3_finalize(stmt);
        
        if( ok != SQLITE_OK && ok != SQLITE_DONE)
        {
            CCLog("Error in CREATE newslist\n");
        }
        
        const char *sql_createChapterlistTable = "CREATE TABLE IF NOT EXISTS chapterlist(chapterID INTEGER PRIMARY KEY,newsID INTEGER,chapterTitle VARCHAR(256), imageSrc VARCHAR(256), chapterContent TEXT,href VARCHAR(1024));";
        stmt=NULL;
        ok=sqlite3_prepare_v2(_sqlite3, sql_createChapterlistTable, -1, &stmt, NULL);
        ok |= sqlite3_step(stmt);
        ok |= sqlite3_finalize(stmt);
        
        if( ok != SQLITE_OK && ok != SQLITE_DONE)
        {
            CCLog("Error in CREATE chapterlist\n");
        }
        
        
        const char *sql_createBookmarksTable = "CREATE TABLE IF NOT EXISTS bookmarklist(bookmarkID INTEGER PRIMARY KEY,newsID INTEGER,chapterID INTEGER,markDigest VARCHAR(256), markProgress float);";
        stmt=NULL;
        ok=sqlite3_prepare_v2(_sqlite3, sql_createBookmarksTable, -1, &stmt, NULL);
        ok |= sqlite3_step(stmt);
        ok |= sqlite3_finalize(stmt);
        
        if( ok != SQLITE_OK && ok != SQLITE_DONE)
        {
            CCLog("Error in CREATE sql_createBookmarksTable\n");
        }
        
        
        
        
        sqlite3_stmt *_sqlite_stmt_insertnews;
        // INSERT
        const char *sql_insertnews = "INSERT INTO newslist (newsID,newsTitle, imageSrc, author, status) VALUES (NULL,?,?,?,?);";
        ret |= sqlite3_prepare_v2(_sqlite3, sql_insertnews, -1, &_sqlite_stmt_insertnews, NULL);
        

        
        sqlite3_stmt *_sqlite_stmt_insertchapter;
        // INSERT
        const char *sql_insert = "INSERT INTO chapterlist (chapterID,newsID, chapterTitle, imageSrc, chapterContent,href) VALUES (NULL,?,?,?,?,?);";
        ret |= sqlite3_prepare_v2(_sqlite3, sql_insert, -1, &_sqlite_stmt_insertchapter, NULL);
        
        CCLog("debug 2===========>");

        string fileTestPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("news/NEWARR.plist");
        CCLog("fileTestPath = %s",fileTestPath.c_str());
        CCArray *newlist = CCArray::createWithContentsOfFile(fileTestPath.c_str());
        CCLog("newlist count = %d",newlist->count());
        CCLog("debug 3===========>");
        for (int i=0; i<newlist->count(); i++)
        {
            CCLog("debug 4===========>");
            
            CCDictionary *itemDic= (CCDictionary*)newlist->objectAtIndex(i);
            int newsId = _insertNews(_sqlite_stmt_insertnews, itemDic);
            
            //载入当前图书所有章节
            string strChapterplist = string("news/")+string(itemDic->valueForKey("spell")->getCString())+".plist";
            
            CCLog("strChapterplist = %s",strChapterplist.c_str());
            
            string strChapterplistpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strChapterplist.c_str());
            
             CCLog("strChapterplistpath = %s",strChapterplistpath.c_str());
            
            CCDictionary *pNewsChapterDic=CCDictionary::createWithContentsOfFileThreadSafe(strChapterplist.c_str());
            
            CCArray* ary = (CCArray*)pNewsChapterDic->objectForKey("chapterArrArr");
            
            CCArray *chapterAry = (CCArray*)ary->objectAtIndex(0);
            CCLog("debug 5===========>");
            
            for (int i=0; i<chapterAry->count(); i++) {
                CCDictionary* itemDic = (CCDictionary*)chapterAry->objectAtIndex(i);
                
                _insertChapter(newsId, _sqlite_stmt_insertchapter, itemDic);
            }
            
        }
        CCLog("debug 6===========>");
        
    }
    CAUserDefault::sharedUserDefault()->setBoolForKey("bIsFirst", false);
}



int FSloadRes::_insertNews(sqlite3_stmt *_sqlite_stmt_insertnews,CCDictionary* dic)
{
    int ok  = sqlite3_bind_text(_sqlite_stmt_insertnews,1,dic->valueForKey("title")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertnews, 2,dic->valueForKey("src")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertnews, 3,dic->valueForKey("author")->getCString(), -1, SQLITE_TRANSIENT);
    
    int newsID=-1;
    int newsStatus=0;
    newsStatus = strcmp(dic->valueForKey("status")->getCString(),"已完成")==0?1:0;
    
    ok |= sqlite3_bind_int(_sqlite_stmt_insertnews, 4, newsStatus);
    ok |= sqlite3_step(_sqlite_stmt_insertnews);
    ok |= sqlite3_reset(_sqlite_stmt_insertnews);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
    {
        printf("Error in Newlist._saved()\n");
    }
    else
    {
//        sqlite3_stmt *_sqlite_stmt_selectnewId;
//        const char *sql_selectnewId = "select last_insert_rowid() newid";
//        ok |= sqlite3_prepare_v2(_sqlite3, sql_selectnewId, -1, &_sqlite_stmt_selectnewId, NULL);
//        newsID = sqlite3_column_int(_sqlite_stmt_selectnewId, 0);
//        
//        char* szError = 0;
//        char** paszResults = 0;
//        int nRows = 0, nCols = 0;
//        int nRet = sqlite3_get_table(_sqlite3, sql_selectnewId, &paszResults, &nRows, &nCols, &szError);
//        if (nRet != SQLITE_OK)
//        {
//            return -1;
//        }
//
//        
//        for (int nCurrentRow = 0; nCurrentRow < nRows; nCurrentRow++)
//        {
////            DownloadRecord v;
////            v.download_id = atol(paszResults[(nCurrentRow*nCols) + nCols + 0]);
////            v.download_Url = paszResults[(nCurrentRow*nCols) + nCols + 1];
////            v.download_header = paszResults[(nCurrentRow*nCols) + nCols + 2];
////            v.filePath = paszResults[(nCurrentRow*nCols) + nCols + 3];
////            v.fileSize = atof(paszResults[(nCurrentRow*nCols) + nCols + 4]);
////            v.startTime = paszResults[(nCurrentRow*nCols) + nCols + 5];
////            v.isFinished = atoi(paszResults[(nCurrentRow*nCols) + nCols + 6]);
////            v.textTag = paszResults[(nCurrentRow*nCols) + nCols + 7];
////            m_mDownloadRecords.insert(std::map<unsigned long, DownloadRecord>::value_type(v.download_id, v));
//            
//            
//        }
//        sqlite3_free_table(paszResults);
        
      newsID =  (int)sqlite3_last_insert_rowid(_sqlite3);
    }
    return newsID;
    
}
void FSloadRes::_insertChapter(int newsID,sqlite3_stmt *_sqlite_stmt_insertchapter,CCDictionary* dic)
{
    int ok = sqlite3_bind_int(_sqlite_stmt_insertchapter, 1, newsID);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertchapter,2,dic->valueForKey("chapterTitle")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertchapter, 3,dic->valueForKey("chapterSrcs")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertchapter, 4,dic->valueForKey("chapterContent")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertchapter, 5,dic->valueForKey("href")->getCString(), -1, SQLITE_TRANSIENT);
    
    ok |= sqlite3_step(_sqlite_stmt_insertchapter);
    ok |= sqlite3_reset(_sqlite_stmt_insertchapter);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in Newlist._saved()\n");
    
}







FSloadRes::~FSloadRes()
{
    
}


bool FSloadRes::init()
{
    FSloadResBase::init();
    
    return true;
}