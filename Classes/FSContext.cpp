//
//  FSContext.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#include "FSContext.h"


FSContext::FSContext()
{
    
}

FSContext::~FSContext()
{

}

string FSContext::getFullDbPath()
{
    string strDBPath = CCFileUtils::sharedFileUtils()->getWritablePath() + string(DBName);
    CCLog("dbPath = %s",strDBPath.c_str());
    return strDBPath;
}