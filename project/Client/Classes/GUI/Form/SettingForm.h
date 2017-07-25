#ifndef __SettingForm_H__
#define __SettingForm_H__
#include "../Form.h"
#include "MessageBox.h"


class SettingForm : public Form
{
public:
	CREATE_(SettingForm)
		_INST(SettingForm);

	virtual bool init();
	SettingForm();
	virtual ~SettingForm();

private:
	void onMusicButtonClicked(Ref *sender, TouchEventType type);
	void onSoundButtonClicked(Ref *sender, TouchEventType type);
	void onParentsButtonClicked(Ref *sender, TouchEventType type);
	void onRateButtonClicked(Ref *sender, TouchEventType type);
	void onSharButtonClicked(Ref *sender, TouchEventType type);
	void onFacebookButtonClicked(Ref *sender, TouchEventType type);
	//void onHomeButtonClicked(Ref *sender, TouchEventType type);
	//void onHomeBtnCallBack(MBCLICK_TYPE type, void* data);
	void onjinCallback(Ref* object);

	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonCallback();

private:
	ImageView*      m_pBkImage;
	Layout* m_pGeceng;

	Button* m_pMusicOnBtn;
	Button* m_pMusicOffBtn;
	Button* m_pSoundOnBtn;
	Button* m_pSoundOffBtn;
	LoadingBar* m_pLoadingBarImg1;
	LoadingBar* m_pLoadingBarImg2;

	ImageView* m_pSound_on;
	ImageView* m_pSound_off;
	ImageView* m_pMusic_on;
	ImageView* m_pMusic_off;


};

#endif