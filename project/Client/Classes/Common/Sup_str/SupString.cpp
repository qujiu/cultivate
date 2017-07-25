/*
** implement utility functions for c string or cpp string
** author: zc
** date: 2014.05.16
*/

#include <cassert>
#include "SupString.h"
#include "../SupMacros.h"

namespace sup{

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996)		// 'strncpy(...)' vc warning
#endif

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

// ---------------------------------------------------------------------------------
// inner functions
// ---------------------------------------------------------------------------------
static inline bool isdigitChar(int chr)
{
	return chr >= '0' && chr <= '9';
}

static inline bool isupperChar(int chr)
{
	return chr >= 'A' && chr <= 'Z';
}

static inline bool islowerChar(int chr)
{
	return chr >= 'a' && chr <= 'z';
}

static inline int toupperChar(int chr)
{
	if(islowerChar(chr))
		return chr - 32;
	return chr;
}

static inline int tolowerChar(int chr)
{
	if(isupperChar(chr))
		return chr + 32;
	return chr;
}

// ---------------------------------------------------------------------------------
// SupString
// ---------------------------------------------------------------------------------
bool SupString::isDigit(const string& str)
{
	string::const_iterator iter = str.begin();
	while(iter != str.end())
	{
		if(!isdigitChar(*iter++))
			return false;
	}
	return true;
}

string SupString::int2String(long long int value)
{
	char buff[16];
	SUP_SNPRINTF(buff, sizeof(buff), "%lld", value);
	return buff;
}

string SupString::double2String(double value)
{
	char buff[16];
	SUP_SNPRINTF(buff, sizeof(buff), "%f", value);
	return buff;
}

// -----------------------------------------------------------------------
string SupString::toUpper(const string& str)
{
	string result;
	string::const_iterator iter = str.begin();
	while(iter != str.end())
	{
		result.append(1, islowerChar(*iter) ?
			toupperChar(*iter++) : *iter++);
	}
	return result;
}

string& SupString::toUpper(string& str)
{
	string::iterator iter = str.begin();
	while(iter != str.end())
	{
		if(islowerChar(*iter))
			*iter = toupperChar(*iter);
		++iter;
	}
	return str;
}

string SupString::toLower(const string& str)
{
	string result;
	string::const_iterator iter = str.begin();
	while(iter != str.end())
	{
		result.append(1, isupperChar(*iter) ?
			tolowerChar(*iter++) : *iter++);
	}
	return result;
}

string& SupString::toLower(string& str)
{
	string::iterator iter = str.begin();
	while(iter != str.end())
	{
		if(isupperChar(*iter))
			*iter = tolowerChar(*iter);
		++iter;
	}
	return str;
}

// -----------------------------------------------------------------------
string SupString::ltrim(const string& str)
{
	size_t pos = str.find_first_not_of(' ');
	return pos == str.npos ? "" : str.substr(pos);
}

string& SupString::ltrim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));
	return str;
}

string SupString::rtrim(const string& str)
{
	string result(str);
	size_t pos = str.find_last_not_of(' ');
	pos = pos == str.npos ? 0 : pos + 1;
	result.erase(pos, str.npos);
	return result;
}

string& SupString::rtrim(string& str)
{
	size_t pos = str.find_last_not_of(' ');
	pos = pos == str.npos ? 0 : pos + 1;
	str.erase(pos, str.npos);
	return str;
}


string SupString::trim(const string& str)
{
	size_t pos1 = str.find_first_not_of(' ');
	size_t pos2 = str.find_last_not_of(' ');

	if (pos1 == str.npos) 
	{
		if(pos2 == str.npos)
			return "";
		pos1 = 0; 
	}	
	if (pos2 != str.npos) {++pos2;}
	return str.substr(pos1, pos2-pos1);
}

string& SupString::trim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));
	size_t pos = str.find_last_not_of(' ');
	pos = pos == str.npos ? 0 : pos + 1;
	str.erase(pos, str.npos);
	return str;
}

// -----------------------------------------------------------------------
string& SupString::replace(string &str, const string& strOld, const string& strNew)
{
	string::size_type pos = 0;
	while((pos = str.find(strOld, pos)) != string::npos)
		str.replace(pos++, strOld.size(), strNew);
	return str;
}

string& SupString::replace(string &str, const char* cstrOld, const char* cstrNew)
{
	size_t oldLen = strlen(cstrOld);
	string::size_type pos = 0;	
	while((pos = str.find(cstrOld, pos)) != string::npos)
	{
		str.replace(pos++, oldLen, cstrNew);
	}
	return str;
}

string SupString::replace(const string &str, const string& strOld, const string& strNew)
{
	string result(str);
	return SupString::replace(result, strOld, strNew);				// 期望编译器能将该临时变量优化为返回的临时变量
}

string SupString::replace(const string &str, const char* cstrOld, const char* cstrNew)
{
	string result(str);
	return SupString::replace(result, cstrOld, cstrNew);			// 期望编译器能将该临时变量优化为返回的临时变量
}


// ---------------------------------------------------------------------------------
// SupCString（C 字符串）
// ---------------------------------------------------------------------------------
bool SupCString::isDigit(const char* cstr)
{
	const char* p = cstr;
	while(*p != 0)
	{
		if(!isdigitChar(*p++))
			return false;
	}
	return true;
}

