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
#include "FSBooklibraryCell.h"
#include "FSNewsView2.h"

using namespace std;


#include "C2DXShareSDK.h"


USING_NS_CC;
using namespace cn::sharesdk;

#define SHARESDKREDIRECT_URI "http://www.511book.cn"
FSBooklibrary::FSBooklibrary()
{
//    BaseViewController::BaseViewController();
}

FSBooklibrary::~FSBooklibrary()
{
//    BaseViewController::~BaseViewController();
}

void FSBooklibrary::viewDidLoad()
{
    size = this->getView()->getBounds().size;
    p_Conllection = CACollectionView::createWithFrame(this->getView()->getBounds());
    p_Conllection->setAllowsSelection(true);
    //p_Conllection->setAllowsMultipleSelection(true);
    p_Conllection->setCollectionViewDelegate(this);
    p_Conllection->setCollectionViewDataSource(this);
    p_Conllection->setScrollViewDelegate(this);
    

    p_Conllection->setHoriInterval(_px(40));
    p_Conllection->setVertInterval(_px(40));
    this->getView()->addSubview(p_Conllection);
    

    
}

void FSBooklibrary::viewDidAppear()
{
//    if(!m_NavBarItem)
    {
        CANavigationBarItem *navItem = CANavigationBarItem::create("金庸小说");
        
        rightButton = CABarButtonItem::create("",  CAImage::create("tabbar_function/userCenter_1.png"),  CAImage::create("tabbar_function/userCenter_1.png"));
        
        rightButton->setTarget(rightButton, CAControl_selector(FSBooklibrary::onClickShareSdk));
        navItem->addRightButtonItem(rightButton);
        
        this->getTabBarController()->setNavigationBarItem(navItem);
        

        
    }
}


void FSBooklibrary::onClickShareSdk(CAControl* btn, CCPoint point)
{
    shareMenuItemClick();
}

void FSBooklibrary::viewDidUnload()
{
    
}

void FSBooklibrary::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
{
//    CCLog("row %d",row);
//    CCLog("item %d",item);
    
    int index =row * 3 + item;
    CCArray& ary = FSDataManager::GetInstance().getNewsManager()->getArynewsList();
    NewsInfo *newsinfo = (NewsInfo*)ary.objectAtIndex(index);
    newsinfo->setReadTimes(newsinfo->getReadTimes()+1);
    FSNewsView2 *fsnewsview2 = new FSNewsView2();
    fsnewsview2->init();
    FSDataManager::GetInstance().getNewsManager()->loadChapterDic(newsinfo->getNewsID());
    FSDataManager::GetInstance().getNewsManager()->loadCurChapterInfo(newsinfo->getNewsID());
    ChapterInfo *chapterInfo =  FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
    
    fsnewsview2->setChapterInfo(chapterInfo);
    
    
    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->pushViewController(fsnewsview2, true);


    float fprogress = FSDataManager::GetInstance().getNewsManager()->getPageProgress(chapterInfo->getChapterID());
    fsnewsview2->gotoChapterProgress(fprogress);
    
//    this->presentModalViewController(fsnewsview2, true);
    
}

void FSBooklibrary::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
{
    
}

