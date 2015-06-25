//
//  FSNewsManager.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSNewsManager__
#define __SharpMessage__FSNewsManager__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "AppMacros.h"
#include "ChapterInfo.h"
#include "NewsInfo.h"
#include "BookMarkInfo.h"

class FSNewsManager:public CAObject
{
public:
    CREATE_FUNC(FSNewsManager)
public:
    bool init();
    ~FSNewsManager();
public:
    CC_SYNTHESIZE_PASS_BY_REF2(CCArray, arynewsList, ArynewsList);
    CC_SYNTHESIZE_PASS_BY_REF2(ChapterInfo*, curChapterInfo, CurChapterInfo);
    CC_SYNTHESIZE_PASS_BY_REF2(CCDictionary, dicChapterInfo, DicChapterInfo);
    CC_SYNTHESIZE_PASS_BY_REF2(CCDictionary, dicBookMarkInfo, DicBookMarkInfo);
public:
    bool removeBookMarkForNewsId(int newsID);
    int getCurChapterID(int newsID);
    void setCurChapterID(int newsID,int chapterID);
    CCArray* getChapterInfoAry(int newsID);
    float getPageProgress(int chapterID);
    void setPageProgress(int chapterID,string progress);
public:
    void loadNewsList();
    void loadCurChapterInfo(int newsID,int chapterNubmer);
    void loadCurChapterInfo(int newsID);
    void loadChapterDic(int newsID);
    
    CCArray* loadBookMarkInfo(int newsID);
    bool addBookMarkInfo(BookMarkInfo*& bookmarkinfo);
    bool insertbookmarkToDB(BookMarkInfo*& bookmarkinfo);
    
    bool deleteBookmarkInDB(int newsID);
    
public:
    NewsInfo* getNewsInfoByNewsId(int newsId);
    

    
protected:
    sqlite3 *_sqlite3;
    
};

#endif /* defined(__SharpMessage__FSNewsManager__) */
