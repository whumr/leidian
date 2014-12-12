//
//  NewPlayer.h
//  PlaneDemo
//
//  Created by �½� on 14-4-28.
//
//

#ifndef __PlaneDemo__NewPlayer__
#define __PlaneDemo__NewPlayer__

#include "cocos2d.h"
using namespace cocos2d;

class NewPlayer : public cocos2d::Sprite
{
public:
    static NewPlayer* createPlayer(const char* fileName);//ʵ������
    int hp;//Ѫ��
    int hpMax;//Ѫ�����ֵ
    int score;//����
    int killCount;//ɱ����
    void downHp();//��Ѫ
    void addHp();//��Ѫ
    void addScore(float _value);//�ӷ�
    void addKillCount(float _value);//��ɱ����
    bool isDead;//�Ƿ�����
    int strongTime;//�޵�ʱ��
    bool isStrong;//�Ƿ����޵�ʱ��
    int strongCount;//�޵�ʱ�ļ�����
    void strongIng(float dt);//�����޵�ʱ����˸�ȴ���
    
private:
    
    void playerInit();//��ʼ������
};

#endif /* defined(__PlaneDemo__NewPlayer__) */




