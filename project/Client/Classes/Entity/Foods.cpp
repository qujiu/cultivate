
/*
** implement ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Foods.h"
#include "SoundManager/SoundManage.h"

/////////////////////////////////////////////////////////////////////////////

Foods::Foods(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setNType(value["Type"].GetInt());
	setTargetImg(value["TargetImage"].GetString());
	setImg(value["Image"].GetString());
	setPrice(value["Price"].GetInt());
}

Foods::~Foods()
{

}


//////////////////////////////////////////////////////////////////////////////
FoodsList::FoodsList(const JsonValue &value)
{
	initFoodsList(value);
}


FoodsList::~FoodsList()
{
	releaseFoodsList();
}

void FoodsList::initFoodsList(const JsonValue &value)
{
	releaseFoodsList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_FoodsList.insert(make_pair(itemID, new Foods(itemValue)));
		}
	}
}

void FoodsList::releaseFoodsList()
{
	for (FoodssIter pIter = m_FoodsList.begin(); pIter != m_FoodsList.end(); ++pIter)
    {
        delete pIter->second;
    }
	m_FoodsList.clear();
}

Foods* FoodsList::getFoodsByID(int itemID)
{
	FoodssIter iter = m_FoodsList.find(itemID);
    return iter->second;
}

