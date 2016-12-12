//
//  SettingViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/13.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "SettingViewController.h"
#import "IOSAppDelegate.h"

@interface SettingViewController ()

@end

@implementation SettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // 設定値にあわせてUIの見た目を変更
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    // BGMのスイッチ
    [_bgmSwitch setOn:[defaults boolForKey:@"bgm_flg"]];
    // SEのスイッチ
    [_seSwitch setOn:[defaults boolForKey:@"se_flg"]];
    // ボリュームのスライダー
    [_volumeSlider setValue:[defaults floatForKey:@"volume"]];
    
    // SEの再生準備
    [self initSePlayer];
}

- (void)initSePlayer{
    NSError *error = nil;
    // 再生する audio ファイルのパスを取得
    NSString *path = [[NSBundle mainBundle] pathForResource:@"se_sample" ofType:@"mp3"];
    // パスから、再生するURLを作成する
    NSURL *url = [[NSURL alloc]initFileURLWithPath:path];
    // audio を再生するプレイヤーを作成する
    self.sePlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
    // 繰り返しの回数を指定
    self.sePlayer.numberOfLoops = 0; // 繰り返しなし(0)
    // 音量の設定
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    self.sePlayer.volume = [defaults floatForKey:@"volume"];
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

// BGMのスイッチが変更された時
- (IBAction)bgmSwitchDidChanged:(UISwitch *)sender {
    // デリゲートを取得する（BGM操作のため）
    IOSAppDelegate *delegate = (IOSAppDelegate *)[[UIApplication sharedApplication] delegate];
    // ユーザーデフォルトのオブジェクトを取得する
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    
    // SEのフラグがONなら
    BOOL seFlg = [defaults boolForKey:@"se_flg"];
    if (seFlg) {
        // SEを鳴らす
        [_sePlayer play];
    }
    
    // スイッチがONになったら
    if (sender.on) {
        // BGMを鳴らす
        if (!delegate.bgmPlayer.playing) {
            [delegate.bgmPlayer play];
        }
    }
    // スイッチがOFFになったら
    else{
        // BGMを止める
        if (delegate.bgmPlayer.playing) {
            [delegate.bgmPlayer stop];
        }
    }

    // ユーザーデフォルトの値を更新
    [defaults setObject:@(sender.on) forKey:@"bgm_flg"];
    [defaults synchronize];
}

// SEのスイッチが変更された時
- (IBAction)seSwitchDidChanged:(UISwitch *)sender {
    // スイッチがONになったら
    if (sender.on) {
        // SEを鳴らす
        [_sePlayer play];
    }
    
    // ユーザーデフォルトの値を更新する
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:@(sender.on) forKey:@"se_flg"];
    [defaults synchronize];
}

// ボリュームのスライダーが操作された時
- (IBAction)volumeSliderValueChanged:(UISlider *)sender {
    
    float volume = sender.value;
    // デリゲートを取得する（BGM操作のため）
    IOSAppDelegate *delegate = (IOSAppDelegate *) [[UIApplication sharedApplication] delegate];
    // ボリュームを変更する
    delegate.bgmPlayer.volume = volume;
    _sePlayer.volume = volume;
    
    // ボリュームの値を保存する
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:@(volume) forKey:@"volume"];

}

// 公式リンクボタンが押された時
//- (IBAction)linkButtonTouched:(UIButton *)sender {
//    NSURL *url = [NSURL URLWithString:@"http://xxxxx.xxx.xxx/"];
//    [[UIApplication sharedApplication] openURL:url];
//}

- (void)dealloc {
    [_volumeSlider release];
    [_bgmSwitch release];
    [_seSwitch release];
    [super dealloc];
}
@end
