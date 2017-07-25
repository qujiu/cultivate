#include "Role.h"
#include "ResManager/ConfigDataCenter.h"
#include "SaveManager/SaveManage.h"
/////////////////////////////////////////////////////////////////////////////

Role::Role(const JsonValue &value)
{
	setRID(value["ID"].GetInt());
	setIsLock(value["Lock"].GetInt());
	setBabyAnisID(sup::SupUtils::SplitStringToInt(value["BabyAni"].GetString()));
}

Role::~Role()
{

}

const int Role::getBabyAniID(int index) const
{
	CC_ASSERT(index >= 0 && index < EBabyExpression_Max);
	return m_BabyAnisID[index];
}

//////////////////////////////////////////////////////////////////////////////
RoleList::RoleList(const JsonValue &value)
{
	initRoleList(value);
}


RoleList::~RoleList()
{
	releaseRoleList();
}

void RoleList::initRoleList(const JsonValue &value)
{
	releaseRoleList();
	if (value.IsArray())
	{
		for (unsigned int i = 0; i < value.Size(); i++)
		{
			const JsonValue &itemValue = value[i];
			int roleID = itemValue["ID"].GetInt();
			m_Roles.insert(make_pair(roleID, new Role(itemValue)));
		}
	}
}

void RoleList::releaseRoleList()
{
	for (RolesIter pIter = m_Roles.begin(); pIter != m_Roles.end(); ++pIter)
    {
		delete pIter->second;
    }
	m_Roles.clear();
}

Role* RoleList::getRoleByID(int nRoleID)
{
	RolesIter iter = m_Roles.find(nRoleID);
	if (iter != m_Roles.end())
	{
		return iter->second;
	}
	return NULL;
}