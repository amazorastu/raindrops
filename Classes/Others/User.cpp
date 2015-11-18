#include "User.h"

USING_NS_CC;

User* User::instance;

User::User()
{

}

User* User::getInstance()
{
	if (!instance)
	{
		instance = new User();
		instance->load();
	}

	return instance;
}

void User::saveHighScoreForChallengeMode(int newScore)
{
	for (int i = 0; i < 5; i++)
	{
		if (newScore>challengeScore[i])
		{
			int temp = newScore;
			newScore = challengeScore[i];
			challengeScore[i] = temp;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5; j++)
		{
			if (challengeScore[j]>challengeScore[i])
			{
				int temp = challengeScore[j];
				challengeScore[j] = challengeScore[i];
				challengeScore[i] = temp;
			}
		}
	}
	instance->save();
}
void User::saveHighScoreForRelaxMode(int newScore)
{         
	for (int i = 0; i < 5; i++)
	{
		if (newScore>relaxScore[i])
		{
			int temp = newScore;
			newScore = relaxScore[i];
			relaxScore[i] = temp;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5; j++)
		{
			if (relaxScore[j]>relaxScore[i])
			{
				int temp = relaxScore[j];
				relaxScore[j] = relaxScore[i];
				relaxScore[i] = temp;
			}
		}
	}
	instance->save();
}

int* User::getHighScoreListForChallengeMode()
{
	return challengeScore;
}
int* User::getHighScoreListForRelaxMode()
{
	return relaxScore;
}

void User::save()
{
	UserDefault::getInstance()->setIntegerForKey("challengeScore0", challengeScore[0]);
	UserDefault::getInstance()->setIntegerForKey("challengeScore1", challengeScore[1]);
	UserDefault::getInstance()->setIntegerForKey("challengeScore2", challengeScore[2]);
	UserDefault::getInstance()->setIntegerForKey("challengeScore3", challengeScore[3]);
	UserDefault::getInstance()->setIntegerForKey("challengeScore4", challengeScore[4]);

	UserDefault::getInstance()->setIntegerForKey("relaxScore0", relaxScore[0]);
	UserDefault::getInstance()->setIntegerForKey("relaxScore1", relaxScore[1]);
	UserDefault::getInstance()->setIntegerForKey("relaxScore2", relaxScore[2]);
	UserDefault::getInstance()->setIntegerForKey("relaxScore3", relaxScore[3]);
	UserDefault::getInstance()->setIntegerForKey("relaxScore4", relaxScore[4]);
}
void User::load()
{
	challengeScore[0] = UserDefault::getInstance()->getIntegerForKey("challengeScore0");
	challengeScore[1] = UserDefault::getInstance()->getIntegerForKey("challengeScore1");
	challengeScore[2] = UserDefault::getInstance()->getIntegerForKey("challengeScore2");
	challengeScore[3] = UserDefault::getInstance()->getIntegerForKey("challengeScore3");
	challengeScore[4] = UserDefault::getInstance()->getIntegerForKey("challengeScore4");

	relaxScore[0] = UserDefault::getInstance()->getIntegerForKey("relaxScore0");
	relaxScore[1] = UserDefault::getInstance()->getIntegerForKey("relaxScore1");
	relaxScore[2] = UserDefault::getInstance()->getIntegerForKey("relaxScore2");
	relaxScore[3] = UserDefault::getInstance()->getIntegerForKey("relaxScore3");
	relaxScore[4] = UserDefault::getInstance()->getIntegerForKey("relaxScore4");
}