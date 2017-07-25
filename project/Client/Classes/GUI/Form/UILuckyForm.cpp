#include "UILuckyForm.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "../UIMask.h"
UILuckyForm::UILuckyForm() :
Form(IDC_Lucky)
, m_bClickBuyItem(true)
{
}

UILuckyForm::~UILuckyForm()
{
	m_Button.clear();
	m_baopo.clear();
	m_baoid.clear();
	m_baoglob.clear();
}

bool UILuckyForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		UIlucky = CSLoader::createNode("UIlucky.csb");
		this->addChild(UIlucky, 1);
		UserDefault::getInstance()->flush();

		m_pGeceng = dynamic_cast<Layout*>(UIlucky->getChildByName("Panel_geceng"));
		m_pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pBg = dynamic_cast<ImageView*>(UIlucky->getChildByName("Image_bg"));
		m_pBg->setPosition(ccp(m_pBg->getPositionX()*SUP_SCALE_X, m_pBg->getPositionY()*SUP_SCALE_Y));
		m_pBg->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_lclose = dynamic_cast<ImageView*>(UIlucky->getChildByName("Image_close"));

		m_lclose->setPosition(ccp(m_lclose->getPositionX()*SUP_SCALE_X, m_lclose->getPositionY()*SUP_SCALE_Y));
		m_lclose->addTouchEventListener(this, toucheventselector(UILuckyForm::onCloseButtonClicked));
		m_lclose->setTouchEnabled(true);

		for (int i = 1; i < 5; i++)
		{
			long long int a = random(90, 130);

			m_glod.push_back(a);
			auto pImg = dynamic_cast<Button*>(UIlucky->getChildByName("Button_" + sup::SupString::int2String(i)));
			pImg->setTag(i);
			pImg->addTouchEventListener(this, toucheventselector(UILuckyForm::onItemTouchListener));
			m_Button.push_back(pImg);
			auto pImg1 = dynamic_cast<ImageView*>(pImg->getChildByName("Image_bg_" + sup::SupString::int2String(i - 1)));
			pImg1->setZOrder(-1);
		}
		return true;
	}
	return false;
}

void UILuckyForm::ActionLuckySpecial(int iTag)
{
	UserDefault::getInstance()->setIntegerForKey(STATUE_TOUCH, 0);

	UserDefault::getInstance()->flush();

	m_lclose->setTouchEnabled(false);

	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	Point pos = ccp(winSize.width / 2, winSize.height / 2);

	png_id = iTag;
	Button* bu = m_Button[png_id - 1];
	for (int i = 0; i < m_Button.size(); i++)
	{
		results();
	}

	for (int i = 0; i < m_Button.size(); i++)
	{
		bu->setTouchEnabled(false);
		Button* bu = m_Button[i];
		Vec2 pos = bu->getPosition();
		bu->setVisible(false);

		if (bu->getTag() == png_id)
		{
			Actionte(bu->getPosition(), png_id);
			continue;
		}
		bu->setOpacity(150);
		Actionte(bu->getPosition(), i + 1);
	}
	auto id = m_baoid.at(png_id - 1);
	if (id == 1)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_BAOXIANGDAOJU);
	}
	if (id == 2)
	{
		SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_BAOXIANGJINBI);
	}
}

