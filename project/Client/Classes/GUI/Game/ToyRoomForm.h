#ifndef __Toy_ROOM_FORM_H__
#define __Toy_ROOM_FORM_H__

#include "../Form.h"
#include "Entity/ItemWidget.h"
#include "../Form/MenuControl.h"
#include "../MiniControl.h"
#include "GUI/Game/GameForm.h"


class ToyRoomForm : public GameForm
{
public:
	CREATE_(ToyRoomForm)
		_INST(ToyRoomForm)
		virtual bool init();
	ToyRoomForm();
	virtual ~ToyRoomForm();
private:
	ImageView* Img_bear;
	ImageView* Img_muma;
	Layout* panel_qiu;
	ImageView* Img_daqi;
	ImageView* Img_tantanqiu;
	MenuControl* m_pMenuControl;
	Layout* Panel_Loadingbar;
	LoadingBar* m_LoadingBar;
public:
	std::vector<int> m_pcurrItem;



public:
	void addMonstersToLayer();
	void setInitialDaqi(Ref* obj);
	void onItemQiTongTouchListener(Ref* ref, TouchEventType type);
	void onItemMuMaTouchListener(Ref* ref, TouchEventType type);
	void onItemBearTouchListener(Ref* ref, TouchEventType type);
	void onItemTanQiuTouchListener(Ref* ref, TouchEventType type);


};
#endif

