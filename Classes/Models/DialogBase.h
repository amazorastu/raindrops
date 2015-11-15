#pragma once

#include "cocos2d.h"
#include "Others/Global.h"
#include "Others/TextBase.h"

enum GameType
{
	gameTypeChallenge = 1,
	gameTypeRelax = 2
};

enum DialogType
{
	dialogTypeGameOver = 1
};

class DialogBase : public cocos2d::Sprite
{
public:
	DialogBase();
	~DialogBase();

public:
	CREATE_FUNC(DialogBase);
	virtual bool init();

	static DialogBase* createDialog(GameType, DialogType, int);

private:
	int score;
	int scoreShown;
	char scoreString[10];

	cocos2d::Label* scoreLabel;

	void update(float);
	void buttonCallback(cocos2d::Ref*);

};