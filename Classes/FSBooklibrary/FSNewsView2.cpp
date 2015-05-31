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
: m_lineNumber(666)
{
//    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
//    drawer->setTouchMoved(false);
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





//add by FX
void FSNewsView2::loadData()
{
    //    double scaleNumber = loadScale();
    
    //    string[] strArray = m_strContent.substr()
    
    //assert(m_chapterInfo)
    
    
    const char* str = m_chapterInfo->getChapterContent().c_str();
    std::string s;
    int index=0;
    for ( int i = 0 , n = (int)m_chapterInfo->getChapterContent().size() ; i <= n ; i++ )
    {
 
//        if ( str[i] == '\n' || i == n || (i>0 && i%m_lineNumber == 0))
        if ((i>0 && index == m_lineNumber) || i == n)
    //    if ( str[i] == '\n' || i == n)
        {
            //            CCLabelTTF *pLabel = CCLabelTTF::create( s.c_str() , UTF8("宋体") , setting.m_nTextSize , CCSize( getView()->getFrame().size.width - 40 , 0 ) , CATextAlignmentLeft );
            //            pLabel->setColor( setting.IntToCCC4( setting.m_nTextColor ) );
            //            pLabel->setFrameOrigin( CCPoint( 20 , ypos ) );
            // m_pScrollView->addSubview( pLabel );
            // ypos += pLabel->getFrame().size.height + 10;
            
            
            m_aryContent.push_back(s);
            s.clear();
    
            //            m_vecControls.push_back( pLabel );
            
//            if(i<n)
//            {
//               s += str[i];
//            }
            index=0;
            
            string             stt = "老儿.";
            
            //stt+="";
            
            int size = (int)stt.size();
            
            
            
            size++;
            
            //那就
            //最妙不过。”
            
            //说罢双眼瞪看卫天望，
            //嘿嘿冷笑。\n　　郭襄大喜，想不到此人如此知趣，这般帮着自己。\n
            
            
            //老儿.那就最妙不过。”说罢双眼瞪看卫天望，嘿嘿冷笑。\n　　郭襄大喜，想不到此人如此知趣，这般帮着自己。\n
            //　　卫天望给他这双眼一瞪，一张铁青的脸更加青了，冷冷的道：“尊驾是谁？”\n
            
//            stt = "老儿.那就最妙不过。”说罢双眼瞪看卫天望，嘿嘿冷笑。\n　　郭襄大喜，想不到此人如此知趣，这般帮着自己。\n　　卫天望给他这双眼一瞪，一张铁青的脸更加青了，冷冷的道：“尊驾是谁？”\n　　那人竟不理他，对郭襄道：“姑娘，你叫甚么名字？”郭襄道：“我姓郭，单名一个襄字。”那人鼓掌道：“啊，当真有眼不识泰山，原来便是四海闻名的郭大姑娘。令尊郭靖郭大侠，令堂黄蓉黄女侠，除了无知无识之徒、不明好歹之辈，江湖上谁人不知，哪人不晓？他二人文武双全，刀枪剑戟，拳掌气\345\212";
            
//                        string stt="抹去，莫着了凉。”曹云奇心中甜甜的说不出的受用，满腔怒气登时化为乌有，挥鞭在那女郎的灰马臀上轻轻一鞭。二人双骑，并肩驰去。\n　　那女郎名叫田青文，年纪虽轻，在关外武林中却已颇有名声。因她容貌美丽，性又机伶，辽东武林中公送她一个外号，叫作“锦毛貂”。那貂鼠在雪地中行走如飞，聪明伶俐， “锦毛”二字，自是形容她的美貌了。她父亲田归农逝世未久，是以她一身缟素，戴着重孝。\n　　两人急奔一阵，追上了殷吉、阮士中、周云阳三人。阮士中向曹云奇横了一眼，说道";
        
            
            //                       string stt="抹去，莫着了凉。”曹云奇心中甜甜的说不出的受用，满腔怒气登时化为乌有，挥鞭在那女郎的灰马臀上轻轻一鞭。二人双骑，并肩驰去。\n　　那女郎名叫田青文，年纪虽轻，在关外武林中却已颇有名声。因她容貌美丽，性又机伶，辽东武林中公送她一个外号，叫作“锦毛貂”。那貂鼠在雪地中行走如飞，聪明伶俐， “锦毛”二字，自是形容她的美貌了。她父亲田归农逝世未久，是以她一身缟素，戴着重孝。\n　　两人急奔一阵，追上了殷吉、阮士中、周云阳三人。阮士中向曹云奇横了一眼，说道";
            
            //， “锦毛”二字，自是形容她的美貌了。她父亲田归农逝世未久，是以她一身缟素，戴着重孝。
            //\n　　两人急奔一阵，追上了殷吉、阮士中、周云阳三人。阮士中向曹云奇横了一眼，说道
            
            //自是形容她的美貌了。她父亲田归农逝世未久，是以她一身缟素，戴着重孝。
            
            //那貂鼠在雪地中行走如飞，
            
            //“锦毛”二字，
            //聪明伶俐
        }
//        else
        {
//            if(str[i] != '\n')
            s += str[i];
            if(str[i]!='\n' && str[i]!=' '&&str[i]!='.')
            {
                index++;
            }
            
            
        }
        
    }
}

