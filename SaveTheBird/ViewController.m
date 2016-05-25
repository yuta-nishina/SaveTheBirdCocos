//
//  ViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/13.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // SEの再生準備  --------------------------------------------------------------------------------
    NSError *error = nil;
    // 再生する audio ファイルのパスを取得
    NSString *path = [[NSBundle mainBundle] pathForResource:@"se_sample" ofType:@"mp3"];
    // パスから、再生するURLを作成する
    NSURL *url = [[NSURL alloc]initFileURLWithPath:path];
    // audio を再生するプレイヤーを作成する
    self.sePlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
    // 繰り返しの回数を指定
    self.sePlayer.numberOfLoops = 0; // 繰り返しなし(0)
    // エラーが起きたとき
    if (error != nil) {
        NSLog(@"Error %@", [error localizedDescription]);
    }
    // 自分自身をデリゲートに設定
    [self.sePlayer setDelegate:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)seSwitchDidChanged:(UISwitch *)sender {
    // スイッチがONになったらSEを鳴らす
    if (sender.on) {
        [_sePlayer play];
    }
    
}


@end
