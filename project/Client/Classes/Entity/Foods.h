/*
** declare FoodsList of my client
** author: zhangchao;
** date: 2015.7.3
*/

#ifndef __FOODS_ENTITY_H__
#define __FOODS_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Item class
// -----------------------------------------------------------------------

class Foods
{
public:
	Foods(const JsonValue &value);
	virtual ~Foods();

public:

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nType, NType, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImg, Img, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strTargetImg, TargetImg, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nPrice, Price, int);
};

// -----------------------------------------------------------------------
// implement ItemList class
// -----------------------------------------------------------------------
class FoodsList : public Ref
{
public:
	FoodsList(const JsonValue &value);
	~FoodsList();

	SUP_TYPEDEF_MAP_INSTS(int, Foods*, Foodss);

public:	
	void initFoodsList(const JsonValue &value);
	void releaseFoodsList();
    
	Foods* getFoodsByID(int foodsID);
private:
	Foodss m_FoodsList;
}; 


#endif