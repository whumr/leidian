//
//  HAbout.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
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
    //�˵���"�������˵�"�Ļص�����
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
