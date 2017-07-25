/*
** desc: 数据管理中心;
** code: zhang chao;
** date: 2014.09.29
*/
#ifndef	__CONFIGDATACENTER_H__
#define __CONFIGDATACENTER_H__

#include "../Json/JsonReader.h"


class ConfigDataCenter : public sup::Singleton<ConfigDataCenter> 
{ 
private:
	SINGLETON_FRIEND_SUB(ConfigDataCenter);
public:
	~ConfigDataCenter();

public:
    const JsonValue& messageBox()const; //确认信息框;
    void purgeMessageBox();

	const JsonValue& item()const; //道具;
	void purgeItem();

	const JsonValue& monster(int nType); //怪物;
	void purgeMonster();

	const JsonValue& animation()const; //动画;
	void purgeAnimation();

	const JsonValue& animationRole()const; //动画;
	void purgeAnimationRole();

	const JsonValue& role()const; //人物;
	void purgeRole();

	const JsonValue& foods()const; //食材;
	void purgeFoods();

	const JsonValue& Level() const;
	void purgeLevel();


	const JsonValue& Lucky()const; //抽奖
	void purgeLucky();

	const JsonValue& tool() const;
	void purgeTool();

	const JsonValue& itemtool() const;
	void purgeItemTool();
private:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nMonsterType, MonsterType, int);
};

//class TextRes : public sup::Singleton<TextRes>
//{
//public:
//	string getText(const string& key) const;
//};

#endif //__CONFIGDATACENTER_H__