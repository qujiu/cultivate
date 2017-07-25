#include "Player.h"
#include "ResManager/ConfigDataCenter.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "SaveManager/SaveManage.h"
#include "SDK/SupSDK.h"
#include "GUI/UIFactory.h"
#include "BabyCare.h"
#include "GUI/Form/UILuckyForm.h"

Player::Player()
: m_eCurrRoomType(ELevel_BabyRoom)
, m_nItemCount(0)
, m_eCurrRoleId(ERole_1)
,m_nBuyGold(0)
, m_pBabyControl(NULL)
, m_nGoodFoodsCount(0)
, m_bIsPopAD(true)
, m_bCanKeyReleased(true)
, m_bCurrIsWaterExist(false)
{
}


bool Player::init()
{
	m_pItemList = new ItemList(ConfigDataCenter::instance()->item());
	m_pAniList = new AniList(ConfigDataCenter::instance()->animation());
	m_pRoleList = new RoleList(ConfigDataCenter::instance()->role());
	m_pFoodsList = new FoodsList(ConfigDataCenter::instance()->foods());
	m_pLevelList = new LevelList(ConfigDataCenter::instance()->Level());
	m_pMonsterList = new MonsterList();
	m_pLuckyDataList = new LuckyList(ConfigDataCenter::instance()->Lucky());
	m_pRoleAniList = new RoleAniList(ConfigDataCenter::instance()->animationRole());
	m_pToolList = new ToolList(ConfigDataCenter::instance()->tool());
	m_pItemToolList = new ItemToolList(ConfigDataCenter::instance()->itemtool());


	return true;
}

void Player::onTimer(float)
{

}

Player::~Player()
{
	SUP_SAFE_DELETE(m_pItemList);
	SUP_SAFE_DELETE(m_pAniList);
	SUP_SAFE_DELETE(m_pFoodsList);
	SUP_SAFE_DELETE(m_pRoleList);
	SUP_SAFE_DELETE(m_pLevelList);
	SUP_SAFE_DELETE(m_pMonsterList);
	SUP_SAFE_DELETE(m_pLuckyDataList);
	SUP_SAFE_DELETE(m_pRoleAniList);
	SUP_SAFE_DELETE(m_pToolList);
	SUP_SAFE_DELETE(m_pItemToolList);
}

void Player::releaseMonsterList()
{
	m_pMonsterList->releaseMonsterList();
}

Role* Player::getCurrRole()
{
	return m_pRoleList->getRoleByID(m_eCurrRoleId);
}

void Player::setItemUse(int itemID, EItemUseType bFlag)
{
	if (itemID >= EItem_Max)
		return;
	m_bUse[itemID] = bFlag;

}

EItemUseType Player::getItemUse(int itemID)
{
	if (itemID >= EItem_Max)
		return EItemUseType_Normal;
	return m_bUse[itemID];
}

void Player::setItemCount(int num)
{
	m_nItemCount += num;
}

bool Player::getAllItemUse()
{
	int count = 0;
	//for (int i = 0; i < EItem_Max; i++)
	//{
	//	if (m_bUse[i])
	//	{
	//		count++;
	//	}
	//}
	if (count >= m_nItemCount)
		return true;
	else return false;
}

void Player::initUseArr()
{
	//for (int i = 0; i < EItem_Max; i++)
	//{
	//	m_bUse[i] = EItemUseType_Normal;
	//}
	//m_nItemCount = 0;
}

Armature* Player::getAnimationArmature(int nAniID)
{
	Ani* pAni = m_pAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(pAni->getFilePath());
		auto armature = Armature::create(pAni->getFileName());
		CC_ASSERT(armature);
		return armature;
	}
	return NULL;
}



const string& Player::getFilePath(int nAniID)
{
	Ani* pAni = m_pAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getFilePath();
	}
}

const string& Player::getAnimationName(int nAniID)
{
	Ani* pAni = m_pAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getAniName();
	}
}

///////////////////////////////////////////////////////////////////////////////////
const int& Player::getRoleSpine(int nAniID)
{
	RoleAni* pAni = m_pRoleAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getSpine();
	}
}

const vector<std::string>& Player::getRoleJsonPath(int nAniID, int type)
{
	RoleAni* pAni = m_pRoleAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getAniJsonPool(type);
	}
}

const vector<std::string>& Player::getRoleAtlasName(int nAniID, int type)
{
	RoleAni* pAni = m_pRoleAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getAniAtlasPool(type);
	}
}


const string& Player::getRoleAnimationSoundName(int nAniID)
{
	RoleAni* pAni = m_pRoleAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getAndroidSound();
	}
}

