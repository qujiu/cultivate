
/*
** json value extention
** author: zhang chao;
** date: 2014.05.20
*/

#ifndef __JSON_VALUE_EX__
#define __JSON_VALUE_EX__

#include "Common/common.h"
#include "json/document.h"

using namespace std;
// -----------------------------------------------------------------------
// exceptions
// -----------------------------------------------------------------------

typedef rapidjson::Document JsonValue;

class JsonWraperEmptyBase{};

template<typename T=JsonWraperEmptyBase>
class JsonWraper : public T
{
public:
	// -----------------------------------------------------------------------
	// inners
	// -----------------------------------------------------------------------

	//// 暂时不做溢出防御
	//static int asInt(string key, const JsonValue &v)
	//{
	//	if (v.isInt()) { return v.asInt(); }
	//	if (v.isDouble()) { return (int)v.asDouble(); }
	//	if (v.isUInt()) { return (int)v.asUInt(); }
	//	return 0;
	//}
	//
	//// 暂时不做溢出防御
	//static unsigned asUInt(string key, const JsonValue &v)
	//{
	//	if (v.isUInt()) { return v.asUInt(); }
	//	if (v.isDouble()) { return (unsigned)v.asDouble(); }
	//	if (v.isInt()) { return (unsigned)v.asInt(); }
	//	return 0;
	//}
	//
	//// 暂时不做溢出防御
	//static float asFloat(string key, const JsonValue &v)
	//{
	//	if (v.isDouble()) { return (float)v.asDouble(); }
	//	if (v.isInt()) { return (float)v.asInt(); }
	//	if (v.isUInt()) { return (float)v.asUInt(); }
	//	return 0.0f;
	//}
	//
	//// 暂时不做溢出防御
	//static bool asBool(string key, const JsonValue &v)
	//{
	//	if (v.isBool()) { return v.asBool(); }
	//	if (v.isDouble()) { return v.asDouble() != 0.0f; }
	//	if (v.isInt()) { return v.asInt() != 0; }
	//	if (v.isUInt()) { return v.asUInt() != 0; }
	//	return false;
	//}
	//
	//static string asString(string key, const JsonValue &v)
	//{
	//	if (v.isString()) { return v.asString(); }
	//	if (v.isInt()) { return sup::SupString::int2String(v.asInt()); }
	//	if (v.isUInt()) { return sup::SupString::int2String(v.asUInt()); }
	//	if (v.isDouble()) { return sup::SupString::double2String(v.asDouble()); }
	//	return "";
	//}
	
public:
	JsonWraper(const JsonValue &doc)
		: m_jValue(doc)
	{
		//assert(!m_jValue.isNull());
	}

private:
	JsonWraper(const JsonWraper&);
	JsonWraper& operator=(const JsonWraper&);

public:

	// -----------------------------------------------------------------------
	// templates
	// -----------------------------------------------------------------------
	
	inline const JsonValue& orign() const
	{
		return m_jValue;
	}
	
	inline int hasKey(const string &key) const
	{
		return m_jValue.isNull();
	}

	inline int queryInt(const string &key, int def = 0) const
	{
		if (!hasKey(key))
		{
			return asInt(key, m_jValue[key]);
		}
		return def;
	}
	
	inline unsigned int queryUInt(const string &key, unsigned int def = 0) const
	{
		if (!hasKey(key))
		{
			return asUInt(key, m_jValue[key]);
		}
		return def;
	}
	
	inline float queryFloat(const string &key, float def = 0.0f) const
	{
		if (!hasKey(key))
		{
			return asFloat(key, m_jValue[key]);
		}
		return def;
	}
	
	inline string queryStr(const string &key, const string &def = "") const
	{
		if (!hasKey(key))
		{
			return asString(key, m_jValue[key]);
		}
		return def;
	}
	
	inline bool queryBool(const string &key, bool def = false) const
	{
		if (!hasKey(key))
		{
			return asBool(key, m_jValue[key]);
		}
		return def;
	}
		
	// ---------------------------------------------------

	void updateValue(const JsonValue &value)
	{
		auto iter = value.begin();
		while (iter != value.end())
		{
			string key = iter++.key().asString();
			if (!hasKey(key)) m_jValue[key] = value[key];
		}
	}
	
	void mergeValue(const JsonValue &value)
	{
		auto iter = value.begin();
		while (iter != value.end())
		{
			string key = iter++.key().asString();
			m_jValue[key] = value[key];
		}
	}

protected:
	JsonValue m_jValue;
};


