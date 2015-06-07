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
    if(!m_NavBarItem)
    {
        m_NavBarItem = CANavigationBarItem::create("金庸小说");
        this->getTabBarController()->setNavigationBarItem(m_NavBarItem);
        
        
        
    }

//    this->getTabBarController()->getNavigationBarItem()->setTitle("小说");
//    
//    CAWindow* window = CAApplication::getApplication()->getRootWindow();
//    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
////    nav->setNavigationBarHidden(true, false);
//    nav->updateItem(this->getTabBarController());
    
}


//CANavigationBarItem* item = CANavigationBarItem::create("ViewController2");
//this->getTabBarController()->setNavigationBarItem(item);

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
    FSNewsView2 *fsnewsview2 = new FSNewsView2();
    fsnewsview2->init();
    FSDataManager::GetInstance().getNewsManager()->loadChapterDic(newsinfo->getNewsID());
    FSDataManager::GetInstance().getNewsManager()->loadCurChapterInfo(newsinfo->getNewsID());
    ChapterInfo *chapterInfo =  FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
    
    fsnewsview2->setChapterInfo(chapterInfo);
    
    
    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->pushViewController(fsnewsview2, true);
    
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



