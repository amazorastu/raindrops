#include "RelaxLayer.h"

USING_NS_CC;

RelaxLayer::RelaxLayer() : score(0), life(0), scoreShown(0), lifeShown(0), isTimerOn(false), isTouched(false),
isPaused(false)
{

}

RelaxLayer::~RelaxLayer()
{

}

Scene* RelaxLayer::createScene()
{
	auto sc = Scene::create();
	auto ly = RelaxLayer::create();
	sc->addChild(ly);
	return sc;
}

bool RelaxLayer::init()
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


	background = Sprite::create("Background.png");
	background->setPosition(Global::getPointCenter());
	background->setOpacity(50.0f);
	this->addChild(background);

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Pause.png");
	auto pause = MenuItemImage::create("", "", CC_CALLBACK_1(GameLayer::buttonCallback, this));
	pause->setScale(0.5f);
	pause->setNormalSpriteFrame(frame);
	pause->setSelectedSpriteFrame(frame);
	pause->setTag(3);
	pause->setPosition(Global::getWinSizeX() - 50.0f, Global::getWinSizeY() - 50.0f);
	pause->setAnchorPoint(Vec2(1.0f, 1.0f));

	auto menu = Menu::create(pause, nullptr);
	menu->setPosition(0.0f, 0.0f);
	this->addChild(menu, 5);

	scoreLabel->setPosition(dockUp->getContentSize().width*0.5f + Global::getWinSizeX()*0.10f, dockUp->getContentSize().height*0.5f);
	lifeLabel->setPosition(dockUp->getContentSize().width*0.5f - Global::getWinSizeX()*0.3f, dockUp->getContentSize().height*0.5f);

#endif




	return true;
}

void RelaxLayer::onEnterTransitionDidFinish()
{
	LayerColor::onEnterTransitionDidFinish();
	dockUp->runAction(MoveBy::create(0.15f, Vec2(0.0f, -200.0f)));
	dockDown->runAction(MoveBy::create(0.15f, Vec2(0.0f, 200.0f)));
	this->setTimeAsLife(3600);
	//this->setMovesAsLife(30);

	
	this->addKeyBoardEvents();
	this->addButtonEvents();


	map = new RelaxMap(this, Global::getWinSizeX(), Global::getWinSizeY());
	map->fillMap();

	//this->schedule(SEL_SCHEDULE(&RelaxLayer::update));
	this->scheduleUpdate();
}

