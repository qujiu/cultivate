/*
** declare RandomDataList of my client
** author: zhangchao;
** date: 2014.10.17
*/

#ifndef __RandomData_ENTITY_H__
#define __RandomData_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement RandomData class
// -----------------------------------------------------------------------

class RandomData
{
public:
	RandomData(const JsonValue &value);
	virtual ~RandomData();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, RID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecRSpaPool, RSpaPool, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecRMakeupPool, RMakeupPool, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecRDressPool, RDressPool, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecRLuckyPool, RLuckyPool, vector<int>);

};

// -----------------------------------------------------------------------
// implement RandomDataList class
// -----------------------------------------------------------------------
class RandomDataList : public Ref
{
public:
	RandomDataList(const JsonValue &value);
	~RandomDataList();

	SUP_TYPEDEF_MAP_INSTS(int, RandomData*, RandomDatas);

public:
	void initRandomDataList(const JsonValue &value);
	void releaseRandomDataList();

	RandomData* getRandomDataByID(int nRandomDataID);
private:
	RandomDatas m_RandomDatas;
};


#endif