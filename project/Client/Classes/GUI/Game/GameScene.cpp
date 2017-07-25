#include "GameScene.h"
#include "BabyCare.h"
#include "../UIFactory.h"
#include "SDK/SupSDK.h"


GameScene::GameScene(void)
{

}

GameScene::~GameScene(void)
{
	EntityMgr::instance()->pPlayer()->releaseMonsterList();
}

bool GameScene::init()
{
	if (Scene::init())
	{
		auto pPlayer = EntityMgr::instance()->pPlayer();
		for (int i = 0; i < EItem_Max; i++)
		{
			pPlayer->setItemUse(i, EItemUseType_Normal);
		}
		pPlayer->getMonsterList()->initMonsterList();

		GameUIInit();
		return true;
	}
	return false;
}

void GameScene::GameUIInit()
{
	m_pGameForm = NULL;

	auto eCurrRoomType = EntityMgr::instance()->pPlayer()->getCurrRoomType();

	m_pBgForm = UIFactory::instance()->showBackgroundForm(eCurrRoomType);

	if (NULL != m_pBgForm )
	{
		this->addChild(m_pBgForm, 1);
	}
	
	switch (eCurrRoomType)
	{
	case ELevel_BabyRoom:
	{
							m_pGameForm = UIFactory::instance()->showBabyRoomForm();
							break;
	}
	case ELevel_WanjuRoom:
	{
							m_pGameForm = UIFactory::instance()->showToyRoomForm();
							break;
	}
	case ELevel_DiningRoom:
	{
							m_pGameForm = UIFactory::instance()->showDiningRoomForm();
							break;
	}
	case ELevel_MuyuRoom:
	{
							m_pGameForm = UIFactory::instance()->showMuyuRoomForm();
							break;
	}
	case ELevel_DressRoom:
	{
							m_pGameForm = UIFactory::instance()->showDressForm();
							break;
	}
	default:
		break;
	}

	if (NULL != m_pGameForm)
	{
		this->addChild(m_pGameForm,2);
	}

	Form* pPlayerForm = NULL;
	pPlayerForm = UIFactory::instance()->showPlayerForm();
	m_PlayerLayer = (BabyControl*)pPlayerForm;
	if (NULL != pPlayerForm)
	{
		this->addChild(pPlayerForm, 3);
	}

	m_pMenuControl = MenuControl::createInst();
	this->addChild(m_pMenuControl, 10);

	//SupSDK::instance()->HideNativeAd();
}

GameScene* GameScene::create()
{
	auto ret = new GameScene();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

Form* GameScene::getGameForm()
{
	return m_pGameForm;
}

Form* GameScene::getBgForm()
{
	return m_pBgForm;
}



