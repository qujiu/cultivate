#include "MenuControl.h"
#include "../../SDK/SupSDK.h"
#include "MessageBox.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "GUI/UIManager.h"

#define BAOXIANG_Child_Tag 90000
MenuControl::MenuControl()
:m_bFlag(true)
{

}

MenuControl::~MenuControl()
{

}

bool MenuControl::init()
{
	if (BaseControl::init())
	{
		pLayout = CSLoader::createNode("menu.csb");
		this->addChild(pLayout, 1);

		m_pCommonPanel = dynamic_cast<Layout*>(pLayout->getChildByName("Panel_menu"));
		m_pCommonPanel->setPosition(ccp(m_pCommonPanel->getPositionX()*SUP_SCALE_X, m_pCommonPanel->getPositionY()*SUP_SCALE_Y));


		m_pSettingBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_shezhi"));
		m_pSettingBtn->addTouchEventListener(this, toucheventselector(MenuControl::onSettingButtonClicked));
		m_pSettingBtn->setPosition(ccp(m_pSettingBtn->getPositionX()*SUP_SCALE_X, m_pSettingBtn->getPositionY()*SUP_SCALE_Y));


		m_pgameBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_minigame"));
		m_pgameBtn->addTouchEventListener(this, toucheventselector(MenuControl::ongameButtonClicked));
		m_pgameBtn->setPosition(ccp(m_pgameBtn->getPositionX()*SUP_SCALE_X, m_pgameBtn->getPositionY()*SUP_SCALE_Y));

		auto pMoreBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_moregame"));
		pMoreBtn->setPosition(ccp(pMoreBtn->getPositionX()*SUP_SCALE_X, pMoreBtn->getPositionY()*SUP_SCALE_Y));
		pMoreBtn->addTouchEventListener(this, toucheventselector(MenuControl::onMoreButtonClicked));
		pMoreBtn->setZOrder(1);

		auto pCoinsBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_jifengqiang"));
		pCoinsBtn->setPosition(ccp(pCoinsBtn->getPositionX()*SUP_SCALE_X, pCoinsBtn->getPositionY()*SUP_SCALE_Y));
		pCoinsBtn->addTouchEventListener(this, toucheventselector(MenuControl::onCoinsButtonClicked));
		pCoinsBtn->setZOrder(1);

		m_pLeftBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_left"));
		m_pLeftBtn->addTouchEventListener(this, toucheventselector(MenuControl::onLeftButtonClicked));
		m_pLeftBtn->setPosition(ccp(m_pLeftBtn->getPositionX()*SUP_SCALE_X, m_pLeftBtn->getPositionY()*SUP_SCALE_Y));

		m_pRightBtn = dynamic_cast<Button*>(m_pCommonPanel->getChildByName("btn_right"));
		m_pRightBtn->addTouchEventListener(this, toucheventselector(MenuControl::onRightButtonClicked));
		m_pRightBtn->setPosition(ccp(m_pRightBtn->getPositionX()*SUP_SCALE_X, m_pRightBtn->getPositionY()*SUP_SCALE_Y));
		sup::SupActions::PulseNode(m_pRightBtn, 1.1f, 1.2f, 1.1f, true);


		m_pGoldBgImg = dynamic_cast<ImageView*>(pLayout->getChildByName("Img_Coin_Bg"));
		m_pGoldBgImg->setPosition(ccp(m_pGoldBgImg->getPositionX()*SUP_SCALE_X, m_pGoldBgImg->getPositionY()*SUP_SCALE_Y));

		m_pGoldgame = dynamic_cast<Button*>(m_pGoldBgImg->getChildByName("btn_jia"));
		m_pGoldgame->addTouchEventListener(this, toucheventselector(MenuControl::onStoreButtonClicked));

		m_TextGoldSum = dynamic_cast<Text*>(m_pGoldBgImg->getChildByName("Label_Coin"));
		m_pPlusImg = dynamic_cast<ImageView*>(m_pGoldBgImg->getChildByName("Image_plus"));
		m_pPlusImg->setVisible(false);
		setGoldTotalSum(EntityMgr::instance()->pPlayer()->getCurrGold());
		return true;
	}
	return false;
}

void MenuControl::setCommonPanelVisible(bool bVisible)
{
	m_pCommonPanel->setVisible(bVisible);
}
void MenuControl::setStoreBtnVisible(bool bVisible)
{
	m_pGoldgame->setVisible(bVisible);
}

void MenuControl::setSettingBtnVisible(bool bVisible)
{
	m_pSettingBtn->setVisible(bVisible);
}

