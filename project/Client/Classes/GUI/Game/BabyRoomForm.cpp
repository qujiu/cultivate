#include "BabyRoomForm.h"
#include "Entity/EntityMgr.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "GUI/Form/MenuControl.h"
#include "Entity/EntityMgr.h"
#include "Entity/MonsterFactory.h"
#include "GUI/Form/BabyControl.h"
#include "GameScene.h"


BabyRoomForm::BabyRoomForm() :
GameForm(IDC_BabyRoom)
, m_eUIStatus(EPropUIStatus_first)
, m_eItemTarget(EGameItemTarget_Normal)
, m_bCool(true)
, m_isOpen(false)
, m_bnight(true)
, m_isSleep(false)
, m_fCurrJingliTimer(0)
, CurWindowState(true)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BabyRoomForm::onPissClean), NOT_ITEM_ZHINIAOKU_PISS, NULL);

}

BabyRoomForm::~BabyRoomForm()
{
	//SoundManage::instance()->stopSound();
	NotificationCenter::getInstance()->removeObserver(this, NOT_ITEM_ZHINIAOKU_PISS);

}

bool BabyRoomForm::init()
{
	if (GameForm::init())
	{
		setKeyboardEnabled(false);
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		m_pLayout = static_cast<Widget*>(CSLoader::createNode("BabyRoom.csb"));
		this->addChild(m_pLayout);

		Layout* panel_zhuozi = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_zhuozi"));
		itemBaiYe = dynamic_cast<Sprite*>(panel_zhuozi->getChildByName("Spr_baiyechuan"));


		auto Panel_baiyechuang = dynamic_cast<Layout*>(panel_zhuozi->getChildByName("Panel_baiyechuang"));
		Panel_baiyechuang->setPosition(ccp(Panel_baiyechuang->getPositionX()*SUP_SCALE_X, Panel_baiyechuang->getPositionY()*SUP_SCALE_Y));
		Panel_baiyechuang->addTouchEventListener(this, toucheventselector(BabyRoomForm::onWindowActionClicked));
		auto pBaiyeChuangNode = dynamic_cast<Node*>(Panel_baiyechuang->getChildByName("Ani_baiyechuang"));
		m_pBaiyeTimeLine = CSLoader::createTimeline("res/UI/Ani_baiyechuang.csb");
		pBaiyeChuangNode->runAction(m_pBaiyeTimeLine);
		m_pBaiyeTimeLine->play("animation2", false);


		auto pClockPanel = dynamic_cast<Layout*>(panel_zhuozi->getChildByName("Panel_clock"));
		pClockPanel->setPosition(ccp(pClockPanel->getPositionX()*SUP_SCALE_X, pClockPanel->getPositionY()*SUP_SCALE_Y));
		pClockPanel->addTouchEventListener(this, toucheventselector(BabyRoomForm::onClockActionClicked));
		auto pClockNode = dynamic_cast<Node*>(pClockPanel->getChildByName("Ani_clock"));
		m_pClockTimeLine = CSLoader::createTimeline("res/UI/Ani_naozhong.csb");
		pClockNode->runAction(m_pClockTimeLine);
		m_pClockTimeLine->play("animation2", false);
		m_clockPos = pClockPanel->convertToWorldSpace(Vec2::ZERO);


		auto pTaidengPanel = dynamic_cast<ImageView*>(panel_zhuozi->getChildByName("Img_taideng"));
		pTaidengPanel->setPosition(ccp(pTaidengPanel->getPositionX()*SUP_SCALE_X, pTaidengPanel->getPositionY()*SUP_SCALE_Y));
		pTaidengPanel->addTouchEventListener(this, toucheventselector(BabyRoomForm::onLightBtnClicked));
		pTaidengPanel->setTouchEnabled(true);
		auto Image_xian = dynamic_cast<ImageView*>(pTaidengPanel->getChildByName("Image_xian"));
		lightguang = dynamic_cast<ImageView*>(pTaidengPanel->getChildByName("guang"));
		lightguang->setVisible(true);

		Layout* panel_chuang = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_chuang"));

		ImageView* Img_chuang = dynamic_cast<ImageView*>(panel_chuang->getChildByName("Img_chuang"));
		m_pItems[EItem_bed] = ItemFactory::instance()->Create(EItem_bed, Img_chuang);
		Img_chuang->setTag((EGameItemType)EItem_bed);
		Img_chuang->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
		Img_chuang->setTouchEnabled(false);
		Img_chuang->setPosition(ccp(Img_chuang->getPositionX()*SUP_SCALE_X, Img_chuang->getPositionY()*SUP_SCALE_Y));
		this->addChild(m_pItems[EItem_bed]);

		Img_zhentou = dynamic_cast<ImageView*>(Img_chuang->getChildByName("Img_zhentou"));
		m_pItems[EItem_zhentou] = ItemFactory::instance()->Create(EItem_zhentou, Img_zhentou);
		Img_zhentou->setTag((EGameItemType)EItem_zhentou);
		Img_zhentou->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
		Img_zhentou->setTouchEnabled(false);
		Img_zhentou->setPosition(ccp(Img_zhentou->getPositionX()*SUP_SCALE_X, Img_zhentou->getPositionY()*SUP_SCALE_Y));
		this->addChild(m_pItems[EItem_zhentou]);

		m_pBeiziImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Img_beizi"));
		m_pItems[EItem_beizi] = ItemFactory::instance()->Create(EItem_beizi, m_pBeiziImg);
		m_pBeiziImg->setTag((EGameItemType)EItem_beizi);
		m_pBeiziImg->addTouchEventListener(this, toucheventselector(BabyRoomForm::onBeiziTouchListener));
		m_pBeiziImg->setTouchEnabled(true);
		m_pBeiziImg->setPosition(ccp(m_pBeiziImg->getPositionX()*SUP_SCALE_X, m_pBeiziImg->getPositionY()*SUP_SCALE_Y));
		this->addChild(m_pItems[EItem_beizi]);
		m_beiziInitPos = m_pBeiziImg->getPosition();
		m_pBeiziImg->setZOrder(5);

	    panel_daoju = dynamic_cast<Layout*>(panel_chuang->getChildByName("Panel_daoju"));
		Img_xiaobear = dynamic_cast<ImageView*>(panel_daoju->getChildByName("Img_xiaobear"));
		m_pItems[EItem_wanju] = ItemFactory::instance()->Create(EItem_wanju, Img_xiaobear);
		Img_xiaobear->setTag((EGameItemType)EItem_wanju);
		Img_xiaobear->setTouchEnabled(true);
		Img_xiaobear->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
		this->addChild(m_pItems[EItem_wanju]);
		m_wanjuPos = Img_xiaobear->convertToWorldSpace(Vec2::ZERO);

		Img_zhiNiuKu = dynamic_cast<ImageView*>(panel_daoju->getChildByName("Img_zhijin"));
		m_pItems[EItem_zhiniaoku] = ItemFactory::instance()->Create(EItem_zhiniaoku, Img_zhiNiuKu);
		Img_zhiNiuKu->setTag((EGameItemType)EItem_zhiniaoku);
		Img_zhiNiuKu->setTouchEnabled(true);
		Img_zhiNiuKu->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
		this->addChild(m_pItems[EItem_zhiniaoku]);
		m_zhiniaokuPos = Img_zhiNiuKu->convertToWorldSpace(Vec2::ZERO);

		pGameFaguangImg = dynamic_cast<ImageView*>(Img_zhiNiuKu->getChildByName("Image_waifaguang"));


		Img_naizui = dynamic_cast<ImageView*>(panel_daoju->getChildByName("Img_naizui"));
		m_pItems[EItem_naizui] = ItemFactory::instance()->Create(EItem_naizui, Img_naizui);
		Img_naizui->setTag((EGameItemType)EItem_naizui);
		Img_naizui->setTouchEnabled(true);
		Img_naizui->addTouchEventListener(this, toucheventselector(GameForm::onItemTouchListener));
		this->addChild(m_pItems[EItem_naizui]);
		m_naizuiPos = Img_naizui->convertToWorldSpace(Vec2::ZERO);


		m_pSubMenu = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_submenu_bg"));
		m_pSubMenu->setPosition(ccp(m_pSubMenu->getPositionX()*SUP_SCALE_X, m_pSubMenu->getPositionY()*SUP_SCALE_Y));
		m_vecInitToolBar = m_pSubMenu->getPosition();

		auto pCatspaw = dynamic_cast<ImageView*>(m_pSubMenu->getChildByName("Image_catspaw"));
		m_pArrow = dynamic_cast<ImageView*>(pCatspaw->getChildByName("Image_arrow"));
		m_pArrow->setTouchEnabled(true);
		m_pArrow->addTouchEventListener(this, toucheventselector(BabyRoomForm::onArrowButtonClicked));
		m_vecArrowPos = m_pArrow->convertToWorldSpaceAR(Vec2::ZERO);
		m_pSubProp = dynamic_cast<ui::ScrollView*>(m_pSubMenu->getChildByName("ScrollView"));
		auto pIconTemplete = dynamic_cast<ui::ImageView*>(m_pSubMenu->getChildByName("Img_templete"));
		pIconTemplete->setVisible(false);
		m_pSubMenu->setVisible(true);
		m_pSubProp->setScrollBarEnabled(false);


		addMonstersToLayer();

		CCLayerColor* back = CCLayerColor::create(ccc4(0, 0, 0, 200));
		auto m_pDrawNode = DrawNode::create();
		m_pDrawNode->setAnchorPoint(ccp(0.0, 0.0));
		ccColor4F yellow(1, 1, 0, 1);
		float radiusX = 55;
		float radiusY = 55;
		const int count = 200;
		const float angel = 2.0f * (float)M_PI / count;
		Vec2 circles[count];
		for (int i = 0; i < count; ++i)
		{
			float radian = i * angel;
			circles[i].x = radiusX * cosf(radian);
			circles[i].y = radiusY * sinf(radian);
		}
		m_pDrawNode->drawPolygon(circles, count, yellow, 0, yellow);
		m_pDrawNode->setPosition(ccp(592 * SUP_SCALE_X, 567 * SUP_SCALE_Y));

		m_pBlackBg = ClippingNode::create();
		m_pBlackBg->setContentSize(winSize);
		m_pBlackBg->setAnchorPoint(ccp(0.5, 0.5));
		m_pBlackBg->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
		m_pBlackBg->setInverted(true);
		m_pBlackBg->addChild(back);
		m_pBlackBg->setStencil(m_pDrawNode);
		this->addChild(m_pBlackBg, 3);
		m_pBlackBg->setVisible(false);    //false
		
		schedule(schedule_selector(BabyRoomForm::InitFirstPissAction), 3.0f);

		m_pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		m_pGeceng->setPosition(ccp(m_pGeceng->getPositionX()*SUP_SCALE_X, m_pGeceng->getPositionY()*SUP_SCALE_Y));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		m_pGeceng->setVisible(false);

		auto Panel_touch = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_touch"));
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(BabyRoomForm::onTouchBeginListener, this);
		listener->onTouchMoved = CC_CALLBACK_2(BabyRoomForm::onTouchMoveListener, this);
		listener->onTouchEnded = CC_CALLBACK_2(BabyRoomForm::onTouchEndListener, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Panel_touch);

		EntityMgr::instance()->pPlayer()->setisSleeping(false);
		return true;
	}
	return false;
}

