#include "BabyControl.h"
#include "../UIFactory.h"
#include "Entity/ItemFactory.h"
#include "Entity/MonsterFactory.h"


BabyControl::BabyControl():
Form(IDC_Player)
, m_eExpression(EBabyExpression_Daiji)
, type(-1)
, m_iIdleStatus(EBabyExpression_Null)
, m_bCurTouch(false)
{
}

BabyControl::~BabyControl()
{

}

bool BabyControl::init()
{
	if (Form::init())
	{
		m_pLayout = (Layout*)CSLoader::createNode("Player.csb");
		this->addChild(m_pLayout);

		m_Player = EntityMgr::instance()->pPlayer();

		if (m_Player->getCurrRoomType() == ELevel_DressRoom)
		{
			m_pAniPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_pos"));

		}
		else if (m_Player->getCurrRoomType() == ELevel_MuyuRoom)
		{
			m_pAniPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_muyu"));
		}
		else if (m_Player->getCurrRoomType() == ELevel_WanjuRoom)
		{
			m_pAniPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_pos"));

		}
		else if (m_Player->getCurrRoomType() == ELevel_BabyRoom)
		{
			m_pAniPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_woshi"));

		}

		m_pAniPanel->setPosition(ccp(m_pAniPanel->getPositionX()*SUP_SCALE_X, m_pAniPanel->getPositionY()*SUP_SCALE_Y));

		//m_vecInitPos = m_pAniPanel->getPosition();

		anipiss = dynamic_cast<Sprite*>(m_pLayout->getChildByName("ani_piss"));
		anipiss->setPosition(ccp(anipiss->getPositionX()*SUP_SCALE_X, anipiss->getPositionY()*SUP_SCALE_Y));

		m_pShouPanel = dynamic_cast<Layout*>(m_pLayout->getChildByName("Panel_shou"));
		m_pShouPanel->setPosition(ccp(m_pShouPanel->getPositionX()*SUP_SCALE_X, m_pShouPanel->getPositionY()*SUP_SCALE_Y));
		m_pShouPanel->setVisible(false);



		EGameRole m_curPlayerID = m_Player->getCurrRoleId();
		

		if (m_curPlayerID < 3)
		{
			tmpid = m_curPlayerID + 1;
		}
		else
		{
			tmpid = m_curPlayerID - 2;
		}
	
		initActionFile();

		spSkeleton* _skeleton = m_sktRoleAni->getspSkeleton();
		for (int i = 0; i < _skeleton->slotsCount; ++i)
		{
			slot = _skeleton->slots[i];
			if (slot->data->attachmentName == NULL)
			{
				continue;
			}
			m_vecSlots.push_back(slot->data->name);
			m_vecAttachments.push_back(slot->data->attachmentName);
		}

		for (int i = 0; i < m_vecSlots.size(); i++)
		{
			string a = SupUtils::SplitString_Slots(m_vecAttachments[i]);
			string b = m_vecAttachments[i];
			if (strcmp(a.c_str(), b.c_str()) == 0)
			{
				continue;
			}
			char tmpChar[32];
			//itoa(tmpid, tmpChar,10);
			snprintf(tmpChar, sizeof(tmpChar), "%d", tmpid);
			string strimg = "0";
			strimg.append(tmpChar);
			strimg.append(SupUtils::SplitString_Slots(m_vecAttachments[i]));
			strimg.append(".png");
			//+std::to_string(tmpid) + SupUtils::SplitString_Slots(m_vecAttachments[i]) + ".png";
			Image* image = new Image;
			std::string str;
			if (EntityMgr::instance()->pPlayer()->getCurrRoleType() == 1)
			{
				str = "res/Plist/girl/" + strimg;
			}
			else
			{
				str = "res/Plist/boy/" + strimg;
			}
			image->initWithImageFile(str.c_str());
			Texture2D* pTexture = new Texture2D();
			pTexture->initWithImage(image);
			m_sktRoleAni->changeAttachment(m_vecSlots[i].c_str(), m_vecAttachments[i].c_str(), pTexture);
		}

		return true;

	}
	return false;
}


void BabyControl::initActionFile()
{
	type = m_Player->getCurrRoleType();
	auto curRole = m_Player->getCurrRole();
	if (NULL != curRole)
	{
		auto id = curRole->getBabyAniID(EBabyExpression_Daiji);
		RoleAni* pAni = m_Player->getRoleAniList()->getAniByID(id);
		if (type == 1)
		{
			EntityMgr::instance()->pPlayer()->setCurrRoleType(1);
		}
		else
		{
			EntityMgr::instance()->pPlayer()->setCurrRoleType(0);
		}
		if (pAni != NULL)
		{
			m_vecJson = pAni->getAniJsonPool(type);
			m_vecAtlas = pAni->getAniAtlasPool(type);
			m_aniName = pAni->getAniName();
		}
		m_sktRoleAni = SkeletonAnimation::createWithFile(m_vecJson[m_vecJson.size() - 1], m_vecAtlas[m_vecAtlas.size() - 1], 1.0f);
		m_sktRoleAni->setAnimation(0, m_aniName, true);
		m_sktRoleAni->update(0);
		m_pAniPanel->addChild(m_sktRoleAni, 1);
		m_sktRoleAni->setPosition(Vec2::ZERO);
	}
}

