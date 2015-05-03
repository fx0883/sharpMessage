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
    CCLog("row is %d,column is %d",r,c);
    //将查询出的数据通过log输出
    for(int i=1;i<=r;i++)
    {
        NewsInfo *newsInfo = new NewsInfo();
        
//        for(int j=0;j<c;j++)
//        {
//            CCLog("%s",re[i*c+j]);
//            
//        }
        int newsId = atoi(re[i*c+0]);
        newsInfo->setNewsID(newsId);
        newsInfo->setNewsTitle(re[i*c+1]);
        newsInfo->setImageSrc(re[i*c+2]);
        newsInfo->setAuthor(re[i*c+3]);
        
        int status = atoi(re[i*c+3]);
        newsInfo->setStatus(status);
        
        arynewsList.addObject(newsInfo);
    }
    sqlite3_free_table(re);
    sqlite3_close(_sqlite3);
}