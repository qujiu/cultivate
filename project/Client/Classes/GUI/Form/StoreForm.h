#ifndef __GUI_StoreForm_H__
#define __GUI_StoreForm_H__

#include "../Form.h"

class StoreForm : public Form
{
public:
	CREATE_(StoreForm)
		_INST(StoreForm)
		virtual bool init();
	StoreForm();
	virtual ~StoreForm();

private:
	Layout* m_pGeceng;
	ImageView* m_pBg;
	vector<int> m_vItems;
	bool m_bClickBuyItem;
	TextAtlas* pDollarSum;
public:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonCallback();
	void onRemoveCallback(Ref* object);
	void onBuyGoldButtonClicked(Ref *sender, TouchEventType type);
	void onBuygameButtonClicked(Ref *sender, TouchEventType type);

	void enableClickBuy(float dt);
	void onCoinsButtonClicked(Ref *sender, TouchEventType type);

};

#endif //__GUI_StoreForm_H__