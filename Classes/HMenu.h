//
//  HMenu.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#ifndef __TankDemo__HMenu__
#define __TankDemo__HMenu__

#include "cocos2d.h"

class HMenu : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HMenu);

private:
    //�����"Play"�˵�����Ļص�����
    void playIsPressed(Ref* psend);
    //�����"Score"�˵�����Ļص�����
    void scoreIsPressed(Ref* psend);
    //�����"About"�˵�����Ļص�����
    void aboutIsPressed(Ref* psend);
    //�����"settings"�˵�����Ļص�����
    void SetttingsIsPressed(Ref* psend);
};
#endif /* defined(__TankDemo__HMenu__) */
