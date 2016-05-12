//
//  Character.h
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#ifndef __SushiNeko__Character__
#define __SushiNeko__Character__

#include "cocos2d.h"
#include "Constants.h"
#include "cocostudio/cocoStudio.h"

class Character : public cocos2d::Node
{
public:
    CREATE_FUNC(Character);
    void setSide(Side side);
    Side getSide();
    
    bool init() override;
    void onExit() override;
    void runChopAnimation();
    
protected:
    Side side;
    cocostudio::timeline::ActionTimeline* timeline;
    
};


#endif /* defined(__SushiNeko__Character__) */
