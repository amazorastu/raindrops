#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Others/TextBase.h"
#include "Others/User.h"

class AchievementLayer : public cocos2d::LayerColor
{
public:
	AchievementLayer();
	~AchievementLayer();

public:
	CREATE_FUNC(AchievementLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);

public:
	

private:
	virtual void onEnterTransitionDidFinish();

	cocos2d::Label* scoreLabel;
};
