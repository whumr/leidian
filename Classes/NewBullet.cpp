//
//  NewBullet.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-29.
//
//

#include "NewBullet.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "NewEnemy.h"

using namespace CocosDenshion;

NewBullet* NewBullet::createBullet(const char* _fileName,float _speed,Point _position,int _type){
    NewBullet* bullet = new NewBullet();
    if(bullet && bullet->initWithSpriteFrameName(_fileName)){
        bullet->autorelease();
        bullet->bulletInit(_speed,_position,_type);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}
void NewBullet::bulletInit(float _speed,Point _position,int _type){
    speed = _speed;
    bulletType = _type;
    this->setPosition(_position);
    
    rotation += 180;
    rotation *=-1;
    
    this->scheduleUpdate();
}

//子弹逻辑
void NewBullet::update(float time){
    
    auto size = Director::getInstance()->getWinSize();
    switch(bulletType)
    {
        case 1:
            //子弹向上运动
            this->setPosition(this->getPosition() + Vec2(0,speed));
            break;
        case 2:
        {            
            Vector<NewEnemy*> enemyArray = LevelScene::sharedLevelScene()->getArrayForEnemy();
			for(int i = 0; i <enemyArray.size(); i++)
            {
				NewEnemy *enemy = (NewEnemy*)enemyArray.at(i);
                
                bulletPoint = this->getPosition();
                enemyPoint = enemy->getPosition();
                
                Point v= enemyPoint - bulletPoint;
                float angel = 3.14/2 - v.getAngle();
                this->setRotation(CC_RADIANS_TO_DEGREES(angel));
                velocity = v.getNormalized() * 4.0;
            }
            
            this->setPosition(this->getPosition() + velocity);
            //log("velocity.(x,y) = (%f,%f)",velocity.x,velocity.y);
                
            break;
        }   
        default:
            break;
            
    }
    if(this->getPositionY() < -this->getContentSize().height || this->getPositionY() > size.height + this->getContentSize().height 
		|| this->getPositionX() < -this->getContentSize().width || this->getPositionX() > size.width + this->getContentSize().width)
    {
        this->removeFromParentAndCleanup(true);
        return;
    }
    
    //处理子弹击中
    Vector<NewEnemy*> array = LevelScene::sharedLevelScene()->getArrayForEnemy();
	for (int i =0; i<array.size(); i++) {
		NewEnemy* enemy = (NewEnemy*)array.at(i);
        if(enemy->getBoundingBox().intersectsRect(this->getBoundingBox()))
        {
			if(enemy->hp > 0 && !enemy->isDead)
			{				
				switch(bulletType)
				{
					case 1:
						(enemy->hp)--;
						break;
					case 2:
						(enemy->hp)-=3;
					default:
						break;
				}      
				if(enemy->hp <= 0 && !enemy->isDead)
				{
					enemy->enemyDead();    
				}
				this->removeFromParentAndCleanup(true);
				break;
			}            
        }
    }
}
//生命周期-退出
void NewBullet::onExit(){
    //取消更新函数
    this->unscheduleUpdate();
    Sprite::onExit();
}