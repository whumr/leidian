//
//  HScore.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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
    
    //��ȡ���óߴ�
    auto size = Director::getInstance()->getWinSize();
    
    //����
    Sprite* sp = Sprite::create("img_bg_logo.jpg");
    sp->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(sp);
    
    for(int i = 1; i <= 3; i++)
    {
        const char* user_score = String::createWithFormat("user_score%d",i)->getCString();
        //���һ���ı�(��ȡ�洢�Ļ���)
        std::string scoreStr="";
        //��ȡ�洢�Ļ���
        std::string score = UserDefault::getInstance()->getStringForKey(user_score,"-1").c_str();
        //�жϵ�ǰ�Ƿ�����߷ֵļ�¼
        if(atoi(score.c_str())!=-1){
            //��������߷ֵļ�¼
            scoreStr+=score;
        }else{
            scoreStr="0";
        }
        
        //��������Lable��ӵ�layer����ʾ����
        Label* ttfAbout = Label::createWithSystemFont(scoreStr.c_str(), "Helvetica", 23);
        ttfAbout->setPosition(Vec2(size.width*2/3,size.height*2/3 -40*(i+1)));
        ttfAbout->setColor(Color3B(255, 0, 0));
        addChild(ttfAbout,3);
    }
 
    //���ͼƬ
    Sprite *crown = Sprite::create("bestScore.png");
    crown->setPosition(Vec2(size.width/2, size.height*4/5-30));
    addChild(crown);
    Sprite *record = Sprite::create("recordGirl.png");
    record->setPosition(Vec2(size.width/2, size.height*2/5));
    record->setOpacity(100);
    addChild(record,2);
    
	auto conf = Configuration::getInstance();
    //��ӷ�����ǩ
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
    
    //���һ����ť���ڷ���Menu
	MenuItemImage * back= MenuItemImage::create("backHomeWord.png", "backHomeWord.png",CC_CALLBACK_1(HScore::backMenu, this));
    Menu* menu =Menu::create(back,NULL);
    menu->setPosition(Vec2(size.width/2, 30));

    addChild(menu);
    
    return true;
}
void HScore::backMenu(Ref* psend){
    //�л���"�˵�"����
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HMenu::scene()));
}
