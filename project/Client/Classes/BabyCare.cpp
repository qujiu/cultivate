#include "BabyCare.h"

#include "GUI/Logo/LogoScene.h"
#include "GUI/Home/HomeScene.h"
#include "GUI/Select/SelectScene.h"
#include "GUI/Game/GameScene.h"
#include "ResManager/ConfigDataCenter.h"
#include "SaveManager/SaveManage.h"
#include "MiniGame/Miniutils/MiniGTools.h"
#include "MiniGame/MiniGame.h"
#include "SDK/SupSDK.h"
#include "SoundManager/SoundManage.h"


SINGLETON_DEFINE_INST(BabyCare);


BabyCare::BabyCare()
:m_eCurrSceneID(EScene_None)
, m_eFrontSceneID(EScene_None)
, m_pCurrScene(NULL)
{
}

BabyCare::~BabyCare()
{
	EntityMgr::release();
	ConfigDataCenter::release();
	SoundManage::release();
	SaveManage::release();
	if (SaveManage::instance()->getIntSave(SAVE_ID_INT_CUR_ROOM) == ELvel_Max - 1)
	{
		SaveManage::instance()->setIntSave(SAVE_ID_INT_CUR_ROOM, 0);
	}
}


void BabyCare::onGameInit()
{
	FileUtils::getInstance()->addSearchPath("res");
	this->onStartGame();

	MiniGTools::getInstance()->_isSoundEnabledCallback = [&](){
		return SoundManage::instance()->isSoundOn();
	};

	MiniGTools::getInstance()->_onShowNativeAdCallback = [](Rect rect, int type){
		SupSDK::instance()->showNativeWithRect(rect, type);
	};

	MiniGTools::getInstance()->_onShowLoadingNativeAdCallback = [&](){
		SupSDK::instance()->ShowNativeAdForLoading();
	};

	MiniGTools::getInstance()->_onHideNativeAdCallback = [&](){
		SupSDK::instance()->HideNativeAd();
	};

	MiniGTools::getInstance()->_isNativeAdLoadedCallback = [&](){
		return SupSDK::instance()->HaveNativeAd();
	};

	MiniGTools::getInstance()->_isRejectPopAndNativeCallback = [](){
		return !SupSDK::instance()->IsNativeWithPop();
	};

	MiniGTools::getInstance()->_onShowPopAdLoad1Callback = [](){
		SupSDK::instance()->showPopADBegin(true);
	};
	MiniGTools::getInstance()->_onShowPopAdLoad2Callback = [](){
		SupSDK::instance()->showPopADEnd(true);
	};

	MiniGTools::getInstance()->_isShowRandomPopAvailableCallback = [](){
		return SupSDK::instance()->CheckPopAdShow();
	};
	MiniGTools::getInstance()->_onEndShowPopAd2 = [](){
		if (SupSDK::instance()->CanPopAdShow())
		{
			SupSDK::instance()->ResetPopAdLimit();
		}
	};

	MiniGTools::getInstance()->_onHidePopAdLoadCallback = [&](){
		SupSDK::instance()->ExitAD();
	};

	MiniGTools::getInstance()->_onShowPopAdLoadCallback = [&](){
		SupSDK::instance()->showPopAD();
	};
}

void BabyCare::onStartGame()
{
	onStatusChanged(EScene_Logo);

}

void BabyCare::removeUnusedTextures()
{
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

	Director::getInstance()->getScheduler()->schedule([&](float dt){
		Director::getInstance()->getTextureCache()->removeUnusedTextures();
	}, this, 0.02f, 0, 0, false, "SCHEDULE_CLEAR");
}

//×´Ì¬»ú¿ØÖÆÓÎÏ·³¡¾°ÇÐ»»;
void BabyCare::onStatusChanged(ESceneID id)
{
	if (m_eCurrSceneID == id)
		return;

	switch (id)
	{
	case EScene_Logo:
	{
						auto scene = LogoScene::create();
						Director::getInstance()->runWithScene(scene);
						m_pCurrScene = scene;
	}
		break;
	case EScene_Home:
	{

						auto scene = HomeScene::create();
						Director::getInstance()->replaceScene(scene);
						m_pCurrScene = scene;
	}
		break;
	case EScene_Select:
	{
						  auto scene = SelectScene::create();
						  Director::getInstance()->replaceScene(scene);
						  m_pCurrScene = scene;
	}
		break;
	case EScene_Game:
	{
						auto scene = GameScene::create();
						Director::getInstance()->replaceScene(scene);
						m_pCurrScene = scene;
	}
		break;
	default:
		break;
	}
	m_eFrontSceneID = m_eCurrSceneID;
	m_eCurrSceneID = id;
}

void BabyCare::SetResultCallback_None()
{
	MiniGTools::getInstance()->SetResultCallback([this](int is_success){

		SupSDK::instance()->HideNativeAd();
		m_pCurrScene->runAction(Sequence::create(DelayTime::create(.0f), CallFunc::create([this, is_success](){
			SoundManage::instance()->stopMusic();
			SoundManage::instance()->playMusic(RES_SOUND_ID_MUSIC_HOME);
		}), NULL));
	});

}

void BabyCare::gotoMinigame()
{
	SupSDK::instance()->ShowUmEvent(MINIGAME_UM);
	Director::getInstance()->pushScene(MiniGame::loadMiniGame(true));
	SoundManage::instance()->stopMusic();
	MiniGTools::getInstance()->SetResultCallback([this](int is_success){
		SupSDK::instance()->HideNativeAd();
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		if (is_success == MiniGame::MiniGame_State_Success) {
			pPlayer->jiesuan();
		}
		m_pCurrScene->runAction(Sequence::create(DelayTime::create(.5f), CallFunc::create([this, pPlayer](){
			SoundManage::instance()->stopMusic();
			pPlayer->soundpl();
		}), NULL));
	});
}
