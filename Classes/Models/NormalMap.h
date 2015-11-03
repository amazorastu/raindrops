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
	//��������ͼ
	void fillMap();
	//���һ����(x,y) ����d�ϵĵ�
	intPoint getDropByDirect(int x, int y, int d);
	//����������ͼ
	void dropDown();
	//��ȡ��ͼ��Drop������
	cocos2d::Point getDropPos(int x, int y);
	//���(x,y)�ĵ�
	DropsBase* getDrop(int x, int y);
	//�ж�mx��my�Ƿ��ڵ�ͼ��Drop�ϣ�����ǣ����ظ�Drop��x,y
	//������ǣ�����-1,-1
	int isInMap(float, float);
	//�ж�x��y�Ƿ��ڵ�ͼ��Drop��
	bool isInMap(int x, int y);
	//�ж��������Ƿ����
	bool isNear(int x1, int y1, int x2, int y2);
	//�϶��¼�
	void DragOn(float, float);
	//̧���¼�
	void DragUp(float, float);
	//�������ȵ�һ��
	float getHalfMaxWidth();
	//�������
	void clearScore();
	//��÷���
	int getScore();
	//����Ƿ��ǻ�·
	bool getIsRound();
	//�����ǰ��ɫ�ĵ�
	void clearColor(Color3B color);
	cocos2d::Color4B getCurrentColor();
};