void BabyRoomForm::onBeiziTouchListener(Ref* ref, TouchEventType type)
{
	auto item_type = (EGameItemType)(((Node*)ref)->getTag());
	unschedule(schedule_selector(BabyRoomForm::showCoolAction));

	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		m_beiziLastPos = m_pBeiziImg->getTouchBeganPosition();
		break;
	case TOUCH_EVENT_MOVED:
	{
							  float tmpPos = m_pBeiziImg->getTouchMovePosition().y - m_beiziLastPos.y;
							  float posY = m_pBeiziImg->getPositionY() + tmpPos;
							  if (posY <= 416 && posY >= m_beiziInitPos.y)
							  {
								  if (m_bnight && posY >= tmpPosy)
								  {
									  m_pBeiziImg->stopAllActions();
									  m_pBeiziImg->setPositionY(posY);
									  tmpPosy = posY;
									  if (posY >= m_naizuiPos.y)
									  {
										  hideItemNaiZuiAction();
									  }

									  if (posY >= m_zhiniaokuPos.y)
									  {
										  hideItemZhiNiaoKuAction();
									  }

									  if (posY >= m_wanjuPos.y)
									  {
										  hideItemWanJuAction();
									  }

									  if (posY >= 400)
									  {
										  m_bnight = false;
									  }
								  }
								  else if (!m_bnight && posY <= tmpPosy)
								  {
									  m_pBeiziImg->stopAllActions();
									  m_pBeiziImg->setPositionY(posY);
									  tmpPosy = posY;

									  if (posY <= (m_naizuiPos.y+Img_naizui->getContentSize().height))
									  {
										  showItemNaiZuiAction();
									  }

									  if (posY <= (m_zhiniaokuPos.y + Img_zhiNiuKu->getContentSize().height))
									  {
										  showItemZhiNiaoKuAction();
									  }

									  if (posY <= (m_wanjuPos.y + Img_xiaobear->getContentSize().height/3))
									  {
										  showItemWanJuAction();
									  }
									  if (posY <= 85)
									  {
										  m_bnight = true;
									  }
								  }
							  }
							  else if (posY <= m_beiziInitPos.y)
							  {
								  m_pBeiziImg->stopAllActions();
								  m_pBeiziImg->setPositionY(m_beiziInitPos.y);
							  }
							  m_beiziLastPos = m_pBeiziImg->getTouchMovePosition();

							  break;
	}

	case TOUCH_EVENT_ENDED:
	case TOUCH_EVENT_CANCELED:
	{

						/*		 if (m_pBeiziImg->getPositionY() <= 100 || !m_bCool)
								 {
									 m_pBeiziImg->stopAllActions();
									 m_pBeiziImg->runAction(MoveTo::create(0.3f, m_beiziInitPos));

									 m_bCool = true;
								 }*/
								if (m_pBeiziImg->getPositionY() >= 200)
								 {
									 hideCoolAction(0);
									 m_bCool = false;
								 }
								 // SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GAIBEIZI);
	}
		break;
	}
}


