//
//  LevelScene.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-29.
//
//

#include "LevelScene.h"
#include "HMap.h"
#include "HMenu.h"
#include "SimpleAudioEngine.h"
#include "HPauseLayer.h"
#include "AppDelegate.h"
#include "NewBullet.h"
#include "Gems.h"
#include "NewEnemy.h"
#include "UniqueSkill.h"

using namespace CocosDenshion;
using namespace cocos2d;

static LevelScene * sh;
extern int sceneLevel;
extern int playerType;
extern int skill1Count;
extern int skill2Count;
extern int skill3Count;

LevelScene * LevelScene::sharedLevelScene(){
    if(sh){
        return sh;
    }
    return NULL;
}

Scene* LevelScene::scene()
{
    Scene *scene = Scene::create();
    LevelScene *layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    sh=this;
    
    playerType = 1;
    skill1Count = 0;
    skill2Count = 0;
    skill3Count = 0;
    allTimeCount = 0;
    BulletDelayCount = 0;
    
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy.plist");
    enemyBatchNode = SpriteBatchNode::create("enemy.png");
    this->addChild(enemyBatchNode,100);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerBullet.plist");
    bulletBatchNode = SpriteBatchNode::create("playerBullet.png");
    this->addChild(bulletBatchNode,100);
    
    switch(sceneLevel)
    {
        case 1:
        {
            creatEnemyInterval = 500;//500����
            passCreatEnemy = false;
            
            //������Ϸ�е�����
            SimpleAudioEngine::getInstance()->playBackgroundMusic("gameMusic.mp3",true);
            
            //��ͼ
            HMap * map  = HMap::createMap("img_bg_level_2.jpg");
            addChild(map);
            
            //����
            auto size = Director::getInstance()->getWinSize();
            NewPlayer * player=NewPlayer::createPlayer("plane1.png");
            player->setPosition(Vec2(size.width*0.5,player->getContentSize().height*0.5));
            addChild(player,1,tag_player);
            
            //�����������
            this->addPlaneProperty();
            
            bulletType1 = "level1_bullet1.png";
            bulletType2 = "level1_bullet2.png";
            
            break;
        }
        case 2:
        {
            creatEnemyInterval = 450;
            passCreatEnemy = true;
            
            //������Ϸ�е�����
            SimpleAudioEngine::getInstance()->playBackgroundMusic("gameMusic.mp3",true);
            
            //��ͼ
            HMap * map  = HMap::createMap("img_bg_level_3.jpg");
            addChild(map);
            
            //����
            auto size = Director::getInstance()->getWinSize();
            NewPlayer * player=NewPlayer::createPlayer("plane11.png");
            player->setPosition(Vec2(size.width*0.5,player->getContentSize().height*0.5));
            addChild(player,1,tag_player);
            
            //�����������
            this->addPlaneProperty();
            
            bulletType1 = "level2_bullet1.png";
            bulletType2 = "level2_bullet2.png";

            break;
        }
        default:
            break;
    }
    
    //�����ӵ��߼�
    this->schedule(schedule_selector(LevelScene::autoCreateBullet));
    
    ////��ʼ����������
    //arrayEnemy= CCArray::create();
    //CC_SAFE_RETAIN(arrayEnemy);
    
    //��ӵ���
    this->schedule(schedule_selector(LevelScene::autoCreateEnemy));
    
    //��ӱ�ʯ
    this->schedule(schedule_selector(LevelScene::autoCreateGems),15);
    
//    this->setTouchEnabled(true);
    
    MenuItemImage *pause = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(LevelScene::doPause, this));
    pause->setAnchorPoint(Vec2(1, 1));
    pause->setPosition(Vec2(Director::getInstance()->getWinSize().width-10, Director::getInstance()->getWinSize().height-10));
    Menu *menu = Menu::create(pause, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    addChild(menu, 1, 10);
    menu->setPosition(Vec2(0, 0));
    
    this->schedule(schedule_selector(LevelScene::resetPlayer));

    return true;
}

