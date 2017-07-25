
#include "StoreForm.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"
#include "../../MiniGame/MiniGame.h"
#include "../Game/GameForm.h"

StoreForm::StoreForm() :
Form(IDC_Store)
, m_bClickBuyItem(true)
{
	int eItemType[] = { 1, 2 };
	for (int i = 0; i < (sizeof(eItemType) / sizeof(eItemType[0])); i++)
	{
		m_vItems.push_back(eItemType[i]);
	}
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(StoreForm::onRemoveCallback), REMOVE_STORY, NULL);
}

StoreForm::~StoreForm()
{
	NotificationCenter::getInstance()->removeObserver(this, REMOVE_STORY);
}

bool StoreForm::init()
{
	if (Form::init())
	{
		EntityMgr::instance()->pPlayer()->setimNotification(0);

		setKeyboardEnabled(false);

		Player* pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->setisglob(0);

		auto pStore = CSLoader::createNode("store.csb");
		this->addChild(pStore, 1);

		m_pGeceng = dynamic_cast<Layout*>(pStore->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		m_pGeceng->setPosition(ccp(m_pGeceng->getPositionX()*SUP_SCALE_X, m_pGeceng->getPositionY()*SUP_SCALE_Y));
		m_pBg = dynamic_cast<ImageView*>(pStore->getChildByName("Image_bg"));
		m_pBg->setPosition(ccp(m_pBg->getPositionX()*SUP_SCALE_X, m_pBg->getPositionY()*SUP_SCALE_Y));

		auto m_pguang = dynamic_cast<Sprite*>(m_pBg->getChildByName("biaoti_guang_1"));
		m_pguang->setZOrder(-1);

		auto pClose = dynamic_cast<ImageView*>(m_pBg->getChildByName("Image_close"));
		pClose->addTouchEventListener(this, toucheventselector(StoreForm::onCloseButtonClicked));
		pClose->setTouchEnabled(true);


		auto pIconTemplete = dynamic_cast<ui::ImageView*>(m_pBg->getChildByName("Image_minigame"));
		pIconTemplete->addTouchEventListener(this, toucheventselector(StoreForm::onBuygameButtonClicked));

		auto pIconTempletegame = dynamic_cast<ui::ImageView*>(m_pBg->getChildByName("Image_video"));
		pIconTempletegame->addTouchEventListener(this, toucheventselector(StoreForm::onBuyGoldButtonClicked));

		auto pCoinsBtn = dynamic_cast<ImageView*>(m_pBg->getChildByName("Image_coins"));
		pCoinsBtn->addTouchEventListener(this, toucheventselector(StoreForm::onCoinsButtonClicked));

		pDollarSum = dynamic_cast<TextAtlas*>(pIconTempletegame->getChildByName("AtlasLabel_playcount"));
		long long  co = UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM);
		pDollarSum->setString(sup::SupString::int2String(co) + "/" + sup::SupString::int2String(PLAY_UNVIDEO_COUNT));
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);

		return true;
	}
	return false;
}

void StoreForm::onCoinsButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		SupSDK::instance()->showOffer();
	}
}

void StoreForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		((ImageView*)sender)->setTouchEnabled(false);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANGSHOUHUI);
		m_pBg->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(StoreForm::onCloseButtonCallback))));
	}
}

void StoreForm::onRemoveCallback(Ref* object)
{
	this->removeFromParentAndCleanup(true);
	if (BabyCare::instance()->getCurrSceneID() == EScene_Home)
	{
		showMessageBoxID("Item4");
	}
}
void StoreForm::onCloseButtonCallback()
{
	Director::getInstance()->getRunningScene()->removeChild(this);
}
void StoreForm::onBuygameButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		BabyCare::instance()->gotoMinigame();
		pPlayer->setimNotification(4);
		//SupSDK::instance()->hideOptAD();
	}
}
void StoreForm::onBuyGoldButtonClicked(Ref *sender, TouchEventType type)
{
	if (!m_bClickBuyItem)
	{
		return;
	}

	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto subMenuItemID = ((Node*)sender)->getTag();

	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		if (SupSDK::instance()->canPlayVideo())
		{
			if (UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM) <= 0)
			{
				///showMessageBoxID("Item1");
				return;
			}
			pPlayer->setStoreis(true);
			SupSDK::instance()->playVideo();
			pPlayer->setimNotification(4);

		}
		else
			showMessageBoxID("Item4");

		this->removeFromParentAndCleanup(true);

	}
}

void StoreForm::enableClickBuy(float dt)
{
	m_bClickBuyItem = true;
}
