#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "define.h"
#include "Common/Common.h"
#include "Item.h"
#include "Monster.h"
#include "Animation.h"
#include "Role.h"
#include "Foods.h"
#include "Level.h"
#include "Store.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "RandomData.h"
#include "Entity/Lucky.h"
#include "RoleAnimation.h"
#include "Tool.h"
#include "ItemTool.h"
class BabyControl;
// -----------------------------------------------------------------------
// implement player class
// -----------------------------------------------------------------------
class Player :public Ref
{
public:
	Player();
	~Player();

	bool init();

public:	
    //计时器;
    void onTimer(float);
	void releaseMonsterList();


public:

	Armature* getAnimationArmature(int nAniID);

	bool getAllItemUse();
	void useAcc(const Acceleration* acc);
	void stopAcc();
	bool isShake(const Acceleration* acc);

	Role* getCurrRole();

	void initUseArr();
	void setItemCount(int num);
	void setItemUse(int itemID, EItemUseType bFlag);
	EItemUseType getItemUse(int itemID);

	void createFoodsRandom(bool bType); //true:水果, false:蔬菜;
	STargetFoods& getTargetFoods();

	void setSelFoods(int nIndex, int nID); //true:水果, false:蔬菜;
	STargetFoods& getSelFoods();

	void setPlayerGold(int nGold);
private:
    SUP_R_PROPERTY_DEF(private, ItemList*, m_pItemList, getItemList);        //道具列表;
	SUP_R_PROPERTY_DEF(private, FoodsList*, m_pFoodsList, getFoodsList);        //食材列表;
	SUP_RW_PROPERTY_PREFIX_DEF(private, MonsterList*, m_pMonsterList, MonsterList, MonsterList*);     //怪物列表;
	SUP_R_PROPERTY_DEF(private, RoleList*, m_pRoleList, getRoleList);        //role列表;
	SUP_R_PROPERTY_DEF(private, LevelList*, m_pLevelList, getLevelList);        //role列表;
	SUP_R_PROPERTY_DEF(private, StoreList*, m_pStoreList, getStoreList);        //role列表;
	SUP_R_PROPERTY_DEF(private, LuckyList*, m_pLuckyDataList, getLuckyDateList);
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nClothesIndex, ClothesIndex, int);     //衣服;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGameRole, m_eCurrRoleId, CurrRoleId, EGameRole);     //当前人物ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_eCurrRoleType, CurrRoleType, int);     //当前角色男女    0男1女
	SUP_RW_PROPERTY_PREFIX_DEF(private, EStoreUIType, m_eStoreType, CurrStoreType, EStoreUIType);     //购物类型;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nBuyID, CurrBuyID, int);     //购物ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nBuyGold, CurrBuyGold, int);     //购物所需金币;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nCurrGold, CurrGold, int);     //玩家金币;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nGoodFoodsCount, GoodFoodsCount, int);     //正确食材数;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGuideStep, m_eGuideStep, GuideStep, EGuideStep);     //新手步骤;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bADSHide, IsADSHide, bool);     //新手步骤;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nVideoCount, VideoCount, int);       //当播放视频次数;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bIsPopAD, IsPopAD, bool);       //是否弹出插屏和原生;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCanKeyReleased, CanKeyReleased, bool);       //是否允许响应返回键;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGameLevel, m_eCurrRoomType, CurrRoomType, EGameLevel);     //当前选择房间ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isStore, Storeis, bool);     //记录是否进入商城
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isAchieveis, Achieveis, bool);     //记录是否进入成就
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isjiesuan, jisuanis, bool);     //记录是否结算
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isHome, Homeis, bool);     //记录是否进入选择房子界面
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_glob, isglob, int);     //;//奖励多少金币
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_imNotification, imNotification, int);//1点击道具视频2游戏中宝箱视屏3结算视频4外部商城5游戏内商城
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_imlucky, imlucky, int);//记录宝箱id
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_imgame, m_imgame, bool);//结算
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_imsign, imsign, bool);
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isStar, Staris, bool);     //记录是否点击开始
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_ismess, ismess, bool);    
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockToy, isUnlockToy, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockDress, isUnlockDress, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockMuyu, isUnlockMuyu, bool);    
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockCanting, isUnlockCanting, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, BabyControl*, m_pBabyControl, pBabyControl, BabyControl*);     //当前Baby;

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isisInitItem, isInitItem, bool);   //第一次进入房间刷新
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_epreItemId, preItemId, int);     //当前角色男女    
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_eclickItemId, ClickItemId, int);     //换装房间点击道具id

	SUP_RW_PROPERTY_PREFIX_DEF(private, string, m_nstrItemyushi, strItemyushi, string);   //第一次进入浴室房间刷新
	SUP_RW_PROPERTY_PREFIX_DEF(private, string, m_nstrZhiniaoku, strZhiniaoku, string);   

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bIsShowNaoling, IsShowNaoling, bool);      //是否弹出闹铃提示;

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isSleeping, isSleeping, bool);

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isRoleAniLoop, isRoleAniLoop, bool);

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isisBoxVideo, isBoxVideo, bool);
														 

	/****************************RandomData*************************************/
