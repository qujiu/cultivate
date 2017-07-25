
/*
** implement ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Store.h"
#include "SoundManager/SoundManage.h"

/////////////////////////////////////////////////////////////////////////////

StorePack::StorePack(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setKey(value["Key"].GetString());
	setPrice(value["Price"].GetInt()*0.01f);
	setGold(value["Gold"].GetInt());
	setImg(value["Image"].GetString());
}

StorePack::~StorePack()
{

}


//////////////////////////////////////////////////////////////////////////////
StoreList::StoreList(const JsonValue &value)
{
	initPackList(value);
}


StoreList::~StoreList()
{
	releasePackList();
}

void StoreList::initPackList(const JsonValue &value)
{
	releasePackList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_PackList.insert(make_pair(itemID, new StorePack(itemValue)));
		}
	}
}

void StoreList::releasePackList()
{
	for (StoresIter pIter = m_PackList.begin(); pIter != m_PackList.end(); ++pIter)
    {
        delete pIter->second;
    }
	m_PackList.clear();
}

StorePack* StoreList::getStorePackByID(int ID)
{
	StoresIter iter = m_PackList.find(ID);
    return iter->second;
}

