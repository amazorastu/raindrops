#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

enum SoundEffectName
{
	SoundEffectClear = 1
};

class AudioManager
{
public:
	static void playSoundEffect(SoundEffectName);
};