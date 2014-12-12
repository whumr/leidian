//
//  HScore.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__HScore__
#define __TankDemo__HScore__

#include "cocos2d.h"

class HScore : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HScore);
    
private:
    //菜单项"返回主菜单"的回调函数
    void backMenu(Ref* psend);
};

#endif /* defined(__TankDemo__HScore__) */
