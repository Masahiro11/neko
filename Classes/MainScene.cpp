#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "CharacterReader.h"
#include "PieceReader.h"

#include "Character.h"

USING_NS_CC;

using namespace cocostudio::timeline;



Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void MainScene::onEnter()
{
    Layer::onEnter();
    this->setupTouchHandling();
    triggerTitle();
    this->scheduleUpdate();
}


// on "init" you need to initialize your instance
bool MainScene::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "MainScene" splash screen"
    auto sprite = Sprite::create("MainScene.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // カスタムクラス用のReaderを登録する
    // CharacterReader::getInstance()ではなく、CharacterReader::getInstanceとすること。さもなくばクラッシュするので、注意が必要
    CSLoader* instance = CSLoader::getInstance();
    
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("PieceReader", (ObjectFactory::Instance) PieceReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    
    this->pieceNode = rootNode->getChildByName("pieceNode");
    
    this->character = rootNode->getChildByName<Character*>("character");
    this->scoreLabel = rootNode->getChildByName<cocos2d::ui::Text*>("scoreLabel");
    
    auto lifeBG = rootNode->getChildByName("lifeBG");
    this->timeBar = lifeBG->getChildByName<Sprite*>("lifeBar");
    
    
    for (int i = 0; i < 10; ++i)
    {
        Piece* piece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));
        piece->setPosition(0.0f, piece->getSpriteHeight() / 2.0f * i);
        this->pieceNode->addChild(piece);
        this->pieces.pushBack(piece);
        
        this->lastObstacleSide = this->getSideForObstacle(this->lastObstacleSide);
        piece->setObstacleSide(this->lastObstacleSide);
    }
    
    
    addChild(rootNode);
    
    this->pieceIndex = 0;
    
    
    gameState = GameState::Title;
    
    resetGameState();

    return true;
}


Side MainScene::getSideForObstacle(Side lastSide)
{
    Side side;
    
    switch (lastSide)
    {
        case Side::None:
        {
            // 0.0fから1.0fの間でランダムな数を生成する
            float random = CCRANDOM_0_1();
            
            // 直前のピースに障害物がない場合
            // 45%の確率で左側に障害物が現れる
            // 45%の確率で右側に障害物が現れる
            // 10%の確率で障害物が現れない
            if (random < 0.45f)
            {
                side = Side::Left;
                
            }
            else if (random < 0.9f)
            {
                side = Side::Right;
            }
            else
            {
                side = Side::None;
            }
        }
            break;
            
            
            // 直前のピースに障害物がある場合、
            // このピースには障害物がない
        case Side::Left:
        case Side::Right:
            side = Side::None;
            break;
    }
    
    return side;
}


void MainScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    
    {
        
        switch (this->gameState)
        {
                
            case GameState::Title:
                this->triggerReady();
                break;
                
            case GameState::Ready:
                this->triggerPlaying();
                
            case GameState::Playing:
            {
                // MainSceneの座標システムでタッチの位置を取得する
                Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
                
                // タッチが画面の右側か左側かを確認する
                // キャラクターを適切なサイドに移動させる
                if (touchLocation.x < this->getContentSize().width / 2.0f)
                {
                    this->character->setSide(Side::Left);
                }
                else
                {
                    this->character->setSide(Side::Right);
                }
                
                if (this->isGameOver())
                {
                    this->triggerGameOver();
                    return true;
                }
                
                
                this->stepTower();
                
                if (this->isGameOver())
                {
                    this->triggerGameOver();
                    return true;
                }
                
                this->score++;
                this->setScore(this->score);
                this->setTimeLeft(this->timeLeft + 0.25);

            }
                break;
                
            case GameState::GameOver:
                this->resetGameState();
                this->triggerReady();
                
                break;
        }
        
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::stepTower()
{
    // 一番下のピースのリファレンスを取得する
    Piece* currentPiece = this->pieces.at(this->pieceIndex);
    
    // 一番下のピースをタワーの一番上に移動させる
    currentPiece->setPosition(currentPiece->getPosition() + Vec2(0.0f, currentPiece->getSpriteHeight() / 2.0f * 10.0f));
    
    // そのピースが他のピースの一番上に現れるようにZオーダーを設定する
    currentPiece->setLocalZOrder(currentPiece->getLocalZOrder() + 1);
    
    // 直前のピースの障害物のサイドに基づいて障害物のサイドを設定する
    currentPiece->setObstacleSide(this->getSideForObstacle(this->lastObstacleSide));
    
    this->lastObstacleSide = currentPiece->getObstacleSide();
    
    // タワー全体が下降するようにpieceNodeを下に移動させる
    this->pieceNode->setPosition(this->pieceNode->getPosition() + Vec2(0.0f, -1.0f * currentPiece->getSpriteHeight() / 2.0f));
    
    // 一番下のピースを参照するインデックスを変える
    this->pieceIndex = (this->pieceIndex + 1) % 10;
}



bool MainScene::isGameOver()
{
    bool gameOver = false;
    
    // 一番下のピースのリファレンスを取得する
    Piece* currentPiece = this->pieces.at(this->pieceIndex);
    
    // 障害物とキャラクターが接触すると、ゲームオーバー
    if (currentPiece->getObstacleSide() == this->character->getSide())
    {
        gameOver = true;
    }
    
    return gameOver;
}


void MainScene::triggerGameOver()
{
    this->gameState = GameState::GameOver;
    this->setTimeLeft(0);
}

void MainScene::triggerTitle()
{
    this->gameState = GameState::Title;
    cocostudio::timeline::ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(titleTimeline);
    titleTimeline->play("title", false);
}


void MainScene::resetGameState()
{
    // 新規ゲーム開始時に、一番下のピースには障害物がないことを確認する
    Piece* currentPiece = this->pieces.at(this->pieceIndex);
    currentPiece->setObstacleSide(Side::None);
    this->setScore(0);
    
    this->setTimeLeft(5.0);
}

void MainScene::triggerPlaying()
{
    this->gameState = GameState::Playing;
    // 最上位のノードのリファレンスを取得
    auto scene = this->getChildByName("Scene");
    
    // 左右のTAPのスプライトのリファレンスを取得
    cocos2d::Sprite* tapLeft = scene->getChildByName<cocos2d::Sprite*>("tap_left_5");
    cocos2d::Sprite* tapRight = scene->getChildByName<cocos2d::Sprite*>("tap_right_6");
    
    // フェードアウトのアクションを2つ作成
    cocos2d::FadeOut* leftFade = cocos2d::FadeOut::create(0.35f);
    cocos2d::FadeOut* rightFade = cocos2d::FadeOut::create(0.35f);
    
    // フェードアウトのアクションを実行
    tapLeft->runAction(leftFade);
    tapRight->runAction(rightFade);
}

void MainScene::triggerReady()
{
    // 最上位のノードのリファレンスを取得
    auto scene = this->getChildByName("Scene");
    // 左右のTAPのスプライトのリファレンスを取得
    cocos2d::Sprite* tapLeft = scene->getChildByName<cocos2d::Sprite*>("tap_left_5");
    cocos2d::Sprite* tapRight = scene->getChildByName<cocos2d::Sprite*>("tap_right_6");
    
    // スプライトが表示されるようにする
    tapLeft->setOpacity(255);
    tapRight->setOpacity(255);
    
    this->gameState = GameState::Ready;
    cocostudio::timeline::ActionTimeline* readyTimeline = CSLoader::createTimeline("MainScene.csb");
    this->stopAllActions();
    this->runAction(readyTimeline);
    readyTimeline->play("ready", true);
}

void MainScene::setScore(int score)
{
    // スコアのインスタンス変数をアップデートする
    this->score = score;
    
    // スコアのラベルをアップデートする
    this->scoreLabel->setString(std::to_string(this->score));
}


void MainScene::setTimeLeft(float timeLeft)
{
    // 残り時間を0秒と10秒の間に固定する
    this->timeLeft = clampf(timeLeft, 0.0f, 10.0f);
    
    // 残り時間を正しく表示するためにUIをアップデートする
    this->timeBar->setScaleX(timeLeft / 10.0f);
}


void MainScene::update(float dt)
{
    // 新しいフレームが描画される前に必ずアップデートを呼び出す
    // dtはこのアップデート呼び出しと直前のアップデート呼び出しとの間の経過時間（秒単位）
    
    // スーパークラスのメソッドのアップデートを呼び出す
    Layer::update(dt);
    
    if (this->gameState == GameState::Playing)
    {
        // ゲームプレイ中の場合
        
        // 経過した分だけタイマーを短くする
        this->setTimeLeft(timeLeft - dt);
        
        // タイマーが0以下なら、ゲームは終了
        if (this->timeLeft <= 0.0f)
        {
            this->triggerGameOver();
        }
    }
}








