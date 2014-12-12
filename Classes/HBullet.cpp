//
//  HBullet.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HBullet.h"
#include "HWorld.h"
#include "HEnemy.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

HBullet* HBullet::createBullet(const char* _fileName,float _speed,Point _position){
    HBullet* bullet = new HBullet();
    if(bullet && bullet->initWithFile(_fileName)){
        bullet->autorelease();
        bullet->bulletInit(_speed,_position);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}
void HBullet::bulletInit(float _speed,Point _position){
    speed = _speed;
    this->setPosition(_position);
    this->scheduleUpdate();
}

//子弹逻辑
void HBullet::update(float time){
    //子弹向上运动
    this->setPosition(this->getPosition() + Vec2(0,speed));
    
    if(this->getPositionY() > Director::getInstance()->getWinSize().height)
    {
        this->removeFromParentAndCleanup(true);
        return;
    }
    
    //处理子弹击中
    Vector<HEnemy*> array = HWorld::sharedWorld()->getArrayForEnemy();
	for (int i =0; i<array.size(); i++) {
		HEnemy* enemy = (HEnemy*)array.at(i);
        if(enemy->getBoundingBox().intersectsRect(this->getBoundingBox()))
        {
            (enemy->hp)--;
            if(enemy->hp <= 0)
            {
                //爆炸音效
                SimpleAudioEngine::getInstance()->playEffect("effect_boom.mp3");
                
                //爆炸粒子效果
                ParticleSystemQuad * particle = ParticleSystemQuad::create("particle_boom.plist");
                particle->setPosition(enemy->getPosition());//怪的位置
                particle->setAutoRemoveOnFinish(true);//自动释放
                HWorld::sharedWorld()->addChild(particle);//添加到主layer
                //增加分数
                HWorld::sharedWorld()->getPlayer()->addScore(enemy->scoreValue);
                //添加杀人数
                HWorld::sharedWorld()->getPlayer()->addKillCount(1);
                //从敌人数组将被攻击的敌怪删除
				array.eraseObject(enemy);
                //删除子弹与敌怪
                HWorld::sharedWorld()->removeChild(enemy, true);
                this->removeFromParentAndCleanup(true);
                break;
            }else
            {
                this->removeFromParentAndCleanup(true);
                break;
            }
            
        }
    }
}
//生命周期-退出
void HBullet::onExit(){
    //取消更新函数
    this->unscheduleUpdate();
    Sprite::onExit();
}