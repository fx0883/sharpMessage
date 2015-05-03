//
//  FSloadRes.h
//  SharpMessage
//
//  Created by 冯璇 on 15/4/29.
//
//

#ifndef __SharpMessage__FSloadRes__
#define __SharpMessage__FSloadRes__

#include <stdio.h>
#include "FSloadResBase.h"


class FSloadRes:public FSloadResBase
{
public:
    CREATE_FUNC(FSloadRes)
public:
    void loadNewsList();
    bool init();
    ~FSloadRes();
private:
    void loadData();
    void loadLanguagePath();
    int _insertNews(sqlite3_stmt *_sqlite_stmt_insertnews,CCDictionary* dic);
    void _insertChapter(int newsID,sqlite3_stmt *_sqlite_stmt_insertchapter,CCDictionary* dic);

};

#endif /* defined(__SharpMessage__FSloadRes__) */
