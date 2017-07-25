/*
** implement form class
** author: zhang chao;
** date: 2014.09.29
*/

#include "Form.h"
#include "UIManager.h"
#include "BabyCare.h"
#include "SDK/SupSDK.h"
#include "Form/MessageBox.h"
///////////////////root/////////////////////////////////////////////////////////////////////////////////////

bool BaseControl::init()
{
    if (Node::init())
    {
        return true;
    }
    return false;

}

BaseControl::BaseControl()
{
}

BaseControl::~BaseControl()
{
}

void BaseControl::onEnter()
{
    Node::onEnter();
}

void BaseControl::onExit()
{
	Node::onExit();
}

///////////////////Form/////////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------
// public
// -----------------------------------------------------------------------
bool Form::init()
{
	if (Layer::init())
	{
		m_winSize = Director::sharedDirector()->getWinSize();
		return true;
	}

	return false;
	
}

// -----------------------------------------------------------------------
// protected
// -----------------------------------------------------------------------
Form::Form(WINDOW_ID id)
:m_pLayout(NULL)
{
	_ID = id;
	UIManager::instance()->createForm(_ID,this);
	setKeyboardEnabled(true);
}


Form::~Form()
{
	UIManager::instance()->releaseForm(_ID);
	setKeyboardEnabled(false);
}

void Form::onEnter()
{
	Layer::onEnter();
}

void Form::onExit()
{
	Layer::onExit();
}

RenderTexture* Form::getPictureRender()
{
	return NULL;
}

void Form::BulgeNode(Node* node, float from, float to, SEL_CallFunc selector)
{
	BulgeNode(node, Vec2(from, from), Vec2(to, to), selector);
}

void Form::BulgeNode(Node* node, Vec2 from, Vec2 to, SEL_CallFunc selector)
{
	if (node)
	{
		node->stopAllActions();
		node->setScaleX(from.x);
		node->setScaleY(from.y);
		auto scaleTo = ScaleTo::create(0.3f, to.x, to.y);
		auto ease = EaseBackOut::create(scaleTo);
		if (selector == NULL)
		{
			node->runAction(ease);
		}
		else
		{
			node->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, selector)));
		}
	}
}

void Form::BulgeNodeReverse(Node* node, float from, float to, SEL_CallFunc selector)
{
	if (node)
	{
		node->stopAllActions();
		node->setScale(to);
		auto scaleTo = ScaleTo::create(0.4f, from, from);
		auto ease = EaseBackIn::create(scaleTo);
		if (selector == NULL)
		{
			node->runAction(ease);
		}
		else
		{
			node->runAction(Sequence::createWithTwoActions(ease, CallFunc::create(this, selector)));
		}
	}
}


void Form::JeteNode3(Node* node, float jete, float dur, bool loop, float delayTime)
{
	if (node)
	{
		node->stopAllActions();
		auto delay = DelayTime::create(delayTime);
		auto move = MoveBy::create(dur, ccp(0, jete));
		auto ease = EaseExponentialIn::create(move);
		move = MoveBy::create(dur, ccp(0, -jete));
		auto ease2 = EaseBounceOut::create(move);

		if (loop)
		{
			node->runAction(RepeatForever::create(Sequence::create(delay, ease, ease2, NULL)));
		}
		else
		{
			node->runAction(Sequence::create(delay, ease, ease2, NULL));
		}
	}
}

void Form::JeteNode3Scale(Node* node, float from, float to, float dur, bool loop, float delayTime)
{
	if (node)
	{
		node->stopAllActions();
		auto delay = DelayTime::create(delayTime);
		node->setScale(from);
		auto scale = ScaleTo::create(dur, to);
		auto ease = EaseExponentialIn::create(scale);
		scale = ScaleTo::create(dur, from);
		auto ease2 = EaseBounceOut::create(scale);

		if (loop)
		{
			node->runAction(RepeatForever::create(Sequence::create(delay, ease, ease2, NULL)));
		}
		else
		{
			node->runAction(Sequence::create(delay, ease, ease2, NULL));
		}
	}
}


void Form::FadeInNode(Node* node, bool zero_opacity, float dur)
{
	if (node)
	{
		node->stopAllActions();
		node->setVisible(true);
		if (zero_opacity)
		{
			node->setOpacity(0);
		}
		node->runAction(FadeIn::create(dur));
	}
}

