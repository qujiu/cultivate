#ifndef __STORE_FORM_H__
#define __STORE_FORM_H__

#include "../Form.h"
#include "BabyCare.h"

class UIFactory;

class ShopForm : public Form
{
public:
	CREATE_(ShopForm, EStoreUIType type)
		_INST(ShopForm, type)

		virtual bool init();
	ShopForm(EStoreUIType type);
	virtual ~ShopForm();

private:
	Layout* m_pShopUI;
	Layout* m_pGoldUI;

	ImageView* m_pShopImg;
	ImageView* m_pGoldImg;

	EStoreUIType m_eCurrStoreUIType;
private:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onGoldButtonClicked(Ref *sender, TouchEventType type);
	void onShopButtonClicked(Ref *sender, TouchEventType type);
	void onPackButtonClicked(Ref *sender, TouchEventType type);
	void onADSButtonClicked(Ref *sender, TouchEventType type);
	void onReStoreButtonClicked(Ref *sender, TouchEventType type);

	void initShopUI();
	void initGoldUI();

	void onIAPSuccessNot(Ref* objeck);
public:

};

#endif //__INFO_FORM_H__