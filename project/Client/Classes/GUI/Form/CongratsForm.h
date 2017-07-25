#ifndef __GUI_CongratulationForm_H__
#define __GUI_CongratulationForm_H__

#include "../Form.h"
#include "MenuControl.h"

class CongratsForm : public Form
{
public:
	CREATE_(CongratsForm, int iID)
		_INST(CongratsForm, iID)

		virtual bool init();
	CongratsForm(int iID);
	virtual ~CongratsForm();

private:
	ImageView* m_pGeceng;
	Layout* m_pPanelPos;

	int m_iID;

public:
	MenuControl* m_pMenuControl;
	void onCloseScheduleFunc(float dt);
	void onCloseButtonCallback();

};

#endif //__GUI_CongratulationForm_H__