void Form::FadeOutNode(Node* node, float dur, SEL_CallFunc selector)
{
	if (node)
	{
		node->stopAllActions();
		if (selector)
		{
			node->runAction(Sequence::createWithTwoActions(FadeOut::create(dur), CallFunc::create(this, selector)));
		}
		else
		{
			node->runAction(FadeOut::create(dur));
		}
	}
}

void Form::MoveTo(Node* node, const Vec2& to, float delayTime)
{
	if (node)
	{
		node->stopAllActions();
		auto delay = DelayTime::create(delayTime);
		auto move = MoveTo::create(.5f, to);
		auto ease = EaseBackIn::create(move);
		node->runAction(Sequence::createWithTwoActions(delay, ease));
	}
}

void Form::MoveTo2(Node* node, const Vec2& to, float delayTime)
{
	if (node)
	{
		node->stopAllActions();
		auto delay = DelayTime::create(delayTime);
		auto move = MoveTo::create(.5f, to);
		auto ease = EaseExponentialOut::create(move);
		node->runAction(Sequence::createWithTwoActions(delay, ease));
	}
}

void Form::MoveTo3(Node* node, const Vec2& to, float delayTime)
{
	if (node)
	{
		node->stopAllActions();
		auto delay = DelayTime::create(delayTime);
		auto move = MoveTo::create(.5f, to);
		auto ease = EaseBackOut::create(move);
		node->runAction(Sequence::createWithTwoActions(delay, ease));
	}
}

void Form::NodeIn(Node* node, Vec2& from, Vec2& to, float delayTime)
{
	if (node)
	{
		//node->stopAllActions();
		auto delay = CCDelayTime::create(delayTime);
		auto move = CCMoveTo::create(.0f, from);
		auto move2 = CCMoveTo::create(.5f, to);
		auto ease = CCEaseExponentialOut::create(move2);
		node->runAction(Sequence::create(delay, move, ease, NULL));
	}
}

void Form::NodeOut(Node* node, Vec2& to)
{
	if (node)
	{
		node->stopAllActions();
		auto move = MoveTo::create(.5f, to);
		auto ease = EaseExponentialIn::create(move);
		node->runAction(ease);
	}
}


void Form::ButtonAction(Node* node, SEL_CallFunc selector)
{
	if (node)
	{
		//node->stopAllActions();
		auto scale1 = ScaleTo::create(.1f, 1.3f, 0.7f);
		auto scale2 = ScaleTo::create(.1f, 0.7f, 1.3f);
		auto scale3 = ScaleTo::create(.1f, 1.0f, 1.0f);
		if (selector)
		{
			node->runAction(Sequence::create(scale1, scale2, scale3, CallFunc::create(this, selector), NULL));
		}
		else
		{
			node->runAction(Sequence::create(scale1, scale2, scale3, NULL));
		}
	}
}

void Form::RotateScaleIn(Node* node, const std::function<void()>& func)
{
	if (node)
	{
		node->stopAllActions();
		node->setRotation(0);
		node->setScale(0);
		auto rotate = RotateBy::create(.5f, -360);
		auto scale = ScaleTo::create(.5f, 1);
		if (func)
		{
			node->runAction((Sequence::createWithTwoActions(Spawn::createWithTwoActions(rotate, scale), CallFunc::create(func))));
		}
		else
		{
			node->runAction(Spawn::createWithTwoActions(rotate, scale));
		}
	}
}

void Form::PulseNode(Node* node, float to1, float to2, float dur, bool loop, bool stop_actions)
{
	if (node)
	{
		if (stop_actions)
			node->stopAllActions();
		auto scale = ScaleTo::create(dur, to1, to1);
		auto ease = EaseExponentialIn::create(scale);
		scale = ScaleTo::create(dur, to2, to2);
		auto ease2 = EaseExponentialOut::create(scale);
		if (loop)
		{
			node->runAction(RepeatForever::create(Sequence::create(ease, ease2, NULL)));
		}
		else
		{
			node->runAction(Sequence::create(ease, ease2, NULL));
		}
	}
}


