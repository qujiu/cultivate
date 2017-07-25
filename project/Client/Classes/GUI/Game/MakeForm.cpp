#include "MakeForm.h"
#include "Entity/EntityMgr.h"
#include "BabyCare.h"
#include "DiningroomForm.h"
#include "../UIManager.h"
#include "Entity/MonsterFactory.h"

#define SHAOZI_MOVE_SPEED 1200.0f
#define MAKETO_MOVE_SPEED 1000.0f;


MakeForm::MakeForm(int type) :
GameForm(IDC_Make)
, m_nType(type)
, m_pCurrFoods(NULL)
, m_nFoodsCount(0)
, m_bTouchEnd(false)
, m_eItemTarget(EGameItemTarget_Normal)
, m_pArmature(NULL)
, m_nShala(0)
, m_nFanqiejiang(0)
, m_nGoodCount(0)
, m_nGoldCount(0)
, m_nCount(0)
, m_bFlagMove(true)
, m_bFlagEnd(true)
, m_bIsCollision(false)
, m_bIsMoving(false)
, m_pJiaoImg(NULL)
, m_bShouFlag(false)
{

}

MakeForm::~MakeForm()
{

}

bool MakeForm::init()
{
	if (Form::init())
	{
		m_pLayout = static_cast<Widget*>(CSLoader::createNode("foodmake.csb"));
		this->addChild(m_pLayout, 1);
		if (m_nType == 0)
		{
			Panel_niunai = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_niunai"));
			Panel_niunai->setVisible(true);
			pBg = dynamic_cast<ImageView*>(Panel_niunai->getChildByName("Image_bg"));
			auto Button_close = dynamic_cast<Button*>(Panel_niunai->getChildByName("Button_close"));
			Button_close->addTouchEventListener(this, toucheventselector(MakeForm::onCloseButtonClicked));

			m_pPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_pot"));
			SupLayout::setRelativePos(m_pPanel, m_pPanel->getPosition(), SUP_ALIGNMENT_LB);
			auto vec = m_pPanel->getPosition();
			
			for (int i = 0; i < 2; i++)
			{
				m_bItem[i] = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_" + sup::SupString::int2String(i+1)));
				m_bItem[i]->addTouchEventListener(this, toucheventselector(MakeForm::onItemBtnClicked));
				SupLayout::setRelativePos(m_bItem[i], m_bItem[i]->getPosition(), SUP_ALIGNMENT_LB);
				m_bItem[i]->setTag(i);
				if (i = 0)
				{
					setItemTips(i);
				}
			}

			pShaozi = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_shaozi"));
			pShaozi->addTouchEventListener(this, toucheventselector(MakeForm::onShouDongClicked));
			m_pItems[EItem_shaoziN] = ItemFactory::instance()->Create(EItem_shaoziN, pShaozi);
			pShaozi->setTouchEnabled(false);
			pShaozi->setTag(EItem_shaoziN);
			this->addChild(m_pItems[EItem_shaoziN]);

			m_pCheckJiaoPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_Collision"));
			m_rectCollision = Rect({
				m_pCheckJiaoPanel->getPositionX(),
				m_pCheckJiaoPanel->getPositionY(),
				m_pCheckJiaoPanel->getContentSize().width,
				m_pCheckJiaoPanel->getContentSize().height,
			});

			m_targetRect = m_rectCollision;

			m_pCheckPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_2"));

			m_pSkHuomian = SkeletonAnimation::createWithFile("Spine/jiaoban/jiaoban.json", "Spine/jiaoban/jiaoban.atlas");
			m_pCheckPanel->addChild(m_pSkHuomian);
			m_pSkHuomian->setVisible(false);
			m_pSkHuomian->setPosition(m_bItem[0]->getPosition());
			m_pSkHuomian->setEndListener([&](int trackIndex) {
				if (trackIndex == 0)
				{
					//SoundManage::instance()->stopAllSound();
					moveToInitPos();
					m_pNextFunc = [&](){
						this->removeFromParentAndCleanup(true);
						NotificationCenter::getInstance()->postNotification(NOT_ITEM_CanTingItemMix);
					};
					m_pRewordFunc = [&](){
					/*	EntityMgr::instance()->pPlayer()->setRewordType(ERewordType_Ticket);
						EntityMgr::instance()->pPlayer()->setRewordCount(1);
						auto pForm = UIFactory::instance()->showRewordForm();
						if (NULL != pForm)
						{
							SceneManager::instance()->getCurrScene()->addChild(pForm);
						}*/
					};
					playWellDownAni();
				}
			});

			MonsterList::MonsterType* pMonsterType1 = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_NiuNai);
			if (NULL != pMonsterType1)
			{
				for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType1->begin(); pTypeIter != pMonsterType1->end(); pTypeIter++)
				{
					MonsterList::Monsters* pMonsters = pTypeIter->second;
					for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
					{
						auto pMonster = MonsterFactory::instance()->Create(*Iter);
						m_pLayout->addChild(pMonster, (*Iter)->getZorder());
						auto pos = (*Iter)->getMPos();
						pMonster->setPosition(ccp(pos.x*SUP_SCALE_X, pos.y*SUP_SCALE_Y));
						auto vec = (*Iter)->getMItemType();
						for (int i = 0; i < vec.size(); i++)
						{
							m_pItems[vec[i]]->addMonsterWidget(pMonster);
						}
					}
				}
			}
		}
		else
		{
			auto Panel_guojiang = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_guojiang"));
			Panel_guojiang->setVisible(true);

			auto pBg = dynamic_cast<ImageView*>(Panel_guojiang->getChildByName("Image_bg"));
			SupLayout::setRelativePos(pBg, pBg->getPosition(), SUP_ALIGNMENT_LB);

			auto pColseBtn = dynamic_cast<Button*>(pBg->getChildByName("Button_close"));
			pColseBtn->addTouchEventListener(this, toucheventselector(MakeForm::onCloseButtonClicked));

			auto pPlayer = EntityMgr::instance()->pPlayer();
			for (int i = 0; i < 3; i++)
			{
				m_pTarget[i] = dynamic_cast<ImageView*>(pBg->getChildByName("Image_target_" + sup::SupString::int2String(i)));
				m_pTarget[i]->loadTexture(pPlayer->getFoodsList()->getFoodsByID(pPlayer->getTargetFoods().foods[i])->getTargetImg(), Widget::TextureResType::LOCAL);
			}

			for (int j = 0; j < 8; j++)
			{
				auto pfoods = dynamic_cast<Layout*>(pBg->getChildByName("Panel_" + sup::SupString::int2String(j)));
				m_oFoods[j].init(pfoods, (EFoodsType)(j));
				m_oFoods[j].getImage()->addTouchEventListener(this, toucheventselector(MakeForm::onFoodsTouchListener));
				m_oFoods[j].getImage()->setTag(j);
			}

			m_pPropLayout = dynamic_cast<Layout*>(pBg->getChildByName("Panel_mianbao"));
			m_pPropLayout->setVisible(true);

			auto m_pPanzi = dynamic_cast<ImageView*>(m_pPropLayout->getChildByName("Img_panzi"));

			m_pMianbao = dynamic_cast<ImageView*>(m_pPanzi->getChildByName("Img_mianbao"));
			//m_pMianbao->addTouchEventListener(this, toucheventselector(MakeForm::onMianbaoClicked));
			m_pMianbao->setTouchEnabled(false);
			m_pItems[EItem_mianbaoG] = ItemFactory::instance()->Create(EItem_mianbaoG, m_pMianbao);
			this->addChild(m_pItems[EItem_mianbaoG]);

			m_pShaozi = dynamic_cast<ImageView*>(m_pPropLayout->getChildByName("Img_shaozi"));
			m_pItems[EItem_shaoziG] = ItemFactory::instance()->Create(EItem_shaoziG, m_pShaozi);
			m_pShaozi->setTag(EItem_shaoziG);
			m_pShaozi->addTouchEventListener(this, toucheventselector(MakeForm::onItemTouchListener));
			this->addChild(m_pItems[EItem_shaoziG]);
			m_pShaozi->setTouchEnabled(false);

			m_pGuoping = dynamic_cast<ImageView*>(m_pPropLayout->getChildByName("Image_pingzi"));
			m_pGuoping->addTouchEventListener(this, toucheventselector(MakeForm::onItemTouchListener));
			m_pGuoping->setTouchEnabled(false);
			m_pItems[EItem_GuoBei] = ItemFactory::instance()->Create(EItem_GuoBei, m_pGuoping);
			this->addChild(m_pItems[EItem_GuoBei]);
			initTargetRect(m_pGuoping);


			MonsterList::MonsterType* pMonsterType1 = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_MianBao);
			if (NULL != pMonsterType1)
			{
				for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType1->begin(); pTypeIter != pMonsterType1->end(); pTypeIter++)
				{
					MonsterList::Monsters* pMonsters = pTypeIter->second;
					for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
					{
						auto pMonster = MonsterFactory::instance()->Create(*Iter);
						m_pLayout->addChild(pMonster, (*Iter)->getZorder());
						auto pos = (*Iter)->getMPos();
						pMonster->setPosition(ccp(pos.x*SUP_SCALE_X, pos.y*SUP_SCALE_Y));
						auto vec = (*Iter)->getMItemType();
						for (int i = 0; i < vec.size(); i++)
						{
							m_pItems[vec[i]]->addMonsterWidget(pMonster);
						}
					}
				}
			}
		}

		return true;
	}
	return false;
}

void MakeForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		auto pPlayer = EntityMgr::instance()->pPlayer();
		if (pPlayer->getCurrIsWaterExist() == true)
		{
			pPlayer->setCurrIsWaterExist(false);
		}
		BabyCare::instance()->getCurrScene()->removeChild(this);
		//nextUIStatus();
	}
}

void MakeForm::FoodsTouchBegin()
{
	m_pCurrFoods->getImage()->loadTexture(m_pCurrFoods->getFoods()->getTargetImg(), Widget::TextureResType::LOCAL);
}

void MakeForm::FoodsTouchMove()
{
	Vec2 offset = ccpSub(m_pCurrFoods->getImage()->getTouchBeganPosition(), m_pCurrFoods->getInitialPos());
	Vec2 pos = ccpSub(m_pCurrFoods->getImage()->getTouchMovePosition(), offset);
	if (CheckFoodsTrigger())
	{
		m_pCurrFoods->getImage()->setPosition(pos);
	}

}

bool MakeForm::CheckFoodsTrigger()
{
	Vec2 pos = m_pCurrFoods->getImage()->convertToWorldSpace(Vec2::ZERO);
	auto size = m_pCurrFoods->getImage()->getSize();
	cocos2d::Rect move_trigger(pos.x,
		pos.y,
		size.width,
		size.height);

	if (m_nFoodsCount < 3 && m_targetRect.intersectsRect(move_trigger))
	{
		m_bTouchEnd = true;
		if (m_nType == 0)
		{
			VeggieEnterAction();
		}
		else
		{
			FruitEnterAction();
		}
		m_pCurrFoods->getLayout()->setZOrder(0);
		foodsEnter(m_pCurrFoods->getFoods()->getID());
		return false;
	}
	return true;
}

