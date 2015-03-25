//
//  HScore.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HScore.h"
#include "HMenu.h"
using namespace cocos2d;

Scene* HScore::scene()
{
    Scene *scene = Scene::create();
    HScore *layer = HScore::create();
    scene->addChild(layer);
    return scene;
}

bool HScore::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //获取设置尺寸
    auto size = Director::getInstance()->getWinSize();
    
    //背景
    Sprite* sp = Sprite::create("img_bg_logo.jpg");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    for(int i = 1; i <= 3; i++)
    {
        const char* user_score = String::createWithFormat("user_score%d",i)->getCString();
        //添加一个文本(获取存储的积分)
        std::string scoreStr="";
        //获取存储的积分
        std::string score = UserDefault::getInstance()->getStringForKey(user_score,"-1").c_str();
        //判断当前是否有最高分的记录
        if(atoi(score.c_str())!=-1){
            //如有有最高分的记录
            scoreStr+=score;
        }else{
            scoreStr="0";
        }
        
        //将分数以Lable添加到layer并显示出来
        Label* ttfAbout = Label::createWithSystemFont(scoreStr.c_str(), "Helvetica", 23);
        ttfAbout->setPosition(Vec2(size.width*2/3,size.height*2/3 -40*(i+1)));
        ttfAbout->setColor(Color3B(255, 0, 0));
        addChild(ttfAbout,3);
    }
 
    //添加图片
    Sprite *crown = Sprite::create("bestScore.png");
    crown->setPosition(Vec2(size.width/2, size.height*4/5-30));
    addChild(crown);
    Sprite *record = Sprite::create("recordGirl.png");
    record->setPosition(Vec2(size.width/2, size.height*2/5));
    record->setOpacity(100);
    addChild(record,2);
    
	auto conf = Configuration::getInstance();
    //添加分数标签
    Label* score1 = Label::createWithSystemFont(conf->getValue("level.practice").asString(), "Helvetica", 24);
    score1->setPosition(Vec2(size.width/3,size.height*2/3 -40*(1+1)));
    score1->setColor(Color3B(255, 0, 0));
    addChild(score1,3);
    Label* score2 = Label::createWithSystemFont(conf->getValue("level.level1").asString(), "Helvetica", 24);
    score2->setPosition(Vec2(size.width/3,size.height*2/3 -40*(2+1)));
    score2->setColor(Color3B(255, 0, 0));
    addChild(score2,3);
    Label* score3 = Label::createWithSystemFont(conf->getValue("level.level2").asString(), "Helvetica", 24);
    score3->setPosition(Vec2(size.width/3,size.height*2/3 -40*(3+1)));
    score3->setColor(Color3B(255, 0, 0));
    addChild(score3,3);
    
    //添加一个按钮用于返回Menu
	MenuItemImage * back= MenuItemImage::create("backHomeWord.png", "backHomeWord.png",CC_CALLBACK_1(HScore::backMenu, this));
    Menu* menu =Menu::create(back,NULL);
    menu->setPosition(Vec2(size.width/2, 30));

    addChild(menu);
    
    return true;
}
void HScore::backMenu(Ref* psend){
    //切换到"菜单"场景
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HMenu::scene()));
}
