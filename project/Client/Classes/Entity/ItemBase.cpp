#include "ItemBase.h"
#include "Entity/EntityMgr.h"
#include "GUI/UIManager.h"
#include "GUI/UIFactory.h"
#include "SaveManager/SaveManage.h"
#include "GUI/Game/MuyuRoomForm.h"
#include "GUI/Game/ZuiForm.h"
#include "GUI/Form/BabyControl.h"
#include "GUI/Game/MakeForm.h"

ItemBase::ItemBase(EGameItemType type, ImageView* pImage)
: m_eType(type)
, m_pTimelineNode(NULL)
, m_pActionTimeline(NULL)
, m_pImage(pImage)
, m_pItem(NULL)
, m_eTarget(EItemAniType_OnTouch)
, m_triggerMonster(NULL)
, m_pLock(NULL)
, m_bLock(true)
, m_bOpen(true)
, m_bShowImage(false)
, m_pTempExImg(NULL)
, m_isEffectPlaying(false)
{
	m_oMonsterWidgets.clear();
}

ItemBase::~ItemBase()
{
}

bool ItemBase::init()
{
	if (BaseControl::init())
	{

		drawNode = DrawNode::create();
		this->addChild(drawNode, 100);

		drawNode2 = DrawNode::create();
		this->addChild(drawNode2, 100);

		Player* pPlayer = EntityMgr::instance()->pPlayer();
		m_pItem = pPlayer->getItemList()->getItemByID(m_eType);
		setInitialPos(m_pImage->getPosition());
		setItemLock(m_pItem->getIsLock());
		setItemOpen();

		m_pStar = ImageView::create("ui/common/Ani_suihao.png",TextureResType::LOCAL);
		m_pImage->addChild(m_pStar, 3);
		m_pStar->setPosition(ccp(m_pImage->getContentSize().width*0.9f, m_pImage->getContentSize().height*0.5f - 50.0f));
		m_pStar->setVisible(false);

		if (m_pItem->getID() == EItem_yashua || m_pItem->getID() == EItem_muyuye)
		{
			m_pTempExImg = (ImageView*)m_pImage->clone();
			m_pTempExImg->setPosition(m_pImage->getPosition());
			m_pImage->getParent()->addChild(m_pTempExImg);
			m_pTempExImg->setVisible(false);
		}

		int nAniSize = m_pItem->getAnisID().size();
		if (nAniSize > 1)
		{
			m_pTimelineNode = CSLoader::createNode(pPlayer->getFilePath(m_pItem->getAniID(EItemAniType_OnHit)));
			m_pActionTimeline = CSLoader::createTimeline(pPlayer->getFilePath(m_pItem->getAniID(EItemAniType_OnHit)));
			m_pTimelineNode->runAction(m_pActionTimeline);
			m_pImage->getParent()->addChild(m_pTimelineNode);
			m_pTimelineNode->setPosition(m_vInitialPos);
			m_pTimelineNode->setVisible(false);

			auto pParticle = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_1"));
			if (pParticle != NULL)
			{
				pParticle->setPositionType(ParticleSystem::PositionType::FREE);
			}
		}
		return true;
	}
	return false;
}

void ItemBase::setItemLock(bool bLock)
{
	m_bLock = bLock;
	if (bLock)
	{
		m_pImage->setColor(Color3B(70, 70, 70));
	}
	else
	{
		if (m_pImage->getColor() == Color3B::WHITE)
		{
			return;
		}
		m_pImage->setColor(Color3B::WHITE);
		ParticleSystemQuad* particle = ParticleSystemQuad::create("effect/effect_jiesuo.plist");
		m_pImage->getParent()->addChild(particle);
		particle->setPosition(m_pImage->getParent()->convertToNodeSpace(m_pImage->getPosition()));
		m_pImage->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.4f, 1.1f), ScaleTo::create(0.4f, 0.9f), DelayTime::create(0.0f), NULL)));
	}
}

