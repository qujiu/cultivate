/*
** declare AniList of my client
** author: zhangchao;
** date: 2014.10.14
*/

#ifndef __ANIMATION_ENTITY_H__
#define __ANIMATION_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

#define _ANI_ID_NULL_					0

// -----------------------------------------------------------------------
// implement Ani class
// -----------------------------------------------------------------------

class Ani
{
public:
	Ani(const JsonValue &value);
	virtual ~Ani();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strFilePath, FilePath, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strFileName, FileName, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strAniName, AniName, string);
};

// -----------------------------------------------------------------------
// implement AniList class
// -----------------------------------------------------------------------
class AniList : public Ref
{
public:
	AniList(const JsonValue &value);
	~AniList();

	SUP_TYPEDEF_MAP_INSTS(int, Ani*, Anis);

public:	
	void initAniList(const JsonValue &value);
	void releaseItemList();
    
	Ani* getAniByID(int itemID);

private:
	Anis m_AniList;
}; 


#endif //__ANIMATION_ENTITY_H__