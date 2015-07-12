//
//  FSNewsBottomView.cpp
//  SharpMessage
//
//  Created by apple on 6/5/15.
//
//

#include "FSNewsBottomView.h"




FSNewsBottomView::FSNewsBottomView()
: openCatalog(NULL)
,m_pageSlider(NULL)

{
    
}


FSNewsBottomView::~FSNewsBottomView()
{
//    CC_SAFE_RELEASE_NULL(m_pTitleLabel);
//    CC_SAFE_RELEASE_NULL(m_pContentLabel);
//    CC_SAFE_RELEASE_NULL(m_pBtnTableView);
}


FSNewsBottomView* FSNewsBottomView::createWithFrame(const CCRect& rect)
{
    FSNewsBottomView* fsnewsbottomview = new FSNewsBottomView();
    if (fsnewsbottomview && fsnewsbottomview->initWithFrame(rect))
    {
        fsnewsbottomview->autorelease();
        return fsnewsbottomview;
    }
    CC_SAFE_DELETE(fsnewsbottomview);
    return NULL;
}

FSNewsBottomView* FSNewsBottomView::createWithCenter(const CCRect& rect)
{
    FSNewsBottomView* fsnewsbottomview = new FSNewsBottomView();
    if (fsnewsbottomview && fsnewsbottomview->initWithCenter(rect))
    {
        fsnewsbottomview->autorelease();
        return fsnewsbottomview;
    }
    CC_SAFE_DELETE(fsnewsbottomview);
    return NULL;
}

bool FSNewsBottomView::init()
{
    if (!CAView::init())
    {
        return false;
    }
//    this->initView();
    return true;
}


void FSNewsBottomView::setTouchSelected(CrossApp::CAControl *control, CrossApp::CCPoint point)
{
    int index = control->getTag();
    switch (index) {
        case 0:
            if (openCatalog) {
                openCatalog();
            }
            break;
        case 1:
            if(showPageSlider)
            {
                showPageSlider();
            }
            break;
        case 2:
            if (showReadSettingView) {
                showReadSettingView();
            }
        default:
            break;
    }
//    if (!m_sForbidSelectedIndexs.count(index))
//    {
//        this->setSelectedAtIndex(control->getTag());
//        
//        if (m_pDelegate)
//        {
//            m_pDelegate->tabBarSelectedItem(this, m_pSelectedItem, m_nSelectedIndex);
//        }
//    }
//    else
//    {
//        if (m_pDelegate)
//        {
//            m_pDelegate->tabBarClickToForbidSelectedItem(this, m_pSelectedItem, m_nSelectedIndex);
//        }
//    }
    
}







