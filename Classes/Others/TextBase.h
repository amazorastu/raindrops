#pragma once

#include "cocos2d.h"

#include "Global.h"

enum TextType
{
	textTypeChallenge = 1,
	textTypeZen = 2,
	textTypeAchievement = 3,
	textTypeShop = 4,
	textTypeHome = 5,
	textTypeContinue = 6,
	textTypeChallengeMode = 7,
	textTypeRelaxMode = 8,
};


class TextBase
{
public:
	static cocos2d::Label* createText(TextType);

private:
	static std::string WStrToUTF8(const std::wstring& src);
};