void BabyRoomForm::showCoolAction(float time)
{

	if (!m_bCool)
	{
		return;
	}
	//m_pPlayer->runRoleAnimation(ERoleExpression_Sad);
	if (m_pBeiziImg->getPositionY() <= m_beiziInitPos.y)
	{
		m_pBeiziImg->stopAllActions();
		m_pBeiziImg->runAction(
			RepeatForever::create(
			Sequence::create(
			MoveBy::create(2.0f, ccp(0, 50)),
			MoveBy::create(2.0f, ccp(0, -50)), NULL)));
	}
}


void BabyRoomForm::hideCoolAction(float time)
{
	//m_pPlayer->runRoleAnimation(ERoleExpression_Smile);
	m_bCool = false;
}

void BabyRoomForm::onArrowButtonClicked(Ref *sender, TouchEventType type)
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
			m_pSubMenu->stopAllActions();
			m_pSubMenu->setPosition(m_vecInitToolBar);
			auto moveto = MoveTo::create(0.5f, ccp(winSize.width - m_pSubMenu->getContentSize().width*0.8, m_pSubMenu->getPositionY()));
			m_pSubMenu->runAction(Sequence::create(moveto, CallFunc::create([this](){
				m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_right.png");
				m_isOpen = true;
			}), NULL));
		}
		else
		{
			auto moveto = MoveTo::create(0.5f, m_vecInitToolBar);
			m_pSubMenu->runAction(Sequence::create(moveto, CallFunc::create([this](){
				m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_left.png");
				m_isOpen = false;
			}), NULL));
		}
	}
}

