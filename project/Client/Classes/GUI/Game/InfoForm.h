/*
** declare InfoForm
** author: zhang chao;
** date: 2015.5.13
*/
#ifndef __INFO_FORM_H__
#define __INFO_FORM_H__

#include "../Form.h"

class InfoForm : public Form
{
public:
	CREATE_(InfoForm)
		_INST(InfoForm)
		virtual bool init();
	InfoForm();
	virtual ~InfoForm();
private:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onInfoClicked(Ref *sender, TouchEventType type);
	void showBuyForm();
	Layout	*m_pInterlayer;
};
#endif 