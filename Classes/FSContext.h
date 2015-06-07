//
//  FSContext.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSContext__
#define __SharpMessage__FSContext__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "AppMacros.h"

class FSContext:CAObject
{
    SINGLETON(FSContext)

public:
    string getFullDbPath();
    CC_SYNTHESIZE_PASS_BY_REF2(CANavigationController*, m_MainNavController, MainNavController)
    CC_SYNTHESIZE_PASS_BY_REF2(CATabBarController*, m_MainTabBarController, MainTabBarController)

    
};

#endif /* defined(__SharpMessage__FSContext__) */
