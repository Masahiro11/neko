#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "Piece.h"
#include "ui/CocosGUI.h"

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver
};

class Character;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    Side getSideForObstacle(Side lastSide);
    
private:
    cocos2d::Node* pieceNode;
    cocos2d::Vector<Piece*> pieces;
    
    Side lastObstacleSide;
    
    int pieceIndex;
    
    void stepTower();
    bool isGameOver();
    
    GameState gameState;
    
    void triggerGameOver();
    void resetGameState();
    void triggerPlaying();
    void triggerTitle();
    void triggerReady();
    
    cocos2d::ui::Text* scoreLabel;
    int score;
    
    void setScore(int score);
    
    float timeLeft;
    cocos2d::Sprite* lifeBG;
    cocos2d::Sprite* timeBar;
    void setTimeLeft(float timeLeft);
    void update(float dt) override;
    
    cocos2d::Vec2 flyingPiecePosition;
    void animateHitPiece(Side obstacleSide);
    
protected:
    void onEnter() override;
    Character* character;
    Piece* piece;
    void setupTouchHandling();
};

#endif // __MainScene_SCENE_H__
