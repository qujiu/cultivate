#include "RoleAnimation.h"


/////////////////////////////////////////////////////////////////////////////

RoleAni::RoleAni(const JsonValue &value)
{
	setID(value["ID"].GetInt());
	setSpine(value["Spine"].GetInt());
	setJsonPath(sup::SupUtils::SplitString(value["JsonPath"].GetString()));
	setAtlasName(sup::SupUtils::SplitString(value["AtlasName"].GetString()));
	setAniName(value["AniName"].GetString());
	setAndroidSound(value["AniSound"].GetString());
	setSpriteFrameName(sup::SupUtils::SplitString(value["SpriteFrameName"].GetString()));
}

RoleAni::~RoleAni()
{

}

vector<std::string> RoleAni::getAniJsonPool(int type)
{
	vector<std::string> result;
	for (int i = 0; i < m_strJsonPath.size(); i++)
	{
		vector<std::string> tmp;
		tmp = sup::SupUtils::SplitString_Special(m_strJsonPath[i], "|");
		if (type == 0)
		{
			result.push_back(tmp[0]);
		}
		else
		{
			result.push_back(tmp[1]);
		}
	}
	return result;
}

vector<std::string> RoleAni::getAniAtlasPool(int type)
{
	vector<std::string> result;
	for (int i = 0; i < m_strAtlasName.size(); i++)
	{
		vector<std::string> tmp;
		tmp = sup::SupUtils::SplitString_Special(m_strAtlasName[i], "|");
		if (type == 0)
		{
			result.push_back(tmp[0]);
		}
		else
		{
			result.push_back(tmp[1]);
		}
	}
	return result;
}

vector<std::string> RoleAni::getAniSpriteFrameNamePool(int type)
{
	vector<std::string> result;
	for (int i = 0; i < m_strSpriteFrameName.size(); i++)
	{
		vector<std::string> tmp;
		tmp = sup::SupUtils::SplitString_Special(m_strSpriteFrameName[i], "|");
		if (type == 0)
		{
			result.push_back(tmp[0]);
		}
		else
		{
			result.push_back(tmp[1]);
		}
	}
	return result;
}
//////////////////////////////////////////////////////////////////////////////
RoleAniList::RoleAniList(const JsonValue &value)
{
	initAniList(value);
}


RoleAniList::~RoleAniList()
{
	releaseItemList();
}

void RoleAniList::initAniList(const JsonValue &value)
{
	releaseItemList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int itemID = itemValue["ID"].GetInt();
			m_AniList.insert(make_pair(itemID, new RoleAni(itemValue)));
		}
	}
}

void RoleAniList::releaseItemList()
{
	for (RoleAnisIter pIter = m_AniList.begin(); pIter != m_AniList.end(); ++pIter)
	{
		delete pIter->second;
	}
	m_AniList.clear();
}

RoleAni* RoleAniList::getAniByID(int itemID)
{
	RoleAnisIter iter = m_AniList.find(itemID);
	if (iter != m_AniList.end())
	{
		return iter->second;
	}
	return NULL;
}
