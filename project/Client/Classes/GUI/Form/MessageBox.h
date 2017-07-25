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

void showMessageBoxID(const string& ID);	//ͨ����ϢID����Ի���
void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MT_TYPE type = MT_YESNO);
void showMessageBoxID(const string& ID, MBParam& param);
void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MBParam& param, MT_TYPE type = MT_YESNO);

//////////////////////////////////////////////////////////////////////////

//��ȡһ����ָ�������滻�����ʾ��Ϣ�ַ���;
//������;
//param:��һ��map key����Ϣ�Ĳ��� ��ʽһ����*XXX*  �滻Ϊvalue
//ID:   ��ʾ��Ϣ�ı��;
//����ֵ;
//		������param�滻�����ʾ��Ϣ;
string getMessageStringID(const string& ID, MBParam& param);
string getMessageStringID(const string& ID);
string getMessageString(const string& info, MBParam& param);


#endif