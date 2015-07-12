//
//  FSNewsCatalog.cpp
//  SharpMessage
//
//  Created by apple on 6/7/15.
//
//

#include "FSNewsCatalog.h"
#include "FSNewsCatalogCell.h"
#include "FSDataManager.h"
#include "FSContext.h"
#include "BookMarkInfo.h"


//#define CAColor_blueStyle ccc4(51,204,255,255)


//静态数据成员的定义和初始化
FSNewsCatalog* FSNewsCatalog::curFSNewsCatalog = NULL;

FSNewsCatalog::FSNewsCatalog()
:loadChapter(NULL),
p_AryMarkInfo(NULL),
p_AryCatalog(NULL)
{
    curFSNewsCatalog = this;
}

FSNewsCatalog::FSNewsCatalog(int newsId)
{
    m_NewsId = newsId;
    curFSNewsCatalog = this;
}

FSNewsCatalog::~FSNewsCatalog()
{

}


void FSNewsCatalog::refreshView(bool isCatalog)
{
    
    CANavigationBarItem *navbaritem = CANavigationBarItem::create(FSDataManager::GetInstance().getNewsManager()->getNewsInfoByNewsId(m_NewsId)->getNewsTitle());
    if (!isCatalog) {
        rightButton = CABarButtonItem::create("",  CAImage::create("image/trash.png"),  CAImage::create("image/trashSelected.png"));
        
        rightButton->setTarget(rightButton, CAControl_selector(FSNewsCatalog::onClickBookMarkClean));
        navbaritem->addRightButtonItem(rightButton);
    }
    
    this->setNavigationBarItem(navbaritem);
    


}


void FSNewsCatalog::loadData()
{
    p_AryCatalog = FSDataManager::GetInstance().getNewsManager()->getChapterInfoAry(m_NewsId);
    
    p_AryMarkInfo =FSDataManager::GetInstance().getNewsManager()->loadBookMarkInfo(m_NewsId);
    
    
}


void FSNewsCatalog::viewDidLoad()
{
    this->refreshView(true);
    size = this->getView()->getBounds().size;
    

    
    vector<string> segmentTitlelist;
    segmentTitlelist.push_back("目录");
    segmentTitlelist.push_back("书签");
    
    segment = CASegmentedControl::createWithCenter(CADipRect(size.width*0.5,
                                                             size.height*0.05,
                                                             size.width*0.8,
                                                             size.height*0.05), (unsigned int)segmentTitlelist.size());
    

    
    for (int i = 0; i < segmentTitlelist.size(); i++)
    {

        segment->setTitleForSegmentAtIndex(segmentTitlelist.at(i), i);
        //		segment->setBackgroundImage(CAImage::create(segNormal));
    }

    segment->setSelectedAtIndex(0);
    segment->addTarget(this, CASegmentedControl_selector(FSNewsCatalog::segmentCallback));
    this->getView()->addSubview(segment);
    
//    CAView *lineView = CAView::createWithFrame(CADipRect(0,size.height*0.08,size.width,1));
//    
//    lineView->setColor(ccc4(0,0,0,255));
//    this->getView()->addSubview(lineView);
    
    p_TableView = CATableView::createWithFrame(CADipRect(0,size.height*0.1,size.width,size.height*0.9));
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    p_TableView->setSeparatorColor(CAColor_gray);
    p_TableView->setSeparatorViewHeight(1);
    this->getView()->addSubview(p_TableView);

    
    
    p_TableViewMarklist = CATableView::createWithFrame(CADipRect(0,size.height*0.1,size.width,size.height*0.9));
    p_TableViewMarklist->setTableViewDataSource(this);
    p_TableViewMarklist->setTableViewDelegate(this);
    p_TableViewMarklist->setAllowsSelection(true);
    p_TableViewMarklist->setSeparatorColor(CAColor_gray);
    p_TableViewMarklist->setSeparatorViewHeight(1);
    this->getView()->addSubview(p_TableViewMarklist);
    p_TableViewMarklist->setVisible(false);
    
    this->loadData();
    

}

void FSNewsCatalog::segmentCallback(CASegmentedControl* btn, int index)
{
    switch (index)
    {
        case 0:
        {
            showMarklist(false);
            break;
        }
        case 1:
        {
            showMarklist(true);
            break;
        }

        default:
            break;
    }
}



void FSNewsCatalog::showMarklist(bool isShow)
{
    p_TableViewMarklist->setVisible(isShow);
    p_TableView->setVisible(!isShow);
    
//    if (rightButton) {
////        rightButton->setVisible(!isShow);
//    }
    this->refreshView(!isShow);
}




void FSNewsCatalog::onClickBookMarkClean(CAControl* btn, CCPoint point)
{
    
    CAAlertView* alertView = CAAlertView::createWithText("提示", "删除所有标签!", "确定","取消",NULL);
    alertView->show();
    alertView->setTarget(this, CAAlertView_selector(FSNewsCatalog::alertClickBookMarkCleanCallBack));
    
    

    
}