ImageView* MakeForm::getTargetImg()
{
	if (m_nType == 0)
	{
		return m_pMianbao;
	}
	else
	{
		return m_pmaipian;
	}

};

void MakeForm::FruitEnterAction()
{
	Vec2 pos = Vec2((m_targetRect.origin.x + m_targetRect.size.width*0.7f), m_targetRect.origin.y + m_targetRect.size.height*1.5f);
	m_pCurrFoods->getImage()->setPosition(m_pCurrFoods->getLayout()->convertToNodeSpace(pos));

	m_pCurrFoods->getImage()->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(0.2f, 1.5f), RotateTo::create(0.2f, 360 * 1), MoveBy::create(0.2f, Vec2(0, m_targetRect.size.height*0.8f)), NULL)
		, Spawn::create(ScaleTo::create(0.4f, 0.3f), RotateTo::create(0.4f, 360 * 3), MoveBy::create(0.4f, Vec2(0, -m_targetRect.size.height*1.8f)), NULL)
		, CallFunc::create(this, callfunc_selector(MakeForm::FruitEnterActionCallback)), NULL));
}

void MakeForm::FruitEnterActionCallback()
{
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ShuiGuo);
	string str[3] = { "ui/canzhuo/mianbao/ui_item_guojiang_di.png", "ui/canzhuo/mianbao/ui_item_guojiang_middle.png", "ui/canzhuo/mianbao/ui_item_guojiang_up.png" };
	for (int i = 0; i < 3;i++)
	{
		auto pGuojiang = dynamic_cast<ImageView*>(m_pGuoping->getChildByName("Image_guozha_" + sup::SupString::int2String(i)));
		pGuojiang->loadTexture(str[i], Widget::TextureResType::LOCAL);
		pGuojiang->setTag(-1);
		if (i == m_nFoodsCount)
		{
			pGuojiang->setVisible(true);
		}
	}


	EntityMgr::instance()->pPlayer()->setSelFoods(m_nFoodsCount, m_pCurrFoods->getFoods()->getID());
	m_nFoodsCount++;
	if (m_nFoodsCount == 3)
	{
		m_pItems[EItem_shaoziG]->getItemImage()->setTouchEnabled(true);
		//m_pItems[EItem_ShuiBei]->showTips(ETipsType_Right_Left, 200);
	}
	m_nGoldCount += m_pCurrFoods->getFoods()->getPrice();
	m_pCurrFoods->getImage()->removeFromParent();
	m_bTouchEnd = false;
}

