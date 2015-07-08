//
//  FSWebViewController.h
//  SharpMessage
//
//  Created by apple on 7/7/15.
//
//

#ifndef __SharpMessage__FSWebViewController__
#define __SharpMessage__FSWebViewController__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"

class FSWebViewController : public CAViewController
{
public:
    FSWebViewController();
    virtual ~FSWebViewController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    
    CREATE_FUNC(FSWebViewController)
    
    bool init();
    
    void setTitleAndUrl(string& strTitle,string& url);
    void setTitleAndFileName(string& strTitle,string& fileName);
    
public:
    CADipSize _size;

protected:
    CAWebView *m_webView;
    string m_strTitle;
    string m_fileName;
    
private:
    void loadContent();

};

#endif /* defined(__SharpMessage__FSWebViewController__) */
