
#include "SelectScene.h"
#include "../UIFactory.h"
#include "BabyCare.h"

SelectScene::SelectScene(void)
{

}

SelectScene::~SelectScene(void)
{
	//SoundManage::instance()->stopSound();
}

bool SelectScene::init()
{
	if (Scene::init())
	{
		m_pselectForm = NULL;
		m_pselectForm = UIFactory::instance()->showSelectForm();
		this->addChild(m_pselectForm);
		return true;
	}
	return false;
}

SelectScene* SelectScene::create()
{
	auto ret = new SelectScene();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

Form* SelectScene::getSelectForm()
{
	return m_pselectForm;
}

