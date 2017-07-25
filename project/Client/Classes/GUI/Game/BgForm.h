/*
** declare BgForm Base
** author: zhang chao;
** date: 2015.11.30
*/

#ifndef __GUI_BgForm_H__
#define __GUI_BgForm_H__

#include "BgForm.h"
#include "../UIFactory.h"
#include "BabyCare.h"
#include "SaveManager/SaveManage.h"
class BgForm : public Form
{
public:
	CREATE_(BgForm, EGameLevel eType)
		_INST(BgForm, eType)

		virtual bool init();
	BgForm(EGameLevel eType);
	virtual ~BgForm();

private:
	Node* m_BgNode;
	ImageView* m_pGameBg;
	Layout* m_pPanel;

	Layout* m_pPanel_Paizhao;
	ImageView* m_pGameBg_Paizhao;

	EGameLevel m_eType;

	Layout* m_pPanelJiesuan1;
	Layout* m_pPanelJiesuan2;

	bool m_isJiesuanBGVisual;

public:
	virtual RenderTexture* getPictureRender();

	void RefreshBackground(string strBg1, string strBg2);
	void ChangeCameraBg(bool bVisual);
	void ChangeBgScale(float fScale);

	void setJiesuanBg(int iType, bool bVisual);
	void setJiesuanBGVisual(int iType, bool bVisual);

};

#endif //