//��ͣ��Ϸ
void LevelScene::doPause(Ref* psend)
{
    Director::getInstance()->pause();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    HPauseLayer *pauseLayer = HPauseLayer::create();
    addChild(pauseLayer,9999,9999);
}

////���ڵ�������ȼ�����
//void LevelScene::registerWithTouchDispatcher()
//{
//    Director *pDirector = Director::getInstance();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

bool LevelScene::TouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}

void LevelScene::TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    //���ǻ�ȡ��Ҫ�ɻ���Ϊ�����������
    Node* node = getChildByTag(tag_player);
    if (!node) {
        return;
    }
    //��ȡ�����켣���룬���ɷɻ���������
    Point diff = pTouch->getDelta();
    Point currentPos = node->getPosition();
    Point targetPos = currentPos + diff;
    //Ϊ����Ҫ�ɻ�ʼ������Ļ��Χ�ڣ����ϵ�����Ļ��Ե�ļ��
    auto winSize = Director::getInstance()->getWinSize();
    auto nodeSize = node->getContentSize();
    if(targetPos.x < nodeSize.width/2)
    {
        targetPos.x = nodeSize.width/2;
    }
    else if(targetPos.x > winSize.width-nodeSize.width/2)
    {
        targetPos.x = winSize.width-nodeSize.width/2;
    }
    if(targetPos.y < nodeSize.height/2)
    {
        targetPos.y = nodeSize.height/2;
    }
    else if(targetPos.y > winSize.height-nodeSize.height/2)
    {
        targetPos.y = winSize.height-nodeSize.height/2;
    }
    //Ŀ�����
    node->setPosition( targetPos );
}

//��ӷɻ�����
void LevelScene::addPlaneProperty()
{
    
    NewPlayer *player = this->getPlayer();
    player->hp=3;//��ʼ����ǰѪ��Ϊ3
    player->score=0;//��ʼ����ǰ���ַ���
    int killCount = player->killCount;
    //��ʼ��hp��Ѫ,���뵽Layer��
    for (int i =1; i<=player->hp; i++) {
        Sprite* spHp = Sprite::create("icon_hp.png");
        spHp->setPosition(Vec2(25*i,spHp->getContentSize().height*0.5));
        if(i==1){
            spHp->setTag(tag_playerHp1);
        }else if(i==2){
            spHp->setTag(tag_playerHp2);
        }else if(i==3){
            spHp->setTag(tag_playerHp3);
        }
        addChild(spHp,10);
    }
    //��ʼ��"����"���ּ���layer��
    Label* label = Label::createWithSystemFont("����:", "Helvetica-Blod", 24);
    label->setPosition(Vec2(30,Director::getInstance()->getWinSize().height-22));
    addChild(label,10);
    
    //�������ּ���layer��
    std::string strScore=Convert2String(player->score);
    Label* labelScores = Label::createWithSystemFont(strScore.c_str(), "Helvetica-Blod", 24);
    labelScores->setPosition(Vec2(110,Director::getInstance()->getWinSize().height-22));
    labelScores->setColor(Color3B(255, 255, 0));
    addChild(labelScores,10,tag_scoreTTF);
    
    //ɱ������
    Label* labelKill = Label::createWithSystemFont("ɱ��:", "Helvetica-Blod", 24);
    labelKill->setPosition(Vec2(30,Director::getInstance()->getWinSize().height-52));
    addChild(labelKill,10);
    
    //ɱ�����ּ���layer��
    std::string strKillCount=Convert2String(killCount);
    Label* labelKillCount = Label::createWithSystemFont(strKillCount.c_str(), "Helvetica-Blod", 24);
    labelKillCount->setPosition(Vec2(110,Director::getInstance()->getWinSize().height-52));
    labelKillCount->setColor(Color3B(255, 255, 0));
    addChild(labelKillCount,10,tag_killsCountTTF);
}

