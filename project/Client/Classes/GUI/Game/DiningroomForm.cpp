#include "DiningroomForm.h"
#include "../Form/MenuControl.h"
#include "../UIFactory.h"
#include "../UIManager.h"
#include "Entity/EntityMgr.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "SDK/SupSDK.h"
#include "Entity/MonsterFactory.h"
#include "GUI/Form/BabyControl.h"


DiningRoomForm::DiningRoomForm() :
GameForm(IDC_DiningRoom)
, m_bOpenMake(true)
, m_eItemTarget(EGameItemTarget_Normal)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(DiningRoomForm::openMianBaoinRoom), UPDATE_MIANBAO, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(DiningRoomForm::openWaninRoom), NOT_ITEM_CanTingItemMix, NULL);


}

DiningRoomForm::~DiningRoomForm()
{
	//SoundManage::instance()->stopSound();
	NotificationCenter::getInstance()->removeObserver(this, UPDATE_MIANBAO);
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_CanTingItemMix);

}

bool DiningRoomForm::init()
{
	if (GameForm::init())
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		m_pLayout = static_cast<Widget*>(CSLoader::createNode("DiningRoom.csb"));
		this->addChild(m_pLayout, 1);

		auto pPropBg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_bg"));
		pPropBg->setPosition(ccp(pPropBg->getPositionX()*SUP_SCALE_X, pPropBg->getPositionY()*SUP_SCALE_Y));
		pPropBg->setPositionX(m_winSize.width*0.5f);

		auto Img_zhuozi = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_zhuozi"));
		Img_zhuozi->setPosition(ccp(Img_zhuozi->getPositionX()*SUP_SCALE_X, Img_zhuozi->getPositionY()*SUP_SCALE_Y));
		Img_zhuozi->setPositionX(m_winSize.width*0.5f);


		m_pImagineImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_fuxiangkuang"));
		SupLayout::setRelativePos(m_pImagineImg, m_pImagineImg->getPosition(), SUP_ALIGNMENT_LB);
		m_pImagineImg->addTouchEventListener(this, toucheventselector(DiningRoomForm::onImagineButtonClicked));
		m_pImagineImg->setVisible(false);
		m_pImagineClothesImg = dynamic_cast<ImageView*>(m_pImagineImg->getChildByName("Image_eat"));
		m_pImagineClothesImg->setVisible(false);

		m_pPropLayoutzhijin = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_banzi1"));
		m_pIzhijin = dynamic_cast<ImageView*>(m_pPropLayoutzhijin->getChildByName("Img_zhijin"));
		m_pItems[EItem_zhijin] = ItemFactory::instance()->Create(EItem_zhijin, m_pIzhijin);
		this->addChild(m_pItems[EItem_zhijin]);

		m_pPropLayoutweijin = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_banzi2"));
		m_pIweijin = dynamic_cast<ImageView*>(m_pPropLayoutweijin->getChildByName("Img_weijin"));
		m_pItems[EItem_weizui] = ItemFactory::instance()->Create(EItem_weizui, m_pIweijin);
		this->addChild(m_pItems[EItem_weizui]);

		auto type = EntityMgr::instance()->pPlayer()->getCurrRoleId();
		m_nRandType = CCRANDOM_0_1() * 2;
		

		m_nRandType = 0;
		
		
		if (m_nRandType == 0)
		{
			m_pPropLayout1 = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_niunai"));
			m_pPropLayout1->setPositionX((m_winSize.width - m_pPropLayout1->getContentSize().width) / 2);
			m_pPropLayout1->setVisible(true);

			auto pLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_mianbao"));
			pLayout->setVisible(false);

			auto pWan = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_wan"));
			pWan->addTouchEventListener(this, toucheventselector(DiningRoomForm::onOpenMakeListener));
			m_pItems[EItem_wan] = ItemFactory::instance()->Create(EItem_wan, pWan);
			this->addChild(m_pItems[EItem_wan]);

			auto pTang = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("tang"));
			pTang->setVisible(false);

			auto pNiunai = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_niunai"));
			pNiunai->addTouchEventListener(this, toucheventselector(DiningRoomForm::onOpenMakeListener));
			m_pItems[EItem_NiuNaiM] = ItemFactory::instance()->Create(EItem_NiuNaiM, pNiunai);
			this->addChild(m_pItems[EItem_NiuNaiM]);

			auto pNaiping = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_naiping"));
			pNaiping->addTouchEventListener(this, toucheventselector(DiningRoomForm::onNaipingItemTouchListener));
			m_pItems[EItem_naiping] = ItemFactory::instance()->Create(EItem_naiping, pNaiping);
			this->addChild(m_pItems[EItem_naiping]);

			m_pNaiping = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Image_naiping"));
			m_pNaiFen = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Image_naifen"));
			m_pNaiping->setVisible(false);
			m_pNaiFen->setVisible(false);

			m_pshaozi = dynamic_cast<ImageView*>(pWan->getChildByName("Img_shaozi"));
			m_pshaozi->addTouchEventListener(this, toucheventselector(DiningRoomForm::onItemTouchListener));
			m_pItems[EItem_shaoziM] = ItemFactory::instance()->Create(EItem_shaoziM, m_pshaozi);
			this->addChild(m_pItems[EItem_shaoziM]);

			MonsterList::MonsterType* pMonsterType1 = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_DiningNiuNai);
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
		else{
			m_pPropLayout1 = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_mianbao"));
			m_pPropLayout1->setPositionX((m_winSize.width - m_pPropLayout1->getContentSize().width) / 2);
			m_pPropLayout1->setVisible(true);

			auto pLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_niunai"));
			pLayout->setVisible(false);

			auto m_pingguo = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_pingguo"));
			m_pingguo->addTouchEventListener(this, toucheventselector(DiningRoomForm::onItemTouchListener));
			m_pItems[EItem_shuiguo] = ItemFactory::instance()->Create(EItem_shuiguo, m_pingguo);
			this->addChild(m_pItems[EItem_shuiguo]);

			m_pmianbao = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_miaobao"));
			m_pmianbao->addTouchEventListener(this, toucheventselector(DiningRoomForm::onItemTouchListener));
			m_pItems[EItem_mianbaoM] = ItemFactory::instance()->Create(EItem_mianbaoM, m_pmianbao);
			this->addChild(m_pItems[EItem_mianbaoM]);
			m_pmianbao->setTag(EItem_mianbaoM);

			MonsterList::MonsterType* pMonsterType1 = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_DiningMianBao);
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
		
		/*m_pMenu = MenuControl::createInst();
		this->addChild(m_pMenu, 10);*/

		runImagineAction();

		auto Panel_touch = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_touch"));

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(DiningRoomForm::onTouchBeginListener, this);
		listener->onTouchMoved = CC_CALLBACK_2(DiningRoomForm::onTouchMoveListener, this);
		listener->onTouchEnded = CC_CALLBACK_2(DiningRoomForm::onTouchEndListener, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Panel_touch);
		return true;
	}
	return false;
}

