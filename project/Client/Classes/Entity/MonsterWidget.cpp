#include "MonsterWidget.h"
#include "GUI/UIManager.h"
#include "GUI//Game/MuyuRoomForm.h"


#define _MONSTER_ACTION_TAG_		10000

/////////////////////////////////MonsterGeneral////////////////////////////////////////////////////////////////////////////////////////
MonsterGeneral::MonsterGeneral(Monster* pMonster)
:MonsterBase(pMonster)
{

}

MonsterGeneral::~MonsterGeneral(){
}


bool MonsterGeneral::init()
{
	if (MonsterBase::init())
	{
	/*	if (m_pMonster->getMAniID() != 0)
		{
			Player* pPlayer = EntityMgr::instance()->pPlayer();;
			Ani* pAni = pPlayer->getAniList->getAniByID(m_pMonster->getMAniID());

			m_pTimelineNode = CSLoader::createNode(pPlayer->getFilePath(m_pMonster->getMAniID()));
			m_pActionTimeline = CSLoader::createTimeline(pPlayer->getFilePath(m_pMonster->getMAniID()));
			m_pTimelineNode->runAction(m_pActionTimeline);
			m_pTimelineNode->setVisible(false);

			m_pActionTimeline->setAnimationEndCallFunc(pAni->getAniName(), CC_CALLBACK_0(MonsterGeneral::AnimationMovementEventListener, this));

		}*/
		return true;
	}
	return false;
}

void MonsterGeneral::AnimationMovementEventListener()
{/*
	if (movementType == COMPLETE)
	{
	if (movementID.find("Ani_monster") == 0)
	{
	onHitComplete();
	}
	}*/
}

void MonsterGeneral::onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn)
{
	if (NULL == m_pImage)
		return;
	m_pItemWidget = pItemWidget;
	m_bTurn = bTurn;
	auto call_func = CallFunc::create(this, callfunc_selector(MonsterGeneral::onHitComplete));
	if (NULL != m_pItemWidget)
	{
		switch (m_pItemWidget->getItem()->getID())
		{
		case EItem_YaGao:
		{
							if (--m_nDoneNum >= 0)
							{
								auto pForm = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));;
								auto pItem = pForm->getItemWidgetByIndex(EItem_YaShua);
								pItem->addYagaoImg();
								m_pImage->runAction(call_func);
							}
							break;
		}
		case EItem_YaShua2:
		{
							  if (--m_nDoneNum >= 0)
							  {
								  float opacity = (float)m_nDoneNum / (float)m_pMonster->getDoneNum();
								  auto fade_to = FadeTo::create(.5f, opacity * 255);
								  auto action_ret = Sequence::create(fade_to, call_func, NULL);
								  action_ret->setTag(_MONSTER_ACTION_TAG_);
								  m_pImage->runAction(action_ret);

								  auto particle = ParticleSystemQuad::create("res/effect/effect_shuaya_pomo.plist");
								  particle->setPosition(0, m_nDoneNum);
								  this->addChild(particle);
							  }
							  break;
		}
		case EItem_maojin:
		{
							   if (--m_nDoneNum >= 0)
							   {
								   auto pForm = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));;
								   pForm->onkoushuihit();
							   }
							   else
							   {
								   m_pImage->runAction(call_func);
							   }
							   break;
		}
		default:
			if (--m_nDoneNum >= 0)
			{
				m_pImage->runAction(call_func);
			}
			break;
		}
	}
	else
	{
		switch (eID)
		{
		case EGameItemProcessId_XiJun:
		{
										 auto action = m_pImage->getActionByTag(_MONSTER_ACTION_TAG_);
										 if ((m_nDoneNum != 0 && (action && action->isDone())) || !action)
										 {
											 if (--m_nDoneNum >= 0)
											 {
												 float opacity = (float)m_nDoneNum / (float)m_pMonster->getDoneNum();
												 auto fade_to = FadeTo::create(.5f, opacity * 255);
												 auto action_ret = Sequence::create(fade_to, call_func, NULL);
												 action_ret->setTag(_MONSTER_ACTION_TAG_);
												 //m_pArmature->runAction(action_ret);

											 }
										 }
										 break;
		}
		default:
			break;
		}
	}
}


