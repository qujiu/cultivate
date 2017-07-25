/*
** implement utility functions for cocoex ;
** author: zhang chao;
** date: 2015.11.27
*/


#ifndef __SUP_COCOEX_H__
#define __SUP_COCOEX_H__

#include "define.h"

namespace sup{

	// ---------------------------------------------------------------------------------
	// SupTips
	// ---------------------------------------------------------------------------------
	namespace SupTips
	{
		typedef enum ETipsType
		{
			ETipsType_Left_Right,
			ETipsType_Right_Left,
			ETipsType_Up_Down,
			ETipsType_Down_Up,
			ETipsType_Click,

		}ETipsType;

		ImageView* ShowHandTips(ETipsType type, int  Distance = 200);//, float delay = 0.0f);
		ImageView* ShowArrowsTips(ETipsType type, int  Distance = 200);
	}//end SupTips

	namespace SupActions
	{
		//delayTime 时间 move 到 to 位置;
		void MoveTo(Node* node, const Vec2& to, float delayTime = 0);

		//停止delayTime后再move;
		void MoveTo2(Node* node, const Vec2& to, float delayTime = 0);

		void NodeIn(Node* node, Vec2& from, Vec2& to, float delay = 0);
		void NodeOut(Node* node, Vec2& to);

		//node缩放跳动效果;
		void PulseNode(Node* node, float to1, float to2, float dur, bool loop = false, bool stop_actions = true);
		//node缩放膨胀效果;
		void BulgeNode(Node* node, float from, float to, CallFunc* callFunc = NULL);
		void BulgeNode(Node* node, Vec2 from, Vec2 to, CallFunc* callFunc = NULL);
		void BulgeNodeReverse(Node* node, float from, float to, CallFunc* callFunc = NULL);

		void BulgeNodeReverse_Tip(Node* node, Vec2 vecFromPos, Vec2 vecToPos, float from, float to, CallFunc* callFunc);

		//按钮果冻效果;
		void ButtonAction(Node* node);
		//按钮果冻效果;
		void ButtonActionyuan(Node* node);

		void ButtonActionForever(Node* node);



		//淡入淡出;
		void FadeInNode(Node* node, float dur = .2f, bool zero_opacity = true, CallFunc* callFunc = NULL);
		void FadeOutNode(Node* node, float dur = .2f, CallFunc* callFunc = NULL);

		//
		void JeteNode3(Node* node, float jete, float dur, bool loop, float delayTime = 0);
		void JeteNode3Scale(Node* node, float from, float to, float dur, bool loop, float delayTime = 0);

		void NodeElasticAppear(Node* node, const std::function<void()>& func = nullptr, float delat_time = 0.0f);
		void NodeElasticDisAppear(Node* node, const std::function<void()>& func = nullptr, float delat_time = 0.0f);

		void RoteNode(Node* node, float to1, float to2, float dur, bool loop = false, bool stop_actions = true);

		ActionInterval* genBounceShowAction();
		ActionInterval* genBounceDisappearAction();
	}

}

#endif