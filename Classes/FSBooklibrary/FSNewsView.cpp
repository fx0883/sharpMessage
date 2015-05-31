//
//  FSNewsView.cpp
//  SharpMessage
//
//  Created by apple on 15/5/17.
//
//

#include "FSNewsView.h"
#include "FSNewsViewCell.h"
#include <string>
using namespace::std;

#define CAColor_blueStyle ccc4(51,204,255,255)

#define SCALEKEY "ScaleKey"



FSNewsView::FSNewsView()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
    
    m_chapterInfo =NULL;
    m_lineNumber = 20*3;
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


//调整大小
void FSNewsView::changeScale(bool bZoomIn)
{
    double scaleNumber = loadScale();
    scaleNumber += 0.1;
    //根据scale算出Size大小
    
}

void FSNewsView::loadData()
{
//    double scaleNumber = loadScale();
    
//    string[] strArray = m_strContent.substr()
    
    //assert(m_chapterInfo)

    
    const char* str = m_chapterInfo->getChapterContent().c_str();
    std::string s;
    
    for ( int i = 0 , n = (int)m_chapterInfo->getChapterContent().size() ; i <= n ; i ++ )
    {
        
//        if ( str[i] == '\n' || i == n || (i>0 && i%m_lineNumber==0))
        if ( str[i] == '\n' || i == n)
        {
//            CCLabelTTF *pLabel = CCLabelTTF::create( s.c_str() , UTF8("宋体") , setting.m_nTextSize , CCSize( getView()->getFrame().size.width - 40 , 0 ) , CATextAlignmentLeft );
//            pLabel->setColor( setting.IntToCCC4( setting.m_nTextColor ) );
//            pLabel->setFrameOrigin( CCPoint( 20 , ypos ) );
//            m_pScrollView->addSubview( pLabel );
//            ypos += pLabel->getFrame().size.height + 10;
            
            
            m_aryContent.push_back(s);
            s.clear();
//            m_vecControls.push_back( pLabel );
        }
        else
        {
            s += str[i];
        }
    }
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
    p_TableView->setSeparatorViewHeight(15);
    p_TableView->setBackGroundColor(CAColor_yellow);
    p_TableView->setSeparatorViewHeight(0);
    this->getView()->addSubview(p_TableView);
    

    this->loadData();
}

void FSNewsView::viewDidUnload()
{
    
}

//void FSNewsView::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
//{
//    
//}
//
//void FSNewsView::tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
//{
//    
//}

CATableViewCell* FSNewsView::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
    CADipSize _size = cellSize;
    FSNewsViewCell *cell = dynamic_cast<FSNewsViewCell*>(table->dequeueReusableCellWithIdentifier("newsView"));
//  MyTableViewCell* cell = dynamic_cast<MyTableViewCell*>(table->dequeueReusableCellWithIdentifier("CrossApp"));
    if (cell == NULL)
    {
        cell = FSNewsViewCell::create("newsView", CADipRect(0, 0, _size.width, _size.height));
        
    }
    cell->setFrame(CADipRect(0, 0, _size.width, _size.height));
    cell->updateWithCell();
    string& strContent = m_aryContent.at(row);
    cell->setContent(strContent);
    return cell;
    
}

//CAView* FSNewsView::tableViewSectionViewForHeaderInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
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
//
//CAView* FSNewsView::tableViewSectionViewForFooterInSection(CATableView* table, const CCSize& viewSize, unsigned int section)
//{
//    CAView* view = CAView::createWithColor(CAColor_gray);
//    
//    
//    return view;
//}

unsigned int FSNewsView::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    int ret=0;

    
    ret = (int)m_aryContent.size();
    
    return ret;
}

unsigned int FSNewsView::numberOfSections(CATableView *table)
{
    return 1;
}

unsigned int FSNewsView::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    int intHeight = 80;
    string& strContext = m_aryContent.at(row);
    
    int textNumber = (int)strContext.size();
    intHeight = intHeight+ textNumber/63*80;
    
    CCLOG("====%d",textNumber);
    
    
    CCLOG(strContext.c_str());
    return _px(intHeight);
}
//
//unsigned int FSNewsView::tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
//{
//    return _px(50);
//}
//
//unsigned int FSNewsView::tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
//{
//    return 1;
//}


