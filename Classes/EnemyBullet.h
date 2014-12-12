//
//  EnemyBullet.h
//  PlaneDemo
//
//  Created by 郝健 on 14-5-6.
//
//

#ifndef __PlaneDemo__EnemyBullet__
#define __PlaneDemo__EnemyBullet__

#include "cocos2d.h"
using namespace cocos2d;

class EnemyBullet : public cocos2d::Sprite
{
public:
    //实例化函数
    static EnemyBullet* createBullet(const char* _fileName,float _speed,Point _position,Point _playerPosition,int _type);
    
private:
    //初始化函数
    void bulletInit(float _speed,Point _position,Point _playerPosition,int _type);
    void update(float time);//逻辑
    float speed;//移动速度
    int bulletType;
        
    virtual void onExit();
    int bulletShootDelay;
    
    void aimAt();
    Point goalPoint;
    Point startingPoint;
    float slope;
    bool isAimAt;
    
    Point velocity;
    
};

#endif /* defined(__PlaneDemo__EnemyBullet__) */
