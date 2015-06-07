//
//  FSBooklibrary.h
//  SharpMessage
//
//  Created by 冯璇 on 15/4/19.
//
//

#ifndef __SharpMessage__FSBooklibrary__
#define __SharpMessage__FSBooklibrary__

#include <iostream>
#include "CrossApp.h"
#include "BaseViewController.h"

USING_NS_CC;

class FSBooklibrary: public BaseViewController, CACollectionViewDelegate, CACollectionViewDataSource, CAScrollViewDelegate
{
    
public:
    
    FSBooklibrary();
    
    virtual ~FSBooklibrary();
    
protected:
    
     void viewDidLoad();
    
     void viewDidUnload();
    
     void viewDidAppear();
    
public:
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
    
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
    virtual unsigned int numberOfSections(CACollectionView *collectionView);
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);

    
private:
    CADipSize size;
    CACollectionView* p_Conllection;
//    CANavigationBarItem* navBarItem;
    
    
};

#endif /* defined(__SharpMessage__FSBooklibrary__) */
