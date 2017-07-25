#include "GameForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "../UIMask.h"
#include "../Form/UILuckyForm.h"
#include "GUI/Game/BabyRoomForm.h"

#define SubmenuList_Item_Lock_Tag   10000


GameForm::GameForm(WINDOW_ID id) : Form(id)
, m_eItemTarget(EGameItemTarget_Normal)
, m_pCurrItem(NULL)
, m_bCurTouch(false)
, m_isShowJindutiaoTexiao(false)
, m_iSubmenuItemID(-1)
, m_bTouchEnable(true)
, m_isClickSelect(true)
, m_isDoubleRewardsCoins(false)
, m_pRewardImg(NULL)
, m_pSkWellDone(NULL)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameForm::afterBuyItemSuccessFunc), ENOTIFY_AFTERBUYITEMSUCCESSFUNC, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameForm::onupdateIcon), UPDATE_FREE, NULL);


}


GameForm:: ~GameForm()
{
	NotificationCenter::getInstance()->removeObserver(this, ENOTIFY_AFTERBUYITEMSUCCESSFUNC);
	NotificationCenter::getInstance()->removeObserver(this, UPDATE_FREE);

}

bool GameForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);
		return true;
	}
	return false;
}

void GameForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto isMulti = pPlayer->getItemList()->getItemByID(item_type)->getIsMultiple();
	auto vecIcon = pPlayer->getItemList()->getItemByID(item_type)->getIconResID();

	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			if (isMulti == 1)
			{
				auto pForm = dynamic_cast<BabyRoomForm*>(UIManager::instance()->findForm(IDC_BabyRoom));
				pForm->openToolBar();
				RefreshSubMenu(vecIcon);
			}
	
			m_pCurrItem->TouchBegin();
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
			break;
		case TOUCH_EVENT_MOVED:
			m_pCurrItem->TouchMove();
			break;
		case TOUCH_EVENT_ENDED:
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}

void GameForm::RefreshSubMenu(const vector<int>& icon_res_ids)
{
	m_pSubMenu->setVisible(true);
	auto pIconTemplete = dynamic_cast<ui::ImageView*>(m_pSubMenu->getChildByName("Img_templete"));
	m_pSubProp->removeAllChildren();
	pIconTemplete->setVisible(true);

	Vec2 start_pos = m_pSubProp->convertToNodeSpaceAR(pIconTemplete->convertToWorldSpaceAR(Vec2::ZERO));
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	float fGap = 10; 

	//winSize.width - m_pSubMenu->getContentSize().width*0.8, m_pSubMenu->getPositionY()

	//float fTotalWidth = (pIconTemplete->getContentSize().width + fGap) * icon_res_ids.size() + fGap;
	//start_pos.x = fTotalWidth > m_pSubProp->getContentSize().width ? fTotalWidth : m_pSubProp->getContentSize().width;

	float fTotalWidth = (pIconTemplete->getContentSize().width + fGap);
	start_pos.x = fTotalWidth;
	start_pos.y = pIconTemplete->getPositionY();

	Vec2 fPos = start_pos;

	for (int i = 0; i < icon_res_ids.size(); i++)
	{
		string strIcon = pPlayer->getIconResByID(icon_res_ids[i]);
		auto item_ui = ImageView::create(strIcon);
		if (i == 0)
		{
			fPos = ccp(fPos.x, fPos.y);
		}
		else
		{
			fPos = ccp(fPos.x + pIconTemplete->getContentSize().width + fGap, fPos.y);
		}
		item_ui->setPosition(fPos);
		item_ui->setVisible(true);
		item_ui->setTouchEnabled(true);
		m_pSubProp->addChild(item_ui);
		item_ui->setTag(icon_res_ids[i]);
		item_ui->addTouchEventListener(this, toucheventselector(GameForm::onSubMenuItemTouchListener));

		ItemTool* pSubMenu = pPlayer->getItemToolList()->getItemToolByID(icon_res_ids[i]);
		if (NULL != pSubMenu)
		{
			if (pSubMenu->getLock() == 1)
			{
				if (UserDefault::getInstance()->getBoolForKey(UNVIDEO) == true)
				{
					if (!pPlayer->GetSubMenuItemStatusByID(icon_res_ids[i]))
					{
						auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
						pLockImg->setTag(SubmenuList_Item_Lock_Tag);
						item_ui->addChild(pLockImg);
						pLockImg->setPosition(ccp(item_ui->getContentSize().width*0.8, item_ui->getContentSize().height*0.2));
						pLockImg->setScale(0.5);
					}
				}
				else
				{
					if (!pPlayer->GetSubMenuItemStatusByID(icon_res_ids[i]))
					{
						if (!pPlayer->GetVideoSubMenuItemStatusByID(icon_res_ids[i]))
						{
							auto pLockImg = ImageView::create("res/ui/common/commonl_button_shipin.png");
							pLockImg->setTag(SubmenuList_Item_Lock_Tag);
							item_ui->addChild(pLockImg);
							pLockImg->setPosition(ccp(item_ui->getContentSize().width*0.5, item_ui->getContentSize().height*0.1));
							pLockImg->setScale(0.8);
						}
					}
				}
			}
			else if (pSubMenu->getLock() == 2)
			{
				if (!pPlayer->GetSubMenuItemStatusByID(icon_res_ids[i]))
				{
					auto pLockImg = ImageView::create("res/ui/common/commonl_button_suo.png");
					pLockImg->setTag(SubmenuList_Item_Lock_Tag);
					item_ui->addChild(pLockImg);
					pLockImg->setPosition(ccp(item_ui->getContentSize().width*0.8, item_ui->getContentSize().height*0.2));
					pLockImg->setScale(0.5);
				}
			}
		}
	}
	auto size = m_pSubProp->getInnerContainerSize();
	size.width = fTotalWidth;
	m_pSubProp->setInnerContainerSize(size);
	m_pSubProp->jumpToRight();
	m_pSubProp->scrollToRight(0.5, false);
	pIconTemplete->setVisible(false);
}

