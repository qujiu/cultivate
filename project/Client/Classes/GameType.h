#ifndef  _GAME_TYPE_H_
#define  _GAME_TYPE_H_


enum EGameRoom
{
	EGameRoom_Common = -1,
	EGameRoom_Baby,
	EGameRoom_Toy,
	EGameRoom_DiningMianBao,
	EGameRoom_DiningNiuNai,
	EGameRoom_MianBao,
	EGameRoom_NiuNai,
	EGameRoom_Muyu,
	EGameRoom_Dress,
	EMonsterScene_Ya,
	EMonsterScene_Zoom,
	EMonsterScene_shuaya,
	EMonsterScene_player,


	EGameRoom_Max,
};

enum EGameLevel
{
	ELevel_Null = -1,
	ELevel_BabyRoom,
	ELevel_WanjuRoom,
	ELevel_DiningRoom,
	ELevel_MuyuRoom,
	ELevel_DressRoom,
	ELvel_Max,
};
enum EGameRole
{
	ERole_Null = -1,
	ERole_1,
	ERole_2,
	ERole_3,
	ERole_4,
	ERole_5,
	ERole_6,
	ERole_Max,
};

enum ERole_Status{
	ERoleStatus_Init,
	ERoleStatus_Walk,
	ERoleStatus_Idle,
	ERoleStatus_Qima,
};

enum EBabyExpression
{
	EBabyExpression_Null,
	EBabyExpression_Chidongxi,
	EBabyExpression_Daiji,
	EBabyExpression_Fadou,
	EBabyExpression_Gaoxing,
	EBabyExpression_Jingxia,
	EBabyExpression_Ku,
	EBabyExpression_LianHong,
	EBabyExpression_ShuiJiao,
	EBabyExpression_YiHuo,
	EBabyExpression_Zhayanjing,
	EBabyExpression_TuShui,
	EBabyExpression_ShuiXing,
	EBabyExpression_Max,
};

enum  EStoreUIType 
{
	EStoreUIType_Shop,
	EStoreUIType_Gold,
	EStoreUIType_Tools,
	EStoreUIType_Rooms,
	EStoreUIType_Roles,
	EStoreUIType_Max,
};



enum EGameItemType
{
	EItem_Null,
	EItem_wanju,
	EItem_naizui,
	EItem_bed,
	EItem_beizi,
	EItem_zhentou,
	EItem_zhiniaoku,

	EItem_muma,
	EItem_xiaobear,
	EItem_qitong,
	EItem_qiqiu1,
	EItem_qiqiu2,
	EItem_qiqiu3,
	EItem_tantanqiu,

	EItem_wan,
	EItem_naiping,
	EItem_shaoziM,
	EItem_NiuNaiM,
	EItem_zhijin,
	EItem_weizui,
	EItem_shuiguo,
	EItem_mianbaoM,

	EItem_guojiang,
	EItem_mianbaoG,
	EItem_shaoziG,
	EItem_GuoBei,

	EItem_NiuNaiN,
	EItem_Maipian,
	EItem_shaoziN,

	EItem_maojin,
	EItem_yashua,
	EItem_muyuye,
	EItem_xiaohuangya,
	EItem_lenshuifa,
	EItem_reshuifa,
	EItem_huasa,
	EItem_yuhua,


	EItem_kuzi,
	EItem_xiuzi,
	EItem_maozi,
	EItem_xiezi,
	EItem_yifu,

	EItem_YaGao,
	EItem_YaShua,
	EItem_FangDaJing,
	EItem_MaoJin_M,
	EItem_Yabei,

	EItem_YaShua2,

	EItem_Max,
};

enum EGameMonsterType
{
	EMonster_Null = -1,
	EMonster_WanJu,
	EMonster_Naizui,
	EMonster_Chuang,
	EMonster_Beizi,
	EMonster_ZhenTou,
	EMonster_ZhiNiaoKu,
	EMonster_MuMa,
	EMonster_XiaoBear,
	EMonster_QiTong,
	EMonster_QiQiu1,
	EMonster_QiQiu2,
	EMonster_QiQiu3,
	EMonster_TanTanQiu,

