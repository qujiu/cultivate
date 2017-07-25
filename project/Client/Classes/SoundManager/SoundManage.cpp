#include "SoundManage.h"
#include "SoundMapping.h"
#include "SaveManager/SaveManage.h"

SINGLETON_DEFINE_INST(SoundManage, Ref);

SoundManage::SoundManage(void) :m_nSoundId(0)
,m_MusicID(RES_SOUND_ID_NONE)
{
	m_isSoundOn = SaveManage::instance()->getBoolSave(SAVE_ID_BOOL_IS_SOUND_ON,true);

	for (int i = RES_SOUND_ID_MUSIC_MIN ;i< RES_SOUND_ID_MUSIC_MAX;i++)
	{
		char* sound = SoundMapping::getSoundPath((RES_SOUND_ID)(i));
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic( FileUtils::getInstance()->fullPathForFilename(sound).c_str());
	}

	for (int i = RES_SOUND_ID_SOUND_MIN ;i<RES_SOUND_ID_SOUND_MAX;i++)
	{
		char* sound = SoundMapping::getSoundPath((RES_SOUND_ID)(i));
		SimpleAudioEngine::getInstance()->preloadEffect( FileUtils::getInstance()->fullPathForFilename(sound).c_str());
	}

};

SoundManage::~SoundManage(void)
{

};


bool SoundManage::isMusicOn(void)
{
	return m_isMusicOn;
}

void SoundManage::setMusicOn(bool isOn)
{
	m_isMusicOn = isOn;
	if (!m_isMusicOn)
	{
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		if (m_MusicID != RES_SOUND_ID_NONE)
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(std::string(FileUtils::getInstance()->fullPathForFilename(SoundMapping::getSoundPath(m_MusicID))).c_str(), true);
		}
	}
	SaveManage::instance()->setBoolSave(SAVE_ID_BOOL_IS_MUSIC_ON, m_isSoundOn);
}


bool SoundManage::isSoundOn(void)
{
	return m_isSoundOn;
}
void SoundManage::setSoundOn(bool isOn)
{

	m_isSoundOn = isOn;
	if (!m_isSoundOn)
	{
		
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->stopEffect(m_nSoundId);
	}
	else
	{
		if (m_MusicID != RES_SOUND_ID_NONE)
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(std::string(FileUtils::getInstance()->fullPathForFilename(SoundMapping::getSoundPath(m_MusicID))).c_str(), true);
		}
		if (m_nSoundId != 0 && m_isLoop)
		{
			playSound(m_nSoundID, true, m_isLoop);
		}
		
	}
	SaveManage::instance()->setBoolSave(SAVE_ID_BOOL_IS_SOUND_ON,m_isSoundOn);
}



void SoundManage::playMusic(RES_SOUND_ID soundID)
{
	if (m_MusicID == soundID)
	{
		return;
	}
	m_MusicID = soundID;

	if(m_isSoundOn)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playBackgroundMusic(std::string(FileUtils::getInstance()->fullPathForFilename(SoundMapping::getSoundPath(soundID))).c_str(), true);
	}
}
void SoundManage::stopMusic()
{
	m_MusicID = RES_SOUND_ID_NONE;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}


void SoundManage::playSound(RES_SOUND_ID soundID, bool isSave, bool isLoop)
{
	if(m_isSoundOn)
	{
		unsigned int id = SimpleAudioEngine::getInstance()->playEffect(std::string(FileUtils::getInstance()->fullPathForFilename(SoundMapping::getSoundPath(soundID))).c_str(), isLoop);
		if (isSave)
		{
			m_nSoundId = id;
			m_isLoop = isLoop;
			m_nSoundID = soundID;
		}

	}
	else if (isSave)
	{
		m_isLoop = isLoop;
		m_nSoundID = soundID;
	}

}

void SoundManage::stopSound(RES_SOUND_ID soundID)
{
	if(m_isSoundOn)
	{
		SimpleAudioEngine::sharedEngine()->stopEffect(soundID);
	}
}

void SoundManage::stopSound()
{
	if(m_isSoundOn && m_nSoundId != 0)
	{
		SimpleAudioEngine::sharedEngine()->stopEffect(m_nSoundId);
		m_nSoundId = 0;
	}
}


void SoundManage::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}


float SoundManage::getBackgroundMusicVolume()
{
	return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}


float SoundManage::getEffectsVolume()
{
	return SimpleAudioEngine::getInstance()->getEffectsVolume();
}


void SoundManage::setEffectsVolume(float volume)
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

