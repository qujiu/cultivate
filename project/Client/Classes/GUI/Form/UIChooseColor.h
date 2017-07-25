#ifndef __GUI_UIChooseColor_H__
#define __GUI_UIChooseColor_H__

#include "../Form.h"

class UIChooseColor : public Form
{
public:
	CREATE_(UIChooseColor)
		_INST(UIChooseColor)
	virtual bool init();
	UIChooseColor();
	virtual ~UIChooseColor();
private:
	ImageView* m_pGeceng;
	ImageView* m_pBg;
	ui::ScrollView* m_pStoreProp;
	ui::ImageView* m_pLightTemp;
	ImageView* toushi;
	Node* pStore;
	vector<ImageView*> m_lab_bg;
public:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonCallback();
	void stamp(Node *obj, int date);
	void onRemoveCallback(Ref* object);
	void updateresult(float dt);
	void onBuygameButtonClicked(Ref *sender, TouchEventType type);
};
#endif