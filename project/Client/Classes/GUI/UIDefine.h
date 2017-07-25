#ifndef __UIDefine_H__
#define __UIDefine_H__


//////////////////////////////////////////////////////////////////////////
//Window ID
//////////////////////////////////////////////////////////////////////////
enum WINDOW_ID{
	IDC_Logo = 0,
	IDC_Loading,
	IDC_Home,
	IDC_ChooseColor,
	IDC_HomeSelect,
	IDC_BabyRoom,
	IDC_DiningRoom,
	IDC_ToyRoom,
	IDC_MuyuRoom,
	IDC_DressRoom,
//	IDC_FoodMakeRoom,
	IDC_DrinkMakeRoom,
	IDC_Zui,
	IDC_Zoom,
	IDC_Make,
	IDC_Reward,
	IDC_Person,
	IDC_Info,
	IDC_Hanger,
	IDC_UnlockTip,
	IDC_Magazine,
	IDC_BuyLucky,
	IDC_Lucky,
	IDC_Message,
	IDC_Scene,
	IDC_UnLock,
	IDC_Store,
	IDC_BuyCoins,
	IDC_Congrats,
	IDC_Video,
	IDC_Signin,
	IDC_NativeAd,
	IDC_ChooseBox,
	IDC_WellDone,
	IDC_MiniGame,
	IDC_Shop,
	IDC_BackGround,
	IDC_PlayStore,
	IDC_Sign,
	IDC_Photo,
	IDC_Rate,
	IDC_Naoling,
	IDC_Setting,
	IDC_Select,
	IDC_BuyTip,
	IDC_Player,
	IDC_MAX_COUNT,									//window count
	IDC_NULL = -1,									//invalid window
};

static const char* gWindowJson[IDC_MAX_COUNT] = {
	"Loading.json",
};

//////////////////////////////////////////////////////////////////////////
//UI Layer ID
//////////////////////////////////////////////////////////////////////////
enum LayerID{
	LayID_BK,
	LayID_Game,
	LayID_UI,
};

#endif //__UIDefine_H__