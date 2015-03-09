//
//  HAbout.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#include "HAbout.h"
#include "HMenu.h"
using namespace cocos2d;

Scene* HAbout::scene()
{
    Scene *scene = Scene::create();
    HAbout *layer = HAbout::create();
    scene->addChild(layer);
    return scene;
}

bool HAbout::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    //��ȡ�豸�ߴ�
    auto size = Director::getInstance()->getWinSize();
    
    //����
    Sprite* logo = Sprite::create("img_bg_logo.jpg");
    logo->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(logo);
    
	CallFunc *func1 = CallFunc::create(CC_CALLBACK_0(HAbout::a, this));
    CallFunc *func2 = CallFunc::create(CC_CALLBACK_0(HAbout::b, this));
    CallFunc *func3 = CallFunc::create(CC_CALLBACK_0(HAbout::c, this));
    CallFunc *func4 = CallFunc::create(CC_CALLBACK_0(HAbout::d, this));
    CallFunc *func5 = CallFunc::create(CC_CALLBACK_0(HAbout::e, this));
    CallFunc *func6 = CallFunc::create(CC_CALLBACK_0(HAbout::f, this));
    this->runAction(Sequence::create(func1,DelayTime::create(4),func2,DelayTime::create(4),func3,DelayTime::create(4),func4,DelayTime::create(4),func5,DelayTime::create(4),func6,NULL));
    
    //���һ����ť�����л���Menu�˵�����
	MenuItemImage * back= MenuItemImage::create("backHomeWord.png", "backHomeWord.png",CC_CALLBACK_1(HAbout::backMenu, this));
    
    //����һ���˵����һ��Menu
    Menu* menu =Menu::create(back,NULL);
    menu->setPosition(Vec2(size.width/2, 30));
    addChild(menu);
    return true;
}

void HAbout::a()
{
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HAbout::remove, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite* girl1 = Sprite::create("aboutGirl1.png");
    girl1->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(girl1,1,11);
    girl1->runAction(Sequence::create(DelayTime::create(2),FadeOut::create(2),func,NULL));
}

void HAbout::b()
{
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HAbout::remove, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite* b = Sprite::create("heroBigShow.png");
    b->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(b,1,11);
    b->runAction(Sequence::create(FadeIn::create(1),DelayTime::create(2),FadeOut::create(1),func,NULL));
}
void HAbout::c()
{
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HAbout::remove, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite* c = Sprite::create("plane1Show.png");
    c->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(c,1,11);
    c->runAction(Sequence::create(FadeIn::create(1),DelayTime::create(2),FadeOut::create(1),func,NULL));
}
void HAbout::d()
{
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HAbout::remove, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite* d = Sprite::create("plane2Show.png");
    d->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(d,1,11);
    d->runAction(Sequence::create(FadeIn::create(1),DelayTime::create(2),FadeOut::create(1),func,NULL));
}
void HAbout::e()
{
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HAbout::remove, this));
    auto size = Director::getInstance()->getWinSize();
    Sprite* e = Sprite::create("plane3Show.png");
    e->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(e,1,11);
    e->runAction(Sequence::create(FadeIn::create(1),DelayTime::create(2),FadeOut::create(1),func,NULL));
}
void HAbout::f()
{
    auto size = Director::getInstance()->getWinSize();
    Sprite* girl2 = Sprite::create("aboutGirl2.png");
    girl2->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(girl2,1,11);
    girl2->runAction(Sequence::create(FadeIn::create(2),DelayTime::create(2),NULL));
}
void HAbout::remove()
{
    removeChildByTag(11, true);
}

void HAbout::backMenu(Ref* psend){
    //�л���"�˵�"����
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1, HMenu::scene(),true));
}
