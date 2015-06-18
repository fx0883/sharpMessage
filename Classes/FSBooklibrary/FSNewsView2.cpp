//
//  FSNewsView2.cpp
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#include "FSNewsView2.h"
#include "FSContext.h"
#include "FSNewsCatalog.h"
#include "FSDataManager.h"
#include "BookMarkInfo.h"


#define CAColor_blueStyle ccc4(51,204,255,255)




//静态数据成员的定义和初始化
FSNewsView2* FSNewsView2::curFSNewsView2 = NULL;

FSNewsView2::FSNewsView2()
: m_CurCell(NULL)
,m_FSPageSliderView(NULL)
,m_chapterInfo(NULL)

{
    m_PagingRule.lineNumber = 16;
    m_PagingRule.lineTextNumber = 13;
    curFSNewsView2 = this;

}

void FSNewsView2::staticOpenCatalog()
{
    curFSNewsView2->openCatalog();
}

void FSNewsView2::openCatalog()
{
    int curNewsId = this->getChapterInfo()->getNewsID();
    FSNewsCatalog *fsnewscatalog = new FSNewsCatalog(curNewsId);
    
    fsnewscatalog->loadChapter =   &FSNewsView2::staticLoadChapter;;
    
    CANavigationController *nav = FSContext::GetInstance().getMainNavController();
    nav->pushViewController(fsnewscatalog, true);
    
}

//static void staticLoadChapter(CAObject *chapterInfo);

void FSNewsView2::staticLoadChapter(CAObject *chapterInfo)
{
    curFSNewsView2->loadCatalog(chapterInfo);
}

void FSNewsView2::loadCatalog(CAObject *chapterInfo)
{
    ChapterInfo *chpInfo = (ChapterInfo*)chapterInfo;
    
    this->setChapterInfo(chpInfo);
    FSDataManager::GetInstance().getNewsManager()->setCurChapterInfo(chpInfo);
    m_chapterInfo=chpInfo;
    
    this->calcPagingRule();
    this->loadData();
    this->refreshView();
    
    this->listView->reloadData();
    this->listView->setCurrPage(0, false);
    
//    m_FSPageSliderView->setMaXPage()
    float fmaxPage = (float)m_aryContent.size();
    if(fmaxPage<1)
        fmaxPage = 1;
    m_FSPageSliderView->setSliderMax(fmaxPage);
}

void FSNewsView2::staticChangePage(int pageNumber)
{
    curFSNewsView2->changePage(pageNumber);
}

void FSNewsView2::changePage(int pageNumber)
{
    this->listView->setCurrPage(pageNumber, false);
}



void FSNewsView2::staticShowChangeSlider()
{
    curFSNewsView2->showChangeSlider();
}

void FSNewsView2::showChangeSlider()
{
    m_FSPageSliderView->setVisible(true);
}




void FSNewsView2::staticShowReadSettingView()
{
    curFSNewsView2->showReadSettingView();
}

void FSNewsView2::showReadSettingView()
{
    m_FSReadSettingView->setVisible(true);
}



void FSNewsView2::staticChangeReadSetting()
{
    curFSNewsView2->changeReadSetting();
}

void FSNewsView2::changeReadSetting()
{
    listView->reloadData();
}

void FSNewsView2::calcPagingRule()
{
    float screenHeight =  CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height;
    CALabel *calcLabel = new CALabel();
    
    screenHeight = screenHeight - NEWSCELLBOTTOMHEIGHT-NEWSCELLTOPHEIGHT;
    
    float screenWidth =  CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width;
    
    screenWidth = screenWidth - NEWSCELLTOPHEIGHT*2;

    
    float curFontSize = CrossApp::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 32;
    calcLabel->setFontSize(curFontSize);
    int lineFontHeihtItem = calcLabel->getLineFontHeight();
    
    m_PagingRule.lineNumber = screenHeight/lineFontHeihtItem;
    
    
    int fontWidthItem = calcLabel->getFontCNUTF8Width();
    m_PagingRule.lineTextNumber = screenWidth/fontWidthItem;
    
    
    float preciseLineNumber = screenHeight/lineFontHeihtItem;
    
    if(preciseLineNumber-m_PagingRule.lineNumber <= 0.5)
    {
        m_PagingRule.lineNumber--;
    }
}