void MakeForm::VeggieEnterAction()
{
	Vec2 pos = Vec2((m_targetRect.origin.x + m_targetRect.size.width*0.5f), m_targetRect.origin.y + m_targetRect.size.height*1.8f);
	m_pCurrFoods->getImage()->setVisible(false);

	auto pImg = ImageView::create(m_pCurrFoods->getFoods()->getTargetImg(), Widget::TextureResType::PLIST);
	auto pJianbing = dynamic_cast<ImageView*>(m_pPropLayout->getChildByName("Image_jianbing"));
	pJianbing->addChild(pImg, 1);
	pImg->setPosition(pJianbing->convertToNodeSpace(pos));

	pImg->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(0.2f, 0.8f), MoveBy::create(0.2f, Vec2(0, -m_targetRect.size.height*1.4f)), NULL)
		, CallFunc::create(this, callfunc_selector(MakeForm::VeggieEnterActionCallback)), NULL));

}

void MakeForm::VeggieEnterActionCallback()
{

	EntityMgr::instance()->pPlayer()->setSelFoods(m_nFoodsCount, m_pCurrFoods->getFoods()->getID());
	m_nGoldCount += m_pCurrFoods->getFoods()->getPrice();
	m_nFoodsCount++;
	m_bTouchEnd = false;
	m_pCurrFoods->getImage()->removeFromParent();
}

void MakeForm::FoodsTouchEnd()
{
	m_pCurrFoods->getImage()->runAction(MoveTo::create(0.2f, m_pCurrFoods->getInitialPos()));
	m_pCurrFoods->getImage()->loadTexture(m_pCurrFoods->getFoods()->getImg(), Widget::TextureResType::LOCAL);
}

void MakeForm::onFoodsTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EFoodsType)(((Node*)ref)->getTag());
	if (m_bTouchEnd)
		return;

	if (NULL != m_pCurrFoods)
		m_pCurrFoods->getLayout()->setZOrder(0);

	m_pCurrFoods = &m_oFoods[item_type];
	m_pCurrFoods->getLayout()->setZOrder(10);

	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		FoodsTouchBegin();
		break;
	case TOUCH_EVENT_MOVED:
		FoodsTouchMove();
		break;
	case TOUCH_EVENT_ENDED:
	case TOUCH_EVENT_CANCELED:
		FoodsTouchEnd();
		m_pCurrFoods->getLayout()->setZOrder(0);
		break;
	}
}

