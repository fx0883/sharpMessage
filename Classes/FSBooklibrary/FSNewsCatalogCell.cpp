//
//  FSNewsCatalogCell.cpp
//  SharpMessage
//
//  Created by apple on 6/7/15.
//
//

#include "FSNewsCatalogCell.h"
#include "AppMacros.h"


FSNewsCatalogCell::FSNewsCatalogCell()
{
    
}

FSNewsCatalogCell::~FSNewsCatalogCell()
{
    
}

FSNewsCatalogCell* FSNewsCatalogCell::create(const std::string& identifier, const CADipRect& _rect)
{
    FSNewsCatalogCell* tableViewCell = new FSNewsCatalogCell();
    if(tableViewCell&&tableViewCell->initWithReuseIdentifier(identifier))
    {
        tableViewCell->setFrame(_rect);
        tableViewCell->autorelease();
        return tableViewCell;
    }
    CC_SAFE_DELETE(tableViewCell);
    return NULL;
}

void FSNewsCatalogCell::initWithCell()
{
    CADipSize m_size = this->getBounds().size;
//    CALabel* cellText = CALabel::createWithCenter(CADipRect(m_size.width*0.1, m_size.height*0.5, m_size.width*0.3, m_size.height*0.8));
    
    
    CALabel* cellText = CALabel::createWithFrame(CADipRect(50,0,m_size.width-50,m_size.height));
    cellText->setTag(100);
    float curFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24;
    cellText->setFontSize(curFontSize);
    cellText->setTextAlignment(CATextAlignmentLeft);
    cellText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    this->addSubview(cellText);
    
//    CAButton* btnOnCell = CAButton::createWithCenter(CADipRect(m_size.width*0.85, m_size.height*0.5, m_size.width*0.2, m_size.height*0.7), CAButtonTypeRoundedRect);
//    btnOnCell->setTag(102);
//    btnOnCell->setTitleForState(CAControlStateAll, "Touch");
//    btnOnCell->addTarget(this, CAControl_selector(MyTableViewCell::cellBtnCallback), CAControlEventTouchUpInSide);
//    this->addSubview(btnOnCell);
}


void FSNewsCatalogCell::setSelectedCell(bool bIsSelected)
{
    CALabel* cell = (CALabel*)this->getSubviewByTag(100);
    if (bIsSelected) {
        cell->setColor(ccc4(15,112,2,132));
    }
    else
    {
        cell->setColor(ccc4(0,0,24,132));
    }
}




void FSNewsCatalogCell::updateCell(string strTitle)
{
    CALabel* cell = (CALabel*)this->getSubviewByTag(100);
    if (cell) {
        cell->setText(strTitle);
    }
}

void FSNewsCatalogCell::normalTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg4.png")));
}

void FSNewsCatalogCell::highlightedTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
}

void FSNewsCatalogCell::selectedTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/cell_bkg3.png")));
}

void FSNewsCatalogCell::disabledTableViewCell()
{
//    this->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_disabled.png")));
}