void ItemBase::setItemOpen()
{
	if (-1 == m_pItem->getBuyID())
	{
		return;
	}
	bool bFlag = SaveManage::instance()->getBoolSave(SAVE_ID(m_pItem->getBuyID()));
	m_bOpen = bFlag;

	if (!bFlag && NULL == m_pLock)
	{
		m_pLock = ImageView::create("ui/role/ani_xuanze_renwu_ui_suozi.png", Widget::TextureResType::LOCAL);
		m_pImage->addChild(m_pLock, 100);
		m_pLock->setPosition(m_pImage->getContentSize()*0.5f);
	}
	else if (bFlag)
	{
		if (NULL != m_pLock)
		{
			m_pLock->removeFromParentAndCleanup(true);
			m_pLock = NULL;
		}
	}
}

void ItemBase::removeHitMonster(MonsterBase* pMonster)
{
	if (NULL != pMonster)
	{
		if (EItemUseType_Normal == EntityMgr::instance()->pPlayer()->getItemUse(m_pItem->getID()))
		{
			EntityMgr::instance()->pPlayer()->setItemUse(m_pItem->getID(), EItemUseType_Useing);
		}
		auto pMonsterList = EntityMgr::instance()->pPlayer()->getMonsterList();
		pMonsterList->removeMonster(pMonster->getMonster());
		pMonster->removeFromParentAndCleanup(true);
		m_oMonsterWidgets.remove(pMonster);
		pMonster = NULL;
		m_triggerMonster = NULL;
		if (m_oMonsterWidgets.empty())
		{
			EntityMgr::instance()->pPlayer()->setItemUse(m_pItem->getID(), EItemUseType_Complete);
			setUserComplete();
			if (m_pItem->getID() == EItem_YaShua2)
			{
				auto pForm = dynamic_cast<ZuiForm*>(UIManager::instance()->findForm(IDC_Zui));
				if (NULL != pForm)
				{
					TouchEnd();
					pForm->showFaDaJing();
				}
			}
			else if (m_pItem->getID() == EItem_Yabei)
			{
				auto pForm = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));
				if (NULL != pForm)
				{
					pForm->runTuKouShuiAction();
				}
			}
			else
			{
				TouchEnd();
			}
			int type = m_pItem->getRoleAniType();
			if (type == -1)
				return;
			else if (type < 100)
			{
				//EntityMgr::instance()->pPlayer()->getpMamControl()->runRoleAnimation((EMamExpression)type);
			}
			else
			{
				type -= 100;
				//EntityMgr::instance()->pPlayer()->getpBabyControl()->runRoleAnimation((EBabyExpression)type);
			}
		}
	}
}

void ItemBase::setOrder(int nOrder)
{
	this->setZOrder(this->getZOrder() + nOrder);
}

void ItemBase::addMonsterWidget(MonsterBase* pMonsterWidget)
{
	m_oMonsterWidgets.push_back(pMonsterWidget);
}

void ItemBase::TurnPos(const Vec2& pos, CallFunc* done)
{
	auto move = MoveTo::create(.5f, pos);
	m_pImage->stopAllActions();

	if (done)
	{
		m_pImage->runAction(Sequence::createWithTwoActions(EaseExponentialOut::create(move), done));
	}
	else
	{
		m_pImage->runAction(EaseExponentialOut::create(move));
	}

	if (m_pTimelineNode)
	{
		auto move1 = MoveTo::create(.5f, pos);
		m_pTimelineNode->runAction(EaseExponentialOut::create(move1));
	}
}

void ItemBase::AnimationMovementEventListener()
{
	if (m_eTarget == EItemAniType_OnHit)
	{
		if (NULL != m_triggerMonster)
		{
			m_triggerMonster->onHitStart(this, m_pItem->getProcessID());
		}
		m_eTarget = EItemAniType_OnRelease;
	}
	else if (m_eTarget == EItemAniType_OnStop)
	{
		m_eTarget = EItemAniType_OnTouch;

		if (NULL != m_triggerMonster)
		{
			m_triggerMonster->onHitStart(this, m_pItem->getProcessID(), true);
		}
		NotificationCenter::getInstance()->postNotification(NOT_ITEM_TARGET_NORMAL);

	}
}

void ItemBase::onFrameEventListener(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex)
{

}

