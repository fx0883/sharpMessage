#include "FSNewsView2Cell.h"
#include "AppMacros.h"
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
	CADipSize _size = this->getFrame().size;
//	CALabel* test = CALabel::createWithCenter(CADipRect(_size.width*0.5,
//		_size.height*0.5,
//		_size.width,
//		_size.height));
    
    
    CAView *view = CAView::createWithFrame(this->getBounds());
    view->setTag(99);
    this->addSubview(view);
    
    CALabel* test = CALabel::createWithFrame(this->getBounds());
	test->setTextAlignment(CATextAlignmentLeft);
//	test->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	test->setFontSize(_px(40));
	test->setTag(100);
	this->addSubview(test);
}

void FSNewsView2Cell::updateWithCell()
{
    
    CADipSize size = this->getBounds().size;
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    if(cellText==NULL)
    {
//        cellText = CALabel::createWithCenter(CCRect(size.width*0.5, size.height*0.5, size.width-6, size.height));
        cellText = CALabel::createWithFrame(this->getBounds());
        this->addSubview(cellText);
        //cellText->setColor(<#const CAColor4B &color#>)
    }
    else
    {
        //cellText->setFrame(CCRect(0, 0, size.width, size.height));
        cellText->CALabel::createWithFrame(this->getBounds());
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
    
    float curRatio = CAApplication::getApplication()->getAdaptationRatio();
//    CCLog("curRatio==============curRatio================%f",curRatio);
//    cellText->setFontSize(_px(curFontSize));
       cellText->setFontSize(curFontSize);
    //cellText->setColor(new CAColor4B(100,100,100,1));
    cellText->setTextAlignment(CATextAlignmentLeft);
    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    
    
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
//    cellText->sizeToFit();
    
//    CCLOG("1======%d",(int)strContext.size());
//    CCLOG("2======%s",strContext.c_str());
//    cellText->setText("我是一个好人，我是一个好人，我是一个好人，\n 那么问题来了\n 大家都认为我是好人嘛？\n我是一个好人，我是一个好人，我是一个好人，\n 那么问题来了\n 大家都认为我是好人嘛？\n");
//    
//    
//    cellText->setText("\"\x88！\”陆高止说得一声：“关上门，别做声！”就闭上眼不言不语了。李沅芷究是将门之女，平时抡刀使枪惯了的，虽然惊慌，还是依言关上了门。\\343\200 {(_M_p = \"\x88！\”陆高止说得一声：“关上门，别做声！”就闭上眼不言不语了。李沅芷究是将门之女，平时抡刀使枪惯了的，虽然惊慌，还是依言关上了门。\n　\343\200)}");
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