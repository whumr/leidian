//
//  NewEnemy.h
//  PlaneDemo
//
//  Created by �½� on 14-5-6.
//
//

#ifndef __PlaneDemo__NewEnemy__
#define __PlaneDemo__NewEnemy__

#include "cocos2d.h"
using namespace cocos2d;

class NewEnemy : public cocos2d::Sprite
{
public:
    //ʵ��������
    static NewEnemy* createEnemy(const char* fileName,int _type,int _way);
    //��ֵ���ٷ���
    int scoreValue;
    //Ѫ��
    int hp;
    int enemyType;
private:
    //��ʼ��
    void enemyInit(const char* fileName,int _type,int _way);
    
    //�����߼�
    void update(float time);
    //�Ƿ��Ѿ��˶�����
    bool isActed;
    //��ǰ��������
    int way;
    void enemyShoot();
    void shootMany(float f);
    int shootManyCount;
    void shootFive(Point playerPoint);
    void shootOne(Point playerPoint);
    void enemyDead();
    
    int timeCount1;
  
};


#endif /* defined(__PlaneDemo__NewEnemy__) */
