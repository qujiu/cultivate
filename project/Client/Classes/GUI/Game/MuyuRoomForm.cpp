#include "BabyRoomForm.h"
#include "Entity/EntityMgr.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "MuyuRoomForm.h"
#include "Entity/MonsterFactory.h"
#include "GameScene.h"
#include "GUI/Form/MenuControl.h"
#include "../Form/MenuControl.h"

#define pTool_Panel_Tag_Before   20000
#define pTool_Panel_Tag_Cur   20001      
#define  Koushui_Animation_ID 47


MuyuRoomForm::MuyuRoomForm() :
GameForm(IDC_MuyuRoom)
, m_bCurTouch(false)
, m_eItemTarget(EGameItemTarget_Normal)
, m_pCurrItem(NULL)
, m_pCurrToolPanel(NULL)
, m_isYuhua(false)
{
	int eItemType[] = {42,43,44,46};
	for (int i = 0; i < (sizeof(eItemType) / sizeof(eItemType[0])); i++)
	{
		vecItem.push_back(eItemType[i]);
	}
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MuyuRoomForm::onItemTargerStop), NOT_ITEM_TARGET_STOP, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MuyuRoomForm::onItemTargerRelease), NOT_ITEM_TARGET_NORMAL, NULL);


}

MuyuRoomForm::~MuyuRoomForm()
{
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_TARGET_STOP);
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_TARGET_NORMAL);

	//SoundManage::instance()->stopSound();
}

bool MuyuRoomForm::init()
{
	if (GameForm::init())
	{
		setKeyboardEnabled(false);
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
		auto m_pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = static_cast<Widget*>(CSLoader::createNode("MuyuRoom.csb"));
		this->addChild(m_pLayout);

		m_pToolBar = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_toolbar"));
		m_pToolBar->setPosition(ccp(winSize.width + m_pToolBar->getContentSize().width*0.5, m_pToolBar->getPositionY()));
		m_vecInitToolBar = m_pToolBar->getPosition();
		m_pToolBar->setZOrder(20);

		auto pCatspaw = dynamic_cast<ImageView*>(m_pToolBar->getChildByName("Image_catspaw"));
		m_pArrow = dynamic_cast<ImageView*>(pCatspaw->getChildByName("Image_arrow"));
		m_pArrow->setTouchEnabled(true);
		m_pArrow->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onArrowButtonClicked));
		m_vecArrowPos = m_pArrow->convertToWorldSpaceAR(Vec2::ZERO);

		auto pHuasaImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_huasa"));
		pHuasaImg->setPosition(ccp(pHuasaImg->getPositionX()*SUP_SCALE_X, pHuasaImg->getPositionY()*SUP_SCALE_Y));
		pHuasaImg->setVisible(true);
		m_pItems[EItem_huasa] = ItemFactory::instance()->Create(EItem_huasa, pHuasaImg);
		pHuasaImg->setTag(EItem_huasa);
		pHuasaImg->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onItemTouchListener));
		pHuasaImg->setTouchEnabled(true);
		this->addChild(m_pItems[EItem_huasa]);

		auto Panel_yugang = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_yugang"));
		ImageView* Img_yagang = dynamic_cast<ImageView*>(Panel_yugang->getChildByName("Img_yagang"));
		m_pItems[EItem_yashua] = ItemFactory::instance()->Create(EItem_yashua, Img_yagang);
		Img_yagang->setTag(EItem_yashua);
		Img_yagang->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onItemRefresh));
		Img_yagang->setTouchEnabled(true);
		this->addChild(m_pItems[EItem_yashua]);

		auto Img_maojin_gun = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_maojin_gun"));
		ImageView* Img_maojin = dynamic_cast<ImageView*>(Img_maojin_gun->getChildByName("Image_maojin"));
		m_pItems[EItem_maojin] = ItemFactory::instance()->Create(EItem_maojin, Img_maojin);
		Img_maojin->setTag(EItem_maojin);
		Img_maojin->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onItemRefresh));
		Img_maojin->setTouchEnabled(true);
		this->addChild(m_pItems[EItem_maojin]);


		m_pKoushuiImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_koushui"));
		m_pKoushuiImg->setZOrder(10);

		initToolBarAndTool();
		addMonstersToLayer();


		//auto pos = dynamic_cast<Layout*>(m_pLayout->getChildByName("pos"));
		//Form* pPlayerForm = NULL;
		//pPlayerForm = UIFactory::instance()->showPlayerForm();
		//m_PlayerLayer = (BabyControl*)pPlayerForm;
		//if (NULL != pPlayerForm)
		//{
		//	pos->addChild(pPlayerForm);
		//}

		return true;
	}
	return false;
}


void MuyuRoomForm::onArrowButtonClicked(Ref *sender, TouchEventType type)
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

