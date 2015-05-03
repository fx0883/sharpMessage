//
//  FSBooklibrary.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/19.
//
//

#include "FSBooklibrary.h"
#include <string>
#include "FSDataManager.h"
#include "PublicHeader.h"
#include "NewsInfo.h"
#include "FSNewsManager.h"
using namespace std;


FSBooklibrary::FSBooklibrary()
{
    
}

FSBooklibrary::~FSBooklibrary()
{
    
}

void FSBooklibrary::viewDidLoad()
{
    // Do any additional setup after loading the view from its nib.
    CCRect winRect = this->getView()->getBounds();
    CAImageView* imageView = CAImageView::createWithImage(CAImage::create("r/HelloWorld.png"));
    imageView->setImageViewScaleType(CAImageViewScaleTypeFitImageInside);
    imageView->setFrame(winRect);
    this->getView()->addSubview(imageView);
    
    CALabel* label = CALabel::createWithCenter(CCRect(winRect.size.width*0.5, winRect.size.height*0.5-270, winRect.size.width, 200));
    label->setTextAlignment(CATextAlignmentCenter);
    label->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    label->setFontSize(_px(72));
    
    std::string fileTitle = CAUserDefault::sharedUserDefault()->getStringForKey("title");
    
    
    
    for (int i=0; i<FSDataManager::GetInstance().getNewsManager().arynewsList.count(); i++) {
        
        
        NewsInfo *newsInfo = (NewsInfo*)FSDataManager::GetInstance().getNewsManager().arynewsList.objectAtIndex(i);
        
        label->setText(newsInfo->getNewsTitle().c_str());

    }
    
    
//    CCLog("fileTitle = %s",fileTitle.c_str());
//    label->setText(fileTitle);
  //  label->setText("Hello World!");
    label->setColor(CAColor_white);
    this->getView()->insertSubview(label, 1);
    
//    std::string fileTitle = CAUserDefault::sharedUserDefault()->getStringForKey("file");
//    label->setText(fileTitle);

}

void FSBooklibrary::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}