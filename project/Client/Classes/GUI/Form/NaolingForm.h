/*
** declare NaolingForm
** author: zhang chao;
** date: 2014.10.09
*/

#ifndef __GUI_NaolingForm_H__
#define __GUI_NaolingForm_H__

#include "../Form.h"

class NaolingForm : public Form
{
public:
	CREATE_(NaolingForm)
		_INST(NaolingForm)

	virtual bool init();
	NaolingForm();
	virtual ~NaolingForm();

private:
	Layout* m_pGeceng;
	ImageView* m_pBgImg;

	
public:
	void onCloseScheduleFunc(float dt);
	void onCloseButtonCallback();

	void onOKButtonClicked(Ref *sender, TouchEventType type);

};

#endif //__GUI_NaolingForm_H__