void MakeForm::onFrameEventListener(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex)
{
	if (evt.compare("daoguozhi") == 0)
	{
		//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_DaoShui);
	}
}

void MakeForm::AnimationMovementEventListener(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	
}


void MakeForm::initTargetRect(Widget* pNode)
{
	Vec2 pos = pNode->convertToWorldSpace(Vec2::ZERO);
	Vec2 size = pNode->getSize();
	m_targetRect.origin = pos;
	m_targetRect.size = size;
}

void MakeForm::runItemCallback()
{


}

void MakeForm::onItemTargerRelease(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Normal;
}

void MakeForm::onItemTargerStop(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Stop;
}

void MakeForm::foodsEnter(int nID)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	for (int i = 0; i < 3; i++)
	{
		if (pPlayer->getTargetFoods().foods[i] == nID)
		{
			m_pTarget[i]->setOpacity(150);
			m_nGoodCount++;
			pPlayer->setGoodFoodsCount(m_nGoodCount);
			break;
		}
	}
}

void MakeForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(0);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);

		switch (type)
		{
		case TOUCH_EVENT_BEGAN:
			m_pCurrItem->TouchBegin();
			//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);// , true);
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

void MakeForm::AddGuojangToFull(EWaterType eType)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	m_pShaozi->loadTexture("res/ui/canzhuo/ani_item_ShaoZi_4.png", TextureResType::LOCAL);
	pPlayer->setCurrWaterType(eType);
	pPlayer->setCurrIsWaterExist(true);
}

void MakeForm::AddGuojangToMianBao()
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	m_pMianbao->loadTexture("res/ui/canzhuo/mianbao/canting_mianbao_01.png", TextureResType::LOCAL);
	NotificationCenter::getInstance()->postNotification(UPDATE_MIANBAO);
	pPlayer->setCurrWaterType(EWater_Null);
	pPlayer->setCurrIsWaterExist(false);
	m_pShaozi->setTouchEnabled(false);
}

void MakeForm::IntialGuojiang(Ref* ref)
{
	EntityMgr::instance()->pPlayer()->setCurrIsWaterExist(false);
}

void MakeForm::moveToInitPos()
{
	pShaozi->setTouchEnabled(false);
	float distance = pShaozi->getPosition().distance(m_vec2InitPos);
	float delayTime = distance / SHAOZI_MOVE_SPEED;
	auto moveTo = MoveTo::create(delayTime, m_vec2InitPos);

	auto callFunc = CallFunc::create([&]{
		pShaozi->setTouchEnabled(true);
		//setBtnVisible(true);
		pShaozi->loadTexture("res/ui/canzhuo/ani_item_ShaoZi_2.png");
		m_pJiaoImg->setRotation(0);
		m_vec2InitPos = m_pJiaoImg->getPosition();
		m_bIsMoving = false;
	});
	auto seq = Sequence::createWithTwoActions(moveTo, callFunc);
	m_pJiaoImg->runAction(seq);
}


void MakeForm::onShouDongClicked(Ref *sender, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)sender)->getTag());
	if (EGameItemTarget_Normal == m_eItemTarget)
	{
		if (NULL != m_pCurrItem)
			m_pCurrItem->setZOrder(0);

		m_pCurrItem = m_pItems[item_type];
		m_pCurrItem->setZOrder(10);
		if (TOUCH_EVENT_BEGAN == type)
		{
			m_bShouFlag = true;
			//setBtnVisible(false);
			m_bFlagMove = true;
			m_pJiaoImg = pShaozi;
			pShaozi->loadTexture("res/ui/canzhuo/ani_item_ShaoZi_2.png");
			if (!m_bIsMoving)
			{
				m_vec2InitPos = pShaozi->getPosition();
			}
			m_vec2Delta = pShaozi->getTouchBeganPosition();

			pShaozi->setRotation(-90);
		}
		else if (TOUCH_EVENT_MOVED == type && m_bFlagMove)
		{
			auto delta = pShaozi->getTouchMovePosition() - m_vec2Delta;
			setToolPos(delta);
			m_vec2Delta = pShaozi->getTouchMovePosition();
			checkCollisionJiao();

		}
		else if ((TOUCH_EVENT_ENDED == type || TOUCH_EVENT_CANCELED == type))
		{
			if (!m_bFlagEnd)
			{
				pauseSkeletonAni();
				m_bFlagEnd = true;
				return;
			}
			m_bShouFlag = false;
			moveToInitPos();
			if (m_nCount == 1)
			{
				m_bIsMoving = false;
				pauseSkeletonAni();
				m_nCount = 2;
			}
		}
	}
}

