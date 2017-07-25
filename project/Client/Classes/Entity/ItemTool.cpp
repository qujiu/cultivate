
/*
** implement ToolList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "ItemTool.h"

/////////////////////////////////////////////////////////////////////////////

ItemTool::ItemTool(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setIcon(value["Icon"].GetString());
	setImage(value["Image"].GetString());
	setScale(value["Scale"].GetInt());
	setLock(value["Lock"].GetInt());
	setPrice(value["Price"].GetInt());
	setRoom(value["Room"].GetInt());
	setPlist(value["Plist"].GetString());
	setUI_Image(value["UI_Image"].GetString());
}

ItemTool::~ItemTool()
{

}

//////////////////////////////////////////////////////////////////////////////
ItemToolList::ItemToolList(const JsonValue &value)
{
	initToolList(value);
}


ItemToolList::~ItemToolList()
{
	releaseToolList();
}

void ItemToolList::initToolList(const JsonValue &value)
{
	releaseToolList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &ToolValue = value[i];
			int ToolID = ToolValue["ID"].GetInt();
			m_ToolList.insert(make_pair(ToolID, new ItemTool(ToolValue)));
		}
	}
}

void ItemToolList::releaseToolList()
{
	for (ToolsIter pIter = m_ToolList.begin(); pIter != m_ToolList.end(); ++pIter)
	{
		delete pIter->second;
	}
	m_ToolList.clear();
}

ItemTool* ItemToolList::getItemToolByID(int ToolID)
{
	ToolsIter iter = m_ToolList.find(ToolID);
	return iter->second;
}

