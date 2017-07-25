
/*
** declare UnlockTipForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "UnlockTipForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "../UIFactory.h"



UnlockTipForm::UnlockTipForm(int iType) :
Form(IDC_UnlockTip)
{
	m_iType = iType;
}

UnlockTipForm::~UnlockTipForm()
{

}

bool UnlockTipForm::init()
{
	if (Form::init())
	{

		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("unlockTip.csb");
		this->addChild(m_pLayout);

		m_pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		auto pOKBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_ok"));
		pOKBtn->addTouchEventListener(this, toucheventselector(UnlockTipForm::onOKButtonClicked));

		auto pUnlockImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_unlock"));
		auto pLockImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_lock"));

		auto pToy = dynamic_cast<Layout*>(m_pBkImage->getChildByName("Panel_toy"));
		auto pCanting = dynamic_cast<Layout*>(m_pBkImage->getChildByName("Panel_canting"));
		auto pMuyu= dynamic_cast<Layout*>(m_pBkImage->getChildByName("Panel_muyu"));
		auto pDress = dynamic_cast<Layout*>(m_pBkImage->getChildByName("Panel_dress"));

		if (m_iType == 0)
		{
			pToy->setVisible(true);
		}
		else if (m_iType == 1)
		{
			pCanting->setVisible(true);
		}
		else if (m_iType == 2)
		{
			pMuyu->setVisible(true);
		}
		else if (m_iType == 3)
		{
			pDress->setVisible(true);
		}

		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);
		return true;
	}
	return false;
}

void UnlockTipForm::onOKButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		m_pGeceng->setVisible(false);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);

		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			this->removeFromParentAndCleanup(true);
		})));
	}
}

//////////////////////////////////////////////////////////