bool BabyRoomForm::onTouchBeginListener(Touch *touch, Event *unusedEvent)
{
	if (m_isOpen)
	{
		auto moveto = MoveTo::create(0.5f, m_vecInitToolBar);
		m_pSubMenu->runAction(Sequence::create(moveto, CallFunc::create([this](){
			m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_left.png");
			m_isOpen = false;
		}), NULL));
	}
	auto pPlayer = EntityMgr::instance()->pPlayer();

	Vec2 touchPos = touch->getStartLocation();

	cocos2d::Rect target_rect_zhijin;
	target_rect_zhijin.origin = m_zhiniaokuPos;
	target_rect_zhijin.size = Img_zhiNiuKu->getContentSize();

	if (target_rect_zhijin.containsPoint(touchPos) && m_pBlackBg->isVisible())
	{

	}

	auto pClockPanel = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pLayout, "Panel_clock"));
	cocos2d::Rect target_rect_Clock;
	target_rect_Clock.origin = m_clockPos;
	target_rect_Clock.size = pClockPanel->getContentSize();
	if (target_rect_Clock.containsPoint(touchPos) && m_pBlackBg->isVisible())
	{
		AfterFinishRecoverJingliTimer();
	}
	return true;
}

void BabyRoomForm::openToolBar()
{
	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	if (!m_isOpen)
	{
		m_pSubMenu->stopAllActions();
		m_pSubMenu->setPosition(m_vecInitToolBar);
		auto moveto = MoveTo::create(0.5f, ccp(winSize.width - m_pSubMenu->getContentSize().width*0.8, m_pSubMenu->getPositionY()));
		m_pSubMenu->runAction(Sequence::create(moveto, CallFunc::create([this](){
			m_pArrow->loadTexture("res/UI/common/prop/ui_common_prop_catspaw_arrow_right.png");
			m_isOpen = true;
		}), NULL));
	}
}

