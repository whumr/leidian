//
//  HPlayer.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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
    //��ʼ������λ��
    this->setPosition(Vec2(size.width*0.5,this->getContentSize().height*0.5));
    //��ʼ�����Ƕ���
    this->createAnimate(fileName);
    
    hpMax =3;//��ʼ��Ѫ������Ϊ3
    hp=3;//��ʼ����ǰѪ��Ϊ3
    score=0;//��ʼ����ǰ���ַ���
    strongTime=5*60;//��ʼ���޵�ʱ��5��
    
    //��ʼ��3��Ѫ,���뵽Layer��
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
    //��ʼ��"����"���ּ���layer��
    Label* label = Label::createWithSystemFont("����:", "Helvetica-Blod", 24);
    label->setPosition(Vec2(30,size.height-22));
    HWorld::sharedWorld()->addChild(label,10);
    
    //�������ּ���layer��
    std::string strScore=Convert2String(score);
    Label* labelScores = Label::createWithSystemFont(strScore.c_str(), "Helvetica-Blod", 24);
    labelScores->setPosition(Vec2(110,size.height-22));
    labelScores->setColor(Color3B(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelScores,10,tag_scoreTTF);
        
    //ɱ������
    Label* labelKill = Label::createWithSystemFont("ɱ��:", "Helvetica-Blod", 24);
    labelKill->setPosition(Vec2(30,size.height-52));
    HWorld::sharedWorld()->addChild(labelKill,10);
    
    //ɱ�����ּ���layer��
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* labelKillCount = Label::createWithSystemFont(strKillCount.c_str(), "Helvetica-Blod", 24);
    labelKillCount->setPosition(Vec2(110,size.height-52));
    labelKillCount->setColor(Color3B(255, 255, 0));
    HWorld::sharedWorld()->addChild(labelKillCount,10,tag_killsCountTTF);
}

//��ӻ��ַ���
void HPlayer::addScore(float _value){
    score+=_value;
    std::string strScore=Convert2String(score);
    Label* ttf = (Label*)HWorld::sharedWorld()->getChildByTag(tag_scoreTTF);
    ttf->setString(strScore.c_str());
}

//���ɱ����
void HPlayer::addKillCount(float _value)
{
    killCount+=_value;
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* ttf = (Label*)HWorld::sharedWorld()->getChildByTag(tag_killsCountTTF);
    ttf->setString(strKillCount.c_str());
    
    {
        //�洢����
		int oldScore =atoi(UserDefault::getInstance()->getStringForKey("user_score1","-1").c_str());
        if(score>oldScore){
            UserDefault::getInstance()->setStringForKey("user_score1", Convert2String(score));
            UserDefault::getInstance()->flush();
            HWorld::sharedWorld()->isGetNewRecord = true;
        }
        
        //����ʤ������
        if(killCount>=100)
            HWorld::sharedWorld()->winGame();
    }
}

//���ǵ�Ѫ������Ĭ��ÿ�ε�һ��Ѫ��
void HPlayer::downHp(){
    if(isStrong){
        return;
    }
    hp-=1;
    
    if(hp<=0){
        this->setVisible(false);
        isDead=true;
        
        //����ʧ�ܽ���
        HWorld::sharedWorld()->lostGame();
    }else{
        //�������Ѫ��icon�������и���
        switch (hp) {
            case 1:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp2, true);
                break;
                
            case 2:
                HWorld::sharedWorld()->removeChildByTag(tag_playerHp3, true);
                break;
        }
        //�����޵�ʱ��
        isStrong=true;
        strongCount=0;
        this->schedule(schedule_selector(HPlayer::strongIng));
    }
}

//�����޵�ʱ��ʱ�Ĵ�����
void HPlayer::strongIng(float dt){
    strongCount++;
    if(strongCount>=strongTime){
        this->setVisible(true);
        isStrong=false;
        this->unschedule(schedule_selector(HPlayer::strongIng));
    }else{
        //���Ǵ����޵�ʱ��ʱ����˸Ч��
        if(strongCount%2==0){
            this->setVisible(false);
        }else{
            this->setVisible(true);
        }
    }
}

//�������ж�̬��Ч��
void HPlayer::createAnimate(const char* fileName)
{
    Animation* animation = Animation::create();
    Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(fileName);
    int eachWidth=this->getContentSize().width/5;//ÿ����Ƭ�Ŀ�
    for (int i =0; i<5; i++)
    {
        animation->addSpriteFrameWithTexture(texture,Rect(i*eachWidth, 0, eachWidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.2f);//�������÷��򲻻ᶯ̬����
    animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
    animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
    Animate * animate = Animate::create(animation);
    this->runAction(animate);
}
