//
//  GameViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/16.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "GameViewController.h"

#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

// cocos2d application instance
static AppDelegate s_sharedApplication;

@interface GameViewController ()

@end

@implementation GameViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initCocosApplication];
}

- (void)viewDidDisappear:(BOOL)animated{
    cocos2d::Director::getInstance()->end();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    
    cocos2d::Director::getInstance()->end();
}

- (void)initCocosApplication{

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    // Use RootViewController manage CCEAGLView
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;
    
    // Set RootViewController to window
    if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        // warning: addSubView doesn't work on iOS6
        [window addSubView: _viewController.view];
    }
    else{
        // use this method on ios6
        [window setRootViewController:_viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    app->run();
    
    bannerView_ = [[GADBannerView alloc]initWithAdSize:kGADAdSizeSmartBannerPortrait];
    
    bannerView_.adUnitID = @"ca-app-pub-9429655873788061/6606985634"; // 広告ユニットID
    bannerView_.rootViewController = self.viewController;
    [self.viewController.view addSubview:bannerView_];
    
    // 一番下に広告を表示
    bannerView_.center = CGPointMake(
                                     self.viewController.view.center.x,
                                     self.viewController.view.frame.size.height-bannerView_.frame.size.height/2
                                     );
    
    GADRequest *request = [GADRequest request];
    
    // テストデバイス登録
    request.testDevices = [NSArray arrayWithObjects:
                           kGADSimulatorID, // エミュレータ
                           @"6d237a60207a037431b8e22bf5d75275",
                           @"c0c09a555c442d707459ce60f6c2d254",
                           nil];
    
    [bannerView_ loadRequest:request];
    
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