void MuyuRoomForm::initToolBarAndTool()
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	std::string name = "Panel_yuhua";
	pPlayer->setstrItemyushi(name);
	auto pToolPanel = dynamic_cast<Layout*>(m_pToolBar->getChildByName(name));
	pToolPanel->setVisible(true);
	auto pItemImg = dynamic_cast<ImageView*>(pToolPanel->getChildByName("Image_1"));
	m_pItems[EItem_yuhua] = ItemFactory::instance()->Create((EGameItemType)EItem_yuhua, pItemImg);
	pItemImg->setTag(EItem_yuhua);
	pItemImg->setTouchEnabled(true);
	pItemImg->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onItemTouchListener));
	this->addChild(m_pItems[EItem_yuhua]);

}

void MuyuRoomForm::RefreshSubMenu(std::string desPanelName, const vector<int>& icon_res_ids)
{
	auto m_pPlayer = EntityMgr::instance()->pPlayer();
	std::string prePanelName = m_pPlayer->getstrItemyushi();

	auto preIconTemplete = dynamic_cast<Layout*>(m_pToolBar->getChildByName(prePanelName));
	auto pIconTemplete = dynamic_cast<Layout*>(m_pToolBar->getChildByName(desPanelName));

	if (!(strcmp(prePanelName.c_str(), desPanelName.c_str()) == 0))
	{
		preIconTemplete->setVisible(false);
		pIconTemplete->setVisible(true);
		m_pPlayer->setstrItemyushi(desPanelName);

		for (int i = 0; i < icon_res_ids.size(); i++)
		{
			auto pItem = m_pPlayer->getItemList()->getItemByID(vecItem[i]);
			if (pItem != NULL)
			{
				auto item_ui = dynamic_cast<ImageView*>(pIconTemplete->getChildByName(pItem->getImageName()));
				item_ui->setVisible(true);
				m_pItems[vecItem[i]] = ItemFactory::instance()->Create((EGameItemType)vecItem[i], item_ui);
				item_ui->addTouchEventListener(this, toucheventselector(MuyuRoomForm::onItemRefresh));
				item_ui->setTouchEnabled(true);
				item_ui->setTag(vecItem[i]);
				this->addChild(m_pItems[vecItem[i]]);
			}
		}

		MonsterList::MonsterType* pMonsterType = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EMonsterScene_shuaya);
		if (NULL != pMonsterType)
		{
			for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType->begin(); pTypeIter != pMonsterType->end(); pTypeIter++)
			{
				MonsterList::Monsters* pMonsters = pTypeIter->second;
				for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
				{
					auto pMonster = MonsterFactory::instance()->Create(*Iter);
					m_pLayout->addChild(pMonster, (*Iter)->getZorder());
					auto pos = (*Iter)->getMPos();
					pMonster->setPosition(ccp(pos.x*SUP_SCALE_X, pos.y*SUP_SCALE_Y));
					pMonster->setVisible(true);
					auto vec = (*Iter)->getMItemType();
					for (int i = 0; i < vec.size(); i++)
					{
						m_pItems[vec[i]]->addMonsterWidget(pMonster);
					}
				}
			}
		}
	}
}

void MuyuRoomForm::addMonstersToLayer()
{
	//读取配置表中怪物
	MonsterList::MonsterType* pMonsterType = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_Muyu);
	if (NULL != pMonsterType)
	{
		for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType->begin(); pTypeIter != pMonsterType->end(); pTypeIter++)
		{
			MonsterList::Monsters* pMonsters = pTypeIter->second;
			for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
			{
				auto pMonster = MonsterFactory::instance()->Create(*Iter);
				m_pLayout->addChild(pMonster, (*Iter)->getZorder());
				auto pos = (*Iter)->getMPos();
				pMonster->setPosition(ccp(pos.x*SUP_SCALE_X, pos.y*SUP_SCALE_Y));
				pMonster->setVisible(true);
				auto vec = (*Iter)->getMItemType();
				for (int i = 0; i < vec.size(); i++)
				{
					m_pItems[vec[i]]->addMonsterWidget(pMonster);
				}
			}
		}
	}
}

