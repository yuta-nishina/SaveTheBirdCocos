//
//  ViewController.h
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/13.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface ViewController : UIViewController<AVAudioPlayerDelegate>

@property(nonatomic) AVAudioPlayer *sePlayer;

@end

