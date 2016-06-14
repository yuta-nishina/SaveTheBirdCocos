//
//  TitleScene.cpp
//  SaveTheBird
//
//  Created by giginet on 2014/8/1.
//
//

#include "TitleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "AudioUtils.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto background = Sprite::create("title.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    Vector<MenuItem*> menuItems;
    
    for (int i = 1; i < 13; i++) {
        auto stageMenu = MenuItemImage::create("btn_stage_off.png", "btn_stage.png", [this,i](Ref *sender){
            this->toStage(i);
        });
        auto label = Label::createWithSystemFont(StringUtils::format("%d",i), "logotypejp_mp_m_1_1", 18);
        label->setPosition(Vec2(30, 30));
        label->setColor(Color3B::BLACK);
        stageMenu->addChild(label);
        
        menuItems.pushBack(stageMenu);
    }
    

    auto menu = Menu::createWithArray(menuItems);
    
    menu->alignItemsHorizontallyWithPadding(50);
    menu->alignItemsVerticallyWithPadding(50);
    
    menu->alignItemsInColumns(3, 3, 3, 3, nullptr);
    menu->setPosition(winSize.width / 2.0, winSize.height * 0.6);
    background->addChild(menu);
    
    
    auto returnHome = MenuItemImage::create("home.png", "home_pressed.png", [this](Ref *sender){
//        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:[NSBundle mainBundle]];
//        UIViewController *initialViewController = [storyboard instantiateInitialViewController];
//
//        UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
//        [controller presentViewController:initialViewController animated:YES completion:nil];
//        Director::getInstance()->end();
    });
    
    auto returnMenu = Menu::createWithItem(returnHome);
    returnMenu->setPosition(winSize.width / 2.0, winSize.height / 5.0);
    
    background->addChild(returnMenu);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
    // BGMの再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioUtils::getFileName("title").c_str(), true);
}

void TitleScene::toStage(int stageNum){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("start").c_str());
    this->getEventDispatcher()->removeAllEventListeners();
    
    this->runAction(Sequence::create(DelayTime::create(1.0),
                                     CallFunc::create([stageNum] {
        auto main = MainScene::createSceneWithStage(stageNum);
        auto transition = TransitionCrossFade::create(0.5, main);
        
        Director::getInstance()->replaceScene(transition);
    }), NULL));
}
