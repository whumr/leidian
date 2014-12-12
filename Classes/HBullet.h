//
//  HBullet.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__HBullet__
#define __TankDemo__HBullet__

#include "cocos2d.h"
using namespace cocos2d;

class HBullet : public cocos2d::Sprite
{
public:
    //实例化函数
    static HBullet* createBullet(const char* _fileName,float _speed,Point _position);
    
private:
    //初始化函数
    void bulletInit(float _speed,Point _position);
    void update(float time);//逻辑
    float speed;//移动速度
    
    virtual void onExit();
};
#endif

