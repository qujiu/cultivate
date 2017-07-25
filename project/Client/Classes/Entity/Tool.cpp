
/*
** implement ToolList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Tool.h"
#include "SoundManager/SoundManage.h"

/////////////////////////////////////////////////////////////////////////////

Tool::Tool(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setNscene(value["scene"].GetInt());
	setIsType(value["type"].GetInt());
	setIsMultiple(value["IsMultiple"].GetInt());
	setIconResID(sup::SupUtils::SplitStringToInt(value["IconResID"].GetString()));
	setPanelName(value["PanelName"].GetString());
	setItemSkin(value["Skin"].GetString());
	setItemAttachment(value["Attachment"].GetString());
}

Tool::~Tool()
{

}

//////////////////////////////////////////////////////////////////////////////
ToolList::ToolList(const JsonValue &value)
{
	initToolList(value);
}


ToolList::~ToolList()
{
	releaseToolList();
}

void ToolList::initToolList(const JsonValue &value)
{
	releaseToolList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &ToolValue = value[i];
			int ToolID = ToolValue["ID"].GetInt();
			m_ToolList.insert(make_pair(ToolID, new Tool(ToolValue)));
		}
	}
}

void ToolList::releaseToolList()
{
	for (ToolsIter pIter = m_ToolList.begin(); pIter != m_ToolList.end(); ++pIter)
	{
		delete pIter->second;
	}
	m_ToolList.clear();
}

Tool* ToolList::getToolByID(int ToolID)
{
	ToolsIter iter = m_ToolList.find(ToolID);
	return iter->second;
}

