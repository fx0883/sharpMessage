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


#define CAColor_blueStyle ccc4(51,204,255,255)

FSNewsCatalog::FSNewsCatalog()
:loadChapter(NULL)
{

}

FSNewsCatalog::FSNewsCatalog(int newsId)
{
    m_NewsId = newsId;
}

FSNewsCatalog::~FSNewsCatalog()
{

}


void FSNewsCatalog::refreshView()
{
    
    CANavigationBarItem *navbaritem = CANavigationBarItem::create(FSDataManager::GetInstance().getNewsManager()->getNewsInfoByNewsId(m_NewsId)->getNewsTitle());
        
    
    this->setNavigationBarItem(navbaritem);
}


void FSNewsCatalog::loadData()
{
    p_AryCatalog = FSDataManager::GetInstance().getNewsManager()->getChapterInfoAry(m_NewsId);
    
}


void FSNewsCatalog::viewDidLoad()
{
    this->refreshView();
    size = this->getView()->getBounds().size;
    
    //p_TableView = CATableView::createWithCenter(CADipRect(size.width*0.5, size.height*0.5, size.width, size.height));
    p_TableView = CATableView::createWithFrame(this->getView()->getBounds());

    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
//    p_TableView->setAllowsMultipleSelection(true);
    p_TableView->setSeparatorColor(CAColor_gray);
    p_TableView->setSeparatorViewHeight(1);
    this->getView()->addSubview(p_TableView);
    
    this->loadData();
    

}

void FSNewsCatalog::viewDidUnload()
{
    
}

void FSNewsCatalog::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
    ChapterInfo *chapterInfo = (ChapterInfo*)p_AryCatalog->objectAtIndex(row);
    
    if (this->loadChapter) {
        this->loadChapter(chapterInfo);
    }
    
    CANavigationController *nav = FSContext::GetInstance().getMainNavController();
//    nav->pushViewController(fsnewscatalog, true);
    nav->popViewControllerAnimated(true);
}

void FSNewsCatalog::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* FSNewsCatalog::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    FSNewsCatalogCell* cell = dynamic_cast<FSNewsCatalogCell*>(table->dequeueReusableCellWithIdentifier("FSNewsCatalogCell"));
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
    
    
//    char order[20] = "";
//    sprintf(order, "Cell-%d", row);
//    CALabel* cellText = (CALabel*)cell->getSubviewByTag(100);
//    cellText->setText(order);
    
    
    
    
    
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
    if (p_AryCatalog) {
        rowCount = p_AryCatalog->count();
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