void MonsterGeneral::onHitComplete()
{
	if (m_nDoneNum <= 0)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ITEM_Complete);
		
		m_pImage->setVisible(false);
		scheduleOnce(schedule_selector(MonsterGeneral::onHitCompleteCallback), 0.5f);

		//if (/*m_bTurn && */NULL != m_pItemWidget)
		//{
		//	m_pItemWidget->TargetEnd();
		//}
	}

}

void MonsterGeneral::onHitCompleteCallback(float delta)
{
	if (NULL != m_pItemWidget)
	{
		m_pItemWidget->removeHitMonster(this);
	}
}

////////////////////////////////MonsterGeneral end/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////MonsterPaomo////////////////////////////////////////////////////////////////////////////////////////
MonsterPaomo::MonsterPaomo(Monster* pMonster)
:MonsterBase(pMonster)
{

}

MonsterPaomo::~MonsterPaomo(){
}


bool MonsterPaomo::init()
{
	if (MonsterBase::init())
	{
		return true;
	}
	return false;
}

void MonsterPaomo::initMonsterStatus()
{
	if (!m_bVisual) return;
	m_bVisual = false;
	auto action = m_pImage->getActionByTag(_MONSTER_ACTION_TAG_);
	if ((action && action->isDone()) || !action)
	{
		auto fade = FadeOut::create(.5f);
		auto move = MoveBy::create(.5f, Vec2(0, -50.0f));
		auto spawn = Spawn::create(fade, move, NULL);
		auto action_ret = Sequence::create(spawn, CallFunc::create(this, callfunc_selector(MonsterPaomo::RefreshMonster)), NULL);
		action_ret->setTag(_MONSTER_ACTION_TAG_);
		m_pImage->runAction(action_ret);
	}
}

void MonsterPaomo::onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn)
{
	if (NULL == m_pImage)
		return;
	m_pItemWidget = pItemWidget;
	m_bTurn = bTurn;

	if (NULL != m_pItemWidget)
	{
		switch (eID)
		{
		case EGameItemProcessId_PaoMo:
		{
										 if (m_bVisual) return;
										 m_bVisual = true;
										 m_pImage->setVisible(true);
										 m_pImage->setScale(0);
										 auto scale1 = ScaleTo::create(0.5f, 1.2);
										 auto scale2 = ScaleTo::create(0.5f, 1.0);
										 auto seq = Sequence::create(scale1, scale2, NULL);

										 m_pImage->runAction(seq);
										 m_iFinishTag = 1;
										 break;
		}
		case EGameItemProcessId_PaoMoXiaoshi:
		{
												if (!m_bVisual) return;
												m_bVisual = false;
												auto action = m_pImage->getActionByTag(_MONSTER_ACTION_TAG_);
												if ((action && action->isDone()) || !action)
												{
													auto fade = FadeOut::create(.5f);
													auto move = MoveBy::create(.5f, Vec2(0, -50.0f));
													auto spawn = Spawn::create(fade, move, NULL);
													auto action_ret = Sequence::create(spawn, CallFunc::create(this, callfunc_selector(MonsterPaomo::RefreshMonster)), NULL);
													action_ret->setTag(_MONSTER_ACTION_TAG_);
													m_pImage->runAction(action_ret);
												}
												m_iFinishTag = 0;
												break;
		}
		default:
			break;
		}
	}
}

void MonsterPaomo::RefreshMonster()
{
	m_pImage->setPosition(Vec2::ZERO);
	m_pImage->setVisible(false);
	m_pImage->setOpacity(255);
}

////////////////////////////////MonsterPaomo end/////////////////////////////////////////////////////////////////////////////////////////////