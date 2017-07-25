#ifndef __GUI_Scene_Form_H__
#define __GUI_Scene_Form_H__


#include "BabyCare.h"
#include "../Form.h"
#include "cocostudio/CCSkin.h"

class SceneForm : public Form
{
public:
	CREATE_(SceneForm)
		_INST(SceneForm)
	virtual bool init();
	SceneForm();
	virtual ~SceneForm();
private:
	SkeletonAnimation* m_pSkeletonNode;
};
#endif