void MakeForm::setToolPos(Vec2 deltaPos)
{
	float fNextPosX = m_pJiaoImg->getPositionX() + deltaPos.x;

	Vec2 checkPos = m_pCheckJiaoPanel->getParent()->convertToWorldSpace(Vec2::ZERO);
	checkPos = m_pJiaoImg->getParent()->convertToNodeSpace(checkPos);  

	//if (fNextPosX >= checkPos.x + m_rectCollision.size.width - 40  && m_bIsCollision)
	//{
	//	fNextPosX = checkPos.x - 40 + m_rectCollision.size.width ;
	//}
	//else if (fNextPosX <= checkPos.x + 40 && m_bIsCollision)
	//{
	//	fNextPosX = checkPos.x + 40;
	//}

	float fNextPosY = m_pJiaoImg->getPositionY() + deltaPos.y;

	if (fNextPosY <= checkPos.y +200 && m_bIsCollision)
	{
		fNextPosY = checkPos.y + 200;
	}

	m_pJiaoImg->setPosition(Vec2(fNextPosX, fNextPosY));
}

void MakeForm::checkCollisionJiao()
{
	Vec2 materialWorldPos = m_pJiaoImg->convertToWorldSpaceAR(Vec2::ZERO);
	Rect materialRect = Rect({
		materialWorldPos.x - m_pJiaoImg->getContentSize().width / 2,
		materialWorldPos.y,
		m_pJiaoImg->getContentSize().width / 2,
		m_pJiaoImg->getContentSize().height
	});


	Vec2 checkPos = m_pCheckJiaoPanel->convertToWorldSpace(Vec2::ZERO);
	Rect shadowRect = Rect({
		checkPos.x,
		checkPos.y,
		m_pCheckJiaoPanel->getContentSize().width,
		m_pCheckJiaoPanel->getContentSize().height 
	});

	if (materialRect.intersectsRect(shadowRect))
	{
		if (!m_bIsMoving)
		{
			m_bFlagMove = true;
			m_bIsMoving = true;
			m_bFlagEnd = false;
			return;
		}

		m_bIsCollision = true;
		if (m_nCount == 0)
		{
			pauseSkeletonAni();
			m_nCount = 2;
			return;
			m_nCount = 1;
		}
		else if (m_nCount == 2)
		{
			this->unschedule(CC_SCHEDULE_SELECTOR(MakeForm::cutDownIdleTime));
			this->schedule(CC_SCHEDULE_SELECTOR(MakeForm::cutDownIdleTime), 0.2f);
			resumSkeletonAni();
			m_nCount = 1;
		}
	}
	else
	{
		m_bIsCollision = false;
		m_bFlagEnd = true;
		if (m_nCount == 1)
		{
			pauseSkeletonAni();
			m_nCount = 2;
		}
	}
}

void MakeForm::pauseSkeletonAni()
{
	m_pSkHuomian->pause();
	//removeStirPart();
}

void MakeForm::resumSkeletonAni()
{
	m_pSkHuomian->resume();
	//addStirPart();
}

