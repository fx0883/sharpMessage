//
//  FSNewsAboutDetailController.cpp
//  SharpMessage
//
//  Created by apple on 7/6/15.
//
//

#include "FSNewsAboutDetailController.h"

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
    
    

    CALabel* test = CALabel::createWithFrame(CADipRectMake(0+20, 0+40, _size.width-20-20, (_size.height-40)*3/4));
    test->setTextAlignment(CATextAlignmentLeft);
    test->setTag(100);
    test->setFontSize(38);
    test->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
//    test->setColor(ccc4(151,212,255,255));
    srv->addSubview(test);
//    this->viewd->addSubview(test);

    this->getView()->addSubview(srv);
    string strText = string(NEWSINTRO);
    setAboutText(strText);
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
