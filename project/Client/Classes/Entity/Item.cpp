
/*
** implement ItemList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Item.h"
#include "SoundManager/SoundManage.h"

/////////////////////////////////////////////////////////////////////////////

Item::Item(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setNscene(value["scene"].GetInt());
	setAwardImg(value["AwardImage"].GetString());
	setImg(value["Image"].GetString());
	setIsLock(value["Lock"].GetInt());
	setNextOpen(value["NextOpen"].GetInt());
	setAward(value["Award"].GetInt());
	setBuyGold(value["BuyGold"].GetInt());
	setBuyID(value["BuyID"].GetInt());
	setTrigger(sup::SupUtils::toRect(value["Trigger"].GetString()));
	setSoundsID(sup::SupUtils::SplitStringToInt(value["SoundID"].GetString()));
	setAnisID(sup::SupUtils::SplitStringToInt(value["AniID"].GetString()));
	setConfigPos(sup::SupUtils::toPoint(value["ConfigPos"].GetString()));
	setProcessID((EGameItemHitProcessId)value["ProcessId"].GetInt());
	setRoleAniType(value["RoleAniType"].GetInt());
	setMoveRect(sup::SupUtils::toRect(value["MoveRange"].GetString()));
	setIsMultiple((EGameItemHitProcessId)value["IsMultiple"].GetInt());
	setPanelName(value["PanelName"].GetString());
	setImageName(value["ImageName"].GetString());
	setIconResID(sup::SupUtils::SplitStringToInt(value["IconResID"].GetString()));
}



Item::~Item()
{

}

int Item::getAniID(EItemAniType type)
{
	int size = m_vecAnisID.size();
	CC_ASSERT(type < size && type >= 0);
	return m_vecAnisID[type];
}

int Item::getSoundID(EItemSoundType type, int& look)
{
	int size = m_vecSound.size();
	CC_ASSERT(type < size && type >= 0);
	auto id = m_vecSound[type];

	if (id != RES_SOUND_ID_NONE)
	{
		look = id / 100;
		return id % 100;
	}

	return RES_SOUND_ID_NONE;
}

//////////////////////////////////////////////////////////////////////////////
ItemList::ItemList(const JsonValue &value)
{
	initItemList(value);
}


ItemList::~ItemList()
{
	releaseItemList();
}

void ItemList::initItemList(const JsonValue &value)
{
	releaseItemList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_ItemList.insert(make_pair(itemID, new Item(itemValue)));
		}
	}
}

void ItemList::releaseItemList()
{
	for (ItemsIter pIter = m_ItemList.begin(); pIter != m_ItemList.end(); ++pIter)
    {
        delete pIter->second;
    }
	m_ItemList.clear();
}

Item* ItemList::getItemByID(int itemID)
{
	ItemsIter iter = m_ItemList.find(itemID);
    return iter->second;
}

