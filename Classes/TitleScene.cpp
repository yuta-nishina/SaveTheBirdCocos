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
#include "NativeLauncher.h"

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
    
    
    
    // データ取得
    auto path = FileUtils::getInstance()->getWritablePath();
    auto unlockStage = 0;
    try {
        ValueMap data = FileUtils::getInstance()->getValueMapFromFile(path + "savedata.plist");
        
        unlockStage = data["unlockStage"].asInt();
    }
    catch (const std::exception& e) {
        
        auto file = path + "savedata.plist";
        ValueMap data;
        data["unlockStage"] = 0;
        if (FileUtils::getInstance()->writeToFile(data, file))
        {
            CCLOG("データを%sに書き出しました。", file.c_str());
        }
        else
        {
            CCLOG("Ops!");
        }

    }
    
    CCLOG("%i", unlockStage);
    
    
    auto winSize = Director::getInstance()->getWinSize();
    auto background = Sprite::create("title.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);

    if(unlockStage == 0){
        auto background = Sprite::create("first.png");
        background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0  - 20));
        
        this->addChild(background);
        
        auto startBtn = MenuItemImage::create("start.png", "start_pressed.png", [this](Ref *sender){
            this->toStage(0);
        });
        Vector<MenuItem*> menuItems;
        menuItems.pushBack(startBtn);
        auto menu = Menu::createWithArray(menuItems);
        menu->setPosition(winSize.width / 2.0, winSize.height / 5.0 );
        this->addChild(menu);
        
        return true;
    }

    Vector<MenuItem*> menuItems;
    auto stageMenu = new MenuItemImage();
    
    for (int i = 1; i < 13; i++) {
        auto label = Label::createWithSystemFont(StringUtils::format("%d",i), "logotypejp_mp_m_1_1", 18);
        label->setPosition(Vec2(30, 30));
        label->setColor(Color3B::BLACK);
        
        if(i <= unlockStage){
             stageMenu = MenuItemImage::create("btn_stage_off.png", "btn_stage.png", [this,i](Ref *sender){
            this->toStage(i);
            });
            
        }else{
             stageMenu = MenuItemImage::create("btn_stage_off.png", "btn_stage_off.png", [this,i](Ref *sender){});
            stageMenu->setOpacity(88);
        }
        stageMenu->addChild(label);
        menuItems.pushBack(stageMenu);
    }
    

    auto menu = Menu::createWithArray(menuItems);
    
    menu->alignItemsHorizontallyWithPadding(50);
    menu->alignItemsVerticallyWithPadding(50);
    
    menu->alignItemsInColumns(3, 3, 3, 3, nullptr);
    menu->setPosition(winSize.width / 2.0, winSize.height * 0.55 );
    this->addChild(menu);
    
    
    auto returnHome = MenuItemImage::create("home.png", "home_pressed.png", [this](Ref *sender){
        
        //  ホーム画面に戻る（ネイティブのメソッドを呼び出す）
        NativeLauncher::returnHome();
        
        // cocosの画面を閉じる
        Director::getInstance()->end();
        
    });
    
    auto returnMenu = Menu::createWithItem(returnHome);
    returnMenu->setPosition(winSize.width / 2.0, winSize.height * 0.18);
    
    this->addChild(returnMenu);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish()
{
    // BGMの再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioUtils::getFileName("title").c_str(), true);
}

void TitleScene::toStage(int stageNum){
    if (NativeLauncher::getSeFlg()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("start").c_str());
    }
    this->getEventDispatcher()->removeAllEventListeners();
    
    this->runAction(Sequence::create(DelayTime::create(1.0),
                                     CallFunc::create([stageNum] {
        auto main = MainScene::createSceneWithStage(stageNum);
        auto transition = TransitionCrossFade::create(0.5, main);
        
        Director::getInstance()->replaceScene(transition);
    }), NULL));
}
