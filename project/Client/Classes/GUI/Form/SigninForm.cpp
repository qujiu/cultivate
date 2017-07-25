#include "SigninForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "../UIMask.h"
#include "GUI/Form/SelectForm.h"
#include "../UIFactory.h"
#include "SelectForm.h"

#define Gold_IMG_Tag  90000

SigninForm::SigninForm() :
Form(IDC_Signin)
, m_pTimelineNode(NULL)
, m_iCountGold(0)
{
	//初始化奖励物品ID
	int eItemType[] = { 21, 26, 12, 29, 77, 95, 81 };
	for (int i = 0; i < (sizeof(eItemType) / sizeof(eItemType[0])); i++)
	{
		m_vecSubItem.push_back(eItemType[i]);
	}

	Player* pPlayer = EntityMgr::instance()->pPlayer();
	m_iDays = pPlayer->readSignInDays();
}

SigninForm::~SigninForm()
{

}

bool SigninForm::init()
{
	if (Form::init())
	{
		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("signin.csb");
		this->addChild(m_pLayout);

		m_pGeceng = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);
		m_pGeceng->setPosition(ccp(m_pGeceng->getPositionX()*SUP_SCALE_X, m_pGeceng->getPositionY()*SUP_SCALE_Y));
		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		auto pCloseImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_close"));
		pCloseImg->addTouchEventListener(this, toucheventselector(SigninForm::onCloseButtonClicked));

		//m_pBoardImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_board"));

		auto pJindutiaoImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_jindutiao_bg"));
		m_pLoadingBarImg = dynamic_cast<LoadingBar*>(pJindutiaoImg->getChildByName("LoadingBar_1"));

		m_pGold1Img = dynamic_cast<ImageView*>(pJindutiaoImg->getChildByName("Image_gold1"));
		m_pGold1Img->addTouchEventListener(this, toucheventselector(SigninForm::onGetGold1ButtonClicked));

		m_pGold2Img = dynamic_cast<ImageView*>(pJindutiaoImg->getChildByName("Image_gold2"));
		m_pGold2Img->addTouchEventListener(this, toucheventselector(SigninForm::onGetGold2ButtonClicked));

		m_pCountLayout = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_count"));
		m_pCountLayout->setPosition(ccp(m_pCountLayout->getPositionX()*SUP_SCALE_X, m_pCountLayout->getPositionY()*SUP_SCALE_Y));
		m_pCountLayout->setVisible(false);
		auto pGoldImg = dynamic_cast<ImageView*>(m_pCountLayout->getChildByName("Image_gold"));
		m_pCountText = dynamic_cast<TextAtlas*>(m_pCountLayout->getChildByName("AtlasLabel_count"));

		sigetbu = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_get"));
		sigetbu->addTouchEventListener(this, toucheventselector(SigninForm::onGetButtonClicked));
		refreshSignInItem();

		int m_iDays = pPlayer->readSignInDays();

		for (int i = 0; i < 7; i++)
		{
			if (i < m_iDays)
			{
				pPlayer->setimsign(false);

			}
			if (i == m_iDays)
			{
				const time_t t = time(NULL);
				const time_t t1 = pPlayer->readSigninDate();
				if (!SupLayout::isSameDay(t, t1))
				{
					sup::SupActions::PulseNode(sigetbu, 1.1f, 1.2f, 1.1f, true);
				}
			}
		}
		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);
		return true;
	}
	return false;
}

