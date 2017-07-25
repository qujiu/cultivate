#ifndef __ROLE_ANIMATION_ENTITY_H__
#define __ROLE_ANIMATION_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement RoleAni class
// -----------------------------------------------------------------------

class RoleAni
{
public:
	RoleAni(const JsonValue &value);
	virtual ~RoleAni();

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nSpine, Spine, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<std::string>, m_strJsonPath, JsonPath, vector<std::string>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<std::string>, m_strAtlasName, AtlasName, vector<std::string>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strAniName, AniName, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strAndroidSound, AndroidSound, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<std::string>, m_strSpriteFrameName, SpriteFrameName, vector<std::string>);
	vector<std::string> getAniJsonPool(int type);
	vector<std::string> getAniAtlasPool(int type);
	vector<std::string> getAniSpriteFrameNamePool(int type);
};

// -----------------------------------------------------------------------
// implement AniList class
// -----------------------------------------------------------------------
class RoleAniList : public Ref
{
public:
	RoleAniList(const JsonValue &value);
	~RoleAniList();
	SUP_TYPEDEF_MAP_INSTS(int, RoleAni*, RoleAnis);
public:
	void initAniList(const JsonValue &value);
	void releaseItemList();
	RoleAni* getAniByID(int itemID);
private:
	RoleAnis m_AniList;
};
#endif //__ANIMATION_ENTITY_H__