void MenuControl::setSelectBtnVisible(bool bVisible)
{
	m_pSelectBtn->setVisible(bVisible);
}

void MenuControl::setLeftBtnVisible(bool bVisible)
{
	m_pLeftBtn->setVisible(bVisible);
}
void MenuControl::setgameBtnVisible(bool bVisible){

	m_pgameBtn->setVisible(bVisible);
}
void MenuControl::setRightBtnVisible(bool bVisible)
{
	m_pRightBtn->setVisible(bVisible);
}

void MenuControl::setGoldImgBtnVisible(bool bVisible)
{
	m_pGoldBgImg->setVisible(bVisible);
}
void MenuControl::setToDevBtnVisible(bool bVisible)
{
	m_sktPersonAni->setVisible(bVisible);
}
//void MenuControl::setPanelPosVisible(bool bVisible)
//{
//	if (bVisible)
//	{
//		tou = 0;
//
//	}
//	else{
//		tou = 1;
//
//	}
//	//m_pPanelPos->setVisible(bVisible);
//}

void MenuControl::setGoldsetTotalSum(int lSum)
{
	if (lSum > 99999)
	{
		m_TextGoldSum->setString("99999");
		m_pPlusImg->setVisible(true);
	}
	else
	{
		m_TextGoldSum->setString(sup::SupString::int2String(lSum));
		m_pPlusImg->setVisible(false);
	}
}

void MenuControl::setGoldTotalSum(int lSum)
{
	if (lSum > 99999)
	{
		m_TextGoldSum->setString("99999");
		m_pPlusImg->setVisible(true);
	}
	else
	{
		m_TextGoldSum->setString(sup::SupString::int2String(lSum));
		m_pPlusImg->setVisible(false);
	}

	auto pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCurrGold(lSum);
	pPlayer->saveTotalGoldSum();
}

void MenuControl::setGenXinTotalSum(Ref* object)
{
	int a = (int)object;
	if (a > 99999)
	{
		m_TextGoldSum->setString("99999");
		m_pPlusImg->setVisible(true);
	}
	else
	{
		m_TextGoldSum->setString(sup::SupString::int2String(a));
		m_pPlusImg->setVisible(false);
	}

	auto pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCurrGold(a);
	pPlayer->saveTotalGoldSum();
}

void MenuControl::buySuccess(Ref* object)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto iCurrBuyGold = pPlayer->getCurrBuyGold();
	if (iCurrBuyGold == -1)
	{
		pPlayer->saveNoAdsStatus();
		//SupSDK::instance()->hideBannerAD();
	}
	else
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GOLDFEIRU);
		setGoldTotalSum(pPlayer->getCurrGold() + iCurrBuyGold);
	}
}

void MenuControl::buyFailed(Ref* object)
{
	auto pForm = UIManager::instance()->findForm(IDC_Message);
	if (NULL != pForm)
	{
		return;
	}
	//¹ºÂòÊ§°Ü
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCurrBuyGold(0);

	showMessageBoxID("Item5");
}

void MenuControl::buyTimeout(Ref* object)
{
	auto pForm = UIManager::instance()->findForm(IDC_Message);
	if (NULL != pForm)
	{
		return;
	}
	//¹ºÂò³¬Ê±
	showMessageBoxID("Item6");
}

//bool MenuControl::onTouchBeginListener(Touch *touch, Event *unusedEvent)
//{
//	cocos2d::Rect triggerRect;
//	Vec2 pStartPos = touch->getStartLocation();
//	if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//ÓÎÏ·ÖÐ
//	{
//		if (tou == 1)
//		{
//			return true;
//		}
//		auto actoin = (SkeletonAnimation*)m_pPanelPos->getChildByTag(BAOXIANG_Child_Tag);
//		if (actoin != NULL)
//		{
//
//			Vec2 pos = m_sktPersonAni->convertToNodeSpace(pStartPos);
//
//			if (spPolygon_containsPoint(m_pCheckPoly, pos.x, pos.y))
//			{
//				//SupSDK::instance()->ShowUmEvent(GIFT_UM);
//
//
//				Player* pPlayer = EntityMgr::instance()->pPlayer();
//				pPlayer->setStoreis(false);
//				pPlayer->setimNotification(2);
//				//EntityMgr::instance()->pPlayer()->setimlucky(boxteg);
//
//				auto pForm = UIFactory::instance()->showVideoForm(1, 0);
//				if (NULL != pForm)
//				{
//					this->addChild(pForm, 10);
//				}
//			}
//		}
//	}
//	return true;
//}

