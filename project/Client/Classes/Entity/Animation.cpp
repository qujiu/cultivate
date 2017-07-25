
/*
** implement AniList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Animation.h"


/////////////////////////////////////////////////////////////////////////////

Ani::Ani(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setFilePath(value["FilePath"].GetString());
	setFileName(value["FileName"].GetString());
	setAniName(value["AniName"].GetString());
}

Ani::~Ani()
{

}


//////////////////////////////////////////////////////////////////////////////
AniList::AniList(const JsonValue &value)
{
	initAniList(value);
}


AniList::~AniList()
{
	releaseItemList();
}

void AniList::initAniList(const JsonValue &value)
{
	releaseItemList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_AniList.insert(make_pair(itemID, new Ani(itemValue)));
		}
	}
}

void AniList::releaseItemList()
{
	for (AnisIter pIter = m_AniList.begin(); pIter != m_AniList.end(); ++pIter)
    {
        delete pIter->second;
    }
	m_AniList.clear();
}

Ani* AniList::getAniByID(int itemID)
{
	AnisIter iter = m_AniList.find(itemID);
	if (iter != m_AniList.end())
	{
		return iter->second;
	}
	return NULL;
}
