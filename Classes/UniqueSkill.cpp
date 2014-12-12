//
//  UniqueSkill.cpp
//  PlaneDemo
//
//  Created by 郝健 on 14-5-6.
//
//

#include "UniqueSkill.h"
#include "LevelScene.h"
#include "NewPlayer.h"
#include "NewBullet.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
int skill1Count = 0;
int skill2Count = 0;
int skill3Count = 0;
UniqueSkill* UniqueSkill::createUniqueSkill(const char* fileName, int _uniqueSkillType)
{
    UniqueSkill* uSkill = new UniqueSkill();
    if(uSkill)
    {
        uSkill->autorelease();
        uSkill->uniqueSkillInit(fileName, _uniqueSkillType);
        return uSkill;
    }
    CC_SAFE_DELETE(uSkill);
    return NULL;
}

void UniqueSkill::uniqueSkillInit(const char* fileName, int _uniqueSkillType)
{
    skill1TimeCount = 0;
    skill2TimeCount = 0;
    skill3TimeCount = 0;
    spritebatch = SpriteBatchNode::create("wsparticle_guenonlighting.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("wsparticle_guenonlighting.plist");
    addChild(spritebatch,1);
    
    switch(_uniqueSkillType)
    {
        case 1:
        {
            if(skill1Count==0)
            {
                auto size = Director::getInstance()->getWinSize();
                MenuItemImage *skill = MenuItemImage::create(fileName, fileName, CC_CALLBACK_0(UniqueSkill::uniqueSkill1, this));
                skill->setPosition(Vec2(size.width-skill->getContentSize().width*_uniqueSkillType,skill->getContentSize().height*0.5));
                Menu *menu = Menu::create(skill, NULL);
                menu->setAnchorPoint(Vec2(0, 0));
                menu->setPosition(Vec2(0, 0));
                this->addChild(menu, 1, tag_uniqueSkill1);
            }
            break;
        }
        case 2:
        {
            if(skill2Count==0)
            {
                auto size = Director::getInstance()->getWinSize();
                MenuItemImage *skill = MenuItemImage::create(fileName, fileName, CC_CALLBACK_0(UniqueSkill::uniqueSkill2, this));
                skill->setPosition(Vec2(size.width-skill->getContentSize().width*_uniqueSkillType-10,skill->getContentSize().height*0.5));
                Menu *menu = Menu::create(skill, NULL);
                menu->setAnchorPoint(Vec2(0, 0));
                menu->setPosition(Vec2(0, 0));
                this->addChild(menu, 1, tag_uniqueSkill2);
            }
            break;
        }
        case 3:
        {
            if(skill3Count==0)
            {
                auto size = Director::getInstance()->getWinSize();
                MenuItemImage *skill = MenuItemImage::create(fileName, fileName, CC_CALLBACK_0(UniqueSkill::uniqueSkill3, this));
                skill->setPosition(Vec2(size.width-skill->getContentSize().width*_uniqueSkillType-20,skill->getContentSize().height*0.5));
                Menu *menu = Menu::create(skill, NULL);
                menu->setAnchorPoint(Vec2(0, 0));
                menu->setPosition(Vec2(0, 0));
                this->addChild(menu, 1, tag_uniqueSkill3);
            }
            break;
        }
        default:
            break;
    }
}

void UniqueSkill::uniqueSkill1()
{
    log("aaa");
    this->removeChildByTag(tag_uniqueSkill1, true);
    skill1Count = 0;
    
    auto size = Director::getInstance()->getWinSize();
    for(int i = 1; i < 5; i++)
    {
        CallFunc *func = CallFunc::create(CC_CALLBACK_0(UniqueSkill::removeSprite, this));
        CallFunc *func1 = CallFunc::create(CC_CALLBACK_0(UniqueSkill::createBullet, this));
        CallFunc *func2 = CallFunc::create(CC_CALLBACK_0(UniqueSkill::finishBullet, this));
        Sprite *sp = Sprite::create("plane6.png");
        sp->setPosition(Vec2(sp->getContentSize().width+(i-1)*70, -sp->getContentSize().height));
        this->addChild(sp,1,i+1);
        sp->runAction(Sequence::create(MoveTo::create(1, Vec2(sp->getPositionX(), sp->getContentSize().height+30)),func1,
			DelayTime::create(10),func2,MoveTo::create(1, Vec2(sp->getPositionX(), -sp->getContentSize().height)),func,NULL));
    }
}

void UniqueSkill::uniqueSkill2()
{
    log("bbb");
    this->removeChildByTag(tag_uniqueSkill2, true);
    skill2Count = 0;
    this->schedule(schedule_selector(UniqueSkill::changeAnimate));
}

void UniqueSkill::uniqueSkill3()
{
    log("ccc");
    this->removeChildByTag(tag_uniqueSkill3, true);
    skill3Count = 0;    
    this->schedule(schedule_selector(UniqueSkill::strongSkill));
}

void UniqueSkill::removeSprite()
{
    for(int i = 1; i < 5; i++)
    {
        this->removeChildByTag(i+1, true);
    }
}

void UniqueSkill::createBullet()
{
    this->schedule(schedule_selector(UniqueSkill::autoCreateBullet));
}

void UniqueSkill::finishBullet()
{
    skill1TimeCount = 0;
    this->unschedule(schedule_selector(UniqueSkill::autoCreateBullet));
}

void UniqueSkill::autoCreateBullet(float time)
{
    skill1TimeCount++;
    if(skill1TimeCount % 30 == 0)
    {
        for(int i = 1; i<5;i++)
        {
            Sprite * player = (Sprite*)this->getChildByTag(i+1);
            this->addChild(NewBullet::createBullet("level1_bullet1.png",20,player->getPosition() + Vec2(15,15),1));
            this->addChild(NewBullet::createBullet("level1_bullet1.png",20,player->getPosition() - Vec2(15,-15),1));
            //子弹音效
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
        } 
    }
}

void UniqueSkill::createAnimate(NewEnemy* enemy)
{
    auto s = Director::getInstance()->getWinSize();
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    Sprite *Layer = Sprite::createWithSpriteFrameName("guenon_00000.png");
    Layer->setPosition(Vec2(enemy->getPositionX(), enemy->getPositionY()+40));
    spritebatch->addChild(Layer,1);
    
    Vector<SpriteFrame*> animFrames(15);
    
    char str[100] = {0};
    for(int i = 0; i < 8; i++)
    {
        sprintf(str, "guenon_0000%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
    Layer->runAction(RepeatForever::create(Animate::create(animation)));
    
    enemy->hp-=2;
}

void UniqueSkill::changeAnimate(float time)
{
    skill2TimeCount++;
    if(skill2TimeCount < 600)
    {
        if(skill2TimeCount%10 == 0)
        {
            if(spritebatch->getChildrenCount() != 0)
            {
                spritebatch->removeAllChildrenWithCleanup(true);
                return;
            }
            
            Vector<NewEnemy*> array = LevelScene::sharedLevelScene()->getArrayForEnemy();
			for(int i = 0; i < array.size(); i++)
            {
				NewEnemy* enemy = (NewEnemy*)array.at(i);
                this->createAnimate(enemy);
                //闪电音效
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("shandian.wav");
            }
        }
    }else
    {
        skill2TimeCount = 0;
        this->unschedule(schedule_selector(UniqueSkill::changeAnimate));
        if(spritebatch->getChildrenCount() != 0)
        {
            spritebatch->removeAllChildrenWithCleanup(true);
            return;
        }
    }
}

void UniqueSkill::strongSkill(float time)
{
    skill3TimeCount++;
    NewPlayer *player = LevelScene::sharedLevelScene()->getPlayer();
    if(skill3TimeCount < 600)
    {
         player->isStrong = true;
        //主角处于无敌时间时的闪烁效果
        if(skill3TimeCount%2==0){
            player->setVisible(false);
        }else{
            player->setVisible(true);
        }
    }else
    {
        skill3TimeCount = 0;
        player->isStrong = false;
        this->unschedule(schedule_selector(UniqueSkill::strongSkill));
    }
}
