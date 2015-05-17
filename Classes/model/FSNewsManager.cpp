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

void FSNewsManager::loadCurChapterInfo(int newsID,int chapterNubmer)
{
    char strNewsID[20];
    sprintf(strNewsID, "%d", newsID);
    
    this->loadChapterDic(newsID);
    
    CAObject *obj = dicChapterInfo.objectForKey(strNewsID);
    if (obj!=NULL) {
        return;
    }
    CCArray* aryChapterInfo = (CCArray*)obj;
    curChapterInfo=(ChapterInfo*)aryChapterInfo->objectAtIndex(chapterNubmer);
    
    
}

void FSNewsManager::loadChapterDic(int newsID)
{
    char strNewsID[20];
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
    snprintf( sql , 32 , "select chapterID,newsID,chapterTitle,imageSrc,chapterContent,href from chapterlist WHERE newsID='%d' ORDER by chapterID" , newsID );
    
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


int FSNewsManager::getCurChapterID(int newsID)
{
    int ret = -1;
    char strNewsID[20];
    sprintf(strNewsID, "%d", newsID);
    
    ret = CAUserDefault::sharedUserDefault()->getIntegerForKey(strNewsID);
    return ret;
}
void FSNewsManager::setCurChapterID(int newsID,int chapterID)
{

    char strNewsID[20];
    sprintf(strNewsID, "%d", newsID);
    
    CAUserDefault::sharedUserDefault()->setIntegerForKey(strNewsID,chapterID);

}



