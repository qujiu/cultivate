/*
** implement json reader; 
** author: zhang chao;
** date: 2014.09.29
*/

#include "JsonReader.h"

SINGLETON_DEFINE_INST(JsonReader);


// -----------------------------------------------------------------------
// JsonReader
// -----------------------------------------------------------------------


JsonReader::JsonReader()
{
}

JsonReader::~JsonReader()
{
	purgeAll();
}

rapidjson::Document &JsonReader::open(const string &path)
{
	auto iter = m_cache.find(path);
	if (iter != m_cache.end()) 
	{
		return *iter->second;
	}

	std::string contentStr = FileUtils::getInstance()->getStringFromFile(path);
	rapidjson::Document *pValue = new rapidjson::Document;
	pValue->Parse<kParseDefaultFlags>(contentStr.c_str());

	if (NULL != pValue->GetParseError())
	{
		delete pValue;
	}

	m_cache[path] = pValue;
	return *pValue;
}

bool JsonReader::purge(const string &path)
{
	JsonsIter iter = m_cache.find(path);
	if (iter != m_cache.end())
	{
		delete iter->second;
		m_cache.erase(iter);
		return true;
	}
	return false;
}

void JsonReader::purgeAll()
{
	JsonsIter iter = m_cache.begin();
	while (iter != m_cache.end())
	{
		delete iter->second;
		iter++;
	}
	m_cache.clear();
}