CACollectionViewCell* FSBooklibrary::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item)
{
//    if (row * 3 + item >= colorArr.size())
//    {
//        return NULL;
//    }
//
    const char* strCellIndentifier = "BooksCell";
    CADipSize _size = cellSize;
    FSBooklibraryCell* p_Cell = (FSBooklibraryCell*)collectionView->dequeueReusableCellWithIdentifier(strCellIndentifier);
    
   //CACollectionViewCell * p_Cell = collectionView->dequeueReusableCellWithIdentifier(strCellIndentifier);
    if(p_Cell == NULL)
    {
        p_Cell = (FSBooklibraryCell*)FSBooklibraryCell::create(strCellIndentifier);
        p_Cell->initWithSize(_size);
        
//                CAView* itemImage = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
//                itemImage->setTag(99);
//                p_Cell->addSubview(itemImage);
//        
//                CADipSize itemSize = itemImage->getBounds().size;
//                CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width*0.5, itemSize.height*0.5, 150, 40));
//                itemText->setTag(100);
//                itemText->setFontSize(_px(29));
//                itemText->setTextAlignment(CATextAlignmentCenter);
//                itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//                itemImage->addSubview(itemText);

        
    }
//    if (p_Cell == NULL)
//    {
//        p_Cell = CACollectionViewCell::create("CrossApp");
//        
//        CAView* itemImage = CAView::createWithFrame(CADipRect(0, 0, _size.width, _size.height));
//        itemImage->setTag(99);
//        p_Cell->addSubview(itemImage);
//        
//        CADipSize itemSize = itemImage->getBounds().size;
//        CALabel* itemText = CALabel::createWithCenter(CADipRect(itemSize.width*0.5, itemSize.height*0.5, 150, 40));
//        itemText->setTag(100);
//        itemText->setFontSize(_px(29));
//        itemText->setTextAlignment(CATextAlignmentCenter);
//        itemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//        itemImage->addSubview(itemText);
//    }
//    CAView* itemImageView = p_Cell->getSubviewByTag(99);
//    itemImageView->setColor(colorArr.at(row * 3 + item));
//    CCLog("%d", row * 3 + item);
//    
//    char pos[20] = "";
//    sprintf(pos, "(%d,%d,%d)", section, row, item);

    
//    return p_Cell;
    
    
 //   NewsInfo *newsinfo
    
    int index =row * 3 + item;
    CCArray& ary = FSDataManager::GetInstance().getNewsManager()->getArynewsList();
    NewsInfo *newsinfo = (NewsInfo*)ary.objectAtIndex(index);
    p_Cell->setNewsInfo(newsinfo);
//p_Cell->setNewsInfo(NULL);
    
    return p_Cell;
}

unsigned int FSBooklibrary::numberOfSections(CACollectionView *collectionView)
{
    return 1;
}

unsigned int FSBooklibrary::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section)
{
    
    int countBook = FSDataManager::GetInstance().getNewsManager()->getArynewsList().count();
    
    int rowsCount = countBook/3+(countBook%3==0?0:1);
    
    CCLOG("rowsCount = %d",rowsCount);
    
    return rowsCount;
}

unsigned int FSBooklibrary::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row)
{
    return 3;
}

unsigned int FSBooklibrary::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row)
{
    return ((this->getView()->getBounds().size.width - _px(40) * 4) / 3)*4/3 *5/4;
  //  return 60;
}




//------------------shareSDK--------------

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("授权成功");
            break;
        case C2DXResponseStateFail:
            CCLog("授权失败");
            break;
        default:
            break;
    }
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
    if (state == C2DXResponseStateSuccess)
    {
        //输出用户信息
        try
        {
            CCArray *allKeys = userInfo -> allKeys();
            allKeys->retain();
            for (int i = 0; i < allKeys -> count(); i++)
            {
                CCString *key = (CCString *)allKeys -> objectAtIndex(i);
                CAObject *obj = userInfo -> objectForKey(key -> getCString());
                
                CCLog("key = %s", key -> getCString());
                if (dynamic_cast<CCString *>(obj))
                {
                    CCLog("value = %s", dynamic_cast<CCString *>(obj) -> getCString());
                }
                else if (dynamic_cast<CCInteger *>(obj))
                {
                    CCLog("value = %d", dynamic_cast<CCInteger *>(obj) -> getValue());
                }
                else if (dynamic_cast<CCDouble *>(obj))
                {
                    CCLog("value = %f", dynamic_cast<CCDouble *>(obj) -> getValue());
                }
            }
            allKeys->release();
        }
        catch(...)
        {
            CCLog("==============error");
        }
        
    }
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            break;
        default:
            break;
    }
}






