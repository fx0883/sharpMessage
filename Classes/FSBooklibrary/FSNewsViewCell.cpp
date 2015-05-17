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
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void FSNewsViewCell::setContent(const std::string& strContext)
{
    cellText->setText(strContext);
    

}

void FSNewsViewCell::initWithCell()
{
//    CADipSize m_size = this->getFrame().size;
    
    cellText = CALabel::createWithFrame(this->getFrame());
    cellText->setTag(100);
    cellText->setFontSize(_px(30));
    cellText->setTextAlignment(CATextAlignmentCenter);
    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    this->addSubview(cellText);
    
//    CAButton* btnOnCell = CAButton::createWithCenter(CADipRect(m_size.width*0.85, m_size.height*0.5, m_size.width*0.2, m_size.height*0.7), CAButtonTypeRoundedRect);
//    btnOnCell->setTag(102);
//    btnOnCell->setTitleForState(CAControlStateAll, "Touch");
//    btnOnCell->addTarget(this, CAControl_selector(FSNewsViewCell::cellBtnCallback), CAControlEventTouchUpInSide);
//    this->addSubview(btnOnCell);
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