void DiningRoomForm::onImagineButtonClicked(Ref* ref, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{

	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		//runImagineActionCallBack();
		if (m_bOpenMake)
		{
			openMakeForm();
		}
	}
}

void DiningRoomForm::runImagineAction()
{
	m_pImagineImg->setVisible(true);
	m_pImagineImg->setScale(0);
	m_pImagineImg->runAction(Sequence::create(
		ScaleTo::create(1.0f, 1.0, 1.0),
		CallFunc::create(this, callfunc_selector(DiningRoomForm::runImagineActionCallBack)), NULL));
}

void DiningRoomForm::runImagineActionCallBack()
{
	m_pImagineClothesImg->setVisible(true);

	string str = "";
	if (m_nRandType)
	{
		str = "ui/canzhuo/ani_item_CanJu_1.png";
	}
	else
	{
		str = "ui/canzhuo/ani_item_CanJu_1.png";
	}
	m_pImagineClothesImg->loadTexture(str, TextureResType::LOCAL);

	m_pImagineClothesImg->runAction(
		RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.75f), ScaleTo::create(0.5f, 0.85f), NULL))
		);
}

void DiningRoomForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	if (m_bOpenMake)
	{
		openMakeForm();
		return;
	}

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
			m_pCurrItem->TouchMove();
			break;
		case TOUCH_EVENT_ENDED:
		case TOUCH_EVENT_CANCELED:
			m_pCurrItem->TouchEnd();
			break;
		}
	}

}

