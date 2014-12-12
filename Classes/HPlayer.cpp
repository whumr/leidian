//
//  HPlayer.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HPlayer.h"
#include "HBullet.h"
#include "HWorld.h"
using namespace cocos2d;

HPlayer* HPlayer::createPlayer(const char* fileName){
    HPlayer* player = new HPlayer();
    if(player && player->initWithFile(fileName)){
        player->autorelease();
        player->playerInit(fileName);
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

void HPlayer::playerInit(const char* fileName){
    auto size = Director::getInstance()->getWinSize();
    //初始化主角位置
    this->setPosition(Vec2(size.width*0.5,this->getContentSize().height*0.5));
    //初始化主角动画
    this->createAnimate(fileName);
    
    hpMax =3;//初始化血量上限为3
    hp=3;//初始化当前血量为3
    score=0;//初始化当前积分分数
    strongTime=5*60;//初始化无敌时间5秒
    
    //初始化3个血,加入到Layer中
    for (int i =1; i<=hp; i++) {
        Sprite* spHp = Sprite::create("icon_hp.png");
        spHp->setPosition(Vec2(size.width-25*i,spHp->getContentSize().height*0.5));
        if(i==1){
            spHp->setTag(tag_playerHp1);
        }else if(i==2){
            spHp->setTag(tag_playerHp2);
        }else if(i==3){
            spHp->setTag(tag_playerHp3);
        }
        HWorld::sharedWorld()->addChild(spHp,10);
    }
    //初始化"分数"文字加入layer中
    Label* label = Label::createWithSystemFont("分数:", "Helvetica-Blod", 24);
    label->setPosition(Vec2(30,size.height-22));
    HWorld::sharedWorld()->addChild(label,10);
    
    //分数数字加入layer中
    std::string strScore=Convert2String(score);
    Label* labelScores = Label::createWithSystemFont(strScore.c_str(), "Helvetica-Blod", 24);
    labelScores->setPosition(Vec2(110,size.height-22));
    labelScores->setColor(Color3B(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelScores,10,tag_scoreTTF);
        
    //杀敌人数
    Label* labelKill = Label::createWithSystemFont("杀敌:", "Helvetica-Blod", 24);
    labelKill->setPosition(Vec2(30,size.height-52));
    HWorld::sharedWorld()->addChild(labelKill,10);
    
    //杀敌数字加入layer中
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* labelKillCount = Label::createWithSystemFont(strKillCount.c_str(), "Helvetica-Blod", 24);
    labelKillCount->setPosition(Vec2(110,size.height-52));
    labelKillCount->setColor(Color3B(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelKillCount,10,tag_killsCountTTF);
}

//添加积分分数
void HPlayer::addScore(float _value){
    score+=_value;
    std::string strScore=Convert2String(score);
    Label* ttf = (Label*)HWorld::sharedWorld()->getChildByTag(tag_scoreTTF);
    ttf->setString(strScore.c_str());
}

//添加杀敌数
void HPlayer::addKillCount(float _value)
{
    killCount+=_value;
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* ttf = (Label*)HWorld::sharedWorld()->getChildByTag(tag_killsCountTTF);
    ttf->setString(strKillCount.c_str());
    
    {
        //存储分数
		int oldScore =atoi(UserDefault::getInstance()->getStringForKey("user_score1","-1").c_str());
        if(score>oldScore){
            UserDefault::getInstance()->setStringForKey("user_score1", Convert2String(score));
            UserDefault::getInstance()->flush();
            HWorld::sharedWorld()->isGetNewRecord = true;
        }
        
        //调用胜利界面
        if(killCount>=100)
            HWorld::sharedWorld()->winGame();
    }
}

//主角掉血函数（默认每次掉一点血）
void HPlayer::downHp(){
    if(isStrong){
        return;
    }
    hp-=1;
    
    if(hp<=0){
        this->setVisible(false);
        isDead=true;
        
        //调用失败界面
        HWorld::sharedWorld()->lostGame();
    }else{
        //将界面的血量icon数量进行更新
        switch (hp) {
            case 1:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp2, true);
                break;
                
            case 2:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp3, true);
                break;
        }
        //主角无敌时间
        isStrong=true;
        strongCount=0;
        this->schedule(schedule_selector(HPlayer::strongIng));
    }
}

//处于无敌时间时的处理函数
void HPlayer::strongIng(float dt){
    strongCount++;
    if(strongCount>=strongTime){
        this->setVisible(true);
        isStrong=false;
        this->unschedule(schedule_selector(HPlayer::strongIng));
    }else{
        //主角处于无敌时间时的闪烁效果
        if(strongCount%2==0){
            this->setVisible(false);
        }else{
            this->setVisible(true);
        }
    }
}

//让主角有动态的效果
void HPlayer::createAnimate(const char* fileName)
{
    Animation* animation = Animation::create();
    Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(fileName);
    int eachWidth=this->getContentSize().width/5;//每个切片的宽
    for (int i =0; i<5; i++)
    {
        animation->addSpriteFrameWithTexture(texture,Rect(i*eachWidth, 0, eachWidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.2f);//必须设置否则不会动态播放
    animation->setRestoreOriginalFrame(true);//是否回到第一帧
    animation->setLoops(-1);//重复次数 （-1:无限循环）
    Animate * animate = Animate::create(animation);
    this->runAction(animate);
}
