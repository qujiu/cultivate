#ifndef __GUI_LogoForm_H__
#define __GUI_LogoForm_H__

#include "../Form.h"
#include <vector>
using namespace std;

class LogoForm : public Form
{
public:
	CREATE_(LogoForm)
		_INST(LogoForm)

	virtual bool init();
	LogoForm();
	virtual ~LogoForm();
	void goHome(float p);
};

#endif