void DiningRoomForm::onOpenMakeListener(Ref* ref, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		
	}
	else if (type == TOUCH_EVENT_ENDED)
	{
		if (m_bOpenMake)
		{
			openMakeForm();
		}
	}
}


void DiningRoomForm::openMakeForm()
{

	if (NULL == UIManager::instance()->findForm(IDC_Make))
	{
		EntityMgr::instance()->pPlayer()->createFoodsRandom(m_nRandType);
		auto pForm = UIFactory::instance()->showMakeForm(m_nRandType);
		BabyCare::instance()->getCurrScene()->addChild(pForm, 100);
	}
}

void DiningRoomForm::makeFormCallback(bool bOpen)
{
	m_bOpenMake = bOpen;

}

void DiningRoomForm::closeMakeFormCallback()
{
	if (m_nRandType)
	{
		//m_pJianbing->setVisible(true);
	}
	else
	{
		//pWan->loadTexture("ani_item_guozhibei_zhuomian.png", Widget::TextureResType::PLIST);
	}
	m_bOpenMake = false;
}

void DiningRoomForm::onItemTargerRelease(Ref* object)
{
	//hideTips();
	m_eItemTarget = EGameItemTarget_Normal;
}

void DiningRoomForm::onItemTargerStop(Ref* object)
{
	m_eItemTarget = EGameItemTarget_Stop;
}

void DiningRoomForm::initState()
{
	if (m_nRandType)
	{
		//m_pJianbing->setVisible(false);
	}
	else
	{
		//m_pGuobei->loadTexture("ani_item_guozhibei.png", Widget::TextureResType::PLIST);
	}
	auto pPlayer = EntityMgr::instance()->pPlayer();
	int num = EntityMgr::instance()->pPlayer()->getGoodFoodsCount();
	//if (pPlayer->getGoodFoodsCount() >= 3)
	//{
	//	pPlayer->getpBabyControl()->runRoleAnimation(EBabyExpression_Smile);
	//}
	//else
	//{
	//	pPlayer->getpBabyControl()->runRoleAnimation(EBabyExpression_Sad);
	//}
	//m_bOpenMake = true;
}

void DiningRoomForm::onLockToolsNot(Ref* object)
{
	for (int i = 0; i < EItem_Max; i++)
	{
		if (NULL != m_pItems[i]->getItem())
		{
			m_pItems[i]->setItemOpen();
		}
	}
}

void DiningRoomForm::onLockRoomNot(Ref* object)
{
	auto pForm = UIManager::instance()->findForm(IDC_Info);
	if (NULL != pForm)
	{
		pForm->removeFromParentAndCleanup(true);
	}
}

void DiningRoomForm::onOpenAwardNot(Ref* object)
{
	this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([this](){
		auto pForm = UIFactory::instance()->showAwardForm(m_nRandType);
		this->addChild(pForm, 100);
	}), NULL));

}

void DiningRoomForm::onCloseAwardNot(Ref* objeck)
{
	BabyCare::instance()->onStatusChanged(EScene_Select);
}

bool DiningRoomForm::onTouchBeginListener(Touch *touch, Event *unusedEvent)
{
	//m_pMenu->MenuClose();
	return true;
}

void DiningRoomForm::onTouchMoveListener(Touch *touch, Event *unusedEvent)
{
}

void DiningRoomForm::onTouchEndListener(Touch *touch, Event *unusedEvent)
{
}

void DiningRoomForm::showTips()
{
	m_pMenu->setVisible(false);
	m_pMini->setVisible(false);
}

