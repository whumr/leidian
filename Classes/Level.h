//
//  Level.h
//  PlaneDemo
//
//  Created by ºÂ½¡ on 14-4-28.
//
//

#ifndef __PlaneDemo__Level__
#define __PlaneDemo__Level__

#include "cocos2d.h"

class Level : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(Level);
    
    void Level1(Ref* psend);
    void Level2(Ref* psend);
    void Level3(Ref* psend);
    void backMenu(Ref* psend);
};

#endif /* defined(__PlaneDemo__Level__) */
