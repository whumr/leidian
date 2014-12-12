//
//  CCParallaxNodeExtras.h
//  ScenesAndLayers
//
//  Created by Star on 14-4-11.
//
//

#ifndef __ScenesAndLayers__CCParallaxNodeExtras__
#define __ScenesAndLayers__CCParallaxNodeExtras__

#include "cocos2d.h"
USING_NS_CC;
class CCParallaxNodeExtras : public ParallaxNode
{
public :
    CCParallaxNodeExtras() ;
    static CCParallaxNodeExtras* node() ;
    void incrementOffset(Point offset, Node* node);

};
#endif /* defined(__ScenesAndLayers__CCParallaxNodeExtras__) */
