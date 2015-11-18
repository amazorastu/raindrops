#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Others/TextBase.h"
#include "Layers/GameLayer.h"
#include "Layers/RelaxLayer.h"
#include "Layers/AchievementLayer.h"

class MenuLayer : public cocos2d::LayerColor
{
public:
	MenuLayer();
	~MenuLayer();

public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);


private:
	void buttonCallback(cocos2d::Ref*);
	virtual void onEnterTransitionDidFinish();

	bool isActive;

	void showMenu();
	void hideMenu();

	cocos2d::Sprite *logo;

	cocos2d::SpriteFrame *frame;
	cocos2d::Menu *menu;
	cocos2d::MenuItemImage *button[4];
	cocos2d::Label *label[4];


};
