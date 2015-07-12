
//
//  FSReadSettingView.cpp
//  SharpMessage
//
//  Created by apple on 6/11/15.
//
//

#include "FSReadSettingView.h"
#include "FSDataManager.h"

#include "AppMacros.h"

FSReadSettingView::FSReadSettingView()
:changeReadSetting(NULL)
{
    
}


FSReadSettingView::~FSReadSettingView()
{
    
    
}


FSReadSettingView* FSReadSettingView::createWithFrame(const CCRect& rect)
{
    FSReadSettingView* fsreadsettingview = new FSReadSettingView();
    if (fsreadsettingview && fsreadsettingview->initWithFrame(rect))
    {
        fsreadsettingview->autorelease();
        return fsreadsettingview;
    }
    CC_SAFE_DELETE(fsreadsettingview);
    return NULL;
}

FSReadSettingView* FSReadSettingView::createWithCenter(const CCRect& rect)
{
    FSReadSettingView* fsreadsettingview = new FSReadSettingView();
    if (fsreadsettingview && fsreadsettingview->initWithCenter(rect))
    {
        fsreadsettingview->autorelease();
        return fsreadsettingview;
    }
    CC_SAFE_DELETE(fsreadsettingview);
    return NULL;
}

bool FSReadSettingView::init()
{
    if (!CAView::init())
    {
        return false;
    }
    //    this->initView();
    return true;
}


void FSReadSettingView::initView()
{
    
    size = this->getBounds().size;
    
    m_HighlightSlider=CASlider::createWithCenter(CADipRect(size.width*0.5,size.height*0.12,size.width*0.8,size.height*0.1));
    m_HighlightSlider->setTag(201);
//    m_HighlightSlider->setMaxValue(100);
//    m_HighlightSlider->setMinValue(1);
    
    //m_HighlightSlider->setColor(ccc4(255, 255, 255, 255));
    
    m_HighlightSlider->addTarget(this, CAControl_selector(FSReadSettingView::highlightSliderValueChange));
//    m_HighlightSlider->addTargetForTouchUpSide(this, CAControl_selector(FSPageSliderView::pageSliderTouchUpSide));
    
    this->addSubview(m_HighlightSlider);
    m_HighlightSlider->setValue(CADevice::getScreenBrightness());
    CAView *lineView = CAView::createWithFrame(CADipRect(0,size.height*0.3,size.width,1));
    
    lineView->setColor(ccc4(0,0,0,255));
    this->addSubview(lineView);
    
    m_svContent = CAScrollView::createWithCenter(CADipRect(size.width*0.5,size.height*0.65,size.width*0.8,size.height*0.6));
    
    m_svContent->setShowsHorizontalScrollIndicator(false);
    m_svContent->setShowsVerticalScrollIndicator(false);
    //    m_svContent->setTouchMovedListenHorizontal(false);
    m_svContent->setBounceVertical(false);
    m_svContent->setTag(202);
//    m_svContent->setColor(ccc4(11,212,255,255));
    m_svContent->setBackGroundColor(MainColor);
    this->addSubview(m_svContent);
    
    addButtons();
}


void FSReadSettingView::addButtons()
{
  //  CADipSize boundsSize = m_svContent->getBounds().size;
    CCSize boundsSize = m_svContent->getBounds().size;
    
    float btnWidth = boundsSize.height*3/4;
    float btnSpace = boundsSize.height/6;
    CCArray *readSettingAry = FSDataManager::GetInstance().getAryReadSettingList();
    for (int i=0; i<readSettingAry->count(); i++) {
        CAButton* itemBtn = CAButton::createWithFrame(CCRectMake((btnWidth+btnSpace)*i,boundsSize.height/8,btnWidth,btnWidth), CAButtonTypeRoundedRect);
        itemBtn->setTag(i);
//        itemBtn->setColor(ccc4(255, 255, 255, 255));
        
          itemBtn->addTarget(this, CAControl_selector(FSReadSettingView::bgItemBtnClick), CAControlEventTouchUpInSide);
        
         itemBtn->setTitleColorForState(CAControlStateNormal, ccc4(51,204,255,255));
        
        //m_svContent->setContentSize(contentSize);

//        itemBtn->setImageAtlas(CrossApp::CAImageAtlas *var)

        CCDictionary *dicItem = (CCDictionary*)readSettingAry->objectAtIndex(i);
        //itemBtn->setImageForState(CAControlStateAll, imageItem);
        const CCString *strImagePath = dicItem->valueForKey(BgReadSettingImage);
    
        CAImage *itemImage = CAImage::create("bg/"+string( strImagePath->getCString()));
        itemBtn->setImageForState(CAControlStateAll, itemImage);
//        itemBtn->setImageColorForState(CAControlStateAll, ccc4(255, 255, 255, 255));
//        
//        CAView *btnView = itemBtn->getBackGroundViewForState(CAControlStateNormal);
//        btnView->setColor(ccc4(255, 255, 255, 255));
        m_svContent->addSubview(itemBtn);
        
    }
    
    CCSize contentSize =  CCSizeMake((btnWidth+btnSpace)*readSettingAry->count()+btnSpace,boundsSize.height);

    m_svContent->setViewSize(contentSize);
}

void FSReadSettingView::bgItemBtnClick(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
    int tag = control->getTag();
    CAUserDefault::sharedUserDefault()->setIntegerForKey(READSETTINGKEY, tag);
    
    if (changeReadSetting) {
        changeReadSetting();
    }
    
}


void FSReadSettingView::highlightSliderValueChange(CAControl* btn, CCPoint point)
{
    CASlider* p_Slider = (CASlider*)btn;
//    char value[50];
//    //maxValue = p_Slider->getMaxValue();
//    
//    sprintf(value, "第%.02f%页", p_Slider->getValue());
////    m_showPercent->setText(value);
//    CCLog(value);
    
    CADevice::setScreenBrightness(p_Slider->getValue());
    
}