void Form::NodeElasticAppear(Node* node, const std::function<void()>& func, float delat_time)
{
	if (node)
	{
		node->stopAllActions();
		node->setVisible(true);
		node->setScale(0);
		DelayTime* delay_action = nullptr;
		if (delat_time > 0.0f)
		{
			delay_action = DelayTime::create(delat_time);
		}
		CallFunc* callback_action = nullptr;
		if (func)
		{
			callback_action = CallFunc::create(func);
		}
		if (delay_action && callback_action)
		{
			node->runAction(Sequence::create(delay_action, genBounceShowAction(), callback_action, nullptr));
		}
		else if (delay_action)
		{
			node->runAction(Sequence::createWithTwoActions(delay_action, genBounceShowAction()));
		}
		else if (callback_action)
		{
			node->runAction(Sequence::createWithTwoActions(genBounceShowAction(), callback_action));
		}
		else
		{
			node->runAction(genBounceShowAction());
		}
	}
}

void Form::NodeElasticDisAppear(Node* node, const std::function<void()>& func, float delat_time)
{
	if (node)
	{
		node->stopAllActions();
		node->setVisible(true);
		node->setScale(1);
		DelayTime* delay_action = nullptr;
		if (delat_time > 0.0f)
		{
			delay_action = DelayTime::create(delat_time);
		}
		CallFunc* callback_action = nullptr;
		if (func)
		{
			callback_action = CallFunc::create(func);
		}
		if (delay_action && callback_action)
		{
			node->runAction(Sequence::create(delay_action, genBounceDisappearAction(), callback_action, nullptr));
		}
		else if (delay_action)
		{
			node->runAction(Sequence::createWithTwoActions(delay_action, genBounceDisappearAction()));
		}
		else if (callback_action)
		{
			node->runAction(Sequence::createWithTwoActions(genBounceDisappearAction(), callback_action));
		}
		else
		{
			node->runAction(genBounceDisappearAction());
		}
	}
}

ActionInterval* Form::genBounceShowAction()
{
	auto callfunc = CallFuncN::create([](Node* node){node->setScale(0.0f); });
	auto scaleBorn = CCEaseInOut::create(CCScaleTo::create(0.08f, 0.3f, 1.1f), 1.2f);

	auto scaleHorDown = CCScaleTo::create(0.08f, 0.8f, 1.1f);
	auto scaleHorBouncing = CCEaseIn::create(scaleHorDown, 1.3f);
	auto scaleVerDown = CCScaleTo::create(0.14f, 1.1f, 0.6f);
	auto scaleVerBouncing = CCEaseInOut::create(scaleVerDown, 1.3f);

	auto shrink = CCSequence::create(scaleHorBouncing, scaleVerBouncing, NULL);

	auto swell = CCScaleTo::create(0.4f, 1.0f);
	auto swellEase = CCEaseElasticOut::create(swell);

	auto buttonAction = CCSequence::create(callfunc, scaleBorn, shrink, swellEase, NULL);
	return buttonAction;
}

ActionInterval* Form::genBounceDisappearAction()
{
	auto callfunc = CallFuncN::create([](Node* node){node->setScale(1.0f); });
	auto swell = CCScaleTo::create(0.1f, 1.1f, 0.65f);

	auto scaleVerDown = CCScaleTo::create(0.1f, 0.75f, 1.1f);
	auto scaleHorDown = CCScaleTo::create(0.1f, 0.3f, 1.1f);

	auto shrink = CCSequence::create(scaleVerDown, scaleHorDown, NULL);
	auto scaleBorn = CCScaleTo::create(0.08f, 0.0f);

	auto buttonAction = CCSequence::create(callfunc, swell, shrink, scaleBorn, NULL);

	return buttonAction;
}


void Form::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}

void Form::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)  //·µ»Ø
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		ESceneID sceneID = BabyCare::instance()->getCurrSceneID();
		switch (sceneID)
		{
		case EScene_Logo:
		case EScene_Home:
			SupSDK::instance()->ExitAD();
			break;
		case EScene_Select:
		{
			BabyCare::instance()->onStatusChanged(EScene_Home);
			//showPopAD();
			break;
		}
		case EScene_Game:
		{
			auto pPlayer = EntityMgr::instance()->pPlayer();	
			if (!pPlayer->getCanKeyReleased())
			{
				break;
			}
			auto pForm = UIManager::instance()->findForm(IDC_Message);
			if (NULL != pForm)
			{
				Director::getInstance()->getRunningScene()->removeChild(pForm);
				CCLog("onKeyReleased removeChild ");

			}
			else
			{
				EntityMgr::instance()->pPlayer()->setIsPopAD(true);
				showMessageBoxID("Item2", MBCall(Form::onHomeBtnCallBack));
				CCLog("onKeyReleased showMessageBoxID ");
			}
		}
			break;
		default:
			break;
		}

