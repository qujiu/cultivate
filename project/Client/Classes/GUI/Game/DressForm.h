#ifndef __DRESS_ROOM_FORM_H__
#define __DRESS_ROOM_FORM_H__

#include "../Form.h"
#include "Entity/ItemWidget.h"
#include "../Form/MenuControl.h"
#include "../MiniControl.h"
#include "GUI/Game/GameForm.h"

class DressForm : public GameForm
{
public:
	CREATE_(DressForm)
		_INST(DressForm)
	virtual bool init();
	DressForm();
	virtual ~DressForm();
public:
	Widget		*m_pLayout;
	ImageView* maozi;
	ImageView* xie;
	ImageView* yanjing;
	ImageView* yifu;

	enum EPorpUIStatus
	{
		EPorpUIStatus_1,
		EPorpUIStatus_2,
		EPorpUIStatus_3,
		EPorpUIStatus_4,
		EPorpUIStatus_5,
		EPorpUIStatus_6,
		EPorpUIStatus_7,
		EPorpUIStatus_8,
		EPorpUIStatus_9,
	};
private:
	ImageView* m_pToolBar;
	Vec2 m_vecInitToolBar;
	ImageView* m_pArrow;
	bool m_isOpen;
	Vec2 m_vecArrowPos;
	ItemBase* m_pCurrItem;
	int m_iSubmenuItemID;
	MenuControl* m_pMenuControl;
	Layout* pToolRolePanel;
	//Layout* pToolPanel;
	int m_pCurrItemid;
	std::vector<int> m_pcurrItem;
	std::vector<int> m_pvecItem;
	std::vector<int> m_pvecItemboy;
	std::vector<int> m_pvecItemgirl;
	Tool* pTool;
	bool isInitItem;
	ui::ScrollView* ItemScrollView;
public:
	void onArrowButtonClicked(Ref *sender, TouchEventType type);
	void refreshSubmenuLockStatus(int id);
	void onItemToolTouchListener(Ref* ref, TouchEventType type);
	bool JudgeItemTool(int id);
	void afterBuyItemSuccessFunc(Ref* object);
	void onItemTouchListener(Ref* ref, TouchEventType type);
	void InitRefreshItem();
protected:
	EPorpUIStatus m_eUIStatus;

};
#endif

