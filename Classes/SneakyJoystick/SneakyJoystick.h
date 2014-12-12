#ifndef __SNEAKY_JOYSTICK_H__
#define __SNEAKY_JOYSTICK_H__

#include "cocos2d.h"

class SneakyJoystick : public cocos2d::Node
{
protected:
	float joystickRadiusSq;
	float thumbRadiusSq;
	float deadRadiusSq;

	CC_SYNTHESIZE_READONLY(cocos2d::Point, stickPosition, StickPosition);
	CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
	CC_SYNTHESIZE_READONLY(cocos2d::Point, velocity, Velocity);
	CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
	CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
	CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
	CC_SYNTHESIZE(int, numberOfDirections, NumberOfDirections);

	CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
	CC_SYNTHESIZE_READONLY(float, thumbRadius, ThumbRadius);
	CC_SYNTHESIZE_READONLY(float, deadRadius, DeadRadius);

	virtual ~SneakyJoystick();

	bool initWithRect(cocos2d::Rect rect);
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	void setIsDPad(bool b);
	void setJoystickRadius(float r);
	void setThumbRadius(float r);
	void setDeadRadius(float r);
	virtual bool TouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void TouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void TouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void TouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	void touchDelegateRelease();
	void touchDelegateRetain();

private:
	void updateVelocity(cocos2d::Point point);
	void setTouchRadius();

};
#endif
