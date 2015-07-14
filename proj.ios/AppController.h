#import <UIKit/UIKit.h>
#import "Reachability.h"
@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    bool isConnect;
    
    

}
@property (nonatomic,strong) Reachability *hostReachability;
@property (nonatomic,strong) Reachability *internetReachability;
@property (nonatomic,strong) Reachability *wifiReachability;

@end

