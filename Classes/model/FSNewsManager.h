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
    
public:
    int getCurChapterID(int newsID);
    void setCurChapterID(int newsID,int chapterID);

public:
    void loadNewsList();
    void loadCurChapterInfo(int newsID,int chapterNubmer);
    void loadCurChapterInfo(int newsID);
    void loadChapterDic(int newsID);
    
protected:
    sqlite3 *_sqlite3;
    
};

#endif /* defined(__SharpMessage__FSNewsManager__) */