void FSNewsBottomView::initView()
{

    CCSize rectItemSize = this->getBounds().size;
    
//    float startX = rectItemSize.width / 3;
//    float startY = rectItemSize.height / 10;
    
    //CCLog("width===============================rectItemSizeWidth==========================%f",rectItemSize.width);
    //rectItemSize.width = MIN(rectItemSize.width, 1024);

    rectItemSize.width = rectItemSize.width / (3*CAApplication::getApplication()->getAdaptationRatio()) ;

    CCLog("width===============================rectItemSizeWidth============================%f",rectItemSize.width);
    
    m_listImage.pushBack(CAImage::create("image/index.png"));
    m_listImage.pushBack(CAImage::create("image/progress.png"));
    m_listImage.pushBack(CAImage::create("image/setting.png"));
    
//    m_listText.pushBack("目录");
//    m_listText.pushBack("进度");
//    m_listText.pushBack("设置");
    
    m_listText.push_back("目录");
    m_listText.push_back("进度");
    m_listText.push_back("设置");


    
    for (int i=0; i<3; i++) {
        
        
        CADipRect rect = CADipRectZero;
        rect.size = rectItemSize;
        rect.size.width = rectItemSize.width;
        rect.origin.x = rectItemSize.width * i;
        
        
        CCLog("rectX=======================%f======= i=%d ",rect.origin.x,i);
        CCLog("rect*****************=======%f       i===========%d== ",rect.size.width,i);
        
        CAButton* btn = CAButton::createWithFrame(rect, CAButtonTypeCustom);
        
        
        
        
        
        this->addSubview(btn);
        btn->setTag(i);
        
        btn->addTarget(this, CAControl_selector(FSNewsBottomView::setTouchSelected), CAControlEventTouchUpInSide);

        
        CAImage* imageItem = m_listImage.at(i);
        btn->setTitleForState(CAControlStateAll, m_listText.at(i));
//         btn->setTitleForState(CAControlStateHighlighted, "设置");
//         btn->setTitleForState(CAControlStateDisabled, "设置");
//         btn->setTitleForState(CAControlStateSelected, "设置");
        btn->setTitleColorForState(CAControlStateAll, CAColor_white);
        btn->setImageForState(CAControlStateAll, imageItem);
        //btn->setTitleForState(CAControlStateAll, "ts");
            
        

//        button->setTitleColorForState(CAControlStateNormal, m_cButtonColor);
       // btn->setTitleForState(CAControlStateHighlighted, "设置");
//        btn->setImageForState(CAControlStateSelected, imageItem);
       // btn->setBackGroundViewForState(CAControlStateNormal, CAView::createWithColor(CAColor_clear));
        
    }
 
//    addSlider();


    
    
  //  CCRectMake(startX, startY, 40, 40);
    
    
    //m_CataloguesButton = CAButton::createWithFrame(<#const CrossApp::CCRect &rect#>, <#const CAButtonType &buttonType#>)
    
    
    
    
    
    
    
    
    
    
    
    
//    m_cItemSize = m_pContentView->getBounds().size;
//    m_cItemSize.width = rect.size.width/count;
//    
//    if (m_pButtons.empty())
//    {
//        for (unsigned int i=0; i<count; i++)
//        {
//            CADipRect rect = CADipRectZero;
//            rect.size = m_cItemSize;
//            rect.origin.x = m_cItemSize.width * i;
//            
//            CAButton* btn = CAButton::createWithFrame(rect, CAButtonTypeCustom);
//            m_pContentView->addSubview(btn);
//            btn->setTag(i);
//            btn->addTarget(this, CAControl_selector(CATabBar::setTouchSelected), CAControlEventTouchUpInSide);
//            m_pButtons.pushBack(btn);
//            
//        }
//    }
    
    
    
    

//    btn->setTitleForState(CAControlStateAll, m_pItems.at(i)->getTitle());
//    btn->setTitleColorForState(CAControlStateAll, m_sTitleColor);
//    btn->setTitleColorForState(CAControlStateHighlighted, m_sSelectedTitleColor);
//    btn->setTitleColorForState(CAControlStateSelected, m_sSelectedTitleColor);
//    btn->setImageForState(CAControlStateNormal, m_pItems.at(i)->getImage());
//    CAImage* selectedImage = m_pItems.at(i)->getSelectedImage()
//    ? m_pItems.at(i)->getSelectedImage()
//    : m_pItems.at(i)->getImage();
//    btn->setImageForState(CAControlStateHighlighted, selectedImage);
//    btn->setImageForState(CAControlStateSelected, selectedImage);
//    btn->setBackGroundViewForState(CAControlStateNormal, CAView::createWithColor(CAColor_clear));
//    if (m_pSelectedBackGroundImage)
//    {
//        btn->setBackGroundViewForState(CAControlStateHighlighted,
//                                       CAScale9ImageView::createWithImage(m_pSelectedBackGroundImage));
//        btn->setBackGroundViewForState(CAControlStateSelected,
//                                       CAScale9ImageView::createWithImage(m_pSelectedBackGroundImage));
//    }
//    else
//    {
//        btn->setBackGroundViewForState(CAControlStateHighlighted,
//                                       CAView::createWithColor(m_sSelectedBackGroundColor));
//        btn->setBackGroundViewForState(CAControlStateSelected,
//                                       CAView::createWithColor(m_sSelectedBackGroundColor));
//    }
//    btn->setAllowsSelected(true);
    
    
    
}


//void FSNewsBottomView::addSlider()
//{
//    m_pageSlider = CASlider::createWithFrame(this->getBounds());
//    
////    CASlider* defaultSlider = CASlider::createWithCenter(CADipRect(size.width*0.5,size.height*0.2,size.width*0.7,20));
////    defaultSlider->addTarget(this, CAControl_selector(SliderTest::defaultSliderValueChange));
////    this->getView()->addSubview(defaultSlider);
//    
//
//    m_pageSlider->setMinValue(0);
//    m_pageSlider->addTarget(this, CAControl_selector(FSNewsBottomView::pageSliderValueChange));
//    this->addSubview(m_pageSlider);
//}


//void FSNewsBottomView::pageSliderValueChange(CAControl* btn, CCPoint point)
//{
//    CASlider* p_Slider = (CASlider*)btn;
////    sprintf(value, "%.02f%%", p_Slider->getValue() * 100);
////    sliderValue->setText(value);
//    if (changePage) {
//        float pageNumber = p_Slider->getValue();
//        int pageNumberInt = (int)pageNumber;
////        if (pageNumber>pageNumberInt) {
////            
////        }
//        if (pageNumber - pageNumberInt >0) {
//            pageNumberInt++;
//        }
//        changePage(pageNumberInt);
//    }
//    
//}




