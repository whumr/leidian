//
//  World.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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
    
    //��ȡ��ǰHWorld�ľ�̬ʵ��
    static HWorld * sharedWorld();
    //��ȡ����
    HPlayer* getPlayer();
    //��ȡ��ŵйֵ�����
    Vector<HEnemy*> getArrayForEnemy();
    void winGame();
    void lostGame();
    
    virtual bool init();
    CREATE_FUNC(HWorld);
    
    Vector<HEnemy*> arrayEnemy;//��ŵйֵ�����
    void autoCreateBullet(float f);//�Զ������ӵ�
    void autoCreateEnemy(float f);//�Զ������й�
    void backMenu(Ref* psend);//�������˵�
    virtual ~HWorld();//��������
    
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
