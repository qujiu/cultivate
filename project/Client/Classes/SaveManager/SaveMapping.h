#ifndef __PS_SAVE_MAPPING_H__
#define __PS_SAVE_MAPPING_H__

#include "SaveID.h"
#include "define.h"
class SaveMapping  : public cocos2d::Ref
{

private:
	SaveMapping(void){};
	~SaveMapping(void){};

public:
	static char* getSaveKey(SAVE_ID saveID);

};

#endif

