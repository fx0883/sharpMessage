//
//  FSNewsViewCell.cpp
//  SharpMessage
//
//  Created by apple on 15/5/17.
//
//

#include "FSNewsViewCell.h"

FSNewsViewCell::FSNewsViewCell()
{
    
}

FSNewsViewCell::~FSNewsViewCell()
{
    
}

FSNewsViewCell* FSNewsViewCell::create(const std::string& identifier, const CADipRect& _rect)
{
    FSNewsViewCell* tableViewCell = new FSNewsViewCell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->setFrame(_rect);
        tableViewCell->setColor(CAColor_green);
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void FSNewsViewCell::setContent(const std::string& strContext)
{
    
    
    
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    cellText->setText(strContext);
  //  cellText->sizeToFit();
    
//    CCLOG("1======%d",(int)strContext.size());
//    
//    
//    
//    string str = "我是一个好人，我是一个好人，我是一个好人，";
//    
//        CCLOG("2======%d",(int)str.size());
//    cellText->setText("我是一个好人，我是一个好人，我是一个好人，");
}

void FSNewsViewCell::updateWithCell()
{

    CADipSize size = this->getBounds().size;
    CALabel *cellText = (CALabel*)this->getSubviewByTag(100);
    if(cellText==NULL)
    {
        cellText = CALabel::createWithCenter(CCRect(size.width*0.5, size.height*0.5, size.width, size.height));
        this->addSubview(cellText);
        //cellText->setColor(<#const CAColor4B &color#>)
    }
    else
    {
        cellText->setFrame(CCRect(0, 0, size.width, size.height));
    }
    cellText->setTag(100);
    cellText->setFontSize(_px(38));
    //cellText->setColor(new CAColor4B(100,100,100,1));
    cellText->setTextAlignment(CATextAlignmentLeft);
   // cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    
    
}


//void FSNewsViewCell::cellBtnCallback(CAControl* btn, CCPoint point)
//{
//    
//}

void FSNewsViewCell::normalTableViewCell()
{
    //this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg4.png")));
}

void FSNewsViewCell::highlightedTableViewCell()
{
    //this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
}

void FSNewsViewCell::selectedTableViewCell()
{
    //this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg3.png")));
}

void FSNewsViewCell::disabledTableViewCell()
{
    //this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_disabled.png")));
}