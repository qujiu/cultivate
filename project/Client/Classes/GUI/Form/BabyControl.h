#ifndef _GUI_BabyControl_H_
#define _GUI_BabyControl_H_

#include "GUI/Form.h"
#include "BabyCare.h"
#include "Entity/ItemWidget.h"
#include "../Form/MenuControl.h"
#include <cstring>  
#include <iostream>  
using namespace std;

class BabyControl : public Form
{
public:
	CREATE_(BabyControl)
	      _INST(BabyControl)
	virtual bool init();
	BabyControl();
	virtual ~BabyControl();
private:
	ImageView* m_pClothesImg;
	ImageView* m_pUnderwearImg;

	ImageView* m_pClothesYinImg;
	ImageView* m_pUnderwearYinImg;

	EBabyExpression m_eExpression;
	int type;
	Layout* m_pAniPanel;
	Layout* m_pShouPanel;
	Vec2 m_vecInitPos;
	SkeletonAnimation* m_sktRoleAni;

	vector<std::string> m_vecJson;
	vector<std::string> m_vecAtlas; 
	std::string m_aniName;
	vector<std::string> m_vecSlots;
	vector<std::string> m_vecAttachments;
	vector<std::string> m_vecSpriteFrame;
	spSlot* slot;
	Player* m_Player;
	EBabyExpression m_iIdleStatus;
	ActionTimeline* m_pTimeLine;
	Sprite* anipiss;
	int tmpid;

public:
	ItemBase* m_pCurrItem;
	EGameItemTarget m_eItemTarget;
	ItemBase* m_pItems[EItem_Max];
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCurTouch, CurTouch, bool);
	SUP_RW_PROPERTY_PREFIX_DEF(protected, Vec2, m_vecHuasaPos, HuasaPos, Vec2);
public:
	void ReplaceRoleSkeletonSkin(const char* skin, const char* attachment, const std::string& spriteFrameName);
	void playRoleAnimation(EBabyExpression type, bool loop = false);
	void stopRoleAnimation();
	void initActionFile();
	bool refreshIdleStatus();
	void ReplaceZhiNiaoKu(const std::string& spriteFrameName);
	void initZhiniukuAction();
	void refreshZhiniukuAction();
	void updateRoleSkin();
};
#endif