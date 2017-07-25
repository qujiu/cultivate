#include "SaveManage.h"
#include "SaveMapping.h"

SINGLETON_DEFINE_INST(SaveManage, Ref);

int SaveManage::getIntSave(SAVE_ID saveID, int defaultValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	return UserDefault::getInstance()->getIntegerForKey(key,defaultValue);
}


void SaveManage::setIntSave(SAVE_ID saveID, int saveValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	UserDefault::getInstance()->setIntegerForKey(key, saveValue);
	UserDefault::getInstance()->flush();
}


float SaveManage::getFloatSave(SAVE_ID saveID, float defaultValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	return UserDefault::getInstance()->getFloatForKey(key,defaultValue);
}


void SaveManage::setFloatSave(SAVE_ID saveID, float saveValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	UserDefault::getInstance()->setFloatForKey(key, saveValue);
	UserDefault::getInstance()->flush();
}



bool SaveManage::getBoolSave(SAVE_ID saveID, bool defaultValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	return UserDefault::getInstance()->getBoolForKey(key,defaultValue);
}


void SaveManage::setBoolSave(SAVE_ID saveID, bool saveValue)
{
	char* key = SaveMapping::getSaveKey(saveID);

	UserDefault::getInstance()->setBoolForKey(key, saveValue);
	UserDefault::getInstance()->flush();
}

int SaveManage::getIntSave(string key, int defaultValue)
{
	return UserDefault::getInstance()->getIntegerForKey(key.c_str(), defaultValue);
}

void SaveManage::setIntSave(string key, int saveValue)
{
	UserDefault::getInstance()->getIntegerForKey(key.c_str(), saveValue);
	UserDefault::getInstance()->flush();
}


float SaveManage::getFloatSave(string key, float defaultValue)
{
	return UserDefault::getInstance()->getFloatForKey(key.c_str(), defaultValue);
}

void SaveManage::setFloatSave(string key, float saveValue)
{
	UserDefault::getInstance()->setFloatForKey(key.c_str(), saveValue);
	UserDefault::getInstance()->flush();
}


bool SaveManage::getBoolSave(string key, bool defaultValue)
{
	return UserDefault::getInstance()->getBoolForKey(key.c_str(), defaultValue);
}

void SaveManage::setBoolSave(string key, bool saveValue)
{
	UserDefault::getInstance()->setBoolForKey(key.c_str(), saveValue);
	UserDefault::getInstance()->flush();
}