/*
** declare MonsterList of my client
** author: zhangchao;
** date: 2014.10.11
*/

#ifndef __MONSTER_ENTITY_H__
#define __MONSTER_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "GameType.h"
#include "ResManager/ConfigDataCenter.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Monster class
// -----------------------------------------------------------------------

class Monster
{
public:
	Monster(const JsonValue &value);
	virtual ~Monster();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, EGameRoom, m_eMSceneID, MSceneID, EGameRoom);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, EGameMonsterType, m_eMType, MType, EGameMonsterType);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_eMItemType, MItemType, vector<int>);//EGameItemType
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, MID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strPicture, MPicture, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Vec2, m_MPos, MPos, Vec2);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, bool, m_bVisible, MVisible, bool);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nDoneNum, DoneNum, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nFlag, MFlag, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nRotation, MRotation, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nParticle, MParticle, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nAniID, MAniID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nZorder, Zorder, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nNextID, NextID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nNextType, NextType, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nValid, Valid, int);
};

// -----------------------------------------------------------------------
// implement ItemList class
// -----------------------------------------------------------------------
class MonsterList : public Ref
{
public:
	MonsterList();
	~MonsterList();

	SUP_TYPEDEF_LIST_INSTS(Monster*, Monsters);
	SUP_TYPEDEF_MAP_INSTS(int, Monsters*, MonsterType);
	SUP_TYPEDEF_MAP_INSTS(EGameRoom, MonsterType*, MonsterScene);
public:	
	void initMonsterList(void);
	void initMonsterList(const JsonValue &value);
	void releaseMonsterList();

	void removeMonster(EGameRoom secenID, EGameMonsterType typeID, int MonsterID);
	void removeMonster(Monster* pMonster);

	MonsterType* getMonsterType(EGameRoom sceneID);
	Monsters* getMonsters(EGameRoom secenID, EGameMonsterType tpye);
	Monster* getMonster(EGameRoom secenID, EGameMonsterType typeID, int MonsterID);
private:
	MonsterScene m_Monsters;
}; 


#endif