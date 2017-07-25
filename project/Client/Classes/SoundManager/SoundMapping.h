#ifndef __SOUND_MAPPING_H__
#define __SOUND_MAPPING_H__

#include "define.h"
#include "SoundID.h"

class SoundMapping  : public cocos2d::Ref
{
private:
	SoundMapping(void){};
	~SoundMapping(void){};

public:
	static char* getSoundPath(RES_SOUND_ID soundID);

};

#endif

