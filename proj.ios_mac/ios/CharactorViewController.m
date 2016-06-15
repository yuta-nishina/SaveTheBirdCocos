//
//  CharactorViewController.m
//  SaveTheBird
//
//  Created by ATGS_Mac on 2016/05/17.
//  Copyright © 2016年 ATGS. All rights reserved.
//

#import "CharactorViewController.h"


@interface CharactorViewController ()

@end

@implementation CharactorViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    _scrollView.delegate = self;
    
    // キャラクターの配列を取得
    IOSAppDelegate *delegate = (IOSAppDelegate *)[[UIApplication sharedApplication] delegate];
    NSMutableArray * charactors = [delegate getCharactors];
    NSInteger pageCount = charactors.count; // ページ数（キャラクターの数）
    
    // ユーザが現在選択しているキャラクターの番号を取得する
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger currentNo = [defaults integerForKey:@"current_charactor_no"] - 1; // 後の処理のため取得した番号マイナス１する
    
    // スクロールの範囲を設定
    CGRect scrollViewFrame = self.scrollView.bounds;
    CGFloat width = scrollViewFrame.size.width;
    CGFloat height = scrollViewFrame.size.height;
    [_scrollView setContentSize:CGSizeMake((pageCount * width), height)];
    
    // スクロールビューに画像を貼り付ける
    NSInteger count = 0;
    for (Charactor * charactor in charactors) {
        UIImage * image = [UIImage imageNamed:charactor.image_stand];
        CGRect rect = CGRectMake(width * count, 0, width, height);
        UIImageView * imageView = [[UIImageView alloc] initWithFrame:rect];
        
        imageView.clipsToBounds = YES;
        imageView.image = image;
        imageView.contentMode = UIViewContentModeScaleAspectFit;
        
        [_scrollView addSubview:imageView];
        
        count++;
    }
    
    // ユーザが選択しているキャラクターの位置にスクロールする
    if(currentNo > 0){
        // キャラクターを変更
        CGRect frame = _scrollView.frame;
        frame.origin.x = frame.size.width * currentNo;
        [_scrollView scrollRectToVisible:frame animated:NO];
    }else{
        // キャラクター情報のみ変更
        [self changeCharactor:currentNo];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


// スクロールビューがスワイプされたとき
- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    CGFloat pageWidth = scrollView.frame.size.width;
    if ((NSInteger)fmod(scrollView.contentOffset.x, pageWidth) == 0) {
        
        // 現在のページ数を取得
        NSInteger currentPage = scrollView.contentOffset.x / pageWidth;
        
        // ページコントロールに現在のページを設定
        _pageControl.currentPage = currentPage;
        
        // キャラクターを変更
        [self changeCharactor:currentPage];
        
    }
}

// ページコントロールがタップされたとき
- (IBAction)pageControl_Tapped:(id)sender {
    
    // 現在のページ数を取得
    NSInteger currentPage = _pageControl.currentPage;
    
    // スクロールビューを現在のページに合わせてスクロール
    CGRect frame = _scrollView.frame;
    frame.origin.x = frame.size.width * currentPage;
    [_scrollView scrollRectToVisible:frame animated:YES];
    
    // キャラクターを変更
    [self changeCharactor:currentPage];
}

- (void)changeCharactor:(NSInteger)charaNo {
    // 選択されたキャラクターのオブジェクトを取得
    IOSAppDelegate *delegate = (IOSAppDelegate *)[[UIApplication sharedApplication] delegate];
    NSMutableArray * charactors = [delegate getCharactors];
    Charactor * charactor = charactors[charaNo];
    // キャラクターの名前を更新
    _imageView.image = [UIImage imageNamed:charactor.name];
    // キャラクターの説明文を更新
    _textView.text = charactor.detail;
    // 選択されたキャラクターの番号を保存
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:charactor.no forKey:@"current_charactor_no"];
    [defaults synchronize];
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
