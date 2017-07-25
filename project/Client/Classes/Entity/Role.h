#ifndef __ROLE_ENTITY_H__
#define __ROLE_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "GameType.h"
#include "ResManager/ConfigDataCenter.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Role class
// -----------------------------------------------------------------------

class Role
{
public:
	Role(const JsonValue &value);
	virtual ~Role();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, RID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, bool, m_bLock, IsLock, bool);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_BabyAnisID, BabyAnisID, vector<int>);
	const int getBabyAniID(int index) const;
};

// -----------------------------------------------------------------------
// implement RoleList class
// -----------------------------------------------------------------------
class RoleList : public Ref
{
public:
	RoleList(const JsonValue &value);
	~RoleList();

	SUP_TYPEDEF_MAP_INSTS(int, Role*, Roles);

public:	
	void initRoleList(const JsonValue &value);
	void releaseRoleList();
    
	Role* getRoleByID(int nRoleID);
private:
	Roles m_Roles;
}; 


#endif