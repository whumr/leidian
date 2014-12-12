//
//  HMap.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-4-16.
//
//

#include "HMap.h"
using namespace cocos2d;

HMap* HMap::createMap(const char* fileName){
    HMap* map = new HMap();
    if(map && map->create()){
        map->autorelease();
        map->mapInit(fileName);
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}

void HMap::mapInit(const char* fileName){
    
    Sprite* para1 = Sprite::create(fileName);
    Sprite* para2 = Sprite::create(fileName);
    para1->setAnchorPoint(Vec2(0, 0));
    para2->setAnchorPoint(Vec2(0, 0));
    Point para1Offset  = Vec2(0, 0);
    Point para2Offset  = Vec2(0,para1->getContentSize().height);
    
    _backgroundNode = CCParallaxNodeExtras::node();
    _backgroundNode->addChild(para1, 1, Vec2(0, 1.0f), para1Offset);
    _backgroundNode->addChild(para2, 1, Vec2(0, 1.0f), para2Offset);
    this->addChild(_backgroundNode);
    this->scheduleUpdate();
}

void HMap::update(float time){
    Point backgroundScrollVel = Vec2(0, -100);
    _backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(), ccpMult(backgroundScrollVel, time)));

    Vector<Node*> spaceDusts = _backgroundNode->getChildren();
	for ( int ii = 0  ; ii < spaceDusts.size() ; ii++ )
    {
		Sprite* spaceDust = (Sprite*)(spaceDusts.at(ii)) ;
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).y  ;
        float size = spaceDust->getContentSize().height ;
        if ( xPosition < -size )
        {
            _backgroundNode->incrementOffset(Vec2(0,spaceDust->getContentSize().height*2),spaceDust) ;
        }
    }
}

void HMap::onExit(){
    //解除更新函数
    this->unscheduleUpdate();
    Layer::onExit();
}