void BabyRoomForm::onTouchMoveListener(Touch *touch, Event *unusedEvent)
{
	
}

void BabyRoomForm::onTouchEndListener(Touch *touch, Event *unusedEvent)
{
	
}

void BabyRoomForm::hideItemNaiZuiAction()
{
	CCActionInterval*  action1 = CCFadeOut::create(1.0f);
	Img_naizui->runAction(action1);
}

void BabyRoomForm::showItemNaiZuiAction()
{
	CCActionInterval*  action2 = CCFadeIn::create(1.0f);
	Img_naizui->runAction(action2);
}

void BabyRoomForm::hideItemZhiNiaoKuAction()
{
	CCActionInterval*  action1 = CCFadeOut::create(1.0f);
	Img_zhiNiuKu->runAction(action1);
}

void BabyRoomForm::showItemZhiNiaoKuAction()
{
	CCActionInterval*  action2 = CCFadeIn::create(1.0f);
	Img_zhiNiuKu->runAction(action2);
}

void BabyRoomForm::hideItemWanJuAction()
{
	CCActionInterval*  action1 = CCFadeOut::create(1.0f);
	Img_xiaobear->runAction(action1);
}

void BabyRoomForm::showItemWanJuAction()
{
	CCActionInterval*  action2 = CCFadeIn::create(1.0f);
	Img_xiaobear->runAction(action2);
}

void BabyRoomForm::addMonstersToLayer()
{
	MonsterList::MonsterType* pMonsterType = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EGameRoom_Baby);
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


