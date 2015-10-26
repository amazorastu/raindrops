#include "GameCoreLayer.h"

USING_NS_CC;

bool GameCoreLayer::init()
{
	if (!Layer::init())
		return false;
	//auto lc = LayerColor::create(Color4B(2, 255, 255, 255), Global::getWinSizeX(), Global::getWinSizeY());
	//lc->setPosition(0, 0);
	//this->addChild(lc);
	map = new NormalMap(this, Global::getWinSizeX(), Global::getWinSizeY());
	eventTouch = EventListenerTouchOneByOne::create();
	eventTouch->onTouchBegan = CC_CALLBACK_2(GameCoreLayer::onTouchBegan, this);
	eventTouch->onTouchMoved = CC_CALLBACK_2(GameCoreLayer::onTouchMoved, this);
	eventTouch->onTouchEnded = CC_CALLBACK_2(GameCoreLayer::onTouchEnded, this);
	dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(eventTouch, this);
	map->fillMap();

	//this->setPosition(Global::getWinSizeHalfX() - map->getHalfMaxWidth(), 0);

	return true;
}

bool GameCoreLayer::onTouchBegan(cocos2d::Touch*, cocos2d::Event*){
	return true;
}
void GameCoreLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event*){
	//map->DragUp(touch->getLocation().x - getPosition().x, touch->getLocation().y - getPosition().y);

	//debug
	int tempScore;
	tempScore = map->DragUp(touch->getLocation().x, touch->getLocation().y);
	((GameLayer*)this->getParent())->setScore(((GameLayer*)this->getParent())->getScore() + tempScore);

}
void GameCoreLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event*){
	//map->DragOn(touch->getLocation().x - getPosition().x, touch->getLocation().y - getPosition().y);
	map->DragOn(touch->getLocation().x, touch->getLocation().y);
}
void GameCoreLayer::onEnterTransitionDidFinish(){

}

GameCoreLayer::GameCoreLayer(){ init(); }
GameCoreLayer::~GameCoreLayer(){}
