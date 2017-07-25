#include "ZuiForm.h"	
#include "Entity/EntityMgr.h"
#include "../UIFactory.h"
#include "GameType.h"
#include "BabyCare.h"
#include "Entity/MonsterFactory.h"


ZuiForm::ZuiForm() :
Form(IDC_Zui)
, m_eItemTarget(EGameItemTarget_Normal)
, m_pCurrItem(NULL)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ZuiForm::onItemTargerRelease), NOT_ITEM_TARGET_NORMAL, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ZuiForm::onItemTargerStop), NOT_ITEM_TARGET_STOP, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ZuiForm::onItemTargerTrigger), NOT_ITEM_TARGET_TRIGGER, NULL);
}

ZuiForm::~ZuiForm()
{
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_TARGET_NORMAL);
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_TARGET_STOP);
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_TARGET_TRIGGER);
}

bool ZuiForm::init()
{
	if (Form::init())
	{
		m_pLayout = static_cast<Widget*>(CSLoader::createNode("panel_zui.csb"));
		this->addChild(m_pLayout, 1);

		auto pBgImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		SupLayout::setRelativePos(pBgImg, pBgImg->getPosition(), SUP_ALIGNMENT_LB);
		pBgImg->setAnchorPoint(ccp(0.5f,0.5f));

		m_pPropLaout = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_prop"));
		m_pPropLaout->setPositionX(m_pPropLaout->getPositionX()*SUP_SCALE_X + (m_winSize.width - m_pPropLaout->getContentSize().width) / 2);

		auto pYashuaImg = dynamic_cast<ImageView*>(m_pPropLaout->getChildByName("Image_yashua"));
		SupLayout::setRelativePos(pYashuaImg, pYashuaImg->getPosition(), SUP_ALIGNMENT_LB);
		m_oItems[EItem_YaShua2] = ItemFactory::instance()->Create(EItem_YaShua2, pYashuaImg);
		pYashuaImg->setTag(EItem_YaShua2);
		pYashuaImg->addTouchEventListener(this, toucheventselector(ZuiForm::onItemTouchListener));
		this->addChild(m_oItems[EItem_YaShua2]);


		auto pFangDaJingImg = dynamic_cast<ImageView*>(m_pPropLaout->getChildByName("Image_fangdajing"));
		SupLayout::setRelativePos(pFangDaJingImg, pFangDaJingImg->getPosition(), SUP_ALIGNMENT_LB);
		pFangDaJingImg->addTouchEventListener(this, toucheventselector(ZuiForm::onItemTouchListener));
		pFangDaJingImg->setTag(EItem_FangDaJing);
		m_oItems[EItem_FangDaJing] = ItemFactory::instance()->Create(EItem_FangDaJing, pFangDaJingImg);
		this->addChild(m_oItems[EItem_FangDaJing]);

		auto pColseBtn = dynamic_cast<Button*>(pBgImg->getChildByName("Button_colse"));
		pColseBtn->addTouchEventListener(this, toucheventselector(ZuiForm::onColseButtonClicked));
		pColseBtn->setVisible(false);

		Vec2 pos = pBgImg->convertToNodeSpace(pBgImg->getPosition());
		MonsterList::MonsterType* pMonsterType1 = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EMonsterScene_Ya);
		if (NULL != pMonsterType1)
		{
			for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType1->begin(); pTypeIter != pMonsterType1->end(); pTypeIter++)
			{
				MonsterList::Monsters* pMonsters = pTypeIter->second;
				for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
				{
					auto pMonster = MonsterFactory::instance()->Create(*Iter);
					pBgImg->addChild(pMonster, 3);
					pMonster->setPosition((*Iter)->getMPos() + pos);
					auto vec = (*Iter)->getMItemType();
					for (int i = 0; i < vec.size(); i++)
					{
						m_oItems[vec[i]]->addMonsterWidget(pMonster);
					}
				}
			}
		}
		return true;
	}
	return false;
}

void ZuiForm::showFaDaJing()
{	
	m_pPropLaout->runAction(Sequence::create(DelayTime::create(1.0f), MoveBy::create(0.2f, Vec2(-m_winSize.width, 0.0f)), NULL));
}

void ZuiForm::removeYaZiMonster()
{
	auto pMonster = m_oItems[EItem_FangDaJing]->getTriggerMonster();
	m_oItems[EItem_FangDaJing]->removeHitMonster(pMonster);
}

void ZuiForm::AnimationMovementEventListener(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{

	}
}

void ZuiForm::onColseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		BabyCare::instance()->getCurrScene()->removeChild(this);
	}
}

void ZuiForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setOrder(-10);

		m_pCurrItem = m_oItems[item_type];
		m_pCurrItem->setOrder(10);


		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
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

void ZuiForm::onItemTargerRelease(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Normal;
}

void ZuiForm::onItemTargerStop(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Stop;
}

void ZuiForm::onItemTargerTrigger(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Trigger;
}