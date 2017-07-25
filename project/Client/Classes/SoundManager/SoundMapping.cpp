#include "SoundMapping.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//sound ogg
//music mp3
char* g_arrSounds[] = 
{
	"Sound/android/main_music.ogg" ,
	"Sound/android/home_music.ogg" ,
};


#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//sound wav
//music mp3
char* g_arrSounds[] = 
{
    "Sound/ios/music_logo.mp3" ,
    "Sound/ios/music_game.mp3" ,
};
#endif



char* SoundMapping::getSoundPath(RES_SOUND_ID soundID)
{
	return g_arrSounds[soundID];
}





