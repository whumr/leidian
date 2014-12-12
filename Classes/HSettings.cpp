//
//  HSettings.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-18.
//
//

#include "HSettings.h"
#include "HMenu.h"
#include "HWorld.h"
#include "AppDelegate.h"
using namespace cocos2d;

extern bool touchType;

Scene* HSettings::scene()
{
    Scene *scene = Scene::create();
    HSettings *layer = HSettings::create();
    scene->addChild(layer);
    return scene;
}

bool HSettings::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    //获取设备尺寸
    auto size = Director::getInstance()->getWinSize();
    
    //背景
    Sprite* sp = Sprite::create("img_bg_logo.jpg");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    //用于切换玩家的操作方式
	MenuItemFont *itemTouchType = MenuItemFont::create("摇杆怀旧", CC_CALLBACK_1(HSettings::touchTypeChange, this));
    MenuItemFont *itemTouchType1 = MenuItemFont::create("手指触摸", CC_CALLBACK_1(HSettings::touchTypeChange2, this));
    
    //利用一个菜单项创建一个Menu
    Menu* menu =Menu::create(itemTouchType,itemTouchType1,NULL);
    menu->setPosition(Vec2(size.width*2/5, size.height/2));
    addChild(menu);
    //pMenu->alignItemsHorizontallyWithPadding(40);    //设置各item的横向间隔
    menu->alignItemsVerticallyWithPadding(40);       //设置各item的竖向间隔
    
    //注释
    Label* annotation = Label::createWithSystemFont("(摇杆怀旧模式仅适用于练习)", "Helvetica", 15);
    annotation->setPosition(Vec2(size.width*0.5-5,size.height*0.5+10));
    annotation->setColor(Color3B(255, 0, 0));
    addChild(annotation);
    
    //添加对号图片，显示当前选择的操作
    if(touchType)
    {
        this->removeChildByTag(1, true);
        Sprite *select = Sprite::create("selected.png");
        select->setPosition(Vec2(size.width*4/5, size.height/2-35));
        addChild(select,1,1);
    }else
    {
        this->removeChildByTag(1, true);
        Sprite *select = Sprite::create("selected.png");
        select->setPosition(Vec2(size.width*4/5, size.height/2+38));
        addChild(select,1,1);
    }
    
    //添加一个按钮用于返回Menu
	MenuItemImage * back= MenuItemImage::create("backHomeWord.png", "backHomeWord.png",CC_CALLBACK_1(HSettings::backMenu, this));
    Menu* menu1 =Menu::create(back,NULL);
    menu1->setPosition(Vec2(size.width/2, 30));
    addChild(menu1);
    
    return true;
}

void HSettings::touchTypeChange(Ref* psend)
{
    touchType = false;
    this->removeChildByTag(1, true);
    auto size = Director::getInstance()->getWinSize();
    Sprite *select = Sprite::create("selected.png");
    select->setPosition(Vec2(size.width*4/5, size.height/2+38));
    addChild(select,1,1);
}

void HSettings::touchTypeChange2(Ref* psend)
{
    touchType = true;
    this->removeChildByTag(1, true);
    auto size = Director::getInstance()->getWinSize();
    Sprite *select = Sprite::create("selected.png");
    select->setPosition(Vec2(size.width*4/5, size.height/2-35));
    addChild(select,1,1);
}

void HSettings::backMenu(Ref* psend){
    //切换到"菜单"场景
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1, HMenu::scene(),true));
}
