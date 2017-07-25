

#include "SupUtils.h"
#include "../Common.h"

namespace sup{


	Vec2 SupUtils::toPoint(const char* str)
	{
		if (!str) return Vec2::ZERO;
		CCPoint p;
		sscanf(str, "{%g,%g}", &p.x, &p.y);
		return p;
	}

	Vec2 SupUtils::toSize(const char* str)
	{
		if (!str) return Vec2::ZERO;
		Size s;
		sscanf(str, "{%g,%g}", &s.width, &s.height);
		return s;
	}

	Rect SupUtils::toRect(const char* str)
	{
		Rect rect;
		sscanf(str, "{%g,%g,%g,%g}", &rect.origin.x, &rect.origin.y, &rect.size.width, &rect.size.height);
		return rect;
	}

	std::vector<std::string> SupUtils::SplitString(std::string str, std::string pattern)
	{
		char temp[1024];
		sscanf(str.c_str(), "{%[^}]", temp);
		std::string str_des(temp);
		std::string::size_type pos;
		std::vector<std::string> result;
		if (str_des == "") return result;
		str_des += pattern;
		for (int i = 0, cnt = str_des.size(); i < cnt; ++i)
		{
			pos = str_des.find(pattern, i);
			if ((int)pos < cnt)
			{
				std::string s = str_des.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	std::vector<std::string> SupUtils::SplitString_Special(std::string str, std::string pattern)
	{
		//char temp[1024];
		//sscanf(str.c_str(), temp);
		std::string str_des = str;
		std::string::size_type pos;
		std::vector<std::string> result;
		if (str_des == "") return result;
		str_des += pattern;
		for (int i = 0, cnt = str_des.size(); i < cnt; ++i)
		{
			pos = str_des.find(pattern, i);
			if ((int)pos < cnt)
			{
				std::string s = str_des.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	std::string SupUtils::SplitString_Slots(std::string str, std::string pattern)
	{
		std::string str_des = str;
		std::string::size_type pos;
		std::string result;
		if (str_des == "") return result;
		pos = str_des.find(pattern, 1);
		if (pos != -1)
		{
			result = str_des.substr(pos + 1, str_des.size() - 1);
			return result;
		}
		return str_des;
	}

	std::vector<int> SupUtils::SplitStringToInt_Special(std::string str, std::string pattern)
	{
		std::vector<int> result;
		std::vector<std::string> result_str = SplitString_Special(str, pattern);
		for (int i = 0, cnt = result_str.size(); i < cnt; ++i)
		{
			result.push_back(sup::SupString::string2Int(result_str[i].c_str()));
		}
		return result;
	}

	std::vector<int> SupUtils::SplitStringToInt(std::string str, std::string pattern)
	{
		std::vector<int> result;
		std::vector<std::string> result_str = SplitString(str, pattern);
		for (int i = 0, cnt = result_str.size(); i < cnt; ++i)
		{
			result.push_back(sup::SupString::string2Int(result_str[i].c_str()));
		}
		return result;
	}

	std::vector<int> SupUtils::SplitStringToInt2(std::string str, int iNum, std::string pattern)
	{
		std::vector<int> result;
		std::vector<std::string> result_str = SplitString(str, pattern);
		for (int i = 0, cnt = result_str.size(); i < cnt; ++i)
		{
			std::vector<int> result1;
			result1 = SplitStringToInt_Special(result_str[i], "|");
			result.push_back(result1[iNum]);
		}
		return result;
	}

	std::vector<float> SupUtils::SplitStringToFloat(std::string str, std::string pattern)
	{
		std::vector<float> result;
		std::vector<std::string> result_str = SplitString(str, pattern);
		for (int i = 0, cnt = result_str.size(); i < cnt; ++i)
		{
			result.push_back(sup::SupString::string2Float(result_str[i].c_str()));
		}
		return result;
	}


	///////////////////时间相关;////////////////////
	std::string SupUtils::getcurrTime()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		struct timeval now;
		struct tm* time;
		gettimeofday(&now, NULL);
		time = localtime(&now.tv_sec);
		int year = time->tm_year + 1900;
		char date[32] = { 0 };
		sprintf(date, "%d%02d%02d%02d%02d%02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday, (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);

		return StringUtils::format("%s", date);
#endif
		return "";
	}

	std::string SupUtils::toStringForHourTime(float seconds)
	{
		int count = (int)seconds / 3600;
		std::string str;
		if (count < 0)
		{
			return "00";
		}
		else if (count < 10)
		{
			str = "0";
			str += sup::SupString::int2String(count);
		}
		else
		{
			str = sup::SupString::int2String(count);
		}
		return str;
	}


	std::string SupUtils::toStringForMinuteTime(float seconds)
	{
		int count = (int)seconds % 3600 / 60;
		std::string str;
		if (count < 0)
		{
			return "00";
		}
		else if (count < 10)
		{
			str = "0";
			str += sup::SupString::int2String(count);
		}
		else
		{
			str = sup::SupString::int2String(count);
		}
		return str;
	}

	std::string SupUtils::toStringForSecondTime(float seconds)
	{
		int count = (int)seconds % 3600 % 60;
		std::string str;
		if (count < 0)
		{
			return "00";
		}
		else if (count < 10)
		{
			str = "0";
			str += sup::SupString::int2String(count);
		}
		else
		{
			str = sup::SupString::int2String(count);
		}
		return str;
	}

}