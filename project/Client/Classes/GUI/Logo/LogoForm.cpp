
#include "LogoForm.h"
#include "BabyCare.h"
#include "cocostudio/CCArmature.h"
#include "SDK/SupSDK.h"

LogoForm::LogoForm() :
Form(IDC_Logo)
{

}

LogoForm::~LogoForm()
{

}

bool LogoForm::init()
{
	if (Form::init())
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Plist/boy.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Plist/girl.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Plist/itemtool.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Plist/babyroom.plist");

		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		auto plogo = CSLoader::createNode("res/loading.csb");
		this->addChild(plogo);

		auto pBg = dynamic_cast<ImageView*>(plogo->getChildByName("Image_bg"));
		pBg->setPosition(ccp(pBg->getPositionX()*SUP_SCALE_X, pBg->getPositionY()*SUP_SCALE_Y));
		pBg->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		EntityMgr::instance()->createPlayer();

		auto pLoadingPanel = dynamic_cast<Layout*>(plogo->getChildByName("Panel_loading"));
		pLoadingPanel->setPosition(ccp(pLoadingPanel->getPositionX()*SUP_SCALE_X, pLoadingPanel->getPositionY()*SUP_SCALE_Y));
		auto pLoadingNode = CSLoader::createNode("res/ui/Ani_logo.csb");
		pLoadingPanel->addChild(pLoadingNode);
		auto pTimelineAction = CSLoader::createTimeline("res/ui/Ani_logo.csb");
		pLoadingNode->runAction(pTimelineAction);
		pTimelineAction->play("ani_loading", true);

		if (!SupSDK::instance()->palywang())//不能播放视屏
		{
			UserDefault::getInstance()->setBoolForKey(UNVIDEO, true);
			UserDefault::getInstance()->flush();
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey(UNVIDEO, false);
			UserDefault::getInstance()->flush();
		}

		schedule(schedule_selector(LogoForm::goHome), 3.0f);
		return true;
	}

	return false;
}

void LogoForm::goHome(float p)
{
	unschedule(schedule_selector(LogoForm::goHome));
	BabyCare::instance()->onStatusChanged(EScene_Home);
}