//�Զ���������ӵ�
void LevelScene::autoCreateBullet(float f)
{
    BulletDelayCount++;//�ӵ��ӳ�ʱ�����
    switch(playerType)
    {
        case 1://�ɻ�1�ӵ�
        {
            
			if(BulletDelayCount % 30 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() + Vec2(18,15),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() - Vec2(18,-15),1));
                //�ӵ���Ч
                SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
            }
            break;
        }
        case 2://�ɻ�2�ӵ�
        {
			if(BulletDelayCount % 25 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() + Vec2(10,25),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() - Vec2(10,-25),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() + Vec2(24,5),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() - Vec2(24,-5),1));
                SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
            }
            break;
        }
        case 3://�ɻ�3�ӵ�
        {
			if(BulletDelayCount % 20 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() + Vec2(10,25),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() - Vec2(10,-25),1));
                SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
            }
            if(BulletDelayCount % 90 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType2,3,player->getPosition() + Vec2(24,5),2));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType2,3,player->getPosition() - Vec2(24,-5),2));
            }
            break;
        }
        case 4://�ɻ�4�ӵ�
        {
            if(BulletDelayCount % 15 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() + Vec2(10,25),1));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType1,6,player->getPosition() - Vec2(10,-25),1));
                SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
            }
            if(BulletDelayCount % 60 == 0 && !this->getArrayForEnemy().empty())
            {
                NewPlayer * player = (NewPlayer*)this->getChildByTag(tag_player);
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType2,3,player->getPosition() + Vec2(24,5),2));
                bulletBatchNode->addChild(NewBullet::createBullet(bulletType2,3,player->getPosition() - Vec2(24,-5),2));
            }
            break;
        }
            break;
    }
}

//�Զ���������
void LevelScene::autoCreateEnemy(float f)
{
    allTimeCount++;
    int killCount = this->getPlayer()->killCount;
    auto size = Director::getInstance()->getWinSize();

    if(killCount<15 && passCreatEnemy==false)
    {
        enemyType = 1;
        this->schedule(schedule_selector(LevelScene::setEnemy));
    }else
    {
        if(allTimeCount>creatEnemyInterval)
        {
            if(killCount%50==0)
            {
                creatEnemyInterval-=50;
            }
            allTimeCount = 0;
            enemyType1TimeCount = 0;
            enemyType2TimeCount = 0;
            enemyType3TimeCount = 0;
            enemyType4TimeCount = 0;
            enemyType5TimeCount = 0;
            enemyType6TimeCount = 0;
            //srand(time(NULL));
            int randomType = CCRANDOM_0_1()*600;
            log("%d",randomType);
            if(randomType<100)
            {
                enemyType = 2;
            }else if (randomType>=100 && randomType<200)
            {
                enemyType = 3;
            }else if (randomType>=200 && randomType<300)
            {
                enemyType = 4;
            }else if (randomType>=300 && randomType<400)
            {
                enemyType = 5;
            }else if (randomType>=400 && randomType<500)
            {
                enemyType = 6;
            }else if (randomType>=500 && randomType<600)
            {
                enemyType = 7;
            }
            this->schedule(schedule_selector(LevelScene::setEnemy));
        }
    }
}

