//
//  FSPageSliderView.h
//  SharpMessage
//
//  Created by apple on 6/8/15.
//
//

#ifndef __SharpMessage__FSPageSliderView__
#define __SharpMessage__FSPageSliderView__

#include <stdio.h>

#include "CrossApp.h"
#include "ListViewEx.h"
#include "CrossAppExt.h"
#include "AppMacros.h"

#include <string>

class FSPageSliderView :public CAView
{
public:
    FSPageSliderView();
    virtual ~FSPageSliderView();
    
    static FSPageSliderView* createWithFrame(const CCRect& rect);
    
    static FSPageSliderView* createWithCenter(const CCRect& rect);
    
    
    
    
    CC_SYNTHESIZE_IS(int,m_maxPage,MaXPage)
    
public:
    void initView();
//    void addSlider();
//    void setSliederShow(bool bIsShow);
    
    void setSliderMax(float maxPage);
    void setSliderCurPage(int page);
    void initSlider();
protected:
    
    bool init();
    


    
    
private:
    CADipSize size;
    CASlider* m_pageSlider;
    CALabel *m_showPercent;
protected:
    void pageSliderValueChange(CAControl* btn, CCPoint point);
    void pageSliderTouchUpSide(CAControl* btn, CCPoint point);
    
    
public:
    FSInt changePage;
};



#endif /* defined(__SharpMessage__FSPageSliderView__) */
