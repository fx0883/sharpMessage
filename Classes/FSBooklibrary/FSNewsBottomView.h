//
//  FSNewsBottomView.h
//  SharpMessage
//
//  Created by apple on 6/5/15.
//
//

#ifndef __SharpMessage__FSNewsBottomView__
#define __SharpMessage__FSNewsBottomView__

#include <stdio.h>

#include "CrossApp.h"
#include "ListViewEx.h"
#include "CrossAppExt.h"
#include "AppMacros.h"

#include <string>
//#include "ChapterInfo.h"



class FSNewsBottomView :public CAView
{
public:
    FSNewsBottomView();
    virtual ~FSNewsBottomView();
    
    static FSNewsBottomView* createWithFrame(const CCRect& rect);
    
    static FSNewsBottomView* createWithCenter(const CCRect& rect);
    
    
    
    
//    CC_SYNTHESIZE_IS(int,m_maxPage,MaXPage)

public:
    void initView();
//    void addSlider();
    void setSliederShow(bool bIsShow);
protected:
    
    bool init();

    void setTouchSelected(CrossApp::CAControl *control, CrossApp::CCPoint point);
    
    
    
private:
    CAVector<CAImage*> m_listImage;
    vector<string> m_listText;
//    CAButton *m_CataloguesButton;
//    CAButton *m_ProgressButton;
//    CAButton *m_SettingButton;
    CASlider* m_pageSlider;
    
protected:
//    void pageSliderValueChange(CAControl* btn, CCPoint point);
    
    
public:
    FS openCatalog;
    FS showPageSlider;
};



#endif /* defined(__SharpMessage__FSNewsBottomView__) */