void SigninForm::refreshSignInItem()
{
	ImageView *pIcontext;
	ImageView *pIcontextim;

	Player* pPlayer = EntityMgr::instance()->pPlayer();
	for (int i = 0; i < 7; i++)
	{
		auto pIconImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_" + sup::SupString::int2String(i + 1)));
		auto pIconbg = dynamic_cast<Sprite*>(m_pBkImage->getChildByName("Image_daojubg_" + sup::SupString::int2String(i + 1)));
		if (i < 6)
		{
			pIcontext = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Text_" + sup::SupString::int2String(i + 1)));
		}
		else
		{
			pIcontextim = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Text_7"));

		}
		auto pDuihao = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_duihao" + sup::SupString::int2String(i + 1)));
		if (i < m_iDays)
		{
			pIconImg->setColor(ccc3(128, 128, 128));
			pIconbg->setColor(ccc3(128, 128, 128));
			pDuihao->setVisible(true);
			sigetbu->setBright(false);
			sigetbu->setTouchEnabled(false);
			pPlayer->setimsign(false);
		}
		else if (i == m_iDays)
		{
			const time_t t = time(NULL);
			const time_t t1 = pPlayer->readSigninDate();
			if (!SupLayout::isSameDay(t, t1))
			{
				if (m_pTimelineNode != NULL)
				{
					m_pTimelineNode->removeFromParent();
					m_pTimelineNode = NULL;
				}
				m_pTimelineNode = CSLoader::createNode("res/ui/sign/ani_lizi.csb");
				m_pActionTimeline = CSLoader::createTimeline("res/ui/sign/ani_lizi.csb");
				auto pParticle1 = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_1"));
				auto pParticle2 = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_2"));
				if (i == 6)
				{
					pParticle1->setVisible(false);

					pIcontextim->loadTexture("res/ui/sign/today.png");
				}
				else{
					//pIcontext->setText("Today");

					pParticle2->setVisible(false);

				}
				pParticle1->setPositionType(ParticleSystem::PositionType::FREE);
				pParticle2->setPositionType(ParticleSystem::PositionType::FREE);
				m_pTimelineNode->runAction(m_pActionTimeline);
				m_pBkImage->addChild(m_pTimelineNode);
				m_pTimelineNode->setPosition(pIconbg->getPosition());
				m_pActionTimeline->play("animation0", true);

				sigetbu->setBright(true);
				sigetbu->setTouchEnabled(true);

				pPlayer->setimsign(true);

			}
		}

	}

	m_pLoadingBarImg->setPercent(m_iDays * 100 / 7);
	if (m_iDays >= 3 && !pPlayer->readIsGetSignInDays(1))
	{
		m_pGold1Img->setTouchEnabled(true);
		m_pGold1Img->runAction(RepeatForever::create(Sequence::create(CallFunc::create([this](){
			auto particle1 = ParticleSystemQuad::create("res/ui/sign/effect_denglujiemian_guang.plist");
			m_pGold1Img->addChild(particle1);
			particle1->setPosition(ccp(m_pGold1Img->getContentSize().width*0.5, m_pGold1Img->getContentSize().height*0.5));

			auto particle2 = ParticleSystemQuad::create("res/ui/sign/effect_denglujiemian_star.plist");
			m_pGold1Img->addChild(particle2);
			particle2->setPosition(ccp(m_pGold1Img->getContentSize().width*0.5, m_pGold1Img->getContentSize().height*0.5));

		}), DelayTime::create(1.0f), CallFunc::create([this](){
			m_pGold1Img->removeAllChildren();
		}), NULL)));
	}

	if (m_iDays == 7 && !pPlayer->readIsGetSignInDays(2))
	{
		m_pGold2Img->setTouchEnabled(true);
		m_pGold2Img->runAction(RepeatForever::create(Sequence::create(CallFunc::create([this](){
			auto particle1 = ParticleSystemQuad::create("res/ui/sign/effect_denglujiemian_guang.plist");
			m_pGold2Img->addChild(particle1);
			particle1->setPosition(ccp(m_pGold2Img->getContentSize().width*0.5, m_pGold2Img->getContentSize().height*0.5));

			auto particle2 = ParticleSystemQuad::create("res/ui/sign/effect_denglujiemian_star.plist");
			m_pGold2Img->addChild(particle2);
			particle2->setPosition(ccp(m_pGold2Img->getContentSize().width*0.5, m_pGold2Img->getContentSize().height*0.5));

		}), DelayTime::create(1.0f), CallFunc::create([this](){
			m_pGold2Img->removeAllChildren();
		}), NULL)));
	}
}

void SigninForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		((ImageView*)sender)->setTouchEnabled(false);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);
		m_pBkImage->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(SigninForm::onCloseButtonCallback))));
	}
}

void SigninForm::onCloseButtonCallback()
{
	this->removeFromParent();
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (pPlayer->getStaris() == true)
	{
		NotificationCenter::getInstance()->postNotification(SHOW_CHOOSE);

	}
	NotificationCenter::getInstance()->postNotification(DAY_TI);

}

void SigninForm::onGetButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		const time_t t = time(NULL);
		const time_t t1 = pPlayer->readSigninDate();
		auto button = (Button*)sender;
		if (!SupLayout::isSameDay(t, t1))
		{
			m_iDays++;
			if (m_iDays <= 7)
			{
				pPlayer->saveSignInDays(m_iDays);
				pPlayer->saveSigninDate(t);

				refreshSignInItem();

				if (m_pTimelineNode != NULL)
				{
					m_pTimelineNode->removeFromParent();
					m_pTimelineNode = NULL;
				}

				pPlayer->SetSubMenuItemStatusByID(m_vecSubItem[m_iDays - 1], true);
				if (m_vecSubItem[m_iDays - 1] == 12)
				{
					pPlayer->SetSubMenuItemStatusByID(17, true);
				}

				auto *pForm = UIFactory::instance()->showCongratsForm(m_vecSubItem[m_iDays - 1]);
				if (NULL != pForm)
				{
					this->addChild(pForm, 20);
				}
			}
			else
			{
				m_iDays = 7;
			}
		}
	}
}

void SigninForm::onGetGold1ButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((Button*)sender)->setTouchEnabled(false);
		m_pGold1Img->removeAllChildren();

		Player* pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->saveIsGetSignInDays(1, true);

		m_iCountGold = 1000;
		GetGoldFunc();
	}
}

void SigninForm::onGetGold2ButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		sup::SupActions::ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		((Node*)sender)->setScale(1.0f);
		((Button*)sender)->setTouchEnabled(false);
		m_pGold2Img->removeAllChildren();

		Player* pPlayer = EntityMgr::instance()->pPlayer();
		pPlayer->saveIsGetSignInDays(2, true);

		m_iCountGold = 3000;
		GetGoldFunc();
	}
}

