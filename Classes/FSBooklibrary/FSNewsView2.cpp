//
//  FSNewsView2.cpp
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#include "FSNewsView2.h"
#include "FSNewsView2Cell.h"

#define CAColor_blueStyle ccc4(51,204,255,255)





FSNewsView2::FSNewsView2()
//: m_lineNumber(666)
{
    m_PagingRule.lineNumber = 13;
    m_PagingRule.lineTextNumber = 13;
    

}

FSNewsView2::~FSNewsView2()
{
//    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
//    drawer->setTouchMoved(true);
}

void FSNewsView2::viewDidLoad()
{
    size = this->getView()->getBounds().size;
    
    listView = ListViewEx::createWithCenter(CADipRect(size.width*0.5,size.height*0.5,size.width,size.height));
    listView->setListViewDelegate(this);
    listView->setListViewDataSource(this);
    listView->setAllowsSelection(true);
    listView->setAllowsMultipleSelection(true);
    listView->setListViewOrientation(CAListViewOrientationHorizontal);
    listView->setSeparatorColor(CAColor_magenta);
    listView->setSeparatorViewHeight(0);
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
    
    
    
    this->loadData();
    
}




void FSNewsView2::viewDidUnload()
{
    
}

void FSNewsView2::listViewDidSelectCellAtIndex(CAListView *listView, unsigned int index)
{
    
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
//        cell->initWithCell();
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




void FSNewsView2::loadData()
{
    PagingRule curPagingRule;
    
    curPagingRule.lineNumber = 0;
    curPagingRule.lineTextNumber = 0;
    
    
    const char* str = m_chapterInfo->getChapterContent().c_str();
    std::string s;
    int index=0;
    for ( int i = 0 , n = (int)m_chapterInfo->getChapterContent().size() ; i <= n ; i++ )
    {
        
        //文字字节数，这个为utf-8 ，一个占用3个字节
        if ((i>0 && index == m_PagingRule.lineTextNumber) || i == n)
        {
            m_aryContent.push_back(s);
            s.clear();
            
            index=0;
            string             stt = "老儿.";
            int size = (int)stt.size();
            size++;
            
        }
        
        
            
        s += str[i];
        if(str[i]!='\n' && str[i]!=' '&&str[i]!='.')
        {
            index++;
        }
        
        
            
            
        
        
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

