//
//  Piece.h
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#ifndef __SushiNeko__Piece__
#define __SushiNeko__Piece__

#include "Constants.h"

class Piece : public cocos2d::Node
{
public:
    CREATE_FUNC(Piece);
    float getSpriteHeight();
    
    void setObstacleSide(Side side);
    Side getObstacleSide();
    
protected:
    Side ObstacleSide;
    
};

#endif /* defined(__SushiNeko__Piece__) */
