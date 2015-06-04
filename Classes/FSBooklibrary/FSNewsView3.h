//
//  FSNewsView3.h
//  SharpMessage
//
//  Created by apple on 6/4/15.
//
//

#ifndef __SharpMessage__FSNewsView3__
#define __SharpMessage__FSNewsView3__

#include <stdio.h>
#include "CrossApp.h"
#include "ListViewEx.h"
#include "CrossAppExt.h"
#include "AppMacros.h"
#include "ChapterInfo.h"


class FSNewsView3 :public CAViewController,CAListViewDelegate,CAListViewDataSource
{
public:
    FSNewsView3();
    virtual ~FSNewsView3();
public:
    CC_SYNTHESIZE_PASS_BY_REF2(ChapterInfo*, m_chapterInfo, ChapterInfo)
    CC_SYNTHESIZE_PASS_BY_REF(int,m_lineNumber,LinNumber)
    
public:
//    virtual void listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index);
//    virtual void listViewDidDeselectCellAtIndex(CAListView *listView, unsigned int index);
//    virtual unsigned int numberOfIndex(CAListView *listView);
//    virtual unsigned int listViewHeightForIndex(CAListView *listView, unsigned int index);
//    virtual CAListViewCell* listViewCellAtIndex(CAListView *listView, const CCSize& cellSize, unsigned int index);
    
protected:
    void viewDidLoad();
    void viewDidUnload();
    void loadData();
protected:
    CAWebView *m_webView;
    CAScrollView *m_sfff;
//    ListViewEx *listView;
//    PagingRule m_PagingRule;
private:
    CADipSize size;
    
    
    vector<std::string> m_aryContent;
};



#endif /* defined(__SharpMessage__FSNewsView3__) */
