#ifndef __Muyu_ROOM_FORM_H__
#define __Muyu_ROOM_FORM_H__

#include "../Form.h"
#include "Entity/ItemWidget.h"
#include "../Form/MenuControl.h"
#include "../MiniControl.h"
#include "GUI/Game/GameForm.h"


class MuyuRoomForm : public GameForm
{
public:
	CREATE_(MuyuRoomForm)
		_INST(MuyuRoomForm)
		virtual bool init();
	MuyuRoomForm();
	virtual ~MuyuRoomForm();
public:
	Widget* m_pLayout;
private:
	ImageView* m_pToolBar;
	Vec2 m_vecInitToolBar;
	ImageView* m_pArrow;
	Vec2 m_vecArrowPos;
	bool m_isOpen;
	std::vector<int> vecItem;
public:
	void onArrowButtonClicked(Ref *sender, TouchEventType type);
	void initToolBarAndTool();
	void RefreshSubMenu(std::string panelName, const vector<int>& icon_res_ids);     //const vector<int>& icon_res_ids
	void addMonstersToLayer();
	void onItemTouchListener(Ref* ref, TouchEventType type);
	void onItemRefresh(Ref* ref, TouchEventType type);
	bool JudgeItemStatus(EGameItemType iType);
	void closeToolBar();
	ItemBase* getItemWidgetByIndex(int index);
	void onItemTargerStop(Ref* object);
	void onItemTargerRelease(Ref* object);

	void runTuKouShuiAction();
	void runKouShuiAction();
	void onFrameEvent(Frame* frame);
	void onkoushuiScheduleFunc(float dt);

	void onkoushuihit();
private:
	ItemBase* m_pCurrItem;
	EGameItemTarget m_eItemTarget;
	ItemBase* m_pItems[EItem_Max];
	Layout* m_pCurrToolPanel;
	bool m_isYuhua;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCurTouch, CurTouch, bool);


private:
	BabyControl* m_PlayerLayer;
	MenuControl* m_pMenuControl;
	ActionTimeline* m_pKoushuiTimeline;
	Node* m_pTimelineNode;
	ImageView* m_pKoushuiImg;

};
#endif

