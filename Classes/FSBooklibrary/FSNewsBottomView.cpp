//
//  FSNewsBottomView.cpp
//  SharpMessage
//
//  Created by apple on 6/5/15.
//
//

#include "FSNewsBottomView.h"




FSNewsBottomView::FSNewsBottomView()
//: m_pContentLabel(NULL)
//, m_pTitleLabel(NULL)
//, m_pCAlertBtnEvent(NULL)
//, m_pCAlertTarget(NULL)
//, m_pBtnTableView(NULL)
//, m_sMsgFontName("")
//, m_fAlertViewHeight(0.0)
//, m_fAlertViewTitleHeight(0.0)
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
    
    m_listImage.pushBack(CAImage::create("tabbar_function/booklibrary_1.png"));
    m_listImage.pushBack(CAImage::create("tabbar_function/booklibrary_1.png"));
    m_listImage.pushBack(CAImage::create("tabbar_function/booklibrary_1.png"));
    
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


