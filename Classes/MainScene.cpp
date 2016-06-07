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

using namespace CocosDenshion;

USING_NS_CC;

/// ステージ数
const int STAGE_COUNT = 13;
const Vec2 GRAVITY_ACCELERATION = Vec2(0, 0);
const Vec2 IMPULSE_ACCELERATION = Vec2(0, 0);
const int MAX_ITEM_COUNT = 2;

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
    world->setSpeed(2.0f);
    
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
    
//    this->scheduleUpdate();
    
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    
    auto parallaxNode = ParallaxNode::create();
    this->addChild(parallaxNode);
    
    auto stage = Stage::createWithLevel(level);
    this->setStage(stage);
    _stage->setScale(1.2f);
    
    auto mapWidth = stage->getTiledMap()->getContentSize().width;
    auto backgroundWidth = background->getContentSize().width;
    
    //480.000000,320.000000,600.000000
    parallaxNode->addChild(background, 0, Vec2((backgroundWidth - winSize.width) / mapWidth, 0), Vec2::ZERO);
    //parallaxNode->addChild(background, 0, Vec2(0.5, 0.5), Vec2::ZERO);
    this->setParallaxNode(parallaxNode);
    
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
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("food").c_str());
            //}
        }
        
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    this->addChild(stage);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event) {
        // タッチされたとき
        return true;
    };
    touchListener->onTouchMoved = [this](Touch* touch, Event* event){
        // タッチ位置が動いた時
        
        // プレイヤーを取得
        auto player = _stage->getPlayer();
        // プレイヤーの位置を絶対座標で取得
        Vec2 playerLocation = player->convertToWorldSpace(Point(player->getScaleX()/2, player->getScaleY()/2));
        // 前回のタッチ位置
        Vec2 previousLocation = touch->getPreviousLocation();
        // 現在のタッチ位置
        Vec2 currentLocation = touch->getLocation();
        
        // プレイヤーとの角度の差分を計算する
        float previousAngle = getAngle(playerLocation, previousLocation);
        float currentAngle = getAngle(playerLocation, currentLocation);
        float diffAngle = previousAngle - currentAngle;

        // プレイヤーの現在の角度を取得する
        float playerRotation = player->getRotation();
        
        // プレイヤーの新しい角度をセットする
        float newRotation = playerRotation + diffAngle;
        player->setRotation(newRotation);
        
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


    // ステージ番号の表示
    auto stageBackground = Sprite::create("stage_ui.png");
    stageBackground->setPosition(Vec2(55,
                                      winSize.height - 26));
    this->addChild(stageBackground);
    
    auto stageLabel = Label::createWithCharMap("numbers.png", 32, 36, '0');
    stageLabel->setString(StringUtils::format("%d", _stage->getLevel()));
    stageLabel->setPosition(Vec2(55, winSize.height - 16));
    this->addChild(stageLabel);
    
    // 制限時間を表示
    auto secondLabel = Label::createWithCharMap("numbers.png", 32, 36, '0');
    secondLabel->setPosition(Vec2(160, winSize.height - 16));
    this->addChild(secondLabel);
    this->setSecondLabel(secondLabel);
    
    //メニューを作成
    auto mItem = MenuItemImage::create("menu_btn.png","menu_btn.png",[this](Ref*sender){
        // menu
        onMenu();
    });
    mItem->setContentSize(Size(141, 64));
    auto _menu = Menu::create(mItem,NULL);
    //_menu->setPosition(Point::ZERO);
    _menu->setPosition(Point(winSize.width/2 + 140, winSize.height - 40));
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
    
    
    // 取得したアイテムの数を表示
    for (int i = 0; i < MAX_ITEM_COUNT; ++i) {
        auto sprite = Sprite::create("item.png");
        sprite->setPosition(Vec2(winSize.width - 70 + i * 20, winSize.height - 20));
        this->addChild(sprite);
        _items.pushBack(sprite);
        sprite->setColor(Color3B::BLACK);
    }
    
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
    // GO演出
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto text = Label::createWithSystemFont("Go!", "logotypejp_mp_m_1_1", 48);
    text->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(text);
    text->setScale(0);
    text->runAction(Sequence::create(ScaleTo::create(0.1, 1.0),
                                   DelayTime::create(0.8),
                                   ScaleTo::create(0.1, 0),
                                   NULL));

    
    //auto go = Sprite::create("go.png");
    //go->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    //this->addChild(go);
    //go->setScale(0);
    //go->runAction(Sequence::create(ScaleTo::create(0.1, 1.0),
    //                               DelayTime::create(0.5),
    //                               ScaleTo::create(0.1, 0),
    //                               NULL));
    
    
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
    
    /*
    // 画面外からはみ出したとき、ゲームオーバー判定
    auto winSize = Director::getInstance()->getWinSize();
    auto position = _stage->getPlayer()->getPosition();
    const auto margin = _stage->getPlayer()->getContentSize().height / 2.0;
    if (position.y < -margin || position.y >= (winSize.height - 160) + margin) {
        if (this->getState() == State::MAIN) {
            //this->onGameOver();
            this->onClear();
        }
    }
     */
    
    
    // コインの枚数の更新
    //this->getCoinLabel()->setString(StringUtils::toString(_coin));
    
    // 画面がタップされている間
    //if (this->getIsPress()) {
        // プレイヤーに上方向の推進力を与える
        //_stage->getPlayer()->getPhysicsBody()->applyImpulse(IMPULSE_ACCELERATION);
    //}
    
    if (_state == State::MAIN) {
        _second += dt;
        this->updateSecond();
    }
}

