
#include "ZoomForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "Entity/MonsterFactory.h"
#include "ZuiForm.h"
#include "../UIManager.h"
#include "MuyuRoomForm.h"
#include "Entity/MonsterWidget.h"

ZoomForm::ZoomForm() :
Form(IDC_Zoom)
{

}

ZoomForm::~ZoomForm()
{

}

bool ZoomForm::init()
{
	if (Form::init())
	{
		auto pBg = ImageView::create("res/ui/zoom/xueban_di.jpg", TextureResType::LOCAL);

		pBg->setPosition(ccp(m_winSize.width*0.5f, m_winSize.height*0.5f));
		pBg->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pLayout = static_cast<Widget*>(CSLoader::createNode("Panel_Zoom.csb"));

		this->addChild(m_pLayout, 1);
		m_pLayout->addChild(pBg, 1);

		auto pReturnBtn = dynamic_cast<Button*>(m_pLayout->getChildByName("ben_return"));
		pReturnBtn->addTouchEventListener(this, toucheventselector(ZoomForm::onNextButtonClicked));
		SupLayout::setRelativePos(pReturnBtn, pReturnBtn->getPosition(), SUP_ALIGNMENT_LB);

		auto pFangdaqi = dynamic_cast<ImageView*>(m_pLayout->getChildByName("Image_fandapian"));
		pFangdaqi->setPositionX(pFangdaqi->getPositionX()*SUP_SCALE_X);
		pFangdaqi->setZOrder(2);
		auto pGeceng = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_geceng"));
		pGeceng->setPositionX(pGeceng->getPositionX()*SUP_SCALE_X);
		auto pBackImage = ImageView::create("res/ui/zoom/black_bg.png", Widget::TextureResType::LOCAL);
		pBackImage->setPosition(ccp(m_winSize.width*0.5f, m_winSize.height*0.5f));
		pBackImage->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		MonsterList::MonsterType* pMonsterType = EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EMonsterScene_Zoom);
		if (NULL != pMonsterType)
		{
			Vec2 vec[6][3] = {
				{ Vec2(80, -280), Vec2(200, 300), Vec2(-280, -20) },
				{ Vec2(-340, -160), Vec2(440, -100), Vec2(-100, 260) },
				{ Vec2(-300, -140), Vec2(220, -180), Vec2(80, 320) },
				{ Vec2(-320, 60), Vec2(220, 320), Vec2(100, -380) },
				{ Vec2(200, -220), Vec2(140, 280), Vec2(-340, -60) },
				{ Vec2(240, -120), Vec2(180, 220), Vec2(-420, -100) }
			};
			for (MonsterList::MonsterTypeIter pTypeIter = pMonsterType->begin(); pTypeIter != pMonsterType->end(); pTypeIter++)
			{
				MonsterList::Monsters* pMonsters = pTypeIter->second;
				for (MonsterList::MonstersIter Iter = pMonsters->begin(); Iter != pMonsters->end(); Iter++)
				{
					auto pMonster = MonsterFactory::instance()->Create(*Iter);
					pBg->addChild(pMonster, 10);
					pMonster->setPosition((*Iter)->getMPos());
					int index = (*Iter)->getMRotation();

					int rand1 = CCRANDOM_0_1() * 11 + 5;
					int rand2 = CCRANDOM_0_1() * 11 + 5;
					int rand3 = CCRANDOM_0_1() * 11 + 5;
					auto moveAct1 = MoveBy::create(0.1f*rand1, vec[index][0]);
					auto moveAct2 = MoveBy::create(0.1f*rand2, vec[index][1]);
					auto moveAct3 = MoveBy::create(0.1f*rand3, vec[index][2]);
					pMonster->runAction(RepeatForever::create(Sequence::create(moveAct1, moveAct2, moveAct3, NULL)));

					pMonster->getImage()->setTouchEnabled(true);
					pMonster->getImage()->addTouchEventListener(this, toucheventselector(ZoomForm::onXiJunButtonClicked));
					pMonster->getImage()->setTag((*Iter)->getMID());
				}
			}
		}


		{
			m_pDrawNode = DrawNode::create();
			m_pDrawNode->setAnchorPoint(ccp(0.0, 0.0));
			ccColor4F yellow(1, 1, 0, 1);
			float radiusX = pFangdaqi->getContentSize().width * .5f * .93f;
			float radiusY = pFangdaqi->getContentSize().height * .5f * .92f;
			const int count = 200;
			const float angel = 2.0f * (float)M_PI / count;
			Vec2 circles[count];
			for (int i = 0; i < count; ++i)
			{
				float radian = i * angel;
				circles[i].x = radiusX * cosf(radian);// -layout_pos.x;
				circles[i].y = radiusY * sinf(radian);// -layout_pos.y;
			}
			m_pDrawNode->drawPolygon(circles, count, yellow, 0, yellow);
			m_pDrawNode->setPosition(pFangdaqi->convertToWorldSpaceAR(Vec2::ZERO));

			m_pClippingNode = ClippingNode::create();
			m_pClippingNode->setContentSize(m_winSize);
			m_pClippingNode->setAnchorPoint(ccp(0.5, 0.5));
			m_pClippingNode->setPosition(ccp(m_winSize.width*0.5f, m_winSize.height*0.5f));//(ccpMult(ccpFromSize(pBackImage->getContentSize()), 0.5f));
			m_pClippingNode->setInverted(true);
			m_pClippingNode->addChild(pBackImage);
			m_pClippingNode->setStencil(m_pDrawNode);
			pGeceng->addChild(m_pClippingNode);

		}

		return true;
	}
	
	return false;
}


