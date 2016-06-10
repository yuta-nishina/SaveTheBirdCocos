#import <UIKit/UIKit.h>

@class RootViewController;

#import <GoogleMobileAds/GoogleMobileAds.h>

@interface GameViewController : UIViewController{
    UIWindow *window;
    GADBannerView *bannerView_;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end
