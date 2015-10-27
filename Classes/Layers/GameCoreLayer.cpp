#include "GameCoreLayer.h"

USING_NS_CC;

bool GameCoreLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
		
	this->setOpacity(50.0f);

	map = new NormalMap(this, Global::getWinSizeX(), Global::getWinSizeY());
	eventTouch = EventListenerTouchOneByOne::create();
	eventTouch->onTouchBegan = CC_CALLBACK_2(GameCoreLayer::onTouchBegan, this);
	eventTouch->onTouchMoved = CC_CALLBACK_2(GameCoreLayer::onTouchMoved, this);
	eventTouch->onTouchEnded = CC_CALLBACK_2(GameCoreLayer::onTouchEnded, this);
	eventTouch->onTouchCancelled = CC_CALLBACK_2(GameCoreLayer::onTouchCancelled, this);
	dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(eventTouch, this);
	map->fillMap();

	//this->setPosition(Global::getWinSizeHalfX() - map->getHalfMaxWidth(), 0);

	this->scheduleUpdate();

	return true;
}

bool GameCoreLayer::onTouchBegan(Touch *touch, Event*){
	if (isTouched)return false;
	isTouched = true;
	return true;
}
void GameCoreLayer::onTouchEnded(Touch *touch, Event*){
	
	map->DragUp(touch->getLocation().x, touch->getLocation().y);
	((GameLayer*)this->getParent())->setScore(map->getScore());
	isTouched = false;

}
void GameCoreLayer::onTouchMoved(Touch *touch, Event*){
	map->DragOn(touch->getLocation().x, touch->getLocation().y);
}
void GameCoreLayer::onTouchCancelled(Touch *touch, Event*){
	isTouched = false;
}

void GameCoreLayer::onEnterTransitionDidFinish(){

}

void GameCoreLayer::update(float dt)
{
	if (map->getIsRound())
	{
		if (Color3B(map->getCurrentColor()) != this->getColor())
		{
			AudioManager::playSoundEffect(SoundEffectRound);
			this->setColor(Color3B(map->getCurrentColor()));
		}
	}
	else this->setColor(Color3B::WHITE);
}

GameCoreLayer::GameCoreLayer() :isTouched(false)
{
	init();
}
GameCoreLayer::~GameCoreLayer()
{

}
