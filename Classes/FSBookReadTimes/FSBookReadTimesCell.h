//
//  FSBookReadTimesCell.h
//  SharpMessage
//
//  Created by apple on 7/3/15.
//
//

#ifndef __SharpMessage__FSBookReadTimesCell__
#define __SharpMessage__FSBookReadTimesCell__

#include <stdio.h>


#include <iostream>
#include "CrossApp.h"
#include "NewsInfo.h"

USING_NS_CC;

class FSBookReadTimesCell:public CATableViewCell
{
public:
    FSBookReadTimesCell();
    virtual ~FSBookReadTimesCell();
    
    static FSBookReadTimesCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    
public:
    void initWithCell();
    void cellBtnCallback(CAControl* btn, CCPoint point);
    void updateNewsInfoForCell(NewsInfo *newsinfo);
    
protected:
    virtual void normalTableViewCell();
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
    virtual void disabledTableViewCell();
    
private:
    
};

#endif /* defined(__SharpMessage__FSBookReadTimesCell__) */
