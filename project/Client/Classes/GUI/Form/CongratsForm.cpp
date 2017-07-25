
#include "CongratsForm.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "GUI/Game/GameScene.h"

CongratsForm::CongratsForm(int iID) :
Form(IDC_Congrats)
{
	m_iID = iID;
}

CongratsForm::~CongratsForm()
{

}

bool CongratsForm::init()
{
	if (Form::init())
	{
		auto pCongratulation = CSLoader::createNode("congratulation.csb");
		this->addChild(pCongratulation, 1);
		setKeyboardEnabled(true);

		m_pGeceng = dynamic_cast<ImageView*>(pCongratulation->getChildByName("Image_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pPanelPos = dynamic_cast<Layout*>(pCongratulation->getChildByName("Panel_pos"));
		m_pPanelPos->setPosition(ccp(m_pPanelPos->getPositionX()*SUP_SCALE_X, m_pPanelPos->getPositionY()*SUP_SCALE_Y));

		auto sktAni = SkeletonAnimation::createWithFile("res/ui/common/payitem.json", "res/ui/common/payitem.atlas", 1.0f);
		sktAni->setAnimation(0, "animation", false);
		m_pPanelPos->addChild(sktAni);

		sktAni->setEventListener([this](int trackIndex, spEvent* event) {
			log("%d event: %s, %d, %f, %s", trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
			if (0 == strcmp(event->data->name, "effect_paopao_01"))
			{
				auto particle = ParticleSystemQuad::create("res/ui/common/effect_zhuhe_star.plist");
				particle->setPosition(0, 0);
				m_pPanelPos->addChild(particle, 3);
			}
		});
		auto native_static_res = EntityMgr::instance()->pPlayer()->getItemToolList()->getItemToolByID(m_iID);
		auto Imagestr = native_static_res->getImage();
		if (m_iID <= 67)
		{
			auto tmpstr = "res/ui/dress/" + Imagestr;
			auto pIcon = ImageView::create(tmpstr.c_str());
			pIcon->setScale(1.0f);
			m_pPanelPos->addChild(pIcon);
		}
		else
		{
			auto pIcon = ImageView::create(native_static_res->getImage().c_str());
			pIcon->setScale(1.0f);
			m_pPanelPos->addChild(pIcon);
		}
		
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_JIESUO);

		sup::SupActions::BulgeNode(m_pPanelPos, 0.0f, 1.0f);

		this->scheduleOnce(schedule_selector(CongratsForm::onCloseScheduleFunc), 2.0f);

		return true;
	}

	return false;
}

void CongratsForm::onCloseScheduleFunc(float dt)
{
	ScaleTo* scaleTo;
	scaleTo = ScaleTo::create(0.5f, 0);
	CCFadeOut* fadeout1 = CCFadeOut::create(0.3);
	m_pGeceng->runAction(fadeout1);
	auto ease = EaseBackIn::create(scaleTo);

	//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANGSHOUHUI);
	this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(CongratsForm::onCloseButtonCallback))));
}

void CongratsForm::onCloseButtonCallback()
{
	UserDefault::getInstance()->setBoolForKey(IsFANHUI.c_str(), false);
	UserDefault::getInstance()->flush();

	this->removeFromParentAndCleanup(true);
	if (EntityMgr::instance()->pPlayer()->getimNotification() == 2)
	{
		auto pForm = UIFactory::instance()->showVideoForm(1, EntityMgr::instance()->pPlayer()->getimlucky());
		if (NULL != pForm)
		{
			Director::getInstance()->getRunningScene()->addChild(pForm, 10);
		}
	}

}