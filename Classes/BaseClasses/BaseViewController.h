//
//  BaseViewController.h
//  SharpMessage
//
//  Created by apple on 6/7/15.
//
//

#ifndef __SharpMessage__BaseViewController__
#define __SharpMessage__BaseViewController__

#include <stdio.h>
#include <iostream>
#include "CrossApp.h"


class BaseViewController: public CAViewController
{
    
protected:
    
    virtual void viewDidLoad() {};
    
    virtual void viewDidUnload() {};
    
    virtual void viewDidAppear() {};
    
    virtual void viewDidDisappear() {};
    
    virtual void reshapeViewRectDidFinish() {};
    
    virtual void keyBackClicked() {};
    
    virtual void keyMenuClicked() {};
    
public:
    
    BaseViewController();
    
    virtual ~BaseViewController();
    
//protected:
//    CANavigationBarItem* m_NavBarItem;
    
    
};


#endif /* defined(__SharpMessage__BaseViewController__) */
