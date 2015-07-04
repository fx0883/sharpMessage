//
//  newsInfo.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__newsInfo__
#define __SharpMessage__newsInfo__

#include <stdio.h>
#include "CrossApp.h"
#include <string>

using namespace::std;

class NewsInfo:public CAObject
{
public:
    CC_SYNTHESIZE_PASS_BY_REF(int, m_newsID, NewsID)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_newsTitle, NewsTitle)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_imageSrc, ImageSrc)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_author, Author)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_status, Status)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_readtimes, ReadTimes)
public:
    NewsInfo();
    ~NewsInfo();
    
};


#endif /* defined(__SharpMessage__newsInfo__) */
