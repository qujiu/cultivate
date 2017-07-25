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
	EGameItemProcessId_Normal,//��ʧ;
	EGameItemProcessId_Shrink,//��С;
	EGameItemProcessId_FadeOut,//����;
	EGameItemProcessId_TakeAway,//�ƶ�;
	EGameItemProcessId_FallOff,//����;
	EGameItemProcessId_PaoMo,   //��ĭ����
	EGameItemProcessId_PaoMoXiaoshi,   //��ĭ��ϴ
	EGameItemProcessId_Replace,   //�滻
	EGameItemProcessId_Appear,   //��ʾ
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
#define UNVIDEO	 "UNVIDEO"		  //��¼�ǲ��ǿ�����Ƶ����;
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
#define MINIGAME_UM  "MINIGAME_UM" //����ǽ
#define OFFER_UM  "OFFER_UM" //����ǽ
#define MORE_UM  "MORE_UM"  //������Ϸ
#define FACEBOOK_UM  "FACEBOOK_UM"  //facebook����
#define GIFT_UM  "GIFT_UM"  //�����
#define DOUB_UM  "DOUB_UM"  //˫�����
#define ICON_UM  "ICON_UM"  //��̬icon
#define  NOT_MORE_DOT_VISIT "NOT_MORE_DOT_VISIT"  //֪ͨmore�Ƿ����
#define  NOT_COINS_DOT_VISIT "NOT_COINS_DOT_VISIT"  //֪ͨcoin�Ƿ���� 
#define NOT_GLOB_LUCKY		 "Glob_lucky"		  //�齱���;
#define NOT_WEI_LUCKY		 "wei_lucky"		  //δ����;
#define NOT_DAOJU_LUCKY		 "Daoju_lucky"		  //�齱����;
#define GAME_ZHONG_GLOB	 "GAME_ZHONG_GLOB"		  //��Ϸ�н�ҽ���;
#define TANGCHU_GLOB	 "TANGCHU_GLOB"		  //����С��Ϸ��ҶԻ���;
#define NOT_BUY_SUCCESS       "BuySuccess"          //BuySuccess;
#define NOT_BUY_FAILED       "BuyFailed"          //BuyFailed;
#define NOT_BUY_TIMEOUT		"BuyTimeout"		//BuyTimeout
#define TOTAL_GLOB		"TOTAL_GLOB"		//��������
#define REMOVE_COMMPLT    "REMOVE_COMMPLT"//�Ƴ���ɳɾ͵�������
#define REMOVE_UIAchievement    "REMOVE_UIAchievement"//�Ƴ��ɾͽ���
#define REMOVE_HOME    "REMOVE_HOME"//�Ƴ�ѡ���ӽ���
#define GAME_GLOB		 100		  //��Ϸ��������
#define PLAY_UNVIDEO_NUM	 "UNVIDEO_NUM"		  //��¼һ�쵱ǰ���ŵڼ���;
#define REMOVE_LUCKY    "REMOVE_LUCKY"
#define REMOVE_STORY    "REMOVE_STORY"
#define STATUE_TOUCH		 "Daoju_fan"		  //���ܷ���
#define ENOTIFY_AFTBUYPRICELUCKY    "ENotify_AFTBUYPRICELUCKY"
#define SHOW_CHOOSE        "SHOW_CHOOSE"
#define BAOXIANG         "BAOXIANG"//���±���
#define DAY_TI         "DAY_TI"//����ÿ������
#define CHENG_DONG         "CHENG_DONG"//��ʾ�ɾ�
#define SHOW_TIP    "SHOW_TIP"//��ʾ��ʾ
#define REMOVE_GAME_CENG 		444		  //�Ƴ���Ϸ��ͼ�㣻
#define CREAT_GLOB 		 30		  //����ͼƬ
#define  SHOW_ICON "SHOW_ICON"
#define PLAY_UNVIDEO_COUNT	 10		  //һ����Բ��ż���;
#define  SHOW_FREE "SHOW_FREE"
#define LIANGXU_DIAN         "LIANGXU_DIAN"//��һ���������û���˳�
#define GAME_GLOB		 100		  //��Ϸ��������
#define LUCKY_ALL		 64		  //�齱��������
#define NEWHOUSE_DONG         "NEWHOUSE_DONG"//�Ƿ񲥷Ž�������

#define ACTION_HOUSE	  		"ACTION_HOUSE"  //�Ƿ񲥷ų齱���������ֳɾͣ��������Ӷ���
#define REN_NUM 		6	  //����������
#define  UPDATE_Ren  "UPDATE_Ren"
#define  UPDATE_MIANBAO "UPDATE_MIANBAO"
#define SELCT_HOUSE_ENABLED "SELCT_HOUSE_ENABLED"
#define NOT_QITONG_DAQI "NOT_QITONG_DAQI"

#define NOT_ITEM_TARGET_TRIGGER       "ItemTargetTrigger"          //����;
#define NOT_ITEM_TARGET_NORMAL       "ItemTargetNormal"		      //����;
#define NOT_ITEM_TARGET_STOP		 "ItemTargetStop"		  //������ͣ;
#define NOT_ITEM_TARGET_TIME		 "ItemTargetTime"		  //������ͣ;

#define  NOT_ITEM_ZHINIAOKU_PISS "NOT_ITEM_ZHINIAOKU_PISS"   //ֽ���������ʧ
#define  NOT_ITEM_CanTingItemMix "NOT_ITEM_CanTingItemMix"   //ţ����Ƭ�������

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const std::string strSubmenuItem = "SubmenuItem";
static const std::string strTotalGoldSum = "TotalGoldSum";
//�齱
static const std::string strLUCKY = "lucky";
//�ɾ���ɶ�
static const std::string strAchievement = "Achievement";
static const std::string strLuckxian = "luckyOne";//��һ�γ齱
static const std::string strLuckNum = "XIANSHIlucky";//��ʾ�齱
//�ɾ�״̬
static const std::string strAchievement_stute = "Achievement_stute";
//�ɾ��Ƿ���ʾ
static const std::string strAchievement_show = "Achievement_show";
//����ID
static const std::string strrole_id = "role_id";
//�Ƿ񲥷ű��䶯��
static const std::string IsShowBAOXIANG = "IsShowBAOXIANG";
//�Ƿ񷴻�
static const std::string IsFANHUI = "IsFANHUI";
static const std::string strHouseID = "CurrHouseID";

static const std::string strNoADS = "NoADS";
static const std::string strIsShowTiaojiaoAni = "IsShowTiaojiaoAni";
static const std::string strSigninDays = "SigninDays";
static const std::string strIsGetSigninDays = "IsGetSigninDays";
static const std::string strSigninDate = "SigninDate";
static const std::string strIsIgnoreRate = "IsIgnoreRate";


//��Ϸ�������
static const std::string strWanjuLock = "WanjuRoomLock";
static const std::string strCantingLock = "CantingRoomLock";
static const std::string strMuyuLock = "MuyuRoomLock";
static const std::string strDressLock = "DressRoomLock";

//��Ϸ�����������
static const std::string strWanjuAction = "WanjuAction";
static const std::string strCantingAction = "CantingAction";
static const std::string strMuyuAction = "MuyuAction";
static const std::string strDressAction = "DressAction";

//��ʾ�Ƿ�������
static const std::string strIsRate = "IsRate";





////////////////////////////////////////////////////////////////


#endif // ! _BABYCARE_TYPE_H_