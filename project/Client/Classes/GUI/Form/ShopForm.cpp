#include "ShopForm.h"
#include "GameType.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "SDK/SupSDK.h"

ShopForm :: ShopForm(EStoreUIType type) :
Form(IDC_Shop)
,m_eCurrStoreUIType(type)
{
}

ShopForm::~ShopForm()
{
}

bool ShopForm::init()
{
	if (Form::init())
	{
		return true;
	}
	return false;
}