// -----------------------------------------------------------------------
// 解释无符号整数(不包括 *p2)
static int tranUInt(const char* p1, const char* p2)
{
	assert(p1 != p2);					// 空串
	int value = 0, power = 1;
	do {
		--p2;
		assert(isdigitChar(*p2));
		value += power * (*p2 - '0');
		power *= 10;
	}while(p2 != p1);
	return value;
}

// 解释浮点数部分(不包括 *p2)
static double tranDecimal(const char* p1, const char* p2)
{
	assert(p1 != p2);							// 空串
	double value = 0.0f, power = 10.0;
	do {
		assert(isdigitChar(*p1));
		value += (*p1 - '0') / power;
		++p1; power *= 10.0;
	}while(p1 != p2);
	return value;
}

int SupCString::string2Int(const char* cstr)
{
	//const char* p = cstr;
	//int m = 1;
	//if(*p == '-') { ++p; m = -1; }
	//else if(*p == '+') { ++p; }
	//assert(*p != 0);							// 不是空串
	//p = cstr + strlen(cstr);
	//return m * tranUInt(cstr, p);

	if (!cstr) return 0;
	int i;
	sscanf(cstr, "%d", &i);
	return i;
}

double SupCString::string2Double(const char* cstr)
{
	assert(*cstr != 0);
	const char* pDot = strchr(cstr, '.');		// 小数点位置
	if(pDot == NULL) 
		return (double)string2Int(cstr);		// 没有小数点

	double m = 1.0;								// 确定正负
	const char* p = cstr;
	if(*p == '-') { ++p; m = -1.0; }
	else if(*p == '+') { ++p; }

	const char* pEnd = cstr + strlen(cstr);
	if(p == pDot)								// 小数点开头
		return m * tranDecimal(++p, pEnd);

	double value = tranUInt(p, pDot);			// 整数部分
	p = pDot + 1;
	if(p != pEnd)
		value += tranDecimal(p, pEnd);
	return m * value;
}

// -----------------------------------------------------------------------
void SupCString::toUpper(char* buff, size_t size, const char* cstr)
{
	const char* pSrc = cstr;
	char* pDst = buff;
	size_t count = 0;
	while(++count < size && *pSrc != 0)
	{
		*pDst++ = islowerChar(*pSrc) ? 
			toupperChar(*pSrc++) : *pSrc++;
	}
	buff[*pSrc == 0 ? count : size-1] = 0;
}

void SupCString::toLower(char* buff, size_t size, const char* cstr)
{
	const char* pSrc = cstr;
	char* pDst = buff;
	size_t count = 0;
	while(++count < size && *pSrc != 0)
	{
		*pDst++ = isupperChar(*pSrc) ? 
			tolowerChar(*pSrc++) : *pSrc++;
	}
	buff[*pSrc == 0 ? count : size-1] = 0;
}

// -----------------------------------------------------------------------
bool SupCString::isWhiteSpace(const char* cstr)
{
	const char* p = cstr;
	while(*p != 0)
	{
		if(*p != ' ' && *p != '\t' &&
			*p != '\r' && *p != '\n') 
				return false;
		++p;
	}
	return true;
}

bool SupCString::isStartsWidth(const char* cstr, const char* sub)
{
	const char* p1 = cstr;
	const char* p2 = sub;
	while(*p2 != 0)
	{
		if(*p1 == 0 || *p1 != *p2)
			return false;
		++p1; ++p2;
	}
	return true;
}

bool SupCString::isEndsWidth(const char* cstr, const char* sub)
{
	const char* p1 = cstr + strlen(cstr);
	const char* p2 = sub + strlen(sub);
	while(p2 != sub)
	{
		if(p1 == cstr || *p1 != *p2)
			return false;
		--p1; --p2;
	}
	return true;
}

// -----------------------------------------------------------------------
void SupCString::ltrim(char* buff, size_t size, const char* cstr)
{
	const char* p = cstr;
	while(*p == ' '){++p;};
	strncpy(buff, p, size);
	buff[size-1] = 0;
}

void SupCString::rtrim(char* buff, size_t size, const char* cstr)
{
	memset(buff, 0, size);
	size_t len = strlen(cstr);
	if(len == 0) return;

	const char* p = cstr + len;
	while(p!=cstr && *--p==' '){--len;}
	strncpy(buff, cstr, min(size-1, len));
}

void SupCString::trim(char* buff, size_t size, const char* cstr)
{
	memset(buff, 0, size);
	size_t len = strlen(cstr);
	if(len == 0) return;

	const char* p1 = cstr;
	const char* p2 = cstr + len;
	while(*p1 == ' '){++p1; --len;};
	while(p2 != cstr && *--p2 == ' '){--len;}
	strncpy(buff, p1, min(size-1, len));
}

// -----------------------------------------------------------------------
void SupCString::replace(char* buff, size_t size, const char* cstr, const char* cstrOld, const char* cstrNew)
{
	size_t oldLen = strlen(cstrOld);
	size_t newLen = strlen(cstrNew);
	char* pBuff = buff;
	const char* p = cstr;
	while(*p != 0 && size > 0)
	{
		if (isStartsWidth(p, cstrOld))
		{
			p += oldLen;
			if(size > newLen)				// 确保不会缓冲溢出（溢出将会将字符串截断）
			{
				strcpy(pBuff, cstrNew);
				pBuff += newLen;
				size -= newLen;
			}
			else
			{
				strncpy(pBuff, cstrNew, size);
				pBuff += size;
				break;
			}
		}
		else
		{
			*pBuff++ = *p++;
			--size;
		}
	}
	*pBuff = 0;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

}