#include "ItemWidget.h"
#include "Entity/EntityMgr.h"
#include "GUI/UIManager.h"
#include "GUI/UIFactory.h"
#include "SaveManager/SaveManage.h"
#include "GUI/Game/MakeForm.h"
#include "GUI/Form/BabyControl.h"
#include "GUI//Game/MuyuRoomForm.h"

ItemWidget::ItemWidget(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemWidget::~ItemWidget(){
}

bool ItemWidget::init()
{
	if (ItemBase::init())
	{
		if (NULL != m_pActionTimeline)
		{
			int nAniID = m_pItem->getAniID(EItemAniType_OnHit);
			Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
			m_pActionTimeline->setAnimationEndCallFunc(pAni->getAniName(), CC_CALLBACK_0(ItemBase::AnimationMovementEventListener, this));
		}
		return true;
	}
	return false;
}

bool ItemWidget::onTriggerMonster()
{
	m_eTarget = EItemAniType_OnHit;
	int type = m_pItem->getID();
	bool bFlag = true;
	switch (type)
	{
	case EItem_NiuNaiN:
	case EItem_Maipian:
		m_pImage->setTouchEnabled(true);
		onItemHit();
		break;
		case EItem_YaShua:
		{
							 auto pZui = UIFactory::instance()->showZuiForm();
							 if (NULL != pZui)
							 {
								 BabyCare::instance()->getCurrScene()->addChild(pZui,10);
							 }
							 onItemRelease();
							 break;
		}
		case EItem_FangDaJing:
		{
								 auto pForm = UIFactory::instance()->showZoomForm();
								 if (NULL != pForm)
								 {
									 Director::getInstance()->getRunningScene()->addChild(pForm,10);
								 }
								 onItemRelease();
								 break;
		}
		default:
		onItemHit();

	}

	return true;
}

void ItemWidget::TouchBegin()
{
	if (EItem_YaGao == m_pItem->getID() && EntityMgr::instance()->pPlayer()->getItemUse(EItem_YaGao) == EItemUseType_Normal)
	{
		m_eTarget = EItemAniType_OnStop;
		NotificationCenter::getInstance()->postNotification(NOT_ITEM_TARGET_STOP);

		EntityMgr::instance()->pPlayer()->setItemUse(EItem_YaGao, EItemUseType_Complete);

		auto pForm = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));
		if (NULL != pForm)
		{
			auto pItem = pForm->getItemWidgetByIndex(EItem_YaShua);
			auto pos = pItem->getItemImage()->convertToWorldSpaceAR(Vec2::ZERO);// pForm->getItemWidgetByIndex(EItem_YaShua)->getInitialPos();
			auto pos1 = m_pImage->getParent()->convertToNodeSpaceAR(pos);
			pos1 = ccpAdd(pos1, m_pItem->getConfigPos());
			TurnPos(pos1);
		}

		for (MonsterWidgetsIter iter = m_oMonsterWidgets.begin(); iter != m_oMonsterWidgets.end(); iter++)
		{
			m_triggerMonster = *iter;
		}
		ItemShowAni();
		onItemHit();
		return;
	}

	m_vNewInitialPos = m_pImage->getParent()->convertToNodeSpace(m_pImage->getTouchBeganPosition());
	m_pImage->setPosition(m_vNewInitialPos);
	m_pTimelineNode->setPosition(m_vNewInitialPos);

	m_bShowImage = false;
	onItemTouch();
	m_eTarget = EItemAniType_OnTrigger;
}


