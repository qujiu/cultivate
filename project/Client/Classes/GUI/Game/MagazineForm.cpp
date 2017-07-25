
#include "MagazineForm.h"
#include "SDK/SupSDK.h"
#include "../Form/MessageBox.h"
#include "BabyCare.h"

MagazineForm::MagazineForm(Form* pBgForm, Form* pPerForm) :
Form(IDC_Magazine)
, m_pBgForm(pBgForm)
, m_pPersonForm(pPerForm)
, m_strCurrPath("")
, m_bShared(false)
, m_bSaveSuccess(false)
{

}

MagazineForm::~MagazineForm()
{

}

bool MagazineForm::init()
{
	if (Form::init())
	{

		auto pPhoto = CSLoader::createNode("magazine.csb");
		this->addChild(pPhoto, 1);

		pGeceng = dynamic_cast<Layout*>(pPhoto->getChildByName("Panel_geceng"));
		pGeceng->setPosition(ccp(pGeceng->getPositionX()*SUP_SCALE_X, pGeceng->getPositionY()*SUP_SCALE_Y));
		pGeceng->setScale(SUP_SCALE_X, SUP_SCALE_Y);

		m_pCameraLayout = dynamic_cast<ImageView*>(pPhoto->getChildByName("Image_bg"));
		m_pCameraLayout->setScale(m_pCameraLayout->getScaleX()*SUP_SCALE_X, m_pCameraLayout->getScaleY()*SUP_SCALE_Y);
		m_pCameraLayout->setPosition(ccp(m_pCameraLayout->getPositionX()*SUP_SCALE_X, m_pCameraLayout->getPositionY()*SUP_SCALE_Y));
		m_vecinitMagazinePos = m_pCameraLayout->getPosition();

		m_pPhotoBg = dynamic_cast<Layout*>(m_pCameraLayout->getChildByName("Panel_photo"));

		m_pMiddleImg = dynamic_cast<ImageView*>(m_pCameraLayout->getChildByName("Image_middle"));
		m_pTopImg = dynamic_cast<ImageView*>(m_pCameraLayout->getChildByName("Image_top"));

		m_pEmailBtn = dynamic_cast<Button*>(m_pCameraLayout->getChildByName("Button_email"));
		m_pEmailBtn->addTouchEventListener(this, toucheventselector(MagazineForm::onEmailButtonClicked));

		m_pPhotoBtn = dynamic_cast<Button*>(m_pCameraLayout->getChildByName("Button_photos"));
		m_pPhotoBtn->addTouchEventListener(this, toucheventselector(MagazineForm::onPhotoButtonClicked));

		m_pCloseBtn = dynamic_cast<Button*>(pPhoto->getChildByName("Button_close"));
		m_pCloseBtn->addTouchEventListener(this, toucheventselector(MagazineForm::onCloseButtonClicked));
		m_pCloseBtn->setPosition(ccp(m_pCloseBtn->getPositionX()*SUP_SCALE_X, m_pCloseBtn->getPositionY()*SUP_SCALE_Y));


		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
		m_pTexture = RenderTexture::create((int)winSize.width, (int)winSize.height, Texture2D::PixelFormat::RGBA8888);
		m_pTexture->setPosition(Vec2(winSize.width* 0.5f, winSize.height* 0.5f));
		addPictureImg();

		CameraFinishRandomPlaySound();

		return true;
	}

	return false;
}

void MagazineForm::CameraFinishRandomPlaySound()
{
	//RES_SOUND_ID resSound[6] = { RES_SOUND_ID_SOUND_GREAT, RES_SOUND_ID_SOUND_I_LOVE_IT, RES_SOUND_ID_SOUND_COOL, RES_SOUND_ID_SOUND_GOOD, RES_SOUND_ID_SOUND_ITS_GREAT, RES_SOUND_ID_SOUND_ITS_PERFECT };

	//int index = CCRANDOM_0_1() * 6;
	//SoundManage::instance()->playSound(resSound[index]);
}

void MagazineForm::initUI()
{

}

void MagazineForm::addPictureImg()
{
	if (NULL != m_pBgForm)
	{
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		auto pLogo = ImageView::create("logo.png", TextureResType::LOCAL);
		auto pRender = m_pBgForm->getPictureRender();

		m_pPhoto = Sprite::createWithTexture(pRender->getSprite()->getTexture());
		m_pPhoto->setPosition(winSize*0.5f);

		if (NULL != m_pPersonForm)
		{
			auto pPersonRender = m_pPersonForm->getPictureRender();
			auto pPersonPhoto = Sprite::createWithTexture(pPersonRender->getSprite()->getTexture());
			pPersonPhoto->setPosition(winSize*0.5f);
			pPersonPhoto->setFlippedY(true);
			m_pPhoto->addChild(pPersonPhoto);
			log("pPersonPhotox%f", pPersonPhoto->getPositionX());

		}

		pLogo->setScale(1.2f);
		m_pPhoto->addChild(pLogo);
		pLogo->setPosition(ccp(winSize.width*0.8f, winSize.height*0.07f));

		this->addChild(m_pPhoto, -1);
		m_pPhoto->setFlippedY(true);

		m_pTexture->begin();
		m_pPhoto->visit();
		m_pTexture->end();
		auto pPhoto2 = Sprite::createWithTexture(m_pTexture->getSprite()->getTexture());
		m_pPhotoBg->addChild(pPhoto2);
		pPhoto2->setFlippedY(true);
		pPhoto2->setPosition(m_pPhotoBg->getContentSize()*0.5f);
		pPhoto2->setScale(m_pPhotoBg->getContentSize().width / pPhoto2->getContentSize().width, m_pPhotoBg->getContentSize().height / pPhoto2->getContentSize().height);
		m_pPhoto->setVisible(false);

		sup::SupActions::BulgeNode(this, 0.0f, 1.0f);
	}
}

