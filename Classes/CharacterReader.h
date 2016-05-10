//
//  CharacterReader.h
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#ifndef __SushiNeko__CharacterReader__
#define __SushiNeko__CharacterReader__


#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class CharacterReader : public cocostudio::NodeReader
{
public:
    static CharacterReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};


#endif /* defined(__SushiNeko__CharacterReader__) */
