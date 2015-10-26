#include "Global.h"

USING_NS_CC;

Size Global::winSize;
float Global::winSizeX;
float Global::winSizeY;
float Global::winSizeHalfX;
float Global::winSizeHalfY;
Vec2 Global::pointCenter;
LanguageType Global::language;

Global::Global()
{

}

void Global::init()
{
	winSize = Director::getInstance()->getWinSize();
	winSizeX = winSize.width;
	winSizeY = winSize.height;
	winSizeHalfX = winSizeX*0.5f;
	winSizeHalfY = winSizeY*0.5f;
	pointCenter = Vec2(winSizeHalfX, winSizeHalfY);
	language = Application::getInstance()->getCurrentLanguage();
}

std::string Global::getDropRes(int tag)
{
	cocos2d::String a;
	a.appendWithFormat("Drop%d.png", tag);
	return a._string;
}


Size Global::getWinSize()
{
	return winSize;
}
Vec2 Global::getPointCenter()
{
	return pointCenter;
}
float Global::getWinSizeX()
{
	return winSizeX;
}
float Global::getWinSizeY()
{
	return winSizeY;
}
float Global::getWinSizeHalfX()
{
	return winSizeHalfX;
}
float Global::getWinSizeHalfY()
{
	return winSizeHalfY;
}
LanguageType Global::getLanguage()
{
	return language;
}