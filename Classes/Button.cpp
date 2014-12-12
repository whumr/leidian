//
//  Button.cpp
//  PlaneDemo
//
//  Created by ºÂ½¡ on 14-4-28.
//
//

#include "Button.h"

using namespace cocos2d;

Button* Button::createButton(HPlayer* player, HWorld* world)
{
    Button* button = new Button();
    if(button && button->create())
    {
        button->autorelease();
        button->buttonInit(player, world);
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}

void Button::buttonInit(HPlayer* player, HWorld* world)
{
    myPlayer = player;
    myWorld = world;
    this->addJoystick();
    this->addFireButton();
    this->scheduleUpdate();
}

void Button::update(float time)
{
    totalTime += time;
    //A¼üÊÇ·ñ¼¤»î×´Ì¬
	// Continuous fire
	if (fireButton->getIsActive() && totalTime > nextShotTime)
	{
		nextShotTime = totalTime + 0.2f;
        myWorld->autoCreateBullet(0);
	}
	// Allow faster shooting by quickly tapping the fire button.
	if (!fireButton->getIsActive())
	{
        totalTime = 0;
		nextShotTime = 0;
	}
         
    auto winSize = Director::getInstance()->getWinSize();
    //»ñÈ¡Ò¡¸Ë·½Ïò
    auto velocity = joystick->getVelocity() * 10000 * time;
    if(velocity.x != 0 && velocity.y != 0)
    {
        
        myPlayer->setPosition(myPlayer->getPosition().x + velocity.x * time, myPlayer->getPosition().y + velocity.y * time);
        float x = myPlayer->getPositionX();
        float y = myPlayer->getPositionY();
        auto playSize = myPlayer->getContentSize();
        float xMax = winSize.width - playSize.width * 0.5f;
        float yMax = winSize.height - playSize.height * 0.5f;
        if(x > xMax)
        {
            myPlayer->setPositionX(xMax);
        }else if (x < playSize.width * 0.5f)
        {
            myPlayer->setPositionX(playSize.width * 0.5f);
        }
        if(y > yMax)
        {
            myPlayer->setPositionY(yMax);
        }else if(y < playSize.height * 0.5f)
        {
            myPlayer->setPositionY(playSize.height * 0.5f);
        }
    }

}

void Button::addJoystick()
{
    //ÐéÄâÊÖ±ú
    //·½Ïò¼ü
    float stickRadius = 50;
    joystick = new SneakyJoystick();
    joystick->initWithRect(Rect(0, 0, stickRadius, stickRadius));
    joystick->autorelease();
    joystick->setAutoCenter(true);
    joystick->setIsDPad(true);
    joystick->setNumberOfDirections(360);
    //Æ¤·ô
    SneakyJoystickSkinnedBase *skinStick = SneakyJoystickSkinnedBase::create();
    skinStick->setPosition(stickRadius * 1.5f, stickRadius * 1.5f);
    
    skinStick->setBackgroundSprite(Sprite::createWithSpriteFrameName("control_bg.png"));
    skinStick->setThumbSprite(Sprite::createWithSpriteFrameName("cen.png"));
    
    skinStick->setJoystick(joystick);
    this->addChild(skinStick);
}

void Button::addFireButton()
{
    //A¼ü
    float buttonRadius = 50;
    auto screenSize = Director::getInstance()->getWinSize();
    fireButton = new SneakyButton();
    fireButton->initWithRect(Rect(0, 0, buttonRadius, buttonRadius));
    fireButton->setIsHoldable(true);
    //Æ¤·ô
    SneakyButtonSkinnedBase * skinFireButton = SneakyButtonSkinnedBase::create();
    skinFireButton->setPosition(Vec2(screenSize.width - buttonRadius * 1.5f, buttonRadius * 1.5f));
    
    skinFireButton->setDefaultSprite(Sprite::createWithSpriteFrameName("fire_button_default.png"));
    skinFireButton->setPressSprite(Sprite::createWithSpriteFrameName("fire_button_press.png"));
    skinFireButton->setActivatedSprite(Sprite::create("Icon.png"));
    skinFireButton->setDisabledSprite(Sprite::createWithSpriteFrameName("fire_button_default.png"));
    
    skinFireButton->setButton(fireButton);
    this->addChild(skinFireButton);
}
