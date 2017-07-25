/*
** declare DialogForm
** author: zhangchao;
** date: 2014.10.09
*/

#ifndef __UNLOCKTIPFORM_H__
#define __UNLOCKTIPFORM_H__



#include "../Form.h"


class UnlockTipForm : public Form
{
public:
	CREATE_(UnlockTipForm, int iType)
		_INST(UnlockTipForm, iType);

	virtual bool init();
	UnlockTipForm(int iType);
	virtual ~UnlockTipForm();

private:
	void onOKButtonClicked(Ref *sender, TouchEventType type);
	void onVideoButtonClicked(Ref *sender, TouchEventType type);
	void onRateButtonClicked(Ref *sender, TouchEventType type);
private:
	ImageView*      m_pBkImage;
	int m_nTag;
	Layout* m_pGeceng;
	int m_iType;
};

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////

#endif