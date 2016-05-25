//
//  GameViewController.h
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/16.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RootViewController;

@interface GameViewController : UIViewController{
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end
