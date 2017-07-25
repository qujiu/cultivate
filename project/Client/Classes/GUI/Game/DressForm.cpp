#include "BabyRoomForm.h"
#include "Entity/EntityMgr.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "DressForm.h"
#include "../Form/MenuControl.h"

#define SubmenuList_Item_Lock_Tag   10000
#define pTool_Panel_Tag   10001                   //1-100

DressForm::DressForm() :
GameForm(IDC_DressRoom)
, m_isOpen(false)
, m_iSubmenuItemID(-1)
, m_pCurrItemid(0)
, m_eUIStatus(EPorpUIStatus_1)
{
	const int m_pvecgirl[5] = { 0, 2, 4, 5, 6 };
	const int m_pvecboy[5] = { 7, 9, 11, 12, 13 };
	int eItemType[] = {37, 38, 39, 40, 41};
	for (int i = 0; i < (sizeof(eItemType) / sizeof(eItemType[0])); i++)
	{
		m_pcurrItem.push_back(eItemType[i]);
	}

	for (int i = 0; i < (sizeof(m_pvecboy) / sizeof(m_pvecboy[0])); i++)
	{
		m_pvecItemboy.push_back(m_pvecboy[i]);
	}

	for (int i = 0; i < (sizeof(m_pvecgirl) / sizeof(m_pvecgirl[0])); i++)
	{
		m_pvecItemgirl.push_back(m_pvecgirl[i]);
	}
	
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(DressForm::afterBuyItemSuccessFunc), ENOTIFY_AFTERBUYITEMSUCCESSFUNC, NULL);
}

DressForm::~DressForm()
{
	//SoundManage::instance()->stopSound();
	NotificationCenter::getInstance()->removeObserver(this, ENOTIFY_AFTERBUYITEMSUCCESSFUNC);

}

bool DressForm::init()
{
	if (GameForm::init())
	{
		setKeyboardEnabled(false);
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();


		m_pLayout = static_cast<Widget*>(CSLoader::createNode("DressRoom.csb"));
		this->addChild(m_pLayout);

		m_pToolBar = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_toolbar"));
		m_pToolBar->setPosition(ccp(winSize.width + m_pToolBar->getContentSize().width*0.5, m_pToolBar->getPositionY()));
		m_vecInitToolBar = m_pToolBar->getPosition();
		m_pToolBar->setZOrder(20);

		auto pCatspaw = dynamic_cast<ImageView*>(m_pToolBar->getChildByName("Image_catspaw"));
		m_pArrow = dynamic_cast<ImageView*>(pCatspaw->getChildByName("Image_arrow"));
		m_pArrow->addTouchEventListener(this, toucheventselector(DressForm::onArrowButtonClicked));
		m_vecArrowPos = m_pArrow->convertToWorldSpaceAR(Vec2::ZERO);



		for (int i = 0; i < m_pcurrItem.size(); i++)
		{
			auto pImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_" + sup::SupString::int2String(i + 1)));
			pImg->setPosition(ccp(pImg->getPositionX()*SUP_SCALE_X, pImg->getPositionY()*SUP_SCALE_Y));
			m_pItems[m_pcurrItem[i]] = ItemFactory::instance()->Create((EGameItemType)m_pcurrItem[i], pImg);
			pImg->setTag(i);
			pImg->setTouchEnabled(true);
			pImg->addTouchEventListener(this, toucheventselector(DressForm::onItemTouchListener));
			this->addChild(m_pItems[m_pcurrItem[i]]);
		}
		
		EntityMgr::instance()->pPlayer()->setisInitItem(true);
		InitRefreshItem();

		Form* pPlayerForm = NULL;
		pPlayerForm = UIFactory::instance()->showPlayerForm();
		if (NULL != pPlayerForm)
		{
			m_pLayout->addChild(pPlayerForm, 2);
		}

		return true;
	}
	return false;
}

void DressForm::onArrowButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
		if (!m_isOpen)
		{
			m_pToolBar->stopAllActions();
			m_pToolBar->setPosition(m_vecInitToolBar);
			auto moveto = MoveTo::create(0.5f, ccp(winSize.width - m_pToolBar->getContentSize().width*0.3, m_pToolBar->getPositionY()));
			m_pToolBar->runAction(Sequence::create(moveto, CallFunc::create([this](){
				m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_right.png");
				m_isOpen = true;
			}), NULL));
		}
		else
		{
			auto moveto = MoveTo::create(0.5f, m_vecInitToolBar);
			m_pToolBar->runAction(Sequence::create(moveto, CallFunc::create([this](){
				m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_left.png");
				m_isOpen = false;
			}), NULL));
		}
	}
}

void DressForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	auto m_pPlayer = EntityMgr::instance()->pPlayer();
	auto m_pcurItemId= ((Node*)ref)->getTag();
	m_pPlayer->setClickItemId(m_pcurItemId);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		sup::SupActions::ButtonAction((Node*)ref);
		break;
	case TOUCH_EVENT_MOVED:
		break;
	case TOUCH_EVENT_CANCELED:
		break;
	case TOUCH_EVENT_ENDED:
		int m_preId = m_pPlayer->getpreItemId();
		auto prePanel = pToolRolePanel->getChildByTag(m_preId);
		if (prePanel != NULL)
		{
			prePanel->setVisible(false);
			//pToolRolePanel->removeChildByTag(m_preId, true);
		}
		pTool = m_pPlayer->getToolList()->getToolByID(m_pvecItem[m_pcurItemId]);
		 if (pTool != NULL)
		 {
			auto  pToolPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pToolBar, pTool->getPanelName()));
			int tagId = pTool_Panel_Tag + m_pcurItemId;
			pToolPanel->setTag(tagId);
			m_pPlayer->setpreItemId(tagId);
			 pToolPanel->setVisible(true);
			 auto vecItem = pTool->getIconResID();
			 ItemScrollView = dynamic_cast<ui::ScrollView*>(pToolPanel->getChildByName("ItemScrollView"));
			 ItemScrollView->setScrollBarEnabled(false);
			 for (int i = 0; i < vecItem.size(); i++)
			 {
				 auto pItem = m_pPlayer->getItemToolList()->getItemToolByID(vecItem[i]);
				 if (pItem != NULL)
				 {
					 auto pItemImg = dynamic_cast<ImageView*>(ItemScrollView->getChildByName(pItem->getUI_Image()));
					 pItemImg->setTag(vecItem[i]);
					 pItemImg->setTouchEnabled(true);
					 pItemImg->addTouchEventListener(this, toucheventselector(DressForm::onItemToolTouchListener));

					 if (pItem->getLock() == 1)
					 {
						 if (UserDefault::getInstance()->getBoolForKey(UNVIDEO) == true)
						 {
							 if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
							 {
								 auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
								 pLockImg->setTag(SubmenuList_Item_Lock_Tag);
								 pItemImg->addChild(pLockImg);
								 pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.8, pItemImg->getContentSize().height*0.35));
							 }
						 }
						 else
						 {
							 if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
							 {
								 if (!m_pPlayer->GetVideoSubMenuItemStatusByID(vecItem[i]))
								 {
									 auto pLockImg = ImageView::create("res/ui/common/commonl_button_shipin.png");
									 pLockImg->setTag(SubmenuList_Item_Lock_Tag);
									 pItemImg->addChild(pLockImg);
									 pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.5, pItemImg->getContentSize().height*0.15));
								 }
							 }
						 }
					 }
					 else if (pItem->getLock() == 2)
					 {
						 if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
						 {
							 auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
							 pLockImg->setTag(SubmenuList_Item_Lock_Tag);
							 pItemImg->addChild(pLockImg);
							 pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.8, pItemImg->getContentSize().height*0.35));
						 }
					 }
				 }
			 }
		 }
		break;
	}

}