void BabyControl::playRoleAnimation(EBabyExpression type, bool loop)
{
	//m_sktRoleAni->setToSetupPose();
	bool tmpbool = EntityMgr::instance()->pPlayer()->getisRoleAniLoop();
	Player* m_pPlayer = EntityMgr::instance()->pPlayer();
	string aniName = m_pPlayer->getRoleAniName(type);
	//this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([this, aniName,loop](){

		m_sktRoleAni->setAnimation(0, aniName, loop);
		updateRoleSkin();

	
		m_sktRoleAni->setEventListener([=](int trackIndex, spEvent* event){
			if (tmpbool == false)
			{
				if (m_Player->getisSleeping() == true)
				{
					return;
				}
				spTrackEntry* entry = spAnimationState_getCurrent(m_sktRoleAni->getState(), trackIndex);
				const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
				log("event->data->name:    %s", event->data->name);
				if (0 == strcmp(event->data->name, "daiji"))
				{
					if (refreshIdleStatus())
					{
						auto id = m_Player->getCurrRole()->getBabyAniID(m_iIdleStatus);
						RoleAni* pAni = m_Player->getRoleAniList()->getAniByID(id);
						m_sktRoleAni->setAnimation(0, pAni->getAniName(), true);
						updateRoleSkin();
					}
				}
			}
		}
		);
		/*	}
			), NULL));*/

}

bool BabyControl::refreshIdleStatus()
{
	auto pPlayer = EntityMgr::instance()->pPlayer();
	if (pPlayer->getisSleeping())
	{
		return false;
	}
	m_iIdleStatus = EBabyExpression_Daiji;
	return true;

}

void BabyControl::stopRoleAnimation()
{
	m_sktRoleAni->setToSetupPose();
}


void BabyControl::ReplaceRoleSkeletonSkin(const char* skin, const char* attachment, const std::string& spriteFrameName)
{
	Image* image = new Image;
	std::string str = "res/Plist/dress/" + spriteFrameName;
	image->initWithImageFile(str.c_str());
	Texture2D* pTexture = new Texture2D();
	pTexture->initWithImage(image);
	m_sktRoleAni->changeAttachment(skin, attachment, pTexture);
	spSlot*  m_pspSlot = m_sktRoleAni->findSlot(skin);
	m_pspSlot->a = 1;
}

void BabyControl::ReplaceZhiNiaoKu(const std::string& spriteFrameName)
{
	Image* image = new Image;
	image->initWithImageFile(spriteFrameName.c_str());
	Texture2D* pTexture = new Texture2D();
	pTexture->initWithImage(image);

	if (EntityMgr::instance()->pPlayer()->getCurrRoleType() == 0)
	{
		m_sktRoleAni->changeAttachment("man_zhiniaoku", "man_zhiniaoku", pTexture);
	}
	else
	{
		m_sktRoleAni->changeAttachment("women_zhiniaoku", "women_zhiniaoku", pTexture);
	}
}

void BabyControl::initZhiniukuAction()
{
	m_pTimeLine = CSLoader::createTimeline("Player.csb");
	m_pLayout->runAction(m_pTimeLine);
	m_pTimeLine->gotoFrameAndPause(0);
	m_pTimeLine->play("ani_piss_01", false);
}

void BabyControl::refreshZhiniukuAction()
{
	m_pTimeLine = CSLoader::createTimeline("Player.csb");
	anipiss->runAction(m_pTimeLine);
	m_pTimeLine->gotoFrameAndPause(0);
	m_pTimeLine->play("ani_piss_02", false);
	playRoleAnimation(EBabyExpression_Gaoxing,false);
	EntityMgr::instance()->pPlayer()->setisRoleAniLoop(false);
}

void BabyControl::updateRoleSkin()
{
	for (int i = 0; i < m_vecSlots.size(); i++)
	{
		string a = SupUtils::SplitString_Slots(m_vecAttachments[i]);
		string b = m_vecAttachments[i];
		if (strcmp(a.c_str(), b.c_str()) == 0)
		{
			continue;
		}
		char tmpChar[32];
		//itoa(tmpid, tmpChar, 10);
		snprintf(tmpChar, sizeof(tmpChar), "%d", tmpid);
		string strimg = "0";
		strimg.append(tmpChar);
		strimg.append(SupUtils::SplitString_Slots(m_vecAttachments[i]));
		strimg.append(".png");
		//string strimg = "0" + to_string(tmpid) + SupUtils::SplitString_Slots(m_vecAttachments[i]) + ".png";
		Image* image = new Image;
		std::string str;
		if (EntityMgr::instance()->pPlayer()->getCurrRoleType() == 1)
		{
			str = "res/Plist/girl/" + strimg;
		}
		else
		{
			str = "res/Plist/boy/" + strimg;
		}
		image->initWithImageFile(str.c_str());
		Texture2D* pTexture = new Texture2D();
		pTexture->initWithImage(image);
		m_sktRoleAni->changeAttachment(m_vecSlots[i].c_str(), m_vecAttachments[i].c_str(), pTexture);
	}
}