void ItemBase::onItemTouch()
{
	int nAniID = m_pItem->getAniID(EItemAniType_OnTouch);
	if (nAniID != _ANI_ID_NULL_ && m_pActionTimeline != NULL)
	{
		Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
		if (NULL != pAni)
		{
			ItemShowAni();
			m_pActionTimeline->play(pAni->getAniName(), false);
		}
	}
	//playItemSound(EItemSoundType_OnTouch);
}

void ItemBase::onItemTrigger()
{
	int nAniID = m_pItem->getAniID(EItemAniType_OnTrigger);
	if (nAniID != _ANI_ID_NULL_ && m_pActionTimeline != NULL)
	{
		Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
		if (NULL != pAni)
		{
			if (!m_pActionTimeline->isPlaying())
			{
				m_pActionTimeline->play(pAni->getAniName(), false);
				playItemSound(EItemSoundType_OnTrigger);
			}
		}
	}
	else
	{
		ItemShowImg();
	}
}

void ItemBase::onItemHit()
{
	int nAniID = m_pItem->getAniID(EItemAniType_OnHit);
	if (nAniID != _ANI_ID_NULL_ && m_pActionTimeline != NULL)
	{
		Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
		if (NULL != pAni)
		{
			if (!m_pActionTimeline->isPlaying())
			{
				m_pActionTimeline->play(pAni->getAniName(), false);
			}
		}
	}
	else
	{
		ItemShowImg();
	}
}

void ItemBase::onItemRelease()
{
	int nAniID = m_pItem->getAniID(EItemAniType_OnRelease);
	if (nAniID != _ANI_ID_NULL_ && m_pActionTimeline != NULL)
	{
		Ani* pAni = EntityMgr::instance()->pPlayer()->getAniList()->getAniByID(nAniID);
		if (NULL != pAni)
		{
			m_pActionTimeline->play(pAni->getAniName(), false);
		}
	}
	//stopItemSound();
}

void ItemBase::playItemSound(EItemSoundType type)
{
	int bLoop = 0;
	auto sound_id = m_pItem->getSoundID(type, bLoop);

	if (sound_id != RES_SOUND_ID_NONE)
	{
		SoundManage::instance()->playSound((RES_SOUND_ID)sound_id, bLoop);//, true, true);
	}
}

void ItemBase::stopItemSound()
{
	for (int i = EItemAniType_OnTouch; i < EItemAniType_OnRelease; i++)
	{
		int bLoop = false;
		auto sound_id = m_pItem->getSoundID((EItemSoundType)i, bLoop);

		if (bLoop)
		{
			SoundManage::instance()->stopSound((RES_SOUND_ID)sound_id);
		}
	}
}


void ItemBase::TargetBegin()
{
	m_eTarget = EItemAniType_OnStop;
	onItemHit();
}

void ItemBase::TargetMove()
{

}

void ItemBase::TargetEnd()
{
	if (m_eTarget == EItemAniType_OnTouch || m_eTarget == EItemAniType_OnRelease)
	{
		m_bShowImage = true;
		onItemRelease();
		TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	}
}

void ItemBase::TouchBegin()
{
	m_vNewInitialPos = m_pImage->getParent()->convertToNodeSpace(m_pImage->getTouchBeganPosition());
	m_pImage->setPosition(m_vNewInitialPos);
	m_pTimelineNode->setPosition(m_vNewInitialPos);

	m_bShowImage = false;
	onItemTouch();
	m_eTarget = EItemAniType_OnTrigger;
}

void ItemBase::TouchMove()
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

void ItemBase::TouchEnd()
{
	onItemRelease();
	m_bShowImage = true;
	TurnPos(m_vInitialPos, CallFunc::create(this, callfunc_selector(ItemBase::ItemShowImg)));
	m_eTarget = EItemAniType_OnTouch;
}

void ItemBase::RefreshToolImage(int iID)
{
	Player* player = EntityMgr::instance()->pPlayer();
	auto native_static_res = EntityMgr::instance()->pPlayer()->getItemToolList()->getItemToolByID(iID);
	auto strItemImg = native_static_res->getImage();
	if (strItemImg.compare("NA") != 0)
	{
		if (m_eType == EItem_zhiniaoku)
		{
			player->setstrZhiniaoku(strItemImg);
			auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
			if (pForm != NULL)
			{
				pForm->ReplaceZhiNiaoKu(strItemImg.c_str());
				NotificationCenter::getInstance()->postNotification(NOT_ITEM_ZHINIAOKU_PISS);
			}
			return;
		}
		m_pImage->loadTexture(strItemImg.c_str());
	}
}

