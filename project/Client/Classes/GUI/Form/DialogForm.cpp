
/*
** declare DialogForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "DialogForm.h"
#include "GameType.h"
#include "SDK/SupSDK.h"
#include "BabyCare.h"
////////////////////////DialogBase////////////////////////////////
DialogBase::DialogBase(string& text, const AlertHandler& handler) :
Form(IDC_Message)
, m_Content(text)
, m_Handler(handler)
{

}

DialogBase::~DialogBase()
{

}

bool DialogBase::init()
{
	if (Form::init())
	{
		m_pLayout = (Layout*)CSLoader::createNode("messagebox.csb");
		this->addChild(m_pLayout);

		auto pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		auto pText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pLayout, "Text_words"));
		pText->setText(m_Content);

		auto m_globImage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_gold"));

		auto pText1 = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pLayout, "Text_x"));
		auto pAtlas = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(m_pLayout, "AtlasLabel_sum"));
		//auto m_globsp = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_21"));

		if (m_Content != "Rewards")
		{
			//pglob->setVisible(false);
			pText1->setVisible(false);
			pAtlas->setVisible(false);
			m_globImage->setVisible(false);
			//m_globsp->setVisible(false);

		}
		else
		{
			pText->setVisible(false);
			pText1->setVisible(true);
			pAtlas->setVisible(true);
			m_globImage->setVisible(true);
			//m_globsp->setVisible(true);

			Player* pPlayer = EntityMgr::instance()->pPlayer();

			pAtlas->setString(sup::SupString::int2String(pPlayer->getisglob()));
			pText->setPosition(ccp(pText->getPositionX(), pText->getPositionY() + 50));

		}




		return true;
	}

	return false;
}

////////////////////////Dialog_OK//////////////////////////////////

Dialog_OK::Dialog_OK(string& text, const AlertHandler& handler)
:DialogBase(text, handler)
{


}

Dialog_OK::~Dialog_OK()
{

}

bool Dialog_OK::init()
{
	if (DialogBase::init())
	{
		setKeyboardEnabled(false);

		cocos2d::Size size = Director::getInstance()->getVisibleSize();
		m_pOKButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_ok"));

		m_pBkImage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		m_pOKButton->setPosition(cocos2d::Point(m_pBkImage->getContentSize().width / 2, m_pOKButton->getPositionY()));
		m_pOKButton->addTouchEventListener(this, toucheventselector(Dialog_OK::onOKButtonClicked));

		m_pYesButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_yes"));
		m_pYesButton->setVisible(false);

		m_pNoButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_no"));
		m_pNoButton->setVisible(false);



		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);
		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);
		return true;
	}

	return false;
}

void Dialog_OK::onOKButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		m_pOKButton->setTouchEnabled(false);
		if (&m_Handler != NULL){
			m_Handler.call(MBCLICK_YES);
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
			sup::SupActions::BulgeNodeReverse(m_pBkImage, 0.0f, 1.0f, CallFunc::create([=]{

				if (m_Content != "Rewards")
				{

					Player* pPlayer = EntityMgr::instance()->pPlayer();

					if (pPlayer->getismess() == false)
					{
						showPopAD(0.5, false);
					}
				}
				Director::getInstance()->getRunningScene()->removeChild(this);



			}));
		}
	}
}

///////////////////////Dialog_YesNo///////////////////////////////////


Dialog_YesNo::Dialog_YesNo(string& text, const AlertHandler& handler)
:DialogBase(text, handler)
{


}

Dialog_YesNo::~Dialog_YesNo()
{
	//SupSDK::instance()->HideNativeAd();

}

bool Dialog_YesNo::init()
{
	if (DialogBase::init())
	{
		m_pBkImage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pLayout, "Image_bg"));

		m_pYesButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_yes"));
		m_pYesButton->addTouchEventListener(this, toucheventselector(Dialog_YesNo::onYesButtonClicked));

		m_pNoButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_no"));
		m_pNoButton->addTouchEventListener(this, toucheventselector(Dialog_YesNo::onNoButtonClicked));

		m_pOKButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_ok"));
		m_pOKButton->setVisible(false);

		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);

		/*	if (SupSDK::instance()->CanPopAdShow() && !pPlayer->readNoAdsStatus() && SupSDK::instance()->HaveNativeAd() && SupSDK::instance()->IsNativeWithPop() && pPlayer->getismess() == false || !SupSDK::instance()->CanPopAdShow() && !pPlayer->readNoAdsStatus() && SupSDK::instance()->HaveNativeAd() && pPlayer->getismess() == false)
			{
			m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, winSize.height*0.5 + m_pBkImage->getCustomSize().height*0.5));
			this->runAction(Sequence::create(DelayTime::create(0.2f), CallFunc::create([this](){
			SupSDK::instance()->ShowNativeAd();
			SupSDK::instance()->hideOptAD();
			}), NULL));
			}
			else
			{*/
			m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));
		//}
		return true;
	}

	return false;
}

void Dialog_YesNo::onYesButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		m_pYesButton->setTouchEnabled(false);
		m_pNoButton->setTouchEnabled(false);

		if (&m_Handler != NULL){
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
			sup::SupActions::BulgeNodeReverse(m_pBkImage, 0.0f, 1.0f, CallFunc::create([=]{
				m_Handler.call(MBCLICK_YES);

				if (m_Content != "Rewards")
				{

					Player* pPlayer = EntityMgr::instance()->pPlayer();

					if (pPlayer->getismess() == false)
					{
						showPopAD(0.5, false);
					}
				}
				Director::getInstance()->getRunningScene()->removeChild(this);
			}));
		}
	}
}

void Dialog_YesNo::onNoButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		m_pYesButton->setTouchEnabled(false);
		m_pNoButton->setTouchEnabled(false);

		if (BabyCare::instance()->getCurrSceneID() == EScene_Select)// 
		{

			NotificationCenter::getInstance()->postNotification(SHOW_ICON);
		}
		if (&m_Handler != NULL){
			//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
			m_Handler.call(MBCLICK_NO);
			sup::SupActions::BulgeNodeReverse(m_pBkImage, 0.0f, 1.0f, CallFunc::create([=]{
				if (m_Content != "Rewards")
				{
					Player* pPlayer = EntityMgr::instance()->pPlayer();
					if (pPlayer->getismess() == false)
					{
						showPopAD(0.5, false);
					}
				}
				Director::getInstance()->getRunningScene()->removeChild(this);
			}));
		}
	}
}

//////////////////////////////////////////////////////////