void BabyRoomForm::onWindowActionClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		playWindowAction();
	}
}


void BabyRoomForm::onClockActionClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		playClockAction();
		auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
		if (pForm != NULL)
		{
			//pForm->AfterFinishRecoverJingliTimer();
		}
	}
}

void BabyRoomForm::playWindowAction()
{
	//SoundManage::instance()->stopSound(RES_SOUND_ID_SOUND_ZOUZHEN);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_MAOLING);
	if (CurWindowState)
	{
		m_pBaiyeTimeLine->play("animation1", false);
		CurWindowState = false;
	}
	else
	{
		m_pBaiyeTimeLine->play("animation0", false);
		CurWindowState = true;
	}
	
}

void BabyRoomForm::playWindowNormalAction()
{
	m_pBaiyeTimeLine->play("animation2", true);
}



void BabyRoomForm::playClockAction()
{
	//SoundManage::instance()->stopSound(RES_SOUND_ID_SOUND_ZOUZHEN);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_MAOLING);
	m_pClockTimeLine->play("animation1", false);
}

void BabyRoomForm::playClockNormalAction()
{
	//SoundManage::instance()->stopSound(RES_SOUND_ID_SOUND_ZOUZHEN);
	m_pClockTimeLine->play("animation0", true);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ZOUZHEN, true);
}

bool BabyRoomForm::getBlackBGVisual()
{
	return m_pBlackBg->isVisible();
}

void BabyRoomForm::onLightBtnClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_KAIDENG);
	
		if (getBlackBGVisual() == false)
		{
			m_pBlackBg->setVisible(true);
			lightguang->setVisible(false);
			setSleepAction(true);
			this->unschedule(CC_SCHEDULE_SELECTOR(BabyRoomForm::InitFirstPissAction));
		}
		else
		{
			m_pBlackBg->setVisible(false);
			lightguang->setVisible(true);
			setSleepAction(false);
			this->schedule(schedule_selector(BabyRoomForm::InitFirstPissAction), 3.0f);
		}

		Player* pPlayer = EntityMgr::instance()->pPlayer();
		if (!pPlayer->getIsShowNaoling())
		{
			auto pForm = UIFactory::instance()->showNaolingForm();
			if (NULL != pForm)
			{
				BabyCare::instance()->getCurrScene()->addChild(pForm, 50);
			}
			pPlayer->setIsShowNaoling(true);
		}
	}
}

void BabyRoomForm::setSleepAction(bool isVisual)
{
	m_pBlackBg->setVisible(isVisual);
	auto m_pPlayer = EntityMgr::instance()->pPlayer();

	if (m_isSleep&& !m_bnight)
	{
		setGeCengVisual(true);
		playClockNormalAction();
		auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
		if (pForm != NULL)
		{
			//pForm->createNextAction_ex(701);
			auto particle1 = ParticleSystemQuad::create("res/Particles/effect_yinfu01.plist");
			particle1->setPosition(ccp(m_winSize.width, 0));
			particle1->setScale(1.0f);

			if (particle1 != NULL)
			{
				//particle1->setPositionType(ParticleSystem::PositionType::FREE);
			}

			auto particle2 = ParticleSystemQuad::create("res/Particles/effect_yinfu02.plist");
			particle2->setPosition(ccp(m_winSize.width, 0));
			particle2->setScale(1.0f);
			if (particle2 != NULL)
			{
				//particle2->setPositionType(ParticleSystem::PositionType::FREE);
			}

			auto particle3 = ParticleSystemQuad::create("res/Particles/effect_yinfu03.plist");
			particle3->setPosition(ccp(m_winSize.width, 0));
			particle3->setScale(1.0f);

			if (particle3 != NULL)
			{
				//particle3->setPositionType(ParticleSystem::PositionType::FREE);
			}
			this->addChild(particle3, 20);

			auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
			if (pForm != NULL)
			{
				pForm->playRoleAnimation(EBabyExpression_ShuiJiao, true);
				m_pPlayer->setisRoleAniLoop(true);
			}
		}
		this->runAction(Sequence::create(DelayTime::create(0.5f), __CCCallFuncO::create(this, callfuncO_selector(BabyRoomForm::startRecoverJingliTimer), NULL), NULL));

		}
	else
	{
		if (m_pGeceng->isVisible())
		{
			setGeCengVisual(false);
		}
	}
}

