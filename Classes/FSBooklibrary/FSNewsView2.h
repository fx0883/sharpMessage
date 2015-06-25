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
#include "FSPageSliderView.h"
#include "BaseViewController.h"
#include "FSReadSettingView.h"

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
     CC_SYNTHESIZE_PASS_BY_REF(float,m_chapterPrecent,ChapterPrecent)
    CC_SYNTHESIZE_PASS_BY_REF(string,m_curContent,CurContent)
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
    FSPageSliderView *m_FSPageSliderView;
    FSReadSettingView *m_FSReadSettingView;

    
    vector<std::string> m_aryContent;
    
public:
    string getDigestForMark();
    
private:
    void openCatalog();
    void loadCatalog(CAObject *chapterInfo);
    void changePage(int pageNumber);
    void showChangeSlider();
    void showReadSettingView();
    void changeReadSetting();
    void onClickBookMark(CAControl* btn, CCPoint point);
    void gotoChapterProgress(float progress);
public:
    static FSNewsView2* curFSNewsView2;
    static void staticOpenCatalog();
    static void staticLoadChapter(CAObject *chapterInfo);
    static void staticChangePage(int pageNumber);
    static void staticShowChangeSlider();
    static void staticShowReadSettingView();
    static void staticChangeReadSetting();
    static void staticgotoChapterProgress(float progress);
};


#endif /* defined(__SharpMessage__FSNewsView2__) */
