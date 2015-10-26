#include "AudioManager.h"

USING_NS_CC;
using namespace CocosDenshion;

void AudioManager::playSoundEffect(SoundEffectName pName)
{
	char soundEffectPath[20];
	switch (pName)
	{
	case SoundEffectClear:
		sprintf(soundEffectPath, "se/Clear%d.wav", random(0, 2));
		SimpleAudioEngine::getInstance()->playEffect(soundEffectPath);
		break;
	default:
		break;
	}
}