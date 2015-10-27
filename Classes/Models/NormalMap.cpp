#include "NormalMap.h"

USING_NS_CC;

Action* NormalMap::creatDropAnimation(Point targetPoint, float height)
{
	return Sequence::create(
		JumpTo::create(0.25f, targetPoint, height*0.08f > 25.0f ? height*0.08 : 25.0f, 1),
		JumpTo::create(0.15f, targetPoint, height*0.04f > 15.0f ? height*0.04 : 15.0f, 1),
		JumpTo::create(0.05f, targetPoint, height*0.02f > 5.0f ? height*0.02 : 5.0f, 1),
		nullptr);
}
float NormalMap::getHalfMaxWidth()
{
	return spaceWidth * (m_MapSize + 1)*0.5f;
}
NormalMap::NormalMap(Node* showNode, float w, float h)
{
	m_ShowNode = showNode;
	for (int i = 0; i < m_MapSize; i++)
		for (int j = 0; j < m_MapSize; j++)
			map[i][j] = NULL;


	spaceHeight = 190;
	spaceWidth = 164;

	startHeight = 755;
	startWidth = Global::getWinSizeHalfX() - spaceWidth * 3;

	touchLine = DrawNode::create();
	showNode->addChild(touchLine, 2);

	currentColor = Color4B::WHITE;
}

void NormalMap::fillMap()
{
	for (int i = 0; i < m_MapSize; i++)
	{
		for (int j = 0; j < ((i < (m_MapSize + 1) * 0.5) ? i + (m_MapSize + 1) * 0.5 : m_MapSize - 1 - i + (m_MapSize + 1) * 0.5); j++)
		{
			if (map[i][j] == NULL)
			{
				map[i][j] = new DropsBase();
				auto pos = getDropPos(i, j);
				pos.y += m_ShowNode->getContentSize().height;
				map[i][j]->randomType();
				map[i][j]->setPos(pos);
				map[i][j]->setParent(m_ShowNode);
				map[i][j]->stopAndRunAnimation(
					creatDropAnimation(getDropPos(i, j), m_ShowNode->getContentSize().height));
			}
		}
	}
}

void NormalMap::dropDown()
{
	for (int i = 0; i < m_MapSize; i++)
	{
		int k = 0;
		for (int j = 0; j < ((i < (m_MapSize + 1) * 0.5) ? i + (m_MapSize + 1) * 0.5 : m_MapSize - 1 - i + (m_MapSize + 1) * 0.5); j++)
		{
			if (map[i][j] == NULL)k++;
			else
			{
				if (k != 0)
				{
					map[i][j - k] = map[i][j];
					map[i][j] = NULL;
					float h = map[i][j - k]->getPos().y - getDropPos(i, j - k).y;
					map[i][j - k]->stopAndRunAnimation(
						creatDropAnimation(getDropPos(i, j - k), h));
				}
			}
		}
	}
}

Point NormalMap::getDropPos(int x, int y)
{
	if (x < (m_MapSize + 1) * 0.5)
		return Point(x* spaceWidth + startWidth, startHeight - spaceHeight* x*0.5f + spaceHeight* y);
	else
		return Point(x* spaceWidth + startWidth, startHeight - spaceHeight*0.5f* (m_MapSize - 1 - x) + spaceHeight* y);
}
DropsBase* NormalMap::getDrop(int x, int y){
	return map[x][y];
}