void ItemWidget::TouchEnd()
{
	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemFood::ItemFood(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemFood::~ItemFood(){
}

bool ItemFood::init()
{
	if (ItemBase::init())
	{
		if (NULL != m_pActionTimeline)
		{
			int nAniID = m_pItem->getAniID(EItemAniType_OnHit);
			auto pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
			m_pActionTimeline->setAnimationEndCallFunc(pAni->getAniName(), CC_CALLBACK_0(ItemBase::AnimationMovementEventListener, this));
		}
		return true;
	}
	return false;
}

bool ItemFood::onTriggerMonster()
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto pForm = dynamic_cast<MakeForm*>(UIManager::instance()->findForm(IDC_Make));
	if (m_pItem->getID() == EItem_shaoziG)
	{
		int currID = m_triggerMonster->getMonster()->getMID();
		if (pPlayer->getCurrIsWaterExist() == true)
		{
			if (currID == EMonster_MianBao_G)
			{
				pForm->AddGuojangToMianBao();
			}
			return true;
		}
		if (pForm != NULL && currID == EMonster_GuoJingPing)
		{
			pForm->AddGuojangToFull(EWater_Guojiang);
		}
		onItemHit();
	}	
	return true;
}

void ItemFood::TouchEnd()
{
	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemReplace::ItemReplace(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemReplace::~ItemReplace(){
}

bool ItemReplace::init()
{
	if (ItemBase::init())
	{
		return true;
	}
	return false;
}

void ItemReplace::TouchBegin()
{
}

void ItemReplace::TouchMove()
{
}

void ItemReplace::TouchEnd()
{
}

void ItemReplace::RefreshItemAndMonsterImage(int iID, const char* skin, const char* attachment)
{
	Player* m_pPlayer = EntityMgr::instance()->pPlayer();
	
	auto pItem = m_pPlayer->getItemToolList()->getItemToolByID(iID);
	std::string image = pItem->getImage();
	auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
	pForm->ReplaceRoleSkeletonSkin(skin, attachment, image);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemCommonToy::ItemCommonToy(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemCommonToy::~ItemCommonToy(){
}

bool ItemCommonToy::init()
{
	if (ItemBase::init())
	{
		return true;
	}
	return false;
}

void ItemCommonToy::TouchBegin()
{
	m_bShowImage = false;
	onItemTouch();
	m_eTarget = EItemAniType_OnTrigger;
}

void ItemCommonToy::TouchMove()
{
	if (m_eTarget != EItemAniType_OnTouch && m_eTarget != EItemAniType_OnBegin)
	{
		Vec2 offset = ccpSub(m_pImage->getTouchBeganPosition(), m_vNewInitialPos);
		Vec2 pos = ccpSub(m_pImage->getTouchMovePosition(), offset);
		CheckItemMoveRange(pos);

		if (CheckTrigger())
		{
			m_pImage->setPosition(pos);
			if (NULL != m_pTimelineNode)
			{
				m_pTimelineNode->setPosition(pos);
			}
		}
	}
}

void ItemCommonToy::TouchEnd()
{
	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}

bool ItemCommonToy::onTriggerMonster()
{
	m_eTarget = EItemAniType_OnHit;
	onItemHit();
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemQiqiu::ItemQiqiu(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemQiqiu::~ItemQiqiu(){
}

bool ItemQiqiu::init()
{
	if (ItemBase::init())
	{
		return true;
	}
	return false;
}

void ItemQiqiu::TouchEnd()
{
	if (m_eTarget == EItemAniType_OnHit)
	{
		onItemRelease();
	}
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}

bool ItemQiqiu::onTriggerMonster()
{
	m_eTarget = EItemAniType_OnHit;
	NotificationCenter::getInstance()->postNotification(NOT_QITONG_DAQI);
	//onItemHit();
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemYuhua::ItemYuhua(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemYuhua::~ItemYuhua(){
}

bool ItemYuhua::init()
{
	if (ItemBase::init())
	{
		if (NULL != m_pActionTimeline)
		{
			int nAniID = m_pItem->getAniID(EItemAniType_OnHit);
			auto pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
			m_pActionTimeline->setAnimationEndCallFunc(pAni->getAniName(), CC_CALLBACK_0(ItemBase::AnimationMovementEventListener, this));
		}
		return true;
	}
	return false;
}

bool ItemYuhua::onTriggerMonster()
{
	m_eTarget = EItemAniType_OnHit;
	onItemHit();

	return true;
}

void ItemYuhua::TouchEnd()
{
	if (EItemUseType_Complete != EntityMgr::instance()->pPlayer()->getItemUse(m_pItem->getID()))
	{
		int iCount = 0;
		int iSum = m_oMonsterWidgets.size();
		for (MonsterWidgetsIter Iter = m_oMonsterWidgets.begin(); Iter != m_oMonsterWidgets.end(); ++Iter)
		{
			auto monster = *Iter;
			if (monster->m_iFinishTag == 1)
			{
				iCount++;
			}
		}

		auto fRate = (float)iCount / iSum;
		if (fRate >= 0.7)
		{
			EntityMgr::instance()->pPlayer()->setItemUse(m_pItem->getID(), EItemUseType_Complete);
			EntityMgr::instance()->pPlayer()->setItemUse(EItem_huasa, EItemUseType_Normal);
		}
	}

	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));

	m_eTarget = EItemAniType_OnTouch;
}
/////////////////////////////////////////////////////////////////////////////////////

ItemHuasa::ItemHuasa(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemHuasa::~ItemHuasa(){
}

bool ItemHuasa::init()
{
	if (ItemBase::init())
	{
		if (NULL != m_pActionTimeline)
		{
			int nAniID = m_pItem->getAniID(EItemAniType_OnHit);
			auto pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
			m_pActionTimeline->setAnimationEndCallFunc(pAni->getAniName(), CC_CALLBACK_0(ItemBase::AnimationMovementEventListener, this));
		}
		return true;
	}
	return false;
}

bool ItemHuasa::onTriggerMonster()
{
	m_eTarget = EItemAniType_OnHit;
	onItemHit();

	return true;
}

void ItemHuasa::TouchBegin()
{
	m_vNewInitialPos = m_pImage->getParent()->convertToNodeSpace(m_pImage->getTouchBeganPosition());
	m_pImage->setPosition(m_vNewInitialPos);
	m_pTimelineNode->setPosition(m_vNewInitialPos);

	m_bShowImage = false;
	onItemTouch();
	m_eTarget = EItemAniType_OnTrigger;
}

void ItemHuasa::TouchMove()
{
	if (m_eTarget != EItemAniType_OnTouch && m_eTarget != EItemAniType_OnBegin)
	{
		Vec2 offset = ccpSub(m_pImage->getTouchBeganPosition(), m_vNewInitialPos);
		Vec2 pos = ccpSub(m_pImage->getTouchMovePosition(), offset);
		CheckItemMoveRange(pos);

		if (CheckTrigger())
		{
			cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
			if (pos.y < winSize.height - m_pImage->getContentSize().height*0.5 - 200)
			{
				pos.y = winSize.height - m_pImage->getContentSize().height*0.5 - 200;
			}
			m_pImage->setPosition(pos);
			if (NULL != m_pTimelineNode)
			{
				m_pTimelineNode->setPosition(pos);
			}
		}
	}

}

void ItemHuasa::TouchEnd()
{
	if (EItemUseType_Complete != EntityMgr::instance()->pPlayer()->getItemUse(m_pItem->getID()))
	{
		int iCount = 0;
		int iSum = m_oMonsterWidgets.size();
		for (MonsterWidgetsIter Iter = m_oMonsterWidgets.begin(); Iter != m_oMonsterWidgets.end(); ++Iter)
		{
			auto monster = *Iter;
			if (monster->m_iFinishTag == 0)
			{
				iCount++;
			}
		}

		if (iCount == iSum)
		{
			EntityMgr::instance()->pPlayer()->setItemUse(m_pItem->getID(), EItemUseType_Complete);
			EntityMgr::instance()->pPlayer()->setItemUse(EItem_yuhua, EItemUseType_Normal);
		}
	}

	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemHuasa::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}

void ItemHuasa::AppearImageAction(bool isAppear)
{
	if (isAppear)
	{
		auto move1 = MoveBy::create(0.2f, ccp(0, -200));
		auto move2 = MoveBy::create(0.2f, ccp(0, 100));

		m_pImage->runAction(Sequence::create(move1, move2, NULL));
		m_vInitialPos = m_vInitialPos + ccp(0, -100);
	}
	else
	{
		auto move1 = MoveBy::create(0.2f, ccp(0, -100));
		auto move2 = MoveBy::create(0.2f, ccp(0, 200));

		m_pImage->runAction(Sequence::create(move1, move2, NULL));
		m_vInitialPos = m_vInitialPos + ccp(0, 100);
	}
}

void ItemHuasa::ItemShowImg()
{
	if (!m_bShowImage)
	{
		return;
	}
	m_pImage->setOpacity(255);
	if (NULL != m_pTimelineNode)
	{
		m_pTimelineNode->setVisible(false);
	}

	if (EItemUseType_Complete == EntityMgr::instance()->pPlayer()->getItemUse(m_pItem->getID()))
	{
		auto pForm = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));
		if (pForm != NULL)
		{
			pForm->closeToolBar();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ItemWanJu::ItemWanJu(EGameItemType type, ImageView* pImage)
:ItemBase(type, pImage)
{
}

ItemWanJu::~ItemWanJu(){
}

bool ItemWanJu::init()
{
	if (ItemBase::init())
	{
		return true;
	}
	return false;
}

void ItemWanJu::TouchBegin()
{
}

void ItemWanJu::TouchMove()
{
}

void ItemWanJu::TouchEnd()
{
}

void ItemWanJu::RefreshToolImage(EGameItemType iID)
{
	Player* m_pPlayer = EntityMgr::instance()->pPlayer();

	auto pItem = m_pPlayer->getItemToolList()->getItemToolByID(iID);
	std::string image = pItem->getImage();

}

