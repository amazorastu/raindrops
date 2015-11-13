#pragma once

#include "cocos2d.h"

#include "Others/Global.h"

struct intPoint{
	int x;
	int y;
};

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

	bool addRune(int rune);
	
	int getRune(){ return m_Rune; }
private:
	int m_Type,m_Rune;
	bool m_Selected;
	cocos2d::Sprite* m_BoarderSprite;
	cocos2d::Sprite* m_CoreSprite;
}; 