void LevelScene::setEnemy(float f)
{
    auto size = Director::getInstance()->getWinSize();
    switch(enemyType)
    {
        case 1:
        {
            enemyType1TimeCount++;
            if(enemyType1TimeCount>100)
            {
                enemyType1TimeCount = 0;
                NewEnemy* enemy = NULL;
                enemy = NewEnemy::createEnemy("enemy1.png", 0,1);
				arrayEnemy.pushBack(enemy);
                enemyBatchNode->addChild(enemy,33);
            }
            break;
        }
        case 2:
        {
            enemyType2TimeCount++;
            if(enemyType2TimeCount<400)
            {
                enemyType2TimeCount++;
                if(enemyType2TimeCount%60==0)
                {
                    NewEnemy* enemy = NULL;
                    enemy = NewEnemy::createEnemy("enemy2.png", 1,0);
                    arrayEnemy.pushBack(enemy);
                    enemyBatchNode->addChild(enemy);
                }
            }
            break;
        }
        case 3:
        {
            enemyType3TimeCount++;
            if(enemyType3TimeCount<120)
            {
                if(enemyType3TimeCount%25==0)
                {
                    NewEnemy* enemy = NULL;
                    enemy = NewEnemy::createEnemy("enemy3.png", 2,3);
                    enemy->setPosition(Vec2(0, size.height+enemy->getContentSize().height));
                    arrayEnemy.pushBack(enemy);
                    enemyBatchNode->addChild(enemy);
                }
            }
            break;
        }
        case 4:
        {
            enemyType4TimeCount++;
            if(enemyType4TimeCount<120)
            {
                if(enemyType4TimeCount%25==0)
                {
                    NewEnemy* enemy = NULL;
                    enemy = NewEnemy::createEnemy("enemy4.png", 3,4);
                    enemy->setPosition(Vec2(size.width/2, size.height+enemy->getContentSize().height));
                    arrayEnemy.pushBack(enemy);
                    enemyBatchNode->addChild(enemy);
                    
                    NewEnemy* enemy1 = NULL;
                    enemy1 = NewEnemy::createEnemy("enemy4.png", 3,5);
                    enemy1->setPosition(Vec2(size.width/2, size.height+enemy1->getContentSize().height));
                    arrayEnemy.pushBack(enemy1);
                    enemyBatchNode->addChild(enemy1);
                }
            }
            break;
        }
        case 5:
        {
            enemyType5TimeCount++;
            if(enemyType5TimeCount<120)
            {
                if(enemyType5TimeCount%25==0)
                {
                    NewEnemy* enemy = NULL;
                    enemy = NewEnemy::createEnemy("enemy3.png", 2,6);
                    enemy->setPosition(Vec2(0, size.height+enemy->getContentSize().height));
                    arrayEnemy.pushBack(enemy);
                    enemyBatchNode->addChild(enemy);
                }
            }
            break;
        }
        case 6:
        {
            enemyType6TimeCount++;
            if(enemyType6TimeCount<120)
            {
                if(enemyType6TimeCount%25==0)
                {
                    NewEnemy* enemy = NULL;
                    enemy = NewEnemy::createEnemy("enemy3.png", 2,7);
                    enemy->setPosition(Vec2(size.width+enemy->getContentSize().width, size.height+enemy->getContentSize().height));
                    arrayEnemy.pushBack(enemy);
                    enemyBatchNode->addChild(enemy);
                }
            }
            break;
        }
        case 7:
        {
            if(!enemyBatchNode->getChildByTag(88))
            {
                NewEnemy* enemy = NULL;
                enemy = NewEnemy::createEnemy("enemy5.png", 4,2);
                arrayEnemy.pushBack(enemy);
                enemyBatchNode->addChild(enemy,10,88);
            }
            break;
        }
        default:
            break;
    }
}

