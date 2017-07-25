
/*
** implement RandomDataList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "RandomData.h"
#include "ResManager/ConfigDataCenter.h"
#include "SaveManager/SaveManage.h"
/////////////////////////////////////////////////////////////////////////////

RandomData::RandomData(const JsonValue &value)
{
	setRID(value["ID"].GetInt());
	setRSpaPool(sup::SupUtils::SplitStringToInt(value["SpaPool"].GetString()));
	setRMakeupPool(sup::SupUtils::SplitStringToInt(value["MakeupPool"].GetString()));
	setRDressPool(sup::SupUtils::SplitStringToInt(value["DressPool"].GetString()));
	setRLuckyPool(sup::SupUtils::SplitStringToInt(value["LuckyPool"].GetString()));

}

RandomData::~RandomData()
{

}


//////////////////////////////////////////////////////////////////////////////
RandomDataList::RandomDataList(const JsonValue &value)
{
	initRandomDataList(value);
}


RandomDataList::~RandomDataList()
{
	releaseRandomDataList();
}

void RandomDataList::initRandomDataList(const JsonValue &value)
{
	releaseRandomDataList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int RandomDataID = itemValue["ID"].GetInt();
			m_RandomDatas.insert(make_pair(RandomDataID, new RandomData(itemValue)));
		}
	}
}

void RandomDataList::releaseRandomDataList()
{
	for (RandomDatasIter pIter = m_RandomDatas.begin(); pIter != m_RandomDatas.end(); ++pIter)
	{
		delete pIter->second;
	}
	m_RandomDatas.clear();
}

RandomData* RandomDataList::getRandomDataByID(int nRandomDataID)
{
	RandomDatasIter iter = m_RandomDatas.find(nRandomDataID);
	if (iter != m_RandomDatas.end())
	{
		return iter->second;
	}
	return NULL;
}