//
//  MainTabController.h
//  SharpMessage
//
//  Created by 冯璇 on 15/4/19.
//
//

#ifndef __SharpMessage__MainTabController__
#define __SharpMessage__MainTabController__

#include <stdio.h>
#include <iostream>
#include "CrossApp.h"

class MainTabBarController:public CATabBarController
{
public:
    MainTabBarController();
    virtual ~MainTabBarController();
    static CAWindow* createWindow();
protected:
    virtual void viewDidLoad();
    virtual void viewDidUnload();
};



#endif /* defined(__SharpMessage__MainTabController__) */
