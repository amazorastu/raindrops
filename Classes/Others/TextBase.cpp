#include "TextBase.h"

USING_NS_CC;

Label* TextBase::createText(TextType textType)
{
	Label *lb = Label::createWithTTF("", "fonts/simhei.ttf", 60.0f);
	lb->setTextColor(Color4B::BLACK);
	if (Global::getLanguage() == LanguageType::CHINESE)
	{
		switch (textType)
		{
		case textTypeChallenge:
			lb->setString("挑战");
			break;
		case textTypeZen:
			lb->setString("休闲");
			break;
		case textTypeAchievement:
			lb->setString("成就");
			break;
		case textTypeShop:
			lb->setString("商店");
			break;
		case textTypeHome:
			lb->enableOutline(Color4B::WHITE, 3.0f);
			lb->setString("菜单");
			break;
		case textTypeContinue:
			lb->enableOutline(Color4B::WHITE, 3.0f);
			lb->setString("继续");
			break;
		default:
			break;
		}
	}
	else
	{
		switch (textType)
		{
		case textTypeChallenge:
			lb->setString("Challenge");
			break;
		case textTypeZen:
			lb->setString("Relax");
			break;
		case textTypeAchievement:
			lb->setString("Achievement");
			break;
		case textTypeShop:
			lb->setString("Shop");
			break;
		case textTypeHome:
			lb->enableOutline(Color4B::WHITE, 3.0f);
			lb->setString("Home");
			break;
		case textTypeContinue:
			lb->enableOutline(Color4B::WHITE, 3.0f);
			lb->setString("Continue");
			break;
		default:
			break;
		}
	}
	return lb;
}

std::string TextBase::WStrToUTF8(const std::wstring& src)
{
	std::string dest;
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
		{
			dest.push_back((char)w);
		}
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
	return dest;
}
