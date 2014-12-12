//
//  HEnemy.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#ifndef __TankDemo__HEnemy__
#define __TankDemo__HEnemy__


#include "cocos2d.h"
using namespace cocos2d;

class HEnemy : public cocos2d::Sprite
{
public:
    //ʵ��������
    static HEnemy* createEnemy(const char* fileName,int _type,int _way);
    //��ֵ���ٷ���
    int scoreValue;
    //Ѫ��
    int hp;
private:
    //��ʼ��
    void enemyInit(const char* fileName,int _type,int _way);
    
    //���˳ɶ�̬����
    void createAnimate(const char* fileName,int allCount);
    //�����߼�
    void update(float time);
    //�Ƿ��Ѿ��˶�����
    bool isActed;
    //��ǰ��������
    int way;
    void removeSelf();
};
#endif