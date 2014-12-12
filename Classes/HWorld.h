//
//  World.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__World__
#define __TankDemo__World__


#include "cocos2d.h"
#include "HPlayer.h"
#include "HEnemy.h"

#include "SneakyJoystick/SneakyButton.h"
#include "SneakyJoystick/SneakyJoystick.h"
#include "SneakyJoystick/SneakyButtonSkinnedBase.h"
#include "SneakyJoystick/SneakyJoystickSkinnedBase.h"

USING_NS_CC;


class HWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    //获取当前HWorld的静态实例
    static HWorld * sharedWorld();
    //获取主角
    HPlayer* getPlayer();
    //获取存放敌怪的数组
    Vector<HEnemy*> getArrayForEnemy();
    void winGame();
    void lostGame();
    
    virtual bool init();
    CREATE_FUNC(HWorld);
    
    Vector<HEnemy*> arrayEnemy;//存放敌怪的数组
    void autoCreateBullet(float f);//自动创建子弹
    void autoCreateEnemy(float f);//自动创建敌怪
    void backMenu(Ref* psend);//返回主菜单
    virtual ~HWorld();//析构函数
    
    SneakyButton * fireButton;
	SneakyJoystick * joystick;
    
    float totalTime;
	float nextShotTime;
    
    SpriteBatchNode *bulletBatchNode;
    
    void TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    bool TouchBegan(Touch *pTouch, Event *pEvent);

    void doPause(Ref* psend);
    
    int smallEnemyTime;
    int mediumEnemyTime;
    int bigEnemyTime;
    int smallEnemyTime2;
    int mediumEnemyTime2;
    
    bool isGetNewRecord;    
};

#endif /* defined(__TankDemo__World__) */
