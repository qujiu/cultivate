/*
** implement utility functions for cocoex ;
** author: zhang chao;
** date: 2015.11.27
*/

#include "SupCocoex.h"

namespace sup{

	////////////////////////////SupTips/////////////////////////////////////////////////////////////////////////////////

	ImageView* SupTips::ShowHandTips(ETipsType type, int  Distance)//, float delay)
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
								pTipImg->setAnchorPoint(ccp(0, 1));
								auto move1 = MoveBy::create(.25f, ccp(20, 20));
								auto scale1 = ScaleTo::create(.25f, 1.2f);
								auto move2 = MoveBy::create(.25f, ccp(-20, -20));
								auto scale2 = ScaleTo::create(.25f, 1.0f);

								auto spawn1 = Spawn::create(move1, scale1, NULL);
								auto spawn2 = Spawn::create(move2, scale2, NULL);

								auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));

								//pTipImg->setVisible(false);
								//pTipImg->runAction(Sequence::create(DelayTime::create(delay), CallFuncN::create([=](Node* pNode){
								//	pNode->setVisible(true);
								//	auto move1 = MoveBy::create(.25f, ccp(20, 20));
								//	auto scale1 = ScaleTo::create(.25f, 1.2f);
								//	auto move2 = MoveBy::create(.25f, ccp(-20, -20));
								//	auto scale2 = ScaleTo::create(.25f, 1.0f);

								//	auto spawn1 = Spawn::create(move1, scale1, NULL);
								//	auto spawn2 = Spawn::create(move2, scale2, NULL);
								//	auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));
								//	pNode->runAction(seq);

								//	}), NULL));
								//}

		}
			break;
		default:
			break;
		}
		return pTipImg;
	}



	ImageView* SupTips::ShowArrowsTips(ETipsType type, int  Distance)//, float delay)
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
								pTipImg->setAnchorPoint(ccp(0, 1));
								auto move1 = MoveBy::create(.25f, ccp(20, 20));
								auto scale1 = ScaleTo::create(.25f, 1.2f);
								auto move2 = MoveBy::create(.25f, ccp(-20, -20));
								auto scale2 = ScaleTo::create(.25f, 1.0f);

								auto spawn1 = Spawn::create(move1, scale1, NULL);
								auto spawn2 = Spawn::create(move2, scale2, NULL);

								auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));

								//pTipImg->setVisible(false);
								//pTipImg->runAction(Sequence::create(DelayTime::create(delay), CallFuncN::create([=](Node* pNode){
								//	pNode->setVisible(true);
								//	auto move1 = MoveBy::create(.25f, ccp(20, 20));
								//	auto scale1 = ScaleTo::create(.25f, 1.2f);
								//	auto move2 = MoveBy::create(.25f, ccp(-20, -20));
								//	auto scale2 = ScaleTo::create(.25f, 1.0f);

								//	auto spawn1 = Spawn::create(move1, scale1, NULL);
								//	auto spawn2 = Spawn::create(move2, scale2, NULL);
								//	auto seq = RepeatForever::create(Sequence::create(spawn1, spawn2, NULL));
								//	pNode->runAction(seq);

								//	}), NULL));
								//}

		}
			break;
		default:
			break;
		}
		return pTipImg;
	}


	///////////////////////////////SupTips end//////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void SupActions::MoveTo(Node* node, const Vec2& to, float delayTime)
	{
		if (node)
		{
			//node->stopAllActions();;
			auto move = MoveTo::create(delayTime, to);
			auto ease = EaseBackIn::create(move);
			node->runAction(Sequence::create(ease, NULL));
		}
	}

	void SupActions::MoveTo2(Node* node, const Vec2& to, float delayTime)
	{
		if (node)
		{
			//node->stopAllActions();
			auto delay = DelayTime::create(delayTime);
			auto move = MoveTo::create(.5f, to);
			auto ease = EaseBackOut::create(move);
			node->runAction(Sequence::createWithTwoActions(delay, ease));
		}
	}

	void SupActions::NodeIn(Node* node, Vec2& from, Vec2& to, float delayTime)
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

	void SupActions::NodeOut(Node* node, Vec2& to)
	{
		if (node)
		{
			//node->stopAllActions();
			auto move = MoveTo::create(.5f, to);
			auto ease = EaseExponentialIn::create(move);
			node->runAction(ease);
		}
	}

	void SupActions::NodeElasticAppear(Node* node, const std::function<void()>& func, float delat_time)
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

	void SupActions::NodeElasticDisAppear(Node* node, const std::function<void()>& func, float delat_time)
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

	ActionInterval* SupActions::genBounceShowAction()
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

	ActionInterval* SupActions::genBounceDisappearAction()
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

	void SupActions::PulseNode(Node* node, float to1, float to2, float dur, bool loop, bool stop_actions)
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

	void SupActions::RoteNode(Node* node, float to1, float to2, float dur, bool loop, bool stop_actions)
	{
		if (node)
		{
			if (stop_actions)
				node->stopAllActions();
			auto rote1 = RotateTo::create(dur, to1);
			auto rote2 = RotateTo::create(dur, 0);
			auto rote3 = RotateTo::create(dur, to2);
			auto seq = Sequence::create(rote1, rote2, rote3, rote2, rote1, rote2, rote3, rote2, rote1, rote2, rote3, rote2, DelayTime::create(2.0f), NULL);
			if (loop)
			{
				node->runAction(RepeatForever::create(seq));
			}
			else
			{
				node->runAction(seq);
			}
		}
	}

	void SupActions::ButtonAction(Node* node)
	{
		if (node)
		{
			node->stopAllActions();
			auto scale1 = ScaleTo::create(.1f, 1.2f, 0.8f);
			auto scale2 = ScaleTo::create(.1f, 0.8f, 1.2f);
			auto scale3 = ScaleTo::create(.1f, 1.0f, 1.0f);
			node->runAction(Sequence::create(scale1, scale2, scale3, NULL));
		}
	}

	void SupActions::ButtonActionForever(Node* node)
	{
		if (node)
		{
			node->stopAllActions();
			auto scale1 = ScaleTo::create(.1f, 1.2f, 0.8f);
			auto scale2 = ScaleTo::create(.1f, .8f, 1.2f);
			auto scale3 = ScaleTo::create(.1f, 1.0f, 1.0f);
			node->runAction(RepeatForever::create(Sequence::create(scale1, scale2, scale3, DelayTime::create(1.0f), NULL)));
		}
	}

	void SupActions::ButtonActionyuan(Node* node)
	{
		if (node)
		{
			node->stopAllActions();
			auto scale1 = ScaleTo::create(.1f, node->getScale()*0.8f);
			auto scale2 = ScaleTo::create(.1f, node->getScale()*1.2f);
			auto scale3 = ScaleTo::create(.1f, node->getScale()*1.0f);
			node->runAction(Sequence::create(scale1, scale2, scale3, NULL));
		}
	}

	void SupActions::FadeInNode(Node* node, float dur, bool zero_opacity, CallFunc* callFunc)
	{
		if (node)
		{
			node->setVisible(true);
			if (zero_opacity)
			{
				node->setOpacity(0);
			}

			if (callFunc)
			{
				node->runAction(Sequence::createWithTwoActions(FadeIn::create(dur), callFunc));
			}
			else
			{
				node->runAction(FadeIn::create(dur));
			}
		}
	}

	void SupActions::FadeOutNode(Node* node, float dur, CallFunc* callFunc)
	{
		if (node)
		{
			if (callFunc)
			{
				node->runAction(Sequence::createWithTwoActions(FadeOut::create(dur), callFunc));
			}
			else
			{
				node->runAction(FadeOut::create(dur));
			}
		}
	}

	void SupActions::BulgeNode(Node* node, float from, float to, CallFunc* callFunc)
	{
		SupActions::BulgeNode(node, Vec2(from, from), Vec2(to, to), callFunc);
	}

	void SupActions::BulgeNode(Node* node, Vec2 from, Vec2 to, CallFunc* callFunc)
	{
		if (node)
		{
			node->setScaleX(from.x);
			node->setScaleY(from.y);
			auto scaleTo = ScaleTo::create(0.3f, to.x, to.y);
			auto ease = EaseBackOut::create(scaleTo);
			if (callFunc == NULL)
			{
				node->runAction(ease);
			}
			else
			{
				node->runAction(Sequence::createWithTwoActions(ease, callFunc));
			}
		}
	}

	void SupActions::BulgeNodeReverse(Node* node, float from, float to, CallFunc* callFunc)
	{
		if (node)
		{
			node->setScale(to);
			auto scaleTo = ScaleTo::create(0.4f, from, from);
			auto ease = EaseBackIn::create(scaleTo);
			if (callFunc == NULL)
			{
				node->runAction(ease);
			}
			else
			{
				node->runAction(Sequence::createWithTwoActions(ease, callFunc));
			}
		}
	}

	void SupActions::JeteNode3(Node* node, float jete, float dur, bool loop, float delayTime)
	{
		if (node)
		{
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

	void SupActions::JeteNode3Scale(Node* node, float from, float to, float dur, bool loop, float delayTime)
	{
		if (node)
		{
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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SupActions::BulgeNodeReverse_Tip(Node* node, Vec2 vecFromPos, Vec2 vecToPos, float from, float to, CallFunc* callFunc)
	{
		if (node)
		{
			node->stopAllActions();
			node->setScale(to);
			node->setPosition(vecToPos);

			auto scaleTo = ScaleTo::create(0.5f, from);
			//auto ease1 = EaseBackOut::create(scaleTo);

			auto move = MoveTo::create(0.5f, vecFromPos);
			//auto ease2 = EaseBackOut::create(move);

			auto spawn = Spawn::create(scaleTo, move, NULL);

			if (callFunc == NULL)
			{
				node->runAction(spawn);
			}
			else
			{
				node->runAction(Sequence::createWithTwoActions(spawn, callFunc));
			}
		}
	}
}//end namespace sup