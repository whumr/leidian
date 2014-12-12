//
//  HEnemy.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__HEnemy__
#define __TankDemo__HEnemy__


#include "cocos2d.h"
using namespace cocos2d;

class HEnemy : public cocos2d::Sprite
{
public:
    //实例化函数
    static HEnemy* createEnemy(const char* fileName,int _type,int _way);
    //价值多少分数
    int scoreValue;
    //血量
    int hp;
private:
    //初始化
    void enemyInit(const char* fileName,int _type,int _way);
    
    //敌人成动态表现
    void createAnimate(const char* fileName,int allCount);
    //敌人逻辑
    void update(float time);
    //是否已经运动过了
    bool isActed;
    //当前敌人类型
    int way;
    void removeSelf();
};
#endif