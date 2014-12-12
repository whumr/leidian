//
//  HPauseLayer.h
//  PlaneDemo
//
//  Created by ºÂ½¡ on 14-4-18.
//
//

#ifndef __PlaneDemo__HPauseLayer__
#define __PlaneDemo__HPauseLayer__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class HPauseLayer : public LayerColor {
    
public:
    virtual bool init();
    
    bool TouchBegan(Touch* touch, Event* event);
    
    void doResume(Ref *pSender);
    CREATE_FUNC(HPauseLayer);
};


#endif /* defined(__PlaneDemo__HPauseLayer__) */