void BabyRoomForm::startRecoverJingliTimer(Ref* object)
{
	this->scheduleUpdate();
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setisSleeping(true);

	auto pGameScene = (GameScene*)this->getParent();
	//pGameScene->setMenuControlVisual(false);
}

void BabyRoomForm::stopRecoverJingliTimer()
{
	auto m_pPlayer = EntityMgr::instance()->pPlayer();

	m_isSleep = false;
	this->unscheduleUpdate();
	m_fCurrJingliTimer = 0;
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setisSleeping(false);

	//auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
	//if (pForm != NULL)
	//{
	//	pForm->playRoleAnimation(EBabyExpression_Daiji, true);
	//}
	auto pGameScene = (GameScene*)this->getParent();
	//pGameScene->setMenuControlVisual(true);
}


void BabyRoomForm::update(float delta)
{
	m_fCurrJingliTimer += delta;
	auto pPlayer = EntityMgr::instance()->pPlayer();
	if (m_fCurrJingliTimer >= 20)
	{
		AfterFinishRecoverJingliTimer();
	}
}

void BabyRoomForm::AfterFinishRecoverJingliTimer()
{
	if (m_isSleep)
	{
		auto m_pPlayer = EntityMgr::instance()->pPlayer();
		stopRecoverJingliTimer();
		playClockAction();
		m_pBlackBg->setVisible(false);
		m_isSleep = false;
		auto moveto = MoveTo::create(3.0f, m_beiziInitPos);
		m_pBeiziImg->runAction(moveto);
		showBedItemVisual();
		auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
		if (pForm != NULL)
		{
			pForm->playRoleAnimation(EBabyExpression_ShuiXing,false);
			EntityMgr::instance()->pPlayer()->setisRoleAniLoop(false);
		}
	}
}

void BabyRoomForm::InitFirstPissAction(float dt)
{
	this->unschedule(CC_SCHEDULE_SELECTOR(BabyRoomForm::InitFirstPissAction));
	this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([&](){
		auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
		if (pForm != NULL)
		{
			pForm->initZhiniukuAction();
			pForm->playRoleAnimation(EBabyExpression_Ku,true);
			EntityMgr::instance()->pPlayer()->setisRoleAniLoop(true);
			this->scheduleOnce(schedule_selector(BabyRoomForm::RefreshItemFaGuang), 3.0f);
		}
	}), NULL));
}

void BabyRoomForm::onPissClean(Ref* object)
{
	auto pForm = dynamic_cast<BabyControl*>(UIManager::instance()->findForm(IDC_Player));
	if (pForm != NULL)
	{
		pForm->refreshZhiniukuAction();
	}
	m_isSleep = true;
	schedule(schedule_selector(BabyRoomForm::showCoolAction), 5.0f);
}

void BabyRoomForm::RefreshItemFaGuang(float dt)
{
	if (pGameFaguangImg->isVisible() == false)
	{
		pGameFaguangImg->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f), NULL)));
	}
	else
	{
		pGameFaguangImg->stopAllActions();
		pGameFaguangImg->setVisible(false);
	}
}

void BabyRoomForm::setGeCengVisual(bool isValue)
{
	m_pGeceng->setVisible(isValue);
}

void BabyRoomForm::showBedItemVisual()
{
	Img_zhiNiuKu->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([this]{showItemZhiNiaoKuAction(); }), NULL));
	Img_xiaobear->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([this]{showItemWanJuAction(); }), NULL));
	Img_naizui->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create([this]{showItemNaiZuiAction(); }), NULL));
}
