/*
** declare form class
** author: zhang chao;
** date: 2014.09.29
*/

#ifndef __FORM_H__
#define __FORM_H__

#include "../define.h"
#include "UIDefine.h"
#include "SoundManager/SoundManage.h"
#include "SupLayout.h"
#include "Entity/SupCocoex.h"
//////////////////////////////////////////////////////////
//确认框
typedef enum MT_TYPE
{
	MT_YES = 0,
	MT_YESNO,
	MT_YESNOCANCEL,

}MT_TYPE;

typedef enum MBCLICK_TYPE
{
	MBCLICK_YES = 0,
	MBCLICK_NO,
	MBCLICK_CANCEL,

}MBCLICK_TYPE;

typedef enum  FORM_SHOW_SPEED {
	FAST,
	MIDDLE,
	SLOW,
};

typedef enum ETipsType
{
	ETipsType_Left_Right,
	ETipsType_Right_Left,
	ETipsType_Up_Down,
	ETipsType_Click,

}ETipsType;

/////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------
//Root：程序自封装一些控件继承此类;
//-----------------------------------------------------------------------
class BaseControl : public Node
{
public:
	BaseControl();
	virtual ~BaseControl();
    virtual bool init();

protected:
    #define CREATE_(CLS, ...) \
public: static CLS* createInst(__VA_ARGS__)
    #define _INST(CLS, ...) { \
    CLS *pInst = new CLS(__VA_ARGS__); \
    if (pInst->init()) { pInst->autorelease(); return pInst; } \
    pInst->release(); return NULL; \
    }

public:
	CREATE_(BaseControl)_INST(BaseControl);

    virtual void onEnter();
    virtual void onExit();
};


// -----------------------------------------------------------------------
// Form
// -----------------------------------------------------------------------

class Form : public cocos2d::Layer
{
protected:
	WINDOW_ID _ID = IDC_NULL;
	
protected:
	#define CREATE_(CLS, ...) \
public: static CLS* createInst(__VA_ARGS__)
	#define _INST(CLS, ...) { \
	CLS *pInst = new CLS(__VA_ARGS__); \
	if (pInst->init()) { pInst->autorelease(); return pInst; } \
	pInst->release(); return NULL; \
	}

protected:
	Form(WINDOW_ID _ID);
public:

	CREATE_(Form, WINDOW_ID id)_INST(Form, id);
	virtual ~Form();

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

public:
	virtual RenderTexture* getPictureRender();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void onHomeBtnCallBack(MBCLICK_TYPE type, void* data);
public:
	void BulgeNode(Node* node, float from, float to, SEL_CallFunc selector = nullptr);
	void BulgeNode(Node* node, Vec2 from, Vec2 to, SEL_CallFunc selector = nullptr);
	void BulgeNodeReverse(Node* node, float from, float to, SEL_CallFunc selector = nullptr);

	void JeteNode3(Node* node, float jete, float dur, bool loop, float delay = 0);
	void JeteNode3Scale(Node* node, float from, float to, float dur, bool loop, float delayTime);

	void FadeInNode(Node* node, bool zero_opacity = true, float dur = .2f);
	void FadeOutNode(Node* node, float dur = .2f, SEL_CallFunc selector = nullptr);

	void MoveTo(Node* node, const Vec2& to, float delay = 0);
	void MoveTo2(Node* node, const Vec2& to, float delay = 0);
	void MoveTo3(Node* node, const Vec2& to, float delayTime = 0);
	void NodeIn(Node* node, Vec2& from, Vec2& to, float delay = 0);
	void NodeOut(Node* node, Vec2& to);

	void ButtonAction(Node* node, SEL_CallFunc selector = nullptr);

	void RotateScaleIn(Node* node, const std::function<void()>& func = nullptr);

	void PulseNode(Node* node, float to1, float to2, float dur, bool loop = false, bool stop_actions = true);
	void NodeElasticAppear(Node* node, const std::function<void()>& func = nullptr, float delat_time = 0.0f);
	void NodeElasticDisAppear(Node* node, const std::function<void()>& func = nullptr, float delat_time = 0.0f);

	ActionInterval* genBounceShowAction();
	ActionInterval* genBounceDisappearAction();


	void delayShowNode(Node *node, float delay, FORM_SHOW_SPEED speed = MIDDLE, bool isShowbreathAfterShow = false);
	void ButtonBreathAction(Node *node);

	virtual ImageView* ShowShouTips(ETipsType type, int  Distance = 200, float delay = 0.0f);

public:
	void showPlayPopAD(float delay = 0.5f, bool isForce = true);
	void showPopAD(float delay, bool  type);
protected:
	Widget		*m_pLayout;
	cocos2d::Size		m_winSize;
};

#endif