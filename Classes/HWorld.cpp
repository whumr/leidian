//
//  HWorld.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#include "HWorld.h"
#include "HMap.h"
#include "HBullet.h"
#include "HEnemy.h"
#include "HMenu.h"
#include "SimpleAudioEngine.h"
#include "Button.h"
#include "HPauseLayer.h"
#include "AppDelegate.h"

using namespace CocosDenshion;
using namespace cocos2d;

static HWorld * sh;
bool touchType = true;

HWorld * HWorld::sharedWorld(){
    if(sh){
        return sh;
    }
    return NULL;
}

Scene* HWorld::scene()
{
    Scene *scene = Scene::create();
    HWorld *layer = HWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HWorld::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    sh=this;
    
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("button.plist","button.png");
    
    //������Ϸ�е�����
    SimpleAudioEngine::getInstance()->playBackgroundMusic("gameMusic.mp3",true);
    
    //��ͼ
    HMap * map  = HMap::createMap("img_bg_level_1.jpg");
    addChild(map);
    
    //����
    HPlayer * player=HPlayer::createPlayer("hero.png");
    addChild(player,1,tag_player);
    
    bulletBatchNode = SpriteBatchNode::create("heroBullet.png");
    this->addChild(bulletBatchNode);

    //�����ӵ��߼����������0.4�룩
    this->schedule(schedule_selector(HWorld::autoCreateBullet),0.4f);
    //�����й��߼�
    this->schedule(schedule_selector(HWorld::autoCreateEnemy));

    if(touchType)
    {
        //this->setTouchEnabled(true);
    }else
    {
        //�����ֱ�
        Button * button = Button::createButton(player, this);
        addChild(button);
    }
    
    MenuItemImage *pause = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(HWorld::doPause, this));
    pause->setAnchorPoint(Vec2(1, 1));
    pause->setPosition(Vec2(Director::getInstance()->getWinSize().width-10, Director::getInstance()->getWinSize().height-10));
    Menu *menu = Menu::create(pause, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    addChild(menu, 1, 10);
    menu->setPosition(Vec2(0, 0));
    
    smallEnemyTime = 0;
    mediumEnemyTime = 0;
    bigEnemyTime = 0;
    smallEnemyTime2 = 0;
    mediumEnemyTime2 = 0;

	auto _listener_touch = EventListenerTouchOneByOne::create();
	_listener_touch->onTouchBegan = CC_CALLBACK_2(HWorld::TouchBegan, this);
	_listener_touch->onTouchMoved = CC_CALLBACK_2(HWorld::TouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

    return true;
}

void HWorld::doPause(Ref* psend)
{
    Director::getInstance()->pause();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
    HPauseLayer *pauseLayer = HPauseLayer::create();
    addChild(pauseLayer,9999,9999);
}

//���ڵ�������ȼ�����
//void HWorld::registerWithTouchDispatcher()
//{
//    Director *pDirector = Director::getInstance();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

bool HWorld::TouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}

void HWorld::TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
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

//�Զ������йֶ���
void HWorld::autoCreateEnemy(float f)
{
    smallEnemyTime++;
    mediumEnemyTime++;
    bigEnemyTime++;
    smallEnemyTime2++;
    mediumEnemyTime2++;
    if(smallEnemyTime > 80)
    {
        HEnemy* enemy = NULL;
        enemy = HEnemy::createEnemy("enemy_bug.png", 0,0);
		arrayEnemy.pushBack(enemy);
        addChild(enemy);
        smallEnemyTime = 0;
    }
    if(mediumEnemyTime > 100)
    {
        HEnemy* enemy = NULL;
        enemy = HEnemy::createEnemy("enemy_duck.png", 1,0);
        arrayEnemy.pushBack(enemy);
        addChild(enemy);
        mediumEnemyTime = 0;
    }
    if(bigEnemyTime > 500)
    {
        HEnemy* enemy = NULL;
        enemy = HEnemy::createEnemy("enemy_pig.png", 2,0);
        arrayEnemy.pushBack(enemy);
        addChild(enemy);
        bigEnemyTime = 0;
    }
    if(smallEnemyTime2 >200)
    {
        HEnemy* enemy = NULL;
        enemy = HEnemy::createEnemy("enemy_bug.png", 0,2);
        arrayEnemy.pushBack(enemy);
        addChild(enemy);
        smallEnemyTime2 = 0;
    }
    if(mediumEnemyTime2 >300)
    {
        HEnemy* enemy = NULL;
        enemy = HEnemy::createEnemy("enemy_duck.png", 0,1);
        arrayEnemy.pushBack(enemy);
        addChild(enemy);
        mediumEnemyTime2 = 0;
    }
}

//�Զ�����ӵ�
void HWorld::autoCreateBullet(float f)
{    
	if(this->getArrayForEnemy().size() != 0)
    {
        //�����ӵ�
        HPlayer * player = (HPlayer*)this->getChildByTag(tag_player);
        bulletBatchNode->addChild(HBullet::createBullet("heroBullet.png",3.5f,player->getPosition() + Vec2(0,player->getContentSize().height*0.5)));
        
        //�ӵ���Ч
        SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
    }    
}

//��Ϸʤ��
void HWorld::winGame()
{
    
    //���ʤ������
    auto size=Director::getInstance()->getWinSize();
    LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 190), size.width, size.height);
    Sprite* sp = Sprite::create("win1.png");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    layer->addChild(sp);
    addChild(layer,100);
    
    //���һ����ť���ڷ���Menu
    Label* ttback =Label::createWithSystemFont("�������˵�", "Helvetica-Bold", 23);
    MenuItemLabel* menuLabel= MenuItemLabel::create(ttback, CC_CALLBACK_1(HWorld::backMenu, this));
    menuLabel->setPosition(Vec2(0,-200));
    Menu* menu =Menu::create(menuLabel,NULL);
    addChild(menu,100);
    
    //ֹͣ��Ϸ
    Director::getInstance()->pause();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->stopAllEffects();

}
//��Ϸʧ��
void HWorld::lostGame()
{
    //���ʧ�ܽ���
    auto size=Director::getInstance()->getWinSize();
    const char* pic = "";
    if(isGetNewRecord)
    {
        pic = "win1.png";
    }else
    {
        pic = "lost1.png";
    }
    LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 190), size.width, size.height);
    Sprite* sp = Sprite::create(pic);
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    layer->addChild(sp);
    addChild(layer,100);
    
    //���һ����ť���ڷ���Menu
    Label* ttback =Label::createWithSystemFont("�������˵�", "Helvetica-Bold", 23);
    MenuItemLabel* menuLabel= MenuItemLabel::create(ttback, CC_CALLBACK_1(HWorld::backMenu, this));
    menuLabel->setPosition(Vec2(0,-200));
    Menu* menu =Menu::create(menuLabel,NULL);
    addChild(menu,100);
    
    //ֹͣ��Ϸ
    Director::getInstance()->pause();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->stopAllEffects();

}

//�˵���"�������˵�"�Ļص�����
void HWorld::backMenu(Ref* psend)
{
    this->unscheduleAllCallbacks();
    //������Ϸ
    Director::getInstance()->resume();
    //�л���"�˵�"����
    Director::getInstance()->replaceScene(HMenu::scene());
}

//��ȡ����
HPlayer* HWorld::getPlayer()
{
    HPlayer* player = (HPlayer*)HWorld::sharedWorld()->getChildByTag(tag_player);
    return player;
}

//��ȡ��������
Vector<HEnemy*> HWorld::getArrayForEnemy()
{
    return arrayEnemy;
}

HWorld::~HWorld()
{
	arrayEnemy.clear();
}
