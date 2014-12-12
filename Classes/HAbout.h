//
//  HAbout.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#ifndef __TankDemo__HAbout__
#define __TankDemo__HAbout__


#include "cocos2d.h"

class HAbout : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HAbout);
    
private:
    //菜单项"返回主菜单"的回调函数
    void backMenu(Ref* psend);
    
    void a();
    void b();
    void c();
    void d();
    void e();
    void f();
    void remove();

};
#endif /* defined(__TankDemo__HAbout__) */
