/*
** implement utility functions for c string or cpp string
** author: zc
** date: 2014.05.16
*/

#include "../SupMacros.h"

namespace sup {
// ---------------------------------------------------------------------------------
// SupString
// ---------------------------------------------------------------------------------
template<typename Iter>
string SupString::join(const string &sp, Iter begin, Iter end)
{
	string s;
	Iter last, iter;
	SUP_EXIT_IF(begin == end);

	last = end - 1;
	if (begin < last)
	{
		for(iter = begin; iter != last; ++iter)
		{
			s.append(*iter);
			s.append(sp);
		}
	}
	s += *last;

exit0:
	return s;
}

// -----------------------------------------------------------------------
template<template<typename, typename Alloc=std::allocator<string> > class Container>
void SupString::split(Container<string>& out, const char* cstr, const char* sp, bool strip)
{
	if(*sp == 0) return;
	const char* pStart = cstr;
	const char* pEnd = cstr;
	const char* pSp = sp;
	const char* p;	
	while(true)
	{
		if(*pEnd == 0)				// ËÑË÷´®½áÊø
		{
			out.push_back(strip ? 
				trim(string(pStart, pEnd)) :
				string(pStart, pEnd));
			break;
		}

		p = pEnd;		
		while(*p == *pSp && *p != 0 && *pSp != 0)
		{ ++p; ++pSp; }
		if(*pSp == 0)				// ÕÒµ½×Ó´®
		{
			out.push_back(strip ? 
				trim(string(pStart, pEnd)) :
				string(pStart, pEnd));
			pStart = pEnd = p;
		}
		else
		{
			++pEnd;
		}
		pSp = sp;
	}
}

template<template<typename, typename Alloc=std::allocator<string> > class Container>
void SupString::split(Container<string>& out, const string& str, const char* sp, bool strip)
{
	if(*sp == 0) return;
	size_t pos = 0, end;
	while(true)
	{
		end = str.find(sp, pos);
		if(end == str.npos) break;
		out.push_back(strip ? 
			trim(str.substr(pos, end-pos)):
			str.substr(pos, end-pos));
		pos = end + 1;
	}
	out.push_back(str.substr(pos));
}

template<template<typename, typename Alloc=std::allocator<string> > class Container>
inline void SupString::split(Container<string>& out, const string& str, const string& sp, bool strip)
{
	split(out, str, sp.c_str(), strip);
}

template<template<typename, typename Alloc=std::allocator<string> > class Container>
inline void SupString::split(Container<string>& out, const char* cstr, char sp, bool strip)
{
	char sps[] = {sp, 0};
	split(out, cstr, sps, strip);
}

template<template<typename, typename Alloc=std::allocator<string> > class Container>
inline void SupString::split(Container<string>& out, const string& str, char sp, bool strip)
{
	split(out, str, string(1, sp), strip);
}


// ---------------------------------------------------------------------------------
// SupCString£¨C ×Ö·û´®£©
// ---------------------------------------------------------------------------------

}