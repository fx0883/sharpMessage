 #include "AppDelegate.h"
#include "RootWindow.h"
#include "MainTabBarController.h"
#include "FSUtilCPlus.h"
#include "CrossApp.h"
#include "FSloadRes.h"
#include "model/FSDataManager.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CAApplication* pDirector = CAApplication::getApplication();
    
//    loadData();
    //initialize db
    FSloadResBase *loadres = FSloadRes::create();
    loadres->loadNewsList();
    loadres->loadReadSetting();
    DELETECLASS(loadres)
    
    //load newslist
    FSDataManager::GetInstance();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    // run
//    pDirector->runWindow(RootWindow::create());

    pDirector->runWindow(MainTabBarController::createWindow());
   //
    
    CCLog("runWindow");
    return true;
}

//void AppDelegate::loadData()
//{
//    
//    bool isFirst = CAUserDefault::sharedUserDefault()->getBoolForKey("bIsFirst", true);
//    if (!isFirst) {
//
//        std::vector<std::string> searchPath;
//        
//        LanguageType langtype = CCApplication::sharedApplication()->getCurrentLanguage();
//      
//        std::string strResourceFolder="cn";
//        switch (langtype) {
//            case kLanguageChinese:
//                strResourceFolder="cn";
//                break;
//            case kLanguageEnglish:
//                strResourceFolder="en";
//                break;
//            
//                
//        }
//    
//        CCLog("strResourceFolder = %s",strResourceFolder.c_str());
//        
//        searchPath.push_back(strResourceFolder);
//        
//        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
//
//        std::string newsPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("local.plist");
//        
//        CCDictionary *plistDic=CCDictionary::createWithContentsOfFileThreadSafe(newsPath.c_str());
//        CCLog("newsPath = %s",newsPath.c_str());
//        
//        const CCString *title = plistDic->valueForKey("ShareContent");
//        CAUserDefault::sharedUserDefault()->setStringForKey("title", title->getCString());
//        
//
//        
////        CAUserDefault::sharedUserDefault()->setBoolForKey("bIsFirst", false);
//        
//
//        
//    }
//}





// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CAApplication::getApplication()->stopAnimation();

    FSDataManager::GetInstance().getNewsManager()->updateNewsReadTimes();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CAApplication::getApplication()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
