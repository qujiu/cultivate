#ifndef __SigninForm_H__
#define __SigninForm_H__
#include "../Form.h"


class SigninForm : public Form
{
public:
	CREATE_(SigninForm)
		_INST(SigninForm);

	virtual bool init();
	SigninForm();
	virtual ~SigninForm();

private:
	void onGetButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonCallback();

	void refreshSignInItem();

	void onGetGold1ButtonClicked(Ref *sender, TouchEventType type);
	void onGetGold2ButtonClicked(Ref *sender, TouchEventType type);

	void showGoldCreateAction();
	void showGoldMoveupAction(float dt);
	void playGoldMoveupSound();
	void showGoldPlusAction(Node* node, void* ivoid);
	void hideGoldPlusAction();
	void randomCreateGoldmove(float& x, float& y);

	void GetGoldFunc();

private:
	ImageView*      m_pBkImage;
	ImageView* m_pGeceng;
	ImageView* m_pBoardImg;

	Button* sigetbu;
	vector<int> m_vecSubItem;

	int m_iDays;
	LoadingBar* m_pLoadingBarImg;

	ActionTimeline* m_pActionTimeline;
	Node* m_pTimelineNode;
	ImageView* m_pGold1Img;
	ImageView* m_pGold2Img;

	int  creat_glob;
	int count_glob;
	int m_iCountGold;
	int glob;

	Layout* m_pCountLayout;
	TextAtlas* m_pCountText;
};

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////

#endif