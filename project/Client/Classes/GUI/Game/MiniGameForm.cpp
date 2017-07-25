
#include "MiniGameForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "MiniGame/MiniGame.h"
#include "SDk/SupSDK.h"
MiniGameForm::MiniGameForm(bool bAgain) :
Form(IDC_MiniGame)
, m_bAgain(bAgain)
{

}

MiniGameForm::~MiniGameForm()
{

}

bool MiniGameForm::init()
{
	if (Form::init())
	{
		cocos2d::Size winSize = Director::getInstance()->getWinSize();

		m_pLayout = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("UI_MiniGame.json"));
		this->addChild(m_pLayout, 1);

		auto pBg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		pBg->setPositionX(pBg->getPositionX()*SUP_SCALE_X);

		auto pPropBg = dynamic_cast<ImageView*>(pBg->getChildByName("Image_prop_bg"));

		auto pMiniBtn = dynamic_cast<Button*>(pBg->getChildByName("Button_minigame"));
		pMiniBtn->addTouchEventListener(this, toucheventselector(MiniGameForm::onMiniGameBtnClicked));

		auto pCloseBtn = dynamic_cast<Button*>(pBg->getChildByName("Button_close"));
		pCloseBtn->addTouchEventListener(this, toucheventselector(MiniGameForm::onCloseButtonClicked));

		BulgeNode(pBg, 0.0f, 1.0f);
		return true;
	}

	return false;
}


void MiniGameForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		//EntityMgr::instance()->pPlayer()->setUnLockItemID(-1);
		this->removeFromParentAndCleanup(true);
	}
}

void MiniGameForm::onMiniGameBtnClicked(Ref *sender, TouchEventType type)
{
	auto Index = ((Node*)sender)->getTag();
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//showPopAD();
		//EntityMgr::instance()->pPlayer()->setItemMini(true);
		Director::getInstance()->pushScene(MiniGame::loadMiniGame(true));
		BabyCare::instance()->SetResultCallback_None();
		this->removeFromParentAndCleanup(true);
	}
}