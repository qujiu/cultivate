#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "LogoForm.h"

class LogoScene : public Scene
{
public:
	static LogoScene* create();
	bool init();

	LogoScene(void);
	virtual ~LogoScene(void);

};


#endif //__LOGO_SCENE_H__