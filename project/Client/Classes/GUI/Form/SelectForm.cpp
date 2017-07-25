#include "SelectForm.h"
#include "BabyCare.h"
#include "define.h"
#include "GameType.h"
#include "GUI/UIFactory.h"
#include "../UIManager.h"
#include "SDK/SupSDK.h"
#include "GUI/Form/LoadingForm.h"
#include "GUI/UIFactory.h"
#include "UnlockTipForm.h"
#include "../Form/SigninForm.h"
#include "../UIMask.h"
#include "../Form/UIChooseColor.h"
#include "SaveManager/SaveManage.h"

SelectForm::SelectForm() :
Form(IDC_Select)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SelectForm::unLocunlockRoom), ACTION_HOUSE, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SelectForm::onshowchoose), SHOW_CHOOSE, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SelectForm::updaterole), UPDATE_Ren, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SelectForm::SelectEnableHouse), SELCT_HOUSE_ENABLED, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SelectForm::onshowchoose), SHOW_CHOOSE, NULL);

}

SelectForm::~SelectForm()
{
	NotificationCenter::getInstance()->removeObserver(this, ACTION_HOUSE);
	NotificationCenter::getInstance()->removeObserver(this, SHOW_CHOOSE);
	NotificationCenter::getInstance()->removeObserver(this, UPDATE_Ren);
	NotificationCenter::getInstance()->removeObserver(this, SELCT_HOUSE_ENABLED);
	NotificationCenter::getInstance()->removeObserver(this, SHOW_CHOOSE);

}