void DiningRoomForm::hideTips()
{
	m_pMenu->setVisible(true);
	m_pMini->setVisible(true);
}

void DiningRoomForm::onCloseInfoNot(Ref* object)
{
	BabyCare::instance()->onStatusChanged(EScene_Select);
}

void DiningRoomForm::openMianBaoinRoom(Ref* object)
{
	m_pmianbao->loadTexture("res/ui/canzhuo/mianbao/canting_mianbao_01.png", TextureResType::LOCAL);
	m_bOpenMake = false;
}

void DiningRoomForm::openWaninRoom(Ref* object)
{
	auto pWan = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("Img_wan"));
	auto pTang = dynamic_cast<ImageView*>(m_pPropLayout1->getChildByName("tang"));
	pTang->setVisible(true);
	m_bOpenMake = false;
}

void DiningRoomForm::onNaipingItemTouchListener(Ref* ref, TouchEventType type)
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		showNaipingImg();
	}
	else if (type == TOUCH_EVENT_ENDED)
	{

	}
}

void DiningRoomForm::showNaipingImg()
{
	m_pItems[EItem_naiping]->getItemImage()->setVisible(false);
	m_pNaiping->setVisible(true);
	auto pNaigai = dynamic_cast<ImageView*>(m_pNaiping->getChildByName("Image_naigai"));
	pNaigai->runAction(EaseBackIn::create(MoveBy::create(0.3f, ccp(-200.0f, -50.0f))));
}

void DiningRoomForm::runYaonaiTips()
{
	auto pNaigai = dynamic_cast<ImageView*>(m_pNaiping->getChildByName("Image_naigai"));
	pNaigai->runAction(EaseBackOut::create(MoveBy::create(0.3f, ccp(200.0f, 50.0f))));

	//Device::setAccelerometerEnabled(true);
	//showShakeAni(true);
	//showTips();
	//m_eItemTarget = EGameItemTarget_Shake;
	//m_pAccListener = EventListenerAcceleration::create([=](Acceleration* acc, Event* event){
	//	EntityMgr::instance()->pPlayer()->useAcc(acc);
	//	if (EntityMgr::instance()->pPlayer()->isShake(acc))
	//	{
	//		EntityMgr::instance()->pPlayer()->stopAcc();
	//		//m_pCurrItem->TargetBegin();
	//		m_eItemTarget = EGameItemTarget_Normal;
	//		showShakeAni(false);
	//		hideTips();
	//		Device::setAccelerometerEnabled(false);
	//		if (m_pAccListener)
	//		{
	//			Director::getInstance()->getEventDispatcher()->removeEventListener(m_pAccListener);
	//			m_pAccListener = NULL;
	//		}
	//		runYaonaiAction();
	//		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_NaiPing);
	//	}
	//});

	runYaonaiAction();
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pAccListener, m_pCurrItem->getItemImage());
}

void DiningRoomForm::runYaonaiAction()
{
	m_pNaiping->setVisible(false);
	m_pNaiFen->setVisible(false);

	Node* m_pTimelineNode = CSLoader::createNode("res/ui/ani_naiping.csb");
	ActionTimeline* m_pActionTimeline = CSLoader::createTimeline("res/ui/ani_naiping.csb");
	m_pTimelineNode->runAction(m_pActionTimeline);
	m_pTimelineNode->setPosition(m_pNaiping->getPosition());
	m_pActionTimeline->play("ani_hunhe", false);
	m_pActionTimeline->setAnimationEndCallFunc("ani_hunhe", CC_CALLBACK_0(DiningRoomForm::AnimationEndListener, this));
}

void DiningRoomForm::AnimationEndListener()
{
	//m_pBabyControl->runRoleAnimation(EBabyExpression_Eat);
	Node* m_pTimelineNode = CSLoader::createNode("res/ui/ani_naiping.csb");
	ActionTimeline* m_pActionTimeline = CSLoader::createTimeline("res/ui/ani_naiping.csb"); 
	m_pActionTimeline->play("ani_henai", false);
}