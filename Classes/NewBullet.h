//
//  NewBullet.h
//  PlaneDemo
//
//  Created by �½� on 14-4-29.
//
//

#ifndef __PlaneDemo__NewBullet__
#define __PlaneDemo__NewBullet__

#include "cocos2d.h"
using namespace cocos2d;

class NewBullet : public cocos2d::Sprite
{
public:
    //ʵ��������
    static NewBullet* createBullet(const char* _fileName,float _speed,Point _position,int _type);
    
private:
    //��ʼ������
    void bulletInit(float _speed,Point _position,int _type);
    void update(float time);//�߼�
    float speed;//�ƶ��ٶ�
    int bulletType;
    
    Point bulletPoint;
    Point enemyPoint;
    float newSlope;
    
    virtual void onExit();
    
    int rotation;
    Point velocity;
};


#endif /* defined(__PlaneDemo__NewBullet__) */
