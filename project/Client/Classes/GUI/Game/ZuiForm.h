/*
** declare BabyRoomForm
** author: zhang chao;
** date: 2015.5.13
*/
#ifndef __ZUI_FORM_H__
#define __ZUI_FORM_H__

#include "../Form.h"
#include "Entity/ItemBase.h"
#include "GUI/Game/GameForm.h"

class ZuiForm : public Form
{
public:
	CREATE_(ZuiForm)
		_INST(ZuiForm)

	virtual bool init();
	ZuiForm();
	virtual ~ZuiForm();

private:
	ImageView* m_pRenchenyeImg;
	Vec2 m_touchLastPos; //记录点击怪物的坐标;
	EGameItemTarget m_eItemTarget;
	Layout* m_pPropLaout;
	ItemBase* m_oItems[EItem_Max];
	ItemBase* m_pCurrItem;
public:
	void AnimationMovementEventListener(Armature *armature, MovementEventType movementType, const std::string& movementID);

	void onItemTouchListener(Ref* ref, TouchEventType type);
	void onColseButtonClicked(Ref *sender, TouchEventType type);

	void onItemTargerRelease(Ref* object);
	void onItemTargerStop(Ref* object);
	void onItemTargerTrigger(Ref* object);

	void showFaDaJing();
	void removeYaZiMonster();
};

#endif 