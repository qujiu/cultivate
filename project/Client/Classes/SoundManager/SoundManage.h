#ifndef __SOUND_MANAGE_H__
#define __SOUND_MANAGE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SoundID.h"
#include "Common/Common.h"

using namespace cocos2d;
using namespace CocosDenshion;

class SoundManage :public sup::Singleton<SoundManage, Ref>
{
private:
	SINGLETON_FRIEND_SUB(SoundManage, Ref);
	SoundManage(void);
	~SoundManage(void);

private:
	bool m_isMusicOn;
	bool m_isSoundOn;
	unsigned int m_nSoundId;
	bool m_isLoop;
	RES_SOUND_ID m_nSoundID;
	RES_SOUND_ID m_MusicID;
public:

	bool isMusicOn(void);
	void setMusicOn(bool isOn);

	bool isSoundOn(void);
	void setSoundOn(bool isOn);

	void playMusic();
	void playMusic(RES_SOUND_ID soundID);
	void stopMusic();
	void setBackgroundMusicVolume(float volume);
	float getBackgroundMusicVolume();


	void playSound(RES_SOUND_ID soundID, bool isSave = false, bool isLoop = false);
	void stopSound(RES_SOUND_ID soundID);
	void stopSound();
	float getEffectsVolume();
  	void setEffectsVolume(float volume);

};

#endif

