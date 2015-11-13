#pragma once

#include "cocos2d.h"

class Global
{
protected:
	Global();

public:
	static void init();

public:
	static cocos2d::Size getWinSize();
	static cocos2d::Vec2 getPointCenter();
	static float getWinSizeX();
	static float getWinSizeY();
	static float getWinSizeHalfX();
	static float getWinSizeHalfY();
	static cocos2d::LanguageType getLanguage();
	static std::string getDropRes(int tag);
	static std::string getRuneRes(int rune);

private:
	static cocos2d::Size winSize;
	static cocos2d::Vec2 pointCenter;
	static float winSizeX;
	static float winSizeY;
	static float winSizeHalfX;
	static float winSizeHalfY;
	static cocos2d::LanguageType language;

	
	
};