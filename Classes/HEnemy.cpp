//
//  HEnemy.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HEnemy.h"
#include "HWorld.h"

HEnemy* HEnemy::createEnemy(const char* fileName,int _type,int _way){
    HEnemy* enemy = new HEnemy();
    if(enemy && enemy->initWithFile(fileName)){
        enemy->autorelease();
        enemy->enemyInit(fileName,_type,_way);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

//初始化
void HEnemy::enemyInit(const char* fileName,int _type,int _way){
    way=_way;
    createAnimate(fileName, 10);
    auto size = Director::getInstance()->getWinSize();
    if(_type==0)
    {
        scoreValue=1;
        hp = 1;
    }else if(_type==1)
    {
        scoreValue=2;
        hp = 3;
    }else if (_type == 2)
    {
        scoreValue=3;
        hp = 8;
    }
    
    //X在屏幕内随机位置
    this->setPosition(Vec2(CCRANDOM_0_1()*size.width,size.height+this->getContentSize().height));

    //敌人逻辑
    this->scheduleUpdate();
}
//三种不同的移动逻辑
void HEnemy::update(float time){
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HEnemy::removeSelf, this));
    switch (way) {
        case 0:{
            this->setPosition(this->getPosition() + Vec2(0,-2.5f));
            break;
        }
        case 1:{
            //判断防止重复调用此动作，保证此逻辑只会执行一次
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction(Sequence::create(MoveTo::create(1, HWorld::sharedWorld()->getPlayer()->getPosition()),
                                                DelayTime::create(1.5),
                                                MoveTo::create(1, this->getPosition()),func,NULL));
            break;
        }
        case 2:
        {
            if(isActed){
                break;
            }
            isActed=true;
            this->runAction(Sequence::create(MoveTo::create(0.6f,  HWorld::sharedWorld()->getPlayer()->getPosition()),DelayTime::create(3),
                                                MoveTo::create(0.6f, this->getPosition()),func,NULL));
        }
        break;
    }
    //删除
    if(this->getPositionY() < -this->getContentSize().height){
        //
		HWorld::sharedWorld()->getArrayForEnemy().eraseObject(this);
        //从父类删除当前节点
        this->getParent()->removeChild(this, true);
    }

    //碰撞检测
    HPlayer * player = HWorld::sharedWorld()->getPlayer();
    if(!player->isDead){
		if(player->getBoundingBox().intersectsRect(this->getBoundingBox())){
            player->downHp();
        }
    }
}
void HEnemy::removeSelf()
{
	HWorld::sharedWorld()->getArrayForEnemy().eraseObject(this);
    //从父类删除当前节点
    this->getParent()->removeChild(this, true);
}
//让敌怪有动态的效果
void HEnemy::createAnimate(const char* fileName,int allCount){

    Animation* animation = Animation::create();
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(fileName);
    int eachWidth=this->getContentSize().width/allCount;//每个切片的宽
    for (int i =0; i<allCount; i++)
    {
        animation->addSpriteFrameWithTexture(texture,Rect(i*eachWidth, 0, eachWidth, this->getContentSize().height));
    }
    animation->setDelayPerUnit(0.03f);//必须设置否则不会动态播放
    animation->setRestoreOriginalFrame(true);//是否回到第一帧
    animation->setLoops(-1);//重复次数 （-1:无限循环）
    Animate * animate = Animate::create(animation);
    this->runAction(animate);
}
