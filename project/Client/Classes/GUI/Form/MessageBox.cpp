#include "MessageBox.h"
#include "ResManager/ConfigDataCenter.h"
#include "../UIFactory.h"

//////////////////////////////////////////////////////////////////////////
//messagebox;
/////////////////////////////////////////////////////////////////////////
void showMessageBox(const string& info, const MBParam &param)
{
	AlertHandler handler;
	MessageBoxArg arg(handler);
	arg.info = info;
	arg.type = MT_YES;
	arg.param = param;

	UIFactory::instance()->showMessgeBox(arg);
}

void showMessageBox(const string& info, const AlertHandler& pHandler, const MBParam &param, MT_TYPE type)
{
	MessageBoxArg arg(pHandler);
	arg.info = info;
	arg.type = type;
	arg.param = param;

	UIFactory::instance()->showMessgeBox(arg);
}

void showMessageBox(const string& info)
{
	AlertHandler handler;
	MessageBoxArg arg(handler);
	arg.info = info;
	arg.type = MT_YES;

	UIFactory::instance()->showMessgeBox(arg);
}

void showMessageBox(const string& info, const AlertHandler& pHandler, MT_TYPE type)
{
	MessageBoxArg arg(pHandler);
	arg.info = info;
	arg.type = type;

	UIFactory::instance()->showMessgeBox(arg);
}

void showMessageBoxID(const string& ID)
{
	const JsonValue &value = ConfigDataCenter::instance()->messageBox();
	string info = value[ID.c_str()].GetString();
	showMessageBox(info);

}

void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MT_TYPE type)
{
	const JsonValue &value = ConfigDataCenter::instance()->messageBox();
	string info = value[ID.c_str()].GetString();
	showMessageBox(info, pHandler, type);
}

void showMessageBoxID(const string& ID, MBParam& param)
{
	string info = getMessageStringID(ID);
	showMessageBox(info, param);
}

void showMessageBoxID(const string& ID, const AlertHandler& pHandler, MBParam& param, MT_TYPE type)
{
	string info = getMessageStringID(ID, param);
	showMessageBox(info, pHandler, param, type);
}


std::string getMessageStringID(const string& ID, MBParam& param)
{
	string info = getMessageStringID(ID);
	return getMessageString(info, param);
}

std::string getMessageStringID(const string& ID)
{
	const JsonValue &value = ConfigDataCenter::instance()->messageBox();
	return   value[ID.c_str()].GetString();

}

std::string getMessageString(const string& info, MBParam& param)
{
	MBParam::const_iterator iter = param.begin();
	while (iter != param.end()){
		string key = iter->first;
		sup::SupString::replace(info, key, iter->second.text);
		++iter;
	}
	return info;
}
