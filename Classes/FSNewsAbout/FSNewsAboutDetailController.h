//
//  FSNewsAboutDetailController.h
//  SharpMessage
//
//  Created by apple on 7/6/15.
//
//

#ifndef __SharpMessage__FSNewsAboutDetailController__
#define __SharpMessage__FSNewsAboutDetailController__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"

class FSNewsAboutDetailController : public CAViewController
{
public:
    FSNewsAboutDetailController();
    virtual ~FSNewsAboutDetailController();
    
    void viewDidLoad();
    
    void viewDidUnload();
    
    void viewDidAppear();
    
    
    CREATE_FUNC(FSNewsAboutDetailController)
    
    bool init();
    
    void setAboutText(string& strText);
    
public:
    CADipSize _size;

};

#endif /* defined(__SharpMessage__FSNewsAboutDetailController__) */
