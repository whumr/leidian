//
//  HBullet.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#ifndef __TankDemo__HBullet__
#define __TankDemo__HBullet__

#include "cocos2d.h"
using namespace cocos2d;

class HBullet : public cocos2d::Sprite
{
public:
    //ʵ��������
    static HBullet* createBullet(const char* _fileName,float _speed,Point _position);
    
private:
    //��ʼ������
    void bulletInit(float _speed,Point _position);
    void update(float time);//�߼�
    float speed;//�ƶ��ٶ�
    
    virtual void onExit();
};
#endif