void MenuControl::onMoreButtonClicked(Ref* sender, ui::TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		SupSDK::instance()->More();
	}
}


void MenuControl::onSelectButtonClicked(Ref *sender, ui::TouchEventType type)
{
	if (!m_bFlag)
	{
		return;
	}
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		showMessageBoxID("Item2", MBCall(MenuControl::onSelectBtnCallBack));
	}
}

void MenuControl::onSettingButtonClicked(Ref *sender, ui::TouchEventType type)
{
	if (!m_bFlag)
	{
		return;
	}
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);

		auto pForm = UIFactory::instance()->showSettingForm();
		if (NULL != pForm)
		{
			BabyCare::instance()->getCurrScene()->addChild(pForm, 10);
		}
	}
}

void MenuControl::ongameButtonClicked(Ref *sender, ui::TouchEventType type)
{
	if (!m_bFlag)
	{
		return;
	}
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);

	}
	else if (TOUCH_EVENT_ENDED == type)
	{

		Player* pPlayer = EntityMgr::instance()->pPlayer();

		BabyCare::instance()->gotoMinigame();
		pPlayer->setimNotification(4);
		SupSDK::instance()->hideOptAD();

	}
}

void MenuControl::onLeftButtonClicked(Ref *sender, ui::TouchEventType type)
{
	BabyCare::instance()->onStatusChanged(EScene_Select);
}

void MenuControl::onRightButtonClicked(Ref *sender, ui::TouchEventType type)
{
}

void MenuControl::onStoreButtonClicked(Ref *sender, ui::TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);

		auto pForm = UIFactory::instance()->showStoreForm();
		if (NULL != pForm)
		{
			BabyCare::instance()->getCurrScene()->addChild(pForm, 5);
		}
	}
}

void MenuControl::onCoinsButtonClicked(Ref *sender, ui::TouchEventType type)
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

//void MenuControl::onDevButtonClicked(Ref *sender, ui::TouchEventType type)
//{
//	if (TOUCH_EVENT_BEGAN == type)
//	{
//		//sup::SupActions::ButtonActionyuan((Node*)sender);
//		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
//
//	}
//	else if (TOUCH_EVENT_ENDED == type)
//	{
//		((Node*)sender)->setScale(1.0f);
//		Button* bu = ((Button*)sender);
//		Player* pPlayer = EntityMgr::instance()->pPlayer();
//		pPlayer->setStoreis(false);
//		pPlayer->setimNotification(2);
//		EntityMgr::instance()->pPlayer()->setimlucky(bu->getTag());
//
//		auto pForm = UIFactory::instance()->showVideoForm(0, bu->getTag());
//		if (NULL != pForm)
//		{
//			this->addChild(pForm, 10);
//		}
//
//		sup::SupActions::ButtonActionForever(pDevBtn);
//		{
//			pDevBtn->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f),
//				CallFunc::create([this](){
//				pDevBtn->setTouchEnabled(false);
//			}),
//				DelayTime::create(10),
//				CallFunc::create([this](){
//				int ccoun = random(1, 3);
//				string name = String::createWithFormat("res/common/common_advertis_button_lipinhe_0%d.png", ccoun)->getCString();
//				//auto native_static_res = EntityMgr::instance()->pPlayer()->getItemSubMenuList()->getItemSubMenuByID(179 + ccoun);
//				pDevBtn->loadTextureNormal(name.c_str(), TextureResType::LOCAL);
//				pDevBtn->setTag(ccoun);
//				//	pDevBtn->setScale(0.8);
//				pDevBtn->setTouchEnabled(true);
//			}), FadeIn::create(0.5f), DelayTime::create(10), NULL)));
//		}
//	}
//}

//void MenuControl::DropGiftTimer(float dt)
//{
//	Player* pPlayer = EntityMgr::instance()->pPlayer();
//
//	pDevBtn->runAction(Sequence::create(DelayTime::create(10), FadeOut::create(0.5f), DelayTime::create(10), FadeIn::create(5.0f),
//		CallFunc::create([this](){
//		int ccoun = random(1, 3);
//		string name = String::createWithFormat("res/common/common_advertis_button_lipinhe_0%d.png", ccoun)->getCString();
//		auto native_static_res = EntityMgr::instance()->pPlayer()->getToolList->getToolByID(ccoun);
//		pDevBtn->loadTextureNormal(name.c_str(), TextureResType::LOCAL);
//		pDevBtn->setTag(ccoun);
//		pDevBtn->setScale(0.8);
//	}), NULL));
//}