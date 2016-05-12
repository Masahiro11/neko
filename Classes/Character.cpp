//
//  Character.cpp
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#include "Character.h"


void Character::setSide(Side side)
{
    this->side = side;
    
    if (this->side == Side::Right)
    {
        this->setScaleX(-1.0f);
    }
    else
    {
        this->setScaleX(1.0f);
    }
}

Side Character::getSide()
{
    return this->side;
}


bool Character::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    // キャラクターは左側からスタートする
    this->side = Side::Left;
    
    // キャラクターのアニメーションのタイムラインを読み込む
    this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
    
    // キャラクターのアニメーションのタイムラインを確保し、メモリ領域が解放されないようにする
    this->timeline->retain();
    
    return true;
}


void Character::onExit()
{
    // initで呼び出したretainを解放する
    this->timeline->release();
    
    Node::onExit();
}


void Character::runChopAnimation()
{
    // キャラクターに新しいアクションをスタートさせるには、実行中のアクションがある場合はまずそれを止める。
    this->stopAllActions();
    
    // フレームごとにアップデートを取得できるようにタイムラインを実行する
    this->runAction(this->timeline);
    
    // 叩き落しのアニメーションを再生するようタイムラインに伝え、falseのloopを設定する
    this->timeline->play("chop", false);
}

