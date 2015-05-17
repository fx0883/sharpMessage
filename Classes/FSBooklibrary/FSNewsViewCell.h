//
//  FSNewsViewCell.h
//  SharpMessage
//
//  Created by apple on 15/5/17.
//
//

#ifndef __SharpMessage__FSNewsViewCell__
#define __SharpMessage__FSNewsViewCell__

#include <stdio.h>


#include "CrossApp.h"

USING_NS_CC;

class FSNewsViewCell:public CATableViewCell
{
public:
    FSNewsViewCell();
    virtual ~FSNewsViewCell();
    
    static FSNewsViewCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    
public:
    void initWithCell();
//    void cellBtnCallback(CAControl* btn, CCPoint point);
    void setContent(const std::string& strContext);
    
protected:
    virtual void normalTableViewCell();
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
    virtual void disabledTableViewCell();
    CALabel* cellText;

    
private:
    
};

#endif /* defined(__SharpMessage__FSNewsViewCell__) */
