#ifndef __BuyTipForm_H__
#define __BuyTipForm_H__
#include "../Form.h"


class BuyTipForm : public Form
{
public:
	CREATE_(BuyTipForm, int iGoldSum, int iID)
		_INST(BuyTipForm, iGoldSum, iID);

	virtual bool init();
	BuyTipForm(int iGoldSum, int iID);
	virtual ~BuyTipForm();

private:
	void onYesButtonClicked(Ref *sender, TouchEventType type);
	void onNoButtonClicked(Ref *sender, TouchEventType type);
	void showStoreForm(MBCLICK_TYPE type, void* data);
private:
	ImageView*      m_pBkImage;
	int m_nTag;
	ImageView* m_pGeceng;
	int m_iGoldSum;
	int m_iID;
};
#endif