void LevelScene::autoCreateGems(float f)
{
	CallFunc *func1 = CallFunc::create(CC_CALLBACK_0(LevelScene::putGems, this));
    CallFunc *func2 = CallFunc::create(CC_CALLBACK_0(LevelScene::removeSupplyPlane, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite *supplyPlane = Sprite::create("plane5.png");
    supplyPlane->setPosition(Vec2(0,-supplyPlane->getContentSize().height));
    this->addChild(supplyPlane,10,100);
    supplyPlane->runAction(Sequence::create(MoveTo::create(2, Vec2(size.width/2, size.height/3)),DelayTime::create(1),func1,DelayTime::create(1),MoveTo::create(2, Vec2(size.width+supplyPlane->getContentSize().width, -supplyPlane->getContentSize().width)),func2,NULL));
}

void LevelScene::putGems()
{
    auto size = Director::getInstance()->getWinSize();
    int randomGemType = CCRANDOM_0_1() *100;
    log("randomGemType:%d",randomGemType);
    if(randomGemType<20)
    {
        Gems *gem = Gems::createGem("hp.png",1);
        gem->setPosition(Vec2(size.width/2, size.height/3));
        addChild(gem,9);
    }else if (randomGemType>=20 && randomGemType<35)
    {
        Gems *gem = Gems::createGem("upLevel.png",0);
        gem->setPosition(Vec2(size.width/2, size.height/3));
        addChild(gem,9);
    }else if (randomGemType>=35 && randomGemType<55)
    {
        Gems *gem = Gems::createGem("skill1.png",2);
        gem->setPosition(Vec2(size.width/2, size.height/3));
        addChild(gem,9);
    }
    else if (randomGemType>=55 && randomGemType<75)
    {
        Gems *gem = Gems::createGem("skill2.png",3);
        gem->setPosition(Vec2(size.width/2, size.height/3));
        addChild(gem,9);
    }else if (randomGemType>=75 && randomGemType<100)
    {
        Gems *gem = Gems::createGem("skill3.png",4);
        gem->setPosition(Vec2(size.width/2, size.height/3));
        addChild(gem,9);
    }
}

void LevelScene::removeSupplyPlane()
{
    this->removeChildByTag(100, true);
}

void LevelScene::resetPlayer(float f)
{
    switch(playerType)
    {
        case 1:
        {
            this->setPlayer(1);
            break;
        }
        case 2:
        {
            this->setPlayer(2);
            break;
        }
        case 3:
        {
            this->setPlayer(3);
            break;
        }
        case 4:
        {
            this->setPlayer(4);
            break;
        }
        break;
    }
}
void LevelScene::setPlayer(int i)
{
    if(!isPlayerChange)
    {
        return;
    }
    isPlayerChange = false;
    Point currentPos = this->getPlayer()->getPosition();
    int hp = this->getPlayer()->hp;
    int score = this->getPlayer()->score;
    int killCount = this->getPlayer()->killCount;
    this->unschedule(schedule_selector(LevelScene::autoCreateBullet));
    this->removeChildByTag(tag_player, true);
    
    const char* planeName = "";
    if(sceneLevel == 1)
    {
        planeName = CCString::createWithFormat("plane%d.png",i)->getCString();
    }else if (sceneLevel ==2 )
    {
        planeName = CCString::createWithFormat("plane%d%d.png",i,i)->getCString();
    }
    
    NewPlayer * player=NewPlayer::createPlayer(planeName);
    player->hp = hp;
    player->score = score;
    player->killCount = killCount;
    player->setPosition(currentPos);
    addChild(player,1,tag_player);
    this->schedule(schedule_selector(LevelScene::autoCreateBullet));
}

void LevelScene::winGame()
{
    
}

void LevelScene::lostGame()
{
    //���ʧ�ܽ���
    auto size=Director::getInstance()->getWinSize();
    const char* pic = "";
    if(isGetNewRecord)
    {
        if(sceneLevel==1)
        {
            pic = "win2.png";
        }else
        {
            pic = "win3.png";
        }
    }else
    {
        if(sceneLevel==1)
        {
            pic = "lost2.png";
        }else
        {
            pic = "lost1.png";
        }
    }
    LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 190), size.width, size.height);
    Sprite* sp = Sprite::create(pic);
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    layer->addChild(sp);
    addChild(layer,100);
    
    //���һ����ť���ڷ���Menu
    Label* ttback =Label::createWithSystemFont("�������˵�", "Helvetica-Bold", 23);
    MenuItemLabel* menuLabel= MenuItemLabel::create(ttback, CC_CALLBACK_1(LevelScene::backMenu, this));
    menuLabel->setPosition(Vec2(0,-200));
    Menu* menu =Menu::create(menuLabel,NULL);
    addChild(menu,100);
    
    //ֹͣ��Ϸ
    Director::getInstance()->pause();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

//�˵���"�������˵�"�Ļص�����
void LevelScene::backMenu(Ref* psend)
{
    this->unscheduleAllSelectors();
    //������Ϸ
    Director::getInstance()->resume();
    //�л���"�˵�"����
    Director::getInstance()->replaceScene(HMenu::scene());
}

//��ȡ����
NewPlayer* LevelScene::getPlayer()
{
    NewPlayer* player = (NewPlayer*)LevelScene::sharedLevelScene()->getChildByTag(tag_player);
    return player;
}

//��ȡ��������
Vector<NewEnemy*> LevelScene::getArrayForEnemy()
{
    return arrayEnemy;
}

LevelScene::~LevelScene()
{
	arrayEnemy.clear();
}