bool SelectForm::init()
{
	if (Form::init())
	{
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		m_pSelect = CSLoader::createNode("SelectForm.csb");
		this->addChild(m_pSelect,1);

		auto pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->setimNotification(0);
		pPlayer->setjisuanis(false);
		/*int currRole = SaveManage::instance()->getIntSave(SAVE_ID_INT_CUR_ROLE);*/
		int currLevel = SaveManage::instance()->getIntSave(SAVE_ID_INT_CUR_ROOM);
		pPlayer->setCurrRoomType((EGameLevel)currLevel);

		auto Panel_Room = dynamic_cast<Layout*>(m_pSelect->getChildByName("Panel_Room"));

	
	    pRoom_woshi = dynamic_cast<ImageView*>(Panel_Room->getChildByName("Img_woshi"));
		pRoom_woshi->setPosition(ccp(pRoom_woshi->getPositionX()*SUP_SCALE_X, pRoom_woshi->getPositionY()*SUP_SCALE_Y));
		pRoom_woshi->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		pRoom_toy = dynamic_cast<ImageView*>(Panel_Room->getChildByName("Img_wanju"));
		pRoom_toy->setPosition(ccp(pRoom_toy->getPositionX()*SUP_SCALE_X, pRoom_toy->getPositionY()*SUP_SCALE_Y));
		pRoom_toy->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		pRoom_toy->addTouchEventListener(this, toucheventselector(SelectForm::onWanjuButtonClicked));

		pRoom_canting = dynamic_cast<ImageView*>(Panel_Room->getChildByName("Img_canting"));
		pRoom_canting->setPosition(ccp(pRoom_canting->getPositionX()*SUP_SCALE_X, pRoom_canting->getPositionY()*SUP_SCALE_Y));
		pRoom_canting->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		pRoom_canting->addTouchEventListener(this, toucheventselector(SelectForm::onCantingButtonClicked));

		pRoom_muyu = dynamic_cast<ImageView*>(Panel_Room->getChildByName("Img_muyu"));
		pRoom_muyu->setPosition(ccp(pRoom_muyu->getPositionX()*SUP_SCALE_X, pRoom_muyu->getPositionY()*SUP_SCALE_Y));
		pRoom_muyu->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		pRoom_muyu->addTouchEventListener(this, toucheventselector(SelectForm::onMuyuButtonClicked));

		pRoom_dress = dynamic_cast<ImageView*>(Panel_Room->getChildByName("Img_dress"));
		pRoom_dress->setPosition(ccp(pRoom_dress->getPositionX()*SUP_SCALE_X, pRoom_dress->getPositionY()*SUP_SCALE_Y));
		pRoom_dress->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		pRoom_dress->addTouchEventListener(this, toucheventselector(SelectForm::onDressButtonClicked));

		for (int i = 0; i < 5; i++)
		{
			std::string name = "im_" + sup::SupString::int2String(i);
			m_pLevelBtn[i] = dynamic_cast<Button*>(Panel_Room->getChildByName(name));
			m_pLevelBtn[i]->addTouchEventListener(this, toucheventselector(SelectForm::onSelectButtonClicked));
			m_pLevelBtn[i]->setTag(i);
			m_pLevelBtn[i]->setZOrder(1);
		}

		m_pImg = ImageView::create("res/ui/role/touxiang_nanhai_01.png", TextureResType::LOCAL);
		Panel_Room->addChild(m_pImg, 2);
		m_pImg->setTouchEnabled(true);
		m_pImg->addTouchEventListener(this, toucheventselector(SelectForm::onRoleSelectClick));
		auto moveAct = MoveBy::create(1.0f, ccp(0, 20));
		m_pImg->runAction(RepeatForever::create(Sequence::create(moveAct, moveAct->reverse(), NULL)));

		auto particle = ParticleSystemQuad::create("Particles/effect_xuanzeyindao.plist");
		Panel_Room->addChild(particle, 0);

		auto particle1 = ParticleSystemQuad::create("Particles/effect_xuanzeyindao_add.plist");
		Panel_Room->addChild(particle1, 0);

		m_pImg->setPosition((m_pLevelBtn[currLevel]->getPosition() + ccp(0, 80)));
		log("x=%f,y=%f", m_pImg->getPositionX(), m_pImg->getPositionY());

		EntityMgr::instance()->pPlayer()->setCurrRoleId(EGameRole(currLevel));
		particle->setPosition(m_pLevelBtn[currLevel]->getPosition());
		particle1->setPosition(m_pLevelBtn[currLevel]->getPosition());


		onfang();
		UserDefault::getInstance()->setIntegerForKey(STATUE_TOUCH, 1);
		UserDefault::getInstance()->flush();

		if (pPlayer->getStaris() == true)
		{
			Player* pPlayer = EntityMgr::instance()->pPlayer();
			int m_iDays = pPlayer->readSignInDays();

			for (int i = 0; i < 7; i++)
			{
				if (i < m_iDays)
				{
					pPlayer->setimsign(false);
				}
				if (i == m_iDays)
				{
					const time_t t = time(NULL);
					const time_t t1 = pPlayer->readSigninDate();
					if (!SupLayout::isSameDay(t, t1))
					{
						pPlayer->setimsign(true);
						//spt->setVisible(true);
					}
				}
			}
			if (pPlayer->getimsign() == true)
			{
				SigninForm* pForm = SigninForm::createInst();
				this->addChild(pForm, 20);
			}
			else
			{
				UIChooseColor* pForm = UIChooseColor::createInst();
				this->addChild(pForm, 20);
			}
		}


		if (UserDefault::getInstance()->getBoolForKey(IsShowBAOXIANG.c_str()) == true && pPlayer->getStaris() == false)
		{
			if (UserDefault::getInstance()->getBoolForKey(LIANGXU_DIAN) == true)
			{
				UserDefault::getInstance()->setBoolForKey(IsFANHUI.c_str(), true);
				UserDefault::getInstance()->flush();
				unLockRoomFunc();
				UserDefault::getInstance()->setBoolForKey(LIANGXU_DIAN, false);
				UserDefault::getInstance()->flush();
			}
			else
			{
				unLockRoomFunc();
			}
		}
		else
		{
			unLockRoomFunc();
		}
		return true;
	}
	return false;
}


void SelectForm::onWanjuButtonClicked(Ref *sender, TouchEventType type)
{
	if (!UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str(), false))
	{
		openUnlockTip(0);
		return;
	}
	/*if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECTBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}*/
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((ImageView*)sender)->setEnabled(false);
		EntityMgr::instance()->pPlayer()->setCurrRoomType(ELevel_WanjuRoom);
		this->scheduleOnce(schedule_selector(SelectForm::turnToGameScene), 0.5f);
	}
}

