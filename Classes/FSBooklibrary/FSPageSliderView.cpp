//
//  FSPageSliderView.cpp
//  SharpMessage
//
//  Created by apple on 6/8/15.
//
//

#include "FSPageSliderView.h"
#include "AppMacros.h"

FSPageSliderView::FSPageSliderView()
: changePage(NULL)

{
    
}


FSPageSliderView::~FSPageSliderView()
{


}


FSPageSliderView* FSPageSliderView::createWithFrame(const CCRect& rect)
{
    FSPageSliderView* fspagesliderview = new FSPageSliderView();
    if (fspagesliderview && fspagesliderview->initWithFrame(rect))
    {
        fspagesliderview->autorelease();
        return fspagesliderview;
    }
    CC_SAFE_DELETE(fspagesliderview);
    return NULL;
}

FSPageSliderView* FSPageSliderView::createWithCenter(const CCRect& rect)
{
    FSPageSliderView* fspagesliderview = new FSPageSliderView();
    if (fspagesliderview && fspagesliderview->initWithCenter(rect))
    {
        fspagesliderview->autorelease();
        return fspagesliderview;
    }
    CC_SAFE_DELETE(fspagesliderview);
    return NULL;
}

bool FSPageSliderView::init()
{
    if (!CAView::init())
    {
        return false;
    }
    //    this->initView();
    return true;
}


void FSPageSliderView::initView()
{
    
    size = this->getBounds().size;
    
    m_showPercent = CALabel::createWithCenter(CADipRect(size.width*0.5,size.height*0.2,size.width,size.height*0.4));
    float percentFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 18;
    m_showPercent->setFontSize(percentFontSize);
    m_showPercent->setTextAlignment(CATextAlignmentCenter);
    m_showPercent->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    m_showPercent->setTag(201);
    this->addSubview(m_showPercent);
    m_showPercent->setText("第1页");
    
    
    

    m_pageSlider=CASlider::createWithCenter(CADipRect(size.width*0.5,size.height*0.7,size.width*0.8,size.height*0.3));
    m_pageSlider->setTag(202);
    m_pageSlider->setMaxValue(m_maxPage);
    m_pageSlider->setMinValue(0);
    m_pageSlider->addTarget(this, CAControl_selector(FSPageSliderView::pageSliderValueChange));
    m_pageSlider->addTargetForTouchUpSide(this, CAControl_selector(FSPageSliderView::pageSliderTouchUpSide));
    
    this->addSubview(m_pageSlider);
}





void FSPageSliderView::pageSliderValueChange(CAControl* btn, CCPoint point)
{
    CASlider* p_Slider = (CASlider*)btn;
    char value[50];
    //maxValue = p_Slider->getMaxValue();
    
    sprintf(value, "第%.02d%页", (int)p_Slider->getValue()+1);
    m_showPercent->setText(value);
    
}

void FSPageSliderView::pageSliderTouchUpSide(CAControl* btn, CCPoint point)
{
    CASlider* p_Slider = (CASlider*)btn;
    //    sprintf(value, "%.02f%%", p_Slider->getValue() * 100);
    //    sliderValue->setText(value);
    if (changePage) {
        float pageNumber = p_Slider->getValue();
        int pageNumberInt = (int)pageNumber;
        //        if (pageNumber>pageNumberInt) {
        //
        //        }
        if (pageNumber - pageNumberInt >0) {
            pageNumberInt++;
        }
        changePage(pageNumberInt);
    }
}

void FSPageSliderView::setSliderMax(float maxPage)
{
    if (m_pageSlider) {
        m_pageSlider->setMaxValue(maxPage);
        this->initSlider();
    }
}
void FSPageSliderView::initSlider()
{
    m_pageSlider->setValue(1);
    m_showPercent->setText("第1页");

}

void FSPageSliderView::setSliderCurPage(int page)
{
    m_pageSlider->setValue(page);
    char value[50];
    //maxValue = p_Slider->getMaxValue();
    
    sprintf(value, "第%.02d%页", page);
    m_showPercent->setText(value);

}




