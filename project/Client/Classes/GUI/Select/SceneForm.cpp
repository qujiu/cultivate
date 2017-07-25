#include "SceneForm.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "HomeSelectForm.h"
#include "../UIManager.h"
#include "SaveManager/SaveManage.h"

SceneForm::SceneForm() :
Form(IDC_Scene)
{

}

SceneForm::~SceneForm()
{
}

bool SceneForm::init()
{
	if (Form::init())
	{
		return true;
	}
	return false;
}

