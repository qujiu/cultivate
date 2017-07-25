#ifndef __LOADINGFORM_H__
#define __LOADINGFORM_H__
#include "../Form.h"


class LoadingForm : public Form
{
public:
	CREATE_(LoadingForm)
		_INST(LoadingForm);

	virtual bool init();
	LoadingForm();
	virtual ~LoadingForm();
private:
	void updateComplete(float t);
private:

};

#endif