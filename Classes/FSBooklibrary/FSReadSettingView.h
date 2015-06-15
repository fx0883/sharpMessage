//
//  FSReadSettingView.h
//  SharpMessage
//
//  Created by apple on 6/11/15.
//
//

#ifndef __SharpMessage__FSReadSettingView__
#define __SharpMessage__FSReadSettingView__



#include <stdio.h>

#include "CrossApp.h"
#include "ListViewEx.h"
#include "CrossAppExt.h"
#include "AppMacros.h"

#include <string>


class FSReadSettingView :public CAView
{
public:
    FSReadSettingView();
    virtual ~FSReadSettingView();
    
    static FSReadSettingView* createWithFrame(const CCRect& rect);
    
    static FSReadSettingView* createWithCenter(const CCRect& rect);
    
    
    
    
//    CC_SYNTHESIZE_IS(int,m_maxPage,MaXPage)
    
public:
    void initView();
//  void addSlider();
//  void setSliederShow(bool bIsShow);
    
//  void setSliderMax(float maxPage);
    void addButtons();
    void initSlider();
    void highlightSliderValueChange(CAControl* btn, CCPoint point);
    void bgItemBtnClick(CrossApp::CAControl *control, CrossApp::CCPoint point);
protected:
    
    bool init();
private:
    CADipSize size;
    CASlider* m_HighlightSlider;
    CAScrollView *m_svContent;
    
    CACollectionView *m_cvContent;
    
public:
    FS changeReadSetting;
};
#endif /* defined(__SharpMessage__FSReadSettingView__) */