	EMonster_WeiZui,
	EMonster_Wan_M,
	EMonster_NaiPing,
	EMonster_ShaoZi_M,
	EMonster_PingGuo,
	EMonster_MianBao_M,
	EMonster_NaiFen,
	EMonster_Wan_N,
	EMonster_ShaoZi_N,
	EMonster_GuoJingPing,
	EMonster_MianBao_G,
	EMonster_ShaoZi_G,
	
	EMonster_ShuiDi,
	EMonster_YaZi,
	EMonster_PaoMo,
	EMonster_HuangYa,
	EMonster_FuZhuang,
	EMonster_XieZi,
	EMonster_MaoZi,
	EMonster_YanJing,

	EMonster_YaGao,
	EMonster_YaShua,
	EMonster_Shuayabei,
	EMonster_Yazi,
	EMonster_Hezi,
	EMonster_XiJun,
	EMonster_KouShui,

	EMonster_Max,
};


enum EItemAniType
{
	EItemAniType_OnTouch,
	EItemAniType_OnTrigger,
	EItemAniType_OnHit,
	EItemAniType_OnRelease,
	EItemAniType_OnBegin,
	EItemAniType_OnStop,
	EItemAniType_Max,
};

enum EGameItemHitProcessId
{
	EGameItemProcessId_Null = -1,
	EGameItemProcessId_Normal,//消失;
	EGameItemProcessId_Shrink,//缩小;
	EGameItemProcessId_FadeOut,//淡出;
	EGameItemProcessId_TakeAway,//移动;
	EGameItemProcessId_FallOff,//剥落;
	EGameItemProcessId_PaoMo,   //泡沫出现
	EGameItemProcessId_PaoMoXiaoshi,   //泡沫冲洗
	EGameItemProcessId_Replace,   //替换
	EGameItemProcessId_Appear,   //显示
	EGameItemProcessId_XiJun,
	EGameItemProcessId_Max,
};

enum EItemSoundType
{
	EItemSoundType_OnTouch,
	EItemSoundType_OnHit,
	EItemSoundType_OnTrigger,

	EItemSoundType_Max,
};

enum EGameItemTarget
{
	EGameItemTarget_Normal,
	EGameItemTarget_Trigger,
	EGameItemTarget_Shake,
	EGameItemTarget_Stop,
	EGameItemTarget_Max,
};

enum EItemUseType{
	EItemUseType_Normal,
	EItemUseType_Useing,
	EItemUseType_Complete,
	EItemUseType_Max,
};

enum EFoodsType
{
	EFoods_ChengZi,
	EFoods_PingGuo,
	EFoods_XiGua,
	EFoods_BoLuo,
	EFoods_CaoMei,
	EFoods_MangGuo,
	EFoods_ShiLiu,
	EFoods_PuTao,

	EFoods_NiuNai,
	EFoods_MaiPian,
	EFoods_Max
};


enum EStoreType
{
	EStore_JueSeBao,
	EStore_GongJuBao,
	EStore_GuanQiaBao,
	EStore_WanQuanBao,
	EStore_JinBiBao1,
	EStore_JinBiBao2,
	EStore_JinBiBao3,
	EStore_JinBiBao4,
	EStore_JinBiBao5,
	EStore_JinBiBao6,
	EStore_GuangGaoBao,
	EStore_Max
};

enum EGuideStep
{
	EGuideStep_Null = -1,
	EGuideStep_CompleteLevel_0,
	EGuideStep_CompleteLevel_1,
	EGuideStep_CompleteLevel_2,
	EGuideStep_CompleteLevel_3,
	EGuideStep_CompleteLevel_4,
	EGuideStep_CompleteLevel_2_1,
	EGuideStep_CompleteLevel_2_2,
	EGuideStep_CompleteLevel_4_1,
};

