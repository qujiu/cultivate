
#include "NaolingForm.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "GUI/Game/GameScene.h"

NaolingForm::NaolingForm() :
Form(IDC_Naoling)
{
}

NaolingForm::~NaolingForm()
{
}

bool NaolingForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = static_cast<Widget*>(CSLoader::createNode("Naoling.csb"));
		this->addChild(m_pLayout, 1);

		m_pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBgImg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBgImg->setPosition(ccp(m_pBgImg->getPositionX()*SUP_SCALE_X, m_pBgImg->getPositionY()*SUP_SCALE_Y));
		m_pBgImg->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		auto pOKBtn = dynamic_cast<Button*>(m_pBgImg->getChildByName("Button_ok"));
		pOKBtn->addTouchEventListener(this, toucheventselector(NaolingForm::onOKButtonClicked));

		sup::SupActions::BulgeNode(m_pBgImg, 0.0f, 1.0f);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_OPENDIALOG);
		this->scheduleOnce(schedule_selector(NaolingForm::onCloseScheduleFunc), 5.0f);

		return true;
	}
	
	return false;
}

void NaolingForm::onCloseScheduleFunc(float dt)
{
    auto scaleTo = ScaleTo::create(0.5f, .2f);
	auto ease = EaseBackIn::create(scaleTo);
	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_CLOSEDIALOG);
	m_pBgImg->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(NaolingForm::onCloseButtonCallback))));
	auto pos = ccp(725, 312);
	pos = ccp(pos.x * SUP_SCALE_X, pos.y * SUP_SCALE_Y);
	sup::SupActions::BulgeNodeReverse_Tip(m_pBgImg, pos, m_pBgImg->getPosition(), 0, 1, CallFunc::create([=]{
		onCloseButtonCallback();
	}));
}

void NaolingForm::onCloseButtonCallback()
{
	this->removeFromParentAndCleanup(true);
}

void NaolingForm::onOKButtonClicked(Ref *sender, TouchEventType type)
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
		onCloseScheduleFunc(0.0f);
	}
}