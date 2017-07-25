#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "HomeForm.h"

class HomeScene : public Scene
{
public:
	static HomeScene* create();
	bool init();

	HomeScene(void);
	virtual ~HomeScene(void);

};
#endif //__HOME_SCENE_H__