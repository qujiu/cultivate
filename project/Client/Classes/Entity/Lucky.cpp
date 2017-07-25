
/*
** implement LuckyList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Lucky.h"
#include "ResManager/ConfigDataCenter.h"
#include "SaveManager/SaveManage.h"
/////////////////////////////////////////////////////////////////////////////

Lucky::Lucky(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setItemsubID(value["ItemsubID"].GetInt());
	setName(value["Name"].GetString());
	setPrice(value["Price"].GetInt());
	setprobability(value["probability"].GetInt());
}

Lucky::~Lucky()
{

}


//////////////////////////////////////////////////////////////////////////////
LuckyList::LuckyList(const JsonValue &value)
{
	initLuckyList(value);
}


LuckyList::~LuckyList()
{
	releaseLuckyList();
}

void LuckyList::initLuckyList(const JsonValue &value)
{
	releaseLuckyList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int LuckyID = itemValue["ID"].GetInt();
			m_Luckys.insert(make_pair(LuckyID, new Lucky(itemValue)));
		}
	}
}

void LuckyList::releaseLuckyList()
{
	for (LuckysIter pIter = m_Luckys.begin(); pIter != m_Luckys.end(); ++pIter)
	{
		delete pIter->second;
	}
	m_Luckys.clear();
}

Lucky* LuckyList::getLuckyByID(int nLuckyID)
{
	LuckysIter iter = m_Luckys.find(nLuckyID);
	if (iter != m_Luckys.end())
	{
		return iter->second;
	}
	return NULL;
}