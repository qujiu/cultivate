#include "InfoForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
InfoForm::InfoForm() :
Form(IDC_Info)
{

}

InfoForm::~InfoForm()
{

}

bool InfoForm::init()
{
	if (Form::init())
	{
		m_pLayout = dynamic_cast<Layout*>(CSLoader::createNode("Info.csb"));
		this->addChild(m_pLayout, 1);

		auto pCloseButton = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pLayout, "Button_close"));
		pCloseButton->addTouchEventListener(this, toucheventselector(InfoForm::onCloseButtonClicked));
		SupLayout::setRelativePos(pCloseButton, pCloseButton->getPosition(), SUP_ALIGNMENT_LB);
		m_pLayout->addTouchEventListener(this, toucheventselector(InfoForm::onInfoClicked));
		m_pInterlayer = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pLayout, "Panel_interlayer"));
		SupLayout::setRelativePos(m_pInterlayer, m_pInterlayer->getPosition(), SUP_ALIGNMENT_LB, E_SUP_SCALE_XY);
		m_pInterlayer->setVisible(false);
		return true;
	}
	return false;
}

void InfoForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		//NotificationCenter::getInstance()->postNotification(NOT_FORM_INFO_CLOSE);
		this->removeFromParentAndCleanup(true);
	}
}

void InfoForm::onInfoClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		if (m_pInterlayer->isVisible())
		{
			showBuyForm();
			return;
		}

		m_pInterlayer->setVisible(true);
		auto pLockImg = ImageView::create("ani_xuanze_renwu_ui_suozi.png", Widget::TextureResType::LOCAL);
		pLockImg->setPosition(m_winSize*0.5f);
		m_pInterlayer->addChild(pLockImg);
		BulgeNode(pLockImg, 0.0f, 2.0f, callfunc_selector(InfoForm::showBuyForm));
	}
}

void InfoForm::showBuyForm()
{
	//int tag = EntityMgr::instance()->pPlayer()->getGameLevel();
	//int flag = tag - SaveManage::instance()->getIntSave(SAVE_ID_INT_Level);
	//if (1 == flag)
	//{
	//	EntityMgr::instance()->pPlayer()->setCurrStoreType(EStoreUIType_Rooms);
	//	EntityMgr::instance()->pPlayer()->setCurrBuyID(tag);

	//	auto pLvevl = EntityMgr::instance()->pPlayer()->getLevelList()->getLevelByID(tag);
	//	EntityMgr::instance()->pPlayer()->setCurrBuyGold(pLvevl->getPrice());

	//	auto pForm = UIFactory::instance()->showUnLockForm();
	//	if (NULL != pForm)
	//	{
	//		BabyCare::instance()->getCurrScene()->addChild(pForm, 10);
	//	}
	//}
	///*else if (flag > 1)
	//{
	//	auto pForm = UIFactory::instance()->showShopForm(EStoreUIType_Shop);
	//	if (NULL != pForm)
	//	{
	//		BabyCare::instance()->getCurrScene()->addChild(pForm, 10);
	//	}

	//}*/
}