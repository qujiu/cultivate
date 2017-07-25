/*
** declare DialogForm
** author: zhangchao;
** date: 2014.10.09
*/

#ifndef __VIDEO_FORM_H__
#define __VIDEO_FORM_H__
#include "../Form.h"


class VideoForm : public Form
{
public:
	CREATE_(VideoForm, int iType)
		_INST(VideoForm, iType);

	virtual bool init();
	VideoForm(int iType);
	virtual ~VideoForm();

private:
	void onCloseButtonClicked(Ref *sender, TouchEventType type);
	void onRateButtonClicked(Ref *sender, TouchEventType type);
	void onVideoButtonClicked(Ref *sender, TouchEventType type);
private:
	ImageView* m_pBkImage;
	ImageView* m_pBoxImg;

	int m_iType;
};

///////////////////////////////////////////////////////////

#endif