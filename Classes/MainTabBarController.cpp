//
//  MainTabController.cpp
//  SharpMessage
//
//  Created by 冯璇 on 15/4/19.
//
//

#include "MainTabBarController.h"
#include "FSBooklibrary/FSBooklibrary.h"
#include "FSBookRankingList.h"
#include "FSBookReadTimes/FSBookReadTimes.h"
#include "FSUserCenter.h"
#include "CrossApp.h"
#include "FSContext.h"
#include "FSNewsAbout/FSNewsAboutController.h"

MainTabBarController::MainTabBarController()
{
    
}

MainTabBarController::~MainTabBarController()
{
    
}

CAWindow* MainTabBarController::createWindow()
{
    
    
    
    FSBooklibrary* fsbooklibrary = new FSBooklibrary();

    
//    CANavigationController *navBooklibrary = CANavigationController.initWithRootViewController
    
//    CANavigationController* navBooklibrary = new CANavigationController();
//    navBooklibrary->initWithRootViewController(fsbooklibrary);
//    navBooklibrary->getView()->setColor(CAColor_clear);
    fsbooklibrary->init();
    fsbooklibrary->setTabBarItem(CATabBarItem::create("library",
                                                       CAImage::create("tabbar_function/booklibrary_1.png"),
                                                       CAImage::create("tabbar_function/booklibrary_2.png")));
    
//    FSBookRankingList* fsbookrankinglist = new FSBookRankingList();
//    fsbookrankinglist->init();
//    fsbookrankinglist->setTabBarItem(CATabBarItem::create("Ranking",
//                                                        CAImage::create("tabbar_function/bookRankingList_1.png"),
//                                                        CAImage::create("tabbar_function/bookRankingList_2.png")));
    
    
    FSBookReadTimes* fsbookreadtimes = new FSBookReadTimes();
    fsbookreadtimes->init();
    fsbookreadtimes->setTabBarItem(CATabBarItem::create("ReadTimes",
                                                          CAImage::create("tabbar_function/bookRankingList_1.png"),
                                                          CAImage::create("tabbar_function/bookRankingList_2.png")));
    
    
    
//    FSUserCenter* fsusercenter = new FSUserCenter();
//    fsusercenter->init();
//    fsusercenter->setTabBarItem(CATabBarItem::create("User",
//                                                        CAImage::create("tabbar_function/userCenter_1.png"),
//                                                        CAImage::create("tabbar_function/userCenter_2.png")));
    
    FSNewsAboutController* fsnewsaboutcontroller = new FSNewsAboutController();
    fsnewsaboutcontroller->init();
    fsnewsaboutcontroller->setTabBarItem(CATabBarItem::create("User",
                                                            CAImage::create("tabbar_function/userCenter_1.png"),
                                                            CAImage::create("tabbar_function/userCenter_2.png")));
    
    
    
    std::vector<CAViewController*> controllerItem;
    controllerItem.push_back(fsbooklibrary);
    controllerItem.push_back(fsbookreadtimes);
    controllerItem.push_back(fsnewsaboutcontroller);
    
    CATabBarController* p_Funtion = new MainTabBarController();
    p_Funtion->initWithViewControllers(controllerItem);
    //p_Funtion->showTabBarSelectedIndicator();
    p_Funtion->setTabBarBackGroundColor(ccc4(100,100,100,255));
    p_Funtion->setTabBarSelectedBackGroundColor(ccc4(100,100,100,255));
    
    CANavigationController* navigationController = new CANavigationController();
    navigationController->initWithRootViewController(p_Funtion);
    navigationController->getView()->setColor(CAColor_clear);
    navigationController->setNavigationBarBackGroundColor(ccc4(100,100,100,255));
    
    
    
//    CC_PROPERTY_PASS_BY_REF(CAColor4B, m_sNavigationBarBackGroundColor, NavigationBarBackGroundColor);
//    
//    CC_PROPERTY_PASS_BY_REF(CAColor4B, m_sNavigationBarTitleColor, NavigationBarTitleColor);
//    
//    CC_PROPERTY_PASS_BY_REF(CAColor4B, m_sNavigationBarButtonColor, NavigationBarButtonColor);
    
    CAWindow* p_Window = CAWindow::create();
//    float winWidth = p_Window->getBounds().size.width;
//    CADrawerController* drawerController = new CADrawerController();
//    drawerController->initWithController(viewController1, navigationController, winWidth*0.5);
//    drawerController->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("background/1.jpg")));
//    drawerController->autorelease();
    
    p_Window->setRootViewController(navigationController);
    
    
    
    FSContext::GetInstance().setMainNavController(navigationController);
    FSContext::GetInstance().setMainTabBarController(p_Funtion);
    
    fsbooklibrary->release();
    fsbookreadtimes->release();
    fsnewsaboutcontroller->release();

    
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