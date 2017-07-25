#include "UnLockForm.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "GUI/UIFactory.h"
#include "SDK/SupSDK.h"

UnLockForm::UnLockForm() :
Form(IDC_UnLock),
m_eStoreType(EStoreUIType_Shop)
{
}

UnLockForm::~UnLockForm()
{
}

bool UnLockForm::init()
{
	if (Form::init())
	{
		return true;
	}
	return false;
}