void MainScene::onGameOver()
{
    this->setState(State::GAMEOVER);
    _stage->getPlayer()->removeFromParent();
    
    auto winSize = Director::getInstance()->getWinSize();
    int currentStage = _stage->getLevel();
    
    //auto gameover = Sprite::create("gameover.png");
    //gameover->setPosition(Vec2(winSize.width / 2.0, winSize.height / 1.5));
    //this->addChild(gameover);

    auto text = Label::createWithSystemFont("Game Over", "logotypejp_mp_m_1_1", 48);
    text->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(text);
    
    auto menuItem = MenuItemImage::create("replay.png", "replay_pressed.png", [currentStage](Ref *sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        auto scene = MainScene::createSceneWithStage(currentStage);
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    auto returnTitle = MenuItemImage::create("return.png", "return_pressed.png", [](Ref *sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
        auto scene = TitleScene::createScene();
        auto transition = TransitionFade::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    auto menu = Menu::create(menuItem, returnTitle, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    this->addChild(menu);
    menu->setPosition(winSize.width / 2.0, winSize.height / 3);
    
    // パーティクル表示
    auto explosition = ParticleExplosion::create();
    explosition->setPosition(_stage->getPlayer()->getPosition());
    _stage->addChild(explosition);
    
    
    // BGM 再生
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("explode").c_str());
}

void MainScene::onClear()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    this->setState(State::CLEAR);
    this->getEventDispatcher()->removeAllEventListeners();
    
    
    _stage->getPlayer()->getPhysicsBody()->setEnabled(false);
    
    auto txtClear = Sprite::create("clear.png");
       txtClear->setPosition(Vec2(winSize.width / 2.0, winSize.height -125));
    txtClear->setScale(0.9);
    this->addChild(txtClear);

    
    auto clear = Sprite::create("chara01_front_stand.png");
    clear->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(clear);
    _stage->getPlayer()->removeFromParent();
    
    
    int nextStage = (_stage->getLevel() + 1) % STAGE_COUNT;
    
    auto menuItem = MenuItemImage::create("next.png", "next_pressed.png", [nextStage](Ref *sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
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
    menuBack->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(menuBack,2,101);
    
    auto text = Label::createWithSystemFont("メニュー", "logotypejp_mp_m_1_1", 26);
    text->setColor(Color3B(60, 60, 60));
    text->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0 + 105));
    menuBack->addChild(text, 2);
    
    //int nextStage = (_stage->getLevel() + 1) % STAGE_COUNT;
    
    //閉じる
    auto closeMenu = MenuItemImage::create("close.png", "close.png", [this](Ref *sender) {
        // 閉じるアクション
        this->removeChildByTag(101);
        _stage->getPlayer()->getPhysicsBody()->setEnabled(true);
        this->setState(State::MAIN);
        return;
    });
    
    auto returnTitle = MenuItemImage::create("return.png", "return_pressed.png", [](Ref *sender) {
     CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(AudioUtils::getFileName("decide").c_str());
     auto scene = TitleScene::createScene();
     auto transition = TransitionFade::create(1.0, scene);
     Director::getInstance()->replaceScene(transition);
     });
    auto menu = Menu::create(returnTitle, closeMenu, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    menu->setPosition(winSize.width / 2.0, winSize.height / 3.0 - 50);
    menuBack->addChild(menu);
    
}


void MainScene::onGetItem(cocos2d::Node * item)
{
    _itemCount += 1;
    for (int i = 0; i < _itemCount; ++i) {
        _items.at(i)->setColor(Color3B::WHITE);
    }
}

void MainScene::updateSecond()
{
    int sec = floor(_second);
    int milisec = floor((_second - sec) * 100);
    auto string = StringUtils::format("%03d:%02d", sec, milisec);
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
