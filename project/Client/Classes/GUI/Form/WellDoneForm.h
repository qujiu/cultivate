#ifndef __WellDone_FORM_H__
#define __WellDone_FORM_H__
#include "../Form.h"

class WellDoneForm : public Form
{
public:
	CREATE_(WellDoneForm)
		_INST(WellDoneForm);

	virtual bool init();
	WellDoneForm();
	virtual ~WellDoneForm();
private:
	void onResetButtonClicked(Ref *sender, TouchEventType type);
	void onNextButtonClicked(Ref *sender, TouchEventType type);
private:
	ImageView* m_pBkImage;
	ImageView* m_pGuangImage;
	Button* m_pResetBtn;
	Button* m_pNextBtn;
};


#endif