void SelectForm::onCantingButtonClicked(Ref *sender, TouchEventType type)
{
	if (!UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str(), false))
	{
		openUnlockTip(1);
		return;
	}
	/*if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECTBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}*/
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((ImageView*)sender)->setEnabled(false);
		EntityMgr::instance()->pPlayer()->setCurrRoomType(ELevel_DiningRoom);
		this->scheduleOnce(schedule_selector(SelectForm::turnToGameScene), 0.5f);
	}
}

void SelectForm::onMuyuButtonClicked(Ref *sender, TouchEventType type)
{
	if (!UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str(), false))
	{
		openUnlockTip(2);
		return;
	}
	/*if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECTBTN);
		sup::SupActions::ButtonAction((Node*)sender);
		}*/
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((ImageView*)sender)->setEnabled(false);
		EntityMgr::instance()->pPlayer()->setCurrRoomType(ELevel_MuyuRoom);
		this->scheduleOnce(schedule_selector(SelectForm::turnToGameScene), 0.5f);
	}
}

void SelectForm::onDressButtonClicked(Ref *sender, TouchEventType type)
{
	if (!UserDefault::getInstance()->getBoolForKey(strDressLock.c_str(), false))
	{
		openUnlockTip(3);
		return;
	}
	/*if (TOUCH_EVENT_BEGAN == type)
	{
	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECTBTN);
	sup::SupActions::ButtonAction((Node*)sender);
	}*/
	else if (TOUCH_EVENT_ENDED == type)
	{
	((Node*)sender)->setScale(1.0f);
	((ImageView*)sender)->setEnabled(false);
	EntityMgr::instance()->pPlayer()->setCurrRoomType(ELevel_DressRoom);
	this->scheduleOnce(schedule_selector(SelectForm::turnToGameScene), 0.5f);
	}
}

void SelectForm::turnToGameScene(float dt)
{
	setKeyboardEnabled(false);
	auto pForm = UIFactory::instance()->showLoadingForm();
	if (NULL != pForm)
	{
		BabyCare::instance()->getCurrScene()->addChild(pForm, 5);
	}
}

void SelectForm::openUnlockTip(int iType)
{
	auto *pForm = UIFactory::instance()->showUnlockTipForm(iType);
	if (NULL != pForm)
	{
		this->addChild(pForm, 20);
	}
}

void SelectForm::onfang(){
	auto bUnlockWanju = UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str(), false);
	auto bUnlockCanting = UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str(), false);
	auto bUnlockMuyu = UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str(), false);
	auto bUnlockDress = UserDefault::getInstance()->getBoolForKey(strDressLock.c_str(), false);
	unlock = 0;
	if (bUnlockWanju)
	{
		unlock = 1;
	}

	if (bUnlockCanting)
	{
		unlock = 2;
	}
	if (bUnlockMuyu)
	{
		unlock = 3;
	}
	if (bUnlockDress)
	{
		unlock = 4;
	}
}

