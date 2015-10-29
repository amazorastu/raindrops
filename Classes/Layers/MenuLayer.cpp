#include "MenuLayer.h"

USING_NS_CC;

MenuLayer::MenuLayer() : isActive(false)
{

}

MenuLayer::~MenuLayer()
{

}

Scene* MenuLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = MenuLayer::create();
	sc->addChild(ly);
	return sc;
}

bool MenuLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 200, 145, 255)))
	{
		return false;
	}


	//create logo -p
	logo = Sprite::create();
	logo->setPosition(Global::getPointCenter());
	this->addChild(logo);
	if (Global::getLanguage() == LanguageType::CHINESE)
	{
		logo->setSpriteFrame("Logo_chs.png");
	}
	else logo->setSpriteFrame("Logo_eng.png");
	

	button[0] = MenuItemImage::create("", "", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button[1] = MenuItemImage::create("", "", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button[2] = MenuItemImage::create("", "", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	button[3] = MenuItemImage::create("", "", CC_CALLBACK_1(MenuLayer::buttonCallback, this));
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button0.png");
	button[0]->setNormalSpriteFrame(frame);
	button[0]->setSelectedSpriteFrame(frame);
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button1.png");
	button[1]->setNormalSpriteFrame(frame);
	button[1]->setSelectedSpriteFrame(frame);
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button2.png");
	button[2]->setNormalSpriteFrame(frame);
	button[2]->setSelectedSpriteFrame(frame);
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button3.png");
	button[3]->setNormalSpriteFrame(frame);
	button[3]->setSelectedSpriteFrame(frame);

	button[0]->setPosition(Vec2(-Global::getWinSizeX(), 800.0f));
	button[1]->setPosition(Vec2(Global::getWinSizeX(), 800.0f));
	button[2]->setPosition(Vec2(-Global::getWinSizeX(), -800.0f));
	button[3]->setPosition(Vec2(Global::getWinSizeX(), -800.0f));
	for (int i = 0; i < 4; i++)
	{
		button[i]->setOpacity(0.0f);
	}


	menu = Menu::create(button[0], button[1], button[2], button[3], nullptr);
	menu->setPosition(Global::getPointCenter() - Vec2(0.0f, Global::getWinSizeY()*0.125f));
	this->addChild(menu, 2);


	label[0] = TextBase::createText(textTypeChallenge);
	label[0]->setPosition(menu->getPosition() + Vec2(-250.0f, 60.0f));
	label[0]->setOpacity(0.0f);
	this->addChild(label[0]);

	label[1] = TextBase::createText(textTypeZen);
	label[1]->setPosition(menu->getPosition() + Vec2(250.0f, 60.0f));
	label[1]->setOpacity(0.0f);
	this->addChild(label[1]);

	label[2] = TextBase::createText(textTypeAchievement);
	label[2]->setPosition(menu->getPosition() + Vec2(-250.0f, -440.0f));
	label[2]->setOpacity(0.0f);
	this->addChild(label[2]);

	label[3] = TextBase::createText(textTypeShop);
	label[3]->setPosition(menu->getPosition() + Vec2(250.0f, -440.0f));
	label[3]->setOpacity(0.0f);
	this->addChild(label[3]);

	

	return true;
}

void MenuLayer::onEnterTransitionDidFinish()
{
	isActive = true;
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(MenuLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->showMenu();
}

void MenuLayer::showMenu()
{
	logo->runAction(FadeIn::create(0.5f));
	logo->runAction(ScaleTo::create(0.6f, 1.0f));
	logo->runAction(JumpTo::create(1.0f, Vec2(Global::getWinSizeHalfX(), Global::getWinSizeHalfY()*1.5f), 40.0f, 1));
	button[0]->runAction(EaseBackOut::create(MoveTo::create(0.6f, Vec2(-250.0f, 250.0f))));
	button[1]->runAction(EaseBackOut::create(MoveTo::create(0.6f, Vec2(250.0f, 250.0f))));
	button[2]->runAction(EaseBackOut::create(MoveTo::create(0.6f, Vec2(-250.0f, -250.0f))));
	button[3]->runAction(EaseBackOut::create(MoveTo::create(0.6f, Vec2(250.0f, -250.0f))));
	for (int i = 0; i < 4; i++)
	{
		button[i]->runAction(FadeIn::create(0.4f));
		label[i]->runAction(Sequence::create(DelayTime::create(0.6f), FadeIn::create(1.0f), nullptr));
	}
}

void MenuLayer::hideMenu()
{
	logo->runAction(FadeOut::create(0.5f));
	logo->runAction(ScaleTo::create(0.6f, 0.3f));
	button[0]->runAction(EaseBackIn::create(MoveTo::create(0.4f, Vec2(-Global::getWinSizeX(), 800.0f))));
	button[1]->runAction(EaseBackIn::create(MoveTo::create(0.4f, Vec2(Global::getWinSizeX(), 800.0f))));
	button[2]->runAction(EaseBackIn::create(MoveTo::create(0.4f, Vec2(-Global::getWinSizeX(), -800.0f))));
	button[3]->runAction(EaseBackIn::create(MoveTo::create(0.4f, Vec2(Global::getWinSizeX(), -800.0f))));
	for (int i = 0; i < 4; i++)
	{
		button[i]->runAction(Sequence::create(DelayTime::create(0.2f), FadeOut::create(0.15f), nullptr));
		label[i]->stopAllActions();
		label[i]->runAction(FadeOut::create(0.3f));
	}
}

void MenuLayer::buttonCallback(Ref *ref)
{
	if(isActive == false)return;
	isActive = false;
	this->hideMenu();
	auto b = (MenuItemImage*)ref;
	if (b == button[0])
	{
		this->runAction(
			Sequence::create(DelayTime::create(0.5f),
			CallFunc::create([&]{
				Director::getInstance()->pushScene(
					TransitionCrossFade::create(0.1f, GameLayer::createScene())); }
		),nullptr)); 
	}
	else if (b == button[1]){}
	else if (b == button[2]){}
	else if (b == button[3]){}

	
}

void MenuLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}
