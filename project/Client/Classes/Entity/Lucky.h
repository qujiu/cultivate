/*
** declare LuckyList of my client
** author: zhangchao;
** date: 2014.10.17
*/

#ifndef __Lucky_ENTITY_H__
#define __Lucky_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Lucky class
// -----------------------------------------------------------------------

class Lucky
{
public:
	Lucky(const JsonValue &value);
	virtual ~Lucky();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_ID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_ItemsubID, ItemsubID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_Name, Name, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_Price, Price, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_probability, probability, int);

};

// -----------------------------------------------------------------------
// implement LuckyList class
// -----------------------------------------------------------------------
class LuckyList : public Ref
{
public:
	LuckyList(const JsonValue &value);
	~LuckyList();

	SUP_TYPEDEF_MAP_INSTS(int, Lucky*, Luckys);

public:
	void initLuckyList(const JsonValue &value);
	void releaseLuckyList();

	Lucky* getLuckyByID(int nLuckyID);
private:
	Luckys m_Luckys;
};


#endif