FSNewsView2::~FSNewsView2()
{

}

void FSNewsView2::viewDidLoad()
{
    size = this->getView()->getBounds().size;
    
//    listView = ListViewEx::createWithCenter(CADipRect(size.width*0.5,size.height*0.5,size.width,size.height));
    listView = ListViewEx::createWithFrame(this->getView()->getBounds());
    listView->setListViewDelegate(this);
    listView->setListViewDataSource(this);
    listView->setAllowsSelection(true);
    listView->setAllowsMultipleSelection(true);
    listView->setListViewOrientation(CAListViewOrientationHorizontal);
    listView->setSeparatorColor(CAColor_magenta);
    listView->setSeparatorViewHeight(0);
    
    //listView->setColor(ccc4(151,212,255,255));
    
    //	listView->setListHeaderHeight(_px(100));
    //	listView->setListFooterHeight(_px(100));
//    listView->setListHeaderView(CAView::createWithColor(CAColor_gray));
//    listView->setListFooterView(CAView::createWithColor(CAColor_gray));
    this->getView()->addSubview(listView);

    
    
    //	CALabel* header = CALabel::createWithCenter(CADipRect(50, size.height*0.5, 100, size.height));
    //	header->setText("Header");
    //	header->setFontSize(35);
    //	header->setTextAlignment(CATextAlignmentCenter);
    //	header->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    //	listView->getListHeaderView()->addSubview(header);
    //
    //	CALabel* footer = CALabel::createWithCenter(CADipRect(50, size.height*0.5, 100, size.height));
    //	footer->setText("Footer");
    //	footer->setFontSize(35);
    //	footer->setTextAlignment(CATextAlignmentCenter);
    //	footer->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    //	CAView* listFootView = CAView::createWithColor(CAColor_green);
    //	listView->getListFooterView()->addSubview(footer);
    
 
    

    
    
    
    this->calcPagingRule();
    this->loadData();
    this->addBottomView();
    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->setNavigationBarHidden(true, false);
    this->refreshView();
    
}


void FSNewsView2::addBottomView()
{
    size = this->getView()->getBounds().size;
    CrossApp::CADipRect rect = CADipRect(0, size.height*10/11, size.width, size.height/11);
    CCLOG("***************************************,%f",size.width);
    
    m_FSNewsBottomView = FSNewsBottomView::createWithFrame(rect);
    //m_FSNewsBottomView->setMaXPage((int)m_aryContent.size());
    m_FSNewsBottomView->setColor(ccc4(11,212,255,255));
    this->getView()->addSubview(m_FSNewsBottomView);
    m_FSNewsBottomView->initView();
    m_FSNewsBottomView->setVisible(false);
    
    m_FSNewsBottomView->openCatalog = &FSNewsView2::staticOpenCatalog;
    
    m_FSNewsBottomView->showPageSlider = &FSNewsView2::staticShowChangeSlider;
    
    m_FSNewsBottomView->showReadSettingView = &FSNewsView2::staticShowReadSettingView;
    
    
    
    CrossApp::CADipRect rect2 = CADipRect(0, size.height*10/12, size.width, size.height/6);
    m_FSPageSliderView = FSPageSliderView::createWithFrame(rect2);
    m_FSPageSliderView->setMaXPage((int)m_aryContent.size());
    m_FSPageSliderView->setColor(ccc4(11,212,255,255));
    this->getView()->addSubview(m_FSPageSliderView);
    m_FSPageSliderView->initView();
    m_FSPageSliderView->setVisible(false);
    m_FSPageSliderView->changePage = &FSNewsView2::staticChangePage;
    
    
    
    CrossApp::CADipRect rect3 = CADipRect(0, size.height*9/12, size.width, size.height/4);
    m_FSReadSettingView = FSReadSettingView::createWithFrame(rect3);

    m_FSReadSettingView->setColor(ccc4(11,212,255,255));
    this->getView()->addSubview(m_FSReadSettingView);
    m_FSReadSettingView->initView();
    m_FSReadSettingView->setVisible(false);
    m_FSReadSettingView->changeReadSetting = &FSNewsView2::staticChangeReadSetting;
    
    
}

