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

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    
    //TODO キャラクターの情報をCoreDataから取得して辞書の配列を作成
    _charactors = self.getCharactors;
    
    //TODO ユーザが現在選択しているキャラクターの番号を取得する
    NSInteger currentNo = 0; //TODO 後の処理のため取得した番号マイナス１する
    
    _scrollView.delegate = self;
    
    NSInteger pageCount = 3; // ページ数
    
    CGRect scrollViewFrame = self.scrollView.bounds;
    CGFloat width = scrollViewFrame.size.width;
    CGFloat height = scrollViewFrame.size.height;
    
    // スクロールの範囲を設定
    [_scrollView setContentSize:CGSizeMake((pageCount * width), height)];
    
    // ユーザが選択しているキャラクターの位置にスクロールする
    CGRect frame = _scrollView.frame;
    frame.origin.x = frame.size.width * currentNo;
    [_scrollView scrollRectToVisible:frame animated:YES];
    
    // スクロールビューに画像を貼り付ける
    NSInteger count = 0;
    for (Charactor * charactor in _charactors) {
        UIImage * image = [UIImage imageNamed:charactor.image_stand];
        CGRect rect = CGRectMake(width * count, 0, width, height);
        UIImageView * imageView = [[UIImageView alloc] initWithFrame:rect];
        
        imageView.clipsToBounds = YES;
        imageView.image = image;
        imageView.contentMode = UIViewContentModeScaleAspectFit;
        
        [_scrollView addSubview:imageView];
        
        count++;
    }
    
    Charactor * charactor = [self getCharactor:currentNo];
    // ユーザが選択しているキャラクターの名前を表示する
    _imageView.image = [UIImage imageNamed:charactor.name];
    
    // ユーザが選択しているキャラクターの説明文を表示する
    _textView.text = charactor.detail;
    
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
        
        
        _charactors = self.getCharactors;
        Charactor * charactor = [self getCharactor:currentPage];
//        charactor = _charactors[currentPage];
//        charactor = [self getCharactor:currentPage];
        // キャラクターの名前を更新
        _imageView.image = [UIImage imageNamed:charactor.name];
        
        // キャラクターの説明文を更新
        _textView.text = charactor.detail;
        
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
    
    _charactors = self.getCharactors;
    Charactor * charactor = [self getCharactor:currentPage];
    //        charactor = _charactors[currentPage];
    //        charactor = [self getCharactor:currentPage];
    // キャラクターの名前を更新
    _imageView.image = [UIImage imageNamed:charactor.name];
    
    // キャラクターの説明文を更新
    _textView.text = charactor.detail;
    
}

-(void)addCharactor:(Charactor *)charactor{
    [_charactors addObject:charactor];
}

-(Charactor *)getCharactor:(NSInteger)i{
    
    return _charactors[i];
}

- (NSMutableArray *)getCharactors{
    
    // データ取得用のオブジェクトであるFetchオブジェクトを作成
    NSFetchRequest * fetchRequest = [[NSFetchRequest alloc] initWithEntityName:NSStringFromClass([Charactor class])];
    
    // Sort条件を設定（No順で昇順）
    NSSortDescriptor * sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"no" ascending:YES];
    NSArray * sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor, nil];
    [fetchRequest setSortDescriptors:sortDescriptors];
    
    // manageObjectContextからデータを取得
    NSManagedObjectContext * context = [[IOSAppDelegate alloc]init].managedObjectContext;
    NSArray * results = [context executeFetchRequest:fetchRequest error:nil];
    
    _charactors = [NSMutableArray array];
    for (Charactor * charactor in results) {
        [self addCharactor:charactor];
    }
    
    return _charactors;
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
