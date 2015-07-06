//
//  CDNewsAboutController.h
//  Test
//
//  Created by renhongguang on 15/4/17.
//
//

#ifndef __Test__FSNewsAboutController__
#define __Test__FSNewsAboutController__

#include "RootWindow.h"
#include "CrossApp.h"
#include "CrossAppExt.h"

class FSNewsAboutTableCell : public CATableViewCell
{
public:
    FSNewsAboutTableCell();
    virtual ~FSNewsAboutTableCell();
    static FSNewsAboutTableCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
public:
    void initWithCell();
};

class FSNewsAboutController : public CAViewController,CATableViewDelegate,CATableViewDataSource
{
public:
    FSNewsAboutController();
    virtual ~FSNewsAboutController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    
    CREATE_FUNC(FSNewsAboutController);
    
    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);
    
    

public:
    CADipSize winSize;
    CATableView* p_TableView;
};

#endif /* defined(__Test__CDNewsAboutController__) */
