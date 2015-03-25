//
//  NewPlayer.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-28.
//
//

#include "NewPlayer.h"
#include "HPlayer.h"
#include "LevelScene.h"
using namespace cocos2d;

int playerType = 1;
extern int sceneLevel;

NewPlayer* NewPlayer::createPlayer(const char* fileName){
    NewPlayer* player = new NewPlayer();
    if(player && player->initWithFile(fileName)){
        player->autorelease();
        player->playerInit();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

void NewPlayer::playerInit()
{    
    hpMax =3;//初始化血量上限为3
    strongTime=5*60;//初始化无敌时间5秒
	isDead = false;
	isStrong = false;
}

//添加积分分数
void NewPlayer::addScore(float _value){
    score+=_value;
    std::string strScore=Convert2String(score);
    Label* ttf = (Label*)LevelScene::sharedLevelScene()->getChildByTag(tag_scoreTTF);
    ttf->setString(strScore.c_str());
}

//Layer* getLevelScene(int iLevel)
//{
//    return LevelScene::sharedLevelScene();
//}

//添加杀敌数
void NewPlayer::addKillCount(float _value)
{
    killCount+=_value;
    std::string strKillCount=Convert2String(killCount);
    Label* ttf = (Label*)LevelScene::sharedLevelScene()->getChildByTag(tag_killsCountTTF);
    ttf->setString(strKillCount.c_str());
    
    {
        if(sceneLevel==1)
        {
            //存储分数
            int oldScore =atoi(UserDefault::getInstance()->getStringForKey("user_score2","-1").c_str());
            if(score>oldScore){
                UserDefault::getInstance()->setStringForKey("user_score2", Convert2String(score));
                UserDefault::getInstance()->flush();
                LevelScene::sharedLevelScene()->isGetNewRecord = true;
            }
        }else if (sceneLevel==2)
        {
            //存储分数
            int oldScore =atoi(UserDefault::getInstance()->getStringForKey("user_score3","-1").c_str());
            if(score>oldScore){
                UserDefault::getInstance()->setStringForKey("user_score3", Convert2String(score));
                UserDefault::getInstance()->flush();
                LevelScene::sharedLevelScene()->isGetNewRecord = true;
            }
        }
        
        
        //调用胜利界面
        if(killCount>=100)
            LevelScene::sharedLevelScene()->winGame();
    }
}

//主角掉血函数（默认每次掉一点血）
void NewPlayer::downHp(){
    if(isStrong){
        return;
    }
    hp-=1;
    if(hp<=0){
        this->setVisible(false);
        isDead=true;

        //调用失败界面
        LevelScene::sharedLevelScene()->lostGame();
    }else{
        //将界面的血量icon数量进行更新
        switch (hp) {
            case 1:
                LevelScene::sharedLevelScene()->removeChildByTag(tag_playerHp2, true);
                break;
                
            case 2:
                LevelScene::sharedLevelScene()->removeChildByTag(tag_playerHp3, true);
                break;
        }
        //主角无敌时间
        isStrong=true;
        strongCount=0;
        this->schedule(schedule_selector(NewPlayer::strongIng));
    }
}

//主角加血函数（默认每次加一点血）
void NewPlayer::addHp()
{
    switch(hp)
    {
        case 1:
        {
            Sprite* spHp = Sprite::create("icon_hp.png");
            spHp->setPosition(Vec2(25*2,spHp->getContentSize().height*0.5));
            spHp->setTag(tag_playerHp2);
            LevelScene::sharedLevelScene()->addChild(spHp,10);
            break;
        }
        case 2:
        {
            Sprite* spHp = Sprite::create("icon_hp.png");
            spHp->setPosition(Vec2(25*3,spHp->getContentSize().height*0.5));
            spHp->setTag(tag_playerHp3);
            LevelScene::sharedLevelScene()->addChild(spHp,10);
            break;
        }
        default:
            break;
    }
}

//处于无敌时间时的处理函数
void NewPlayer::strongIng(float dt){
    strongCount++;
    if(strongCount>=strongTime){
        this->setVisible(true);
        isStrong=false;
        this->unschedule(schedule_selector(NewPlayer::strongIng));
    }else{
        //主角处于无敌时间时的闪烁效果
        if(strongCount%2==0){
            this->setVisible(false);
        }else{
            this->setVisible(true);
        }
    }
}