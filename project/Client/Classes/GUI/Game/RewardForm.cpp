#include "RewardForm.h"
#include "Entity/EntityMgr.h"
#include "BabyCare.h"
#include "GUI/UIFactory.h"

RewardForm::RewardForm(int type) :
Form(IDC_Reward)
, m_nCountGold(0)
{
	m_nAwardType = type;
}

RewardForm::~RewardForm()
{

}

bool RewardForm::init()
{
	if (Form::init())
	{
		showPlayPopAD(0.5f, false);
		m_pLayout = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("UI_Award.json"));
		this->addChild(m_pLayout, 1);

		auto pBg1 = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg_2"));
		SupLayout::setRelativePos(pBg1, pBg1->getPosition(), SUP_ALIGNMENT_LB, E_SUP_SCALE_X);

		auto pBg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		SupLayout::setRelativePos(pBg, pBg->getPosition(), SUP_ALIGNMENT_LB, E_SUP_SCALE_X);
		pBg->setCascadeOpacityEnabled(false);

		BulgeNode(pBg1, Vec2(.0f, 0.0f), Vec2(pBg1->getScaleX(), pBg1->getScaleY()), callfunc_selector(RewardForm::setRewardInfo));
		BulgeNode(pBg, Vec2(.0f, 0.0f), Vec2(pBg->getScaleX(), pBg->getScaleY()));

		auto pCloseButton = dynamic_cast<Button*>(Helper::seekWidgetByName(pBg, "Button_close"));
		pCloseButton->addTouchEventListener(this, toucheventselector(RewardForm::onCloseButtonClicked));

		auto pAwardGoldBg = dynamic_cast<ImageView*>(pBg->getChildByName("Image_gold_bg"));
		m_pAwardGold = dynamic_cast<TextAtlas*>(Helper::seekWidgetByName(pAwardGoldBg, "AtlasLabel_gold_text"));
		m_pGoldImg = dynamic_cast<ImageView*>(pAwardGoldBg->getChildByName("Image_gold"));

		m_pAwardGold->setStringValue(sup::SupString::int2String(m_nCountGold));

		for (int i = 0; i < 10; i++)
		{
			m_pKuangImg[i] = dynamic_cast<ImageView*>(pBg->getChildByName("Image_kuang_" + sup::SupString::int2String(i)));
			m_pKuangImg[i]->setVisible(false);

			m_pIconImg[i] = dynamic_cast<ImageView*>(pBg->getChildByName("Image_icon_" + sup::SupString::int2String(i)));
			m_pIconImg[i]->setVisible(false);

			m_pUseImg[i] = dynamic_cast<ImageView*>(m_pIconImg[i]->getChildByName("Image_use"));
			m_pUseImg[i]->setVisible(false);

			m_pGold[i] = dynamic_cast<TextAtlas*>(m_pIconImg[i]->getChildByName("AtlasLabel_gold"));
			m_pGold[i]->setVisible(false);

		}

		//setRewardInfo();
#define _GAME_START_PARTICLE_TAG_		100017
		auto particle = this->getChildByTag(_GAME_START_PARTICLE_TAG_);
		if (particle)
			particle->removeFromParent();
		particle = ParticleSystemQuad::create("Particles/yizu2.plist");
		particle->setPosition(ccp(SUP_DEFAULT_W*0.5, 50.0f));
		this->addChild(particle, 11);
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_GAME_Complete);
		return true;
	}
	return false;
}

