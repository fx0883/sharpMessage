//
//  ListViewEx.h
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#ifndef __SharpMessage__ListViewEx__
#define __SharpMessage__ListViewEx__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"

//NS_CC_BEGIN
class ListViewEx :public CAListView
{
public:
    static ListViewEx* createWithFrame(const CCRect& rect);
    
    static ListViewEx* createWithCenter(const CCRect& rect);
    
    
public:
    
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
private:
    
    typedef enum
    {
        CAListViewLast,
        CAListViewNext,
        CAListViewNone
    }CAListViewExState;
    
    CAListViewExState m_eListViewExState;

    
public:
    
    CC_PROPERTY_READONLY(int, m_nCurrPage, CurrPage);
//
    void setCurrPage(int var, bool animated, bool listener = false);
//
    
    //unsigned int getPageCount();
    CC_SYNTHESIZE_IS(unsigned int,m_listCount,ListCount)
};


//NS_CC_END


#endif /* defined(__SharpMessage__ListViewEx__) */
