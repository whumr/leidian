//
//  HMenu.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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
    
    //���Ų˵�����������
    SimpleAudioEngine::getInstance()->playBackgroundMusic("menuMusic.mp3",true);
    
    //��ȡ�����豸�ĳߴ�
    auto size = Director::getInstance()->getWinSize();
    
    //����Menu����
    Sprite* sp1 = Sprite::create("img_bg_logo.jpg");
    sp1->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp1);
    
    Sprite* sp2 = Sprite::create("LOGO.png");
    sp2->setPosition(Vec2(size.width*0.5,size.height*2/3+15));
    addChild(sp2);
    
    //����Menu�˵���-play
    MenuItemImage * itemPlay= MenuItemImage::create("play_nor.png", "play_pre.png",this,menu_selector(HMenu::playIsPressed));
    
    //����Menu�˵���-score
    MenuItemImage * itemScore= MenuItemImage::create("score_nor.png", "score_pre.png",this,menu_selector(HMenu::scoreIsPressed));
    itemScore->setPosition(Vec2(0,-itemScore->getContentSize().height-20));
    
    //����Menu�˵���-about
    MenuItemImage * itemAbout= MenuItemImage::create("about_nor.png", "about_pre.png",this,menu_selector(HMenu::aboutIsPressed));
    itemAbout->setPosition(Vec2(0,-itemScore->getContentSize().height*2-40));
    
    //����Menu�˵���-settings
    MenuItemImage * itemSettings = MenuItemImage::create("setting.png", "setting.png",this,menu_selector(HMenu::SetttingsIsPressed));
    itemSettings->setPosition(Vec2(0,-itemScore->getContentSize().height*3-40));
    
    //����3���˵����Menu�˵�
    Menu * menu = Menu::create(itemPlay,itemScore,itemAbout,itemSettings,NULL);
    menu->setPosition(Vec2(size.width/2, size.height/3-10));
    addChild(menu);
    menu->alignItemsVerticallyWithPadding(10);
    
    return true;
}

//�˵���Play������ʱ�Ļص�����
void HMenu::playIsPressed(Ref* psend){
    //�л���"�ؿ�"����
    Director::getInstance()->replaceScene(TransitionFade::create(1, Level::scene()));

}

//�˵���High Scores������ʱ�Ļص�����
void HMenu::scoreIsPressed(Ref* psend){
    //�л������߷֡�����
    Director::getInstance()->replaceScene(TransitionJumpZoom::create(1, HScore::scene()));
}

//�˵���About������ʱ�Ļص�����
void HMenu::aboutIsPressed(Ref* psend){
    //�л��������ڡ�����
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HAbout::scene()));
}

//�˵���Settings������ʱ�Ļص�����
void HMenu::SetttingsIsPressed(Ref* psend){
    //�л�����Settings������
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HSettings::scene()));
}
