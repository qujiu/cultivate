
#include "HomeSelectForm.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIFactory.h"
#include "../MiniControl.h"
#include "SDK/SupSDK.h"

HomeSelectForm::HomeSelectForm() :
Form(IDC_HomeSelect)
{
}

HomeSelectForm::~HomeSelectForm()
{

}

bool HomeSelectForm::init()
{
	if (Form::init())
	{
		return true;
	}

	return false;
}

