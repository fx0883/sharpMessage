#include "FSNewsView2Cell.h"
#include "AppMacros.h"
#include "FSDataManager.h"

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
    
    
    CAScale9ImageView *bgImageView = CAScale9ImageView::createWithFrame(this->getBounds());
    bgImageView->setTag(98);
    this->addSubview(bgImageView);
    
    
    CALabel* test = CALabel::createWithFrame(CADipRectMake(0, 0+NEWSCELLTOPHEIGHT, _size.width-NEWSCELLSPACEWIDTH+NEWSCELLSPACEWIDTH, _size.height-NEWSCELLBOTTOMHEIGHT-NEWSCELLTOPHEIGHT));
	test->setTextAlignment(CATextAlignmentLeft);
	test->setTag(100);
	this->addSubview(test);
    

    CALabel* bottomLabel = CALabel::createWithFrame(CADipRectMake(0, _size.height-NEWSCELLTOPHEIGHT-NEWSCELLBOTTOMHEIGHT, _size.width-NEWSCELLSPACEWIDTH*4, NEWSCELLBOTTOMHEIGHT));
    bottomLabel->setTag(101);
    this->addSubview(bottomLabel);

}

void FSNewsView2Cell::updateWithCell()
{
    
    CADipSize size = this->getBounds().size;
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
//    if(cellText==NULL)
//    {
//
//        cellText = CALabel::createWithFrame(CADipRectMake(0+NEWSCELLSPACEWIDTH, 0+NEWSCELLTOPHEIGHT, size.width-NEWSCELLSPACEWIDTH*2, size.height-NEWSCELLBOTTOMHEIGHT-NEWSCELLTOPHEIGHT));
//
//    }
//    else
    {
        //cellText->setFrame(CCRect(0, 0, size.width, size.height));
        cellText->setFrame(CADipRectMake(0+NEWSCELLSPACEWIDTH, 0+NEWSCELLTOPHEIGHT, size.width-NEWSCELLSPACEWIDTH*1.5, size.height-NEWSCELLBOTTOMHEIGHT-NEWSCELLTOPHEIGHT));
    }
    cellText->setTag(100);
    
    float width1 = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width;
    
    //CCLog("width1==============width1================%f",width1);

    
    float width2 = CrossApp::CCEGLView::sharedOpenGLView()->getFrameSize().width;
    
    //CCLog("width2==============width2================%f",width2);
    
    
    float curFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 32;
    
    CCLog("curFontSize==============curFontSize================%f",curFontSize);
    CCLog("curFontSize==============getBounds().size.height================%f",this->getBounds().size.height);
    
    cellText->setFontSize(curFontSize);
    //cellText->setColor(new CAColor4B(100,100,100,1));
    cellText->setTextAlignment(CATextAlignmentLeft);
    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    
    
    CALabel *bottomLabel = (CALabel*)this->getSubviewByTag(101);
    bottomLabel->setFrame (CADipRectMake(0, size.height-NEWSCELLTOPHEIGHT-NEWSCELLBOTTOMHEIGHT, size.width-NEWSCELLSPACEWIDTH*5, NEWSCELLBOTTOMHEIGHT));
    float percentFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 18;
    bottomLabel->setFontSize(percentFontSize);
    bottomLabel->setTextAlignment(CATextAlignmentRight);
    bottomLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    bottomLabel->setTag(101);

    CAView *view = (CAView*)this->getSubviewByTag(99);

    view->setColor(ccc4(151,212,255,255));
    
    //CCDrawNode
    
    
//    int tag = control->getTag();
//    CAUserDefault::sharedUserDefault()->setIntegerForKey(READSETTINGKEY, tag);
//    
    
    
    CAScale9ImageView *bgImageView = (CAScale9ImageView*)this->getSubviewByTag(98);
    
    int indexReadSetting = CAUserDefault::sharedUserDefault()->getIntegerForKey(READSETTINGKEY, 0);
    CCArray *readSettingAry = FSDataManager::GetInstance().getAryReadSettingList();

        
    CCDictionary *dicItem = (CCDictionary*)readSettingAry->objectAtIndex(indexReadSetting);
    const CCString *strImagePath = dicItem->valueForKey(BgReadSettingImage);
        
    CAImage *itemImage = CAImage::create("bkg/"+string( strImagePath->getCString()));
    //itemImage->autorelease();
    bgImageView->setImage(itemImage);
    
    
    CCDictionary *dicColor = (CCDictionary*)dicItem->objectForKey(FontColor);
    const CCString *r = dicColor->valueForKey("r");
    const CCString *g = dicColor->valueForKey("g");
    const CCString *b = dicColor->valueForKey("b");
    const CCString *a = dicColor->valueForKey("a");
    
    int rint = r->intValue();
    int gint = g->intValue();
    int bint = b->intValue();
    int aint = a->intValue();
    
    
    cellText->setColor(ccc4(rint,gint,bint,aint));
    bottomLabel->setColor(ccc4(rint,gint,bint,aint));
        //cellText->setColor(new CAColor4B(100,100,100,1));
    
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
//	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg4.png")));
}

void FSNewsView2Cell::highlightedListViewCell()
{
//	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
}

void FSNewsView2Cell::selectedListViewCell()
{
	//this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/ex4.png")));
}

void FSNewsView2Cell::disabledListViewCell()
{
//	this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/ex5.png")));
}