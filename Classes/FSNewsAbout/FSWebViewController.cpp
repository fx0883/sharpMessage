//
//  FSWebViewController.cpp
//  SharpMessage
//
//  Created by apple on 7/7/15.
//
//

#include "FSWebViewController.h"




FSWebViewController::FSWebViewController()
:m_webView(NULL),m_fileName(""),m_strTitle("")
{
    
}

FSWebViewController::~FSWebViewController()
{
    
}

bool FSWebViewController::init()
{
    return true;
    
}

void FSWebViewController::viewDidAppear()
{
    
    CANavigationBarItem *navBarItem = CANavigationBarItem::create(m_strTitle);
    //    this->getTabBarController()->setNavigationBarItem(navBarItem);
    
    //    CAWindow* window = CAApplication::getApplication()->getRootWindow();
    //    CANavigationController *nav = (CANavigationController*)window->getRootViewController();
    this->setNavigationBarItem(navBarItem);
    
}

void FSWebViewController::viewDidLoad()
{
    _size = this->getView()->getBounds().size;
    //CAScrollView *srv = CAScrollView::createWithFrame(this->getView()->getBounds());
    m_webView = CAWebView::createWithFrame(this->getView()->getBounds());
    
    this->getView()->addSubview(m_webView);
    
    
    
    loadContent();
    
    //    CC_PROPERTY_IS(bool, m_bShowsHorizontalScrollIndicator, ShowsHorizontalScrollIndicator);
    //
    //    CC_PROPERTY_IS(bool, m_bShowsVerticalScrollIndicator, ShowsVerticalScrollIndicator);
    //
    //    CC_PROPERTY_IS(bool, m_bShowsScrollIndicators, ShowsScrollIndicators);
    

}

void FSWebViewController::loadContent()
{
    if (m_fileName.size()>0) {
        m_webView->loadFile(m_fileName);
    }
}


void FSWebViewController::setTitleAndUrl(string& strTitle,string& url)
{
    m_strTitle = strTitle;
    //m_webView->
    m_webView->loadURL(url);
}

void FSWebViewController::setTitleAndFileName(string& strTitle,string& fileName)
{
    m_strTitle = strTitle;
    //m_webView->
    //m_webView->loadFile(fileName);
    
    m_fileName = fileName;
}


void FSWebViewController::viewDidUnload()
{
    
}
