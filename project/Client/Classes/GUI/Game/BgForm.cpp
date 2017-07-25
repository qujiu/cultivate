
#include "BgForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"


BgForm::BgForm(EGameLevel eType)
:Form(IDC_BackGround)
, m_isJiesuanBGVisual(false)
{
	m_eType = eType;
}

BgForm::~BgForm()
{
}

bool BgForm::init()
{
	if (Form::init())
	{
		setKeyboardEnabled(false);
		cocos2d::Size winSize = Director::sharedDirector()->getWinSize();

		m_BgNode = CSLoader::createNode("Background.csb");
		this->addChild(m_BgNode);

		m_eType = EntityMgr::instance()->pPlayer()->getCurrRoomType();
		switch (m_eType)
		{
		case ELevel_BabyRoom:
			{
								   m_pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_BabyRoom"));
								   m_pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
								   m_pGameBg = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_bg"));
								   m_pPanel->setVisible(true);
								   break;
			}
		case ELevel_DiningRoom:
			{
									 m_pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_DiningRoom"));
									 m_pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
									 m_pGameBg = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_bg"));
									 m_pPanel->setVisible(true);
									 break;
			}
		case ELevel_MuyuRoom:
				m_pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_MuyuRoom"));
				m_pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
				m_pGameBg = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_bg"));
				m_pPanel->setVisible(true);
				break;
		case ELevel_WanjuRoom:
				m_pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_ToyRoom"));
				m_pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
				m_pGameBg = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_bg"));
				m_pPanel->setVisible(true);
				break;
			default:   //DressRoom
			{
						   m_pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_DressRoom"));
						   m_pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
						   m_pGameBg = dynamic_cast<ImageView*>(m_pPanel->getChildByName("Image_bg"));
						   m_pPanel->setVisible(true);
						   break;
			}
		}
		return true;
	}
	return false;
}

void BgForm::RefreshBackground(string strBg1, string strBg2)
{
	m_pGameBg->loadTexture(strBg1);
	m_pGameBg_Paizhao->loadTexture(strBg2);
}

void BgForm::ChangeCameraBg(bool bVisual)
{
	m_pPanel->setVisible(bVisual);
	m_pPanel_Paizhao->setVisible(!bVisual);
}

void BgForm::ChangeBgScale(float fScale)
{
	m_pGameBg_Paizhao->setScale(fScale);
}

void BgForm::setJiesuanBg(int iType, bool bVisual)
{
	setJiesuanBGVisual(iType, bVisual);
	m_isJiesuanBGVisual = bVisual;
}

void BgForm::setJiesuanBGVisual(int iType, bool bVisual)
{
	auto pPanel = dynamic_cast<Layout*>(m_BgNode->getChildByName("Panel_" + sup::SupString::int2String(iType)));
	pPanel->setScale(SUP_SCALE_X, SUP_SCALE_Y);
	pPanel->setVisible(bVisual);
}

RenderTexture* BgForm::getPictureRender()
{
	cocos2d::Size winSize = Director::getInstance()->getWinSize();
	auto texture = RenderTexture::create((int)winSize.width, (int)winSize.height, Texture2D::PixelFormat::RGBA8888);

	auto eCurrRoomType = EntityMgr::instance()->pPlayer()->getCurrRoomType();
	if (m_isJiesuanBGVisual)
	{
		if (eCurrRoomType == EGameRoom_Dress)
		{
			setJiesuanBGVisual(2, false);
		}
		else
		{
			setJiesuanBGVisual(1, false);
		}
	}


	texture->setPosition(Vec2(winSize.width* 0.5f, winSize.height* 0.5f));
	texture->begin();
	if (NULL != m_BgNode) m_BgNode->visit();
	//this->visit();
	texture->end();

	this->runAction(Sequence::create(DelayTime::create(0.01f), CallFunc::create([this, eCurrRoomType](){
		if (m_isJiesuanBGVisual)
		{
			if (eCurrRoomType == EGameRoom_Dress)
			{
				setJiesuanBGVisual(2, true);
			}
			else
			{
				setJiesuanBGVisual(1, true);
			}
		}
	}), NULL));

	return texture;
}