#include "LoadingLayer.h"

USING_NS_CC;

LoadingLayer::LoadingLayer()
{

}

LoadingLayer::~LoadingLayer()
{

}

Scene* LoadingLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = LoadingLayer::create();
	sc->addChild(ly);
	return sc;
}

bool LoadingLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 225, 200, 255)))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/texture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("drops/default/drops.plist");

	if (!UserDefault::getInstance()->getIntegerForKey("challengeScore0"))
		UserDefault::getInstance()->setIntegerForKey("challengeScore0", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("challengeScore1"))
		UserDefault::getInstance()->setIntegerForKey("challengeScore1", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("challengeScore2"))
		UserDefault::getInstance()->setIntegerForKey("challengeScore2", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("challengeScore3"))
		UserDefault::getInstance()->setIntegerForKey("challengeScore3", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("challengeScore4"))
		UserDefault::getInstance()->setIntegerForKey("challengeScore4", 0);

	if (!UserDefault::getInstance()->getIntegerForKey("relaxScore0"))
		UserDefault::getInstance()->setIntegerForKey("relaxScore0", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("relaxScore1"))
		UserDefault::getInstance()->setIntegerForKey("relaxScore1", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("relaxScore2"))
		UserDefault::getInstance()->setIntegerForKey("relaxScore2", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("relaxScore3"))
		UserDefault::getInstance()->setIntegerForKey("relaxScore3", 0);
	if (!UserDefault::getInstance()->getIntegerForKey("relaxScore4"))
		UserDefault::getInstance()->setIntegerForKey("relaxScore4", 0);


	Global::init();

	

	return true;
}

void LoadingLayer::onEnterTransitionDidFinish()
{
	this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([&]{Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, MenuLayer::createScene())); }), nullptr));
}
