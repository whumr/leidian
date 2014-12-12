//
//  HPlayer.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#ifndef __TankDemo__HPlayer__
#define __TankDemo__HPlayer__

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;

typedef enum{
    tag_player,//����
    tag_playerHp1,//Ѫ��1
    tag_playerHp2,//Ѫ��2
    tag_playerHp3,//Ѫ��3
    tag_scoreTTF,//����
    tag_killsCountTTF,//ɱ����
    tag_uniqueSkill1,//����1
    tag_uniqueSkill2,//����2
    tag_uniqueSkill3,//����3
}tagPlayer;//ö�ٱ���

//��Ҫ���ڽ�int float ������ת����string����
template<typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

class HPlayer : public cocos2d::Sprite
{
public:
    static HPlayer* createPlayer(const char* fileName);//ʵ������
    int hp;//Ѫ��
    int hpMax;//Ѫ�����ֵ
    int score;//����
    int killCount;//ɱ����
    void downHp();//��Ѫ
    void addScore(float _value);//�ӷ�
    void addKillCount(float _value);//��ɱ����
    bool isDead;//�Ƿ�����
    
private:
    int strongTime;//�޵�ʱ��
    bool isStrong;//�Ƿ����޵�ʱ��
    int strongCount;//�޵�ʱ�ļ�����
    void strongIng(float dt);//�����޵�ʱ����˸�ȴ���
    
    void playerInit(const char* fileName);//��ʼ������
    
    void createAnimate(const char* fileName);
};
#endif
