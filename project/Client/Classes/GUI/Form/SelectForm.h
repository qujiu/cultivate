#ifndef __GUI_SelectForm_H__
#define __GUI_SelectForm_H__

#include "../Form.h"
#include <vector>
#include "MenuControl.h"
#include "GameType.h"
using namespace std;

class SelectForm : public Form
{
	CREATE_(SelectForm)
	_INST(SelectForm);
	SelectForm();
	virtual ~SelectForm();
	virtual bool init(); 
public:
	Node* m_pSelect;
	MenuControl* m_pMenuControl;
	int unlock;
	ImageView* pRoom_woshi;
	ImageView* pRoom_toy;
	ImageView* pRoom_canting;
	ImageView* pRoom_muyu;
	ImageView* pRoom_dress;
	Layout* pSelect;
	ImageView* Img_dizuo;
	Button* btn_select;
	ui::ImageView* m_pImg;
	ui::Button* m_pLevelBtn[ELvel_Max];
public:
	void onWanjuButtonClicked(Ref *sender, TouchEventType type);
	void onCantingButtonClicked(Ref *sender, TouchEventType type);
	void onMuyuButtonClicked(Ref *sender, TouchEventType type);
	void onDressButtonClicked(Ref *sender, TouchEventType type);
	void onSelectButtonClicked(Ref *sender, TouchEventType type);
	void onRoleSelectClick(Ref *sender, TouchEventType type);
	void openUnlockTip(int iType);
	void turnToGameScene(float dt);
	void onfang();
	void unLockRoomFunc();
	void unLockWanjuRoom(float dt);
	void unLockDressRoom(float dt);
	void unLockMuyuRoom(float dt);
	void unLockCantingRoom(float dt);
	void HomejiesuoAction();
	void updateAppear(float dt);
	void AssignmentSystem();
	void KaignmentSystem();
	void unLocunlockRoom(Ref* ref);
	void onshowchoose(Ref* ref);
	void updaterole(Ref* ref);
	void SelectEnableHouse(Ref* ref);
	void onRoleBtnCallback();
};


#endif