const string& Player::getRoleAniName(int nAniID)
{
	RoleAni* pAni = m_pRoleAniList->getAniByID(nAniID);
	if (NULL != pAni)
	{
		return pAni->getAniName();
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void Player::createFoodsRandom(bool bType)
{
	int i = 0;
	while (i < 3)
	{
		m_oFoods.foods[i] = CCRANDOM_0_1() * 8;
		if (m_oFoods.foods[i] != m_oFoods.foods[i - 1])
		{
			if (i >= 2 && (m_oFoods.foods[i] != m_oFoods.foods[i - 2]) || i < 2)
			{
				i++;
			}
			
		}
	}
}

STargetFoods& Player::getTargetFoods()
{
	return m_oFoods;
}


void Player::setSelFoods(int nIndex, int nID)
{
	m_oSelFoods.foods[nIndex] = nID;
}

STargetFoods& Player::getSelFoods()
{
	return m_oSelFoods;
}


void Player::setPlayerGold(int nGold)
{
	/*m_nCurrGold += nGold;
	SaveManage::instance()->setIntSave(SAVE_ID_INT_GOLD, m_nCurrGold);
	NotificationCenter::getInstance()->postNotification(NOT_GAME_GOID_UPDATA);*/
}

void Player::useAcc(const Acceleration* acc)
{
	if (m_dAccTimestamp == -1)
	{
		m_oAcc = *acc;
		m_dAccTimestamp = m_oAcc.timestamp;
	}
}

void Player::stopAcc()
{
	m_dAccTimestamp = -1;
}

bool Player::isShake(const Acceleration* acc)
{
	if (m_dAccTimestamp != -1 &&  abs(m_oAcc.y - acc->y) > .9f)
	{
		return true;
	}
	return false;
}

//保存每日签到天数
void Player::saveSignInDays(int iDays)
{
	UserDefault::getInstance()->setIntegerForKey(strSigninDays.c_str(), iDays);
	UserDefault::getInstance()->flush();
}

//读取每日签到天数
int Player::readSignInDays()
{
	return UserDefault::getInstance()->getIntegerForKey(strSigninDays.c_str(), 0);
}

void Player::saveIsGetSignInDays(int iType, bool isGet)
{
	string strItemName = strIsGetSigninDays + sup::SupString::int2String(iType);
	UserDefault::getInstance()->setBoolForKey(strItemName.c_str(), isGet);
	UserDefault::getInstance()->flush();
}

bool Player::readIsGetSignInDays(int iType)
{
	string strItemName = strIsGetSigninDays + sup::SupString::int2String(iType);
	return UserDefault::getInstance()->getBoolForKey(strItemName.c_str(), false);
}

void Player::saveIsIgnoreRate(bool isIgnore)
{
	UserDefault::getInstance()->setBoolForKey(strIsIgnoreRate.c_str(), isIgnore);
	UserDefault::getInstance()->flush();
}
bool Player::readIsIgnoreRate()
{
	return UserDefault::getInstance()->getBoolForKey(strIsIgnoreRate.c_str(), false);
}

void Player::saveSigninDate(int iDate)
{
	UserDefault::getInstance()->setIntegerForKey(strSigninDate.c_str(), iDate);
	UserDefault::getInstance()->flush();
}

int Player::readSigninDate()
{
	return UserDefault::getInstance()->getIntegerForKey(strSigninDate.c_str(), 0);
}

void Player::getfacebookgift(int glob){

	int cout = this->getCurrGold() + 500;


	this->setCurrGold(cout);
	this->saveTotalGoldSum();

	this->SetSubMenuItemStatusByID(74, true);
	this->SetSubMenuItemStatusByID(182, true);
	__NotificationCenter::getInstance()->postNotification(UPDATE_FACEIM);



	if (BabyCare::instance()->getCurrSceneID() != EScene_Home)//主界面
	{


		//this->setisglob(GAME_GLOB);


		__NotificationCenter::getInstance()->postNotification(TOTAL_GLOB, (Ref*)(intptr_t)cout);
	}


	Director::getInstance()->getRunningScene()->scheduleOnce(schedule_selector(Player::updatecon), 0.1f);

}
void Player::updatecon(float dt){
	UserDefault::getInstance()->setBoolForKey(FACEBOOK_GIFT, true);
	UserDefault::getInstance()->flush();

	__NotificationCenter::getInstance()->postNotification(FACEBOOK_jib);

	auto *pForm = UIFactory::instance()->showCongratsForm(10);
	if (NULL != pForm)
	{
		Director::getInstance()->getRunningScene()->addChild(pForm, 10);
	}

}


void Player::saveTotalGoldSum()
{
	UserDefault::getInstance()->setIntegerForKey(strTotalGoldSum.c_str(), m_nCurrGold);
	UserDefault::getInstance()->flush();
}

//保存是否已购买去广告
void Player::saveNoAdsStatus()
{
	UserDefault::getInstance()->setBoolForKey(strNoADS.c_str(), true);
	UserDefault::getInstance()->flush();
}

bool Player::readNoAdsStatus()
{
	return UserDefault::getInstance()->getBoolForKey(strNoADS.c_str(), false);
}

//通过ID设置item解锁， isLock:true 表示已解锁
void Player::SetSubMenuItemStatusByID(int iID, bool isLock)
{
	string strItemName = strSubmenuItem + sup::SupString::int2String(iID);
	UserDefault::getInstance()->setBoolForKey(strItemName.c_str(), isLock);
	UserDefault::getInstance()->flush();
}

//通过ID获取item是否已解锁
bool Player::GetSubMenuItemStatusByID(int iID)
{
	string strItemName = strSubmenuItem + sup::SupString::int2String(iID);

	return UserDefault::getInstance()->getBoolForKey(strItemName.c_str(), false);
}

//通过ID设置item解锁， isLock:true 表示已解锁
void Player::SetVideoSubMenuItemStatusByID(int iID, bool isLock)
{
	m_mapVideoLockStatus[iID] = isLock;
}

//通过ID获取item是否已解锁
bool Player::GetVideoSubMenuItemStatusByID(int iID)
{
	map<int, bool>::iterator l_it;
	l_it = m_mapVideoLockStatus.find(iID);//返回的是一个指针
	if (l_it == m_mapVideoLockStatus.end())
		return false;
	else
		return m_mapVideoLockStatus[iID];
}

void Player::initSubMenuItemStatus()
{
	m_mapVideoLockStatus.clear();
}

void Player::jiesuan(){

	NotificationCenter::getInstance()->postNotification(REMOVE_STORY);//移除商城界面
	UserDefault::getInstance()->setIntegerForKey(STATUE_TOUCH, 0);
	UserDefault::getInstance()->flush();
	//SoundManage::instance()->stopMusic();

	if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//游戏中
	{
		//SoundManage::instance()->playMusic(RES_SOUND_ID_MUSIC_GAME);
		__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画

	}
	if (BabyCare::instance()->getCurrSceneID() == EScene_Select)//选择房间
	{
		//SoundManage::instance()->playMusic(RES_SOUND_ID_MUSIC_GAME);
		__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画

		if (this->getAchieveis() == true)
		{
			NotificationCenter::getInstance()->postNotification(REMOVE_UIAchievement);//移除成就界面
			this->setAchieveis(false);
		}
		if (this->getHomeis() == true)
		{
			NotificationCenter::getInstance()->postNotification(REMOVE_HOME);//移除选择房子界面
			this->setHomeis(false);
		}
	}
	if (BabyCare::instance()->getCurrSceneID() == EScene_Home)//主界面
	{
		//SoundManage::instance()->playMusic(RES_SOUND_ID_MUSIC_MAIN);

		this->setisglob(GAME_GLOB);

		NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//金币对话框

		this->setCurrGold(this->getCurrGold() + GAME_GLOB);
		this->saveTotalGoldSum();
	}
}

int  Player::readLuckyID(int id)
{
	std::string name = strLUCKY + sup::SupString::int2String(id);
	return UserDefault::getInstance()->getIntegerForKey(name.c_str());
}

void  Player::saveLuckyID(int id)
{
	std::string name = strLUCKY + sup::SupString::int2String(id);
	UserDefault::getInstance()->setIntegerForKey(name.c_str(), id);
	UserDefault::getInstance()->flush();
	UserDefault::getInstance()->setIntegerForKey("count", UserDefault::getInstance()->getIntegerForKey("count") + 1);
	UserDefault::getInstance()->flush();
}

void Player::readLuckyALLID()
{
	for (int i = 1; i <= LUCKY_ALL; i++)
	{
		std::string name = strLUCKY + sup::SupString::int2String(i);
		UserDefault::getInstance()->getIntegerForKey(name.c_str());
	}
}

void Player::saveRoomLockStatus()
{
	UserDefault::getInstance()->setBoolForKey(strWanjuLock.c_str(), m_isUnlockToy);
	UserDefault::getInstance()->setBoolForKey(strCantingLock.c_str(), m_isUnlockCanting);
	UserDefault::getInstance()->setBoolForKey(strMuyuLock.c_str(), m_isUnlockMuyu);
	UserDefault::getInstance()->setBoolForKey(strDressLock.c_str(), m_isUnlockDress);
	UserDefault::getInstance()->flush();
}

void Player::saveroleid(int id)
{
	std::string name2 = strrole_id;
	UserDefault::getInstance()->setIntegerForKey(name2.c_str(), id);
	UserDefault::getInstance()->flush();
}
int  Player::readroleid()
{
	std::string name = strrole_id;
	return UserDefault::getInstance()->getIntegerForKey(name.c_str());
}

const string& Player::getIconResByID(int nResID)
{
	ItemTool* pSubMenu = m_pItemToolList->getItemToolByID(nResID);
	if (NULL != pSubMenu)
	{
		return pSubMenu->getIcon();
	}
}

const string& Player::getImageResByID(int nResID)
{
	ItemTool* pSubMenu = m_pItemToolList->getItemToolByID(nResID);
	if (NULL != pSubMenu)
	{
		return pSubMenu->getImage();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//是否已评价
//
void Player::SetIsRated(bool isFinished)
{
	UserDefault::getInstance()->setBoolForKey(strIsRate.c_str(), isFinished);
	UserDefault::getInstance()->flush();
}
//
bool Player::GetIsRated()
{
	return UserDefault::getInstance()->getBoolForKey(strIsRate.c_str(), false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////