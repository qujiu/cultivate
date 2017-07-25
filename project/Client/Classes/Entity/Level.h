/*
** declare ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __LEVEL_ENTITY_H__
#define __LEVEL_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement StorePack class
// -----------------------------------------------------------------------

class Level
{
public:
	Level(const JsonValue &value);
	virtual ~Level();

public:
	//int getAniID(EItemAniType type);
	//int getSoundID(EItemSoundType type);
public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nPrice, Price, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nOpen, Open, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImge, Imge, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecReward1ID, Reward1ID, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecReward2ID, Reward2ID, vector<int>);
};

// -----------------------------------------------------------------------
// implement ItemList class
// -----------------------------------------------------------------------
class LevelList : public Ref
{
public:
	LevelList(const JsonValue &value);
	~LevelList();

	SUP_TYPEDEF_MAP_INSTS(int, Level*, Levels);

public:	
	void initLevelList(const JsonValue &value);
	void releaseLevelList();
    
	Level* getLevelByID(int ID);
private:
	Levels m_LevelList;
}; 


#endif