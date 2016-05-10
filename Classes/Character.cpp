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