#endif


	//inline bool hasKey(const string& key) const{
	//	return _JsonDoc[key].IsNull();
	//}

	//inline bool hasKey(const char* key ) const{
	//	return _JsonDoc[key].IsNull();
	//}

	//inline int queryInt(const string& key, int defvalue= -1) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asInt(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}

	//inline long long int queryInt64(const string& key, long long int defvalue = -1) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asInt64(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}

	//inline unsigned int queryUInt(const string& key, unsigned int defvalue = 0) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asUInt(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}

	//inline  unsigned long long int queryUInt64(const string& key, unsigned long long int defvalue = 0) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asUInt64(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}


	//inline float queryFloat(const string& key, float defvalue = 0.0) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asFloat(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}


	//inline string queryStr(const string& key, const string& defvalue = "") const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asString(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}


	//inline bool queryBool(const string& key, bool defvalue = false) const{
	//	if (!_JsonDoc[key.c_str()].IsNull())
	//	{
	//		return asBool(key, _JsonDoc[key.c_str()]);
	//	}
	//	return defvalue;
	//}

	//void updateValue(const JsonValue& value){
	//	auto iter = value.MemberonBegin();
	//	while (iter != value.MemberonEnd())
	//	{
	//		const char* key = (iter++)->name.GetString();
	//		if (hasKey(key)) _JsonDoc[key] = value[key];
	//	}
	//}

	//void mergeValue(const JsonValue& value){
	//	auto iter = value.MemberonBegin();
	//	while (iter != value.MemberonEnd())
	//	{
	//		const char* key = iter->name.GetString();
	//		if (hasKey(key))
	//		{
	//			_JsonDoc[key] = value[key];
	//		}
	//		else
	//		{
	//			_JsonDoc.AddMember(key, value[key], _JsonDoc.GetAllocator());
	//		}
	//		++iter;
	//	}
	//}

//// 暂时不做溢出防御
//static int asInt(string key, const JsonValue &v)
//{
//	if (v.IsInt()) { return v.GetInt(); }
//	if (v.IsDouble()) { return (int)v.GetDouble(); }
//	if (v.IsUint()) { return (int)v.GetUint(); }
//	return 0;
//}
//
//// 暂时不做溢出防御
//static long long int asInt64(string key, const JsonValue &v)
//{
//	if (v.IsInt64()) { return v.GetInt64() != 0; }
//	if (v.IsInt()) { return v.GetInt(); }
//	if (v.IsDouble()) { return (int)v.GetDouble(); }
//	if (v.IsUint64()) { return v.GetUint64() != 0; }
//	if (v.IsUint()) { return (int)v.GetUint(); }
//	return 0;
//}
//
//// 暂时不做溢出防御
//static unsigned long long int asUInt64(string key, const JsonValue &v)
//{
//	if (v.IsUint64()) { return v.GetUint64() != 0; }
//	if (v.IsUint()) { return (int)v.GetUint(); }
//	if (v.IsInt64()) { return v.GetInt64() != 0; }
//	if (v.IsInt()) { return v.GetInt(); }
//	if (v.IsDouble()) { return (int)v.GetDouble(); }
//	return 0;
//}
//
//// 暂时不做溢出防御
//static unsigned asUInt(string key, const JsonValue &v)
//{
//	if (v.IsUint()) { return v.GetUint(); }
//	if (v.IsDouble()) { return (unsigned)v.GetDouble(); }
//	if (v.IsInt()) { return (unsigned)v.GetInt(); }
//	return 0;
//}
//
//// 暂时不做溢出防御
//static float asFloat(string key, const JsonValue &v)
//{
//	if (v.IsDouble()) { return (float)v.GetDouble(); }
//	if (v.IsInt()) { return (float)v.GetInt(); }
//	if (v.IsUint()) { return (float)v.GetUint(); }
//	return 0.0f;
//}
//
//// 暂时不做溢出防御
//static bool asBool(string key, const JsonValue &v)
//{
//	if (v.IsBool()) { return v.GetBool(); }
//	if (v.IsDouble()) { return v.GetDouble() != 0.0f; }
//	if (v.IsInt()) { return v.GetInt() != 0; }
//	if (v.IsUint()) { return v.GetUint() != 0; }
//	if (v.IsInt64()) { return v.GetInt64() != 0; }
//	if (v.IsUint64()) { return v.GetUint64() != 0; }
//	return false;
//}
//
//static string asString(string key, const JsonValue &v)
//{
//	if (v.IsString()) { return v.GetString(); }
//	if (v.IsInt()) { return sup::SupString::int2String(v.GetInt()); }
//	if (v.IsUint()) { return sup::SupString::int2String(v.GetUint()); }
//	if (v.IsInt64()) { return sup::SupString::int2String(v.GetInt64()); }
//	if (v.IsUint64()) { return sup::SupString::int2String(v.GetUint64()); }
//	if (v.IsDouble()) { return sup::SupString::double2String(v.GetDouble()); }
//
//	return "";
//}