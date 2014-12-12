//
//  Button.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-28.
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
    //实例化函数
    static Button* createButton(HPlayer* player, HWorld* world);
    
private:
    //初始化
    void buttonInit(HPlayer* player, HWorld* world);
    //逻辑
    void update(float time);
    
    void addFireButton();
    void addJoystick();
};


#endif /* defined(__PlaneDemo__Button__) */