void MuyuRoomForm::onItemRefresh(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto isMulti = pPlayer->getItemList()->getItemByID(item_type)->getIsMultiple();
	auto strPanel = pPlayer->getItemList()->getItemByID(item_type)->getPanelName();

	if (EGameItemTarget_Normal == m_eItemTarget){
		if (NULL != m_pCurrItem)
			m_pCurrItem->setOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
			//runRoleExpression((ERoleExpression)pPlayer->getItemList()->getItemByID(item_type)->getRoleAniType());
			m_bCurTouch = true;
			if (isMulti == 1)
			{
				auto vecIcon = pPlayer->getToolList()->getToolByID(item_type)->getIconResID();
				RefreshSubMenu(strPanel, vecIcon);
			}
			m_pCurrItem->TouchBegin();
			break;
		case TOUCH_EVENT_MOVED:
			if (m_bCurTouch)
			{
				m_pCurrItem->TouchMove();
			}
			break;
		case TOUCH_EVENT_ENDED:
		case TOUCH_EVENT_CANCELED:
			//stopRoleExpression();
			m_bCurTouch = false;
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}


void MuyuRoomForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	auto pGameScene = (GameScene*)this->getParent();
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (EGameItemTarget_Normal == m_eItemTarget){
		if (NULL != m_pCurrItem)
			m_pCurrItem->setOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
			if (JudgeItemStatus(item_type))
			{
				m_bCurTouch = true;
				m_pCurrItem->TouchBegin();
			}
			break;
		case TOUCH_EVENT_MOVED:
			if (m_bCurTouch)
			{
				m_pCurrItem->TouchMove();
			}
			break;
		case TOUCH_EVENT_ENDED:
		case TOUCH_EVENT_CANCELED:
			m_bCurTouch = false;
			m_pCurrItem->TouchEnd();
			break;
		}
	}
	else if (EGameItemTarget_Trigger == m_eItemTarget)
	{
		if (m_pCurrItem->getItemType() != item_type)
			return;
		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TargetBegin();
			m_bCurTouch = true;
			break;
		case TOUCH_EVENT_MOVED:
			m_pCurrItem->TargetMove();
			break;
		case TOUCH_EVENT_ENDED:
		case TOUCH_EVENT_CANCELED:
			m_bCurTouch = false;
			m_pCurrItem->TargetEnd();
			break;
		}
	}
}

bool MuyuRoomForm::JudgeItemStatus(EGameItemType iType)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto eItem = pPlayer->getItemList()->getItemByID(iType);
	if (eItem->getIsLock() == 1)
	{
		if (pPlayer->GetSubMenuItemStatusByID(iType) == false)
		{
			auto *pForm = UIFactory::instance()->showBuyTipForm(eItem->getBuyGold(), iType);
			if (NULL != pForm)
			{
				Director::getInstance()->getRunningScene()->addChild(pForm, 10);
			}
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

void MuyuRoomForm::closeToolBar()
{
	if (m_isOpen)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_DAOJULAN);
		m_isOpen = false;
		auto moveto = MoveTo::create(0.5f, m_vecInitToolBar);
		m_pToolBar->runAction(Sequence::create(moveto, CallFunc::create([this](){
			m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_left.png");
			//m_pToolBar->setVisible(false);
		}), NULL));
	}
	else
	{
		m_pToolBar->setVisible(false);
	}
}

ItemBase* MuyuRoomForm::getItemWidgetByIndex(int index)
{
	if (index >= 0 && index < EItem_Max)
	{
		return m_pItems[index];
	}
	return NULL;
}

void MuyuRoomForm::onItemTargerStop(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Stop;
}

void MuyuRoomForm::onItemTargerRelease(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Normal;
}

void MuyuRoomForm::runTuKouShuiAction()
{
	m_eItemTarget = EGameItemTarget_Stop;
	//m_pMamControl->runRoleAnimation(EMam_Stand_TuShui);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ShuKou);
	this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(this, callfunc_selector(MuyuRoomForm::runKouShuiAction)), NULL));
}


void MuyuRoomForm::runKouShuiAction()
{
		auto aniName = EntityMgr::instance()->pPlayer()->getFilePath(Koushui_Animation_ID);
		m_pTimelineNode = CSLoader::createNode(aniName);
		m_pKoushuiTimeline = CSLoader::createTimeline(aniName);
		m_pTimelineNode->runAction(m_pKoushuiTimeline);
		m_pLayout->addChild(m_pTimelineNode, 10);
		m_pTimelineNode->setPosition(m_pKoushuiImg->getPosition());
		this->scheduleOnce(schedule_selector(MuyuRoomForm::onkoushuiScheduleFunc), 2.0f); 
		//m_pKoushuiTimeline->setFrameEventCallFunc(CC_CALLBACK_1(MuyuRoomForm::onFrameEvent, this));
}

void MuyuRoomForm::onkoushuiScheduleFunc(float dt)
{
	m_eItemTarget = EGameItemTarget_Normal;
	m_pTimelineNode->setVisible(false);
	m_pKoushuiImg->setVisible(true);
}

void MuyuRoomForm::onkoushuihit()
{
	auto spawn = Spawn::create(FadeTo::create(1.0f, m_pKoushuiImg->getOpacity() - 45), ScaleTo::create(1.0f, m_pKoushuiImg->getScale() - 0.2f), NULL);
	m_pKoushuiImg->runAction(spawn);
}


//void MuyuRoomForm::onFrameEvent(Frame* frame)
//{
//		//if (movementID.compare("Ani_biao") == 0)
//		//{
//		//	if (NULL != m_pCurrItem)
//		//	{
//		//		m_eItemTarget = EGameItemTarget_Normal;
//		//		hideTimeAni();
//		//	}
//		//}
//			m_eItemTarget = EGameItemTarget_Normal;
//			m_pTimelineNode->setVisible(false);
//			m_pKoushuiImg->setVisible(true);
//}