void SigninForm::GetGoldFunc()
{
	UIMask* la = UIMask::create(0);
	la->setTag(REMOVE_GAME_CENG);
	this->addChild(la, 23);

	if (m_iCountGold >= CREAT_GLOB)
	{
		glob = CREAT_GLOB;
	}
	else
	{
		glob = m_iCountGold;
	}

	showGoldCreateAction();
}
//////////////////////////////////////////////////////////////////////////////////////////
void SigninForm::showGoldCreateAction()
{
	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

	if (m_iCountGold > 0)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GOLDCHUXIAN);
	}

	Vec2 vecGoldPos = ccp(winSize.width*0.5 - 100, winSize.height*0.5 + 100);
	float initY = -150;

	for (int i = 0; i < glob; i++)
	{
		auto pGoldImg = ImageView::create("res/common/common_button_gold.png");
		pGoldImg->setPosition(vecGoldPos);
		this->addChild(pGoldImg, 13);
		pGoldImg->setOpacity(0);
		pGoldImg->setTag(Gold_IMG_Tag + i);

		Vec2 vecMove;
		randomCreateGoldmove(vecMove.x, vecMove.y);
		auto move1 = MoveBy::create(0.1f, vecMove);
		auto move2 = MoveBy::create(0.05f, ccp(0, 20));
		auto seq = Sequence::create(Spawn::create(FadeIn::create(0.1f), move1, NULL), move2, NULL);
		pGoldImg->runAction(seq);
	}

	this->scheduleOnce(schedule_selector(SigninForm::showGoldMoveupAction), 0.5f);
}

void SigninForm::showGoldMoveupAction(float dt)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	count_glob = pPlayer->getCurrGold();
	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	Vec2 vecMoveTo = ((SelectForm*)this->getParent())->m_pMenuControl->getGoldImgWorldPos();
	float t;
	if (m_iCountGold >= CREAT_GLOB)
	{
		t = (float)3 / (float)glob;
	}
	else
	{
		t = 0.06;
	}

	for (int i = 0; i < glob; i++)
	{
		auto pGoldImg = this->getChildByTag(Gold_IMG_Tag + i);

		auto move1 = MoveBy::create(0.1f, ccp(0, -10));
		auto move2 = MoveTo::create(0.15f, vecMoveTo);
		auto scale = ScaleTo::create(0.15f, 1.0);
		auto spawn = Spawn::create(move2, scale, NULL);

		auto call_func = CCCallFuncND::create(this, callfuncND_selector(SigninForm::showGoldPlusAction), (void*)i);
		auto seq = Sequence::create(DelayTime::create((i*t)), CallFunc::create(this, callfunc_selector(SigninForm::playGoldMoveupSound)), move1, spawn, call_func, NULL);
		pGoldImg->runAction(seq);
	}
}

void SigninForm::playGoldMoveupSound()
{
	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GOLDFEIRU);
}

void SigninForm::showGoldPlusAction(Node* node, void* ivoid)
{
	auto iCurr = ((int)ivoid);

	if (m_iCountGold >= CREAT_GLOB)
	{
		creat_glob = m_iCountGold - glob;
	}
	else
	{
		creat_glob = 0;
	}

	m_pCountLayout->setVisible(true);
	m_pCountText->setString(sup::SupString::int2String((iCurr + 1) + creat_glob));

	auto pGoldImg = this->getChildByTag(Gold_IMG_Tag + iCurr);
	pGoldImg->removeFromParentAndCleanup(true);
	pGoldImg = NULL;

	auto scale1 = ScaleTo::create(0.02f, 0.8f);
	auto scale2 = ScaleTo::create(0.02f, 1.5f);
	auto scale3 = ScaleTo::create(0.02f, 1.0f);

	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GOLDZENGJIA);
	auto seq = Sequence::create(scale1, scale2, scale3, NULL);

	if ((iCurr + 1) + creat_glob == m_iCountGold)
	{
		seq = Sequence::create(scale1, scale2, scale3, DelayTime::create(0.1f), CallFunc::create(this, callfunc_selector(SigninForm::hideGoldPlusAction)), NULL);
	}
	m_pCountLayout->runAction(seq);
	((SelectForm*)this->getParent())->m_pMenuControl->setGoldTotalSum(count_glob + (iCurr + 1) + creat_glob);
}

void SigninForm::hideGoldPlusAction()
{
	m_pCountLayout->setVisible(false);
	UIMask*la = (UIMask*)this->getChildByTag(REMOVE_GAME_CENG);
	if (la != nullptr)
	{
		this->removeChild(la, 20);
		UserDefault::getInstance()->setIntegerForKey(STATUE_TOUCH, 1);
		UserDefault::getInstance()->flush();
	}
}

void SigninForm::randomCreateGoldmove(float& x, float& y)
{
	float init_y = -150;
	int fMax = 100;

	int ix = CCRANDOM_0_1() * (fMax);
	int iy = CCRANDOM_0_1() * fMax;

	x = fMax - ix;
	if (x > 0)
	{
		x += 50;
	}
	else
	{
		x -= 50;
	}

	y = init_y - iy;
}

//////////////////////////////////////////////////////////