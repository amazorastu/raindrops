#pragma once

#include "cocos2d.h"

#include "Models/DropsBase.h"
#include "Others/Global.h"
#include "Others/AudioManager.h"

struct intPoint{
	int x;
	int y;
};

class NormalMap
{
private:
	const static int m_MapSize=7;
	cocos2d::Node* m_ShowNode;
	DropsBase* map[m_MapSize][m_MapSize];
	std::stack<intPoint> dropsLinked;
	std::stack<cocos2d::DrawNode*> linesLinked;
	cocos2d::DrawNode* touchLine;
	int m_Score=0;
	float spaceHeight;
	float spaceWidth;
	float startHeight;
	float startWidth;

	bool isRound = false;
	cocos2d::Color4B currentColor;

	cocos2d::Action* creatDropAnimation(cocos2d::Point targetPoint, float height);
public:
	NormalMap(cocos2d::Node* showNode, float w, float h);
	//用于填充地图
	void fillMap();
	//用来调整地图
	void dropDown();
	//获取地图上Drop的坐标
	cocos2d::Point getDropPos(int x, int y);
	DropsBase* getDrop(int x, int y);
	//判断mx，my是否在地图的Drop上，如果是，返回该Drop的x,y
	//如果不是，返回-1,-1
	int isInMap(float, float);
	bool isNear(int x1, int y1, int x2, int y2);
	void DragOn(float, float);
	void DragUp(float, float);
	float getHalfMaxWidth();
	void clearScore();
	int getScore();
	bool getIsRound();
	void clearColor();
	cocos2d::Color4B getCurrentColor();
};