int NormalMap::isInMap(float touchPositionX, float touchPositionY)
{
	int x, y;
	x = (int)((touchPositionX - startWidth) / (spaceWidth - 1) + 0.5f);
	if (x < (m_MapSize + 1) * 0.5)
		y = (int)((touchPositionY - startHeight + spaceHeight*x*0.5f) / spaceHeight + 0.5f);
	else
		y = (int)((touchPositionY - startHeight + spaceHeight*0.5f*(m_MapSize - 1 - x)) / spaceHeight + 0.5f);
	if (x >= m_MapSize || y >= m_MapSize || x < 0 || y < 0 || !map[x][y]) return -1;
	Point p = getDropPos(x, y);

	if (abs(touchPositionX - p.x) < map[x][y]->getWidth() * 0.8f
		&& abs(touchPositionY - p.y) < map[x][y]->getWidth()  *0.8f)
		return x*m_MapSize + y;
	return -1;
}
bool NormalMap::isNear(int x1, int y1, int x2, int y2)
{
	auto p1 = getDropPos(x1, y1);
	auto p2 = getDropPos(x2, y2);
	if (!(x1 == x2 && y1 == y2) &&
		map[x1][y1]->getType() == map[x2][y2]->getType() &&
		abs(p1.x - p2.x) <= spaceWidth*1.5f && abs(p1.y - p2.y) <= spaceWidth*1.5f)
		return true;
	return false;
}
void NormalMap::DragOn(float touchPositionX, float touchPositionY)
{
	int temp = isInMap(touchPositionX, touchPositionY);
	bool drawLine = true;
	if (temp >= 0)
	{
		int x = temp / m_MapSize;
		int y = temp % m_MapSize;
		intPoint pt;
		pt.x = x;
		pt.y = y;
		if (dropsLinked.size() < 1)
		{
			dropsLinked.push(pt);
			map[x][y]->setSelected(true);
		}
		else
		{
			auto p1 = getDropPos(dropsLinked.top().x, dropsLinked.top().y);
			auto p2 = getDropPos(x, y);
			if (isNear(x, y, dropsLinked.top().x, dropsLinked.top().y))
			{
				if (!isRound)
				{
					if (!map[x][y]->getSelected())
					{
						auto node = DrawNode::create();
						node->drawSegment(getDropPos(x, y), getDropPos(dropsLinked.top().x, dropsLinked.top().y),
							8.0f, Color4F(map[x][y]->getColor()));
						linesLinked.push(node);
						m_ShowNode->addChild(node, 2);
						dropsLinked.push(pt);
						map[x][y]->setSelected(true);
						drawLine = false;
					}
					else//��
					{
						intPoint tmp = dropsLinked.top();
						dropsLinked.pop();
						if (x == dropsLinked.top().x&&y == dropsLinked.top().y)
						{
							linesLinked.top()->removeFromParentAndCleanup(true);
							linesLinked.pop();
							map[tmp.x][tmp.y]->setSelected(false);
							drawLine = false;
						}
						else
						{
							dropsLinked.push(tmp);

							auto node = DrawNode::create();
							node->drawSegment(getDropPos(x, y), getDropPos(dropsLinked.top().x, dropsLinked.top().y),
								8.0f, Color4F(map[x][y]->getColor()));
							linesLinked.push(node);
							m_ShowNode->addChild(node, 2);
							currentColor = map[tmp.x][tmp.y]->getColor();
							isRound = true;//回路
							touchLine->runAction(Hide::create());
							drawLine = false;
						}
					}
				}
			}
			else
			{
				if (isRound&&x == dropsLinked.top().x && y == dropsLinked.top().y)
					//if (x == 0 && y == 0)
				{
					linesLinked.top()->removeFromParentAndCleanup(true);
					linesLinked.pop();
					drawLine = false;
					isRound = false;
					touchLine->runAction(Show::create());
				}
			}
		}
	}
	if (dropsLinked.size() > 0 && drawLine &&!isRound)
	{
		touchLine->clear();
		if (map[dropsLinked.top().x][dropsLinked.top().y])
		{
			touchLine->drawSegment(getDropPos(dropsLinked.top().x, dropsLinked.top().y),
				Point(touchPositionX, touchPositionY),
				8.0f, Color4F(map[dropsLinked.top().x][dropsLinked.top().y]->getColor()));

		}

	}
}
void NormalMap::DragUp(float touchPositionX, float touchPositionY)
{
	currentColor = Color4B::WHITE;
	touchLine->clear();
	if (dropsLinked.size() == 1)
	{
		if (map[dropsLinked.top().x][dropsLinked.top().y])
			map[dropsLinked.top().x][dropsLinked.top().y]->setSelected(false);

		dropsLinked.pop();
	}
	else if (dropsLinked.size() > 1)
	{
		//debug-p
		m_Score += dropsLinked.size();
		if (isRound)
			m_Score += dropsLinked.size();
		AudioManager::playSoundEffect(SoundEffectClear);
		while (dropsLinked.size() != 0)
		{
			int x = dropsLinked.top().x;
			int y = dropsLinked.top().y;
			if (map[x][y])map[x][y]->remove();
			map[x][y] = NULL;
			dropsLinked.pop();
		}
		dropDown();
		fillMap();
	}
	while (linesLinked.size() != 0)
	{
		linesLinked.top()->removeFromParentAndCleanup(true);
		linesLinked.pop();
	}
	if (isRound)
	{
		currentColor = Color4B::WHITE;
		isRound = false;
		touchLine->runAction(Show::create());
	}
}

bool NormalMap::getIsRound()
{
	return isRound;
}
Color4B NormalMap::getCurrentColor()
{
	return currentColor;
}

void NormalMap::clearScore(){
	m_Score = 0;
}
int NormalMap::getScore(){
	return m_Score;
}