//
//  FSNewsCatalogCell.h
//  SharpMessage
//
//  Created by apple on 6/7/15.
//
//

#ifndef __SharpMessage__FSNewsCatalogCell__
#define __SharpMessage__FSNewsCatalogCell__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class FSNewsCatalogCell:public CATableViewCell
{
public:
    FSNewsCatalogCell();
    virtual ~FSNewsCatalogCell();
    
    static FSNewsCatalogCell* create(const std::string& identifier, const CADipRect& _rect = CADipRectZero);
    
public:
    void initWithCell();
//    void cellBtnCallback(CAControl* btn, CCPoint point);
public:
    void updateCell(string strTitle);
    void setSelectedCell(bool bIsSelected);
    
protected:
    virtual void normalTableViewCell();
    virtual void highlightedTableViewCell();
    virtual void selectedTableViewCell();
    virtual void disabledTableViewCell();
    
private:
    
};

#endif /* defined(__SharpMessage__FSNewsCatalogCell__) */
