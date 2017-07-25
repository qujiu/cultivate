#include "BuyCoinsForm.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "MiniGame/MiniGame.h"
#include "SDK/SupSDK.h"
#include "MessageBox.h"
#include "GUI/UIFactory.h"
#include "BabyCare.h"

BuyCoinsForm::BuyCoinsForm() :
Form(IDC_BuyCoins)
{
}

BuyCoinsForm::~BuyCoinsForm()
{
}

bool BuyCoinsForm::init()
{
	if (Form::init())
	{
		m_pLayout = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("UI_Buy.json"));
		this->addChild(m_pLayout, 1);

		auto pBg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_bg"));
		SupLayout::setRelativePos(pBg, pBg->getPosition(), SUP_ALIGNMENT_LB);
		BulgeNode(pBg, Vec2(.0f, 0.0f), Vec2(pBg->getScaleX(), pBg->getScaleY()));

		auto pPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pLayout, "Panel_bg"));
		SupLayout::setRelativePos(pPanel, pPanel->getPosition(), SUP_ALIGNMENT_LB);
		BulgeNode(pPanel, Vec2(.0f, 0.0f), Vec2(pPanel->getScaleX(), pPanel->getScaleY()));

		auto pColseButton = dynamic_cast<Button*>(Helper::seekWidgetByName(pPanel, "Button_close"));
		pColseButton->addTouchEventListener(this, toucheventselector(BuyCoinsForm::onCloseButtonClicked));

		auto pMiniGameButton = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_game"));
		pMiniGameButton->addTouchEventListener(this, toucheventselector(BuyCoinsForm::onMiniGameButtonClicked));
		delayShowNode(pMiniGameButton, 0.3f);

		auto pBuyButton = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_gold"));
		pBuyButton->addTouchEventListener(this, toucheventselector(BuyCoinsForm::onBuyButtonClicked));
		delayShowNode(pBuyButton, 0.3f);

		auto pPack = EntityMgr::instance()->pPlayer()->getStoreList()->getStorePackByID(EStore_JinBiBao3);
		pBuyButton->loadTexture(pPack->getImg(), Widget::TextureResType::PLIST);
		auto pText = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(pBuyButton, "AtlasLabel_gold"));
		pText->setStringValue(sup::SupString::int2String(pPack->getGold()));
		return true;
	}
	return false;
}

void BuyCoinsForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	if (TOUCH_EVENT_ENDED == type)
	{
		auto pBg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_bg"));
		auto pPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pLayout, "Panel_bg"));

		auto spawn = Spawn::create(ScaleTo::create(0.4f, 0.0f), RotateTo::create(0.4f, 90), NULL);
		pPanel->runAction(Sequence::create(spawn->clone(), CallFunc::create([this](){
			Director::getInstance()->getRunningScene()->removeChild(this);
		}), NULL));

		pBg->runAction(spawn->clone());
	}
}

void BuyCoinsForm::onBuyButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
	/*	if (SupSDK::instance()->isBillingSetupOK())
		{
			EntityMgr::instance()->pPlayer()->setCurrStoreType(EStoreUIType_Gold);
			EntityMgr::instance()->pPlayer()->setCurrBuyID(EStore_JinBiBao3);

			string str = EntityMgr::instance()->pPlayer()->getStoreList()->getStorePackByID(EStore_JinBiBao3)->getKey();
			SupSDK::instance()->purchaseItem(str);
		}
		else
		{
			EntityMgr::instance()->pPlayer()->setIsPopAD(false);
			showMessageBoxID("Item6");
		}*/
	}
}


void BuyCoinsForm::onMiniGameButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Director::getInstance()->pushScene(MiniGame::loadMiniGame(true));
		BabyCare::instance()->SetResultCallback_None();
		this->removeFromParentAndCleanup(true);
	}
}

void BuyCoinsForm::onIAPSuccessNot(Ref* objeck)
{
	/*auto type = EntityMgr::instance()->pPlayer()->getCurrBuyID();
	auto nGold = EntityMgr::instance()->pPlayer()->getStoreList()->getStorePackByID(EStore_JinBiBao3)->getGold();
	nGold = EntityMgr::instance()->pPlayer()->getCurrGold() + nGold;
	EntityMgr::instance()->pPlayer()->setCurrGold(nGold);
	SaveManage::instance()->setIntSave(SAVE_ID_INT_GOLD, nGold);

	NotificationCenter::getInstance()->postNotification(NOT_STORE_GOLD_COMPLETE);
	NotificationCenter::getInstance()->postNotification(NOT_GAME_GOID_UPDATA);

	auto pForm = UIFactory::instance()->showCongratsForm();
	if (NULL != pForm)
	{
		BabyCare::instance()->getCurrScene()->addChild(pForm, 10);
	}
	this->removeFromParentAndCleanup(true);*/
}