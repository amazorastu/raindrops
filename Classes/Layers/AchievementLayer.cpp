#include "AchievementLayer.h"

USING_NS_CC;

AchievementLayer::AchievementLayer()
{

}
AchievementLayer::~AchievementLayer()
{

}

bool AchievementLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 225, 200, 255)))
	{
		return false;
	}

	char scoreString[10];
	for (int i = 0; i < 5; i++)
	{
		scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 100.0f);
		scoreLabel->setTextColor(Color4B(0, 0, 0, 255));
		scoreLabel->setPosition(Global::getWinSizeHalfX()*0.5f, Global::getWinSizeY() - 400.0f - 200.0f*i);
		this->addChild(scoreLabel);
		sprintf(scoreString, "%d", *(User::getInstance()->getHighScoreListForChallengeMode() + i));
		scoreLabel->setString(scoreString);
	}
	for (int i = 0; i < 5; i++)
	{
		scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 100.0f);
		scoreLabel->setTextColor(Color4B(0, 0, 0, 255));
		scoreLabel->setPosition(Global::getWinSizeX()*0.75f, Global::getWinSizeY() - 400.0f - 200.0f*i);
		this->addChild(scoreLabel);
		sprintf(scoreString, "%d", *(User::getInstance()->getHighScoreListForRelaxMode() + i));
		scoreLabel->setString(scoreString);
	}

	auto label = TextBase::createText(textTypeChallengeMode);
	label->setPosition(Global::getWinSizeHalfX()*0.5f, Global::getWinSizeY() - 200.0f);
	this->addChild(label);

	label = TextBase::createText(textTypeRelaxMode);
	label->setPosition(Global::getWinSizeX()*0.75f, Global::getWinSizeY() - 200.0f);
	this->addChild(label);


	return true;
}

void AchievementLayer::onEnterTransitionDidFinish()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(AchievementLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

Scene* AchievementLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = AchievementLayer::create();
	sc->addChild(ly);
	return sc;
}

void AchievementLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->popScene();
	}
}