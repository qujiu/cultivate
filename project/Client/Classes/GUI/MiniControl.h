/*
** declare MiniControl
** author: zhang chao;
** date: 2015.9.10
*/
#ifndef __Mini_Control_H__
#define __Mini_Control_H__

#include "Form.h"

class MiniControl : public BaseControl
{
public:
	CREATE_(MiniControl)
		_INST(MiniControl)

	virtual bool init();
	MiniControl();
	virtual ~MiniControl();

private:
	ImageView* m_pMiniImg;
private:
	void onMiniButtonClicked(Ref *sender, ui::TouchEventType type);

};

#endif //__MENU_FORM_H__