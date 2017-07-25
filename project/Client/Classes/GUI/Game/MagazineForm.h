/*
** declare MagazineForm
** author: zhang chao;
** date: 2014.10.09
*/

#ifndef __GUI_MagazineForm_H__
#define __GUI_MagazineForm_H__

#include "../Form.h"

class MagazineForm : public Form
{
public:
	CREATE_(MagazineForm, Form* pBgForm, Form* pPerForm)
		_INST(MagazineForm, pBgForm, pPerForm)

		virtual bool init();
	MagazineForm(Form* pBgForm, Form* pPerForm);
	virtual ~MagazineForm();

private:
	Form* m_pBgForm;
	Form* m_pPersonForm;
	ImageView* m_pCameraLayout;
	Layout* m_pPhotoBg;
	Sprite* m_pPhoto;
	RenderTexture* m_pTexture;
	Layout* pGeceng;
	Button* m_pEmailBtn;
	Button* m_pPhotoBtn;
	Button* m_pCloseBtn;

	Vec2 m_vecinitMagazinePos;
	ImageView* m_pMiddleImg;
	ImageView* m_pTopImg;

	std::string m_strCurrPath;
	bool m_bShared;
	bool m_bSaveSuccess;
public:
	void onEmailButtonClicked(Ref *sender, TouchEventType type);
	void onPhotoButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonClicked(Ref *sender, TouchEventType type);

	void addPictureImg();
	void onCloseButtonCallback();

	void FlushCapturePicture();
	void CapturePictureComplete();

	void CameraFinishRandomPlaySound();
	void onPgecengvisible();

private:
	void initUI();
	void saveCapturePicture(char *to);
	void shareToEmailCallback(char* file);

};

#endif //__GUI_MagazineForm_H__