//
//  BookMarkInfo.h
//  SharpMessage
//
//  Created by apple on 6/17/15.
//
//

#ifndef __SharpMessage__BookMarkInfo__
#define __SharpMessage__BookMarkInfo__

#include <stdio.h>

#include <stdio.h>
#include "CrossApp.h"
#include <string>
class BookMarkInfo:public CAObject
{
public:
    CC_SYNTHESIZE_PASS_BY_REF(int, m_bookmarkID, BookMarkID)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_chapterID, ChapterID)
    CC_SYNTHESIZE_PASS_BY_REF(int, m_newsID, NewsID)
    CC_SYNTHESIZE_PASS_BY_REF(double, m_markProgress, MarkProgress)
    CC_SYNTHESIZE_PASS_BY_REF(string, m_markDigest, MarkDigest)
public:
    BookMarkInfo();
    ~BookMarkInfo();
    
    //比较两个对象的大小
    bool operator == (const BookMarkInfo &bookmarkinfo) const{
    
        return (m_chapterID==bookmarkinfo.getChapterID()
                &&m_newsID==bookmarkinfo.getNewsID()
                &&m_markProgress == bookmarkinfo.getMarkProgress());
    };
};

#endif /* defined(__SharpMessage__BookMarkInfo__) */
