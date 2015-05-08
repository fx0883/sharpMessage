//
//  FSBooklibraryCell.cpp
//  SharpMessage
//
//  Created by apple on 15/5/7.
//
//

#include "FSBooklibraryCell.h"





bool FSBooklibraryCell::init()
{

    
//        CAView* itemImageView = p_Cell->getSubviewByTag(99);
//        itemImageView->setColor(colorArr.at(row * 3 + item));
//        CCLog("%d", row * 3 + item);
//    
//        char pos[20] = "";
//        sprintf(pos, "(%d,%d,%d)", section, row, item);
//        CALabel* itemText = (CALabel*)p_Cell->getSubviewByTag(99)->getSubviewByTag(100);
//        itemText->setText(pos);

    
    
    return true;
}



void FSBooklibraryCell::initWithSize(CADipSize& cellSize)
{
    CADipSize _size = cellSize;
    
    
    
//    itemImage = CAImageView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
//    itemImage->setTag(99);
//    this->addSubview(itemImage);
    
//    CADipSize itemSize = itemImage->getBounds().size;
//        CALabel*   itemText = CALabel::createWithCenter(CADipRect(_size.width*0.5, _size.height*0.5, 150, 40));
//    itemText->setTag(100);
//    itemText->setFontSize(_px(29));
//    itemText->setTextAlignment(CATextAlignmentCenter);
//    itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    itemImage->addSubview(itemText);
    
    
    CAImageView* itemImage = CAImageView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
    itemImage->setTag(99);
    this->addSubview(itemImage);
    
    CADipSize itemSize = itemImage->getBounds().size;
    CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width*0.5, itemSize.height*0.5, 150, 40));
    itemText->setTag(100);
    itemText->setFontSize(_px(29));
    itemText->setTextAlignment(CATextAlignmentCenter);
    itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    itemImage->addSubview(itemText);
    
    
}



void FSBooklibraryCell::setNewsInfo(NewsInfo *newsinfo)
{
    
//    CCLOG("imageSrc = %s",newsinfo->getImageSrc());
    string strImage = "news/"+newsinfo->getImageSrc();
//    
//    
////    tabbar_function/bookRankingList_1.png
////    CAImage* image=CAImage::create(strImage);
//
//    CAImage* image=CAImage::create("tabbar_function/bookRankingList_1.png");
//    
//    itemText->setText(strImage);
    
    //itemText->setText("123123");
    
    //image->autorelease();
//    itemImage->setImage(image);
    
    CAImageView *itemImage = (CAImageView*)this->getSubviewByTag(99);
    CAImage* image=CAImage::create("news/112.png");
    itemImage->setImage(image);
    CALabel* itemText = (CALabel*)this->getSubviewByTag(99)->getSubviewByTag(100);
    itemText->setText(newsinfo->getNewsTitle());
    
    
}

