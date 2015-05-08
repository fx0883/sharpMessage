#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "CrossApp.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "EGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
    CrossApp::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { CrossApp::CCSizeMake(480, 320),   "iphone" };
static Resource mediumResource =  { CrossApp::CCSizeMake(1024, 768),  "ipad"   };
static Resource largeResource  =  { CrossApp::CCSizeMake(2048, 1536), "ipadhd" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static CrossApp::CCSize designResolutionSize = CrossApp::CCSizeMake(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static CrossApp::CCSize designResolutionSize = CrossApp::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static CrossApp::CCSize designResolutionSize = CrossApp::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (CrossApp::EGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)


#define DBName "newsdb.db"



//单例模式宏
#define SINGLETON(_CLASS_)                  \
public:                                     \
inline static _CLASS_& GetInstance()    \
{                                       \
    static _CLASS_ s_instance;              \
    return s_instance;                      \
}                                       \
private:                                    \
_CLASS_();                              \
_CLASS_(_CLASS_ const&){}               \
_CLASS_& operator= (_CLASS_ const&){}   \
~_CLASS_();                             \

//单例模式默认构造函数与析构函数（配合单例模式宏使用）
#define SINGLETON_C_D(_CLASS_)      \
_CLASS_::_CLASS_(){}            \
_CLASS_::~_CLASS_(){}           \

//删除当前对象
#define DELETECLASS(anyObject)  \
if(anyObject)   \
{   \
    delete anyObject;   \
    anyObject = NULL;   \
}   \


#define CC_SYNTHESIZE_PASS_BY_REF2(varType, varName, funName)\
protected: varType varName;\
public: inline virtual varType& get##funName(void) { return varName; }\
public: virtual void set##funName(varType& var){ varName = var; }


#endif /* __APPMACROS_H__ */
