#include "NativeAdForm.h"
#include "BabyCare.h"
#include "GUI/UIManager.h"
#include "cocostudio/CCArmature.h"
#include "SDK/SupSDK.h"
#include "GUI/Game/GameScene.h"

NativeAdForm::NativeAdForm() :
Form(IDC_NativeAd)
, m_loadIndex(0)
{
	setKeyboardEnabled(false);
}

NativeAdForm::~NativeAdForm()
{
	//SupSDK::instance()->HideNativeAd();
}

bool NativeAdForm::init()
{
	if (Form::init())
	{
		return true;
	}

	return false;
}

void NativeAdForm::updateComplete(float t)
{
	if (m_loadIndex < 20)
	{
		m_loadIndex++;
		int flag = m_loadIndex % 4;
		for (int i = 0; i < 3; i++)
		{
			if (i < flag)
				m_pImg[i]->setVisible(true);
			else
				m_pImg[i]->setVisible(false);
		}
		return;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_pImg[i]->setVisible(true);
		}
		unschedule(schedule_selector(NativeAdForm::updateComplete));
		this->removeFromParentAndCleanup(true);

		(dynamic_cast<GameScene*>(BabyCare::instance()->getCurrScene()))->GameUIInit();
	}

}
