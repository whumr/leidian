//
//  Gems.cpp
//  PlaneDemo
//
//  Created by �½� on 14-4-29.
//
//

#include "Gems.h"
#include "LevelScene.h"
#include "NewPlayer.h"
#include "UniqueSkill.h"
using namespace cocos2d;

extern int playerType;
extern int skill1Count;
extern int skill2Count;
extern int skill3Count;

Gems* Gems::createGem(const char* fileName, int gemTypeTemp){
    Gems* gem = new Gems();
    if(gem && gem->initWithFile(fileName)){
        gem->autorelease();
        gem->gemInit(gemTypeTemp);
        return gem;
    }
    CC_SAFE_DELETE(gem);
    return NULL;
}

void Gems::gemInit(int gemTypeTemp){
    gemType = gemTypeTemp;
	gemMoveCount = 0;
    glintTime = 15*60;
    glintCount = 0;
    isDisappear = false;
    this->scheduleUpdate();
}

void Gems::update(float dt)
{
    //��ʯ�ƶ�
    gemMoveCount++;
    if (gemMoveCount > 100)
    {
        gemMoveCount = 0;
        auto * action = MoveBy::create(2, Vec2(CCRANDOM_0_1()*100-50,CCRANDOM_0_1()*100-80));
        this->runAction(action);
    }

    //��ʯ��˸
    glintCount++;
    if(glintCount>=glintTime)
	{
        this->setVisible(true);
        isDisappear = true;
        this->unscheduleUpdate();
        this->removeFromParentAndCleanup(true);
    }
	else
	{
        //��ʯ����˸Ч��
        if(glintCount%20==0)
		{
            this->setVisible(false);
        }
		else
		{
            this->setVisible(true);
        }
		//��ײ���
		NewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
		if(!player->isDead)
		{
			if(player->getBoundingBox().intersectsRect(this->getBoundingBox()))
			{				
				switch(gemType)
				{
					case 0:    //�ı�ɻ�����
					{
						if(playerType <= 3)
						{
							LevelScene::sharedLevelScene()->isPlayerChange = true;
							playerType++;
						}
						break;
					}
					case 1:    //��Ѫ
					{ 
						if(player->hp<3)
						{
							player->addHp();
							player->hp++;
						} 
						break;
					}
					case 2:    //�Ӵ���1
					{
						Node *skill = UniqueSkill::createUniqueSkill("skill1.png", 1);
						LevelScene::sharedLevelScene()->addChild(skill);
						skill1Count++;
						break;
					}
					case 3:    //�Ӵ���2
					{
						Node *skill = UniqueSkill::createUniqueSkill("skill2.png", 2);
						LevelScene::sharedLevelScene()->addChild(skill);
						skill2Count++;
						break;
					}
					case 4:    //�Ӵ���3
					{
						Node *skill = UniqueSkill::createUniqueSkill("skill3.png", 3);
						LevelScene::sharedLevelScene()->addChild(skill);
						skill3Count++;
						break;
					}
					default:
						break;
				}
				this->removeFromParentAndCleanup(true);
			}
		}
    }    
    
}
