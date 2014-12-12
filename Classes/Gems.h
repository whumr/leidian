//
//  Gems.h
//  PlaneDemo
//
//  Created by �½� on 14-4-29.
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
    static Gems* createGem(const char* fileName, int gemType);//ʵ������
    
private:
    int glintTime;
    int glintCount;
    bool isDisappear;
    int gemType;
    int gemMoveCount;
    void gemInit(int gemTypeTemp);//��ʼ������
    void update(float dt);

};

#endif /* defined(__PlaneDemo__Gems__) */
