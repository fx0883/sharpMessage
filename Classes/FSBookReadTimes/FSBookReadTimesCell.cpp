//
//  FSBookReadTimesCell.cpp
//  SharpMessage
//
//  Created by apple on 7/3/15.
//
//

#include "FSBookReadTimesCell.h"

#include "AppMacros.h"

#define LEFTSPACE 20
#define TOPSPACE 20
#define BOTTOMSPACE 20

FSBookReadTimesCell::FSBookReadTimesCell()
{
    
}

FSBookReadTimesCell::~FSBookReadTimesCell()
{
    
}

FSBookReadTimesCell* FSBookReadTimesCell::create(const std::string& identifier, const CADipRect& _rect)
{
    FSBookReadTimesCell* tableViewCell = new FSBookReadTimesCell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->setFrame(_rect);
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void FSBookReadTimesCell::initWithCell()
{
    
    CADipSize _size = this->getBounds().size;
//    CAView *view = CAView::createWithFrame(this->getBounds());
//    view->setTag(99);
//    this->addSubview(view);
    
    CAImageView* itemImage = CAImageView::createWithFrame(CADipRect(LEFTSPACE, TOPSPACE, (_size.height-TOPSPACE-BOTTOMSPACE)*3/4, _size.height-TOPSPACE-BOTTOMSPACE));
    itemImage->setTag(99);
    this->addSubview(itemImage);
    
//    CADipSize itemSize = itemImage->getBounds().size;
//    CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width*0.5, itemSize.height+20, 150, 40));
//    itemText->setTag(100);
//    itemText->setFontSize(_px(29));
//    itemText->setTextAlignment(CATextAlignmentCenter);
//    itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    itemImage->addSubview(itemText);
    
    
    CALabel *textTitle = CALabel::createWithFrame(CADipRect(itemImage->getFrame().size.width+LEFTSPACE*2, TOPSPACE, _size.width-itemImage->getFrame().size.width-LEFTSPACE*2, (_size.height-TOPSPACE-BOTTOMSPACE)/2));
    
    textTitle->setTag(100);
        textTitle->setFontSize(_px(29));
        textTitle->setTextAlignment(CATextAlignmentLeft);
        textTitle->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//        textTitle->setColor(ccc4(100,100,100,1));
    this->addSubview(textTitle);
    
    
    CALabel *authorTitle = CALabel::createWithFrame(CADipRect(itemImage->getFrame().size.width+LEFTSPACE*2, TOPSPACE+(_size.height-TOPSPACE-BOTTOMSPACE)/2, _size.width-itemImage->getFrame().size.width-LEFTSPACE-LEFTSPACE, (_size.height-TOPSPACE-BOTTOMSPACE)/2));
    authorTitle->setTag(101);
    authorTitle->setFontSize(_px(29));
    authorTitle->setTextAlignment(CATextAlignmentLeft);
    authorTitle->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    this->addSubview(authorTitle);
    
//    CADipSize m_size = this->getFrame().size;
//    CALabel* cellText = CALabel::createWithCenter(CADipRect(m_size.width*0.1, m_size.height*0.5, m_size.width*0.3, m_size.height*0.8));
//    cellText->setTag(100);
//    cellText->setFontSize(_px(30));
//    cellText->setTextAlignment(CATextAlignmentCenter);
//    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    this->addSubview(cellText);
    
//    CAButton* btnOnCell = CAButton::createWithCenter(CADipRect(m_size.width*0.85, m_size.height*0.5, m_size.width*0.2, m_size.height*0.7), CAButtonTypeRoundedRect);
//    btnOnCell->setTag(102);
//    btnOnCell->setTitleForState(CAControlStateAll, "Touch");
//    btnOnCell->addTarget(this, CAControl_selector(FSBookReadTimesCell::cellBtnCallback), CAControlEventTouchUpInSide);
//    this->addSubview(btnOnCell);
}

void FSBookReadTimesCell::updateNewsInfoForCell(NewsInfo *newsinfo)
{
    
    //    CCLOG("imageSrc = %s",newsinfo->getImageSrc());
    string strImage = "news/"+newsinfo->getImageSrc();
    //
    CAImageView *itemImage = (CAImageView*)this->getSubviewByTag(99);
    CAImage* image=CAImage::create(strImage);
    itemImage->setImage(image);
    CALabel* itemText = (CALabel*)this->getSubviewByTag(100);
    itemText->setText(newsinfo->getNewsTitle());
    CALabel* authorTitle = (CALabel*)this->getSubviewByTag(101);
    authorTitle->setText(newsinfo->getAuthor());
    
}


void FSBookReadTimesCell::cellBtnCallback(CAControl* btn, CCPoint point)
{
    
}

void FSBookReadTimesCell::normalTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg4.png")));
}

void FSBookReadTimesCell::highlightedTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
}

void FSBookReadTimesCell::selectedTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg3.png")));
}

void FSBookReadTimesCell::disabledTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_disabled.png")));
}