void ZoomForm::onNextButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		ButtonAction((Node*)sender);
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
		((Node*)sender)->setScale(1.0f);
		BabyCare::instance()->getCurrScene()->removeChild(this);
	}
}

void ZoomForm::onXiJunButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
		int tag = ((Node*)sender)->getTag();
		auto call_func = CallFuncN::create(this, callfuncN_selector(ZoomForm::onHitComplete));
		
		auto pMonster = dynamic_cast<MonsterBase*>(((Node*)sender)->getParent());
		pMonster->onHitStart(NULL, EGameItemProcessId_XiJun);

		if (pMonster->getDoneNum() == 0)
		{
			auto pMonsterList = EntityMgr::instance()->pPlayer()->getMonsterList();
			pMonsterList->removeMonster(pMonster->getMonster());
			pMonster->runAction(Sequence::create(DelayTime::create(1.0f), call_func, NULL));
		}
	}
}

void ZoomForm::onHitComplete(Node* node)
{
	node->removeAllChildrenWithCleanup(true);

	if (NULL == EntityMgr::instance()->pPlayer()->getMonsterList()->getMonsterType(EMonsterScene_Zoom))
	{
		EntityMgr::instance()->pPlayer()->setItemUse(EItem_FangDaJing, EItemUseType_Complete);
		auto pForm = dynamic_cast<ZuiForm*>(UIManager::instance()->findForm(IDC_Zui));;
		if (NULL != pForm)
		{
			pForm->removeYaZiMonster();
			BabyCare::instance()->getCurrScene()->removeChild(pForm);
		}
		auto pForm1 = dynamic_cast<MuyuRoomForm*>(UIManager::instance()->findForm(IDC_MuyuRoom));
		if (NULL != pForm1)
		{
			auto pItem = pForm1->getItemWidgetByIndex(EItem_YaShua);
			EntityMgr::instance()->pPlayer()->setItemUse(EItem_YaShua, EItemUseType_Complete);
			pItem->releaseYaogaoImg();
			pItem->setUserComplete();
		}
		BabyCare::instance()->getCurrScene()->removeChild(this);
	}
}