void RewardForm::setRewardInfo()
{
	m_nIndex = 0;

	auto pPlayer = EntityMgr::instance()->pPlayer();
	auto pLevel = pPlayer->getLevelList()->getLevelByID(pPlayer->getCurrRoomType());

	auto vecID1 = pLevel->getReward1ID();
	auto vecID2 = pLevel->getReward2ID();

	auto vecID = vecID1;
	if (m_nAwardType == 1)
	{
		vecID = vecID2;
	}

	int i = 0;
	for (i = 0; i < vecID.size(); i++)
	{
		m_pIconImg[i]->setVisible(true);

		int id = vecID[i];
		auto pItem = pPlayer->getItemList()->getItemByID(id);
		m_pIconImg[i]->loadTexture(pItem->getImg(), Widget::TextureResType::PLIST);
		m_pIconImg[i]->setScale(0.1f);
		m_pIconImg[i]->runAction(ScaleTo::create(0.2f, 1.0f));

		m_pKuangImg[i]->setVisible(true);
		m_pKuangImg[i]->setScale(0.0f);
		m_pKuangImg[i]->runAction(Sequence::create(ScaleTo::create(0.3f, 1.05f), ScaleTo::create(0.2f, 0.95f), ScaleTo::create(0.1f, 1.0f), NULL));

		if (EItemUseType_Complete == pPlayer->getItemUse(id))
			//if(1)
		{
			m_nGold[i] = pItem->getAward();
			runGoldAction(i, m_nIndex);
			m_nIndex++;
		}
	}

	int nLevel = pPlayer->getCurrRoomType();
	if (nLevel == ELevel_BabyRoom)
	{
		m_pIconImg[i]->setVisible(true);
		m_pIconImg[i]->loadTexture("ui_item_YiFu_0" + sup::SupString::int2String(pPlayer->getClothesIndex() + 1) + ".png", Widget::TextureResType::PLIST);
		m_pIconImg[i]->setScale(0.1f);
		m_pIconImg[i]->runAction(ScaleTo::create(0.2f, 1.0f));
		m_pKuangImg[i]->setVisible(true);
		m_pKuangImg[i]->setScale(0.0f);
		m_pKuangImg[i]->runAction(Sequence::create(ScaleTo::create(0.3f, 1.05f), ScaleTo::create(0.2f, 0.95f), ScaleTo::create(0.1f, 1.0f), NULL));
		m_nGold[i] = 10;
		runGoldAction(i, m_nIndex);
		m_nIndex++;
	}
	else if (nLevel == ELevel_DiningRoom)
	{
		if (m_nAwardType == 0)
		{
			m_pIconImg[i]->setVisible(true);
			m_pIconImg[i]->loadTexture("ani_item_bolishuibei_xiao.png", Widget::TextureResType::PLIST);
			m_pIconImg[i]->setScale(0.1f);
			m_pIconImg[i]->runAction(ScaleTo::create(0.2f, 1.0f));
			m_pKuangImg[i]->setVisible(true);
			m_pKuangImg[i]->setScale(0.0f);
			m_pKuangImg[i]->runAction(Sequence::create(ScaleTo::create(0.3f, 1.05f), ScaleTo::create(0.2f, 0.95f), ScaleTo::create(0.1f, 1.0f), NULL));

			m_nGold[i] = 5;
			runGoldAction(i, m_nIndex);
			m_nIndex++;
			i++;
		}


		i--;
		for (int j = 0; j < 3; j++)
		{
			i++;
			m_pIconImg[i]->setVisible(true);
			int ID = pPlayer->getTargetFoods().foods[j];
			m_pIconImg[i]->loadTexture(pPlayer->getFoodsList()->getFoodsByID(ID)->getImg(), Widget::TextureResType::PLIST);
			m_pIconImg[i]->setScale(0.1f);
			m_pIconImg[i]->runAction(ScaleTo::create(0.2f, 1.0f));
			m_pKuangImg[i]->setVisible(true);
			m_pKuangImg[i]->setScale(0.0f);
			m_pKuangImg[i]->runAction(Sequence::create(ScaleTo::create(0.3f, 1.15f), ScaleTo::create(0.3f, 0.85f), ScaleTo::create(0.1f, 1.0f), NULL));

			for (int k = 0; k < 3; k++)
			{
				if (pPlayer->getSelFoods().foods[k] == ID)
				{
					m_nGold[i] = 5;
					runGoldAction(i, m_nIndex);
					m_nIndex++;
					break;
				}
			}
		}
	}
}

void RewardForm::runGoldAction(int nIndex, int t)
{

	m_pUseImg[nIndex]->setVisible(true);
	m_pUseImg[nIndex]->setScale(0.0f);
	auto scaleTo = ScaleTo::create(0.3f, 1.0f);
	auto spawn = Spawn::create(scaleTo, NULL);
	auto seq = Sequence::create(DelayTime::create(0.3f*t + 1.3f), spawn, NULL);
	m_pUseImg[nIndex]->runAction(seq);

	m_pGold[nIndex]->setVisible(true);
	m_pGold[nIndex]->setStringValue(sup::SupString::int2String(m_nGold[nIndex]));
	m_pGold[nIndex]->setScale(0.0f);
	auto seq1 = Sequence::create(DelayTime::create(0.3f*t + 1.3f), ScaleTo::create(0.3f, 1.0f), NULL);
	m_pGold[nIndex]->runAction(seq1);

	m_nCountGold += m_nGold[nIndex];

	auto pGoldImg = ImageView::create("Ani_jinbi.png", Widget::TextureResType::PLIST);
	m_pIconImg[nIndex]->getParent()->addChild(pGoldImg);
	pGoldImg->setPosition(ccp(100, 0) + m_pIconImg[nIndex]->getPosition());
	pGoldImg->setOpacity(0);
	auto action = Spawn::create(FadeIn::create(0.1f), MoveBy::create(0.1f, ccp(0, 10.0f)), NULL);
	auto vec = m_pGoldImg->convertToWorldSpaceAR(Vec2::ZERO);
	auto vec1 = pGoldImg->getParent()->convertToNodeSpace(vec);

	pGoldImg->runAction(
		Sequence::create(DelayTime::create(t*0.3f + 1.3f),
		action,
		MoveTo::create(0.3f, vec1),
		__CCCallFuncND::create(this, callfuncND_selector(RewardForm::runGoldActionCallback), &m_nGold[nIndex]),
		CallFunc::create(pGoldImg, callfunc_selector(RewardForm::removeFromParent)),
		NULL));
}


void RewardForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		auto pBg1 = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg_2"));

		auto pBg = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));

		auto spawn = Spawn::create(ScaleTo::create(0.4f, 0.0f), RotateTo::create(0.4f, 90), NULL);
		//auto action = Sequence::create(spawn, );
		pBg1->runAction(Sequence::create(spawn->clone(), CallFunc::create([this](){
			EntityMgr::instance()->pPlayer()->setPlayerGold(m_nCountGold);
			//NotificationCenter::getInstance()->postNotification(NOT_FORM_AWARD_CLOSE);
			this->removeFromParentAndCleanup(true);
			auto pForm = UIFactory::instance()->showWellDoneForm();
			if (NULL != pForm)
			{
				BabyCare::instance()->getCurrScene()->addChild(pForm, 20);
			}

		}), NULL));

		pBg->runAction(spawn->clone());

	}
}

void RewardForm::runGoldActionCallback(Node* node, void* num)
{
	//node->removeFromParentAndCleanup(true);
	//int n = ((Item*)num)->getAward();
	int n = *((int*)num);
	n += sup::SupString::string2Int(m_pAwardGold->getStringValue());
	m_pAwardGold->setStringValue(sup::SupString::int2String(n));
	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Gold_add);
}