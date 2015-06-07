#include "FSNewsView2Cell.h"
#include "AppMacros.h"

#define bottomMargin 50
FSNewsView2Cell::FSNewsView2Cell()
{

}

FSNewsView2Cell::~FSNewsView2Cell()
{

}

FSNewsView2Cell* FSNewsView2Cell::create(const std::string& identifier, const CADipRect& _rect)
{
	FSNewsView2Cell* listViewCell = new FSNewsView2Cell();
	if (listViewCell&&listViewCell->initWithReuseIdentifier(identifier))
	{
		listViewCell->setFrame(_rect);
		listViewCell->autorelease();
		return listViewCell;
	}
	CC_SAFE_DELETE(listViewCell);
	return NULL;
}

void FSNewsView2Cell::initWithCell()
{
	CADipSize _size = this->getBounds().size;
    CAView *view = CAView::createWithFrame(this->getBounds());
    view->setTag(99);
    this->addSubview(view);
    
    CALabel* test = CALabel::createWithFrame(CADipRectMake(0, 0, _size.width, _size.height-NEWSCELLBOTTOMHEIGHT));
	test->setTextAlignment(CATextAlignmentLeft);
//	test->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//	test->setFontSize(_px(40));
	test->setTag(100);
	this->addSubview(test);
    

    CALabel* bottomLabel = CALabel::createWithFrame(CADipRectMake(0, _size.height-NEWSCELLBOTTOMHEIGHT, _size.width-bottomMargin, NEWSCELLBOTTOMHEIGHT));
    bottomLabel->setTag(101);
    this->addSubview(bottomLabel);

}

void FSNewsView2Cell::updateWithCell()
{
    
    CADipSize size = this->getBounds().size;
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    if(cellText==NULL)
    {
//        cellText = CALabel::createWithCenter(CCRect(size.width*0.5, size.height*0.5, size.width-6, size.height));
        cellText = CALabel::createWithFrame(CADipRectMake(0, 0, size.width, size.height-NEWSCELLBOTTOMHEIGHT));
        this->addSubview(cellText);
        //cellText->setColor(<#const CAColor4B &color#>)
    }
    else
    {
        //cellText->setFrame(CCRect(0, 0, size.width, size.height));
        cellText->setFrame(CADipRectMake(0, 0, size.width, size.height-NEWSCELLBOTTOMHEIGHT));
    }
    cellText->setTag(100);
    
    float width1 = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width;
    
    //CCLog("width1==============width1================%f",width1);

    
    float width2 = CrossApp::CCEGLView::sharedOpenGLView()->getFrameSize().width;
    
    //CCLog("width2==============width2================%f",width2);
    
    
    float curFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 34;
    
    CCLog("curFontSize==============curFontSize================%f",curFontSize);
    CCLog("curFontSize==============getBounds().size.height================%f",this->getBounds().size.height);
    
    
    
    
//    int fontHeight = CAImage::getFontHeight(m_nfontName.c_str(), m_nfontSize);
//    int defaultLineSpace = fontHeight / 4;
    
//    float curRatio = CAApplication::getApplication()->getAdaptationRatio();
//    CCLog("curRatio==============curRatio================%f",curRatio);
//    cellText->setFontSize(_px(curFontSize));
    cellText->setFontSize(curFontSize);
    //cellText->setColor(new CAColor4B(100,100,100,1));
    cellText->setTextAlignment(CATextAlignmentLeft);
    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    
    
    CALabel *bottomLabel = (CALabel*)this->getSubviewByTag(101);
    bottomLabel->setFrame (CADipRectMake(0, size.height-NEWSCELLBOTTOMHEIGHT, size.width-bottomMargin, NEWSCELLBOTTOMHEIGHT));
    float percentFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 18;
    bottomLabel->setFontSize(percentFontSize);
    bottomLabel->setTextAlignment(CATextAlignmentRight);
    bottomLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    bottomLabel->setTag(101);
    
    CAView *view = (CAView*)this->getSubviewByTag(99);
    //view->setColor(new CAColor4B(100,100,100,1));
    view->setColor(ccc4(151,212,255,255));
    
    
    
    
    int lintFontHeihtItem = cellText->getLineFontHeight();
    CCLog("lintFontHeihtItem================%d",lintFontHeihtItem);
}

void FSNewsView2Cell::setContent(const std::string& strContext)
{
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    cellText->setText(strContext);

    
//    CALabel *bottomLabel = (CALabel*)this->getSubviewByTag(101);
    
    
}

void FSNewsView2Cell::setContent(const std::string& strContext,float percent)
{
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    cellText->setText(strContext);
    percent = percent * 100;
    
    CALabel *bottomLabel = (CALabel*)this->getSubviewByTag(101);
    char strPercent[50];
    sprintf(strPercent, "%20.2f", percent);
    bottomLabel->setText(string(strPercent)+"%");
}



void FSNewsView2Cell::cellBtnCallback(CAControl* btn, CCPoint point)
{

}

void FSNewsView2Cell::normalListViewCell()
{
	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg4.png")));
}

void FSNewsView2Cell::highlightedListViewCell()
{
	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
}

void FSNewsView2Cell::selectedListViewCell()
{
	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/ex4.png")));
}

void FSNewsView2Cell::disabledListViewCell()
{
	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/ex5.png")));
}