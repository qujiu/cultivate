/*
** declare DialogForm
** author: zhangchao;
** date: 2014.10.09
*/

#ifndef __DIALOG_FORM_H__
#define __DIALOG_FORM_H__
#include "../Form.h"

class FontStyle{
public:
	FontStyle(){};
	FontStyle(string text) :
		text(text){};

	string text;
};

typedef std::map<string, FontStyle> MBParam;

/////////////////////////////////////////////////////////////////////
typedef void (Ref::*MBHandler)(MBCLICK_TYPE, void*);
typedef void(*MBCBFunc)(MBCLICK_TYPE, void*);

#define MBCall(func)\
	AlertHandler(static_cast<Ref*>(this), (MBHandler)&func)
#define MBARGCall(func, pStuff)\
	AlertHandler(static_cast<Ref*>(this), (MBHandler)&func, pStuff)
//////////////////////////////////////////////////////////////////////

class AlertHandler
{
public:
	AlertHandler(Ref *pOwner, MBHandler pHandler, void *pStuff = nullptr)
		: m_pStuff(pStuff), m_pHandler(pHandler), m_pOwner(pOwner), m_pCBFunc(nullptr)
	{
	};
	AlertHandler(MBCBFunc func, void *pStuff = nullptr)
		:m_pCBFunc(func), m_pStuff(pStuff), m_pOwner(nullptr)
	{
	};
	AlertHandler()
		:m_pCBFunc(nullptr), m_pOwner(nullptr){}

	void call(MBCLICK_TYPE ret)
	{
		if (m_pCBFunc){
			(*m_pCBFunc)(ret, m_pStuff);
		}
		else if (m_pOwner){
			(m_pOwner->*m_pHandler)(ret, m_pStuff);
		}
	};

private:
	Ref *m_pOwner;
	MBHandler m_pHandler;
	MBCBFunc m_pCBFunc;
	void *m_pStuff;
};



//////////////////////////////////////////////////////////

class DialogBase : public Form
{
public:
	CREATE_(DialogBase, string text, const AlertHandler& handler)
		_INST(DialogBase, text, handler);

	virtual bool init();
	DialogBase(string& text, const AlertHandler& handler);
	virtual ~DialogBase();

protected:
	string          m_Content;
	Layout		    *m_pLayout;
	AlertHandler    m_Handler;
	ImageView*      m_pBkImage;

	Button* m_pOKButton;
	Button* m_pYesButton;
	Button* m_pNoButton;
};

///////////////////////////////////////////////////////////


class Dialog_OK : public DialogBase
{
public:
	CREATE_(Dialog_OK, string text, const AlertHandler& handler)
		_INST(Dialog_OK, text, handler)

		virtual bool init();
	Dialog_OK(string& text, const AlertHandler& handler);
	virtual ~Dialog_OK();

public:
	void onOKButtonClicked(Ref *sender, TouchEventType type);
};

///////////////////////////////////////////////////////////

class Dialog_YesNo : public DialogBase
{
public:
	CREATE_(Dialog_YesNo, string text, const AlertHandler& handler)
		_INST(Dialog_YesNo, text, handler)

		virtual bool init();
	Dialog_YesNo(string& text, const AlertHandler& handler);
	virtual ~Dialog_YesNo();

public:
	void onYesButtonClicked(Ref *sender, TouchEventType type);
	void onNoButtonClicked(Ref *sender, TouchEventType type);
private:

};

///////////////////////////////////////////////////////////

#endif