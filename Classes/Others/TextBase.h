#pragma once

#include "cocos2d.h"

#include "Global.h"

enum TextType
{
	textTypeChallenge = 1,
	textTypeZen = 2,
	textTypeAchievement = 3,
	textTypeShop = 4
};


class TextBase
{
public:
	static cocos2d::Label* createText(TextType);

private:
	static std::string WStrToUTF8(const std::wstring& src);
};