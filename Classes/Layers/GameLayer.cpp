#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer() : score(0), life(0), scoreShown(0), lifeShown(0), isTimerOn(false)
{

}

GameLayer::~GameLayer()
{

}

Scene* GameLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = GameLayer::create();
	sc->addChild(ly);
	return sc;
}

bool GameLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	
	dockUp = Sprite::createWithSpriteFrameName("Dock.png");
	dockUp->setPosition(Global::getWinSizeHalfX(), Global::getWinSizeY() + 100.0f);
	this->addChild(dockUp, 4);
	


	dockDown = Sprite::createWithSpriteFrameName("Dock.png");
	dockDown->setPosition(Global::getWinSizeHalfX(), -100.0f);
	this->addChild(dockDown, 4);


	scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 100.0f);
	scoreLabel->setPosition(dockUp->getContentSize().width*0.5f + Global::getWinSizeX()*0.25f, dockUp->getContentSize().height*0.5f);
	scoreLabel->setTextColor(Color4B::BLACK);
	dockUp->addChild(scoreLabel, 5);

	lifeLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 100.0f);
	lifeLabel->setPosition(dockUp->getContentSize().width*0.5f - Global::getWinSizeX()*0.25f, dockUp->getContentSize().height*0.5f);
	lifeLabel->setTextColor(Color4B::BLACK);
	dockUp->addChild(lifeLabel, 5);

	auto coreLayer = new GameCoreLayer();
	this->addChild(coreLayer);
	return true;
}

void GameLayer::onEnterTransitionDidFinish()
{
	LayerColor::onEnterTransitionDidFinish();
	dockUp->runAction(MoveBy::create(0.15f, Vec2(0.0f, -200.0f)));
	dockDown->runAction(MoveBy::create(0.15f, Vec2(0.0f, 200.0f)));
	this->setTimeAsLife(3600);
	//this->setMovesAsLife(30);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//this->schedule(SEL_SCHEDULE(&GameLayer::update));
	this->scheduleUpdate();
}

void GameLayer::setTimeAsLife(int time)
{
	life = time;
	lifeShown = life / 60;
	isTimerOn = true;
}

void GameLayer::setMovesAsLife(int moves)
{
	life = moves;
	lifeShown = life;
	isTimerOn = false;
}

void GameLayer::update(float dt)
{
	if (isTimerOn)
	{
		life--;
		lifeShown = life / 60 + 1;
	}
	else
	{
		lifeShown = life;
	}

	if (score > scoreShown)scoreShown++;
	sprintf(scoreString, "%d", scoreShown);
	sprintf(lifeString, "%d", lifeShown);
	scoreLabel->setString(scoreString);
	lifeLabel->setString(lifeString);


	if (lifeShown == 0)
	{
		this->unscheduleUpdate();
		//this->unschedule(SEL_SCHEDULE(&GameLayer::update));
		//todo
	}

}

void GameLayer::setScore(int para)
{
	score = para;
}
void GameLayer::setLife(int para)
{
	life = para;
}
int GameLayer::getScore()
{
	return score;
}
int GameLayer::getLife()
{
	return life;
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		/*this->runAction(
			Sequence::create(DelayTime::create(0.3f),
			CallFunc::create([&]{
				Director::getInstance()->replaceScene(
				TransitionCrossFade::create(1.0f, MenuLayer::createScene())); }), 
				nullptr));*/
		this->runAction(
			Sequence::create(DelayTime::create(0.0f),
			CallFunc::create([&]{
			Director::getInstance()->popScene(); }),nullptr));
	}
}
