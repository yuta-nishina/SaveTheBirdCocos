//
//  MainScene.cpp
//  SaveTheBird
//
//  Created by giginet on 2014/7/9.
//
//

#include "TitleScene.h"
#include "MainScene.h"
#include "AudioUtils.h"
#include "SimpleAudioEngine.h"
#include "NativeLauncher.h"


using namespace CocosDenshion;

USING_NS_CC;

/// ステージ数
const int STAGE_COUNT = 13;
const Vec2 GRAVITY_ACCELERATION = Vec2(0, 0);
const Vec2 IMPULSE_ACCELERATION = Vec2(0, 0);

Scene* MainScene::createSceneWithStage(int level)
{
    // 物理エンジンを有効にしたシーンを作成する
    auto scene = Scene::createWithPhysics();
    
    // 物理空間を取り出す
    auto world = scene->getPhysicsWorld();
    
    // 重力を設定する
    world->setGravity(GRAVITY_ACCELERATION);
    
    //#if COCOS2D_DEBUG > 1
    //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //#endif
    // スピードを設定する
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        // for ios
        world->setSpeed(2.0f);
    }else{
        // for android
        world->setSpeed(3.3f);
    }

    auto layer = new MainScene();
    if (layer && layer->initWithLevel(level)) {
        layer->autorelease();
    } else {
        CC_SAFE_RELEASE_NULL(layer);
    }
    
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init()
{
    return this->initWithLevel(0);
}