void ItemBase::RefreshItemAndMonsterImage(int iID, const char* str1,  const char* str2)
{

}

void ItemBase::initMonsterImage(bool before)
{

}


void ItemBase::CheckItemMoveRange(Vec2& pos)
{

	cocos2d::Rect rect = m_pItem->getMoveRect();
	if (rect.size.width <= 0)
		return;

	rect.size.width = rect.size.width*m_pImage->getScaleX();
	rect.size.height = rect.size.height*m_pImage->getScaleY();

	Vec2 posTemp = m_pImage->getParent()->convertToWorldSpace(pos);

	if (posTemp.x > rect.getMaxX())
	{
		posTemp.x = rect.getMaxX();
	}
	else if (posTemp.x < rect.getMinX())
	{
		posTemp.x = rect.getMinX();
	}

	if (posTemp.y > rect.getMaxY())
	{
		posTemp.y = rect.getMaxY();
	}
	else if (posTemp.y < rect.getMinY())
	{
		posTemp.y = rect.getMinY();
	}

	pos = m_pImage->getParent()->convertToNodeSpace(posTemp);
}

bool ItemBase::CheckTrigger()
{
	Vec2 pos = m_pImage->convertToWorldSpace(Vec2::ZERO);
	auto range = m_pItem->getTrigger();
	cocos2d::Rect move_trigger(pos.x + range.origin.x * m_pImage->getScaleX(),
		pos.y + range.origin.y * m_pImage->getScaleY(),
		range.size.width * m_pImage->getScaleX(),
		range.size.height * m_pImage->getScaleY());


	Vec2 x = Vec2(move_trigger.origin.x, move_trigger.origin.y);
	Vec2 x1 = Vec2(move_trigger.origin.x + move_trigger.size.width, move_trigger.origin.y + move_trigger.size.height);

	drawNode->clear();
	drawNode->drawRect(x, x1, Color4F(0, 1, 0, 1));

	for (MonsterWidgetsIter Iter = m_oMonsterWidgets.begin(); Iter != m_oMonsterWidgets.end(); ++Iter)
	{
		if (((*Iter)->getMonsterVisual() && m_pItem->getID() == EItem_yuhua)
			|| (!(*Iter)->getMonsterVisual() && m_pItem->getID() == EItem_huasa))
		{
			continue;
		}

		if (m_pItem->getID() == EItem_NiuNaiN || m_pItem->getID() == EItem_Maipian)
		{
			auto pForm = dynamic_cast<MakeForm*>(UIManager::instance()->findForm(IDC_Make));
			if (pForm != NULL)
			{
				Rect m_targetRect = pForm->getTargetRect();

				Vec2 x = Vec2(m_targetRect.origin.x, m_targetRect.origin.y);
				Vec2 x1 = Vec2(m_targetRect.origin.x + m_targetRect.size.width, m_targetRect.origin.y + m_targetRect.size.height);

				drawNode->drawRect(x, x1, Color4F(0, 1, 0, 1));

				if (m_targetRect.intersectsRect(move_trigger))
				{
					m_triggerMonster = *Iter;
					if (m_triggerMonster->getDoneNum() > 0 || m_triggerMonster->getDoneNum() == -1)
					{
						return onTriggerMonster();
					}
				}
			}
			return true;
		}

		Vec2 pos1 = (*Iter)->convertToWorldSpace(Vec2::ZERO);
		Vec2 size = (*Iter)->getImage()->getSize();
		cocos2d::Rect target_rect;
		target_rect.origin = pos1;
		target_rect.size = size;

		if (target_rect.intersectsRect(move_trigger))
		{
			m_triggerMonster = *Iter;
			if (m_triggerMonster->getDoneNum() > 0 || m_triggerMonster->getDoneNum() == -1)
			{
				return onTriggerMonster();
			}
		}
	}
	return true;
}

