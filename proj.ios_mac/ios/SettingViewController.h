//
//  SettingViewController.h
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/13.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface SettingViewController : UIViewController<AVAudioPlayerDelegate>

@property (retain, nonatomic) IBOutlet UISwitch *bgmSwitch;

@property (retain, nonatomic) IBOutlet UISwitch *seSwitch;

@property (retain, nonatomic) IBOutlet UISlider *volumeSlider;

@property (retain, nonatomic) AVAudioPlayer *sePlayer;


@end

