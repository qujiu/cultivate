#include "HomeScene.h"
#include "../UIFactory.h"

HomeScene::HomeScene(void)
{

}

HomeScene::~HomeScene(void)
{

}

bool HomeScene::init()
{
	if (Scene::init())
	{
		auto *pForm = UIFactory::instance()->showHomeForm();
		this->addChild(pForm);
		return true;
	}
	return false;
}

HomeScene* HomeScene::create()
{
	auto ret = new HomeScene();
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