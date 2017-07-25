#include "MonsterBase.h"
#include "ItemWidget.h"
#include "Entity/EntityMgr.h"
#include "GUI/UIManager.h"
#include "GUI/UIFactory.h"
#include "BabyCare.h"

#define _MONSTER_ACTION_TAG_		10000

MonsterBase::MonsterBase(Monster* pMonster)
:m_pMonster(pMonster)
, m_pImage(NULL)
, m_pItemWidget(NULL)
, m_nDoneNum(m_pMonster->getDoneNum())
, m_bTurn(false)
, m_pParticle(NULL)
, m_pArmature(NULL)
, m_bTouchFlag(true)
, m_bRemove(false)
, m_pTip(NULL)
, m_iFinishTag(0)
, m_bVisual(false)
{

}

MonsterBase::~MonsterBase()
{
	m_pImage = NULL;
}

bool MonsterBase::init()
{
	if (BaseControl::init())
	{
		if (m_pMonster->getMPicture().compare("null") != 0)
		{
			m_pImage = ImageView::create(m_pMonster->getMPicture(), TextureResType::LOCAL);
			this->addChild(m_pImage);
			m_pImage->setVisible(m_pMonster->getMVisible());
			m_pImage->setRotation((float)m_pMonster->getMRotation());
		}
		if (m_pMonster->getMParticle() != 0)
		{
			m_pParticle = ParticleSystemQuad::create("res/effect/effect_yindao.plist");
			this->addChild(m_pParticle, 10);
			m_pParticle->setVisible(false);
			m_pParticle->setPosition(ccp(0.0f, 0.0f));
		}

	

		setContentSize(m_pImage->getContentSize());
		setAnchorPoint(ccp(0.0f, 0.0f));
		return true;
	}
	return false;
}


void MonsterBase::onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn)
{
	if (NULL == m_pImage)
		return;
	
	m_pItemWidget = pItemWidget;
	m_bTurn == bTurn;

	auto call_func = CallFunc::create(this, callfunc_selector(MonsterBase::onHitComplete));
	if (NULL != m_pItemWidget)
	{
		switch (eID)
		{
		case EGameItemProcessId_Null:
			m_pImage->runAction(CallFunc::create(this, callfunc_selector(MonsterBase::onHitComplete)));
			break;
		case EGameItemProcessId_Normal:
			if (--m_nDoneNum >= 0)
			{
				m_pImage->runAction(call_func);
			}
			break;
		case EGameItemProcessId_Shrink:
		{
										  auto action = m_pImage->getActionByTag(_MONSTER_ACTION_TAG_);
										  if ((m_nDoneNum != 0 && (action && action->isDone())) || !action)
										  {
											  if (--m_nDoneNum >= 0)
											  {
												  float scaleTo = (float)m_nDoneNum / (float)m_pMonster->getDoneNum();
												  auto scale = ScaleTo::create(.5f, scaleTo);
												  auto action_ret = Sequence::createWithTwoActions(scale, call_func);
												  action_ret->setTag(_MONSTER_ACTION_TAG_);
												  m_pImage->runAction(action_ret);
											  }
										  }
										  break;
		}
			
		case EGameItemProcessId_FadeOut:
		{
										   auto action = m_pImage->getActionByTag(_MONSTER_ACTION_TAG_);
										   if ((m_nDoneNum != 0 && (action && action->isDone())) || !action)
										   {
											   if (--m_nDoneNum >= 0)
											   {
												   auto move = EaseExponentialIn::create(MoveBy::create(.5f, Vec2(0, -150.0f)));
												   auto action_ret = Sequence::createWithTwoActions(move, call_func);
												   action_ret->setTag(_MONSTER_ACTION_TAG_);
												   m_pImage->runAction(action_ret);
											   }
										   }
										   break;
		}
		
		case EGameItemProcessId_TakeAway:
			break;
		case EGameItemProcessId_FallOff:
			break;
		case EGameItemProcessId_Max:
			break;
		default:
			break;
		}
	}
}

void MonsterBase::onHitComplete()
{
	if (m_nDoneNum <= 0)
	{
		m_pImage->setVisible(false);
		this->runAction(Sequence::create(CallFunc::create([this]{
			if (NULL != m_pItemWidget)
			{
				m_pItemWidget->removeHitMonster(this);
			}
		}
		), NULL));
		if (m_bTurn && NULL != m_pItemWidget)
		{
			m_pItemWidget->TargetEnd();
		}

	}
}

void MonsterBase::onComplete()
{
	m_pImage->setVisible(false);
	this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([this]{
		EntityMgr::instance()->pPlayer()->setItemUse(m_pItemWidget->getItem()->getID(), EItemUseType_Complete);
	}), NULL));

	m_pItemWidget->TouchEnd();
}

void MonsterBase::runTwinkle(bool bFlag)
{
	if (bFlag)
	{
		m_pImage->setVisible(true);
		auto fadeOut = FadeOut::create(1.0f);
		auto fadeIn = FadeIn::create(1.0f);
		m_pImage->runAction(RepeatForever::create(Sequence::create(fadeOut, fadeIn, NULL)));
	}
	else
	{
		m_pImage->stopAllActions();
		m_pImage->setVisible(false);
	}
}

void MonsterBase::runParticle(bool bFlag)
{
	if (NULL != m_pParticle)
	{
		m_pParticle->setVisible(bFlag);
	}
}

void MonsterBase::removeParticle()
{
	if (NULL != m_pParticle)
	{
		m_pParticle->removeFromParentAndCleanup(true);
		m_pParticle = NULL;
	}

}

void MonsterBase::runAnimation(bool bFlag)
{
	if (bFlag)
	{
		m_pArmature->setVisible(true);
		Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(m_pMonster->getMAniID());
		if (NULL != pAni)
		{
			if (!m_pArmature->getAnimation()->isPlaying())
			{
				m_pArmature->getAnimation()->play(pAni->getAniName());
			}
		}
	}
	else
	{
		m_pArmature->setVisible(false);
		m_pArmature->getAnimation()->stop();
	}
}

bool MonsterBase::DrawBoard(const Vec2& pos)
{
	return false;
}

void MonsterBase::SetBrushOrEraser(bool flag)
{
}

void MonsterBase::ChangeGraphicsBoard(int native_res_id, bool brush_or_eraser)
{
}

void MonsterBase::ChangeMonsterImage(int native_res_id)
{
}

bool MonsterBase::getMonsterVisual()
{
	return m_bVisual;
}

void MonsterBase::initMonsterStatus()
{
}

bool MonsterBase::getCurrMonsterGraphicsNotZeroPixel()
{
	return false;
}

void MonsterBase::RefreshMonster(bool bVisual)
{
}

void MonsterBase::Removes()
{

}