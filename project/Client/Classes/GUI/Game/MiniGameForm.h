#ifndef __GUI_MiniGame_Form_H__
#define __GUI_MiniGame_Form_H__

#include "../Form.h"

class MiniGameForm : public Form
{
public:
	CREATE_(MiniGameForm, bool bAgain)
		_INST(MiniGameForm, bAgain)

	virtual bool init();
	MiniGameForm(bool bAgain);
	virtual ~MiniGameForm();
private:
	bool m_bAgain;
private:
	void onMiniGameBtnClicked(Ref *sender, TouchEventType type);
	void onCloseButtonClicked(Ref *sender, TouchEventType type);

};
#endif //__GUI_MiniGame_Form_H__