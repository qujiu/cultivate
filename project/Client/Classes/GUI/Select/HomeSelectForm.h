#ifndef __GUI_Home_SelectForm_H__
#define __GUI_Home_SelectForm_H__

#include "../Form.h"
#include "GameType.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCSkin.h"
#include "../Form/MenuControl.h"

class HomeSelectForm : public Form
{
public:
	CREATE_(HomeSelectForm)
		_INST(HomeSelectForm)

	virtual bool init();
	HomeSelectForm();
	virtual ~HomeSelectForm();
};

#endif 