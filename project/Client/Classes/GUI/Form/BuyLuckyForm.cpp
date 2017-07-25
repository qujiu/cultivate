
/*
** declare BuyLuckyForm
** author: zhangchao;
** date: 2014.10.09
*/

#include "BuyLuckyForm.h"
#include "SDK/SupSDK.h"
#include "Entity/EntityMgr.h"
#include "SaveManager/SaveManage.h"
#include "../UIManager.h"
#include "../../BabyCare.h"
#include "../UIFactory.h"
#include "MenuControl.h"



BuyLuckyForm::BuyLuckyForm(int iGoldSum, int iID) :
Form(IDC_BuyLucky)
, m_bClickBuyItem(true)
{
	m_iGoldSum = iGoldSum;
	m_iID = iID;
}

BuyLuckyForm::~BuyLuckyForm()
{

}

bool BuyLuckyForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);

		Player* pPlayer = EntityMgr::instance()->pPlayer();

		m_pLayout = (Layout*)CSLoader::createNode("buyTip.csb");
		this->addChild(m_pLayout);

		m_pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBkImage = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_bg"));
		m_pBkImage->setPosition(ccp(m_pBkImage->getPositionX()*SUP_SCALE_X, m_pBkImage->getPositionY()*SUP_SCALE_Y));

		auto pText = dynamic_cast<Text*>(m_pBkImage->getChildByName("Text_text"));

		auto pStarFishImg = dynamic_cast<ImageView*>(m_pBkImage->getChildByName("Image_starfish"));

		auto pGoldSum = dynamic_cast<TextAtlas*>(m_pBkImage->getChildByName("AtlasLabel_gold"));
		pGoldSum->setString(sup::SupString::int2String(m_iGoldSum));

		auto pYesBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_yes"));
		pYesBtn->addTouchEventListener(this, toucheventselector(BuyLuckyForm::onYesButtonClicked));

		auto pNoBtn = dynamic_cast<Button*>(m_pBkImage->getChildByName("Button_no"));
		pNoBtn->addTouchEventListener(this, toucheventselector(BuyLuckyForm::onNoButtonClicked));

		sup::SupActions::BulgeNode(m_pBkImage, 0.0f, 1.0f);

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANG);

		return true;
	}

	return false;
}

void BuyLuckyForm::onYesButtonClicked(Ref *sender, TouchEventType type)
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

		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANGSHOUHUI);

		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			auto pPlayer = EntityMgr::instance()->pPlayer();
			//尚未解锁，购买
			if (m_iGoldSum <= pPlayer->getCurrGold())
			{
				auto iNewGoldSum = pPlayer->getCurrGold() - m_iGoldSum;
				//	m_pMenuControl->setGoldTotalSum(iNewGoldSum);
				__NotificationCenter::getInstance()->postNotification(TOTAL_GLOB, (Ref*)(intptr_t)iNewGoldSum);//金币奖励动画
				__NotificationCenter::getInstance()->postNotification(ENOTIFY_AFTBUYPRICELUCKY, (Ref*)(intptr_t)m_iID);

				//rand();

				//NotificationCenter::getInstance()->postNotification(ENOTIFY_AFTERBUYITEMSUCCESSFUNC, __Integer::create(m_iID));
			}
			else
			{
				showMessageBoxID("Item3", MBCall(BuyLuckyForm::showStoreForm));
			}
			this->removeFromParentAndCleanup(true);
		})));

	}
}

void BuyLuckyForm::rand(){

	auto pPlayer = EntityMgr::instance()->pPlayer();

	int a = CCRANDOM_0_1() * 10;

	if (a < 3)//未抽中
	{
		log("kkkkk%d count%d", a, UserDefault::getInstance()->getIntegerForKey("count"));

	}
	else
	{//抽中
		int count = UserDefault::getInstance()->getIntegerForKey("count");
		log("kkkkk%d count%d", a, UserDefault::getInstance()->getIntegerForKey("count"));

		if (count >= 59)
		{
			int price = CCRANDOM_0_1() * 100;

			if (price <= 5 - 1)//抽中大包金币
			{

			}
			else if (price > 5 - 1 && price <= 35 - 1){//抽中中保金币


			}
			else if (price > 35 - 1 && price <= 100 - 1){//抽中小宝金币

			}
			log("kkkkk%dkkkkkkk", a);

		}
		else
		{

			int b = CCRANDOM_0_1() * 100;
			if (b <= 25 - 1){//抽中道具
				vector<int> vecPool;
				vector<int> vecPoolid;


				auto pPlayer = EntityMgr::instance()->pPlayer();
				vecPool = pPlayer->getRandomDataList()->getRandomDataByID(0)->getRLuckyPool();

				int a = vecPool.size();

				int index = CCRANDOM_0_1() * vecPool.size();
				int id = pPlayer->readLuckyID(index);

				//if (id == index)//id相同
				//{


				while (true)
				{
					/* int indexid = CCRANDOM_0_1() * vecPool.size();
					log("index = %d\n", indexid);
					int luckyid = pPlayer->readLuckyID(indexid);*/

					if (id != index)
					{
						//id不同

						pPlayer->saveLuckyID(index);
						break;
					}
				}

				//}
				//else//id不同
				//{


				//	pPlayer->saveLuckyID(index);


				//}

				log("kkkkk%d,uuuuuuuu%d,bbbbb%d", index, a, b);





			}
			else
			{////抽中金币
				int price = CCRANDOM_0_1() * 100;

				if (price <= 5 - 1)//抽中大包金币
				{

				}
				else if (price > 5 - 1 && price <= 35 - 1){//抽中中保金币
				}
				else if (price > 35 - 1 && price <= 100 - 1){//抽中小宝金币
				}
			}
		}
	}
}
void BuyLuckyForm::showStoreForm(MBCLICK_TYPE type, void* data)
{
	if (MBCLICK_YES == type)
	{
		auto *pForm = UIFactory::instance()->showStoreForm();
		if (NULL != pForm)
		{
			Director::getInstance()->getRunningScene()->addChild(pForm, 52);
		}
	}
}

void BuyLuckyForm::onNoButtonClicked(Ref *sender, TouchEventType type)
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

		//	SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_TANKUANGSHOUHUI);

		this->runAction(Sequence::createWithTwoActions(ease, CallFunc::create([this](){
			this->removeFromParentAndCleanup(true);
		})));
	}
}