void DressForm::onItemToolTouchListener(Ref* ref, TouchEventType type)
{
	auto m_pPlayer = EntityMgr::instance()->pPlayer();
	auto m_iSubmenuItemID = ((Node*)ref)->getTag();
	m_eUIStatus = (EPorpUIStatus)(m_pPlayer->getClickItemId());
	m_pCurrItem = m_pItems[m_pcurrItem[m_eUIStatus]];
	int eType =m_pCurrItem->getItemType();
	int m_eType = eType > 37 ? 2 : 0;
	int m_eType_r = eType > 37 ? 2 : 1;
	int roleType = m_pPlayer->getCurrRoleType();
	int m_pcurItemId = m_pPlayer->getClickItemId();
	if (m_pCurrItem->getItemType() == EItem_xiuzi)
	{
		m_eType = 1;
	}
	Tool* pTool = m_pPlayer->getToolList()->getToolByID(m_pcurItemId + m_eType);
	Tool* pToolR = m_pPlayer->getToolList()->getToolByID(m_pcurItemId + m_eType_r);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		sup::SupActions::ButtonAction((Node*)ref);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		break;
	case TOUCH_EVENT_ENDED:
		if (!JudgeItemTool(m_iSubmenuItemID))
		{
			return;
		}
		if (roleType == 0)
		{
			if (m_pCurrItem->getItemType() == EItem_xiuzi)
			{

				m_pItems[EItem_xiuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_xiuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID + 5, (pToolR->getItemSkin()).c_str(), (pToolR->getItemAttachment()).c_str());
			}
			else if (m_pCurrItem->getItemType() == EItem_kuzi)
			{
				m_pItems[EItem_kuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_kuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID + 5, (pToolR->getItemSkin()).c_str(), (pToolR->getItemAttachment()).c_str());
			}
			else if (m_pCurrItem->getItemType() == EItem_xiezi)
			{ 
				string strskinleft = pTool->getItemSkin() + "left";
				string strskinright = pTool->getItemSkin() + "right";

				m_pItems[EItem_xiezi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, strskinleft.c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_xiezi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, strskinright.c_str(), (pTool->getItemAttachment()).c_str());
			}
			else
			{
				m_pCurrItem->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
			}
		}
		else
		{
			if (m_pCurrItem->getItemType() == EItem_xiuzi)
			{
				m_pItems[EItem_xiuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_xiuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID + 5, (pToolR->getItemSkin()).c_str(), (pToolR->getItemAttachment()).c_str());
			}
			else if (m_pCurrItem->getItemType() == EItem_kuzi)
			{
				m_pItems[EItem_kuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_kuzi]->RefreshItemAndMonsterImage(m_iSubmenuItemID + 4, (pToolR->getItemSkin()).c_str(), (pToolR->getItemAttachment()).c_str());
			}
			else if (m_pCurrItem->getItemType() == EItem_xiezi)
			{
				string strskinleft = pTool->getItemSkin() + "left";
				string strskinright = pTool->getItemSkin() + "right";

				m_pItems[EItem_xiezi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, strskinleft.c_str(), (pTool->getItemAttachment()).c_str());
				m_pItems[EItem_xiezi]->RefreshItemAndMonsterImage(m_iSubmenuItemID, strskinright.c_str(), (pTool->getItemAttachment()).c_str());
			}
			else
			{
				m_pCurrItem->RefreshItemAndMonsterImage(m_iSubmenuItemID, (pTool->getItemSkin()).c_str(), (pTool->getItemAttachment()).c_str());
			}
		}
		break;
	}
}

bool DressForm::JudgeItemTool(int iID)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto itemtool = pPlayer->getItemToolList()->getItemToolByID(iID);
	if (itemtool->getLock() == 1)
	{
		if (UserDefault::getInstance()->getBoolForKey(UNVIDEO) == true)
		{
			if (!pPlayer->GetSubMenuItemStatusByID(iID))
			{
				m_iSubmenuItemID = iID;
				auto *pForm = UIFactory::instance()->showBuyTipForm(itemtool->getPrice(), iID);
				if (NULL != pForm)
				{
					Director::getInstance()->getRunningScene()->addChild(pForm, 10);
				}
				return false;
			}
		}
		else
		{
			if (!pPlayer->GetSubMenuItemStatusByID(iID))
			{
				if (!pPlayer->GetVideoSubMenuItemStatusByID(iID))
				{
					m_iSubmenuItemID = iID;
					auto *pForm = UIFactory::instance()->showVideoForm(0, iID);
					if (NULL != pForm)
					{
						Director::getInstance()->getRunningScene()->addChild(pForm, 10);
					}
					return false;
				}
			}
		}
	}
	else if (itemtool->getLock() == 2)
	{
		if (!pPlayer->GetSubMenuItemStatusByID(iID))
		{
			m_iSubmenuItemID = iID;
			auto *pForm = UIFactory::instance()->showBuyTipForm(itemtool->getPrice(), iID);
			if (NULL != pForm)
			{
				Director::getInstance()->getRunningScene()->addChild(pForm, 10);
			}
			return false;
		}
	}
	return true;
}


void DressForm::afterBuyItemSuccessFunc(Ref* object)
{
	if (m_iSubmenuItemID == -1) return;
	auto pPlayer = EntityMgr::instance()->pPlayer();

	auto native_static_res = pPlayer->getItemToolList()->getItemToolByID(m_iSubmenuItemID);
	auto room_id = pPlayer->getItemToolList()->getItemToolByID(m_iSubmenuItemID)->getRoom();

	if (room_id == pPlayer->getCurrRoomType())
	{
		auto iNewGoldSum = pPlayer->getCurrGold() - native_static_res->getPrice();
		m_pMenuControl->setGoldTotalSum(iNewGoldSum);
		pPlayer->SetSubMenuItemStatusByID(m_iSubmenuItemID, true);

		refreshSubmenuLockStatus(m_iSubmenuItemID);
		/*	auto *pForm = UIFactory::instance()->showCongratulationForm(m_iSubmenuItemID);
		if (NULL != pForm)
		{
		Director::getInstance()->getRunningScene()->addChild(pForm, 10);
		}*/
	}
	m_iSubmenuItemID = -1;
}

