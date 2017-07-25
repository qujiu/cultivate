/*
** declare BabyRoomForm
** author: zhang chao;
** date: 2015.5.13
*/
#ifndef __REWARD_FORM_H__
#define __REWARD_FORM_H__

#include "../Form.h"

class RewardForm : public Form
{
public:
	CREATE_(RewardForm, int type)
		_INST(RewardForm, type)

		virtual bool init();
	RewardForm(int type);
	virtual ~RewardForm();

private:
	ImageView* m_pKuangImg[10];
	ImageView* m_pIconImg[10];
	ImageView* m_pUseImg[10];
	TextAtlas* m_pGold[10];

	TextAtlas* m_pAwardGold;
	ImageView* m_pGoldImg;

	int m_nCountGold;
	int m_nAwardType;

	int m_nGold[10];
private:
	void setRewardInfo();
	int m_nIndex;

	void runGoldAction(int nIndex, int t);

	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void runGoldActionCallback(Node* node, void* num);

};

#endif //__MAM_ROOM_FORM_H__