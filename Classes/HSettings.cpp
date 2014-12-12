//
//  HSettings.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-18.
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
    //��ȡ�豸�ߴ�
    auto size = Director::getInstance()->getWinSize();
    
    //����
    Sprite* sp = Sprite::create("img_bg_logo.jpg");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    //�����л���ҵĲ�����ʽ
	MenuItemFont *itemTouchType = MenuItemFont::create("ҡ�˻���", CC_CALLBACK_1(HSettings::touchTypeChange, this));
    MenuItemFont *itemTouchType1 = MenuItemFont::create("��ָ����", CC_CALLBACK_1(HSettings::touchTypeChange2, this));
    
    //����һ���˵����һ��Menu
    Menu* menu =Menu::create(itemTouchType,itemTouchType1,NULL);
    menu->setPosition(Vec2(size.width*2/5, size.height/2));
    addChild(menu);
    //pMenu->alignItemsHorizontallyWithPadding(40);    //���ø�item�ĺ�����
    menu->alignItemsVerticallyWithPadding(40);       //���ø�item��������
    
    //ע��
    Label* annotation = Label::createWithSystemFont("(ҡ�˻���ģʽ����������ϰ)", "Helvetica", 15);
    annotation->setPosition(Vec2(size.width*0.5-5,size.height*0.5+10));
    annotation->setColor(Color3B(255, 0, 0));
    addChild(annotation);
    
    //��ӶԺ�ͼƬ����ʾ��ǰѡ��Ĳ���
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
    
    //���һ����ť���ڷ���Menu
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
    //�л���"�˵�"����
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1, HMenu::scene(),true));
}
