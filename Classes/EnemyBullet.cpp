//
//  EnemyBullet.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-5-6.
//
//

#include "EnemyBullet.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "NewEnemy.h"

using namespace CocosDenshion;

EnemyBullet* EnemyBullet::createBullet(const char* _fileName,float _speed,Point _position,Point _playerPosition,int _type){
    EnemyBullet* bullet = new EnemyBullet();
    if(bullet && bullet->initWithSpriteFrameName(_fileName)){
        bullet->autorelease();
        bullet->bulletInit(_speed,_position,_playerPosition,_type);
        return bullet;
    }
    CC_SAFE_DELETE(bullet);
    return NULL;
}
void EnemyBullet::bulletInit(float _speed,Point _position,Point _playerPosition,int _type){
    speed = _speed;
    bulletType = _type;
    goalPoint = _playerPosition;
    bulletShootDelay = 0;
    this->setPosition(_position);
    this->scheduleUpdate();
}

//子弹逻辑
void EnemyBullet::update(float time){
    auto size = Director::getInstance()->getWinSize();
    switch(bulletType)
    {
        case 1:
        {
            this->setPosition(this->getPosition() + Vec2(0,-speed));//竖直向下
            break;
        }
        case 2:
        {
            this->aimAt();
            break;
        }
        case 3:
        {
            this->setPosition(this->getPosition() + Vec2(-speed,-speed));//左下
            break;
        }
        case 4:
        {
            this->setPosition(this->getPosition() + Vec2(speed,-speed));//右下
            break;
        }
        case 5:
        {
            this->setPosition(this->getPosition() + Vec2(-speed/3,-speed));//左下下
            break;
        }
        case 6:
        {
            this->setPosition(this->getPosition() + Vec2(speed/3,-speed));//右下下
            break;
        }
        default:
            break;
    }
    if(this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height+this->getContentSize().height || this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width+this->getContentSize().width)
    {
        this->removeFromParentAndCleanup(true);
        return;
    }
    
    //处理子弹击中
    NewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
    if(player->getBoundingBox().intersectsRect(this->getBoundingBox()))
    {
        this->removeFromParentAndCleanup(true);
        player->downHp();
    }
}

//子弹瞄准
void EnemyBullet::aimAt()
{
    if(!isAimAt)
    {
        startingPoint = this->getPosition();
        slope = (goalPoint.y-startingPoint.y)/(goalPoint.x-startingPoint.x);
    }
    isAimAt = true;
    
    Point v = goalPoint - startingPoint;
    velocity = v.getNormalized() * 2.5;
    this->setPosition(this->getPosition() + velocity);

    //下面是以前写的，上面三行代码搞定。
//    if(goalPoint.y>startingPoint.y && goalPoint.x>startingPoint.x)//飞机在子弹右上方
//    {
//        if(slope<=1)
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(speed, speed*slope)));
//        }else
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(speed/slope, speed)));
//        }
//        
//    }else if(goalPoint.y>startingPoint.y && goalPoint.x<startingPoint.x)//飞机在子弹左上方
//    {
//        if(slope>=-1)
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(-speed, -speed*slope)));
//        }else
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(speed/slope, speed)));
//        }
//        
//    }else if (goalPoint.y<startingPoint.y && goalPoint.x>startingPoint.x)//飞机在子弹右下方
//    {
//        if(slope>=-1)
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(speed, speed*slope)));
//        }else
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(-speed/slope, -speed)));
//        }
//    }else if (goalPoint.y<startingPoint.y && goalPoint.x<startingPoint.x)//飞机在子弹左下方
//    {
//        if(slope<=1)
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(-speed, -speed*slope)));
//        }else
//        {
//            this->setPosition(ccpAdd(this->getPosition(), Vec2(-speed/slope, -speed)));
//        }
//    }
}

//生命周期-退出
void EnemyBullet::onExit(){
    //取消更新函数
    this->unscheduleUpdate();
    Sprite::onExit();
}







