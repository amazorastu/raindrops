#pragma once
#include "cocos2d.h"
#include "Models/DropsBase.h"
#include "Others/Global.h"
#include "Others/AudioManager.h"

class NormalMap
{
private:
	const static int m_MapSize = 7;
	cocos2d::Node* m_ShowNode;
	DropsBase* map[m_MapSize][m_MapSize];
	std::stack<intPoint> dropsLinked;
	std::stack<cocos2d::DrawNode*> linesLinked;
	cocos2d::DrawNode* touchLine;
	int m_Score = 0;
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
	//获得一个点(x,y) 方向d上的点
	intPoint getDropByDirect(int x, int y, int d);
	//用来调整地图
	void dropDown();
	//获取地图上Drop的坐标
	cocos2d::Point getDropPos(int x, int y);
	//获得(x,y)的点
	DropsBase* getDrop(int x, int y);
	//判断mx，my是否在地图的Drop上，如果是，返回该Drop的x,y
	//如果不是，返回-1,-1
	int isInMap(float, float);
	//判断x，y是否在地图的Drop上
	bool isInMap(int x, int y);
	//判断两个点是否可连
	bool isNear(int x1, int y1, int x2, int y2);
	//拖动事件
	void DragOn(float, float);
	//抬起事件
	void DragUp(float, float);
	//获得最大宽度的一半
	float getHalfMaxWidth();
	//清楚分数
	void clearScore();
	//获得分数
	int getScore();
	//获得是否是环路
	bool getIsRound();
	//清楚当前颜色的点
	void clearColor(cocos2d::Color4B color);
	cocos2d::Color4B getCurrentColor();
	void clearRune(int x, int y);
	std::stack<intPoint> getCrossLine(int x, int y);
	int clearSelectDrops();
	void randomRune();
};