void FSBooklibrary::menuCloseCallback(CAObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
//    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void FSBooklibrary::authMenuItemClick(CAObject* pSender)
{
    //    C2DXShareSDK::authorize(C2DXPlatTypeFacebook, authResultHandler);
}

void FSBooklibrary::cancelAuthMenuItemClick(CAObject* pSender)
{
    //    C2DXShareSDK::cancelAuthorize(C2DXPlatTypeSinaWeibo);
}

void FSBooklibrary::hasAuthMenuItemClick(CAObject* pSender)
{
    if (C2DXShareSDK::hasAutorized(C2DXPlatTypeSinaWeibo))
    {
        CCLog("用户已授权");
    }
    else
    {
        CCLog("用户尚未授权");
    }
}

void FSBooklibrary::getUserInfoMenuItemClick(CAObject* pSender)
{
    C2DXShareSDK::getUserInfo(C2DXPlatTypeSinaWeibo, getUserResultHandler);
}


std::string FSBooklibrary::getShareImagePath()
{
    
    
    std::vector<std::string> listImagePath;
    listImagePath.push_back("http://a.hiphotos.baidu.com/image/h%3D360/sign=984de4228418367ab28979db1e738b68/0b46f21fbe096b63de38775b0e338744ebf8ac93.jpg");
    listImagePath.push_back("http://d.hiphotos.baidu.com/image/h%3D360/sign=6dc6980d8494a4c21523e12d3ef41bac/a8773912b31bb0514357ca2a357adab44aede045.jpg");
    listImagePath.push_back("http://e.hiphotos.baidu.com/image/h%3D360/sign=7d7b0123223fb80e13d167d106d02ffb/4034970a304e251fe958e9eaa486c9177f3e5370.jpg");
    
    listImagePath.push_back("http://g.hiphotos.baidu.com/image/h%3D200/sign=cb073b61f1deb48fe469a6dec01e3aef/c9fcc3cec3fdfc03a4b842b8d63f8794a5c226e9.jpg");
    listImagePath.push_back("http://image.s1979.com/allimg/131228/25-13122Q54631.jpg");
    
    listImagePath.push_back("http://a.hiphotos.baidu.com/image/pic/item/9d82d158ccbf6c814884f9b9be3eb13533fa4034.jpg");
    
    listImagePath.push_back("http://e.hiphotos.baidu.com/image/pic/item/b999a9014c086e06e1652a6f01087bf40bd1cbc1.jpg");
    listImagePath.push_back("http://a.hiphotos.baidu.com/image/pic/item/1b4c510fd9f9d72a80f8481ad62a2834349bbb1d.jpg");
    //        listImagePath.push_back("http://img0.imgtn.bdimg.com/it/u=3959729808,1330752766&fm=23&gp=0.jpg");
    //        listImagePath.push_back("http://img2.imgtn.bdimg.com/it/u=1488062681,3317039875&fm=21&gp=0.jpg");
    
    int count = (int)listImagePath.size();
    srand((int)time(0));
    
    int j=rand()%count;
    if (j>=count) {
        j--;
    }
    
    
    
    
    std::string imagePath = listImagePath.at(j);
    return imagePath;
}

void FSBooklibrary::shareMenuItemClick(CAObject* pSender)
{
    CCDictionary *content = CCDictionary::create();
    content -> setObject(CCString::create("飞雪连天射白鹿，笑书神侠倚碧鸳。"), "content");
    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
    content -> setObject(CCString::create("测试标题"), "title");
    content -> setObject(CCString::create("测试描述"), "description");
    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(CCString::create("ShareSDK"), "site");
    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
    //    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}

void FSBooklibrary::shareMenuItemClick()
{
    CCDictionary *content = CCDictionary::create();
    
    //    std::string searchPath=    CCFileUtils::getInstance()->getSearchPaths()[0];
    std::string imagePath = this->getShareImagePath();
    
    content -> setObject(CCString::create("飞雪连天射白鹿，笑书神侠倚碧鸳。"), "content");
    content -> setObject(CCString::create(imagePath), "image");
    content -> setObject(CCString::create("金庸全集Free"), "title");
    content -> setObject(CCString::create("飞雪连天射白鹿，笑书神侠倚碧鸳。"), "description");
    content -> setObject(CCString::create(SHARESDKREDIRECT_URI), "url");
    //    content -> setObject(CCString::create(FSLocalizedNSStringByKey("ShareTitle")), "site");
    
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create(SHARESDKREDIRECT_URI), "siteUrl");
    //    content -> setObject(CCString::create("ShareSDK"), "site");
    //    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
    //    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}

void FSBooklibrary::checkClientItemClick(CAObject* pSender)
{
    if (C2DXShareSDK::isClientInstalled(C2DXPlatTypeQQ))
    {
        CCLOG("客户端已安装");
    }else
    {
        CCLOG("客户端未安装");
    }
}



