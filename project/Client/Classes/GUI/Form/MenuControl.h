#ifndef __MENU_FORM_H__
#define __MENU_FORM_H__

#include "../Form.h"

class MenuControl : public BaseControl
{
public:
	CREATE_(MenuControl)
		_INST(MenuControl)

		virtual bool init();
	MenuControl();
	virtual ~MenuControl();
public:
	SUP_RW_PROPERTY_PREFIX_DEF(private, Vec2, m_vecGoldImgWorldPos, GoldImgWorldPos, Vec2);
public:
	void onSelectButtonClicked(Ref *sender, ui::TouchEventType type);
	void onSettingButtonClicked(Ref *sender, ui::TouchEventType type);
	void ongameButtonClicked(Ref *sender, ui::TouchEventType type);
	void onLeftButtonClicked(Ref *sender, ui::TouchEventType type);
	void onRightButtonClicked(Ref *sender, ui::TouchEventType type);
	void onStoreButtonClicked(Ref *sender, ui::TouchEventType type);
	void onMoreButtonClicked(Ref *sender, TouchEventType type);
	void onCoinsButtonClicked(Ref *sender, TouchEventType type);
	void onDevButtonClicked(Ref *sender, TouchEventType type);
	void DropGiftTimer(float dt);
	void setCommonPanelVisible(bool bVisible);
	void setSettingBtnVisible(bool bVisible);
	void setSelectBtnVisible(bool bVisible);
	void setLeftBtnVisible(bool bVisible);
	void setRightBtnVisible(bool bVisible);
	void setToDevBtnVisible(bool bVisible);
	void setgameBtnVisible(bool bVisible);
	void setPanelPosVisible(bool bVisible);
	void setGoldImgBtnVisible(bool bVisible);
	void setGoldTotalSum(int lSum);
	void setStoreBtnVisible(bool bVisible);
	void setGoldsetTotalSum(int lSum);
	void setGenXinTotalSum(Ref* re);
	void onSelectBtnCallBack(MBCLICK_TYPE type, void* data);
	void buySuccess(Ref* object);
	void buyFailed(Ref* object);
	void buyTimeout(Ref* object);
	void updatebox(float dt);
	void hiddenbox();
	bool onTouchBeginListener(Touch *touch, Event *unusedEvent);
public:
	Layout* m_pCommonPanel;
	Button* m_pSelectBtn;
	Button* m_pSettingBtn;
	Button* m_pgameBtn;
	Button* m_pLeftBtn;
	Button* m_pRightBtn;
	Button* pDevBtn;
	ImageView* m_pGoldBgImg;
	Text* m_TextGoldSum;
	ImageView* m_pPlusImg;
	Button* m_pGoldgame;
	Layout* m_pPanelPos;
	SkeletonAnimation* m_sktPersonAni;
	spPolygon* m_pCheckPoly;
	spSkeletonBounds* m_pSkeletonBounds;
	Form* m_pCamerForm;
	Node* pLayout;
	int tou;
	bool m_bFlag;
};

#endif //__MENU_FORM_H__