/*
** declare UILuckyForm
** author: zhang chao;
** date: 2014.10.09
*/

#ifndef __GUI_UILuckyForm_H__
#define __GUI_UILuckyForm_H__

#include "../Form.h"

class UILuckyForm : public Form
{
public:
	CREATE_(UILuckyForm)
		_INST(UILuckyForm)

		virtual bool init();
	UILuckyForm();
	virtual ~UILuckyForm();

private:
	Layout* m_pGeceng;
	ImageView* m_pBg;
	vector<int> m_vItems;
	bool m_bClickBuyItem;
	vector<int> m_glod;
	vector<Button*> m_Button;
	vector<TextAtlas*> m_Atlas;
	vector<ImageView*> m_lab_bg;
	vector<Vec2> m_baopo;
	vector<Node*> m_paction;
	vector<int > m_baoid;
	vector<int > m_baoglob;

	ActionTimeline* m_pActionTimeline;
	Node* m_pTimelineNode;
	Node* UIlucky;
	int png_id;
	int glob_count;

	ImageView* m_lodao;
	ImageView* m_lclose;
	int daoju_id;
	int sound_id;//1道具音效2金币
public:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onCloseButtonCallback(Ref* object);
	void RefreshSubMenu();
	void ActionLucky(Ref* object);
	void LuckyJie(float dt);
	void creatglobfu();
	void randomGoldmove(float& x, float& y);
	void createglob(float dt);
	void createdaoju(float dt);
	void createwu(float dt);
	void Actionte(Vec2 pos, int i);
	void results();
	void randomda();
	void onBuyGoldButtonClicked(Ref *sender, TouchEventType type);
	void onItemTouchListener(Ref* ref, TouchEventType type);
	void enableClickBuy(float dt);
	void ActionLuckySpecial(int iTag);

};

#endif //__GUI_UILuckyForm_H__