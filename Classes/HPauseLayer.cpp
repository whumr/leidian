//
//  HPauseLayer.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-18.
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
    
    // 开启触控
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

// 触摸被吞掉了，这个回调不会调用
void HPauseLayer::doResume(Ref *pSender)
{
    log("resume!");
}

//void HPauseLayer::registerWithTouchDispatcher()
//{
//    // NDK编译，需加上头 #include <limits>
//    // 优先级数字设为最小，那么具有最高优先级，最后参数设为true，则触摸会被这里吞掉，下面的层不会接收到触摸事件
//   // Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, std::numeric_limits<int>::min(), true);
//    Layer::registerWithTouchDispatcher();
//}

bool HPauseLayer::TouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // 因为回调调不到了，所以resume写在了这里
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
        //停止游戏
        Director::getInstance()->pause();
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        SimpleAudioEngine::getInstance()->stopAllEffects();
        
        this->unscheduleAllSelectors();
        //继续游戏
        Director::getInstance()->resume();
        //切换到"菜单"场景
        Director::getInstance()->replaceScene(HMenu::scene());
        sceneLevel = 9999;
    }
    
    return true;
}






