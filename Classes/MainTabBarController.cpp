//
//  MainTabController.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/19.
//
//

#include "MainTabBarController.h"
#include "FSBooklibrary.h"
#include "FSBookRankingList.h"
#include "FSUserCenter.h"
#include "CrossApp.h"

MainTabBarController::MainTabBarController()
{
    
}

MainTabBarController::~MainTabBarController()
{
    
}

CAWindow* MainTabBarController::createWindow()
{
    
//    std::string newsPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("news/local.plist");
//    
//    CrossApp::CCDictionary *plistdoc = CrossApp::CCDictionary::createWithContentsOfFileThreadSafe("news/local.plist");
//    
//CCArray* cal =    plistdoc->allKeys();
//    
//    for (unsigned int i = 0; i <cal->count(); ++i)
//    {
//        CCString* pObj=(CCString*)cal->objectAtIndex(i);
//        CCLog("item is = %s",pObj->getCString());
//        int j=i+i;
//    }
    
//    CCDictionary *plistdoc = CCDictionary::create();
    
//    plistdoc->setObject(new CCString("123"), "123");
//    CCLog("newsPath = %s",newsPath.c_str());
//    
//    const char *title = plistdoc->valueForKey("Music")->getCString();
//    CCLog("title = %s",title);
//    std::string strTitle(title);
//    CAUserDefault::sharedUserDefault()->setStringForKey("title", strTitle);
    
    
    FSBooklibrary* fsbooklibrary = new FSBooklibrary();
    fsbooklibrary->init();
    fsbooklibrary->setTabBarItem(CATabBarItem::create("library",
                                                        CAImage::create("tabbar_function/booklibrary_1.png"),
                                                        CAImage::create("tabbar_function/booklibrary_2.png")));
    
    
    FSBookRankingList* fsbookrankinglist = new FSBookRankingList();
    fsbookrankinglist->init();
    fsbookrankinglist->setTabBarItem(CATabBarItem::create("Ranking",
                                                        CAImage::create("tabbar_function/bookRankingList_1.png"),
                                                        CAImage::create("tabbar_function/bookRankingList_2.png")));
    
    
    FSUserCenter* fsusercenter = new FSUserCenter();
    fsusercenter->init();
    fsusercenter->setTabBarItem(CATabBarItem::create("User",
                                                        CAImage::create("tabbar_function/userCenter_1.png"),
                                                        CAImage::create("tabbar_function/userCenter_2.png")));
    
    
    std::vector<CAViewController*> controllerItem;
    controllerItem.push_back(fsbooklibrary);
    controllerItem.push_back(fsbookrankinglist);
    controllerItem.push_back(fsusercenter);
    
    MainTabBarController* p_Funtion = new MainTabBarController();
    p_Funtion->initWithViewControllers(controllerItem);
    p_Funtion->showTabBarSelectedIndicator();
    
//    CANavigationController* navigationController = new CANavigationController();
//    navigationController->initWithRootViewController(p_Funtion);
//    navigationController->getView()->setColor(CAColor_clear);
    
    CAWindow* p_Window = CAWindow::create();
//    float winWidth = p_Window->getBounds().size.width;
//    CADrawerController* drawerController = new CADrawerController();
//    drawerController->initWithController(viewController1, navigationController, winWidth*0.5);
//    drawerController->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("background/1.jpg")));
//    drawerController->autorelease();
    
    p_Window->setRootViewController(p_Funtion);
    fsbooklibrary->release();
    fsbookrankinglist->release();
    fsusercenter->release();

    
    p_Funtion->release();
    
    return p_Window;
}

void MainTabBarController::viewDidLoad()
{
    CATabBarController::viewDidLoad();
}

void MainTabBarController::viewDidUnload()
{
    CATabBarController::viewDidUnload();
}