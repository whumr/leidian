//
//  Level.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-28.
//
//

#include "Level.h"
#include "HMenu.h"
#include "HWorld.h"
#include "LevelScene.h"
using namespace cocos2d;

#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
#pragma execution_character_set("utf-8")
#endif

int sceneLevel;

Scene* Level::scene()
{
    Scene *scene = Scene::create();
    Level *layer = Level::create();
    scene->addChild(layer);
    return scene;
}

bool Level::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    //获取设备尺寸
    auto size = Director::getInstance()->getWinSize();
    
    //背景
    Sprite* sp = Sprite::create("img_bg_logo.jpg");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp);
    
	auto conf = Configuration::getInstance();

    //创建Level菜单项-settings
	MenuItemFont *levelOne = MenuItemFont::create(conf->getValue("level.practice").asString(), CC_CALLBACK_1(Level::Level1, this));    //可以点击的字体
    MenuItemFont *levelTwo = MenuItemFont::create(conf->getValue("level.level1").asString(), CC_CALLBACK_1(Level::Level2, this));
    MenuItemFont *levelThree = MenuItemFont::create(conf->getValue("level.level2").asString(), CC_CALLBACK_1(Level::Level3, this));
    
    //利用一个菜单项创建一个Menu
    Menu* menu =Menu::create(levelOne, levelTwo, levelThree, NULL);
    menu->setPosition(Vec2(size.width*2/3, size.height/2));
    addChild(menu);
    menu->alignItemsVerticallyWithPadding(40);       //设置各item的竖向间隔
    
    Sprite *hero = Sprite::create("heroShow.png");
    hero->setPosition(Vec2(size.width/4, size.height/2 + 70));
    addChild(hero,2,11);
    Sprite *plane1 = Sprite::create("plane1.png");
    plane1->setPosition(Vec2(size.width/4, size.height/2));
    addChild(plane1,2,22);
    Sprite *plane2 = Sprite::create("plane11.png");
    plane2->setPosition(Vec2(size.width/4, size.height/2 - 70));
    addChild(plane2,2,33);
    
    //添加一个按钮用于返回Menu
	MenuItemImage * back= MenuItemImage::create("backHomeWord.png", "backHomeWord.png", CC_CALLBACK_1(Level::backMenu, this));
    Menu* menu1 =Menu::create(back,NULL);
    menu1->setPosition(Vec2(size.width/2, 30));
    addChild(menu1);

    return true;
}

void Level::Level1(Ref* psend)
{
    auto size = Director::getInstance()->getWinSize();
    Sprite *Layer = (Sprite*)this->getChildByTag(11);
    MoveTo *move = MoveTo::create(0.5, Vec2(size.width/2, Layer->getContentSize().height));
    Layer->runAction(move);
    sceneLevel = 0;
    Director::getInstance()->replaceScene(TransitionFade::create(1, HWorld::scene()));
}

void Level::Level2(Ref* psend)
{
    auto size = Director::getInstance()->getWinSize();
    Sprite *Layer = (Sprite*)this->getChildByTag(22);
    MoveTo *move = MoveTo::create(0.5, Vec2(size.width/2, Layer->getContentSize().height));
    Layer->runAction(move);
    sceneLevel = 1;
    Director::getInstance()->replaceScene(TransitionFade::create(1, LevelScene::scene()));
}

void Level::Level3(Ref* psend)
{
    auto size = Director::getInstance()->getWinSize();
    Sprite *Layer = (Sprite*)this->getChildByTag(33);
    MoveTo *move = MoveTo::create(0.5, Vec2(size.width/2, Layer->getContentSize().height));
    Layer->runAction(move);
    sceneLevel = 2;
    Director::getInstance()->replaceScene(TransitionFade::create(1, LevelScene::scene()));
}

void Level::backMenu(Ref* psend)
{
    //切换到"菜单"场景
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1, HMenu::scene(),true));
}
