//
//  FSNewsView.cpp
//  SharpMessage
//
//  Created by apple on 15/5/17.
//
//

#include "FSNewsView.h"
#include "FSNewsViewCell.h"

#define CAColor_blueStyle ccc4(51,204,255,255)

#define SCALEKEY "ScaleKey"

FSNewsView::FSNewsView()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

FSNewsView::~FSNewsView()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

double FSNewsView::loadScale()
{
//    char strNewsID[20];
//    sprintf(strNewsID, "%d", newsID);
    
    return CAUserDefault::sharedUserDefault()->getDoubleForKey(SCALEKEY,1.0);
}



void FSNewsView::viewDidLoad()
{

    
    size = this->getView()->getBounds().size;
    
    p_TableView = CATableView::createWithCenter(CADipRect(size.width*0.5, size.height*0.5, size.width, size.height));
    p_TableView->setTableViewDataSource(this);
    p_TableView->setTableViewDelegate(this);
    p_TableView->setAllowsSelection(true);
    p_TableView->setAllowsMultipleSelection(true);
    p_TableView->setSeparatorColor(CAColor_red);
    p_TableView->setSeparatorViewHeight(0);
    this->getView()->addSubview(p_TableView);
}

void FSNewsView::viewDidUnload()
{
    
}

void FSNewsView::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

void FSNewsView::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    
}

CATableViewCell* FSNewsView::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    FSNewsViewCell *cell = dynamic_cast<FSNewsViewCell*>(table->dequeueReusableCellWithIdentifier("newsView"));
//    MyTableViewCell* cell = dynamic_cast<MyTableViewCell*>(table->dequeueReusableCellWithIdentifier("CrossApp"));
    if (cell == NULL)
    {
        cell = FSNewsViewCell::create("newsView", CADipRect(0, 0, _size.width, _size.height));
        cell->initWithCell();
    }
    
    
//    if (section == 1)
//    {
//        CAButton* cellBtn = (CAButton*)cell->getSubviewByTag(102);
//        cellBtn->setVisible(false);
//    }
//    else
//    {
//        CAButton* cellBtn = (CAButton*)cell->getSubviewByTag(102);
//        cellBtn->setVisible(true);
//    }
//    char order[20] = "";
//    sprintf(order, "Cell-%d", row);
//    CALabel* cellText = (CALabel*)cell->getSubviewByTag(100);
//    cellText->setText(order);
    
    
    
    return cell;
    
}

CAView* FSNewsView::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    std::string head = "";
    head = (section == 0) ? "Selection-0" : "Selection-1";
    CAView* view = CAView::createWithColor(CAColor_gray);
    
    CADipSize _size = viewSize;
    CALabel* header = CALabel::createWithCenter(CADipRect(_size.width*0.5, _size.height*0.5, _size.width*0.8, _size.height));
    header->setText(head);
    header->setFontSize(_px(30));
    header->setColor(CAColor_white);
    header->setTextAlignment(CATextAlignmentCenter);
    header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    view->addSubview(header);
    
    return view;
}

CAView* FSNewsView::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
{
    CAView* view = CAView::createWithColor(CAColor_gray);
    
    
    return view;
}

unsigned int FSNewsView::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return 10;
}

unsigned int FSNewsView::numberOfSections(CATableView *table)
{
    return 2;
}

unsigned int FSNewsView::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return _px(130);
}

unsigned int FSNewsView::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
{
    return _px(50);
}

unsigned int FSNewsView::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
{
    return 1;
}


