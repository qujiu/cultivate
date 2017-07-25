#include "BabyRoomForm.h"
#include "Entity/EntityMgr.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "ToyRoomForm.h"
#include "../Form/MenuControl.h"
#include "Entity/MonsterFactory.h"
#include "chipmunk.h"



ToyRoomForm::ToyRoomForm() :
GameForm(IDC_MuyuRoom)
{
	int eItemType[] = { 10,11,12 };
	for (int i = 0; i < (sizeof(eItemType) / sizeof(eItemType[0])); i++)
	{
		m_pcurrItem.push_back(eItemType[i]);
	}
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ToyRoomForm::setInitialDaqi), NOT_QITONG_DAQI, NULL);
}

ToyRoomForm::~ToyRoomForm()
{
	//SoundManage::instance()->stopSound();
	NotificationCenter::getInstance()->removeObserver(this, NOT_QITONG_DAQI);

}

bool ToyRoomForm::init()
{
	if (GameForm::init())
	{
		setKeyboardEnabled(false);
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		m_pLayout = static_cast<Widget*>(CSLoader::createNode("ToyRoom.csb"));
		this->addChild(m_pLayout);

		Img_bear = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_bear"));
		m_pItems[EItem_xiaobear] = ItemFactory::instance()->Create(EItem_xiaobear, Img_bear);
		Img_bear->setTag((EGameItemType)EItem_xiaobear);
		Img_bear->addTouchEventListener(this, toucheventselector(ToyRoomForm::onItemBearTouchListener));
		Img_bear->setTouchEnabled(true);
		this->addChild(m_pItems[EItem_xiaobear]);

		Img_muma = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_muma"));
		m_pItems[EItem_muma] = ItemFactory::instance()->Create(EItem_muma, Img_muma);
		Img_muma->setTag((EGameItemType)EItem_muma);
		Img_muma->setTouchEnabled(true);
		Img_muma->addTouchEventListener(this, toucheventselector(ToyRoomForm::onItemMuMaTouchListener));
		this->addChild(m_pItems[EItem_muma]);

		Img_tantanqiu = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_tantanqiu"));
		m_pItems[EItem_tantanqiu] = ItemFactory::instance()->Create(EItem_tantanqiu, Img_tantanqiu);
		Img_tantanqiu->setTag((EGameItemType)EItem_tantanqiu);
		Img_tantanqiu->addTouchEventListener(this, toucheventselector(ToyRoomForm::onItemTanQiuTouchListener));
		Img_tantanqiu->setTouchEnabled(true);
		this->addChild(m_pItems[EItem_tantanqiu]);

		Layout* panel_qiu = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_qiqiu"));
		Img_daqi = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_daqi"));
		m_pItems[EItem_qitong] = ItemFactory::instance()->Create(EItem_qitong, Img_daqi);
		Img_daqi->setTag((EGameItemType)EItem_qitong);
		Img_daqi->setTouchEnabled(true);
		Img_daqi->addTouchEventListener(this, toucheventselector(ToyRoomForm::onItemQiTongTouchListener));

		this->addChild(m_pItems[EItem_qitong]);

		for (int i = 0; i < 3; i++)
		{
			auto pImg = dynamic_cast<ImageView*>(panel_qiu->getChildByName("Image_" + sup::SupString::int2String(i + 1)));
			pImg->setPosition(ccp(pImg->getPositionX()*SUP_SCALE_X, pImg->getPositionY()*SUP_SCALE_Y));
			pImg->setTag((EGameItemType)m_pcurrItem[i]);
			m_pItems[m_pcurrItem[i]] = ItemFactory::instance()->Create((EGameItemType)m_pcurrItem[i], pImg);
			pImg->setTouchEnabled(true);
			pImg->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
			this->addChild(m_pItems[m_pcurrItem[i]]);
		}

		Panel_Loadingbar = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_loadingbar"));
		Panel_Loadingbar->setPosition(ccp(Panel_Loadingbar->getPositionX()*SUP_SCALE_X, Panel_Loadingbar->getPositionY()*SUP_SCALE_Y));
		m_LoadingBar = dynamic_cast<LoadingBar*>(Panel_Loadingbar->getChildByName("LoadingBar"));
		Panel_Loadingbar->setVisible(false);


		addMonstersToLayer();

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

void ToyRoomForm::addMonstersToLayer()
{
	MonsterList::MonsterType* pMonsterType = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_Toy);
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

void ToyRoomForm::onItemQiTongTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
			break;
		case TOUCH_EVENT_MOVED:
		case TOUCH_EVENT_ENDED:
			m_pCurrItem->onTriggerMonster();
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}

void ToyRoomForm::onItemBearTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
			break;
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}

void ToyRoomForm::onItemTanQiuTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
			break;
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}

void ToyRoomForm::onItemMuMaTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(-10);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
			break;
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}
}



void ToyRoomForm::setInitialDaqi(Ref* obj)
{
	Panel_Loadingbar->setVisible(true);
	m_LoadingBar->setPercent(0);

}

