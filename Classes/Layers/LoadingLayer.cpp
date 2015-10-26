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
	if (!LayerColor::initWithColor(Color4B(230, 255, 255, 255)))
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/texture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("drops/default/drops.plist");

	Global::init();

	

	return true;
}

void LoadingLayer::onEnterTransitionDidFinish()
{
	this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([&]{Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, MenuLayer::createScene())); }), nullptr));
}