void MagazineForm::onEmailButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		char file[128] = { 0 };
		m_bShared = true;
		saveCapturePicture(file);
	}
}

void MagazineForm::onPhotoButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		saveCapturePicture(NULL);
		showMessageBoxID("Item1");
	}
}

void MagazineForm::onCloseButtonClicked(Ref *sender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_COMMONBTN);
		auto scaleTo = ScaleTo::create(0.5f, .2f);
		auto ease = EaseBackIn::create(scaleTo);
		auto action1 = Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(MagazineForm::onCloseButtonCallback)));
		auto action2 = Sequence::createWithTwoActions(ease, CallFunc::create(this, callfunc_selector(MagazineForm::onCloseButtonCallback)));
		auto spawn = Spawn::create(action1, action2, NULL);
		this->runAction(spawn);

	}
}

void MagazineForm::onCloseButtonCallback()
{
	Director::getInstance()->getRunningScene()->removeChild(this);
}

void MagazineForm::onPgecengvisible()
{
	pGeceng->setVisible(false);
}

void MagazineForm::saveCapturePicture(char *to)
{
	cocos2d::Size size = Director::getInstance()->getWinSize();

	auto pMagazineImg = Sprite::create("res/camera/camera_zazhi_di.png");
	this->addChild(pMagazineImg, -2);
	pMagazineImg->setScale(size.width / m_pCameraLayout->getContentSize().width, size.height / m_pCameraLayout->getContentSize().height);
	pMagazineImg->setPosition(Vec2(size.width / 2, size.height / 2));
	pMagazineImg->setVisible(true);

	m_pPhoto->setVisible(true);
	RenderTexture* texturetemp = RenderTexture::create((int)size.width, (int)size.height, Texture2D::PixelFormat::RGBA8888);
	texturetemp->setPosition(Vec2(size.width / 2, size.height / 2));
	texturetemp->begin();
	m_pPhoto->visit();
	texturetemp->end();
	m_pPhoto->setVisible(false);
	auto pPhoto = Sprite::createWithTexture(texturetemp->getSprite()->getTexture());
	pPhoto->setFlippedY(true);
	pMagazineImg->addChild(pPhoto, 0);
	pPhoto->setPosition(ccp(m_pPhotoBg->getPositionX() + m_pPhotoBg->getContentSize().width*0.5f, m_pPhotoBg->getPositionY() + m_pPhotoBg->getContentSize().height*0.5f));
	pPhoto->setScale(m_pPhotoBg->getContentSize().width / pPhoto->getContentSize().width, m_pPhotoBg->getContentSize().height / pPhoto->getContentSize().height);

	auto pMiddleImg = m_pMiddleImg->clone();
	auto pTopImg = m_pTopImg->clone();
	pMagazineImg->addChild(pMiddleImg, 1);
	pMagazineImg->addChild(pTopImg, 2);
	pMiddleImg->setPosition(m_pMiddleImg->getPosition());
	pTopImg->setPosition(m_pTopImg->getPosition());

	RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height, Texture2D::PixelFormat::RGBA8888);
	texture->setPosition(Vec2(size.width / 2, size.height / 2));
	texture->begin();
	pMagazineImg->visit();
	texture->end();
	pMagazineImg->setVisible(false);

	if (m_strCurrPath == "")
	{
		m_strCurrPath = SupSDK::instance()->getCaptureImgPath();
		if (texture->saveToFile(m_strCurrPath.c_str()))
		{
			this->runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f), CallFunc::create(this, callfunc_selector(MagazineForm::FlushCapturePicture))));
		}
	}
	else
	{
		CapturePictureComplete();
	}
}

void MagazineForm::shareToEmailCallback(char* file)
{
	SupSDK::instance()->shareToEmail(file);
}


void MagazineForm::FlushCapturePicture()
{
	if (m_strCurrPath != "")
	{
		char file[128] = { 0 };
		strcpy(file, m_strCurrPath.c_str());
		SupSDK::instance()->FlushCapturePicture(file);
		m_bSaveSuccess = true;
		CapturePictureComplete();
	}
}

void MagazineForm::CapturePictureComplete()
{
	if (m_bSaveSuccess)
	{
		if (m_bShared)
		{
			char file[128] = { 0 };
			strcpy(file, m_strCurrPath.c_str());
			shareToEmailCallback(file);
			m_bShared = false;
		}
	}
}