void SelectForm::unLockRoomFunc()
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	auto bUnlockWanju = UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str(), false);
	auto bUnlockCanting = UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str(), false);
	auto bUnlockMuyu = UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str(), false);
	auto bUnlockDress = UserDefault::getInstance()->getBoolForKey(strDressLock.c_str(), false);
	if (bUnlockWanju && bUnlockCanting && bUnlockMuyu && bUnlockDress)
	{
		//AssignmentSystem();
	}
	else
	{
		if (!bUnlockWanju)
		{
			pRoom_toy->loadTexture("res/ui/select/wanju_unclock.png");
			SkeletonAnimation* im = (SkeletonAnimation*)pRoom_toy->getChildByTag(10);
			if (im == nullptr)
			{
				//未解锁时候房间的状态
			}
			if (pPlayer->getisUnlockToy() && pPlayer->getStaris() == false)
			{
				unlock = 1;
				this->scheduleOnce(schedule_selector(SelectForm::unLockWanjuRoom), 0.5f);
			}
		}
		else
		{
			HomejiesuoAction();
		}

		if (!bUnlockCanting)
		{
			pRoom_dress->loadTexture("res/ui/select/dress_unlock.png");
			SkeletonAnimation* im = (SkeletonAnimation*)pRoom_dress->getChildByTag(10);
			if (im == nullptr)
			{

			}
			if (pPlayer->getisUnlockCanting() && pPlayer->getStaris() == false)
			{
				unlock = 4;
				this->scheduleOnce(schedule_selector(SelectForm::unLockCantingRoom), 0.5f);
			}
		}

		if (!bUnlockMuyu)
		{
			pRoom_canting->loadTexture("res/ui/select/canting_unlock.png");
			SkeletonAnimation* im = (SkeletonAnimation*)pRoom_canting->getChildByTag(10);
			if (im == nullptr)
			{
			}
			if (pPlayer->getisUnlockMuyu() && pPlayer->getStaris() == false)
			{
				unlock = 2;
				this->scheduleOnce(schedule_selector(SelectForm::unLockMuyuRoom), 0.5f);
			}
		}

		if (!bUnlockDress)
		{
			pRoom_muyu->loadTexture("res/ui/select/yushi_unlock.png");
			SkeletonAnimation* im = (SkeletonAnimation*)pRoom_muyu->getChildByTag(10);
			if (im == nullptr)
			{
			}
			if (pPlayer->getisUnlockDress() && pPlayer->getStaris() == false)
			{
				unlock = 3;
				this->scheduleOnce(schedule_selector(SelectForm::unLockDressRoom), 0.5f);
			}
			else
			{
				if (UserDefault::getInstance()->getIntegerForKey("count_ar") == 1 || pPlayer->getStaris() == true)
				{
					return;
				}
				//showAchievement(0);
			}
		}
		else
		{
			if (UserDefault::getInstance()->getIntegerForKey("count_ar") == 1 
				|| UserDefault::getInstance()->getBoolForKey(strDressAction.c_str()) == false)
			{
				return;
			}
			//showAchievement(0);
		}
		this->scheduleOnce(schedule_selector(SelectForm::updateAppear), 0.5f);
	}
}


void SelectForm::unLockWanjuRoom(float dt)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pRoom_toy->loadTexture("res/ui/select/wanju.png");
	auto particle1 = ParticleSystemQuad::create("res/ui/house/effect_fangjianjiesuo.plist");
	particle1->setPosition(ccp(pRoom_toy->getContentSize().width*0.5, pRoom_toy->getContentSize().height*0.5));
	pRoom_toy->addChild(particle1, 10);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ROOMJIESUO);
	pPlayer->saveRoomLockStatus();
}

void SelectForm::unLockDressRoom(float dt)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pRoom_dress->loadTexture("res/ui/select/dress.png");
	auto particle1 = ParticleSystemQuad::create("res/ui/house/effect_fangjianjiesuo.plist");
	particle1->setPosition(ccp(pRoom_dress->getContentSize().width*0.5, pRoom_dress->getContentSize().height*0.5));
	pRoom_dress->addChild(particle1, 10);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ROOMJIESUO);
	pPlayer->saveRoomLockStatus();
}

void SelectForm::unLockCantingRoom(float dt)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pRoom_canting->loadTexture("res/ui/select/canting.png");
	auto particle1 = ParticleSystemQuad::create("res/ui/house/effect_fangjianjiesuo.plist");
	particle1->setPosition(ccp(pRoom_canting->getContentSize().width*0.5, pRoom_canting->getContentSize().height*0.5));
	pRoom_canting->addChild(particle1, 10);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ROOMJIESUO);
	pPlayer->saveRoomLockStatus();
}

