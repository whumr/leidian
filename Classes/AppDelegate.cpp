//
//  PlaneDemoAppDelegate.cpp
//  PlaneDemo
//
//  Created by Himi on 12-10-21.
//  Copyright __MyCompanyName__ 2012Äê. All rights reserved.
//

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "HMenu.h"
#include "HWorld.h"
#include "LevelScene.h"
using namespace CocosDenshion;
USING_NS_CC;

extern int sceneLevel;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    Director *pDirector = Director::getInstance();
	auto glview = pDirector->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");        
		glview->setFrameSize(512,768);
		glview->setFrameZoomFactor(0.6f);
		pDirector->setOpenGLView(glview);
    }

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    Scene *pScene = HMenu::scene();

    // run
    pDirector->runWithScene(pScene);

	Configuration::getInstance()->loadConfigFile("strings.plist");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
//    Director::getInstance()->pause();
//
//    // if you use SimpleAudioEngine, it must be pause
//     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    switch(sceneLevel)
    {
        case 0:
        {
            if(!HWorld::sharedWorld()->getChildByTag(9999))
            {
                HWorld::sharedWorld()->doPause(NULL);
            }
            break;
        }
        case 1:
        {
            if(!LevelScene::sharedLevelScene()->getChildByTag(9999))
            {
                LevelScene::sharedLevelScene()->doPause(NULL);
            }
            break;
        }
        case 2:
        {
            if(!LevelScene::sharedLevelScene()->getChildByTag(9999))
            {
                LevelScene::sharedLevelScene()->doPause(NULL);
            }
            break;
        }
        case 9999:
        {
            Director::getInstance()->pause();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        default:
            break;
    }    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    if(sceneLevel==9999)
    {
        Director::getInstance()->resume();
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