void GameForm::onSubMenuItemTouchListener(Ref* ref, TouchEventType type)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	auto subMenuItemID = ((Node*)ref)->getTag();

	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		sup::SupActions::ButtonAction((Node*)ref);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		break;
	case TOUCH_EVENT_MOVED:
	case TOUCH_EVENT_CANCELED:
		break;
	case TOUCH_EVENT_ENDED:
		pPlayer->setimNotification(1);
		if (!JudgeSubmenuItemBuy(subMenuItemID))
		{
			return;
		}
		else
		{
			m_pCurrItem->RefreshToolImage(subMenuItemID);
		}
		break;
	}
}

bool GameForm::JudgeSubmenuItemBuy(int iID)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	auto native_static_res = pPlayer->getItemToolList()->getItemToolByID(iID);
	if (native_static_res->getLock() == 1)
	{
		if (UserDefault::getInstance()->getBoolForKey(UNVIDEO) == true)
		{
			if (!pPlayer->GetSubMenuItemStatusByID(iID))
			{
				m_iSubmenuItemID = iID;
				auto *pForm = UIFactory::instance()->showBuyTipForm(native_static_res->getPrice(), iID);
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
	else if (native_static_res->getLock() == 2)
	{
		if (!pPlayer->GetSubMenuItemStatusByID(iID))
		{
			m_iSubmenuItemID = iID;
			auto *pForm = UIFactory::instance()->showBuyTipForm(native_static_res->getPrice(), iID);
			if (NULL != pForm)
			{
				Director::getInstance()->getRunningScene()->addChild(pForm, 10);
			}
			return false;
		}
	}
	return true;
}

void GameForm::afterBuyItemSuccessFunc(Ref* object)
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
		auto *pForm = UIFactory::instance()->showCongratsForm(m_iSubmenuItemID);
		if (NULL != pForm)
		{
			Director::getInstance()->getRunningScene()->addChild(pForm, 10);
		}
	}
	m_iSubmenuItemID = -1;
}


void GameForm::refreshSubmenuLockStatus(int iID)
{
	auto pItem = (ImageView*)m_pSubProp->getChildByTag(iID);
	auto pLockImg = (ImageView*)pItem->getChildByTag(SubmenuList_Item_Lock_Tag);
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (pLockImg != NULL)
	{
		pLockImg->setVisible(false);
		pLockImg->removeAllChildrenWithCleanup(true);
	}

}

