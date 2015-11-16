#pragma once

#include "cocos2d.h"

#include "Others/Global.h"
#include "Layers/MenuLayer.h"
#include "Models/RelaxMap.h"
#include "Models/DialogBase.h"

class RelaxLayer : public cocos2d::LayerColor
{
public:
	RelaxLayer();
	~RelaxLayer();

public:
	CREATE_FUNC(RelaxLayer);
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
	RelaxMap* map;
	cocos2d::EventListenerTouchOneByOne* eventTouch;
	cocos2d::EventDispatcher* dispatcher;

	void addButtonEvents();
	void addKeyBoardEvents();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event*);
	
	void buttonCallback(cocos2d::Ref*);

	bool isPaused;
	bool isTouched;
	bool isTimerOn;
	bool isGameOver;

	void showDialog();
	void hideDialog();
	void showGameOver();
	cocos2d::LayerColor *dialog;

	cocos2d::Sprite *dockUp;
	cocos2d::Sprite *dockDown;

	cocos2d::Sprite *background;

	cocos2d::Label *scoreLabel;
	cocos2d::Label *lifeLabel;
	char scoreString[10];
	char lifeString[10];
	int scoreShown;
	int lifeShown;
	int score;
	int life;
};
