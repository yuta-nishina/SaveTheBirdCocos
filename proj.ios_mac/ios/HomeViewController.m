//
//  HomeViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/16.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "HomeViewController.h"


@interface HomeViewController ()

@end

@implementation HomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    // タブバーの初期化処理
    [self initTabBar];
}

-(void)viewDidAppear:(BOOL)animated{
    // スタートボタン（キャラクターの画像）の初期化
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    IOSAppDelegate *delegate = (IOSAppDelegate *)[[UIApplication sharedApplication] delegate];
    Charactor *charactor = [delegate getCharactor:[defaults integerForKey:@"current_charactor_no"] - 1]; // -1する
    [_startButton setBackgroundImage:[UIImage imageNamed:charactor.image_stand] forState:UIControlStateNormal];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)initTabBar{
    UITabBar *tabBar = self.tabBarController.tabBar;
    
    // 1つ目のタブ（ホーム）
    UITabBarItem *item1 = [tabBar.items objectAtIndex:0];
    
    UIImage *image1 = [UIImage imageNamed:@"ic_menu_home_66@2x.png"];
    UIImage *selectedImage1 = [UIImage imageNamed:@"ic_menu_home_on_66@2x.png"];
    
    item1.image = [image1 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    item1.selectedImage = [selectedImage1 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    
    // 2つ目のタブ（キャラ選択）
    UITabBarItem *item2 = [tabBar.items objectAtIndex:1];
    
    UIImage *image2 = [UIImage imageNamed:@"ic_menu_chara_66@2x.png"];
    UIImage *selectedImage2 = [UIImage imageNamed:@"ic_menu_chara_on_66@2x.png"];
    
    item2.image = [image2 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    item2.selectedImage = [selectedImage2 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    
    // 3つ目のタブ（設定）
    UITabBarItem *item3 = [tabBar.items objectAtIndex:2];
    
    UIImage *image3 = [UIImage imageNamed:@"ic_menu_setting_66@2x.png"];
    UIImage *selectedImage3 = [UIImage imageNamed:@"ic_menu_setting_on_66@2x.png"];
    
    item3.image = [image3 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    item3.selectedImage = [selectedImage3 imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
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

- (void)dealloc {
    [_startButton release];
    [_fukidashi release];
    [super dealloc];
}
@end