void FSNewsView2::viewDidUnload()
{
    
}

void FSNewsView2::listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index)
{
    static bool s = true;

    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->setNavigationBarHidden(!s, false);

    this->bottomAnimation(s);


    m_FSPageSliderView->setVisible(false);
    m_FSReadSettingView->setVisible(false);
    s = !s;
    return;
}

void FSNewsView2::listViewDidDeselectCellAtIndex(CAListView *listView, unsigned int index)
{
    
}

unsigned int FSNewsView2::numberOfIndex(CAListView *listView)
{
    unsigned int number =0;
    number = (unsigned int)m_aryContent.size();
    this->listView->setListCount(number);
    return number;
}

unsigned int FSNewsView2::listViewHeightForIndex(CAListView *listView, unsigned int index)
{
    return listView->getBounds().size.width;
    //return _px(500);
}

CAListViewCell* FSNewsView2::listViewCellAtIndex(CAListView *listView, const CCSize& cellSize, unsigned int index)
{
    CADipSize _size = cellSize;
    FSNewsView2Cell* cell = (FSNewsView2Cell*)listView->dequeueReusableCellWithIdentifier("FSNewsView2Cell");
    if (!cell)
    {
        cell = FSNewsView2Cell::create("FSNewsView2Cell", CADipRect(0, 0, _size.width, _size.height));
        cell->initWithCell();
    }
    char idx[10] = "";
    sprintf(idx,"list%d",index);
    string& strContent = m_aryContent.at(index);
//    CALabel* test = (CALabel*)cell->getSubviewByTag(100);
//    test->setText(idx);
    cell->updateWithCell();
    m_chapterPrecent = ((float)(index+1))/m_aryContent.size();
    cell->setContent(strContent,m_chapterPrecent);
    
    m_FSPageSliderView->setSliderCurPage(index);
    
    return cell;
}

void FSNewsView2::reshapeViewRectDidFinish()
{
    listView->setFrame(this->getView()->getBounds());
//    if(m_CurCell)
//        m_CurCell->updateWithCell();
    this->listView->reloadData();
    
//    this->bottomAnimation(true);
}


