#include "DropsBase.h"

USING_NS_CC;

DropsBase::DropsBase()
{
	m_CoreSprite = NULL;
	m_BoarderSprite = NULL;
	m_Selected = false;
	m_Rune = -1;
}
DropsBase::~DropsBase(){}
bool DropsBase::addRune(int rune)
{
	if (m_Rune != -1)return false;
	m_Rune = rune;
	auto sprite = Sprite::createWithSpriteFrameName(Global::getRuneRes(rune));
	Color3B newColor = (Color3B)getColor();
	newColor.r = 255 - newColor.r;
	newColor.g = 255 - newColor.g;
	newColor.b = 255 - newColor.b;
	sprite->setColor(newColor);
	m_CoreSprite->addChild(sprite);
	sprite->setPosition(m_CoreSprite->getContentSize().width / 2, m_CoreSprite->getContentSize().height / 2);
	return true;
}
void DropsBase::remove()
{
	m_CoreSprite->runAction(
		Sequence::create(ScaleTo::create(0.2f, 0),
		CallFunc::create([&]{
		m_CoreSprite->removeFromParentAndCleanup(true);	}
	), NULL));
}

void DropsBase::setParent(Node* parent){
	parent->addChild(m_CoreSprite);
}

void DropsBase::runAnimation(cocos2d::Action* action){
	m_CoreSprite->runAction(action);
}

void DropsBase::stopAndRunAnimation(cocos2d::Action* action){
	m_CoreSprite->stopAllActions();
	m_CoreSprite->runAction(action);
}

void DropsBase::randomType(){
	setType(random(1, 5));
}

void DropsBase::setPos(cocos2d::Point pos){
	m_CoreSprite->setPosition(pos);
}
cocos2d::Point DropsBase::getPos()
{
	return m_CoreSprite->getPosition();
}

int DropsBase::getType()
{
	return m_Type;
}
float DropsBase::getWidth()
{
	return m_CoreSprite->getContentSize().width;
}
void DropsBase::setType(int type){
	if (type < 0){ m_Type = -1; return; }
	m_Type = type;
	if (m_CoreSprite)m_CoreSprite->removeFromParentAndCleanup(true);
	m_CoreSprite = Sprite::createWithSpriteFrameName(Global::getDropRes(type));
	//m_CoreSprite->setScale(1.0f);


	if (m_BoarderSprite)m_BoarderSprite->removeFromParentAndCleanup(true);
	m_BoarderSprite = Sprite::createWithSpriteFrameName(Global::getDropRes(type));
	//m_BoarderSprite->setScale(1.0f);
	m_BoarderSprite->setPosition(m_CoreSprite->getContentSize().width / 2, m_CoreSprite->getContentSize().height / 2);
	m_BoarderSprite->setColor(m_CoreSprite->getColor());
	m_BoarderSprite->setOpacity(150);
	m_CoreSprite->addChild(m_BoarderSprite);
}
cocos2d::Color4B DropsBase::getColor()
{
	switch (m_Type)
	{
	case 0:
		return Color4B(255, 255, 255, 180);
	case 1:
		return Color4B(255, 64, 0, 180);
	case 2:
		return Color4B(255, 196, 0, 180);
	case 3:
		return Color4B(182, 255, 128, 180);
	case 4:
		return Color4B(0, 204, 255, 180);
	case 5:
		return Color4B(255, 128, 255, 180);
	case 6:
		return Color4B(29, 32, 136, 180);
	case 7:
		return Color4B(89, 73, 63, 180);
	case 8:
		return Color4B(0, 115, 8, 180);
	}
	return Color4B(0, 0, 0, 0);
}

void DropsBase::setSelected(bool selected)
{
	m_Selected = selected;
	if (m_Selected)
	{
		m_BoarderSprite->runAction(
			RepeatForever::create(
			Sequence::create(ScaleTo::create(0.3f, 1.6f), ScaleTo::create(0.3f, 1.3f), NULL)));
	}
	else
	{
		m_BoarderSprite->stopAllActions();
		m_BoarderSprite->runAction(ScaleTo::create(0.3f, 1.0f));
	}
}

bool DropsBase::getSelected()
{
	return m_Selected;
}