void SelectForm::unLockMuyuRoom(float dt)
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	pRoom_muyu->loadTexture("res/ui/select/yushi.png");
	auto particle1 = ParticleSystemQuad::create("res/ui/house/effect_fangjianjiesuo.plist");
	particle1->setPosition(ccp(pRoom_muyu->getContentSize().width*0.5, pRoom_muyu->getContentSize().height*0.5));
	pRoom_muyu->addChild(particle1, 10);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_ROOMJIESUO);
	pPlayer->saveRoomLockStatus();
	//AssignmentSystem();
}

void SelectForm::HomejiesuoAction(){


	if (UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str()) == true)
	{
		if (UserDefault::getInstance()->getBoolForKey(strWanjuAction.c_str()) == false)
		{
			pRoom_toy->loadTexture("res/ui/select/wanju_unclock.png");
			this->scheduleOnce(schedule_selector(SelectForm::unLockWanjuRoom), 0.5f);
			UserDefault::getInstance()->setBoolForKey(strWanjuLock.c_str(), true);
			UserDefault::getInstance()->flush();
		}
	}

	if (UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str()) == true)
	{
		if (UserDefault::getInstance()->getBoolForKey(strCantingAction.c_str()) == false)
		{
			pRoom_canting->loadTexture("res/ui/select/canting_unlock.png");
			this->scheduleOnce(schedule_selector(SelectForm::unLockCantingRoom), 0.5f);
			UserDefault::getInstance()->setBoolForKey(strCantingAction.c_str(), true);
			UserDefault::getInstance()->flush();
		}
	}
	if (UserDefault::getInstance()->getBoolForKey(strDressLock.c_str()) == true)
	{
		if (UserDefault::getInstance()->getBoolForKey(strDressAction.c_str()) == false)
		{
			pRoom_dress->loadTexture("res/ui/select/dress_unlock.png");
			this->scheduleOnce(schedule_selector(SelectForm::unLockDressRoom), 0.5f);
			UserDefault::getInstance()->setBoolForKey(strDressAction.c_str(), true);
			UserDefault::getInstance()->flush();
		}
	}
	if (UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str()) == true)
	{
		if (UserDefault::getInstance()->getBoolForKey(strMuyuAction.c_str()) == false)
		{
			pRoom_muyu->loadTexture("res/ui/select/yushi_unlock.png");
			this->scheduleOnce(schedule_selector(SelectForm::unLockDressRoom), 0.5f);
			UserDefault::getInstance()->setBoolForKey(strMuyuAction.c_str(), true);
			UserDefault::getInstance()->flush();
		}
	}
}

void SelectForm::updateAppear(float dt)
{
	KaignmentSystem();
}

void SelectForm::unLocunlockRoom(Ref* re)
{
	auto bUnlockWanju = UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str(), false);
	auto bUnlockCanting = UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str(), false);
	auto bUnlockMuyu = UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str(), false);
	auto bUnlockDress = UserDefault::getInstance()->getBoolForKey(strDressLock.c_str(), false);
	if (bUnlockWanju && bUnlockCanting && bUnlockMuyu && bUnlockDress)
	{
		return;
	}
	unLockRoomFunc();
}

void SelectForm::onshowchoose(Ref* object)
{
	UIChooseColor* pForm = UIChooseColor::createInst();
	this->addChild(pForm, 20);
}

void SelectForm::KaignmentSystem()
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	auto bUnlockWanju = UserDefault::getInstance()->getBoolForKey(strWanjuLock.c_str(), false);
	auto bUnlockCanting = UserDefault::getInstance()->getBoolForKey(strCantingLock.c_str(), false);
	auto bUnlockDress = UserDefault::getInstance()->getBoolForKey(strDressLock.c_str(), false);
	auto bUnlockMuyu = UserDefault::getInstance()->getBoolForKey(strMuyuLock.c_str(), false);

	if (bUnlockWanju && bUnlockCanting && bUnlockDress && bUnlockMuyu)
	{
		return;
	}
	/*if (unlock == 0)
	{
		if (unlock == ELevel_BabyRoom)
		{
			pSelect->setPosition(m_vec[ELevel_BabyRoom]->getPosition());
		}
	}
	if (unlock == 1)
	{
		if (unlock == ELevel_WanjuRoom)
		{
			pSelect->setPosition(m_vec[ELevel_WanjuRoom]->getPosition());
		}
	}
	if (unlock == 2)
	{
		if (unlock == ELevel_DiningRoom)
		{
			pSelect->setPosition(m_vec[ELevel_DiningRoom]->getPosition());
		}
	}
	if (unlock == 3)
	{
		if (unlock == ELevel_MuyuRoom)
		{
			pSelect->setPosition(m_vec[ELevel_MuyuRoom]->getPosition());
		}
	}
	if (unlock == 4)
	{
		if (unlock == ELvel_HuanZhuangRoom)
		{
			pSelect->setPosition(m_vec[ELvel_HuanZhuangRoom]->getPosition());
		}
	}
	pSelect->setVisible(true);*/
}

