
#include "HomeForm.h"
#include "SDK/SupSDK.h"
#include "BabyCare.h"
#include "../UIFactory.h"

HomeForm::HomeForm() :
Form(IDC_Home)
, m_isClickStart(false)
{

}

HomeForm::~HomeForm()
{

}

bool HomeForm::init()
{
	if (Form::init())
	{
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		m_pLayout = (Layout*)CSLoader::createNode("home.csb");
		this->addChild(m_pLayout, 1);

		auto pBackImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		pBackImage->setPosition(ccp(pBackImage->getPositionX()*SUP_SCALE_X, pBackImage->getPositionY()*SUP_SCALE_Y));
		pBackImage->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		pBackImage->setZOrder(-1);

		auto m_pBiaoti = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_biaoti"));
		m_sktBiaotiAni = SkeletonAnimation::createWithFile("res/ui/home/logo.json", "res/ui/home/logo.atlas", 1.0f);
		m_pBiaoti->setPosition(ccp(m_pBiaoti->getPositionX()*SUP_SCALE_X, m_pBiaoti->getPositionY()*SUP_SCALE_Y));
		m_pBiaoti->addChild(m_sktBiaotiAni);
		m_sktBiaotiAni->update(0);
		m_sktBiaotiAni->setAnimation(0, "animation", true);

		auto panelPos = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_pos"));
		panelPos->setPosition(ccp(panelPos->getPositionX()*SUP_SCALE_X, panelPos->getPositionY()*SUP_SCALE_Y));

		auto m_pPerson = dynamic_cast<Layout*>(panelPos->getChildByName("Panel_person"));
		auto m_sktPerAni = SkeletonAnimation::createWithFile("res/Spine/fengmian/fengmian.json", "res/Spine/fengmian/fengmian.atlas", 1.0f);
		m_pPerson->addChild(m_sktPerAni);
		m_sktPerAni->setAnimation(0, "daiji", true);
		m_sktPerAni->update(0);


		m_sktPersonAni = SkeletonAnimation::createWithFile("res/ui/home/start.json", "res/ui/home/start.atlas", 1.0f);
		m_pstar = dynamic_cast<Layout*>(panelPos->getChildByName("Panel_start"));
		m_pstar->setPosition(ccp(m_pstar->getPositionX()*SUP_SCALE_X, m_pstar->getPositionY()*SUP_SCALE_Y));
		m_pstar->addChild(m_sktPersonAni);
		m_sktPersonAni->update(0);

		auto pBoundingbox = (spBoundingBoxAttachment*)m_sktPersonAni->getAttachment("001", "001");
		auto rec = m_sktPersonAni->getSkeleton();
		m_pSkeletonBounds = spSkeletonBounds_create();
		spSkeletonBounds_update(m_pSkeletonBounds, rec, 1);
		m_pCheckPoly = spSkeletonBounds_getPolygon(m_pSkeletonBounds, pBoundingbox);

		m_sktPersonAni->setAnimation(0, "start", false);
		m_sktPersonAni->addAnimation(0, "xunhuan", true);


		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(HomeForm::onTouchBeginListener, this);

		auto touchLayout = dynamic_cast<ui::Layout*>(m_pLayout->getChildByName("Panel_touch"));
		touchLayout->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, touchLayout);

		UserDefault::getInstance()->flush();

		//this->scheduleOnce(schedule_selector(HomeForm::updateicon), 0.5f);
		return true;
	}
	return false;
}

bool HomeForm::onTouchBeginListener(Touch *touch, Event *unusedEvent)
{
	if (m_isClickStart)
	{
		return true;
	}
	cocos2d::Rect triggerRect;
	Vec2 pStartPos = touch->getStartLocation();

	Vec2 pos = m_sktPersonAni->convertToNodeSpace(pStartPos);

	if (spPolygon_containsPoint(m_pCheckPoly, pos.x, pos.y))
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->setStaris(true);
	//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_PLAYBTN);
		m_sktPersonAni->setAnimation(0, "start", false);
		m_sktPersonAni->setEndListener([this](int trackIndex) {
			spTrackEntry* entry = spAnimationState_getCurrent(m_sktPersonAni->getState(), trackIndex);
			const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
			if (trackIndex == 0 && 0 == strcmp(animationName, "start"))
			{
				BabyCare::instance()->onStatusChanged(EScene_Select);

			}
		});
		spSkeletonBounds_dispose(m_pSkeletonBounds);

		m_isClickStart = true;
	}

	return true;
}

void HomeForm::onMinigameButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		BabyCare::instance()->gotoMinigame();
		pPlayer->setimNotification(4);
		//SupSDK::instance()->hideOptAD();

	}
}void HomeForm::onParentsButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//SupSDK::instance()->showParentsMail();
	}
}
void HomeForm::onMoreButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		Image_moredot->setVisible(false);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);

		//SupSDK::instance()->More();
		//SupSDK::instance()->updateMoredot();

	}
}


void HomeForm::onCoinsButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		Image_coindot->setVisible(false);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		//SupSDK::instance()->showOffer();
		//SupSDK::instance()->updatecoinsdot();
	}
}

void HomeForm::onSettingButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		auto pForm = UIFactory::instance()->showSettingForm();
		if (NULL != pForm)
		{
			this->addChild(pForm, 10);
		}
	}
}
void HomeForm::updateicon(float dt){
	auto pSettinggame = dynamic_cast<Button*>(m_pLayout->getChildByName("Button_game"));
	pSettinggame->setPosition(ccp(pSettinggame->getPositionX()*SUP_SCALE_X, pSettinggame->getPositionY()*SUP_SCALE_Y));

	if (SupSDK::instance()->CanShowOptAD())
	{
		SupSDK::instance()->showOptAD(pSettinggame->getPositionX(), pSettinggame->getPositionY(), pSettinggame->getCustomSize().width, pSettinggame->getCustomSize().height);
	}


}
void HomeForm::tankuang(Ref* object){

	this->scheduleOnce(schedule_selector(HomeForm::updatedui), 0.01f);


}
void HomeForm::updatedui(float dt){
	showMessageBoxID("Item9");
}
void HomeForm::buySuccess(Ref* object)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	auto iCurrBuyGold = pPlayer->getCurrBuyGold();
	if (iCurrBuyGold == -1)
	{
		pPlayer->saveNoAdsStatus();
		//SupSDK::instance()->hideBannerAD();
	}
	else
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GOLDFEIRU);
		pPlayer->setCurrGold(pPlayer->getCurrGold() + iCurrBuyGold);
		pPlayer->saveTotalGoldSum();
	}
}

void HomeForm::buyFailed(Ref* object)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	pPlayer->setCurrBuyGold(0);
	showMessageBoxID("Item5");
}

void HomeForm::buyTimeout(Ref* object)
{
	showMessageBoxID("Item6");
}

void HomeForm::moredot_can(Ref* object)
{
	Image_moredot->setVisible(true);
}

void HomeForm::coinsdot_can(Ref* object)
{
	Image_coindot->setVisible(true);
}