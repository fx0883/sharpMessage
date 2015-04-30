//
//  FSloadRes.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/29.
//
//

#include "FSloadRes.h"

void FSloadRes::loadNewsList()
{
    loadLanguagePath();
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
    if (!isFirst) {
 
        int ret = 0;
        
        std::string fullPath = CCFileUtils::sharedFileUtils()->getWritablePath() + getDBName();
        
        ret = sqlite3_open(fullPath.c_str(), &_sqlite3);
        
        
        const char *sql_createNewslistTable = "CREATE TABLE IF NOT EXISTS newslist(newsID int PRIMARY KEY, newsTitle VARCHAR(256), imageSrc VARCHAR(256), author VARCHAR(128), status int);";
        sqlite3_stmt *stmt;
        int ok=sqlite3_prepare_v2(_sqlite3, sql_createNewslistTable, -1, &stmt, NULL);
        ok |= sqlite3_step(stmt);
        ok |= sqlite3_finalize(stmt);
        
        if( ok != SQLITE_OK && ok != SQLITE_DONE)
        {
            CCLog("Error in CREATE newslist\n");
        }
        
        const char *sql_createChapterlistTable = "CREATE TABLE IF NOT EXISTS chapterlist(chapterID int PRIMARY KEY,newsID int,chapterTitle VARCHAR(256), imageSrc VARCHAR(256), chapterContent TEXT);";
        stmt=NULL;
        ok=sqlite3_prepare_v2(_sqlite3, sql_createChapterlistTable, -1, &stmt, NULL);
        ok |= sqlite3_step(stmt);
        ok |= sqlite3_finalize(stmt);
        
        if( ok != SQLITE_OK && ok != SQLITE_DONE)
        {
            CCLog("Error in CREATE chapterlist\n");
        }
        
        sqlite3_stmt *_sqlite_stmt_insertnews;
        // INSERT
        const char *sql_insertnews = "INSERT INTO newslist (newsTitle, imageSrc, author, status) VALUES (?,?,?,?);";
        ret |= sqlite3_prepare_v2(_sqlite3, sql_insertnews, -1, &_sqlite_stmt_insertnews, NULL);
        
        sqlite3_stmt *_sqlite_stmt_selectnewId;
        const char *sql_selectnewId = "select last_insert_rowid() newid;";
        ret |= sqlite3_prepare_v2(_sqlite3, sql_selectnewId, -1, &_sqlite_stmt_selectnewId, NULL);
        
        sqlite3_stmt *_sqlite_stmt_insertchapter;
        // INSERT
        const char *sql_insert = "INSERT INTO chapterlist (newsID, chapterTitle, imageSrc, chapterContent) VALUES (?,?,?,?);";
        ret |= sqlite3_prepare_v2(_sqlite3, sql_insert, -1, &_sqlite_stmt_insertchapter, NULL);
        
//
//        // DELETE
//        const char *sql_remove = "DELETE FROM downloadInfo WHERE bookID=?;";
//        ret |= sqlite3_prepare_v2(_sqlite3, sql_remove, -1, &_sqlite_stmt_remove, NULL);
//        
//        // SELECT
//        const char *sql_select = "SELECT bookTitle, imageUrl, alreadyCache, notCache, sizeExplain FROM downloadInfo WHERE bookID=?;";
//        ret |= sqlite3_prepare_v2(_sqlite3, sql_select, -1, &_sqlite_stmt_select, NULL);
//        
//        // UPDATE
//        const char *sql_update = "UPDATE downloadInfo set alreadyCache=?, notCache=?, sizeExplain=? where bookID=?;";
//        ret |= sqlite3_prepare_v2(_sqlite3, sql_update, -1, &_sqlite_stmt_update, NULL);


 
        CCDictionary *plistDic=CCDictionary::createWithContentsOfFileThreadSafe("news/NEWARR.plist");
        CCArray *newlist = plistDic->allKeys();
        
        
        for (int i=0; i<newlist->count(); i++) {
            CCDictionary *itemDic= (CCDictionary*)newlist->objectAtIndex(i);
            _insertNews(_sqlite_stmt_insertnews, itemDic);
            int newsId = -1;
            
            ret |= sqlite3_step(_sqlite_stmt_insertchapter);
            newsId = sqlite3_column_int(_sqlite_stmt_insertchapter, 0);
            
            
        }
        
    }
}

void FSloadRes::_insertNews(sqlite3_stmt *_sqlite_stmt_insertnews,CCDictionary* dic)
{
    int ok  = sqlite3_bind_text(_sqlite_stmt_insertnews,1,dic->valueForKey("title")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertnews, 2,dic->valueForKey("src")->getCString(), -1, SQLITE_TRANSIENT);
    ok |= sqlite3_bind_text(_sqlite_stmt_insertnews, 3,dic->valueForKey("author")->getCString(), -1, SQLITE_TRANSIENT);
    
    
    int newsStatus=0;
    newsStatus = strcmp(dic->valueForKey("status")->getCString(),"已完成")==0?1:0;
    
    ok |= sqlite3_bind_int(_sqlite_stmt_insertnews, 4, newsStatus);
    ok |= sqlite3_step(_sqlite_stmt_insertnews);
    ok |= sqlite3_reset(_sqlite_stmt_insertnews);
    
    if( ok != SQLITE_OK && ok != SQLITE_DONE)
        printf("Error in DMBriefInfoManager._saved()\n");
    
}
void FSloadRes::_insertChapter(sqlite3_stmt *_sqlite_stmt_insertchapter,CCDictionary* dic)
{

    
}







FSloadRes::~FSloadRes()
{
    
}


bool FSloadRes::init()
{
    FSloadResBase::init();
    
    return true;
}