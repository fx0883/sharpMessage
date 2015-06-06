//
//  FSNewsView2.cpp
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#include "FSNewsView2.h"


#define CAColor_blueStyle ccc4(51,204,255,255)





FSNewsView2::FSNewsView2()
: m_CurCell(NULL)
{
    m_PagingRule.lineNumber = 12;
    m_PagingRule.lineTextNumber = 14;
    

}

FSNewsView2::~FSNewsView2()
{
//    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
//    drawer->setTouchMoved(true);
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
    
    this->addBottomView();
    
    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->setNavigationBarHidden(true, false);
    
    
    
    
    this->loadData();
    
}


void FSNewsView2::addBottomView()
{

//    m_FSNewsBottomView->init();
    CCSize size = this->getView()->getBounds().size;
    
    //CCSize size = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    //m_FSNewsBottomView->initWithCenter(const CrossApp::CCRect &rect, cc4(255,255,255,255);
    
    CrossApp::CCRect rect = CCRectMake(0, size.height*10/11, size.width, size.height/11);
    
    
    CCLOG("***************************************,%f",size.width);
    
    m_FSNewsBottomView = FSNewsBottomView::createWithFrame(rect);
    m_FSNewsBottomView->setColor(ccc4(11,212,255,255));
    this->getView()->addSubview(m_FSNewsBottomView);
    m_FSNewsBottomView->initView();
    m_FSNewsBottomView->setVisible(false);
}

void FSNewsView2::viewDidUnload()
{
    
}

void FSNewsView2::listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index)
{
    static bool s = true;
//
//    CAWindow* window = CAApplication::getApplication()->getRootWindow();
//
//    CANavigationController* nav = this->getNavigationController();
//    CATabBarController* tab = (CATabBarController*)window->getRootViewController();
//    nav->setNavigationBarHidden(!s, true);
//    tab->setTabBarHidden(!s, true);
//    
//

    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    nav->setNavigationBarHidden(!s, false);

    this->bottomAnimation(s);
    
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
    cell->setContent(strContent);
    

    
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
    PagingRule curPagingRule;
    
    curPagingRule.lineNumber = 0;
    curPagingRule.lineTextNumber = 0;
    
    const int countbyte=3;
    
    int curCountByte = 0;
    const char* str = m_chapterInfo->getChapterContent().c_str();
    std::string s;
    int index=0;
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
        
        
            
        s += str[i];
        if(str[i] == '\n')
        {
            curPagingRule.lineTextNumber = 0;
            curPagingRule.lineNumber++;
        }
        else if(str[i] ==' ' || str[i]=='.')
        {
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

