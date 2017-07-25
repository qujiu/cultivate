/*
** desc: 数据管理中心
** code: zhangchao
** date: 2014.05.21
*/

#include "ConfigDataCenter.h"

SINGLETON_DEFINE_INST(ConfigDataCenter);

//////////////////////////ConfigDataCenter//////////////////////////////////////////////////

ConfigDataCenter::~ConfigDataCenter()
{
	JsonReader::instance()->purgeAll();
}


const JsonValue& ConfigDataCenter::messageBox() const
{
	return JsonReader::instance()->open("Config/messageBox.json")[unsigned(0)];
}

void ConfigDataCenter::purgeMessageBox()
{
    JsonReader::instance()->purge("Config/messageBox.json");
}

const JsonValue& ConfigDataCenter::item()const
{
	return JsonReader::instance()->open("Config/Item.json");
}

void ConfigDataCenter::purgeItem()
{
	JsonReader::instance()->purge("Config/Item.json");
}


const JsonValue& ConfigDataCenter::monster(int nType) //怪物;
{
	m_nMonsterType = nType;
	return JsonReader::instance()->open("Config/Monster.json");
}

void ConfigDataCenter::purgeMonster()
{
	JsonReader::instance()->purge("Config/Monster.json");
}

const JsonValue& ConfigDataCenter::animation() const //动画;
{
	return JsonReader::instance()->open("Config/Ani.json");
}

void ConfigDataCenter::purgeAnimation()
{
	JsonReader::instance()->purge("Config/Ani.json");
}

const JsonValue& ConfigDataCenter::animationRole() const //动画;
{
	return JsonReader::instance()->open("Config/AniRole.json");
}

void ConfigDataCenter::purgeAnimationRole()
{
	JsonReader::instance()->purge("Config/AniRole.json");
}

const JsonValue& ConfigDataCenter::role() const
{
	return JsonReader::instance()->open("Config/Role.json");
}

void ConfigDataCenter::purgeRole()
{
	JsonReader::instance()->purge("Config/Role.json");
}

const JsonValue& ConfigDataCenter::foods() const
{
	return JsonReader::instance()->open("Config/Foods.json");
}

void ConfigDataCenter::purgeFoods()
{
	JsonReader::instance()->purge("Config/Foods.json");
}

const JsonValue& ConfigDataCenter::Level() const
{
	return JsonReader::instance()->open("Config/Level.json");
}

void ConfigDataCenter::purgeLevel()
{
	JsonReader::instance()->purge("Config/Level.json");
}


const JsonValue& ConfigDataCenter::Lucky() const
{
	return JsonReader::instance()->open("res/Config/Lucky.json");
}

void ConfigDataCenter::purgeLucky()
{
	JsonReader::instance()->purge("res/Config/Lucky.json");
}


const JsonValue& ConfigDataCenter::tool() const //动画;
{
	return JsonReader::instance()->open("Config/Tool.json");
}

const JsonValue& ConfigDataCenter::itemtool() const //动画;
{
	return JsonReader::instance()->open("Config/ItemTool.json");
}

void ConfigDataCenter::purgeTool()
{
	JsonReader::instance()->purge("Config/Tool.json");
}

void ConfigDataCenter::purgeItemTool()
{
	JsonReader::instance()->purge("Config/ItemTool.json");
}
//////////////////////////////////////////////////////////