void DressForm::refreshSubmenuLockStatus(int id)
{
	auto m_pPlayer = EntityMgr::instance()->pPlayer();
	int m_preId = m_pPlayer->getpreItemId();
	auto prePanel = pToolRolePanel->getChildByTag(m_preId);
	auto scrollView = dynamic_cast<ui::ScrollView*>(prePanel->getChildByName("ItemScrollView"));
	auto pItem = (ImageView*)scrollView->getChildByTag(id);
	auto pLockImg = (ImageView*)pItem->getChildByTag(SubmenuList_Item_Lock_Tag);

	if (pLockImg != NULL)
	{
		pLockImg->setVisible(false);
		pLockImg->removeAllChildrenWithCleanup(true);
	}
}

void DressForm::InitRefreshItem()
{
	Player* m_pPlayer = EntityMgr::instance()->pPlayer();
	m_pPlayer->setClickItemId(m_pCurrItemid);
	int roleType = m_pPlayer->getCurrRoleType();
	roleType = 0;
	if (roleType == 0)
	{
		pToolRolePanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pToolBar, "girl"));
		m_pvecItem.assign(m_pvecItemgirl.begin(), m_pvecItemgirl.end());
	}
	else
	{
		pToolRolePanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pToolBar, "boy"));
		m_pvecItem.assign(m_pvecItemboy.begin(), m_pvecItemboy.end());

	/*	for (int i = 0; i < (sizeof(m_pvecgirl) / sizeof(m_pvecgirl[0])); i++)
		{
			m_pvecItem.push_back(m_pvecgirl[i]);
		}*/
	}
	pToolRolePanel->setVisible(true);

	if (m_pPlayer->getisInitItem() == true)
	{
		pTool = m_pPlayer->getToolList()->getToolByID(m_pvecItem[m_pCurrItemid]);
		if (pTool != NULL)
		{
			auto pToolPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pToolBar, pTool->getPanelName()));
			int tagId = pTool_Panel_Tag + m_pCurrItemid;
			pToolPanel->setTag(tagId);
			m_pPlayer->setpreItemId(tagId);
			pToolPanel->setVisible(true);

			ItemScrollView = dynamic_cast<ui::ScrollView*>(pToolPanel->getChildByName("ItemScrollView"));
			ItemScrollView->setScrollBarEnabled(false);

			auto vecItem = pTool->getIconResID();
			int size = pTool->getIconResID().size();
			for (int i = 0; i < vecItem.size(); i++)
			{
				auto pItem = m_pPlayer->getItemToolList()->getItemToolByID(vecItem[i]);
				if (pItem != NULL)
				{
					auto pItemImg = dynamic_cast<ImageView*>(ItemScrollView->getChildByName(pItem->getUI_Image()));
					pItemImg->setTag(vecItem[i]);
					pItemImg->setTouchEnabled(true);
					//ItemScrollView->addChild(pItemImg);
					pItemImg->addTouchEventListener(this, toucheventselector(DressForm::onItemToolTouchListener));

					if (pItem->getLock() == 1)
					{
						if (UserDefault::getInstance()->getBoolForKey(UNVIDEO) == true)
						{
							if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
							{
								auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
								pLockImg->setTag(SubmenuList_Item_Lock_Tag);
								pItemImg->addChild(pLockImg);
								pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.8, pItemImg->getContentSize().height*0.35));
							}
						}
						else
						{
							if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
							{
								if (!m_pPlayer->GetVideoSubMenuItemStatusByID(vecItem[i]))
								{
									auto pLockImg = ImageView::create("res/ui/common/commonl_button_shipin.png");
									pLockImg->setTag(SubmenuList_Item_Lock_Tag);
									pItemImg->addChild(pLockImg);
									pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.5, pItemImg->getContentSize().height*0.15));
								}
							}
						}
					}
					else if (pItem->getLock() == 2)
					{
						if (!m_pPlayer->GetSubMenuItemStatusByID(vecItem[i]))
						{
							auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
							pLockImg->setTag(SubmenuList_Item_Lock_Tag);
							pItemImg->addChild(pLockImg);
							pLockImg->setPosition(ccp(pItemImg->getContentSize().width*0.8, pItemImg->getContentSize().height*0.35));
						}
					}
				}
			}
			auto scrollsize = ItemScrollView->getInnerContainerSize();
			ItemScrollView->setInnerContainerSize(scrollsize);
			ItemScrollView->jumpToRight();
			ItemScrollView->scrollToRight(0.5, false);
		}
	}
}


