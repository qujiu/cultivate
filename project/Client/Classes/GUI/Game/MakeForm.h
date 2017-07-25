/*
** declare MakeForm
** author: zhang chao;
** date: 2015.5.13
*/
#ifndef __MAKE_FORM_H__
#define __MAKE_FORM_H__

#include "GUI/Game/GameForm.h"
#include "FoodsWidget.h"
#include "Entity/ItemWidget.h"

class MakeForm : public GameForm
{
public:
	CREATE_(MakeForm, int type)
		_INST(MakeForm, type)

		virtual bool init();
	MakeForm(int type);
	virtual ~MakeForm();
	inline cocos2d::Rect& getTargetRect(){ return m_targetRect; };
	ImageView* getTargetImg();
private:
	int m_nType;
	int m_nFoodsCount;
	cocos2d::Rect m_targetRect;
	EGameItemTarget m_eItemTarget;
	bool m_bTouchEnd;
	Armature* m_pArmature;
	ImageView* m_pTarget[3];
	FoodsWidget m_oFoods[8];
	FoodsWidget* m_pCurrFoods;
	Layout* m_pPropLayout;
	Layout* Panel_niunai;
	ImageView* m_pMianbao;
	ImageView* m_pShaozi;
	ImageView* m_pGuoping;
	ImageView* m_pGuozha;
	ImageView* m_pmaipian;
	ImageView* pShaozi;
	ImageView* pBg;
	Rect m_rectCollision;

	Layout* m_pPanel;

	SkeletonAnimation* m_pSkHuomian;

	Layout* m_pCheckPanel;
	Layout* m_pCheckJiaoPanel;


	Vec2 m_vec2InitPos;
	Vec2 m_vec2Delta;
	bool m_bIsCollision;
	bool m_bIsMoving;

	int m_nCount;
	bool m_bFlagMove;
	bool m_bFlagEnd;
	ImageView* m_pJiaoImg;
	bool m_bShouFlag;

	int m_nShala;
	int m_nFanqiejiang;

	int m_nGoodCount; //标记正确水果数;
	int m_nGoldCount;
	int m_nTag;
	ImageView* m_bItem[2];

private:
	void initTargetRect(Widget* pNode);

	void FoodsTouchBegin();
	void FoodsTouchMove();
	void FoodsTouchEnd();

	bool CheckFoodsTrigger();
	bool CheckTrigger();

	void FruitEnterAction();
	void FruitEnterActionCallback();

	void VeggieEnterAction();
	void VeggieEnterActionCallback();

	void onMaipianClicked(Ref* ref, TouchEventType type);

	void foodsEnter(int nID);

public:
	void onCloseButtonClicked(Ref* ref, TouchEventType type);
	void onFoodsTouchListener(Ref* ref, TouchEventType type);
	void onShouDongClicked(Ref *sender, TouchEventType type);
	void onItemTargerRelease(Ref* object);
	void onItemTargerStop(Ref* object);

	void runItemCallback();
	void runShuibeiCallback(int nIndex);

	void AnimationMovementEventListener(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void onFrameEventListener(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);
	void onItemTouchListener(Ref* ref, TouchEventType type);
	void onItemBtnClicked(Ref *sender, TouchEventType type);

	void AddGuojangToFull(EWaterType type);
	void AddGuojangToMianBao();
	void IntialGuojiang(Ref* ref);

	void moveToInitPos();
	void setToolPos(Vec2 deltaPos);
	void pauseSkeletonAni();
	void resumSkeletonAni();
	void checkCollisionJiao();
	void cutDownIdleTime(float dt);
	void setItemTips(int nIndex);
	void showAddAction(int nIndex);
	void checkCollision();
	void AnimationEndListener(Node *obj, int index);
};

#endif //__MAKE_FORM_H__