void FSNewsView2::loadData()
{
    //            index=0;
//    string             stt = "“天龙八部”这名词出于佛经。许多大乘佛经叙述佛向诸菩萨、比丘等说法时，常有天龙八部参与听法。如《法华经·提婆达多品》：“天龙八部、人与非人，皆遥见彼龙女成佛”。“非人”是形貌似人而实际不是人的众生。\n　　“天龙八部”都是“非人”，包括八种神道怪物，因为以“天”及“龙”为首，所以称为“天龙八部”。八部者，一天，二龙，三夜叉，四乾达婆，五阿修罗，六迦楼罗，七紧那罗，八摩呼罗迦。\n　　“天”是指天神。在佛教中，天神的地位并非至高无上，只不过比人能享受到更大、更长久的福报而已。佛教认为一切事";
    
//        string             stt = "";
            string             stt = "·";
    //“天龙八部”这名词出于佛经。许多大乘佛经叙述佛向诸菩萨、比丘等说法时，常有天龙八部参与听法。
    //如《法华经·
//    “天龙八部、人与非人，皆遥见彼龙女成佛”。“非人”是形貌似人而实际不是人的众生。\n
                int size = (int)stt.size();
                size++;
    
   const char *aaa=stt.c_str();
    
//    “天龙八部”这名词出于佛经。许多大乘佛经叙述佛向诸菩萨、比丘等说法时，常有天龙八部参与听法。如《法华经·提婆达多品》：“天龙八部、人与非人，皆遥见彼龙女成佛”。“非人”是形貌似人而实际不是人的众生。\n　　“天龙八部”都是“非人”，包括八种神道怪物，因为以“天”及“龙”为首，所以称为“天龙八部”。八部者，一天，二龙，三夜叉，四乾达婆，五阿修罗，六迦楼罗，七紧那罗，八摩呼罗迦。\n　　“天”是指天神。在佛教中，天神的地位并非至高无上，只不过比人能享受到更大、更长久的福报而已。佛教认为一切事
    
    
    PagingRule curPagingRule;
    
    curPagingRule.lineNumber = 0;
    curPagingRule.lineTextNumber = 0;
    
    const int countbyte=3;
    
    int curCountByte = 0;
    

    
    const char* str = m_chapterInfo->getChapterContent().c_str();
    std::string s;
//    int index=0;
    
    m_aryContent.clear();
    for ( int i = 0 , n = (int)m_chapterInfo->getChapterContent().size() ; i <= n ; i++ )
    {
        
        //文字字节数，这个为utf-8 ，一个占用3个字节
        if ((i>0 && curPagingRule.lineNumber == m_PagingRule.lineNumber) || i == n )
        {
            m_aryContent.push_back(s);
            s.clear();
            
//            index=0;
            curPagingRule.lineNumber = 0;
            curPagingRule.lineTextNumber = 0;
            
        }
        
//        char eChar[2];
//        eChar[0]=str[i];
//        eChar[1]=str[i+1];
//        string strEChar(eChar);
        
        if (str[i]=='\302'&&str[i+1]=='\345'&&str[i+2]=='\x8d'&&str[i+3]=='\xb7') {
            i=i+3;
            continue;
        }
        
        s += str[i];
        if(str[i] == '\n')
        {
            curPagingRule.lineTextNumber = 0;
            curPagingRule.lineNumber++;
        }
        else if(str[i] ==' '
                || str[i]=='.'
                || (str[i]=='\xc2'&&str[i+1]=='\xb7')
                )
        {
            if (str[i]=='\xc2'&&str[i+1]=='\xb7') {
                s += str[++i];
            }
            curCountByte = 0;
            curPagingRule.lineTextNumber++;
            
            if (curPagingRule.lineTextNumber == m_PagingRule.lineTextNumber) {
                curPagingRule.lineTextNumber = 0;
                curPagingRule.lineNumber++;
                
            }

        }
        else
        {
            curCountByte++;
            if(countbyte==curCountByte)
            {
                curCountByte = 0;
                curPagingRule.lineTextNumber++;
                
                if (curPagingRule.lineTextNumber == m_PagingRule.lineTextNumber) {
                    curPagingRule.lineTextNumber = 0;
                    curPagingRule.lineNumber++;

                }
                
                
            }
            
        }
        
        
            
            
        
        
    }
}




void FSNewsView2::bottomAnimation(bool bIsShow)
{
    //开始执行动画
    CAViewAnimation::beginAnimations("", NULL);
    //动画时长
    CAViewAnimation::setAnimationDuration(1.0f);
    //动画延迟时长执行
    //CAViewAnimation::setAnimationDelay(0.3f);
    //动画波频控制
    CAViewAnimation::setAnimationCurve(CAViewAnimationCurveLinear);
    
//    CAViewAnimation::setAnimationRepeatCount(1.5);
    
    CAViewAnimation::setAnimationRepeatAutoreverses(true);
    //    //动画开始前回调(两参数)
    //    CAViewAnimation::setAnimationWillStartSelector(this, CAViewAnimation2_selector(FourthViewController::willStartAction));
    //    //动画完成回调(两参数)
    //    CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation2_selector(FourthViewController::didStopAction));
    
    //    this->refreshView(true);
    bottomViewRefresh(bIsShow);
    //执行动画
    CAViewAnimation::commitAnimations();
}

