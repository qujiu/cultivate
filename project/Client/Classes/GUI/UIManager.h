#ifndef __UIManager_H__
#define __UIManager_H__

#include "UIDefine.h"
#include "../define.h"

class Form;
class UIManager : public sup::Singleton<UIManager, Ref>
{
	friend class Form;
private:

	SINGLETON_FRIEND_SUB(UIManager, Ref);
	UIManager();
	virtual ~UIManager();

protected:
	Form *	m_FormArr[IDC_MAX_COUNT];
protected:
	Form* createForm(WINDOW_ID id, Form * form);
	void  releaseForm(WINDOW_ID id);

public:
	Form* findForm(WINDOW_ID id);
	
};

#endif //__UIManager_H