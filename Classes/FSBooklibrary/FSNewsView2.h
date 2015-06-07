//
//  FSNewsView2.h
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#ifndef __SharpMessage__FSNewsView2__
#define __SharpMessage__FSNewsView2__

#include <stdio.h>
#include "CrossApp.h"
#include "ListViewEx.h"
#include "CrossAppExt.h"
#include "AppMacros.h"
#include "ChapterInfo.h"

#include "FSNewsView2Cell.h"
#include "FSNewsBottomView.h"
#include "BaseViewController.h"

struct PagingRule
{
    int lineNumber;
    int lineTextNumber;
};

class FSNewsView2 :public BaseViewController,CAListViewDelegate,CAListViewDataSource
{
public:
    FSNewsView2();
    virtual ~FSNewsView2();
public:
    CC_SYNTHESIZE_PASS_BY_REF2(ChapterInfo*, m_chapterInfo, ChapterInfo)
    CC_SYNTHESIZE_PASS_BY_REF(int,m_lineNumber,LinNumber)
    
public:
    virtual void listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index);
    virtual void listViewDidDeselectCellAtIndex(CAListView *listView, unsigned int index);
    virtual unsigned int numberOfIndex(CAListView *listView);
    virtual unsigned int listViewHeightForIndex(CAListView *listView, unsigned int index);
    virtual CAListViewCell* listViewCellAtIndex(CAListView *listView, const CCSize& cellSize, unsigned int index);
    
protected:
    void viewDidLoad();
    void viewDidUnload();
    void viewDidAppear();
    void loadData();
    void reshapeViewRectDidFinish();
    void addBottomView();
    void calcPagingRule();
    void refreshView();
protected:
    ListViewEx *listView;
    PagingRule m_PagingRule;
private:
    void bottomAnimation(bool bIsShow);
    void bottomViewRefresh(bool bIsShow);
private:
    CADipSize size;
    
    FSNewsView2Cell *m_CurCell;
    FSNewsBottomView *m_FSNewsBottomView;

    
    vector<std::string> m_aryContent;
    
public:
    void openCatalog();

public:
    static FSNewsView2* curFSNewsView2;
    static void staticOpenCatalog();
};


#endif /* defined(__SharpMessage__FSNewsView2__) */
