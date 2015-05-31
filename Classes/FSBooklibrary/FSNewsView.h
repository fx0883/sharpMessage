//
//  FSNewsView.h
//  SharpMessage
//
//  Created by apple on 15/5/17.
//
//

#ifndef __SharpMessage__FSNewsView__
#define __SharpMessage__FSNewsView__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "ChapterInfo.h"
#include "AppMacros.h"
#include <vector>



class FSNewsView :public CAViewController,public CATableViewDelegate ,public CATableViewDataSource
{
public:
    FSNewsView();
    virtual ~FSNewsView();
    
protected:
    void viewDidLoad();
    void viewDidUnload();
    
public:
    CC_SYNTHESIZE_PASS_BY_REF2(ChapterInfo*, m_chapterInfo, ChapterInfo)
    CC_SYNTHESIZE_PASS_BY_REF(int,m_lineNumber,LinNumber)
protected:
    void loadData();
public:
//    virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
//    virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
    
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
//    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
//    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section);
    virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
    virtual unsigned int numberOfSections(CATableView *table);
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
//    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section);
//    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section);

public:
    double loadScale();
//    void setScale(double dScale);
    void changeScale(bool bZoomIn);
    
private:
    CADipSize size;
    CATableView* p_TableView;
//    CCArray m_aryContent;
    
    vector<std::string> m_aryContent;
    
};










#endif /* defined(__SharpMessage__FSNewsView__) */
