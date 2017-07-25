/*
** declare ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __STORE_ENTITY_H__
#define __STORE_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement StorePack class
// -----------------------------------------------------------------------

class StorePack
{
public:
	StorePack(const JsonValue &value);
	virtual ~StorePack();

public:
	//int getAniID(EItemAniType type);
	//int getSoundID(EItemSoundType type);
public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strKey, Key, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, float, m_fPrice, Price, float);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nGold, Gold, int); //¶Ò»»¶àÉÙ½ð±Ò;
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImg, Img, string);
};

// -----------------------------------------------------------------------
// implement ItemList class
// -----------------------------------------------------------------------
class StoreList : public Ref
{
public:
	StoreList(const JsonValue &value);
	~StoreList();

	SUP_TYPEDEF_MAP_INSTS(int, StorePack*, Stores);

public:	
	void initPackList(const JsonValue &value);
	void releasePackList();
    
	StorePack* getStorePackByID(int ID);
private:
	Stores m_PackList;
}; 


#endif