void FSNewsCatalog::alertClickBookMarkCleanCallBack(int btnIndex)
{
    if (btnIndex==0) {
        //清除所有标签
        ChapterInfo *chapterInfo = FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
        
        bool isOK=FSDataManager::GetInstance().getNewsManager()->removeBookMarkForNewsId(chapterInfo->getNewsID());
        if (isOK) {
            
            curFSNewsCatalog->loadData();
            
            
            curFSNewsCatalog->p_TableViewMarklist->reloadData();
            
        }
    }

}



void FSNewsCatalog::viewDidUnload()
{
    
}

void FSNewsCatalog::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    if (table==p_TableView) {
        ChapterInfo *chapterInfo = (ChapterInfo*)p_AryCatalog->objectAtIndex(row);
        
        if (this->loadChapter) {
            this->loadChapter(chapterInfo);
        }
        
        CANavigationController *nav = FSContext::GetInstance().getMainNavController();
        nav->popViewControllerAnimated(true);
    }
    else if(table==p_TableViewMarklist)
    {
        
        BookMarkInfo *bookmarkinfo = (BookMarkInfo*)p_AryMarkInfo->objectAtIndex(row);
        const int chapterId = bookmarkinfo->getChapterID();
        ChapterInfo *chapterInfo = NULL;
        for (int i=0; i<p_AryCatalog->count(); i++) {
            
            chapterInfo = (ChapterInfo*)p_AryCatalog->objectAtIndex(i);
            
            if (chapterId == chapterInfo->getChapterID()) {
                break;
            }
        }
        
        double dProgress = atof(bookmarkinfo->getMarkProgress().c_str());
        
        if (this->loadChapter && this->gotoChapterProgress) {
            this->loadChapter(chapterInfo);
            this->gotoChapterProgress(dProgress);
            CANavigationController *nav = FSContext::GetInstance().getMainNavController();
            nav->popViewControllerAnimated(true);
        }
//
//        CANavigationController *nav = FSContext::GetInstance().getMainNavController();
//        nav->popViewControllerAnimated(true);
    }
    

}

void FSNewsCatalog::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* FSNewsCatalog::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    FSNewsCatalogCell* cell = NULL;
    
    if (table==p_TableView)
    {
    cell = dynamic_cast<FSNewsCatalogCell*>(table->dequeueReusableCellWithIdentifier("FSNewsCatalogCell"));
    if (cell == NULL)
    {
        cell = FSNewsCatalogCell::create("FSNewsCatalogCell", CADipRect(0, 0, _size.width, _size.height));
        cell->initWithCell();
    }
    
    ChapterInfo *chapterInfo = (ChapterInfo*)p_AryCatalog->objectAtIndex(row);
    
    
    ChapterInfo *curChapterInfo =  FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
    
        bool bIsSelected = chapterInfo->getChapterID() == curChapterInfo->getChapterID();
    
        cell->setSelectedCell(bIsSelected);
        cell->updateCell(chapterInfo->getChapterTitle());
    }
    else
    {
        
        cell = dynamic_cast<FSNewsCatalogCell*>(table->dequeueReusableCellWithIdentifier("FSNewsCatalogCell"));
        if (cell == NULL)
        {
            cell = FSNewsCatalogCell::create("FSNewsCatalogCell", CADipRect(0, 0, _size.width, _size.height));
            cell->initWithCell();
        }
        
        BookMarkInfo *bookmarkinfo = (BookMarkInfo*)p_AryMarkInfo->objectAtIndex(row);
        
        
        
//        ChapterInfo *curChapterInfo =  FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
        
//        bool bIsSelected = chapterInfo->getChapterID() == curChapterInfo->getChapterID();
//        
//        cell->setSelectedCell(bIsSelected);
        cell->updateCell(bookmarkinfo->getMarkDigest());
    }
    return cell;
    
}

//CAView* FSNewsCatalog::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
//{
//    std::string head = "";
//    head = (section == 0) ? "Selection-0" : "Selection-1";
//    CAView* view = CAView::createWithColor(CAColor_gray);
//    
//    CADipSize _size = viewSize;
//    CALabel* header = CALabel::createWithCenter(CADipRect(_size.width*0.5, _size.height*0.5, _size.width*0.8, _size.height));
//    header->setText(head);
//    header->setFontSize(_px(30));
//    header->setColor(CAColor_white);
//    header->setTextAlignment(CATextAlignmentCenter);
//    header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
//    view->addSubview(header);
//    
//    return view;
//}

//CAView* FSNewsCatalog::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
//{
//    CAView* view = CAView::createWithColor(CAColor_gray);
//    
//    
//    return view;
//}

unsigned int FSNewsCatalog::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int rowCount = 0;
    if (table == p_TableView) {
        if (p_AryCatalog) {
            rowCount = p_AryCatalog->count();
        }
    }
    else
    {
        if (p_AryMarkInfo) {
            rowCount = p_AryMarkInfo->count();
        }
    }

    return rowCount;
}

unsigned int FSNewsCatalog::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int FSNewsCatalog::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(80);
}

//unsigned int FSNewsCatalog::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
//{
//    return _px(50);
//}
//
//unsigned int FSNewsCatalog::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
//{
//    return 1;
//}