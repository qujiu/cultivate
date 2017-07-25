#ifndef __SAVE_MANAGE_H__
#define __SAVE_MANAGE_H__

#include "SaveID.h"
#include "Common/Common.h"

class SaveManage : public sup::Singleton<SaveManage, Ref>
{	 
private:
	SINGLETON_FRIEND_SUB(SaveManage, Ref);
	SaveManage(void){};
	~SaveManage(void){};

public:
	int getIntSave(SAVE_ID saveID,int defaultValue = 0);
	void setIntSave(SAVE_ID saveID,int saveValue);


	float getFloatSave(SAVE_ID saveID,float defaultValue = 0.000000);
	void setFloatSave(SAVE_ID saveID,float saveValue);


	bool getBoolSave(SAVE_ID saveID,bool defaultValue = false);
	void setBoolSave(SAVE_ID saveID,bool saveValue);

	int getIntSave(string key, int defaultValue = 0);
	void setIntSave(string key, int saveValue);


	float getFloatSave(string key, float defaultValue = 0.000000);
	void setFloatSave(string key, float saveValue);


	bool getBoolSave(string key, bool defaultValue = false);
	void setBoolSave(string key, bool saveValue);
};

#endif