void UILuckyForm::ActionLucky(Ref* object)
{


}
void UILuckyForm::randomda(){

	vector<int> vecPool;

	auto pPlayer = EntityMgr::instance()->pPlayer();
	vecPool = pPlayer->getRandomDataList()->getRandomDataByID(0)->getRLuckyPool();
	int a = vecPool.size();
	for (int i = 1; i < a; i++)
	{
		int index = i;
		int luckyId = pPlayer->getLuckyDateList()->getLuckyByID(index)->getItemsubID();
		int id = pPlayer->readLuckyID(index);
		if (id != index && !pPlayer->GetSubMenuItemStatusByID(luckyId))//id不同并且解锁
		{
			glob_count = luckyId;
			daoju_id = index;
			sound_id = 1;
			m_baoid.push_back(sound_id);
			m_baoglob.push_back(glob_count);
			UserDefault::getInstance()->setBoolForKey(strLuckxian.c_str(), true);
			UserDefault::getInstance()->flush();
			break;
		}
		if (index == a - 1)
		{
			int coun = random(40, 70);
			glob_count = coun;
			sound_id = 2;
			m_baoid.push_back(sound_id);
			m_baoglob.push_back(glob_count);
			UserDefault::getInstance()->setBoolForKey(strLuckxian.c_str(), true);
			UserDefault::getInstance()->flush();
		}

	}
}
void UILuckyForm::Actionte(Vec2 pos, int i){



	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

	m_pTimelineNode = CSLoader::createNode("res/common/LuckyAction.csb");
	m_pActionTimeline = CSLoader::createTimeline("res/common/LuckyAction.csb");

	auto img = (ImageView*)m_pTimelineNode->getChildByName("Image_1");
	auto img2 = (ImageView*)m_pTimelineNode->getChildByName("Image_2");
	auto img3 = (ImageView*)m_pTimelineNode->getChildByName("Image_3");
	m_lodao = (ImageView*)m_pTimelineNode->getChildByName("Image_4");
	img->loadTexture(CCString::createWithFormat("res/common/common_button_%d.png", i)->getCString());
	img2->loadTexture(CCString::createWithFormat("res/common/common_button_%d_%d.png", i, 0)->getCString());
	img3->loadTexture(CCString::createWithFormat("res/common/common_button_%d_%d.png", i, 1)->getCString());

	auto pParticle1 = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_2"));
	auto pParticle2 = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_1"));

	pParticle1->setVisible(false);
	pParticle1->setPositionType(ParticleSystem::PositionType::FREE);
	pParticle2->setPositionType(ParticleSystem::PositionType::FREE);
	pParticle2->setVisible(false);

	m_pTimelineNode->setPosition(pos);
	m_pTimelineNode->setVisible(true);
	m_pActionTimeline->play("animation0", false);

	UIlucky->addChild(m_pTimelineNode, 20);
	m_paction.push_back(m_pTimelineNode);
	m_baopo.push_back(m_lodao->getPosition());
	for (int i = 0; i < m_baopo.size(); i++)
	{
		auto m_node = m_paction.at(i);

		if (i != png_id - 1)
		{

			auto img = (ImageView*)m_node->getChildByName("Image_1");
			//img->setOpacity(150);
			img->runAction((FadeTo::create(4, 150)));

			auto img2 = (ImageView*)m_node->getChildByName("Image_2");
			//img2->setOpacity(150);
			img2->runAction((FadeTo::create(4, 150)));

			auto img3 = (ImageView*)m_node->getChildByName("Image_3");
			//img3->setOpacity(150);
			img3->runAction((FadeTo::create(4, 150)));

			//m_node->stopAllActions();
			m_node->setScale(0.8);
		}
		else
		{
			m_node->runAction(m_pActionTimeline);

		}
	}



	scheduleOnce(schedule_selector(UILuckyForm::LuckyJie), 2.0f);

}
void UILuckyForm::createglob(float dt){


	auto pemitter = this->getChildByTag(111);

	m_pTimelineNode->removeChild(pemitter);

	auto coun = m_baoglob.at(png_id - 1);
	if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//游戏中
	{
		__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)coun);//金币奖励动画


	}
	else
	{
		__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)coun);//金币奖励动画

	}


}
void UILuckyForm::createdaoju(float dt){

	auto pemitter = this->getChildByTag(111);

	m_pTimelineNode->removeChild(pemitter);


	auto coun = m_baoglob.at(png_id - 1);
	if (BabyCare::instance()->getCurrSceneID() == EScene_Game)
	{
		auto *pForm = UIFactory::instance()->showCongratsForm(coun);
		if (NULL != pForm)
		{
			Director::getInstance()->getRunningScene()->addChild(pForm, 20);
		}
	}
	else{

		__NotificationCenter::getInstance()->postNotification(NOT_DAOJU_LUCKY, (Ref*)(intptr_t)coun);//道具奖励动画

	}


}
void UILuckyForm::createwu(float dt){
	this->removeFromParentAndCleanup(true);
}
void UILuckyForm::randomGoldmove(float& x, float& y)
{
	float init_y = -100;
	int fMax = 50;

	int ix = CCRANDOM_0_1() * (fMax);
	int iy = CCRANDOM_0_1() * fMax;

	x = fMax - ix;
	y = init_y - iy;
}
void UILuckyForm::results(){

	auto pPlayer = EntityMgr::instance()->pPlayer();
	if (UserDefault::getInstance()->getBoolForKey(strLuckxian.c_str()) == false)
	{
		randomda();
	}
	else
	{
		{//抽中
			int count = UserDefault::getInstance()->getIntegerForKey("count");
			if (count >= LUCKY_ALL)
			{
				int price = CCRANDOM_0_1() * 99;
				sound_id = 2;
				if (price <= 4)//暴击
				{
					int coun = random(150, 300);
					glob_count = coun;
				}
				if (price > 4 && price <= 14)//抽中大包金币
				{
					int coun = random(100, 150);
					glob_count = coun;
				}
				else if (price > 14 && price <= 34){//抽中中保金币
					int coun = random(70, 100);
					glob_count = coun;
				}
				else if (price > 34 && price <= 99){//抽中小宝金币

					int coun = random(40, 70);
					glob_count = coun;
				}
				m_baoid.push_back(sound_id);
				m_baoglob.push_back(glob_count);
			}
			else
			{
				int b = CCRANDOM_0_1() * 100;
				if (b <= 25 - 1){//抽中道具
					vector<int> vecPool;
					auto pPlayer = EntityMgr::instance()->pPlayer();
					vecPool = pPlayer->getRandomDataList()->getRandomDataByID(0)->getRLuckyPool();
					int a = vecPool.size();
					int index = random(1, a);
					int luckyId = pPlayer->getLuckyDateList()->getLuckyByID(index)->getItemsubID();
					int id = pPlayer->readLuckyID(index);
					if (id != index && !pPlayer->GetSubMenuItemStatusByID(luckyId))//id不同并且解锁
					{

						glob_count = luckyId;
						daoju_id = index;
						sound_id = 1;
					}
					else{
						sound_id = 2;
						int coun = random(40, 70);
						glob_count = coun;
					}
					m_baoid.push_back(sound_id);
					m_baoglob.push_back(glob_count);
				}
				else
				{////抽中金币
					int price = CCRANDOM_0_1() * 99;
					sound_id = 2;
					if (price <= 4)//暴击
					{
						int coun = random(150, 300);
						glob_count = coun;
					}
					if (price > 4 && price <= 14)//抽中大包金币
					{
						int coun = random(100, 150);
						glob_count = coun;
					}
					else if (price > 14 && price <= 34){//抽中中保金币
						int coun = random(70, 100);
						glob_count = coun;
					}
					else if (price > 34 && price <= 99){//抽中小宝金币
						int coun = random(40, 70);
						glob_count = coun;
					}
					m_baoid.push_back(sound_id);
					m_baoglob.push_back(glob_count);
				}

			}

		}


	}

}
void UILuckyForm::creatglobfu(){

	{
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
		auto img3 = (ImageView*)m_pTimelineNode->getChildByName("Image_3");
		for (int i = 0; i < 50; i++)
		{
			auto pGoldImg = ImageView::create("res/common/common_button_gold.png");
			Vec2 vecMove;
			randomGoldmove(vecMove.x, vecMove.y);
			pGoldImg->setPosition(ccp(m_lodao->getPositionX()*SUP_SCALE_X + vecMove.x + 100, m_lodao->getPositionY()*SUP_SCALE_Y + vecMove.y + 200));
			img3->addChild(pGoldImg, 50);
			pGoldImg->setOpacity(0);
			pGoldImg->setScale(0.5);
			pGoldImg->setTag(i + i);


			auto move2 = MoveBy::create(0.05f, ccp(0, 20));
			auto seq = Sequence::create(Spawn::create(FadeIn::create(0.1f), NULL), move2, NULL);
			pGoldImg->runAction(seq);
		}

	}

}
void UILuckyForm::LuckyJie(float dt){


	//auto pPlayer = EntityMgr::instance()->pPlayer();
	//for (int i = 0; i < m_baoid.size(); i++)
	//{
	//	auto maction = m_paction.at(i);
	//	auto id = m_baoid.at(i);
	//	auto coun = m_baoglob.at(i);

	//	if (i == png_id - 1)
	//	{
	//		auto imgli = (Layout*)maction->getChildByName("Panel_1_0");
	//		auto imgguan = (ImageView*)maction->getChildByName("Image_huo");


	//		auto pParticle1 = dynamic_cast<cocos2d::ParticleSystemQuad*>(m_pTimelineNode->getChildByName("Particle_2"));

	//		CCParticleSystemQuad* m_emitter = new CCParticleSystemQuad();
	//		std::string filename = "res/common/effect_ star1.plist";
	//		m_emitter->initWithFile(filename.c_str());
	//		m_emitter->setPosition(ccp(imgli->getPositionX(), imgli->getPositionY()));//设置发射粒子的位置
	//		m_emitter->setTag(111);
	//		m_emitter->setAutoRemoveOnFinish(true);//完成后制动移除



	//		//将粒子系统添加到节点(也可以直接将其添加到一个背景精灵CCSprite里面)
	//		m_emitter->setPositionType(ParticleSystem::PositionType::FREE);
	//		imgli->addChild(m_emitter, 1);
	//		if (id == 1)
	//		{

	//			auto img3 = (Layout*)maction->getChildByName("Panel_1_1");

	//			std::string name = pPlayer->getItemSubMenuList()->getItemSubMenuByID(coun)->getSIcon();

	//			auto sp = ImageView::create(name);
	//			//	sp->setPosition(ccp(img3->getPositionX()*SUP_SCALE_X, img3->getPositionY()*SUP_SCALE_Y));
	//			sp->setTag(9999);
	//			img3->addChild(sp, 20);
	//			this->scheduleOnce(schedule_selector(UILuckyForm::createdaoju), 7.0f);
	//			pPlayer->SetSubMenuItemStatusByID(coun, true);
	//			//pPlayer->saveLuckyID(daoju_id);
	//		}
	//		if (id == 2)
	//		{

	//			cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	//			auto img3 = (Layout*)maction->getChildByName("Panel_1");



	//			auto pGoldImg = ImageView::create("res/common/common_button_gold.png");
	//			//pGoldImg->setPosition(ccp(img3->getPositionX()+30, img3->getPositionY()));
	//			img3->addChild(pGoldImg, 50);
	//			pGoldImg->setScale(0.7);

	//			TextAtlas * textAtlas = TextAtlas::create("100", "res/achievement/common_shuzi.png", 50, 52, "0");
	//			textAtlas->setString(sup::SupString::int2String(coun));
	//			textAtlas->setScale(0.8);
	//			textAtlas->setPosition(ccp(pGoldImg->getPositionX() - (pGoldImg->getContentSize().width / 2) + 10, pGoldImg->getPositionY() + (pGoldImg->getContentSize().height / 2) - 10));
	//			pGoldImg->addChild(textAtlas, 60);
	//			this->scheduleOnce(schedule_selector(UILuckyForm::createglob), 7.0f);


	//			auto pjiaImg = ImageView::create("res/jiesuan/jiesuan_jia.png");
	//			pjiaImg->setScale(1.2);
	//			pjiaImg->setPosition(ccp(pGoldImg->getPositionX() - pGoldImg->getContentSize().width - 20, pGoldImg->getPositionY() + (pGoldImg->getContentSize().height / 2) - 10));
	//			pGoldImg->addChild(pjiaImg, 50);
	//		}

	//		continue;
	//	}
	//	else if (id == 1)

	//	{
	//		auto img3 = (Layout*)maction->getChildByName("Panel_1_1");
	//		std::string name = pPlayer->getItemSubMenuList()->getItemSubMenuByID(coun)->getSIcon();
	//		auto sp = ImageView::create(name);
	//		//sp->setPosition(ccp(img3->getPositionX()*SUP_SCALE_X - 50, img3->getPositionY()*SUP_SCALE_Y));
	//		sp->setTag(9999);
	//		img3->addChild(sp, 20);

	//		sp->setOpacity(0);
	//		sp->runAction((FadeIn::create(5)));

	//	}
	//	if (id == 2)
	//	{



	//		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	//		auto img3 = (Layout*)maction->getChildByName("Panel_1");





	//		auto pGoldImg = ImageView::create("res/common/common_button_gold.png");
	//		//	pGoldImg->setPosition(ccp(img3->getPositionX()*SUP_SCALE_X, img3->getPositionY()*SUP_SCALE_Y));
	//		img3->addChild(pGoldImg, 50);
	//		TextAtlas * textAtlas = TextAtlas::create("100", "res/achievement/common_shuzi.png", 50, 52, "0");
	//		textAtlas->setString(sup::SupString::int2String(coun));
	//		textAtlas->setPosition(ccp(pGoldImg->getPositionX() - (pGoldImg->getContentSize().width / 2) + 10, pGoldImg->getPositionY() + (pGoldImg->getContentSize().height / 2) - 10));


	//		auto pjiaImg = ImageView::create("res/jiesuan/jiesuan_jia.png");
	//		pjiaImg->setScale(1.2);

	//		pjiaImg->setPosition(ccp(pGoldImg->getPositionX() - pGoldImg->getContentSize().width - 20, pGoldImg->getPositionY() + (pGoldImg->getContentSize().height / 2) - 10));
	//		pGoldImg->addChild(pjiaImg, 50);
	//		pjiaImg->setOpacity(0);
	//		textAtlas->setOpacity(0);
	//		textAtlas->setScale(0.8);
	//		pGoldImg->addChild(textAtlas, 10);
	//		pGoldImg->setOpacity(0);
	//		pGoldImg->setScale(0.8);

	//		pGoldImg->runAction((FadeIn::create(5)));
	//		textAtlas->runAction((FadeIn::create(5)));
	//		pjiaImg->runAction((FadeIn::create(5)));

	//	}
	//}
	//this->scheduleOnce(schedule_selector(UILuckyForm::createwu), 7.0f);


}
void UILuckyForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		m_Button.clear();
		this->removeFromParentAndCleanup(true);

	}
}

void UILuckyForm::onCloseButtonCallback(Ref* object)
{

	this->removeFromParentAndCleanup(true);
}

void UILuckyForm::onBuyGoldButtonClicked(Ref *sender, TouchEventType type)
{

}
void UILuckyForm::onItemTouchListener(Ref* ref, TouchEventType type)
{
	Node* teg = (Node*)ref;
	if (TOUCH_EVENT_ENDED == type)
	{
		ActionLuckySpecial(teg->getTag());
	}
}


void UILuckyForm::enableClickBuy(float dt)
{
	m_bClickBuyItem = true;
}

void UILuckyForm::RefreshSubMenu()
{

}
