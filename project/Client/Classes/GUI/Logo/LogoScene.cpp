#include "LogoScene.h"
#include "../UIFactory.h"

LogoScene::LogoScene(void)
{

}

LogoScene::~LogoScene(void)
{

}

bool LogoScene::init()
{
	if (Scene::init())
	{
		auto *pForm = UIFactory::instance()->showLogoForm();
		this->addChild(pForm);
		return true;
	}
	return false;
}

LogoScene* LogoScene::create()
{
	auto ret = new LogoScene();
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