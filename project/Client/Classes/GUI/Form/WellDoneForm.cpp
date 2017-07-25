#include "WellDoneForm.h"
#include "BabyCare.h"
#include "GUI/UIFactory.h"
#include "GUI/UIManager.h"
#include "SDK/SupSDK.h"
#include "GUI/Game/GameScene.h"

WellDoneForm::WellDoneForm() :
Form(IDC_WellDone)
{


}

WellDoneForm::~WellDoneForm()
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCanKeyReleased(true);
}

bool WellDoneForm::init()
{
	if (Form::init())
	{
		
	}
	return false;
}

void WellDoneForm::onResetButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		NodeElasticDisAppear(m_pBkImage, [this](){
		this->removeFromParentAndCleanup(true);

		EntityMgr::instance()->pPlayer()->getMonsterList()->releaseMonsterList();
		EntityMgr::instance()->pPlayer()->getMonsterList()->initMonsterList();
		EntityMgr::instance()->pPlayer()->initUseArr();

		//SupSDK::instance()->HideNativeAd();
		(dynamic_cast<GameScene*>(BabyCare::instance()->getCurrScene()))->m_pGameForm->removeFromParentAndCleanup(true);
		(dynamic_cast<GameScene*>(BabyCare::instance()->getCurrScene()))->GameUIInit();
		});
	}
}

void WellDoneForm::onNextButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//SupSDK::instance()->HideNativeAd();
		this->removeFromParentAndCleanup(true);
		NotificationCenter::getInstance()->postNotification(NOT_FORM_AWARD_CLOSE);
	}
}

