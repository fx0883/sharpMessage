//
//  FSNewsAboutDetailController.cpp
//  SharpMessage
//
//  Created by apple on 7/6/15.
//
//

#include "FSNewsAboutDetailController.h"
#include "FSData.h"

#define NEWSINTRO "金庸小说主要是指金庸的武侠小说，一共十五部，它们可以由这几句话描述：\"飞雪连天射白鹿，笑书神侠倚碧鸳。\"他们分别是《飞狐外传》（1960年）、《雪山飞狐》（1959年）、《连城诀》（1963年）、《天龙八部》（1963年）、《射雕英雄传》（1957年）、《白马啸西风》（1961年）、《鹿鼎记》（1969年）、《笑傲江湖》（1967年）、《书剑恩仇录》（1955年）、《神雕侠侣》（1959年）、《侠客行》（1965年）、《倚天屠龙记》（1961年）、《碧血剑》（1956年）《鸳鸯刀》（1961年）、《越女剑》（1970年）。"



FSNewsAboutDetailController::FSNewsAboutDetailController()
{

}

FSNewsAboutDetailController::~FSNewsAboutDetailController()
{
    
}

bool FSNewsAboutDetailController::init()
{
    return true;
    
}

void FSNewsAboutDetailController::viewDidAppear()
{
    
    CANavigationBarItem *navBarItem = CANavigationBarItem::create("关于");
//    this->getTabBarController()->setNavigationBarItem(navBarItem);
    
//    CAWindow* window = CAApplication::getApplication()->getRootWindow();
//    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    this->setNavigationBarItem(navBarItem);
    
}

void FSNewsAboutDetailController::viewDidLoad()
{
    _size = this->getView()->getBounds().size;
    CAScrollView *srv = CAScrollView::createWithFrame(this->getView()->getBounds());
    
    
    
//    CC_PROPERTY_IS(bool, m_bShowsHorizontalScrollIndicator, ShowsHorizontalScrollIndicator);
//    
//    CC_PROPERTY_IS(bool, m_bShowsVerticalScrollIndicator, ShowsVerticalScrollIndicator);
//    
//    CC_PROPERTY_IS(bool, m_bShowsScrollIndicators, ShowsScrollIndicators);
    
    srv->setShowsHorizontalScrollIndicator(false);
    srv->setShowsVerticalScrollIndicator(true);
    
    srv->setTag(99);
    
    

    CALabel* test = CALabel::createWithCenter(CADipRectMake(_size.width/2, 100, _size.width*2/3, 50));
    test->setTextAlignment(CATextAlignmentCenter);
    test->setTag(100);
    test->setFontSize(50);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    srv->addSubview(test);

    this->getView()->addSubview(srv);
    string strTitle(unicode_to_utf8(aboutDetail[0]));
    setAboutText(strTitle);
    
    
    
    CAImageView *imageView = CAImageView::createWithCenter(CADipRectMake(_size.width/2, 300, 200, 200));
    imageView->setImage(CAImage::create("image/appicon.png"));
    srv->addSubview(imageView);
    
    
    CALabel* versionLabel = CALabel::createWithCenter(CADipRectMake(_size.width/2, 460, _size.width*2/4, 40));
    versionLabel->setTextAlignment(CATextAlignmentCenter);
    versionLabel->setTag(100);
    versionLabel->setFontSize(30);
    versionLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
    srv->addSubview(versionLabel);
    
    string strVersion(unicode_to_utf8(aboutDetail[1]));
    versionLabel->setText(strVersion);
    
    
    this->getView()->setColor(ccc4(100,100,100,255));
    srv->setBackGroundColor(ccc4(230,230,230,255));
}


void FSNewsAboutDetailController::setAboutText(string& strText)
{
    CALabel *textLabel = (CALabel*)this->getView()->getSubviewByTag(99)->getSubviewByTag(100);
    if (textLabel) {
        textLabel->setText(strText);
    }
    
}


void FSNewsAboutDetailController::viewDidUnload()
{
    
}
