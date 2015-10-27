#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Models/DropsBase.h"
#include "Models/NormalMap.h"
#include "Layers/GameLayer.h"

class GameCoreLayer : public cocos2d::LayerColor
{
private:
	NormalMap* map;
	cocos2d::EventListenerTouchOneByOne* eventTouch;
	cocos2d::EventDispatcher* dispatcher;
	void update(float);
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event*);
	virtual void onEnterTransitionDidFinish();

	bool isTouched;
public:
	GameCoreLayer();
	~GameCoreLayer();
	CREATE_FUNC(GameCoreLayer);
	static cocos2d::Scene* createScene();
};