#endif
	}
}

void Form::onHomeBtnCallBack(MBCLICK_TYPE type, void* data)
{
	if (MBCLICK_YES == type)
	{
		BabyCare::instance()->onStatusChanged(EScene_Home);
	}
}

void Form::delayShowNode(Node *node, float delay, FORM_SHOW_SPEED speed, bool isShowbreathAfterShow){
	node->stopAllActions();
	node->setScale(0);
	float _duration = 0.1;
	if (speed == FAST){
		_duration = 0.05f;
	}
	else if (speed == MIDDLE){
		_duration = 0.1f;
	}
	else if (speed == SLOW){
		_duration = 0.15f;
	}

	auto delay1 = DelayTime::create(delay);
	auto scale1 = ScaleTo::create(_duration, 1.3f);
	auto scale2 = ScaleTo::create(_duration, 0.9f);
	auto scale3 = ScaleTo::create(_duration, 1.0f);

	if (isShowbreathAfterShow){
		auto seq = Sequence::create(delay1, scale1, scale2, scale3, CallFuncN::create(CC_CALLBACK_1(Form::ButtonBreathAction, this)), NULL);
		node->runAction(seq);
	}
	else {
		auto seq = Sequence::create(delay1, scale1, scale2, scale3, NULL);
		node->runAction(seq);
	}
}

void Form::ButtonBreathAction(Node *node){
	node->stopAllActions();
	auto scale1 = ScaleTo::create(1.0f, 1.1f);
	auto scale2 = ScaleTo::create(1.0f, 1.0f);
	auto seq = Sequence::create(scale1, scale2, NULL);
	node->runAction(RepeatForever::create(seq));
}

ImageView* Form::ShowShouTips(ETipsType type, int  Distance, float delay)
{
	auto pTipImg = ImageView::create("ani_tip_shou.png", Widget::TextureResType::PLIST);
	switch (type)
	{
	case ETipsType_Up_Down:
		{
			auto move1 = MoveBy::create(Distance*.002f, ccp(0, -Distance));
			auto move2 = MoveBy::create(Distance*.002f, ccp(0, Distance));
			auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
			pTipImg->runAction(seq);
		}
		break;
	case ETipsType_Left_Right:
		{		
			auto move1 = MoveBy::create(Distance*.002f, ccp(Distance, 0));
			auto move2 = MoveBy::create(Distance*.002f, ccp(-Distance, 0));
			auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
			pTipImg->runAction(seq);
		}
		break;
	case ETipsType_Right_Left:
		{		
			auto move1 = MoveBy::create(Distance*.002f, ccp(-Distance, 0));
			auto move2 = MoveBy::create(Distance*.002f, ccp(Distance, 0));
			auto seq = RepeatForever::create(Sequence::create(move1, move2, NULL));
			pTipImg->runAction(seq);
		}
		break;
	case ETipsType_Click:
		{
			pTipImg->setVisible(false);
			pTipImg->runAction(Sequence::create(DelayTime::create(delay), CallFuncN::create([this](Node* pNode){
				pNode->setVisible(true);
				auto move1 = MoveBy::create(.25f, ccp(20, 20));
				auto scale1 = ScaleTo::create(.25f, 1.2f);
				auto move2 = MoveBy::create(.25f, ccp(-20, -20));
				auto scale2 = ScaleTo::create(.25f, 1.0f);

				auto spawn1 = Spawn::create(move1, scale1, NULL);
				auto spawn2 = Spawn::create(move2, scale2, NULL);
				auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));
				pNode->runAction(seq);

				}), NULL));
			}
		break;
	}

	return pTipImg;
}

void Form::showPlayPopAD(float delay, bool isForce)
{
	SupSDK::instance()->showPopADBegin(isForce);
	auto pScene = BabyCare::instance()->getCurrScene();
	if (pScene != NULL)
	{
		pScene->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([this, isForce]{
			SupSDK::instance()->showPopADEnd(isForce);
		}), NULL));
	}
}

void Form::showPopAD(float delay, bool type)
{
	Player* pPlayer = EntityMgr::instance()->pPlayer();
	if (pPlayer->readNoAdsStatus())
	{
		return;
	}
	SupSDK::instance()->showPopADBegin(type);

	Director::getInstance()->getRunningScene()->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([this, type]{
		SupSDK::instance()->showPopADEnd(type);
	}), NULL));
}
