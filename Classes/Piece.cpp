//
//  Piece.cpp
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#include "Piece.h"

using namespace cocos2d;

float Piece::getSpriteHeight()
{
    // 巻き寿司のスプライトのリファレンスを取得する
    Sprite* roll = this->getChildByName<Sprite*>("roll");
    
    // 次に巻き寿司のスプライトの高さを返す
    return roll->getContentSize().height;
}

void Piece::setObstacleSide(Side side)
{
    this->ObstacleSide = side;
    
    Sprite* roll = this->getChildByName<Sprite*>("roll");
    
    Sprite* leftChopstick = roll->getChildByName<Sprite*>("leftChopstick");
    Sprite* rightChopstick = roll->getChildByName<Sprite*>("rightChopstick");
    
    
    switch (this->ObstacleSide)
    {
        case Side::None:
            leftChopstick->setVisible(false);
            rightChopstick->setVisible(false);
            break;
            
        case Side::Left:
            leftChopstick->setVisible(true);
            rightChopstick->setVisible(false);
            break;
            
        case Side::Right:
            rightChopstick->setVisible(true);
            leftChopstick->setVisible(false);
            break;
    }
}

Side Piece::getObstacleSide()
{
    return this->ObstacleSide;
}