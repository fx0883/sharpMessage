//
//  ChapterInfo.h
//  SharpMessage
//
//  Created by apple on 15/5/12.
//
//
// chapterID,newsID, chapterTitle, imageSrc, chapterContent,href 
#ifndef __SharpMessage__ChapterInfo__
#define __SharpMessage__ChapterInfo__

#include <stdio.h>
#include "CrossApp.h"
#include <string>
class ChapterInfo:public CAObject
{
public:
    CC_SYNTHESIZE_PASS_BY_REF(int, m_chapterID, ChapterID)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_newsID, NewsID)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_chapterTitle, ChapterTitle)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_imageSrc, ImageSrc)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_chapterContent, ChapterContent)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_href, Href)
    
public:
    ChapterInfo();
    ~ChapterInfo();
    
};


#endif /* defined(__SharpMessage__ChapterInfo__) */