void RelaxLayer::addButtonEvents()
{
	eventTouch = EventListenerTouchOneByOne::create();
	eventTouch->onTouchBegan = CC_CALLBACK_2(RelaxLayer::onTouchBegan, this);
	eventTouch->onTouchMoved = CC_CALLBACK_2(RelaxLayer::onTouchMoved, this);
	eventTouch->onTouchEnded = CC_CALLBACK_2(RelaxLayer::onTouchEnded, this);
	eventTouch->onTouchCancelled = CC_CALLBACK_2(RelaxLayer::onTouchCancelled, this);
	dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(eventTouch, this);
}
void RelaxLayer::addKeyBoardEvents()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(RelaxLayer::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

bool RelaxLayer::onTouchBegan(Touch *touch, Event*){
	if (isTouched)return false;
	isTouched = true;
	return true;
}
void RelaxLayer::onTouchEnded(Touch *touch, Event*){

	map->DragUp(touch->getLocation().x, touch->getLocation().y);
	this->setScore(map->getScore());
	isTouched = false;

}
void RelaxLayer::onTouchMoved(Touch *touch, Event*){
	map->DragOn(touch->getLocation().x, touch->getLocation().y);
}
void RelaxLayer::onTouchCancelled(Touch *touch, Event*){
	isTouched = false;
}

void RelaxLayer::setTimeAsLife(int time)
{
	life = time;
	lifeShown = life / 60;
	isTimerOn = true;
}

void RelaxLayer::setMovesAsLife(int moves)
{
	life = moves;
	lifeShown = life;
	isTimerOn = false;
}

void RelaxLayer::update(float dt)
{
	if (map->getIsRound())
	{
		if (Color3B(map->getCurrentColor()) != background->getColor())
		{
			AudioManager::playSoundEffect(SoundEffectRound);
			background->setColor(Color3B(map->getCurrentColor()));
		}
	}
	else background->setColor(Color3B::WHITE);



	if (isTimerOn)
	{
		life--;
		lifeShown = life / 60 + 1;
		if(life <= 0)lifeShown=0;
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
		Director::getInstance()->popScene();
		//this->unschedule(SEL_SCHEDULE(&RelaxLayer::update));
		//todo
	}

}

void RelaxLayer::showDialog()
{
	if (isPaused || isTouched)return;
	else isPaused = true;

	this->unscheduleUpdate();
	dispatcher->removeEventListener(eventTouch);

	dialog = LayerColor::create(Color4B(0.0f, 0.0f, 0.0f, 128.0f));
	dialog->setOpacity(0.0f);
	this->addChild(dialog, 6);
	dialog->runAction(FadeTo::create(0.15f, 128.0f));

	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button5.png");
	auto b1 = MenuItemImage::create("", "", CC_CALLBACK_1(RelaxLayer::buttonCallback, this));
	b1->setNormalSpriteFrame(frame);
	b1->setSelectedSpriteFrame(frame);
	b1->setPosition(-300.0f, 0.0f);
	b1->setTag(1);
	b1->setOpacity(0.0f);
	b1->runAction(FadeIn::create(0.2f));

	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Button4.png");
	auto b2 = MenuItemImage::create("", "", CC_CALLBACK_1(RelaxLayer::buttonCallback, this));
	b2->setNormalSpriteFrame(frame);
	b2->setSelectedSpriteFrame(frame);
	b2->setPosition(300.0f, 0.0f);
	b2->setTag(2);
	b2->setOpacity(0.0f);
	b2->runAction(FadeIn::create(0.2f));

	auto m = Menu::create(b1, b2, nullptr);
	m->setPosition(Global::getPointCenter());
	dialog->addChild(m, 2);

	auto l1 = TextBase::createText(textTypeHome);
	l1->setPosition(Global::getPointCenter() + Vec2(-300.0f, -190.0f));
	l1->setOpacity(0.0f);
	dialog->addChild(l1, 3);
	l1->runAction(FadeIn::create(0.2f));

	auto l2 = TextBase::createText(textTypeContinue);
	l2->setPosition(Global::getPointCenter() + Vec2(300.0f, -190.0f));
	l2->setOpacity(0.0f);
	dialog->addChild(l2, 3);
	l2->runAction(FadeIn::create(0.2f));
}
void RelaxLayer::hideDialog()
{
	isPaused = false;
	this->scheduleUpdate();
	this->addButtonEvents();

	this->removeChild(dialog, true);
}

void RelaxLayer::buttonCallback(Ref* ref)
{
	auto button = (MenuItemImage*)ref;

	switch (button->getTag())
	{
	case 1:
		Director::getInstance()->popScene();
		break;
	case 2:
		this->hideDialog();
		break;
	default:
		break;
	}
}

void RelaxLayer::setScore(int para)
{
	score = para;
}
void RelaxLayer::setLife(int para)
{
	life = para;
}
int RelaxLayer::getScore()
{
	return score;
}
int RelaxLayer::getLife()
{
	return life;
}

void RelaxLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		/*this->runAction(
			Sequence::create(DelayTime::create(0.3f),
			CallFunc::create([&]{
				Director::getInstance()->replaceScene(
				TransitionCrossFade::create(1.0f, MenuLayer::createScene())); }), 
				nullptr));*/
		//Director::getInstance()->popScene();
		/*this->runAction(
			Sequence::create(DelayTime::create(0.0f),
			CallFunc::create([&]{
			Director::getInstance()->popScene(); }),nullptr));*/
		if (!isPaused)
		{
			this->showDialog();
		}
		else this->hideDialog();
	}
}
