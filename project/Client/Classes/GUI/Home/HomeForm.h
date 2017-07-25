#ifndef __GUI_HomeForm_H__
#define __GUI_HomeForm_H__

#include "../Form.h"
#include "GUI/Form/BabyControl.h"

class HomeForm : public Form
{
public:
	CREATE_(HomeForm)
		_INST(HomeForm)

		virtual bool init();
	HomeForm();
	virtual ~HomeForm();

private:

	Armature* m_pArmature;
	SkeletonAnimation* m_sktPersonAni;
	SkeletonAnimation* m_sktBiaotiAni;
	spSkeletonBounds* m_pSkeletonBounds;
	spPolygon* m_pCheckPoly;
	Layout* m_pstar;

	Layout* m_pLogoPos;
	BabyControl* m_pBabyControl;
	bool m_isClickStart;

public:
	void onMoreButtonClicked(Ref *sender, TouchEventType type);   //更多;
	void onCoinsButtonClicked(Ref *sender, TouchEventType type);	//积分墙;	
	void onSettingButtonClicked(Ref *sender, TouchEventType type);
	void onMinigameButtonClicked(Ref *sender, TouchEventType type);
	void onParentsButtonClicked(Ref *sender, TouchEventType type);

	bool onTouchBeginListener(Touch *touch, Event *unusedEvent);
	void tankuang(Ref* object);

	void updateicon(float dt);

	void updatedui(float dt);
	void buySuccess(Ref* object);
	void buyFailed(Ref* object);
	void buyTimeout(Ref* object);

	void moredot_can(Ref* object);
	void coinsdot_can(Ref* object);

	ImageView* Image_coindot;
	ImageView* Image_moredot;

};

#endif //__GUI_HomeForm_H__