enum SimpleDialogButtonEnum
{
	SimpleDialog_NO = 0,
	SimpleDialog_YES,
	SimpleDialog_AGAIN,
	SimpleDialog_CONTINUE,
	SimpleDialog_OK,
};

struct STargetFoods
{
	int foods[3];
};

enum EWaterType
{
	EWater_Null = -1,
	EWater_Guojiang,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  UPDATE_FREE "UPDATE_FREE"
#define UNVIDEO	 "UNVIDEO"		  //记录是不是可以视频播放;
#define ENOTIFY_AFTERBUYITEMSUCCESSFUNC    "ENotify_AFTERBUYITEMSUCCESSFUNC"
#define ENOTIFY_REFRESHBUILDING           "ENotify_Refreshbuilding"
#define ENotify_Finish_WatchVideo         "ENotify_Finish_WatchVideo"
#define NOT_FORM_AWARD_CLOSE			"Game_Form_Award_Close"		  
#define NOT_GAME_GOID_UPDATA			"Game_Gold_updata"	
#define NOT_STORE_GOLD_COMPLETE			"Store_Gold_complete"		 
#define FACEBOOK_GIFT					"FACEBOOK_GIFT"
#define FACEBOOK_jib					"FACEBOOK_jib"	
#define UPDATE_FACEIM					"UPDATE_FACEIM"
#define TOTAL_GLOB						"TOTAL_GLOB"
#define MINIGAME_UM  "MINIGAME_UM" //积分墙
#define OFFER_UM  "OFFER_UM" //积分墙
#define MORE_UM  "MORE_UM"  //更多游戏
#define FACEBOOK_UM  "FACEBOOK_UM"  //facebook任务
#define GIFT_UM  "GIFT_UM"  //礼物盒
#define DOUB_UM  "DOUB_UM"  //双倍金币
#define ICON_UM  "ICON_UM"  //动态icon
#define  NOT_MORE_DOT_VISIT "NOT_MORE_DOT_VISIT"  //通知more是否出现
#define  NOT_COINS_DOT_VISIT "NOT_COINS_DOT_VISIT"  //通知coin是否出现 
#define NOT_GLOB_LUCKY		 "Glob_lucky"		  //抽奖金币;
#define NOT_WEI_LUCKY		 "wei_lucky"		  //未抽中;
#define NOT_DAOJU_LUCKY		 "Daoju_lucky"		  //抽奖道具;
#define GAME_ZHONG_GLOB	 "GAME_ZHONG_GLOB"		  //游戏中金币奖励;
#define TANGCHU_GLOB	 "TANGCHU_GLOB"		  //弹出小游戏金币对话框;
#define NOT_BUY_SUCCESS       "BuySuccess"          //BuySuccess;
#define NOT_BUY_FAILED       "BuyFailed"          //BuyFailed;
#define NOT_BUY_TIMEOUT		"BuyTimeout"		//BuyTimeout
#define TOTAL_GLOB		"TOTAL_GLOB"		//更新总数
#define REMOVE_COMMPLT    "REMOVE_COMMPLT"//移除完成成就弹窗界面
#define REMOVE_UIAchievement    "REMOVE_UIAchievement"//移除成就界面
#define REMOVE_HOME    "REMOVE_HOME"//移除选择房子界面
#define GAME_GLOB		 100		  //游戏奖励总数
#define PLAY_UNVIDEO_NUM	 "UNVIDEO_NUM"		  //记录一天当前播放第几次;
#define REMOVE_LUCKY    "REMOVE_LUCKY"
#define REMOVE_STORY    "REMOVE_STORY"
#define STATUE_TOUCH		 "Daoju_fan"		  //不能反回
#define ENOTIFY_AFTBUYPRICELUCKY    "ENotify_AFTBUYPRICELUCKY"
#define SHOW_CHOOSE        "SHOW_CHOOSE"
#define BAOXIANG         "BAOXIANG"//更新宝箱
#define DAY_TI         "DAY_TI"//更新每日提醒
#define CHENG_DONG         "CHENG_DONG"//显示成就
#define SHOW_TIP    "SHOW_TIP"//显示提示
#define REMOVE_GAME_CENG 		444		  //移除游戏中图层；
#define CREAT_GLOB 		 30		  //绘制图片
#define  SHOW_ICON "SHOW_ICON"
#define PLAY_UNVIDEO_COUNT	 10		  //一天可以播放几次;
#define  SHOW_FREE "SHOW_FREE"
#define LIANGXU_DIAN         "LIANGXU_DIAN"//第一次连续点击没有退出
#define GAME_GLOB		 100		  //游戏奖励总数
#define LUCKY_ALL		 64		  //抽奖道具总数
#define NEWHOUSE_DONG         "NEWHOUSE_DONG"//是否播放解锁场景

#define ACTION_HOUSE	  		"ACTION_HOUSE"  //是否播放抽奖动画，出现成就，解锁房子动画
#define REN_NUM 		6	  //人物数量；
#define  UPDATE_Ren  "UPDATE_Ren"
#define  UPDATE_MIANBAO "UPDATE_MIANBAO"
#define SELCT_HOUSE_ENABLED "SELCT_HOUSE_ENABLED"
#define NOT_QITONG_DAQI "NOT_QITONG_DAQI"

#define NOT_ITEM_TARGET_TRIGGER       "ItemTargetTrigger"          //道具;
#define NOT_ITEM_TARGET_NORMAL       "ItemTargetNormal"		      //正常;
#define NOT_ITEM_TARGET_STOP		 "ItemTargetStop"		  //道具暂停;
#define NOT_ITEM_TARGET_TIME		 "ItemTargetTime"		  //道具暂停;

#define  NOT_ITEM_ZHINIAOKU_PISS "NOT_ITEM_ZHINIAOKU_PISS"   //纸尿裤污渍消失
#define  NOT_ITEM_CanTingItemMix "NOT_ITEM_CanTingItemMix"   //牛奶麦片制作完成

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const std::string strSubmenuItem = "SubmenuItem";
static const std::string strTotalGoldSum = "TotalGoldSum";
//抽奖
static const std::string strLUCKY = "lucky";
//成就完成度
static const std::string strAchievement = "Achievement";
static const std::string strLuckxian = "luckyOne";//第一次抽奖
static const std::string strLuckNum = "XIANSHIlucky";//显示抽奖
//成就状态
static const std::string strAchievement_stute = "Achievement_stute";
//成就是否显示
static const std::string strAchievement_show = "Achievement_show";
//人物ID
static const std::string strrole_id = "role_id";
//是否播放宝箱动画
static const std::string IsShowBAOXIANG = "IsShowBAOXIANG";
//是否反回
static const std::string IsFANHUI = "IsFANHUI";
static const std::string strHouseID = "CurrHouseID";

static const std::string strNoADS = "NoADS";
static const std::string strIsShowTiaojiaoAni = "IsShowTiaojiaoAni";
static const std::string strSigninDays = "SigninDays";
static const std::string strIsGetSigninDays = "IsGetSigninDays";
static const std::string strSigninDate = "SigninDate";
static const std::string strIsIgnoreRate = "IsIgnoreRate";


//游戏房间解锁
static const std::string strWanjuLock = "WanjuRoomLock";
static const std::string strCantingLock = "CantingRoomLock";
static const std::string strMuyuLock = "MuyuRoomLock";
static const std::string strDressLock = "DressRoomLock";

//游戏房间解锁动画
static const std::string strWanjuAction = "WanjuAction";
static const std::string strCantingAction = "CantingAction";
static const std::string strMuyuAction = "MuyuAction";
static const std::string strDressAction = "DressAction";

//表示是否已评价
static const std::string strIsRate = "IsRate";





////////////////////////////////////////////////////////////////


#endif // ! _BABYCARE_TYPE_H_