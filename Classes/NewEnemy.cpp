//
//  NewEnemy.cpp
//  PlaneDemo
//
//  Created by �½� on 14-5-6.
//
//

#include "NewEnemy.h"
#include "LevelScene.h"
#include "EnemyBullet.h"
#include "SimpleAudioEngine.h"
#include "Gems.h"

using namespace CocosDenshion;

NewEnemy* NewEnemy::createEnemy(const char* fileName,int _type,int _way){
    NewEnemy* enemy = new NewEnemy();
    if(enemy && enemy->initWithSpriteFrameName(fileName)){
        enemy->autorelease();
        enemy->enemyInit(fileName,_type,_way);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}
//��ʼ��
void NewEnemy::enemyInit(const char* fileName,int _type,int _way){
	isActed = false;
	isDead = false;
    way=_way;
    enemyType = _type;
    shootManyCount = 0;
    auto size = Director::getInstance()->getWinSize();
    if(_type==0)
    {
        scoreValue=2;
        hp = 4;
    }else if(_type==1)
    {
        scoreValue=5;
        hp = 6;
    }else if(_type==2)
    {
        scoreValue=10;
        hp = 10;
    }else if(_type==3)
    {
        scoreValue=15;
        hp = 13;
    }else if (_type==4)
    {
        scoreValue=100;
        hp = 200;
    }
 
    this->setPosition(Vec2(CCRANDOM_0_1()*size.width, size.height + this->getContentSize().height));

    //�����߼�
    this->scheduleUpdate();
}
//���ֲ�ͬ���ƶ��߼�
void NewEnemy::update(float time){
    
    timeCount1++;
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(NewEnemy::enemyShoot, this));
    auto size = Director::getInstance()->getWinSize();
    switch (way) {
        case 0://����
        {
            this->setPosition(this->getPosition() + Vec2(0, -1));
            if(isActed)
            {
                break;
            }
            isActed=true;
            this->runAction(Sequence::create(DelayTime::create(4),func,DelayTime::create(2),func,NULL));
            break;
        }
        case 1://���������ƶ�
        {
            //�жϷ�ֹ�ظ����ô˶�������֤���߼�ֻ��ִ��һ��
            if(isActed)
            {
                break;
            }
            isActed=true;
            this->runAction(Sequence::create(MoveTo::create(1, Vec2(this->getPositionX(), CCRANDOM_0_1() *200 + size.height/2)),func,
				MoveBy::create(2, Vec2(CCRANDOM_0_1() *300 - 150, 0)),func,
				MoveBy::create(2, Vec2(CCRANDOM_0_1() *300 - 150, 0)),func,
				MoveBy::create(2, Vec2(CCRANDOM_0_1() *300 - 150, 0)),func,
				MoveTo::create(1, Vec2(this->getPositionX(), size.height+2*this->getContentSize().height)),NULL));
            break;
        }
        case 2://��������
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            this->runAction(Sequence::create(MoveTo::create(2, Vec2(size.width/2, size.height*4/7)),func,
				DelayTime::create(3),func,DelayTime::create(3),func,
				DelayTime::create(3),func,DelayTime::create(3),func,
				DelayTime::create(3),func,DelayTime::create(3),func,
				DelayTime::create(3),func,DelayTime::create(3),func,
				DelayTime::create(3),func,DelayTime::create(2),
				MoveTo::create(2, Vec2(this->getPositionX(), size.height+2*this->getContentSize().height)),NULL));
            break;
        }
        case 3://�ϻ�
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            
            ccBezierConfig bezier; // ��������������
            bezier.controlPoint_1 = Vec2(0, size.height+this->getContentSize().height); // ��ʼ��
            bezier.controlPoint_2 = Vec2(size.width/2, size.height/5); //���Ƶ�
            bezier.endPosition = Vec2(size.width, size.height+2*this->getContentSize().height); // ����λ��
            BezierTo *actionMove = BezierTo::create(4, bezier);
            FiniteTimeAction *sequence = Sequence::create(DelayTime::create(1),func,DelayTime::create(2),func,NULL);
            this->runAction(Spawn::create(actionMove,sequence,NULL));
            
            break;
        }
        case 4://��
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            ccBezierConfig bezier; // ��������������
            bezier.controlPoint_1 = Vec2(size.width/2, size.height+this->getContentSize().height); // ��ʼ��
            bezier.controlPoint_2 = Vec2(size.width/2, size.height/2); //���Ƶ�
            bezier.endPosition = Vec2(-2*this->getContentSize().width, size.height/2); // ����λ��
            BezierTo *actionMove = BezierTo::create(4, bezier);
            FiniteTimeAction *sequence = Sequence::create(DelayTime::create(0.5),func,
				DelayTime::create(0.5),func,DelayTime::create(0.5),func,DelayTime::create(0.5),func,NULL);
            this->runAction(Spawn::create(actionMove,sequence,NULL));
            
            break;
        }
        case 5://�һ�
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            ccBezierConfig bezier; // ��������������
            bezier.controlPoint_1 = Vec2(size.width/2, size.height+this->getContentSize().height); // ��ʼ��
            bezier.controlPoint_2 = Vec2(size.width/2, size.height/2); //���Ƶ�
            bezier.endPosition = Vec2(size.width+2*this->getContentSize().width, size.height/2); // ����λ��
            BezierTo *actionMove = BezierTo::create(4, bezier);
            FiniteTimeAction *sequence = Sequence::create(DelayTime::create(0.5),func,
				DelayTime::create(0.5),func,DelayTime::create(0.5),func,DelayTime::create(0.5),func,NULL);
            this->runAction(Spawn::create(actionMove,sequence,NULL));
            
            break;
        }
        case 6://����
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            FiniteTimeAction *sequence = Sequence::create(DelayTime::create(1),func,DelayTime::create(1),func,NULL);
            this->runAction(Spawn::create(MoveTo::create(5, Vec2(size.width+2*this->getContentSize().width, size.height/2)),sequence,NULL));
            break;
        }
        case 7://����
        {
            if(isActed)
            {
                break;
            }
            isActed=true;
            FiniteTimeAction *sequence = Sequence::create(DelayTime::create(1),func,DelayTime::create(1),func,NULL);
            this->runAction(Spawn::create(MoveTo::create(5, Vec2(-2*this->getContentSize().width, size.height/2)),sequence,NULL));
            break;
        }
            break;
    }
    //ɾ��
    if(this->getPositionY()<-this->getContentSize().height || this->getPositionY()>size.height+this->getContentSize().height 
		|| this->getPositionX()<-this->getContentSize().width || this->getPositionX()>size.width+this->getContentSize().width)
    {   
        this->removeFromParentAndCleanup(true);
        LevelScene::sharedLevelScene()->getArrayForEnemy().eraseObject(this);
    }
    
    if(hp <= 0 && !isDead)
    {
        this->enemyDead();
    }
    
    //��ײ���
    NewPlayer * player = LevelScene::sharedLevelScene()->getPlayer();
    if(!player->isDead && !isDead)
    {
        if(player->getBoundingBox().intersectsRect(this->getBoundingBox()))
        {
            player->downHp();
        }
    }
}

