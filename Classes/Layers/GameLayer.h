#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Layers/MenuLayer.h"
#include "Layers/GameCoreLayer.h"

class GameLayer : public cocos2d::LayerColor
{
public:
	GameLayer();
	~GameLayer();

public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	static cocos2d::Scene* createScene();
	
	void setTimeAsLife(int Time);
	void setMovesAsLife(int moves);

	void setScore(int);
	void setLife(int);
	int getScore();
	int getLife();

	void update(float);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);


private:
	virtual void onEnterTransitionDidFinish();

	bool isTimerOn;

	cocos2d::Sprite *dockUp;
	cocos2d::Sprite *dockDown;

	cocos2d::Label *scoreLabel;
	cocos2d::Label *lifeLabel;
	char scoreString[10];
	char lifeString[10];
	int scoreShown;
	int lifeShown;
	int score;
	int life;
};