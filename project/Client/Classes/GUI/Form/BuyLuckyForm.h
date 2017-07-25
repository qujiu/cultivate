/*
** declare DialogForm
** author: zhangchao;
** date: 2014.10.09
*/

#ifndef __BuyLuckyForm_H__
#define __BuyLuckyForm_H__
#include "../Form.h"


class BuyLuckyForm : public Form
{
public:
	CREATE_(BuyLuckyForm, int iGoldSum, int iID)
		_INST(BuyLuckyForm, iGoldSum, iID);

	virtual bool init();
	BuyLuckyForm(int iGoldSum, int iID);
	virtual ~BuyLuckyForm();

private:
	void onYesButtonClicked(Ref *sender, TouchEventType type);
	void onNoButtonClicked(Ref *sender, TouchEventType type);

	void rand();
	void showStoreForm(MBCLICK_TYPE type, void* data);

private:
	ImageView*      m_pBkImage;
	int m_nTag;
	Layout* m_pGeceng;
	int m_iGoldSum;
	int m_iID;
	bool m_bClickBuyItem;
};

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////

#endif