//
//  PieceReader.cpp
//  SushiNeko
//
//  Created by 伊藤雅博 on 5/6/16.
//
//

#include "PieceReader.h"
#include "Piece.h"

using namespace cocos2d;

static PieceReader* _instancePieceReader = nullptr;

PieceReader* PieceReader::getInstance()
{
    if (!_instancePieceReader)
    {
        _instancePieceReader = new PieceReader();
    }
    return _instancePieceReader;
}

void PieceReader::purge()
{
    CC_SAFE_DELETE(_instancePieceReader);
}

Node* PieceReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    Piece* node = Piece::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}

