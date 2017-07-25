#ifndef __BUY_COINS_FORM_H__
#define __BUY_COINS_FORM_H__

#include "../Form.h"

class BuyCoinsForm : public Form
{
public:
	CREATE_(BuyCoinsForm)
		_INST(BuyCoinsForm)

		virtual bool init();
	BuyCoinsForm();
	virtual ~BuyCoinsForm();
private:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onBuyButtonClicked(Ref *sender, TouchEventType type);
	void onMiniGameButtonClicked(Ref *sender, TouchEventType type);
	void onIAPSuccessNot(Ref* objeck);
public:
};

#endif //__BUY_COINS_FORM_H__