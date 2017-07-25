#include "MiniControl.h"
#include "BabyCare.h"
#include "../MiniGame/MiniGame.h"
#include "define.h"
MiniControl::MiniControl()
{

}

MiniControl::~MiniControl()
{

}

bool MiniControl::init()
{
	if (BaseControl::init())
	{
		m_pMiniImg = ImageView::create("mini_game.png", Widget::TextureResType::PLIST);
		m_pMiniImg->setTouchEnabled(true);
		m_pMiniImg->setPosition(ccp(Director::getInstance()->getVisibleSize().width*0.88f, Director::getInstance()->getVisibleSize().height*0.4f));
		m_pMiniImg->addTouchEventListener(this, toucheventselector(MiniControl::onMiniButtonClicked));
		this->addChild(m_pMiniImg);
		return true;
	}
	return false;
}


void MiniControl::onMiniButtonClicked(Ref *sender, ui::TouchEventType type)
{
	if (TOUCH_EVENT_BEGAN == type)
	{
	}
	else if (TOUCH_EVENT_ENDED == type)
	{
		SoundManage::instance()->stopSound();
		//SoundManage::instance()->playSound(RES_SOUND_ID_SOUND_Button);
		Director::getInstance()->pushScene(MiniGame::loadMiniGame(true));
		BabyCare::instance()->SetResultCallback_None();

	}
}