void MakeForm::cutDownIdleTime(float dt)
{
	Vec2 curPos = m_pJiaoImg->getTouchMovePosition();
	if (m_vec2Delta == curPos)
	{
		m_nCount = 2;
		pauseSkeletonAni();
	}
	this->unschedule(CC_SCHEDULE_SELECTOR(MakeForm::cutDownIdleTime));
}

void MakeForm::onItemBtnClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//setBtnVisible(false);
		m_nTag = ((Node*)sender)->getTag();

		if (!m_bFlagEnd)
		{
			showAddAction(m_nTag);
			return;
		}
		m_bFlagMove = true;
		m_bItem[m_nTag]->stopAllActions();
		m_bItem[m_nTag]->setLocalZOrder(10);
		m_vec2InitPos = m_bItem[m_nTag]->getPosition();
		m_vec2Delta = m_bItem[m_nTag]->getTouchBeganPosition();
	}
	else if (TOUCH_EVENT_MOVED == type && m_bFlagMove)
	{
		m_vec2Delta = m_bItem[m_nTag]->getTouchMovePosition() - m_vec2Delta;
		m_bItem[m_nTag]->setPosition(m_bItem[m_nTag]->getPosition() + m_vec2Delta);
		m_vec2Delta = m_bItem[m_nTag]->getTouchMovePosition();
		checkCollision();
	}
	else if ((TOUCH_EVENT_ENDED == type || TOUCH_EVENT_CANCELED == type) && m_bFlagEnd)
	{
		//setBtnVisible(true);
		string str[] = { "res/ui/canzhuo/ui_item_cailiao_milk_nosd.png", "res/ui/canzhuo/ui_item_maipian.png"};
		m_bItem[m_nTag]->loadTexture(str[m_nTag]);
		m_bItem[m_nTag]->setTouchEnabled(false);
		float distance = m_bItem[m_nTag]->getPosition().distance(m_vec2InitPos);
		float delayTime = distance / MAKETO_MOVE_SPEED;
		auto moveTo = MoveTo::create(delayTime, m_vec2InitPos);

		auto callFunc = CallFunc::create([&]{
			m_bItem[m_nTag]->setTouchEnabled(true);
			m_bItem[m_nTag]->setLocalZOrder(0);
		});
		auto seq = Sequence::createWithTwoActions(moveTo, callFunc);
		m_bItem[m_nTag]->runAction(seq);
	}
}

void MakeForm::setItemTips(int nIndex)
{
	m_bItem[nIndex]->setTouchEnabled(true);
	auto scale = ScaleTo::create(0.5f, 1.1f);
	auto scale1 = ScaleTo::create(0.5f, 0.9f);
	m_bItem[nIndex]->runAction(RepeatForever::create(Sequence::create(scale, scale1, NULL)));
	//setBtnVisible(true);
}

