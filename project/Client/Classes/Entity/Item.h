/*
** declare ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __ITEM_ENTITY_H__
#define __ITEM_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Item class
// -----------------------------------------------------------------------

class Item
{
public:
	Item(const JsonValue &value);
	virtual ~Item();

public:
	int getAniID(EItemAniType type);
	int getSoundID(EItemSoundType type, int& look);
public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nScene, Nscene, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_bLock, IsLock, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nNextOpen, NextOpen, int);
	//SUP_RW_REF_PROPERTY_PREFIX_DEF(private, EGameMonsterType, m_nMonsterType, MonsterType, EGameMonsterType);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImg, Img, string);
	//SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strTips, Tips, string);
	//SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Vec2, m_TipsPos, TipsPos, Vec2);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Rect, m_Trigger, Trigger, Rect);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Rect, m_MoveRect, MoveRect, Rect);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecSound, SoundsID, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecAnisID, AnisID, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Vec2, m_ConfigPos, ConfigPos, Vec2);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, EGameItemHitProcessId, m_nProcessID, ProcessID, EGameItemHitProcessId);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nRoleAniType, RoleAniType, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nBuyGold, BuyGold, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nAward, Award, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nBuyID, BuyID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strAwardImg, AwardImg, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nIsMultiple, IsMultiple, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strPanelName, PanelName, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImageName, ImageName, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecIconResID, IconResID, vector<int>);


};

// -----------------------------------------------------------------------
// implement ItemList class
// -----------------------------------------------------------------------
class ItemList : public Ref
{
public:
	ItemList(const JsonValue &value);
	~ItemList();

	SUP_TYPEDEF_MAP_INSTS(int, Item*, Items);

public:	
	void initItemList(const JsonValue &value);
	void releaseItemList();
    
	Item* getItemByID(int itemID);
private:
	Items m_ItemList;
}; 


#endif