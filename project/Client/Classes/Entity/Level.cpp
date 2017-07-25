
/*
** implement ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Level.h"
#include "SoundManager/SoundManage.h"

/////////////////////////////////////////////////////////////////////////////

Level::Level(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setPrice(value["Price"].GetInt());
	setOpen(value["IsOpen"].GetInt());
	setImge(value["BuyImg"].GetString());
	setReward1ID(sup::SupUtils::SplitStringToInt(value["Reward1ID"].GetString()));
}

Level::~Level()
{

}


//////////////////////////////////////////////////////////////////////////////
LevelList::LevelList(const JsonValue &value)
{
	initLevelList(value);
}


LevelList::~LevelList()
{
	releaseLevelList();
}

void LevelList::initLevelList(const JsonValue &value)
{
	releaseLevelList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_LevelList.insert(make_pair(itemID, new Level(itemValue)));
		}
	}
}

void LevelList::releaseLevelList()
{
	for (LevelsIter pIter = m_LevelList.begin(); pIter != m_LevelList.end(); ++pIter)
    {
        delete pIter->second;
    }
	m_LevelList.clear();
}

Level* LevelList::getLevelByID(int ID)
{
	LevelsIter iter = m_LevelList.find(ID);
    return iter->second;
}

