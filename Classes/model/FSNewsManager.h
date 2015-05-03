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

class FSNewsManager:public CAObject
{
public:
    CREATE_FUNC(FSNewsManager)
public:
    bool init();
    ~FSNewsManager();
public:
    CCArray arynewsList;
    
private:
    void loadNewsList();
protected:
    sqlite3 *_sqlite3;
    
};

#endif /* defined(__SharpMessage__FSNewsManager__) */
