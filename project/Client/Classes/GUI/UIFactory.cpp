#include "UIFactory.h"
#include "GameType.h"
#include "UIManager.h"
#include "Logo/LogoForm.h"
#include "Home/HomeForm.h"
#include "Form/UnLockForm.h"
#include "Form/BuyCoinsForm.h"
#include "Form/CongratsForm.h"
#include "Game/RewardForm.h"
#include "Select/SceneForm.h"
#include "Form/UILuckyForm.h"
#include "Form/WellDoneForm.h"
#include "Game/MiniGameForm.h"
#include "Select/HomeSelectForm.h"
#include "Game/BabyRoomForm.h"
#include "Game/DiningRoomForm.h"
#include "Game/MakeForm.h"
#include "Form/NativeAdForm.h"
#include "Game/DressForm.h"
#include "Game/MuyuRoomForm.h"
#include "Game/ToyRoomForm.h"
#include "Form/SettingForm.h"
#include "Form/SelectForm.h"
#include "Form/LoadingForm.h"
#include "Form/UnlockTipForm.h"
#include "Form/StoreForm.h"
#include "Form/VideoForm.h"
#include "Game/InfoForm.h"
#include "Form/ShopForm.h"
#include "Game/BgForm.h"
#include "Form/BuyTipForm.h"
#include "Game/ZuiForm.h"
#include "Game/ZoomForm.h"
#include "Form/NaolingForm.h"

SINGLETON_DEFINE_INST(UIFactory, Ref);

UIFactory::UIFactory()
{

}

UIFactory::~UIFactory()
{

}


void UIFactory::showMessgeBox(MessageBoxArg &arg)
{
	if (arg.type == MT_YES)
	{
		auto *pForm = Dialog_OK::createInst(arg.info, arg.handler);
		Director::getInstance()->getRunningScene()->addChild(pForm, 200);
	}
	else
	{
		auto *pForm = Dialog_YesNo::createInst(arg.info, arg.handler);
		Director::getInstance()->getRunningScene()->addChild(pForm, 200);
	}
}

Form* UIFactory::showLogoForm()
{
	
	if (NULL == UIManager::instance()->findForm(IDC_Logo))
	{
		return LogoForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showSettingForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Setting))
	{
		return SettingForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showHomeForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Home))
	{
		return HomeForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showHomeSelectForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_HomeSelect))
	{
		return HomeSelectForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showBabyRoomForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_BabyRoom))
	{
		return BabyRoomForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showMakeForm(int makeType)
{
	if (NULL == UIManager::instance()->findForm(IDC_Make))
	{
		return MakeForm::createInst(makeType);
	}
	return NULL;
}

Form* UIFactory::showDiningRoomForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_DiningRoom))
	{
		return DiningRoomForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showToyRoomForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_ToyRoom))
	{
		return ToyRoomForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showMuyuRoomForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_MuyuRoom))
	{
		return MuyuRoomForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showDressForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_DressRoom))
	{
		return DressForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showNativeAdFrom()
{
	if (NULL == UIManager::instance()->findForm(IDC_NativeAd))
	{
		return NativeAdForm::createInst();
	}
}

//Form* UIFactory::showShopForm(EStoreUIType type)
//{
//	if (NULL == UIManager::instance()->findForm(IDC_Shop))
//	{
//		return ShopForm::createInst(type);
//	}
//	return NULL;
//}

Form* UIFactory::showMiniGameForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_MiniGame))
	{
		return MiniGameForm::createInst(true);
	}
	return NULL;
}

Form* UIFactory::showSelectForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Select))
	{
		return SelectForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showLoadingForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Loading))
	{
		return LoadingForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showUnlockTipForm(int iType)
{
	if (NULL == UIManager::instance()->findForm(IDC_UnlockTip))
	{
		return UnlockTipForm::createInst(iType);
	}
	return NULL;
}

Form* UIFactory::showStoreForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Store))
	{
		return StoreForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showBuyCoinsForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_BuyCoins))
	{
		return BuyCoinsForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showWellDoneForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_WellDone))
	{
		return WellDoneForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showAwardForm(int type)
{
	if (NULL == UIManager::instance()->findForm(IDC_Reward))
	{
		return RewardForm::createInst(type);
	}
	return NULL;
}

Form* UIFactory::showCongratsForm(int iID)
{
	if (NULL == UIManager::instance()->findForm(IDC_Congrats))
	{
		return CongratsForm::createInst(iID);
	}
	return NULL;
}

Form* UIFactory::showVideoForm(int iType)
{
	if (NULL == UIManager::instance()->findForm(IDC_Video))
	{
		return VideoForm::createInst(iType);
	}
	return NULL;
}

Form* UIFactory::showBuyTipForm(int iGoldSum, int iID)
{
	if (NULL == UIManager::instance()->findForm(IDC_BuyTip))
	{
		return BuyTipForm::createInst(iGoldSum, iID);
	}
	return NULL;
}

Form* UIFactory::showUnLockForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_UnLock))
	{
		return UnLockForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showInfoForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Info))
	{
		return InfoForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showPlayerForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Player))
	{
		return BabyControl::createInst();
	}
	return NULL;
}

Form* UIFactory::showBackgroundForm(EGameLevel eType)
{
	if (NULL == UIManager::instance()->findForm(IDC_BackGround))
	{
		return BgForm::createInst(eType);
	}
	return NULL;
}

Form* UIFactory::showZuiForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Zui))
	{
		return ZuiForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showZoomForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Zoom))
	{
		return ZoomForm::createInst();
	}
	return NULL;
}

Form* UIFactory::showNaolingForm()
{
	if (NULL == UIManager::instance()->findForm(IDC_Naoling))
	{
		return NaolingForm::createInst();
	}
	return NULL;
}