void FSNewsView2::bottomViewRefresh(bool bIsShow)
{
//    //CCSize size = this->getView()->getBounds().size;
//    CrossApp::CCRect rect = m_FSNewsBottomView->getFrame();
//    if(rect.origin.y < this->getView()->getBounds().size.height)
//    {
////        CrossApp::CCRect rect = CCRectMake(0, size.height*9/10, size.width, size.height/10);
//        
//        
//        //m_FSNewsBottomView->setFrame(rect);
//        rect.origin.y = this->getView()->getBounds().size.height;
//    }
//    else
//    {
////        CrossApp::CCRect rect = CCRectMake(0, size.height, size.width, size.height/10);
//        
//        rect.origin.y = this->getView()->getBounds().size.height - rect.size.height;
//    }
//    m_FSNewsBottomView->setFrame(rect);
    
    m_FSNewsBottomView->setVisible(bIsShow);
}



void FSNewsView2::viewDidAppear()
{
//        if(!m_NavBarItem)
//        {
//            m_NavBarItem = CANavigationBarItem::create(m_chapterInfo->getChapterTitle());
//        }
//    this->setNavigationBarItem(m_NavBarItem);
//    this->refreshView();
}

void FSNewsView2::refreshView()
{

    m_NavBarItem = CANavigationBarItem::create(m_chapterInfo->getChapterTitle());
    
    CABarButtonItem* rightButton = CABarButtonItem::create("",  CAImage::create("tabbar_function/userCenter_1.png"),  CAImage::create("tabbar_function/userCenter_1.png"));
    
    
    rightButton->setTarget(rightButton, CAControl_selector(FSNewsView2::onClickBookMark));

    
    m_NavBarItem->addRightButtonItem(rightButton);
//    m_NavBarItem->addRightButtonItem(CrossApp::CABarButtonItem *item)
    this->setNavigationBarItem(m_NavBarItem);
    //m_NavBarItem->autorelease();
}

void FSNewsView2::onClickBookMark(CAControl* btn, CCPoint point)
{
    //加入标签
    BookMarkInfo *bookmarkinfo = new BookMarkInfo();
    ChapterInfo *curChapterInfo =  FSDataManager::GetInstance().getNewsManager()->getCurChapterInfo();
//    int dff= this->getChapterInfo()->getNewsID();
    
    bookmarkinfo->setChapterID(curChapterInfo->getChapterID());
    bookmarkinfo->setNewsID(curChapterInfo->getNewsID());
    
    bookmarkinfo->setMarkProgress(curFSNewsView2->getChapterPrecent());
    
    bool flag = FSDataManager::GetInstance().getNewsManager()->addBookMarkInfo(bookmarkinfo);
    if (!flag) {
        //加入失败
    }
}

//add by FX
//void FSNewsView2::loadData()
//{
//    PagingRule curPagingRule;
//    
//    curPagingRule.lineNumber = 0;
//    curPagingRule.lineTextNumber = 0;
//    
//    
//    const char* str = m_chapterInfo->getChapterContent().c_str();
//    std::string s;
//    int index=0;
//    for ( int i = 0 , n = (int)m_chapterInfo->getChapterContent().size() ; i <= n ; i++ )
//    {
// 
//        if ((i>0 && index == m_lineNumber) || i == n)
//        {
//            m_aryContent.push_back(s);
//            s.clear();
//    
//            index=0;
//            string             stt = "老儿.";
//            int size = (int)stt.size();
//            size++;
//
//        }
//
//        {
//
//            s += str[i];
//            if(str[i]!='\n' && str[i]!=' '&&str[i]!='.')
//            {
//                index++;
//            }
//            
//            
//        }
//        
//    }
//}

