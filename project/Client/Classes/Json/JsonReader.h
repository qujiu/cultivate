/*
** implement json reader;
** author: zhang chao;
** date: 2014.09.29
*/

#ifndef __JSON_READER_H__
#define __JSON_READER_H__

#include "../define.h"
#include <cassert>
#include <string>
#include <map>
#include "json/document.h"

using namespace sup;
using namespace rapidjson;

// -----------------------------------------------------------------------
// implement JsonValueEx
// -----------------------------------------------------------------------
typedef rapidjson::Value JsonValue;

// -----------------------------------------------------------------------
// implement JsonReader
// -----------------------------------------------------------------------
class JsonReader: public sup::Singleton<JsonReader>
{
private:
	typedef map<string, rapidjson::Document*> Jsons;
	typedef Jsons::iterator JsonsIter;

private:
	SINGLETON_FRIEND_SUB(JsonReader);
	JsonReader();
	virtual ~JsonReader();
	JsonReader(const JsonReader&);
	JsonReader &operator=(const JsonReader&);

public:
	rapidjson::Document &open(const string &path);
	bool purge(const string &path);
	void purgeAll();

private:
	Jsons m_cache;
};


#endif
