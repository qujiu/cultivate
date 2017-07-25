#ifndef __GUI_GAMEFORM_H__
#define __GUI_GAMEFORM_H__

#include "../Form.h"
#include "Entity/ItemFactory.h"

class GameForm : public Form
{
public:
	CREATE_(GameForm, WINDOW_ID id)
		_INST(GameForm, id)
		GameForm(WINDOW_ID id);
	virtual ~GameForm();
	virtual bool init();

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
	ImageView* m_pTipsImg;
	int m_iSubmenuItemID;
	bool m_isClickSelect;
public:
	ItemBase* m_pItems[EItem_Max];
	ItemBase* m_pCurrItem;
	Layout* m_pmainMenu;
	Layout* m_pMainProp;
	Layout* m_pSubMenu;
	ui::ScrollView* m_pSubProp;
	Layout* m_pStarProp;
	std::vector<int> m_vItems;

protected:
	EGameItemTarget m_eItemTarget;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCurTouch, CurTouch, bool);     

	bool m_isShowJindutiaoTexiao;
	int m_iCountGold;

	Layout* m_pCountLayout;
	TextAtlas* m_pCountText;

	bool m_bTouchEnable;
	int m_iUIPropSum;

	ImageView* m_pReporterImg;
	Vec2 m_vecInitReporterPos;

	ImageView* m_pRewardImg;
	ImageView* m_pRewardGold;
	Button* m_pGetBtn;
	Button* m_pDoubleBtn;
	Layout* m_jieb;
	Button* m_pcon;
	bool m_isDoubleRewardsCoins;
	TextAtlas* m_pRewardCoins;
public:
	void onItemTouchListener(Ref* ref, TouchEventType type);
	void onSubMenuItemTouchListener(Ref* ref, TouchEventType type);
	virtual void RefreshSubMenu(const vector<int>& icon_res_ids);
	bool JudgeSubmenuItemBuy(int iID);
	void afterBuyItemSuccessFunc(Ref* object);
	void refreshSubmenuLockStatus(int iID);
	void onupdateIcon(Ref* object);
	void initWellDownAni();
	void playWellDownAni(bool bFlag = true);
	void removeWellDownAni();
	SkeletonAnimation* m_pSkWellDone;
	typedef std::function<void()> rewordFunc;
	rewordFunc m_pRewordFunc;
	typedef std::function<void()> supGameNextFunc;
	supGameNextFunc m_pNextFunc;
	void addRandPart(std::string filePath);
};

#endif