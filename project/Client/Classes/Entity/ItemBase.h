#ifndef __GAME_ITEM_BASE_H__
#define __GAME_ITEM_BASE_H__

#include "define.h"
#include "GUI/Form.h"
#include "GameType.h"
#include "Common/Common.h"
#include "Entity/Item.h"
#include "MonsterBase.h"
#include "Entity/item.h"

class ItemBase : public BaseControl
{
public:
	CREATE_(ItemBase, EGameItemType type, ImageView* pImage)
		_INST(ItemBase, type, pImage)

		ItemBase(EGameItemType type, ImageView* pImage);
	virtual ~ItemBase();
	virtual bool init();
	void setOrder(int nOrder);
public:
	virtual void TouchBegin();
	virtual void TouchMove();
	virtual void TouchEnd();

	virtual void TargetBegin();
	virtual void TargetMove();
	virtual void TargetEnd();

	virtual void onItemTouch();
	virtual void onItemTrigger();
	virtual void onItemHit();
	virtual void onItemRelease();
	virtual bool onTriggerMonster();
	virtual void propUserEnd();
	virtual void setUserComplete();
	virtual void removeHitMonster(MonsterBase* pMonster);
	virtual void ItemShowImg();
	virtual void ItemShowAni();
	virtual void RefreshToolImage(int iID);
	virtual void RefreshItemAndMonsterImage(int iID, const char* str1, const char* str2);
	virtual void TurnPos(const Vec2& pos, CallFunc* done = nullptr);
	bool CheckTrigger();
	void CheckItemMoveRange(Vec2& pos);
	void addMonsterWidget(MonsterBase* pMonsterWidget);
	virtual void AnimationMovementEventListener();
	virtual void initMonsterImage(bool before);
	void setItemOpen();
	void showTips(ETipsType type, int  Distance);

protected:
	void onFrameEventListener(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);
	void playItemSound(EItemSoundType type);
	void stopItemSound();
	void setItemLock(bool bLock); 
	void openNextItem(EGameItemType type);
public:

	SUP_RW_REF_PROPERTY_PREFIX_DEF(protected, Vec2, m_vInitialPos, InitialPos, Vec2);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(protected, Vec2, m_vNewInitialPos, NewInitialPos, Vec2);
	SUP_TYPEDEF_LIST_INSTS(MonsterBase*, MonsterWidgets);

	inline EGameItemType getItemType()const{ return m_eType; };
	inline ImageView* getItemImage()const{ return m_pImage; };
	inline Item* getItem()const { return m_pItem; };
	inline MonsterWidgets& getMonsterWidgets() { return m_oMonsterWidgets; };
	inline MonsterBase* getTriggerMonster() { return m_triggerMonster; };
	inline bool getIsOpen()const{ return m_bOpen; };
	inline bool getIsLock()const{ return m_bLock; };
	void stopEffectPlaying(float dt);
	void releaseYaogaoImg();
	void addYagaoImg();
protected:
	ActionTimeline* m_pActionTimeline;
	Node* m_pTimelineNode;
	ImageView* m_pImage;
	ImageView* m_pLock;
	EGameItemType m_eType;
	Item* m_pItem;

	MonsterWidgets m_oMonsterWidgets;
	MonsterBase* m_triggerMonster;

	EItemAniType m_eTarget;

	bool m_bLock;
	bool m_bOpen;

	bool m_bShowImage;

	ImageView* m_pTempExImg;

	bool m_isEffectPlaying;
	ImageView* m_pStar;
	ImageView* m_pTip;

private:
	DrawNode* drawNode;
	DrawNode* drawNode2;


};

#endif