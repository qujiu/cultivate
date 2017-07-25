/*
** desc: ���ݹ�������;
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
    const JsonValue& messageBox()const; //ȷ����Ϣ��;
    void purgeMessageBox();

	const JsonValue& item()const; //����;
	void purgeItem();

	const JsonValue& monster(int nType); //����;
	void purgeMonster();

	const JsonValue& animation()const; //����;
	void purgeAnimation();

	const JsonValue& animationRole()const; //����;
	void purgeAnimationRole();

	const JsonValue& role()const; //����;
	void purgeRole();

	const JsonValue& foods()const; //ʳ��;
	void purgeFoods();

	const JsonValue& Level() const;
	void purgeLevel();


	const JsonValue& Lucky()const; //�齱
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