bool ItemBase::onTriggerMonster()
{
	return true;
}


void ItemBase::ItemShowImg()
{
	if (!m_bShowImage)
	{
		return;
	}
	m_pImage->setOpacity(255);
	if (m_pTempExImg != NULL)
	{
		m_pTempExImg->setVisible(false);
	}
	if (NULL != m_pTimelineNode)
	{
		m_pTimelineNode->setVisible(false);
	}
}

void ItemBase::ItemShowAni()
{
	
	m_pImage->setOpacity(0);
	if (m_pTempExImg != NULL)
	{
		m_pTempExImg->setVisible(true);
	}
	if (NULL != m_pTimelineNode)
	{
		m_pTimelineNode->setVisible(true);
	}
}

void ItemBase::propUserEnd()
{

}

void ItemBase::setUserComplete()
{
	if (!m_pStar->isVisible() && EItemUseType_Complete == EntityMgr::instance()->pPlayer()->getItemUse(m_pItem->getID()))
	{
		m_pStar->setPosition(m_pStar->getPosition() + ccp(100, 200));
		m_pImage->setTouchEnabled(false);
		m_pStar->runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([this]{m_pStar->setVisible(true); }), MoveBy::create(0.2f, ccp(-100, -200)), NULL));

	}
	openNextItem((EGameItemType)m_pItem->getNextOpen());
}

void ItemBase::openNextItem(EGameItemType type)
{

}

void ItemBase::showTips(ETipsType type, int  Distance)
{
	if (m_pTip == NULL)
	{
		m_pTip = ImageView::create("ani_tip_shou.png", Widget::TextureResType::PLIST);
		m_pImage->addChild(m_pTip, 10);
		m_pTip->setPosition(ccp(50, -50) + m_pImage->getContentSize()*0.5f);
		m_pTip->setAnchorPoint(ccp(0, 0.5f));
	}

	m_pTip->setVisible(true);

	switch (type)
	{
	case ETipsType_Up_Down:
	{
							  auto move1 = MoveBy::create(Distance*.002f, ccp(0, -Distance));
							  auto move2 = MoveBy::create(Distance*.002f, ccp(0, Distance));
							  auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
							  m_pTip->runAction(seq);
	}
		break;
	case ETipsType_Left_Right:
	{
								 auto move1 = MoveBy::create(Distance*.002f, ccp(Distance, 0));
								 auto move2 = MoveBy::create(Distance*.002f, ccp(-Distance, 0));
								 auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
								 m_pTip->runAction(seq);
	}
		break;
	case ETipsType_Right_Left:
	{
								 auto move1 = MoveBy::create(Distance*.002f, ccp(-Distance, 0));
								 auto move2 = MoveBy::create(Distance*.002f, ccp(Distance, 0));
								 auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
								 m_pTip->runAction(seq);
	}
		break;
	case ETipsType_Click:
	{
							auto move1 = MoveBy::create(.25f, ccp(20, 20));
							auto scale1 = ScaleTo::create(.25f, 1.2f);
							auto move2 = MoveBy::create(.25f, ccp(-20, -20));
							auto scale2 = ScaleTo::create(.25f, 1.0f);

							auto spawn1 = Spawn::create(move1, scale1, NULL);
							auto spawn2 = Spawn::create(move2, scale2, NULL);

							auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));
							m_pTip->runAction(seq);
	}
		break;
	}
}

void ItemBase::stopEffectPlaying(float dt)
{
	m_isEffectPlaying = false;
}

void ItemBase::releaseYaogaoImg()
{
	if (m_pItem->getID() == EItem_YaShua)
	{
		m_pImage->removeChildByTag(110);
	}
}

void ItemBase::addYagaoImg()
{
	if (m_pItem->getID() == EItem_YaShua)
	{
		auto pImg = ImageView::create("res/ui/yushi/ani_item_YaGao_3.png", Widget::TextureResType::LOCAL);
		m_pImage->addChild(pImg, 1, 110);
		pImg->setPosition(ccp(m_pImage->getContentSize().width*0.15 + 3, m_pImage->getContentSize().height + 2));

	}
}
