//
//  HPauseLayer.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-18.
//
//

#include "HPauseLayer.h"
#include "SimpleAudioEngine.h"
#include <limits>
#include "HMenu.h"

using namespace CocosDenshion;
extern int sceneLevel;

Menu *menu;
bool HPauseLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100))) {
        return  false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    
    // ��������
    //setTouchEnabled(true);
    MenuItemImage *play = MenuItemImage::create("backGame.png", "play.png");
    play->setTag(10);
    play->setPosition(Vec2(winSize.width/2, winSize.height/2+50));
    
    MenuItemImage * back= MenuItemImage::create("backHome.png", "score_pre.png");
    back->setTag(20);
    back->setPosition(Vec2(winSize.width/2, winSize.height/2-50));
    
    menu = Menu::create(play, back, NULL);
    menu->setAnchorPoint(Vec2(0, 0));
    addChild(menu, 1, 10);
    menu->setPosition(Vec2(0, 0));
    
    return true;
}

// �������̵��ˣ�����ص��������
void HPauseLayer::doResume(Ref *pSender)
{
    log("resume!");
}

//void HPauseLayer::registerWithTouchDispatcher()
//{
//    // NDK���룬�����ͷ #include <limits>
//    // ���ȼ�������Ϊ��С����ô����������ȼ�����������Ϊtrue�������ᱻ�����̵�������Ĳ㲻����յ������¼�
//   // Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, std::numeric_limits<int>::min(), true);
//    Layer::registerWithTouchDispatcher();
//}

bool HPauseLayer::TouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // ��Ϊ�ص��������ˣ�����resumeд��������
	Rect rect =  menu->getChildByTag(10)->getBoundingBox();
    if (rect.containsPoint(touch->getLocation())) {
        //log("touch play");
        Director::getInstance()->resume();
        SimpleAudioEngine::getInstance()->resumeAllEffects();
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        removeFromParentAndCleanup(true);
    }
    
    Rect rect2 =  menu->getChildByTag(20)->getBoundingBox();
    if (rect2.containsPoint(touch->getLocation())) {
        //ֹͣ��Ϸ
        Director::getInstance()->pause();
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        SimpleAudioEngine::getInstance()->stopAllEffects();
        
        this->unscheduleAllSelectors();
        //������Ϸ
        Director::getInstance()->resume();
        //�л���"�˵�"����
        Director::getInstance()->replaceScene(HMenu::scene());
        sceneLevel = 9999;
    }
    
    return true;
}






