/*
** ui factory for this project
** author: zhang chao;
** date: 2014.09.29
*/


#ifndef __UIFACTORY_H__
#define __UIFACTORY_H__

#include "Form.h"
#include "Form/MessageBox.h"
#include "GameType.h"
//extern enum EGameMonsterScene;

//////////////////////////////////////////////////////////////////////////////
class UIFactory: public sup::Singleton<UIFactory, Ref>
{
private:
    SINGLETON_FRIEND_SUB(UIFactory, Ref);
	UIFactory();
	virtual ~UIFactory();

public:
	void showMessgeBox(MessageBoxArg &arg);

	Form* showLogoForm();
	Form* showHomeForm();

	Form* showHomeSelectForm();

	Form* showBabyRoomForm();
	Form* showDiningRoomForm();
	Form* showToyRoomForm();
	Form* showMuyuRoomForm();
	Form* showDressForm();
	Form* showNativeAdFrom();
	Form* showMakeForm(int makeType);
	Form* showMiniGameForm();
	Form* showSettingForm();
	Form* showSelectForm();
	Form* showLoadingForm();
	Form* showUnlockTipForm(int iType);
	Form* showStoreForm();
	Form* showBuyCoinsForm();
	Form* showWellDoneForm();
	Form* showAwardForm(int type);
	Form* showCongratsForm(int iID);
	Form* showVideoForm(int iType);
	Form* showBuyTipForm(int iGoldSum, int iID);
	Form* showUnLockForm();
	Form* showInfoForm();
	Form* showPlayerForm();
	Form* showBackgroundForm(EGameLevel eType);
	Form* showZuiForm();
	Form* showZoomForm();
	Form* showNaolingForm();
	//Form* showShopForm(EStoreUIType type);

};


#endif
