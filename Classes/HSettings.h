//
//  HSettings.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-18.
//
//

#ifndef __PlaneDemo__HSettings__
#define __PlaneDemo__HSettings__

#include <iostream>
#include "cocos2d.h"

class HSettings : public cocos2d::Layer
{
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(HSettings);
    
private:
    //当点击"touchType"菜单项触发的回调函数
    void touchTypeChange(Ref* psend);
    void touchTypeChange2(Ref* psend);
    
    void backMenu(Ref* psend);
    
};
#endif /* defined(__PlaneDemo__HSettings__) */
