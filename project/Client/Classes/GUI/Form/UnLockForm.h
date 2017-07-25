#ifndef __UN_LOCK_FORM_H__
#define __UN_LOCK_FORM_H__

#include "../Form.h"
#include "BabyCare.h"

class UnLockForm : public Form
{
public:
	CREATE_(UnLockForm)
		_INST(UnLockForm)

		virtual bool init();
	UnLockForm();
	virtual ~UnLockForm();

private:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onGoldButtonClicked(Ref *sender, TouchEventType type);
	void onPackButtonClicked(Ref *sender, TouchEventType type);
	void onFullButtonClicked(Ref *sender, TouchEventType type);

	void onIAPSuccessNot(Ref* object);
private:
	Layout* m_pRoomLayout;
	Layout* m_pRoleLayout;
	Layout* m_pToolLayout;

	ImageView* m_pRoomImg;
	ImageView* m_pRoleImg;
	ImageView* m_pToolImg;

	TextAtlas* m_pRoomGold;
	TextAtlas* m_pRoleGold;
	TextAtlas* m_pToolGold;

	EStoreUIType m_eStoreType;

public:

};

#endif //__INFO_FORM_H__