private:
	SUP_R_PROPERTY_DEF(private, RandomDataList*, m_pRandomDataList, getRandomDataList);
	/***************************Tool************************************************/
private:
	SUP_R_PROPERTY_DEF(private, ToolList*, m_pToolList, getToolList);

	/***************************ItemTool************************************************/
private:
	SUP_R_PROPERTY_DEF(private, ItemToolList*, m_pItemToolList, getItemToolList);

	/****************************勺子中果酱*************************************/
private:
	SUP_RW_PROPERTY_PREFIX_DEF(private, EWaterType, m_eCurrWaterType, CurrWaterType, EWaterType);     //当前饮水盆中饮水类型;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCurrIsWaterExist, CurrIsWaterExist, bool);     //当前饮水盆中是否有饮水;
	/////////////////////////////////////////////////////////////////////////////////

	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_bCurrAttributeValue, CurrAttributeValue, bool);     //当前需求的数值;



private:
	int m_nItemCount;
	STargetFoods m_oFoods;
	STargetFoods m_oSelFoods;

	EItemUseType m_bUse[EItem_Max];

	void onMiniGameGold(Ref* object);

	Acceleration m_oAcc;  //计算手机摇动;
	double m_dAccTimestamp;
	map<int, bool> m_mapVideoLockStatus;

	/****************************Animation动画*************************************/
public:
	const string& getFilePath(int nAniID);
	const string& getAnimationName(int nAniID);
	SUP_R_PROPERTY_DEF(private, AniList*, m_pAniList, getAniList);
	/////////////////////////////////////////////////////////////////////////////////

	/****************************RoldAnimation动画*************************************/
public:
	const int& getRoleSpine(int nAniID);
	const vector<std::string>& getRoleJsonPath(int nAniID, int type);
	const vector<std::string>& getRoleAtlasName(int nAniID, int type);
	const string& getRoleAnimationSoundName(int nAniID);
	const string& getRoleAniName(int nAniID);

	SUP_R_PROPERTY_DEF(private, RoleAniList*, m_pRoleAniList, getRoleAniList);
	/////////////////////////////////////////////////////////////////////////////////
public:
	const string& getIconResByID(int nResID);
	const string& getImageResByID(int nResID);
public:
	void saveIsIgnoreRate(bool isIgnore);
	bool readIsIgnoreRate();

	void saveIsGetSignInDays(int iType, bool isGet);
	bool readIsGetSignInDays(int iType);

	void saveSignInDays(int iDays);
	int readSignInDays();

	void saveSigninDate(int iDate);
	int readSigninDate();

	void saveNoAdsStatus();
	bool readNoAdsStatus();

	void jiesuan();
	void saveRoomLockStatus();
	void getfacebookgift(int glob);
	void saveTotalGoldSum();
	void updatecon(float dt);
	void SetSubMenuItemStatusByID(int iID, bool isLock);
	bool GetSubMenuItemStatusByID(int iID);
	void SetVideoSubMenuItemStatusByID(int iID, bool isLock);
	bool GetVideoSubMenuItemStatusByID(int iID);
	void initSubMenuItemStatus();
	int readLuckyID(int id);
	void saveLuckyID(int id);
	void readLuckyALLID();
	void saveroleid(int id);
	int readroleid();
	void SetIsRated(bool isFinished);
	bool GetIsRated();
}; 
#endif