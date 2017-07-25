
/*
** declare SettingForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "SettingForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "GUI/UIFactory.h"
#include "MessageBox.h"
#include "BabyCare.h"



SettingForm::SettingForm() :
Form(IDC_Setting)
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SettingForm::onjinCallback), FACEBOOK_jib, NULL);

}

SettingForm::~SettingForm()
{
	NotificationCenter::getInstance()->removeObserver(this, FACEBOOK_jib);

}

bool SettingForm::init()
{
	if (Form::init())
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("settingbox.csb");
		this->addChild(m_pLayout);	

		m_pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setVisible(true);
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		auto pCloseImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_close"));
		pCloseImg->addTouchEventListener(this, toucheventselector(SettingForm::onCloseButtonClicked));

		m_pMusicOnBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_music_on"));
		m_pMusicOnBtn->addTouchEventListener(this, toucheventselector(SettingForm::onMusicButtonClicked));
		m_pMusicOnBtn->setTouchEnabled(true);

		m_pLoadingBarImg1 = dynamic_cast<LoadingBar*>(m_pMusicOnBtn->getChildByName("LoadingBar_1"));
		m_pMusic_on = dynamic_cast<ImageView*>(m_pMusicOnBtn->getChildByName("Music_on"));
		m_pMusic_off = dynamic_cast<ImageView*>(m_pMusicOnBtn->getChildByName("Music_off"));

		if (SoundManage::instance()->isMusicOn() == true)
		{
			m_pLoadingBarImg1->setPercent(100.0f);
			m_pMusic_on->setVisible(true);
			m_pMusic_off->setVisible(false);
		}
		else
		{
			m_pLoadingBarImg1->setPercent(0.0f);
			m_pMusic_on->setVisible(false);
			m_pMusic_off->setVisible(true);
		}

		m_pSoundOnBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_sound_on"));
		m_pSoundOnBtn->addTouchEventListener(this, toucheventselector(SettingForm::onSoundButtonClicked));
		m_pSoundOnBtn->setTouchEnabled(true);

		m_pLoadingBarImg2 = dynamic_cast<LoadingBar*>(m_pMusicOnBtn->getChildByName("LoadingBar_1"));
		m_pSound_on = dynamic_cast<ImageView*>(m_pMusicOnBtn->getChildByName("Sound_on"));
		m_pSound_off = dynamic_cast<ImageView*>(m_pMusicOnBtn->getChildByName("Sound_off"));

		if (SoundManage::instance()->isSoundOn() == true)
		{
			m_pLoadingBarImg2->setPercent(100.0f);
			m_pSound_on->setVisible(true);
			m_pSound_off->setVisible(false);
		}
		else
		{
			m_pLoadingBarImg2->setPercent(0.0f);
			m_pSound_on->setVisible(false);
			m_pSound_off->setVisible(true);
		}

		auto pForparents = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_forparents"));
		pForparents->addTouchEventListener(this, toucheventselector(SettingForm::onParentsButtonClicked));

		auto pAboutusBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_share"));
		pAboutusBtn->addTouchEventListener(this, toucheventselector(SettingForm::onSharButtonClicked));

		auto pRateBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_rate"));
		pRateBtn->addTouchEventListener(this, toucheventselector(SettingForm::onRateButtonClicked));

		auto pResetBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_face"));
		pResetBtn->addTouchEventListener(this, toucheventselector(SettingForm::onFacebookButtonClicked));

		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);

	//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);
		return true;
	}

	return false;
}
void SettingForm::onjinCallback(Ref* object){
	auto pResetBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_face"));
	pResetBtn->addTouchEventListener(this, toucheventselector(SettingForm::onFacebookButtonClicked));
}

void SettingForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		((ImageView*)sender)->setTouchEnabled(false);

	//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);
		m_pBkImage->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(SettingForm::onCloseButtonCallback))));
	}
}

void SettingForm::onCloseButtonCallback()
{
	this->removeFromParent();
}

void SettingForm::onMusicButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//((Node*)sender)->setScale(1.0f);
		if (SoundManage::instance()->isMusicOn() == true)
		{
			m_pLoadingBarImg1->setPercent(100.0f);
			m_pMusic_on->setVisible(true);
			m_pMusic_off->setVisible(false);
			SoundManage::instance()->setMusicOn(false);
		}
		else
		{
			m_pLoadingBarImg1->setPercent(0.0f);
			m_pMusic_on->setVisible(false);
			m_pMusic_off->setVisible(true);
			SoundManage::instance()->setMusicOn(true);
		}
	}
}

//void SettingForm::onHomeButtonClicked(Ref *sender, TouchEventType type)
//{
//	if (TOUCH_EVENT_BEGAN == type)
//	{
//		sup::SupActions::ButtonAction((Node*)sender);
//	}
//	else if (TOUCH_EVENT_ENDED == type)
//	{
//		((Node*)sender)->setScale(1.0f);
//		showMessageBoxID("Item2", MBCall(SettingForm::onHomeBtnCallBack));
//
//	}
//}
//
//void SettingForm::onHomeBtnCallBack(MBCLICK_TYPE type, void* data)
//{
//	if (MBCLICK_YES == type)
//	{
//		BabyCare::instance()->onStatusChanged(EScene_Home);
//	}
//}


void SettingForm::onSoundButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//((Node*)sender)->setScale(1.0f);
		if (SoundManage::instance()->isSoundOn() == true)
		{
			m_pLoadingBarImg2->setPercent(100.0f);
			m_pSound_on->setVisible(true);
			m_pSound_off->setVisible(false);
			SoundManage::instance()->setSoundOn(false);
		}
		else
		{
			m_pLoadingBarImg2->setPercent(0.0f);
			m_pSound_on->setVisible(false);
			m_pSound_off->setVisible(true);
			SoundManage::instance()->setSoundOn(true);
		}
	}
}

void SettingForm::onParentsButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		SupSDK::instance()->showParentsMail();
	}
}

void SettingForm::onRateButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		SupSDK::instance()->comment();
	}
}

void SettingForm::onSharButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		SupSDK::instance()->share();

	}
}

void SettingForm::onFacebookButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		SupSDK::instance()->ShowUmEvent(FACEBOOK_UM);


		if (SupSDK::instance()->getfacebooktype())
		{
			showMessageBoxID("Item10");
			return;
		}
		SupSDK::instance()->showfacebook();
	}
}
