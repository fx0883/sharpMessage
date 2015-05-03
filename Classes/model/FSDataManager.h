//
//  FSDataManager.h
//  SharpMessage
//
//  Created by 冯璇 on 15/5/2.
//
//

#ifndef __SharpMessage__FSDataManager__
#define __SharpMessage__FSDataManager__

#include <stdio.h>
#include "AppMacros.h"
#include "CrossApp.h"


//单例模式宏
//#define SINGLETON(_CLASS_)                  \
//public:                                     \
//inline static _CLASS_& GetInstance()    \
//{                                       \
//static _CLASS_ s_instance;              \
//return s_instance;                      \
//}                                       \
//private:                                    \
//_CLASS_();                              \
//_CLASS_(_CLASS_ const&){}               \
//_CLASS_& operator= (_CLASS_ const&){}   \
//~_CLASS_();                             \
//
////单例模式默认构造函数与析构函数（配合单例模式宏使用）
//#define SINGLETON_C_D(_CLASS_)      \
//_CLASS_::_CLASS_(){}            \
//_CLASS_::~_CLASS_(){}
#include "FSNewsManager.h"
class FSDataManager:public CAObject
{
    SINGLETON(FSDataManager)
    CC_SYNTHESIZE_PASS_BY_REF2(FSNewsManager, *m_NewsManager, NewsManager)
};

#endif /* defined(__SharpMessage__FSDataManager__) */
