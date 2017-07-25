#ifndef __MESSAGEBOX_H__
#define __MESSAGEBOX_H__

#include "DialogForm.h"
using namespace std;

struct MessageBoxArg
{
	MessageBoxArg(const AlertHandler& handler)
	:handler(handler)
	{
		info = "";
		type = MT_YES;
	};
	string info;
	const AlertHandler& handler;
	MT_TYPE type;
	MBParam param;
};

//////////////////////////////////////////////////////////////////////////
void showMessageBox(const string& info);
void showMessageBox(const string& info, const AlertHandler& pHandler, MT_TYPE type = MT_YESNO);
void showMessageBox(const string& info, const MBParam &param);
void showMessageBox(const string& info, const AlertHandler& pHandler, const MBParam &param, MT_TYPE type = MT_YESNO);

void showMessageBoxID(const string& ID);	//通过信息ID输出对话框
void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MT_TYPE type = MT_YESNO);
void showMessageBoxID(const string& ID, MBParam& param);
void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MBParam& param, MT_TYPE type = MT_YESNO);

//////////////////////////////////////////////////////////////////////////

//获取一个用指定参数替换后的提示信息字符串;
//参数：;
//param:是一个map key是消息的参数 形式一般是*XXX*  替换为value
//ID:   提示信息的编号;
//返回值;
//		返回用param替换后的提示信息;
string getMessageStringID(const string& ID, MBParam& param);
string getMessageStringID(const string& ID);
string getMessageString(const string& info, MBParam& param);


#endif