void GameForm::onupdateIcon(Ref* object)
{

	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (m_pCurrItem != nullptr)
	{
		auto Multiple = pPlayer->getItemList()->getItemByID(m_pCurrItem->getItemType())->getIsMultiple();
		if (Multiple == 0)
		{
			return;
		}

		auto vecIcon = pPlayer->getItemList()->getItemByID(m_pCurrItem->getItemType())->getIconResID();

		for (int i = 0; i < vecIcon.size(); i++)
		{
			auto pItem = (ImageView*)m_pSubProp->getChildByTag(vecIcon[i]);
			auto pLockImg = (ImageView*)pItem->getChildByTag(SubmenuList_Item_Lock_Tag);

			ItemTool* pSubMenu = pPlayer->getItemToolList()->getItemToolByID(vecIcon[i]);

			if (pLockImg != NULL && pSubMenu->getLock() == 1)
			{
				pItem->removeChild(pLockImg);
				if (pPlayer->GetVideoSubMenuItemStatusByID(vecIcon[i]))
				{
					continue;
				}
				if (SupSDK::instance()->canPlayVideo())
				{
					auto pLock = ImageView::create("res/ui/common/commonl_button_shipin.png");
					pLock->setTag(SubmenuList_Item_Lock_Tag);
					pItem->addChild(pLock);
					pLock->setPosition(ccp(pItem->getContentSize().width*0.5, pItem->getContentSize().height*0.1));
					pLock->setScale(0.8);
				}
				else
				{
					auto pLock = ImageView::create("res/ui/common/commonl_button_suo.png");
					pLock->setTag(SubmenuList_Item_Lock_Tag);
					pItem->addChild(pLock);
					pLock->setPosition(ccp(pItem->getContentSize().width*0.8, pItem->getContentSize().height*0.2));
					pLock->setScale(0.5);
				}
			}
		}
	}
}


void GameForm::initWellDownAni()
{
	m_pSkWellDone = SkeletonAnimation::createWithFile("res/Spine/welldone/welldone.json", "res/Spine/welldone/welldone.atlas", 1.0f);
	m_pSkWellDone->setPosition(Vec2(320, 720 * SUP_SCALE_Y));
	m_pSkWellDone->setScale(0.9f);
	m_pLayout->addChild(m_pSkWellDone, 15);

	m_pSkWellDone->setStartListener([&](int trackIndex){
		//SoundManage::instance()->stopMusic();
	});

	m_pSkWellDone->setEndListener([&](int trackIndex){
		//SoundManage::instance()->playMusic(RES_SOUND_ID_MUSIC_PALY);
		if (nullptr != m_pRewordFunc)
		{
			this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this](){
				removeWellDownAni();
				m_pRewordFunc();
				m_pRewordFunc = nullptr;
			}), NULL));
		}
		else if (nullptr != m_pNextFunc)
		{
			this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([this](){
				m_pNextFunc();
				m_pNextFunc = nullptr;
			}), NULL));
		}
	});

	m_pSkWellDone->setEventListener([&](int trackIndex, spEvent* event){
		if (0 == strcmp(event->data->name, "effect_lizi_zhuanquan"))
		{
			addRandPart(event->stringValue);
		}
		else if (0 == strcmp(event->data->name, "effect_star1"))
		{
			addRandPart(event->stringValue);
		}
		else if (0 == strcmp(event->data->name, "effect_star2"))
		{
			addRandPart(event->stringValue);
		}
		else if (0 == strcmp(event->data->name, "sound"))
		{
			//SoundManage::instance()->playSound(RES_SOUND_ID(event->intValue));
		}
	});
}
			   
void GameForm::playWellDownAni(bool bFlag)
{
	if (NULL == m_pSkWellDone)
		initWellDownAni();

	m_pSkWellDone->setVisible(true);
	m_pSkWellDone->setToSetupPose();
	m_pSkWellDone->setAnimation(0, "animation", false);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_WELLDONE);

	//m_pReturn->setVisible(false);
	//if (m_pMiniControl != NULL)
	//{
	//	m_pMiniControl->removeFromParentAndCleanup(true);
	//	m_pMiniControl = NULL;
	//}
	//if (m_pMenu != NULL)
	//{
	//	m_pMenu->removeFromParentAndCleanup(true);
	//	m_pMenu = NULL;
	//}
}

void GameForm::removeWellDownAni()
{
	if (NULL != m_pSkWellDone)
	{
		m_pSkWellDone->removeFromParentAndCleanup(true);
		m_pSkWellDone = NULL;
	}
}

void GameForm::addRandPart(std::string filePath)
{
	auto particle = ParticleSystemQuad::create("res/effect/" + filePath);
	m_pLayout->addChild(particle, 16);
	auto winSize = Director::getInstance()->getWinSize();
	int randPosX = rand() % ((int)winSize.width - 200) + 100;
	srand(time(0) + rand());
	int randPosY = rand() % ((int)winSize.height - 200) + 100;
	srand(time(0) + rand());

	particle->setPosition(m_pSkWellDone->getPosition());
}