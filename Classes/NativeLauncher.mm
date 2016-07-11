//
//  NativeLauncher.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/06/14.
//
//

#include "NativeLauncher.h"

void NativeLauncher::returnHome()
{
    // ホーム画面に戻る処理
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
    UIViewController *initialViewController = [storyboard instantiateInitialViewController];
    
    UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
    [controller presentViewController:initialViewController animated:YES completion:nil];
//    cocos2d::Director::getInstance()->end();
}

bool NativeLauncher::getSeFlg()
{
    // SEの設定を読み込む処理
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    BOOL seFlg = [defaults boolForKey:@"se_flg"];
    
    return seFlg;
}
