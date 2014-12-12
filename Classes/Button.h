//
//  Button.h
//  PlaneDemo
//
//  Created by �½� on 14-4-28.
//
//

#ifndef __PlaneDemo__Button__
#define __PlaneDemo__Button__

#include <iostream>

#include "cocos2d.h"
#include "SneakyJoystick/SneakyButton.h"
#include "SneakyJoystick/SneakyButtonSkinnedBase.h"
#include "SneakyJoystick/SneakyJoystick.h"
#include "SneakyJoystick/SneakyJoystickSkinnedBase.h"
#include "HWorld.h"

class Button : public cocos2d::Layer
{
public:
    SneakyButton *fireButton;
    SneakyJoystick *joystick;
    HPlayer* myPlayer;
    HWorld* myWorld;
    float totalTime;
    float nextShotTime;
    
public:
    //ʵ��������
    static Button* createButton(HPlayer* player, HWorld* world);
    
private:
    //��ʼ��
    void buttonInit(HPlayer* player, HWorld* world);
    //�߼�
    void update(float time);
    
    void addFireButton();
    void addJoystick();
};


#endif /* defined(__PlaneDemo__Button__) */
