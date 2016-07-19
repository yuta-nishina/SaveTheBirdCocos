//
//  Player.cpp
//  SaveTheBird
//
//  Created by giginet on 2014/7/9.
//
//

#include "Player.h"
#include "Stage.h"
#include "NativeLauncher.h"

USING_NS_CC;

/// アニメーションが何フレームあるか
const int FRAME_COUNT = 2;

bool Player::init()
{
    
    
    // キャラデータ取得
    int setchara = NativeLauncher::getCurrentCharacterNo();
    auto playerImg = StringUtils::format("chara0%i_player.png", setchara);
    
    if (!Sprite::initWithFile(playerImg)) {
        return false;
    }
    
    // 1フレームの画像サイズを取得する
    auto frameSize = Size(this->getContentSize().width / FRAME_COUNT,
                          this->getContentSize().height);
    // テクスチャの大きさを1フレーム分にする
    this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    
    Vector<SpriteFrame *> frames;
    for (int i = 0; i < FRAME_COUNT; ++i) {
        // 1コマずつアニメーションを作成する
        auto frame = SpriteFrame::create(playerImg, Rect(frameSize.width * i,
                                                            0,
                                                            frameSize.width,
                                                            frameSize.height));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames);
    // アニメの動く時間
    animation->setDelayPerUnit(0.3);
    this->runAction(RepeatForever::create(Animate::create(animation)));
    
    auto material = PhysicsMaterial();
    auto body = PhysicsBody::createCircle((this->getContentSize().width / 2) - 5);
    // 摩擦
    material.friction = 0.2;
    
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    
    // カテゴリをPLAYERにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::PLAYER));
    // 壁とのみ衝突する
    body->setCollisionBitmask(static_cast<int>(Stage::TileType::WALL));
    // 全ての剛体と接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    this->setPhysicsBody(body);
    
    this->scheduleUpdate();
    
    return true;
}

void Player::update(float dt)
{
    // プレイヤーの推進力を0にする
    this->getPhysicsBody()->setVelocity(Vec2(0,0));
    
    // プレイヤーに推進力を与える
    this->getPhysicsBody()->applyImpulse(Vec2(0,5000));
}