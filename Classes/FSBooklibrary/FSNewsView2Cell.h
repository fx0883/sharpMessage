#ifndef _My_ListViewCell_h_
#define _My_ListViewCell_h_

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class FSNewsView2Cell :public CAListViewCell
{
public:
	FSNewsView2Cell();
	virtual ~FSNewsView2Cell();

	static FSNewsView2Cell* create(const std::string& identifier,const CADipRect& _rect=CADipRectZero);

public:
	void initWithCell();
	void cellBtnCallback(CAControl* btn, CCPoint point);
    void setContent(const std::string& strContext);
    void updateWithCell();
protected:
	virtual void normalListViewCell();
	virtual void highlightedListViewCell();
	virtual void selectedListViewCell();
	virtual void disabledListViewCell();

private:

};

#endif