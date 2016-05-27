//
//  CharactorViewController.h
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/17.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IOSAppDelegate.h"
#import "Charactor.h"

@interface CharactorViewController : UIViewController<UIScrollViewDelegate>

@property (strong, nonatomic) IBOutlet UIImageView *imageView;

@property (strong, nonatomic) IBOutlet UIScrollView *scrollView;

@property (strong, nonatomic) IBOutlet UIPageControl *pageControl;

@property (strong, nonatomic) IBOutlet UITextView *textView;

@property (strong, nonatomic) NSMutableArray * charactors;

-(NSMutableArray *) getCharactors;

@end
