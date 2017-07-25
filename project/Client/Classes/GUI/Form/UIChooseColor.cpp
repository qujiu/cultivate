#include "UIChooseColor.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"
#include "../../MiniGame/MiniGame.h"
#include "../UIMask.h"

UIChooseColor::UIChooseColor() :
Form(IDC_ChooseColor)
{
}

UIChooseColor::~UIChooseColor()
{
}

bool UIChooseColor::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);
		m_lab_bg.clear();

		pStore = CSLoader::createNode("UIChooseColor.csb");
		this->addChild(pStore, 1);
		this->setAnchorPoint(ccp(0.5, 0.5));

		m_pGeceng = dynamic_cast<ImageView*>(pStore->getChildByName("ImgGeceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		auto pClose = dynamic_cast<ImageView*>(pStore->getChildByName("Img_close"));
		pClose->addTouchEventListener(this, toucheventselector(UIChooseColor::onCloseButtonClicked));
		pClose->setPosition(ccp(pClose->getPositionX()*SUP_SCALE_X, pClose->getPositionY()*SUP_SCALE_Y));
		pClose->setTouchEnabled(true);

		for (int i = 1; i < REN_NUM + 1; i++)
		{
			std::string name = "Image_" + sup::SupString::int2String(i);
			auto pClose = dynamic_cast<ImageView*>(pStore->getChildByName(name));
			m_lab_bg.push_back(pClose);
			pClose->setTag(i);
			pClose->setTouchEnabled(true);
			pClose->addTouchEventListener(this, toucheventselector(UIChooseColor::onBuygameButtonClicked));

		}
		return true;
	}
	return false;
}

void UIChooseColor::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		((ImageView*)sender)->setEnabled(false);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		auto scaleTo = ScaleTo::create(1.0f, 0.0f);
		auto ease = EaseBackIn::create(scaleTo);
		CCFadeOut* fadeout1 = CCFadeOut::create(0.5);
		m_pGeceng->runAction(fadeout1);
		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(UIChooseColor::onCloseButtonCallback))));
	}
}

void UIChooseColor::onCloseButtonCallback()
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCurrRoleId((EGameRole)pPlayer->readroleid());
	int type = (EGameRole)pPlayer->readroleid() > 2 ? type = 1 : type = 0;
	pPlayer->setCurrRoleType(type);
	Director::getInstance()->getRunningScene()->removeChild(this);
	//NotificationCenter::getInstance()->postNotification(UPDATE_Ren);
	//NotificationCenter::getInstance()->postNotification(ACTION_HOUSE);
}
void UIChooseColor::onBuygameButtonClicked(Ref *sender, TouchEventType type)
{
	auto tag = ((Node*)sender)->getTag();
	if (TOUCH_EVENT_BEGAN == type)
	{

	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->setStaris(false);
		sup::SupActions::ButtonActionyuan((Node*)sender);
		UIMask* la = UIMask::create(0);
		this->addChild(la, 2);
		for (int i = 0; i < m_lab_bg.size(); i++)
		{
			ImageView* bu = m_lab_bg[i];
			if (bu->getTag() == tag)
			{
				continue;
			}
			bu->setVisible(false);
		}
		int roid = tag -1 ;
		pPlayer->setCurrRoleId((EGameRole)roid);
		pPlayer->saveroleid(roid);
		int type = roid > 2 ? type = 1 : type = 0;
		pPlayer->setCurrRoleType(type);
		std::string name = "Image_" + sup::SupString::int2String(tag);
		auto pClose = dynamic_cast<ImageView*>(pStore->getChildByName(name));
		auto scale1 = ScaleTo::create(.1f, 1.2f, 0.8f);
		auto scale2 = ScaleTo::create(.1f, 0.8f, 1.2f);
		auto scale3 = ScaleTo::create(.1f, 1.0f, 1.0f);
		auto spawn = Spawn::create(scale1, scale2, scale3, NULL);
		pClose->setZOrder(10);
		pClose->runAction(Sequence::create(DelayTime::create(0.5f), spawn, DelayTime::create(0.5f), CallFuncN::create(CC_CALLBACK_1(UIChooseColor::stamp, this, tag)), NULL));
	}
}

void UIChooseColor::stamp(Node *obj, int date)
{
	std::string name = "Image_house" + sup::SupString::int2String(date);
	auto pClose = dynamic_cast<ImageView*>(pStore->getChildByName(name));
	scheduleOnce(schedule_selector(UIChooseColor::updateresult), 1.5f);
}


void UIChooseColor::updateresult(float dt){

//	NotificationCenter::getInstance()->postNotification(UPDATE_Ren);
	this->removeFromParentAndCleanup(true);
	//NotificationCenter::getInstance()->postNotification(BAOXIANG, (Ref*)(intptr_t)10);
	//NotificationCenter::getInstance()->postNotification(ACTION_HOUSE);
}