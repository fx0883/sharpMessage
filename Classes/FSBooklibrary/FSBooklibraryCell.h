//
//  FSBooklibraryCell.h
//  SharpMessage
//
//  Created by apple on 15/5/7.
//
//

#ifndef __SharpMessage__FSBooklibraryCell__
#define __SharpMessage__FSBooklibraryCell__

#include <stdio.h>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "AppMacros.h"

#include "NewsInfo.h"
USING_NS_CC;

class FSBooklibraryCell: public CACollectionViewCell
{
    
    
    public:
        FSBooklibraryCell();
        ~FSBooklibraryCell();
    public:
        bool init();
        void initWithSize(CADipSize& cellSize);
        void setNewsInfo(NewsInfo *newsinfo);
    
    private:
        CAImageView* itemImage;
    
  //  CALabel*   itemText;
    
};



#endif /* defined(__SharpMessage__FSBooklibraryCell__) */
