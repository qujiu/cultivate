
/*
** declare BuyTipForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "BuyTipForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "../UIFactory.h"
#include "MenuControl.h"
#include "BabyCare.h"

BuyTipForm::BuyTipForm(int iGoldSum, int iID) :
Form(IDC_BuyTip)
{
	m_iGoldSum = iGoldSum;
	m_iID = iID;
}

BuyTipForm::~BuyTipForm()
{

}

bool BuyTipForm::init()
{
	if (Form::init())
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("BuyTip.csb");
		this->addChild(m_pLayout);

		m_pGeceng = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_1"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		auto pText = dynamic_cast<Text*>(m_pBkImage->getChildByName("Text_words"));

		auto pStarFishImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_gold"));

		auto pGoldSum = dynamic_cast<TextBMFont*>(m_pBkImage->getChildByName("BitmapFontLabel_gold"));
		pGoldSum->setString(sup::SupString::int2String(m_iGoldSum));

		auto pYesBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_yes"));
		pYesBtn->addTouchEventListener(this, toucheventselector(BuyTipForm::onYesButtonClicked));

		auto pNoBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_no"));
		pNoBtn->addTouchEventListener(this, toucheventselector(BuyTipForm::onNoButtonClicked));

		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);

		return true;
	}

	return false;
}

void BuyTipForm::onYesButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((Button*)sender)->setTouchEnabled(false);
		m_pGeceng->setVisible(false);
		auto scaleTo = ScaleTo::create(0.5f, 0.0f);
		auto ease = EaseBackIn::create(scaleTo);

		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			auto pPlayer = EntityMgr::instance()->pPlayer();
			if (m_iGoldSum <= pPlayer->getCurrGold())
			{
				NotificationCenter::getInstance()->postNotification(ENOTIFY_AFTERBUYITEMSUCCESSFUNC, __Integer::create(m_iID));
			}
			else
			{
				auto pForm = UIFactory::instance()->showStoreForm();
				if (NULL != pForm)
				{
					BabyCare::instance()->getCurrScene()->addChild(pForm, 5);
				}
			}
			this->removeFromParentAndCleanup(true);
		})));

	}
}

void BuyTipForm::showStoreForm(MBCLICK_TYPE type, void* data)
{
	if (MBCLICK_YES == type)
	{
		auto *pForm = UIFactory::instance()->showStoreForm();
		if (NULL != pForm)
		{
			Director::getInstance()->getRunningScene()->addChild(pForm, 10);
		}
	}
}

void BuyTipForm::onNoButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
//		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((Button*)sender)->setTouchEnabled(false);
		m_pGeceng->setVisible(false);
		auto scaleTo = ScaleTo::create(0.5f, 0.0f);
		auto ease = EaseBackIn::create(scaleTo);

		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			this->removeFromParentAndCleanup(true);
		})));
	}
}

