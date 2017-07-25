#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "define.h"
#include "../Form.h"

class SelectScene : public Scene
{
public:
	static SelectScene* create();
	bool init();

	SelectScene(void);
	virtual ~SelectScene(void);
private:
	Form* m_pselectForm;
public:
	Form* getSelectForm();
};


#endif //__SELECT_SCENE_H__