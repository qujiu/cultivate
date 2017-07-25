#include "LoadingForm.h"
#include "GUI/UIManager.h"
#include "SDK/SupSDK.h"
#include "GUI/UIFactory.h"
#include "BabyCare.h"

LoadingForm::LoadingForm() :
Form(IDC_Loading)
{

}

LoadingForm::~LoadingForm()
{

}

bool LoadingForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);

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

		schedule(schedule_selector(LoadingForm::updateComplete), 3.0f);

		return true;
	}

	return false;
}

void LoadingForm::updateComplete(float t)
{
	this->removeFromParentAndCleanup(true);

	BabyCare::instance()->onStatusChanged(EScene_Game);
}

//////////////////////////////////////////////////////////