void NewEnemy::enemyShoot()
{
    Point playerPoint = LevelScene::sharedLevelScene()->getPlayer()->getPosition();
    if(way==0 || way==3 || way==6 || way==7)
    {
        way = 0;
    }
    switch(way)
    {
        case 0:
        {
            this->shootOne(playerPoint);
            break;
        }
        case 1:
        {
            LevelScene::sharedLevelScene()->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2, this->getPosition(), playerPoint, 1));
            break;
        }
        case 2:
        {
            int randomType = CCRANDOM_0_1() *20;
            if(randomType>=0 && randomType<10)
            {
                randomType = 1;
            }else
            {
                randomType = 2;
            }
            switch(randomType)
            {
                case 1:
                {
                    this->schedule(schedule_selector(NewEnemy::shootMany));
                    break;
                }
                case 2:
                {
                    this->shootFive(playerPoint);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 4:
        {
            LevelScene::sharedLevelScene()->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2, this->getPosition(), playerPoint, 6));
            break;
        }
        case 5:
        {
            LevelScene::sharedLevelScene()->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2, this->getPosition(), playerPoint, 5));
            break;
        }
    }
}

void NewEnemy::shootMany(float f)
{
    Point playerPoint = LevelScene::sharedLevelScene()->getPlayer()->getPosition();
    shootManyCount++;
    if(shootManyCount%12==0)
    {
        LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, this->getPosition(), playerPoint, 1));
        LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, this->getPosition(), playerPoint, 3));
        LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, this->getPosition(), playerPoint, 4));
    }
    if(shootManyCount>90)
    {
        shootManyCount = 0;
        this->unschedule(schedule_selector(NewEnemy::shootMany));
    }
}

void NewEnemy::shootFive(Point playerPoint)
{
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, Vec2(this->getPositionX(), this->getPositionY()+10), playerPoint, 2));
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, Vec2(this->getPositionX()+10, this->getPositionY()+3), playerPoint, 2));
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, Vec2(this->getPositionX()-10, this->getPositionY()+3), playerPoint, 2));
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, Vec2(this->getPositionX()-6, this->getPositionY()-6), playerPoint, 2));
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, Vec2(this->getPositionX()+6, this->getPositionY()-6), playerPoint, 2));
}

void NewEnemy::shootOne(Point playerPoint)
{
    LevelScene::sharedLevelScene()->enemyBatchNode->addChild(EnemyBullet::createBullet("enemy_bullet.png", 2.5, this->getPosition(), playerPoint, 2));
}

void NewEnemy::enemyDead()
{
    //��ը��Ч
	if(enemyType == 4)
    {
        SimpleAudioEngine::getInstance()->playEffect("effect_bigBoom.wav");
    }
	else
    {
        SimpleAudioEngine::getInstance()->playEffect("effect_boom.mp3");
    }
    
    //��ը����Ч��
    ParticleSystemQuad* particle = ParticleSystemQuad::create("particle_boom.plist");
    particle->setPosition(this->getPosition());//�ֵ�λ��
    particle->setAutoRemoveOnFinish(true);//�Զ��ͷ�
    LevelScene::sharedLevelScene()->addChild(particle);//��ӵ���layer
    //���ӷ���
    LevelScene::sharedLevelScene()->getPlayer()->addScore(scoreValue);
    //���ɱ����
    LevelScene::sharedLevelScene()->getPlayer()->addKillCount(1);
    
    if(enemyType ==4)
    {
        auto size = Director::getInstance()->getWinSize();
        Gems *gem = Gems::createGem("hp.png",1);
        gem->setPosition(Vec2(size.width/2, size.height/2));
        LevelScene::sharedLevelScene()->addChild(gem,9);
    }
    
    //�ӵ������齫�������ĵй�ɾ��
    Vector<NewEnemy*> array = LevelScene::sharedLevelScene()->getArrayForEnemy();
	array.eraseObject(this);
    //ɾ���й�
    this->removeFromParentAndCleanup(true);
	isDead = true;
}
