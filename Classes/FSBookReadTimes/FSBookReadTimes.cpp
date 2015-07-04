 //
//  FSBookReadTimes.cpp
//  SharpMessage
//
//  Created by apple on 7/3/15.
//
//

#include "FSBookReadTimes.h"



#include "FSBookReadTimesCell.h"
#include "FSNewsManager.h"
#include "FSDataManager.h"
#include "AppMacros.h"
#include "FSNewsView2.h"
#define CAColor_blueStyle ccc4(51,204,255,255)

FSBookReadTimes::FSBookReadTimes()
{

}

FSBookReadTimes::~FSBookReadTimes()
{
    
}
void FSBookReadTimes::viewDidAppear()
{

     CANavigationBarItem *navBarItem = CANavigationBarItem::create("我的最爱");
     this->getTabBarController()->setNavigationBarItem(navBarItem);
//     navBarItem->release();
    FSDataManager::GetInstance().getNewsManager()->loadNewsListOrderbyReadTimes2();
    p_TableView->reloadData();
}

void FSBookReadTimes::viewDidLoad()
{
    size = this->getView()->getBounds().size;
    
    p_TableView = CATableView::createWithCenter(CADipRect(size.width*0.5, size.height*0.5, size.width, size.height));
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    p_TableView->setAllowsMultipleSelection(true);
    p_TableView->setSeparatorColor(CAColor_gray);
    p_TableView->setSeparatorViewHeight(1);
    this->getView()->addSubview(p_TableView);
}

void FSBookReadTimes::viewDidUnload()
{
    
}

void FSBookReadTimes::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    int index =row;
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
}

void FSBookReadTimes::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* FSBookReadTimes::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    FSBookReadTimesCell* cell = dynamic_cast<FSBookReadTimesCell*>(table->dequeueReusableCellWithIdentifier("FSBookReadTimesCell"));
    if (cell == NULL)
    {
        cell = FSBookReadTimesCell::create("FSBookReadTimesCell", CADipRect(0, 0, _size.width, _size.height));
        cell->initWithCell();
    }
    
    CCArray& ary = FSDataManager::GetInstance().getNewsManager()->getAryNewsListOrderbyReadTimes();
    
    NewsInfo *itemNewsInfo = (NewsInfo*)ary.objectAtIndex(row);
    cell->updateNewsInfoForCell(itemNewsInfo);
    
    return cell;
    
}




unsigned int FSBookReadTimes::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int count =0;
    CCArray& ary = FSDataManager::GetInstance().getNewsManager()->getAryNewsListOrderbyReadTimes();
    count = ary.count();
    return count;
}

unsigned int FSBookReadTimes::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int FSBookReadTimes::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(230);
}



