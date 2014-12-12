//
//  HBullet.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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

//�ӵ��߼�
void HBullet::update(float time){
    //�ӵ������˶�
    this->setPosition(this->getPosition() + Vec2(0,speed));
    
    if(this->getPositionY() > Director::getInstance()->getWinSize().height)
    {
        this->removeFromParentAndCleanup(true);
        return;
    }
    
    //�����ӵ�����
    Vector<HEnemy*> array = HWorld::sharedWorld()->getArrayForEnemy();
	for (int i =0; i<array.size(); i++) {
		HEnemy* enemy = (HEnemy*)array.at(i);
        if(enemy->getBoundingBox().intersectsRect(this->getBoundingBox()))
        {
            (enemy->hp)--;
            if(enemy->hp <= 0)
            {
                //��ը��Ч
                SimpleAudioEngine::getInstance()->playEffect("effect_boom.mp3");
                
                //��ը����Ч��
                ParticleSystemQuad * particle = ParticleSystemQuad::create("particle_boom.plist");
                particle->setPosition(enemy->getPosition());//�ֵ�λ��
                particle->setAutoRemoveOnFinish(true);//�Զ��ͷ�
                HWorld::sharedWorld()->addChild(particle);//��ӵ���layer
                //���ӷ���
                HWorld::sharedWorld()->getPlayer()->addScore(enemy->scoreValue);
                //���ɱ����
                HWorld::sharedWorld()->getPlayer()->addKillCount(1);
                //�ӵ������齫�������ĵй�ɾ��
				array.eraseObject(enemy);
                //ɾ���ӵ���й�
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
//��������-�˳�
void HBullet::onExit(){
    //ȡ�����º���
    this->unscheduleUpdate();
    Sprite::onExit();
}