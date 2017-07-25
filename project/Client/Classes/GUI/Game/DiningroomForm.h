#ifndef __DINING_ROOM_FORM_H__
#define __DINING_ROOM_FORM_H__

#include "../Form.h"
#include "Entity/ItemWidget.h"
#include "Entity/ItemFactory.h"
#include "../Form/MenuControl.h"
#include "../MiniControl.h"
#include "GUI/Game/GameForm.h"

class DiningRoomForm : public GameForm
{
public:
	CREATE_(DiningRoomForm)
		_INST(DiningRoomForm)

		virtual bool init();
	DiningRoomForm();
	virtual ~DiningRoomForm();

private:

	Layout* m_pPropLayout1;
	Layout* m_pPropLayout2;
	Layout* m_pPropLayoutzhijin;
	Layout* m_pPropLayoutweijin;

	Layout* m_pzhuozi;
	ImageView* m_pImagineClothesImg;
	int m_nRandType;

	ImageView* m_pshaozi;
	ImageView* m_pmianbao;

	EGameItemTarget m_eItemTarget;
	bool m_bOpenMake;

	MenuControl* m_pMenu;
	MiniControl* m_pMini;
public:
	BabyControl* m_pBabyControl;
	ImageView* m_pImagineImg;
	ImageView* m_pIzhijin;
	ImageView* m_pIweijin;
	ImageView* m_pNaiping;
	ImageView* m_pNaiFen;


public:

	void onItemTouchListener(Ref* ref, TouchEventType type);
	void onOpenMakeListener(Ref* ref, TouchEventType type);
	void onNextButtonClicked(Ref *ref, TouchEventType type);
	void onImagineButtonClicked(Ref* ref, TouchEventType type);
	void onNaipingItemTouchListener(Ref* ref, TouchEventType type);

	bool onTouchBeginListener(Touch *touch, Event *unusedEvent);
	void onTouchMoveListener(Touch *touch, Event *unusedEvent);
	void onTouchEndListener(Touch *touch, Event *unusedEvent);


	void runImagineAction();
	void runImagineActionCallBack();

	void openMakeForm();
	void makeFormCallback(bool bOpen);

	void closeMakeFormCallback();

	void onItemTargerRelease(Ref* object);
	void onItemTargerStop(Ref* object);
	void onLockToolsNot(Ref* object);
	void onLockRoomNot(Ref* object);
	void onOpenAwardNot(Ref* object);
	void onCloseAwardNot(Ref* object);
	void onCloseInfoNot(Ref* object);
	void initState();

	inline int& getRandType(){ return m_nRandType; };
	void showNaipingImg();
	void runYaonaiTips();
	void runYaonaiAction();
	void AnimationEndListener();
private:
	void showTips();
	void hideTips();

public:
	void openMianBaoinRoom(Ref* object);
	void openWaninRoom(Ref* object);
};

#endif //__DINING_ROOM_FORM_H__