bool MainScene::initWithLevel(int level)
{
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    
    auto parallaxNode = ParallaxNode::create();
    this->addChild(parallaxNode);
    
    auto stage = Stage::createWithLevel(level);
    this->setStage(stage);
    
    // プラットフォームによってスケールを切り替える
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        // for ios
        _stage->setScale(1.2f);
    }else{
        // for android
        _stage->setScale(0.9f);
    }
    this->addChild(background);
    
    
    // 物体が衝突したことを検知するEventListener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](PhysicsContact& contact) {
        
        auto otherShape = contact.getShapeA()->getBody() == _stage->getPlayer()->getPhysicsBody() ? contact.getShapeB() : contact.getShapeA();
        auto body = otherShape->getBody();
        
        auto category = body->getCategoryBitmask();
        auto layer = dynamic_cast<TMXLayer *>(body->getNode()->getParent());
        
        if (category & static_cast<int>(Stage::TileType::ENEMY)) {
            // ゲームオーバー
            this->onGameOver();
        //} else if (category & (int)Stage::TileType::COIN) {
            // コイン
        //    layer->removeChild(body->getNode(), true);
        //    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("coin").c_str());
        //    _coin += 1;
        } else if (category & static_cast<int>(Stage::TileType::ITEN)) {
            // アイテム
            layer->removeChild(body->getNode(), true);
            this->onGetItem(body->getNode());
            //if (_itemCount == MAX_ITEM_COUNT) {
            //    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("complete").c_str());
            //} else {
            if (NativeLauncher::getSeFlg()) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("food").c_str());
            }
            //}
        }
        
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->addChild(stage);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        
        // 現在のタッチ位置
        //auto winSize = Director::getInstance()->getWinSize();
        /*Vec2 currentLocation = touch->getLocation();
        auto touchStart = Sprite::create("touch_outer.png");
        touchStart->setPosition(currentLocation);
        //touchStart->setPosition(Vec2(winSize.width/2, winSize.height/5));
        touchStart->setOpacity(164);
        this->addChild(touchStart,2,51);
        auto action = FadeTo::create(0.5, 256);
        touchStart->runAction(action);*/
        
        // タッチされたとき
        return true;
    };
    touchListener->onTouchMoved = [this](Touch* touch, Event* event){
        // タッチ位置が動いた時
        
        // タッチが外れたとき
        this->removeChildByTag(52);
        
        // プレイヤーを取得
        auto player = _stage->getPlayer();
        // プレイヤーの位置を絶対座標で取得
        Vec2 playerLocation = player->convertToWorldSpace(Point(player->getContentSize().width / 2,
                                                                player->getContentSize().height / 2));
        
        //auto touchStart = this->getChildByTag(51);
        //Vec2 touchLocation = touchStart->convertToWorldSpace(Point(player->getContentSize().width / 2,
        //                                                        player->getContentSize().height / 2));
        // 前回のタッチ位置
        Vec2 previousLocation = touch->getPreviousLocation();
        // 現在のタッチ位置
        Vec2 currentLocation = touch->getLocation();
        
        // プレイヤーとの角度の差分を計算する
        float previousAngle = getAngle(playerLocation, previousLocation);
        float currentAngle = getAngle(playerLocation, currentLocation);
        //float previousAngle = getAngle(touchLocation, previousLocation);
        //float currentAngle = getAngle(touchLocation, currentLocation);
        float diffAngle = previousAngle - currentAngle;

        // プレイヤーの現在の角度を取得する
        float playerRotation = player->getRotation();
        
        // プレイヤーの新しい角度をセットする
        float newRotation = playerRotation + diffAngle;
        player->setRotation(newRotation);
        
        //dotをセット
        /*if(diffAngle > 7 || diffAngle < -7){
            auto dot = Sprite::create("dot.png");
            dot->setPosition(currentLocation);
            this->addChild(dot,2,53);
            auto action = FadeTo::create(0.5, 256);
            dot->runAction(action);
        }
        
        //poiterをセット
        auto touchPointer = Sprite::create("touch_pointer.png");
        touchPointer->setPosition(currentLocation);
        touchPointer->setOpacity(64);
        this->addChild(touchPointer,2,52);
        */
        
    };
    touchListener->onTouchEnded = [this](Touch* touch, Event* event) {

        // タッチが外れたとき
        this->removeChildByTag(51);
        this->removeChildByTag(52);
        return;

    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


    // ステージ番号の表示
    auto stageBackground = Sprite::create("stage_ui.png");
    stageBackground->setPosition(Vec2(90,
                                      winSize.height - 26));
    this->addChild(stageBackground);
    
    auto stageLabel = Label::create();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        // for ios
        stageLabel = Label::createWithCharMap("numbers2.png", 32, 36, '0');
    }else{
        // for android
        stageLabel = Label::createWithCharMap("numbers2.png", 16, 18, '0');
    }

    stageLabel->setString(StringUtils::format("%d", _stage->getLevel()));
    stageLabel->setPosition(Vec2(22, winSize.height - 26));
    this->addChild(stageLabel);
    
    // 制限時間を表示
    auto secondLabel = Label::create();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        // for ios
        secondLabel = Label::createWithCharMap("numbers2.png", 32, 36, '0');
    }else{
        // for android
        secondLabel = Label::createWithCharMap("numbers2.png", 16, 18, '0');
    }

    secondLabel->setPosition(Vec2(115, winSize.height - 26));
    this->addChild(secondLabel);
    this->setSecondLabel(secondLabel);
    
    //メニューを作成
    auto mItem = MenuItemImage::create("menu_btn.png","menu_btn.png",[this](Ref*sender){
        // menu
        onMenu();
    });
    mItem->setContentSize(Size(141, 24));
    auto _menu = Menu::create(mItem,NULL);
    _menu->setPosition(Point(winSize.width/2 + 150, winSize.height - 30));
    this->addChild(_menu);
    
    
    // コインの枚数の表示
    //auto coin = Sprite::create("coin.png");
    //coin->setPosition(Vec2(160, winSize.height - 15));
    //this->addChild(coin);
    
    //auto label = Label::createWithCharMap("numbers.png", 16, 18, '0');
    //this->addChild(label);
    //label->setPosition(Vec2(200, winSize.height - 10));
    //label->enableShadow();
    //this->setCoinLabel(label);
    
    return true;
}

MainScene::MainScene()
: _isPress(false)
//, _coin(0)
, _itemCount(0)
, _second(0)
, _state(State::MAIN)
, _stage(nullptr)
, _parallaxNode(nullptr)
//, _coinLabel(nullptr)
, _stageLabel(nullptr)
, _secondLabel(nullptr)
{
}

MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_stage);
    CC_SAFE_RELEASE_NULL(_parallaxNode);
    //CC_SAFE_RELEASE_NULL(_coinLabel);
    CC_SAFE_RELEASE_NULL(_stageLabel);
    CC_SAFE_RELEASE_NULL(_secondLabel);
}

void MainScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    // BGM 再生
    // CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioUtils::getFileName("main").c_str(), true);
    auto winSize = Director::getInstance()->getWinSize();
    
    auto text = Label::createWithSystemFont("START!!", "logotypejp_mp_m_1_1", 48);
    text->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(text);
    text->setScale(0);
    text->runAction(Sequence::create(ScaleTo::create(0.1, 1.0),
                                   DelayTime::create(1.0),
                                   ScaleTo::create(0.1, 0),
                                   NULL));

    this->scheduleUpdate();
}

