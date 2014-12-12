//
//  Gems.h
//  PlaneDemo
//
//  Created by 郝健 on 14-4-29.
//
//

#ifndef __PlaneDemo__Gems__
#define __PlaneDemo__Gems__

#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class Gems : public cocos2d::Sprite
{
public:
    static Gems* createGem(const char* fileName, int gemType);//实例函数
    
private:
    int glintTime;
    int glintCount;
    bool isDisappear;
    int gemType;
    int gemMoveCount;
    void gemInit(int gemTypeTemp);//初始化函数
    void update(float dt);

};

#endif /* defined(__PlaneDemo__Gems__) */
