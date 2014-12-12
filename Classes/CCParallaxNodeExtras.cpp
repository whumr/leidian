//
//  CCParallaxNodeExtras.cpp
//  ScenesAndLayers
//
//  Created by Star on 14-4-11.
//
//

#include "CCParallaxNodeExtras.h"

class PointObject : Ref {
    CC_SYNTHESIZE(Point, m_tRatio, Ratio)
    CC_SYNTHESIZE(Point, m_tOffset, Offset)
    CC_SYNTHESIZE(Node*, m_pChild, Child) // weak ref
};

// Need to provide our own constructor

CCParallaxNodeExtras::CCParallaxNodeExtras()
{
	ParallaxNode::create(); // call parent constructor
}

CCParallaxNodeExtras* CCParallaxNodeExtras::node() {    
    return new CCParallaxNodeExtras();    
}

void CCParallaxNodeExtras::incrementOffset(Point offset,Node* node)
{
    for(int i=0;i < _parallaxArray->num;i++) {        
        PointObject* point = (PointObject*)_parallaxArray->arr[i];        
        Node* curNode = point->getChild() ;        
        if(curNode == node) {            
            point->setOffset(point->getOffset() + offset);
            break;
        }
    }
}