void MainScene::update(float dt)
{
    Vec2 playerPosition = _stage->getPlayer()->getPosition();
    TMXTiledMap *map = _stage->getTiledMap();
    
    // クリア判定
    // 右
    if (playerPosition.x >= map->getContentSize().width * map->getScale()) {
        if (_state == State::MAIN) {
            this->onClear();
        }
    }
    // 上
    if (playerPosition.y >= map->getContentSize().height * map->getScale()) {
        if (_state == State::MAIN) {
            this->onClear();
        }
    }
    // 左
    if (playerPosition.x < 0) {
        if (_state == State::MAIN) {
            this->onClear();
        }
    }
    // 下
    if (playerPosition.y < 0) {
        if (_state == State::MAIN) {
            this->onClear();
        }
    }
    
    // コインの枚数の更新
    //this->getCoinLabel()->setString(StringUtils::toString(_coin));
    
    if (_state == State::MAIN) {
        _second += dt;
        this->updateSecond();
    }
}

void MainScene::onGameOver()
{
    this->setState(State::GAMEOVER);
    _stage->getPlayer()->removeFromParent();
    //イベント停止
    //this->getEventDispatcher()->removeAllEventListeners();
    this->getEventDispatcher()->removeEventListenersForTarget(_secondLabel);
    
    auto winSize = Director::getInstance()->getWinSize();
    int currentStage = _stage->getLevel();
    
    
    //スプライトを作成
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //auto sprite = Sprite::create("black.png");
    //sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    //addChild(sprite);
    
    //1秒かけてフェードアーウト
    //auto action = FadeTo::create(0.9, 256);
    //sprite->runAction(action);
    
    
    auto gameover = Sprite::create("gameover_ani.png");
    // 1フレームの画像サイズを取得する
    auto frameSize = Size(gameover->getContentSize().width,
                          gameover->getContentSize().height / 5);
    // テクスチャの大きさを1フレーム分にする
    gameover->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    
    Vector<SpriteFrame *> frames;
    for (int i = 0; i < 5; ++i) {
        // 1コマずつアニメーションを作成する
        auto frame = SpriteFrame::create("gameover_ani.png", Rect(0,
                                                                  frameSize.height * i,
                                                                    frameSize.width,
                                                                    frameSize.height));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames);
    // アニメの動く時間
    animation->setDelayPerUnit(0.2);
    gameover->runAction(Repeat::create(Animate::create(animation),1));
    gameover->setPosition(Vec2(winSize.width / 2.0, winSize.height / 1.35));
    gameover->setScale(1.4);
    
    this->addChild(gameover);
    
    auto menuItem = MenuItemImage::create("replay.png", "replay_pressed.png", [currentStage](Ref *sender) {
        if (NativeLauncher::getSeFlg()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        }
        auto scene = MainScene::createSceneWithStage(currentStage);
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    auto returnTitle = MenuItemImage::create("return.png", "return_pressed.png", [](Ref *sender) {
        if (NativeLauncher::getSeFlg()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        }
        auto scene = TitleScene::createScene();
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    auto menu = Menu::create(menuItem, returnTitle, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    this->addChild(menu);
    menu->setPosition(winSize.width / 2.0, winSize.height / 2.4);
    
    // パーティクル表示
    auto explosition = ParticleSystemQuad::create("particle_texture.plist");
    explosition->setPosition(_stage->getPlayer()->getPosition());
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        // for ios
        explosition->setScale(0.3f);
    }else{
        // for android
        explosition->setScale(0.8f);
    }
    _stage->addChild(explosition);
    
    
    // BGM 再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("explode").c_str());
}

void MainScene::onClear()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    this->setState(State::CLEAR);
    
    //イベント停止
    //this->getEventDispatcher()->removeAllEventListeners();
    this->getEventDispatcher()->removeEventListenersForTarget(_secondLabel);
    
    _stage->getPlayer()->getPhysicsBody()->setEnabled(false);
    
    //スプライトを作成
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //auto sprite = Sprite::create("white.png");
    //sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    //sprite->setOpacity(40);
    //addChild(sprite);
    
    // クリアステージ更新
    auto path = FileUtils::getInstance()->getWritablePath();
    ValueMap data = FileUtils::getInstance()->getValueMapFromFile(path + "savedata.plist");
    auto unlockStage = data["unlockStage"].asInt();
    
    if(unlockStage == _stage->getLevel()){
        auto file = path + "savedata.plist";
        ValueMap data;
        data["unlockStage"] = _stage->getLevel() + 1;
        if (FileUtils::getInstance()->writeToFile(data, file))
        {
            CCLOG("データを%sに書き出しました。", file.c_str());
        }
        else
        {
            CCLOG("Ops!");
        }
    }
    
    auto txtClear = Sprite::create("clear.png");
    txtClear->setPosition(Vec2(winSize.width / 2.0, winSize.height -125));
    txtClear->setScale(0.9);
    this->addChild(txtClear);

    int setchara = NativeLauncher::getCurrentCharacterNo();
    auto clearImg = StringUtils::format("chara0%i_front_stand.png", setchara);
    
    auto clear = Sprite::create(clearImg);
    clear->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(clear);
    _stage->getPlayer()->removeFromParent();
    //ジャンプ
    auto action = JumpBy::create(3.4f,Vec2(0.7,0.4),4,10);
    clear->runAction(action);
    
    
    int nextStage = (_stage->getLevel() + 1) % STAGE_COUNT;
    
    auto menuItem = MenuItemImage::create("next.png", "next_pressed.png", [nextStage](Ref *sender) {
        if (NativeLauncher::getSeFlg()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        }
        auto scene = MainScene::createSceneWithStage(nextStage);
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    auto menu = Menu::create(menuItem, nullptr);
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu);
    menu->setPosition(winSize.width / 2.0, winSize.height / 3.0 - 60);
    
    // BGM 再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(AudioUtils::getFileName("clear").c_str());
}


void MainScene::onMenu()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    this->setState(State::READY);
    
    _stage->getPlayer()->getPhysicsBody()->setEnabled(false);
    
    auto menuBack = Sprite::create("menu_back.png");
    menuBack->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0 + 30));
    this->addChild(menuBack,2,101);
    
    int currentStage = _stage->getLevel();
    
    //閉じる
    auto closeMenu = MenuItemImage::create("close.png", "close.png", [this](Ref *sender) {
        // 閉じるアクション
        this->removeChildByTag(101);
        _stage->getPlayer()->getPhysicsBody()->setEnabled(true);
        this->setState(State::MAIN);
        return;
    });
    
    auto menuItem = MenuItemImage::create("replay.png", "replay_pressed.png", [currentStage](Ref *sender) {
        if (NativeLauncher::getSeFlg()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        }
        auto scene = MainScene::createSceneWithStage(currentStage);
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });

    auto returnTitle = MenuItemImage::create("return.png", "return_pressed.png", [](Ref *sender) {
        if (NativeLauncher::getSeFlg()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        }
        auto scene = TitleScene::createScene();
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });

    auto returnHome = MenuItemImage::create("home.png", "home_pressed.png", [this](Ref *sender){
        //  ホーム画面に戻る（ネイティブのメソッドを呼び出す）
        NativeLauncher::returnHome();
        
        // cocosの画面を閉じる
        Director::getInstance()->end();
        
    });
    
    auto menu = Menu::create(returnTitle, menuItem, returnHome, closeMenu, nullptr);
    menu->alignItemsVerticallyWithPadding(18);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(winSize.width / 2.0 - 10, winSize.height / 2.0 - 110);
    menuBack->addChild(menu);
    
}


void MainScene::onGetItem(cocos2d::Node * item)
{
    auto winSize = Director::getInstance()->getWinSize();

    _itemCount += 1;
    // 取得したアイテムの数を表示
    for (int i = 0; i < _itemCount; ++i) {
        auto sprite = Sprite::create("item.png");
        sprite->setPosition(Vec2(winSize.width/2 + 40 + i * 20, winSize.height - 27));
        this->addChild(sprite);
        _items.pushBack(sprite);
        
    }
}

void MainScene::updateSecond()
{
    int sec = floor(_second);
    int min = sec / 60;
    int msec = sec % 60;
    
    //int milisec = floor((_second - sec) * 100);
    auto string = StringUtils::format("%02d:%02d", min, msec);
    _secondLabel->setString(string);
}

// 2点の成す角(0~360度)を返す
float MainScene::getAngle(cocos2d::Vec2 from, cocos2d::Vec2 to)
{
    float dX = to.x - from.x;
    float dY = to.y - from.y;
    
    float radian = atan2f(dY, dX);
    // ラジアンから度へ変換
    float angle = CC_RADIANS_TO_DEGREES(radian);
    
    // 0 ~ 360度に限定
    angle += 360;
    while (angle >= 360) {
        angle -= 360;
    }
    
    return angle;
}
