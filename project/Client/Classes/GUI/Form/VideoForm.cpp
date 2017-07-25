
/*
** declare VideoForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "VideoForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "../UIFactory.h"
////////////////////////DialogBase////////////////////////////////
VideoForm::VideoForm(int iType) :
Form(IDC_Rate)
{
	m_iType = iType;
}

VideoForm::~VideoForm()
{

}

bool VideoForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);

		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("Video.csb");
		this->addChild(m_pLayout);

		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));
		m_pBkImage->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBoxImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_box"));
		m_pBoxImg->setPosition(ccp(m_pBoxImg->getPositionX()*SUP_SCALE_X, m_pBoxImg->getPositionY()*SUP_SCALE_Y));

		auto pCloseBtn = dynamic_cast<Button*>(m_pBoxImg->getChildByName("Button_close"));
		pCloseBtn->addTouchEventListener(this, toucheventselector(VideoForm::onCloseButtonClicked));

		auto pVideo = dynamic_cast<Layout*>(m_pBoxImg->getChildByName("Panel_video"));
		auto pRate = dynamic_cast<Layout*>(m_pBoxImg->getChildByName("Panel_rate"));
		auto pVideoBox = dynamic_cast<Layout*>(m_pBoxImg->getChildByName("Panel_video_Box"));
		pVideo->setVisible(false);
		pRate->setVisible(false);
		pVideoBox->setVisible(false);

		//video
		if (m_iType == 0)
		{
			pVideo->setVisible(true);

			auto pVideoBtn = dynamic_cast<Button*>(pVideo->getChildByName("Button_video"));
			pVideoBtn->addTouchEventListener(this, toucheventselector(VideoForm::onVideoButtonClicked));
			sup::SupActions::PulseNode(pVideoBtn, 1.1f, .9f, 1.5f, true);
		}
		//video ³é½±
		else if (m_iType == 1)
		{
			pVideoBox->setVisible(true);

			auto pVideoBtn = dynamic_cast<Button*>(pVideoBox->getChildByName("Button_video"));
			pVideoBtn->addTouchEventListener(this, toucheventselector(VideoForm::onVideoButtonClicked));
			sup::SupActions::PulseNode(pVideoBtn, 1.1f, .9f, 1.5f, true);
		}
		else //rate
		{
			pRate->setVisible(true);

			auto pRateBtn = dynamic_cast<Button*>(pRate->getChildByName("Button_rate"));
			pRateBtn->addTouchEventListener(this, toucheventselector(VideoForm::onRateButtonClicked));
			sup::SupActions::PulseNode(pRateBtn, 1.1f, .9f, 1.5f, true);
		}

		sup::SupActions::BulgeNode(m_pBoxImg, 0.0f, 1.0f);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_OPENDIALOG);

		return true;
	}

	return false;
}

void VideoForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_CLOSEDIALOG);
		m_pBoxImg->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			this->removeFromParentAndCleanup(true);
		})));
	}
}

void VideoForm::onRateButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		this->removeFromParentAndCleanup(true);
		SupSDK::instance()->comment();
		pPlayer->SetIsRated(true);
	}
}

void VideoForm::onVideoButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		if (m_iType == 1)
		{
			pPlayer->setisBoxVideo(true);
		}

		if (SupSDK::instance()->canPlayVideo())
		{
			pPlayer->setStoreis(false);
			SupSDK::instance()->playVideo();
		}
		else
		{
			showMessageBoxID("Item4");
			pPlayer->setisBoxVideo(false);
		}

		this->removeFromParentAndCleanup(true);
	}
}

//////////////////////////////////////////////////////////