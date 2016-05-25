//
//  HomeViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/16.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "HomeViewController.h"
#import "GameViewController.h"

@interface HomeViewController ()

@end

@implementation HomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


// スタートボタン（鳥の画像）を押した時の処理
- (IBAction)startButtonTouched:(id)sender {
    
//    // ゲーム画面に遷移する（別のStoryboardを開く）
//    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"GameStoryboard" bundle:[NSBundle mainBundle]];
//    UIViewController *initialViewController = [storyboard instantiateInitialViewController];
//    [self presentViewController:initialViewController animated:YES completion:nil];
    
    // ゲーム画面に遷移する（Storyboardを使わない）
    GameViewController *gameVC = [[GameViewController alloc] init];
    [self presentViewController: gameVC animated:YES completion: nil];
    
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
