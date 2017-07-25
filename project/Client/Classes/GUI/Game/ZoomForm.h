/*
** declare ZoomForm
** author: zhang chao;
** date: 2015.04.02
*/

#ifndef __GUI_ZoomForm_H__
#define __GUI_ZoomForm_H__

#include "../Form.h"

class ZoomForm : public Form
{
public:
	CREATE_(ZoomForm)
		_INST(ZoomForm)

	virtual bool init();
	ZoomForm();
	virtual ~ZoomForm();

private:
	DrawNode* m_pDrawNode;
	ClippingNode* m_pClippingNode;
public:
	
	void onNextButtonClicked(Ref *sender, TouchEventType type);
	void onXiJunButtonClicked(Ref *sender, TouchEventType type);
	void onHitComplete(Node* node);
};

#endif //__GUI_RoomForm_H__