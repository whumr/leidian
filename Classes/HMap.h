//
//  HMap.h
//  PlaneDemo
//
//  Created by �½� on 14-4-16.
//
//

#ifndef __TankDemo__HMap__
#define __TankDemo__HMap__

#include "cocos2d.h"
using namespace cocos2d;
//#include "CCParallaxNodeExtras.h"

typedef enum{
    tag_oneImg,
    tag_twoImg,
}tagMap;//ö�����ŵ�ͼ�����Ľ������

class HMap : public cocos2d::Layer
{
public:
    //ʵ��������
    static HMap* createMap(const char* fileName);
    
private:
    //��ʼ��
    void mapInit(const char* fileName);
    //�߼�
    void update(float time);
    //�������ں������˳�
    virtual void onExit();
    
    ParallaxNode *_backgroundNode;
};
#endif
