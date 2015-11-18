#pragma once

#include "cocos2d.h"

class User
{
protected:
	User();

public:
	static User* getInstance();

	void saveHighScoreForChallengeMode(int);
	void saveHighScoreForRelaxMode(int);

	int* getHighScoreListForChallengeMode();
	int* getHighScoreListForRelaxMode();


private:
	static User* instance;
	void save();
	void load();

	int challengeScore[5];
	int relaxScore[5];
};