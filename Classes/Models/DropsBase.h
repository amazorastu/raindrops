#pragma once

#include "cocos2d.h"

#include "Others/Global.h"

class DropsBase
{
public:
	DropsBase();

	~DropsBase();

	void remove();

	void setParent(cocos2d::Node* parent);

	void runAnimation(cocos2d::Action* action);

	void stopAndRunAnimation(cocos2d::Action* action);

	void randomType();

	void setPos(cocos2d::Point pos);

	cocos2d::Point getPos();

	int getType();

	float getWidth();

	void setType(int type);

	cocos2d::Color4B getColor();

	void setSelected(bool selected);

	bool getSelected();

private:
	int m_Type;
	bool m_Selected;
	cocos2d::Sprite* m_BoarderSprite;
	cocos2d::Sprite* m_CoreSprite;
}; 