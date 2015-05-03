//
//  FSDataManager.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#include "FSDataManager.h"




FSDataManager::FSDataManager()
{
    m_NewsManager = FSNewsManager::create();
    m_NewsManager->retain();
}

FSDataManager::~FSDataManager()
{
    m_NewsManager->release();
    CCLog("~FSDataManager");
}