void SelectForm::onSelectButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECTBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		auto node = (Node*)sender;
		int tag = node->getTag();
		SaveManage::instance()->setIntSave(SAVE_ID_INT_CUR_ROOM,tag);
		EntityMgr::instance()->pPlayer()->setCurrRoomType((EGameLevel)tag);
		((ImageView*)sender)->setEnabled(false);
		m_pImg->stopAllActions();
		auto JumpAct = JumpTo::create(0.4f, m_pLevelBtn[tag]->getPosition() + ccp(0, 80), 100, 1);
		auto scaleAct1 = ScaleTo::create(0.1f, 1.2f, 0.8f);
		auto scaleAct2 = ScaleTo::create(0.2f, 0.8f, 1.2f);
		auto scaleAct3 = ScaleTo::create(0.1f, 1.0f, 1.0f);
		auto seq = Sequence::create(scaleAct1, scaleAct2, scaleAct3, NULL);
		auto sqa = Spawn::create(JumpAct, seq, NULL);

		m_pImg->runAction(Sequence::create(sqa, CallFunc::create(this, callfunc_selector(SelectForm::onRoleBtnCallback)), NULL));
		NotificationCenter::getInstance()->postNotification(SELCT_HOUSE_ENABLED, (Ref*)(intptr_t)tag);
	}
}

void SelectForm::updaterole(Ref* ref)
{
	EGameRole curRole = EntityMgr::instance()->pPlayer()->getCurrRoleId();
	string name;
	if (curRole >= 3)
	{
		name = String::createWithFormat("res/ui/role/touxiang_nvhai_0%d.png", curRole - 2)->getCString();
	}
	else
	{
		 name = String::createWithFormat("res/ui/role/touxiang_nanhai_0%d.png", curRole + 1)->getCString();
	}
	btn_select->loadTextures(name.c_str(), name.c_str(), name.c_str(), TextureResType::LOCAL);
}

void SelectForm::SelectEnableHouse(Ref* ref)
{
	int curRoom = (int)ref;
}

void SelectForm::onRoleSelectClick(Ref *sender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_SELECT_ROLE);
		int tag = EntityMgr::instance()->pPlayer()->getCurrRoomType();

	    m_pImg->stopAllActions();
		m_pImg->setTouchEnabled(false);
		auto JumpAct = JumpTo::create(0.4f, m_pLevelBtn[tag]->getPosition() + ccp(0, 80), 100, 1);
		auto scaleAct1 = ScaleTo::create(0.1f, 1.2f, 0.8f);
		auto scaleAct2 = ScaleTo::create(0.2f, 0.8f, 1.2f);
		auto scaleAct3 = ScaleTo::create(0.1f, 1.0f, 1.0f);
		auto seq = Sequence::create(scaleAct1, scaleAct2, scaleAct3, NULL);
		auto sqa = Spawn::create(JumpAct, seq, NULL);

		m_pImg->runAction(Sequence::create(sqa, CallFunc::create(this, callfunc_selector(SelectForm::onRoleBtnCallback)), NULL));
	}
}

void SelectForm::onRoleBtnCallback()
{
	setKeyboardEnabled(false);
	auto pForm = UIFactory::instance()->showLoadingForm();
	if (NULL != pForm)
	{
		BabyCare::instance()->getCurrScene()->addChild(pForm, 5);
	}
}
