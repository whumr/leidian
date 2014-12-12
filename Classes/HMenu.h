//
//  HMenu.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
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
    //当点击"Play"菜单项触发的回调函数
    void playIsPressed(Ref* psend);
    //当点击"Score"菜单项触发的回调函数
    void scoreIsPressed(Ref* psend);
    //当点击"About"菜单项触发的回调函数
    void aboutIsPressed(Ref* psend);
    //当点击"settings"菜单项触发的回调函数
    void SetttingsIsPressed(Ref* psend);
};
#endif /* defined(__TankDemo__HMenu__) */
