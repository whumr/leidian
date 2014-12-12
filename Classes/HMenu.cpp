//
//  HMenu.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HMenu.h"
#include "HWorld.h"
#include "HAbout.h"
#include "HScore.h"
#include "HSettings.h"
#include "SimpleAudioEngine.h"
#include "Level.h"

using namespace CocosDenshion;
using namespace cocos2d;
extern int sceneLevel;

Scene* HMenu::scene()
{
    Scene *scene = Scene::create();
    HMenu *layer = HMenu::create();
    scene->addChild(layer);
    return scene;
}

bool HMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    sceneLevel = 9999;
    
    //播放菜单场景的音乐
    SimpleAudioEngine::getInstance()->playBackgroundMusic("menuMusic.mp3",true);
    
    //获取整个设备的尺寸
    auto size = Director::getInstance()->getWinSize();
    
    //创建Menu背景
    Sprite* sp1 = Sprite::create("img_bg_logo.jpg");
    sp1->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp1);
    
    Sprite* sp2 = Sprite::create("LOGO.png");
    sp2->setPosition(Vec2(size.width*0.5,size.height*2/3+15));
    addChild(sp2);
    
    //创建Menu菜单项-play
    MenuItemImage * itemPlay= MenuItemImage::create("play_nor.png", "play_pre.png",this,menu_selector(HMenu::playIsPressed));
    
    //创建Menu菜单项-score
    MenuItemImage * itemScore= MenuItemImage::create("score_nor.png", "score_pre.png",this,menu_selector(HMenu::scoreIsPressed));
    itemScore->setPosition(Vec2(0,-itemScore->getContentSize().height-20));
    
    //创建Menu菜单项-about
    MenuItemImage * itemAbout= MenuItemImage::create("about_nor.png", "about_pre.png",this,menu_selector(HMenu::aboutIsPressed));
    itemAbout->setPosition(Vec2(0,-itemScore->getContentSize().height*2-40));
    
    //创建Menu菜单项-settings
    MenuItemImage * itemSettings = MenuItemImage::create("setting.png", "setting.png",this,menu_selector(HMenu::SetttingsIsPressed));
    itemSettings->setPosition(Vec2(0,-itemScore->getContentSize().height*3-40));
    
    //利用3个菜单项创建Menu菜单
    Menu * menu = Menu::create(itemPlay,itemScore,itemAbout,itemSettings,NULL);
    menu->setPosition(Vec2(size.width/2, size.height/3-10));
    addChild(menu);
    menu->alignItemsVerticallyWithPadding(10);
    
    return true;
}

//菜单项Play被按下时的回调函数
void HMenu::playIsPressed(Ref* psend){
    //切换到"关卡"场景
    Director::getInstance()->replaceScene(TransitionFade::create(1, Level::scene()));

}

//菜单项High Scores被按下时的回调函数
void HMenu::scoreIsPressed(Ref* psend){
    //切换到“高分”场景
    Director::getInstance()->replaceScene(TransitionJumpZoom::create(1, HScore::scene()));
}

//菜单项About被按下时的回调函数
void HMenu::aboutIsPressed(Ref* psend){
    //切换到“关于”场景
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HAbout::scene()));
}

//菜单项Settings被按下时的回调函数
void HMenu::SetttingsIsPressed(Ref* psend){
    //切换到“Settings”场景
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HSettings::scene()));
}
