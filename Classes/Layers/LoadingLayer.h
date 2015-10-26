#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Layers/MenuLayer.h"

class LoadingLayer : public cocos2d::LayerColor
{
public:
	LoadingLayer();
	~LoadingLayer();

public:
	CREATE_FUNC(LoadingLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();

private:
	virtual void onEnterTransitionDidFinish();

	cocos2d::Sprite *logo;
};