void MakeForm::showAddAction(int nIndex)
{
	if (nIndex == 0)
	{
		m_bItem[nIndex]->setRotation(30);

		Node* m_pTimelineNode = CSLoader::createNode("res/ui/ani_milk.csb");
		ActionTimeline* m_pActionTimeline = CSLoader::createTimeline("res/ui/ani_milk.csb");
		m_pTimelineNode->runAction(m_pActionTimeline);
		m_bItem[nIndex]->getParent()->addChild(m_pTimelineNode);
		auto m_vInitialPos = m_bItem[nIndex]->convertToWorldSpace(Vec2(0, 0));
		m_pTimelineNode->setPosition(m_vInitialPos);
		m_pActionTimeline->play("aniHit", false);
		m_pActionTimeline->setAnimationEndCallFunc("aniHit", CC_CALLBACK_1(MakeForm::AnimationEndListener, this,nIndex));


		auto Panelpos = dynamic_cast<Layout*>(m_bItem[nIndex]->getChildByName("liushui"));
		auto LiushuiPos = Panelpos->convertToWorldSpace(Vec2(0, 0));
		ParticleSystemQuad * liushui;
		liushui = ParticleSystemQuad::create("res/effect/effect_niunai.plist");
		m_pTimelineNode->addChild(liushui);
		liushui->setAutoRemoveOnFinish(true);
		liushui->setPosition(LiushuiPos);
	}
	else
	{
		m_bItem[nIndex]->setRotation(-30);

		Node* m_pTimelineNode = CSLoader::createNode("res/ui/ani_milk.csb");
		ActionTimeline* m_pActionTimeline = CSLoader::createTimeline("res/ui/ani_maipian.csb");
		m_pTimelineNode->runAction(m_pActionTimeline);
		m_bItem[nIndex]->getParent()->addChild(m_pTimelineNode);
		auto m_vInitialPos = m_bItem[nIndex]->convertToWorldSpace(Vec2(0, 0));
		m_pTimelineNode->setPosition(m_vInitialPos);
		m_pActionTimeline->play("aniHit", false);
		m_pActionTimeline->setAnimationEndCallFunc("aniHit", CC_CALLBACK_1(MakeForm::AnimationEndListener, this,nIndex));


		auto Panelpos = dynamic_cast<Layout*>(m_bItem[nIndex]->getChildByName("liushui"));
		auto LiushuiPos = Panelpos->convertToWorldSpace(Vec2(0, 0));
		ParticleSystemQuad * liushui;
		liushui = ParticleSystemQuad::create("res/effect/effect_maipian.plist");
		m_pTimelineNode->addChild(liushui);
		liushui->setAutoRemoveOnFinish(true);
		liushui->setPosition(LiushuiPos);
	}


}

void MakeForm::checkCollision()
{
	Vec2 materialWorldPos = m_bItem[m_nTag]->convertToWorldSpaceAR(Vec2::ZERO);

	Rect materialRect = Rect({
		materialWorldPos.x - m_bItem[m_nTag]->getContentSize().width / 2,
		materialWorldPos.y - m_bItem[m_nTag]->getContentSize().height / 2,
		m_bItem[m_nTag]->getContentSize().width / 2,
		m_bItem[m_nTag]->getContentSize().height / 2
	});


	Vec2 checkPos = m_pCheckJiaoPanel->convertToWorldSpace(Vec2::ZERO);
	Rect shadowRect = Rect({
		checkPos.x,
		checkPos.y,
		m_pCheckJiaoPanel->getContentSize().width / 2,
		m_pCheckJiaoPanel->getContentSize().height
	});

	if (materialRect.intersectsRect(shadowRect))
	{
		m_bFlagMove = false;
		m_bFlagEnd = false;

		Vec2 vec[2] = { Vec2(80, 200), Vec2(100, 170)};
		Vec2 pos = m_bItem[m_nTag]->getParent()->convertToNodeSpace(vec[m_nTag] + checkPos);

		float distance = m_bItem[m_nTag]->getPosition().distance(pos);
		float delayTime = distance / MAKETO_MOVE_SPEED;

		auto moveTo = MoveTo::create(delayTime, pos);
		m_bItem[m_nTag]->setTouchEnabled(false);

		auto callFunc = CallFunc::create([&]{
			m_bItem[m_nTag]->setTouchEnabled(true);
		});
		auto seq = Sequence::createWithTwoActions(moveTo, callFunc);
		m_bItem[m_nTag]->runAction(seq);

		m_nCount++;
	}
	else
	{
		m_bFlagEnd = true;
	}
}

void MakeForm::AnimationEndListener(Node *obj, int index)
{
	if (index == 0)
	{
		auto m_pNiunai = dynamic_cast<ImageView*>(m_pCheckPanel->getChildByName("Image_niunai"));
		m_pNiunai->setVisible(true);
	}
	else
	{
	/*	auto m_pMaipian = dynamic_cast<ImageView*>(m_pCheckPanel->getChildByName("Image_maipian"));
		m_pMaipian->setVisible(true);*/
		pShaozi->setTouchEnabled(true);

		auto m_pNiunai = dynamic_cast<ImageView*>(m_pCheckPanel->getChildByName("Image_niunai"));
		m_pNiunai->setVisible(false);

		m_pSkHuomian->setVisible(true);
		m_pSkHuomian->setAnimation(0, "animation", false);
	}
}