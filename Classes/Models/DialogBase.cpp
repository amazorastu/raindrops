#include "DialogBase.h"

USING_NS_CC;

DialogBase::DialogBase() : score(0), scoreShown(0)
{

}
DialogBase::~DialogBase()
{

}

bool DialogBase::init()
{
	if (!Sprite::initWithFile("Background.png"))
	{
		return false;
	}

	this->setColor(Color3B(255, 225, 200));

	scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 400.0f);
	scoreLabel->setPosition(this->getContentSize().width*0.5f, Global::getWinSizeY()*0.75f);
	scoreLabel->setTextColor(Color4B(0, 0, 0, 255));
	scoreLabel->enableOutline(Color4B(255, 255, 255, 255), 5.0f);
	this->addChild(scoreLabel);

	auto button = MenuItemImage::create("", "", CC_CALLBACK_1(DialogBase::buttonCallback, this));
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button5.png");
	button->setNormalSpriteFrame(frame);
	button->setSelectedSpriteFrame(frame);
	button->setPosition(this->getContentSize().width*0.5f, Global::getWinSizeY()*0.25f);
	auto menu = Menu::create(button, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	return true;
}

DialogBase* DialogBase::createDialog(GameType gameType, DialogType dialogType, int pScore)
{
	

	auto dialog = DialogBase::create();
	dialog->setPosition(Global::getPointCenter());
	dialog->setScale(0.2f);
	dialog->runAction(ScaleTo::create(0.3f, 1.0f));

	dialog->score = pScore;
	dialog->scheduleUpdate();

	Label* label;
	switch (gameType)
	{
	case gameTypeChallenge:
		label = TextBase::createText(textTypeChallengeMode);
		User::getInstance()->saveHighScoreForChallengeMode(pScore);
		break;
	case gameTypeRelax:
		label = TextBase::createText(textTypeRelaxMode);
		User::getInstance()->saveHighScoreForRelaxMode(pScore);
		break;
	default:
		break;
	}
	if (label)
	{
		label->setPosition(dialog->getContentSize().width*0.5f, Global::getWinSizeY()*0.65f);
		dialog->addChild(label);
	}

	auto labelBack = TextBase::createText(textTypeBack);
	labelBack->setPosition(dialog->getContentSize().width*0.5f, Global::getWinSizeY()*0.25f - 190.0f);
	dialog->addChild(labelBack);


	return dialog;
}

void DialogBase::update(float dt)
{
	log("[Pruto]%d,%d", score, scoreShown);
	if (scoreShown >= score)
	{
		this->unscheduleUpdate();
	}
	else if (scoreShown < score - 60)
	{
		scoreShown += 10;
	}
	else scoreShown++;

	sprintf(scoreString, "%d", scoreShown);
	scoreLabel->setString(scoreString);
}

void DialogBase::buttonCallback(Ref* ref)
{
	Director::getInstance()->popScene();
}