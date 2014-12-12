//
//  UniqueSkill.h
//  PlaneDemo
//
//  Created by 郝健 on 14-5-6.
//
//

#ifndef __PlaneDemo__UniqueSkill__
#define __PlaneDemo__UniqueSkill__

#include <iostream>
#include "cocos2d.h"
#include "NewEnemy.h"
using namespace std;
using namespace cocos2d;

class UniqueSkill : public Node
{
public:
    static UniqueSkill* createUniqueSkill(const char* fileName, int _uniqueSkillType);//实例函数
private:

    int skill1TimeCount;
    int skill2TimeCount;
    int skill3TimeCount;
    
    void uniqueSkillInit(const char* fileName, int _uniqueSkillType);//初始化函数
    void uniqueSkill1();
    void uniqueSkill2();
    void uniqueSkill3();
    void removeSprite();
    void createBullet();
    void finishBullet();
    void autoCreateBullet(float time);
    void changeAnimate(float time);
    void createAnimate(NewEnemy* enemy);
    void strongSkill(float time);
    SpriteBatchNode* spritebatch;
};

#endif /* defined(__PlaneDemo__UniqueSkill__) */
