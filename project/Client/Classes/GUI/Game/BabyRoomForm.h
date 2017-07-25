#ifndef __BABY_ROOM_FORM_H__
#define __BABY_ROOM_FORM_H__

#include "../Form.h"
#include "Entity/ItemWidget.h"
#include "../MiniControl.h"
#include "GameType.h"
#include "GUI/Game/GameForm.h"

class BabyRoomForm : public GameForm
{
public:
	CREATE_(BabyRoomForm)
		_INST(BabyRoomForm)

		virtual bool init();
	BabyRoomForm();
	virtual ~BabyRoomForm();

private:
	enum EPropUIStatus
	{
		EPropUIStatus_first,
		EPropUIStatus_second,
		EPropUIStatus_third,
		EPropUIStatus_max,
	};

	EPropUIStatus m_eUIStatus;
	Layout* m_pPropLayout[EPropUIStatus_max];


	BabyControl* m_pBabyControl;
	EGameItemTarget m_eItemTarget;
	bool m_bCool;
	bool m_isOpen;
	bool m_bwanjuTrue;
	bool m_bzhiniukuTrue;
	bool m_bnaizuiTrue;

	bool m_bnight;

	float tmpPosy;

	CCClippingNode* m_pBlackBg;

public:
	Layout* panel_daoju;
	Button* m_pNextBtn;
	MenuControl* m_pMenuControl;
	Sprite* itemBaiYe;
	ActionTimeline* m_pClockTimeLine;
	ActionTimeline* m_pBaiyeTimeLine;

	bool CurWindowState;
	



	ImageView* Img_zhentou;
	ImageView* m_pBeiziImg;
	Vec2 m_beiziLastPos;
	Vec2 m_beiziInitPos;
	ImageView* Img_xiaobear;
	ImageView* Img_zhiNiuKu;
	ImageView* pGameFaguangImg;
	ImageView* Img_naizui;
	ImageView* lightguang;
	Vec2 m_vecInitToolBar;
	ImageView* m_pArrow;
	Vec2 m_vecArrowPos;

	Vec2 m_naizuiPos;
	Vec2 m_wanjuPos;
	Vec2 m_zhiniaokuPos;
	Vec2 m_clockPos;
	bool m_isSleep;

	float m_fCurrJingliTimer;
	Layout* m_pGeceng;

public:
	void onBeiziTouchListener(Ref* ref, TouchEventType type);
	void onArrowButtonClicked(Ref *sender, TouchEventType type);
	bool onTouchBeginListener(Touch *touch, Event *unusedEvent);
	void onTouchMoveListener(Touch *touch, Event *unusedEvent);
	void onTouchEndListener(Touch *touch, Event *unusedEvent);
	void onClockActionClicked(Ref *sender, TouchEventType type);
	void onLightBtnClicked(Ref *sender, TouchEventType type);
	void onWindowActionClicked(Ref *sender, TouchEventType type);

	
	void playWindowNormalAction();
	void playWindowAction();
	void showCoolAction(float time);
	void hideCoolAction(float time);
	void openToolBar();
	void hideItemNaiZuiAction();
	void showItemNaiZuiAction();
	void hideItemZhiNiaoKuAction();
	void showItemZhiNiaoKuAction();
	void hideItemWanJuAction();
	void showItemWanJuAction();
	void addMonstersToLayer();
	void playClockNormalAction();
	void playClockAction();
	bool getBlackBGVisual();
	void setSleepAction(bool isVisual);
	void startRecoverJingliTimer(Ref* object);
	void stopRecoverJingliTimer();
	void update(float delta);
	void AfterFinishRecoverJingliTimer();


	void InitFirstPissAction(float t);
	void onPissClean(Ref* object);
	void RefreshItemFaGuang(float dt);
	void setGeCengVisual(bool isValue);
	void MoveOutBedItem();
	void showBedItemVisual();
};

#endif 