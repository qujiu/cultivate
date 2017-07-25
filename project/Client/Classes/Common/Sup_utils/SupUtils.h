#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

namespace sup{

	namespace SupUtils{


		Vec2 toPoint(const char* str);
		Vec2 toSize(const char* str);
		Rect toRect(const char* str);

		std::vector<std::string> SplitString(std::string str, std::string pattern = ",");
		std::vector<int> SplitStringToInt(std::string str, std::string pattern = ",");
		std::vector<float> SplitStringToFloat(std::string str, std::string pattern = ",");
		std::vector<int> SplitStringToInt2(std::string str, int iNum, std::string pattern = ",");

		std::vector<std::string> SplitString_Special(std::string str, std::string pattern = "|");
		std::vector<int> SplitStringToInt_Special(std::string str, std::string pattern = "|");
		std::string SplitString_Slots(std::string str,std::string pattern = "0");
		///////////////////时间相关;
		std::string getcurrTime();
		std::string toStringForHourTime(float seconds);
		std::string toStringForMinuteTime(float seconds);
		std::string toStringForSecondTime(float seconds);
	}
}
#endif
