//
//  HPlayer.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__HPlayer__
#define __TankDemo__HPlayer__

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;

typedef enum{
    tag_player,//主角
    tag_playerHp1,//血量1
    tag_playerHp2,//血量2
    tag_playerHp3,//血量3
    tag_scoreTTF,//分数
    tag_killsCountTTF,//杀敌数
    tag_uniqueSkill1,//大招1
    tag_uniqueSkill2,//大招2
    tag_uniqueSkill3,//大招3
}tagPlayer;//枚举变量

//主要用于将int float 等数字转换成string类型
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
    static HPlayer* createPlayer(const char* fileName);//实例函数
    int hp;//血量
    int hpMax;//血量最大值
    int score;//分数
    int killCount;//杀敌数
    void downHp();//掉血
    void addScore(float _value);//加分
    void addKillCount(float _value);//加杀敌数
    bool isDead;//是否死亡
    
private:
    int strongTime;//无敌时间
    bool isStrong;//是否处于无敌时间
    int strongCount;//无敌时的计数器
    void strongIng(float dt);//处理无敌时的闪烁等处理
    
    void playerInit(const char* fileName);//初始化函数
    
    void createAnimate(const char* fileName);
};
#endif
