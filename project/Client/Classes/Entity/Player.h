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
    //��ʱ��;
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

	void createFoodsRandom(bool bType); //true:ˮ��, false:�߲�;
	STargetFoods& getTargetFoods();

	void setSelFoods(int nIndex, int nID); //true:ˮ��, false:�߲�;
	STargetFoods& getSelFoods();

	void setPlayerGold(int nGold);
private:
    SUP_R_PROPERTY_DEF(private, ItemList*, m_pItemList, getItemList);        //�����б�;
	SUP_R_PROPERTY_DEF(private, FoodsList*, m_pFoodsList, getFoodsList);        //ʳ���б�;
	SUP_RW_PROPERTY_PREFIX_DEF(private, MonsterList*, m_pMonsterList, MonsterList, MonsterList*);     //�����б�;
	SUP_R_PROPERTY_DEF(private, RoleList*, m_pRoleList, getRoleList);        //role�б�;
	SUP_R_PROPERTY_DEF(private, LevelList*, m_pLevelList, getLevelList);        //role�б�;
	SUP_R_PROPERTY_DEF(private, StoreList*, m_pStoreList, getStoreList);        //role�б�;
	SUP_R_PROPERTY_DEF(private, LuckyList*, m_pLuckyDataList, getLuckyDateList);
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nClothesIndex, ClothesIndex, int);     //�·�;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGameRole, m_eCurrRoleId, CurrRoleId, EGameRole);     //��ǰ����ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_eCurrRoleType, CurrRoleType, int);     //��ǰ��ɫ��Ů    0��1Ů
	SUP_RW_PROPERTY_PREFIX_DEF(private, EStoreUIType, m_eStoreType, CurrStoreType, EStoreUIType);     //��������;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nBuyID, CurrBuyID, int);     //����ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nBuyGold, CurrBuyGold, int);     //����������;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nCurrGold, CurrGold, int);     //��ҽ��;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nGoodFoodsCount, GoodFoodsCount, int);     //��ȷʳ����;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGuideStep, m_eGuideStep, GuideStep, EGuideStep);     //���ֲ���;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bADSHide, IsADSHide, bool);     //���ֲ���;
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_nVideoCount, VideoCount, int);       //��������Ƶ����;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bIsPopAD, IsPopAD, bool);       //�Ƿ񵯳�������ԭ��;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCanKeyReleased, CanKeyReleased, bool);       //�Ƿ�������Ӧ���ؼ�;
	SUP_RW_PROPERTY_PREFIX_DEF(private, EGameLevel, m_eCurrRoomType, CurrRoomType, EGameLevel);     //��ǰѡ�񷿼�ID;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isStore, Storeis, bool);     //��¼�Ƿ�����̳�
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isAchieveis, Achieveis, bool);     //��¼�Ƿ����ɾ�
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isjiesuan, jisuanis, bool);     //��¼�Ƿ����
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isHome, Homeis, bool);     //��¼�Ƿ����ѡ���ӽ���
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_glob, isglob, int);     //;//�������ٽ��
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_imNotification, imNotification, int);//1���������Ƶ2��Ϸ�б�������3������Ƶ4�ⲿ�̳�5��Ϸ���̳�
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_imlucky, imlucky, int);//��¼����id
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_imgame, m_imgame, bool);//����
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_imsign, imsign, bool);
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isStar, Staris, bool);     //��¼�Ƿ�����ʼ
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_ismess, ismess, bool);    
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockToy, isUnlockToy, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockDress, isUnlockDress, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockMuyu, isUnlockMuyu, bool);    
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isUnlockCanting, isUnlockCanting, bool);     
	SUP_RW_PROPERTY_PREFIX_DEF(private, BabyControl*, m_pBabyControl, pBabyControl, BabyControl*);     //��ǰBaby;

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_isisInitItem, isInitItem, bool);   //��һ�ν��뷿��ˢ��
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_epreItemId, preItemId, int);     //��ǰ��ɫ��Ů    
	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_eclickItemId, ClickItemId, int);     //��װ����������id

	SUP_RW_PROPERTY_PREFIX_DEF(private, string, m_nstrItemyushi, strItemyushi, string);   //��һ�ν���ԡ�ҷ���ˢ��
	SUP_RW_PROPERTY_PREFIX_DEF(private, string, m_nstrZhiniaoku, strZhiniaoku, string);   

	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bIsShowNaoling, IsShowNaoling, bool);      //�Ƿ񵯳�������ʾ;

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

	/****************************�����й���*************************************/
private:
	SUP_RW_PROPERTY_PREFIX_DEF(private, EWaterType, m_eCurrWaterType, CurrWaterType, EWaterType);     //��ǰ��ˮ������ˮ����;
	SUP_RW_PROPERTY_PREFIX_DEF(private, bool, m_bCurrIsWaterExist, CurrIsWaterExist, bool);     //��ǰ��ˮ�����Ƿ�����ˮ;
	/////////////////////////////////////////////////////////////////////////////////

	SUP_RW_PROPERTY_PREFIX_DEF(private, int, m_bCurrAttributeValue, CurrAttributeValue, bool);     //��ǰ�������ֵ;



private:
	int m_nItemCount;
	STargetFoods m_oFoods;
	STargetFoods m_oSelFoods;

	EItemUseType m_bUse[EItem_Max];

	void onMiniGameGold(Ref* object);

	Acceleration m_oAcc;  //�����ֻ�ҡ��;
	double m_dAccTimestamp;
	map<int, bool> m_mapVideoLockStatus;

	/****************************Animation����*************************************/
public:
	const string& getFilePath(int nAniID);
	const string& getAnimationName(int nAniID);
	SUP_R_PROPERTY_DEF(private, AniList*, m_pAniList, getAniList);
	/////////////////////////////////////////////////////////////////////////////////

	/****************************RoldAnimation����*************************************/
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