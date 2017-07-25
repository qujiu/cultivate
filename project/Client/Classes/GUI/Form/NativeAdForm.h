#ifndef __NativeAd_FORM_H__
#define __NativeAd_FORM_H__
#include "../Form.h"


class NativeAdForm : public Form
{
public:
	CREATE_(NativeAdForm)
		_INST(NativeAdForm);

	virtual bool init();

	NativeAdForm();
	virtual ~NativeAdForm();

private:
	void updateComplete(float t);
private:
	ImageView* m_pImg[3];
	int m_loadIndex;
};

#endif