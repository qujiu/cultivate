/*
** implement utility inline functions for c string or cpp string
** author: zc
** date: 2014.05.16
*/

#include <string.h>		// memset(...)

namespace sup{

// ---------------------------------------------------------------------------------
// SupString
// ---------------------------------------------------------------------------------
inline string SupString::float2String(float value)
{
	return double2String(value);
}

inline int SupString::string2Int(const string& str)
{
	return SupCString::string2Int(str.c_str());
}

inline float SupString::string2Float(const string& str)
{
	return (float)string2Double(str);
}

inline double SupString::string2Double(const string& str)
{
	return SupCString::string2Double(str.c_str());
}

inline bool SupString::isWhiteSpace(const string& str)
{
	return SupCString::isWhiteSpace(str.c_str());
}

// -----------------------------------------------------------------------
inline bool SupString::equal(const string& src, const string& dst, bool ignorCase)
{
	return ignorCase ? toLower(src).compare(dst) == 0 : src.compare(dst) == 0;
}

inline bool SupString::equal(const string& src, const char* cdst, bool ignorCase)
{
	return ignorCase ? toLower(src).compare(cdst) == 0 : src.compare(cdst) == 0;
}

// ---------------------------------------------------------------------------------
// SupCString£¨C ×Ö·û´®£©
// ---------------------------------------------------------------------------------
inline float SupCString::string2Float(const char* cstr)
{
	return (float)string2Double(cstr);
}

inline void SupCString::makeCharLine(char buff[], char chr, unsigned len)
{
	memset(buff, chr, (size_t)len);
	buff[len-1] = 0;
}

}