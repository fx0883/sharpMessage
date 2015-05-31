//
//  ListViewEx.cpp
//  SharpMessage
//
//  Created by apple on 5/31/15.
//
//

#include "ListViewEx.h"

ListViewEx* ListViewEx::createWithFrame(const CCRect& rect)
{
    ListViewEx* listView = new ListViewEx();
    if (listView && listView->initWithFrame(rect))
    {
        listView->autorelease();
        return listView;
    }
    CC_SAFE_DELETE(listView);
    return NULL;
}

ListViewEx* ListViewEx::createWithCenter(const CCRect& rect)
{
    ListViewEx* listView = new ListViewEx();
    if (listView && listView->initWithCenter(rect))
    {
        listView->autorelease();
        return listView;
    }
    CC_SAFE_DELETE(listView);
    return NULL;
}


void ListViewEx::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
    CAListView::ccTouchEnded(pTouch, pEvent);
    
    
    //add By FX
    if (m_pListViewOrientation == CAListViewOrientationHorizontal)
    {
        float off_x = -m_tInertia.x;
        
        if (off_x > 0)
        {
            m_eListViewExState = CAListViewNext;
        }
        else if (off_x < 0)
        {
            m_eListViewExState = CAListViewLast;
        }
        else
        {
            m_eListViewExState = CAListViewNone;
        }
    }
    else
    {
        float off_y = -m_tInertia.y;
        
        if (off_y > 0)
        {
            m_eListViewExState = CAListViewNext;
        }
        else if (off_y < 0)
        {
            m_eListViewExState = CAListViewLast;
        }
        else
        {
            m_eListViewExState = CAListViewNone;
        }
    }
    
    int page = this->getCurrPage();
    if (m_eListViewExState == CAListViewNext)
    {
        page++;
    }
    else if (m_eListViewExState == CAListViewLast)
    {
        page--;
    }
    else
    {
        if (m_pListViewOrientation == CAListViewOrientationHorizontal)
        {
            float width = this->getBounds().size.width;
            float off_x = this->getContentOffset().x - this->getCurrPage() * width;
            
            if (off_x > width/2)
            {
                page++;
            }
            else if (off_x < -width/2)
            {
                page--;
            }
        }
        else
        {
            float height = this->getBounds().size.height;
            float off_y = this->getContentOffset().y - this->getCurrPage() * height;
            
            if (off_y > height/2)
            {
                page++;
            }
            else if (off_y < -height/2)
            {
                page--;
            }
        }
    }
    
    if (!pTouch->isDelta())
    {
//        if (m_pPageViewDelegate)
//        {
//            CCPoint point = this->convertTouchToNodeSpace(pTouch);
//            m_pPageViewDelegate->pageViewDidSelectPageAtIndex(this, this->getCurrPage(), point);
//        }
    }
    else
    {
        page = MIN(page, this->isListCount() - 1);
        page = MAX(page, 0);
        
        this->setCurrPage(page, true, true);
    }

    
    
}


void ListViewEx::setCurrPage(int var, bool animated, bool listener)
{
    var = MIN(var, this->isListCount() - 1);
    var = MAX(var, 0);
    
    m_nCurrPage = var;
//
    if (m_pListViewOrientation == CAListViewOrientationHorizontal)
    {
        this->setContentOffset(CCPoint(m_nCurrPage * this->getBounds().size.width, 0), animated);
    }
    else
    {
        this->setContentOffset(CCPoint(0, m_nCurrPage * this->getBounds().size.height), animated);
    }
    
}
//
int ListViewEx::getCurrPage()
{
    return m_nCurrPage;
}
//
