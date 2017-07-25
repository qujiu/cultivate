#include "SupLayout.h"

float SUP_DEFAULT_W = 640.0f;
float SUP_DEFAULT_H = 960.f;

float SUP_SCALE_X = 0.0f;
float SUP_SCALE_Y = 0.0f;


void SupLayout::SupLayoutInit()
{
	cocos2d::Size winSize = Director::sharedDirector()->getWinSize();
	if (winSize.width / winSize.height > SUP_DESIGN_W / SUP_DESIGN_H) {
		SUP_DEFAULT_W = winSize.width / winSize.height*SUP_DESIGN_H;
		SUP_DEFAULT_H = SUP_DESIGN_H;

	}
	else
	{
		SUP_DEFAULT_W = SUP_DESIGN_W;
		SUP_DEFAULT_H = winSize.height / winSize.width*SUP_DESIGN_W;
	}

	SUP_SCALE_X = SUP_DEFAULT_W / SUP_DESIGN_W;
	SUP_SCALE_Y = SUP_DEFAULT_H / SUP_DESIGN_H;
}

float SupLayout::SupGetScaleX()
{
	if (SUP_SCALE_X <= 0.01f && SUP_SCALE_X >= -0.01f)
	{
		SupLayoutInit();
	}
	return SUP_SCALE_X;
}

float SupLayout::SupGetScaleY()
{
	if (SUP_SCALE_Y <= 0.01f && SUP_SCALE_Y >= -0.01f)
	{
		SupLayoutInit();
	}
	return SUP_SCALE_Y;
}

float SupLayout::SupGetCenterX()
{
	cocos2d::Size winSize =
		Director::sharedDirector()->getWinSize();
	return winSize.width / 2.0f;
}

float SupLayout::SupGetCenterY()
{
	cocos2d::Size winSize =
		Director::sharedDirector()->getWinSize();
	return winSize.height / 2.0f;
}

cocos2d::Point SupLayout::SupGetCenterXY()
{
	cocos2d::Size winSize =
		Director::sharedDirector()->getWinSize();
	return ccp(winSize.width / 2.0f, winSize.height / 2.0f);
}

cocos2d::Point SupLayout::SupGetScreenPoint(float x, float y, SupAlignment alignment)
{
	cocos2d::Size winSize =
		Director::sharedDirector()->getWinSize();
	//const float scaleX = winSize.width / SUP_DESIGN_W;
	//const float scaleY = winSize.height / SUP_DESIGN_H;

	const float scaleX = SupGetScaleX();
	const float scaleY = SupGetScaleY();

	cocos2d::Point result;

	if (alignment % 3 == 0)
	{
		result.x = x * scaleX;
	}
	else if (alignment % 3 == 2)
	{
		result.x = winSize.width + x * scaleX;
	}
	else
	{
		result.x = winSize.width / 2.0f + x * scaleX;
	}

	if (alignment / 3 == 0)
	{
		result.y = y * scaleY;
	}
	else if (alignment / 3 == 2)
	{
		result.y = winSize.height + y * scaleY;
	}
	else
	{
		result.y = winSize.height / 2.0f + y * scaleY;
	}

	CCLOG("result.x:%f,result.y%f", result.x, result.y);
	return result;
}

cocos2d::Point SupLayout::SupGetScreenPoint(const cocos2d::Point& point, SupAlignment alignment)
{
	return SupGetScreenPoint(point.x, point.y, alignment);
}

void SupLayout::setRelativePos(Node* node, float x, float y, SupAlignment alignment, ESupScale scale){
	node->setPosition(SupGetScreenPoint(x, y, alignment));
	if (E_SUP_SCALE_N == scale)
	{
		return;
	}
	else if (E_SUP_SCALE_X == scale)
	{
		node->setScaleX(SUP_SCALE_X);
	}
	else if (E_SUP_SCALE_Y == scale)
	{
		node->setScaleY(SUP_SCALE_Y);
	}
	else if (E_SUP_SCALE_XY == scale)
	{
		node->setScale(SUP_SCALE_X, SUP_SCALE_Y);
	}

}

void SupLayout::setRelativePos(Node* node, const cocos2d::Point& point, SupAlignment alignment, ESupScale scale){
	node->setPosition(SupGetScreenPoint(point, alignment));

	if (E_SUP_SCALE_N == scale)
	{
		return;
	}
	else if (E_SUP_SCALE_X == scale)
	{
		node->setScaleX(SUP_SCALE_X);
	}
	else if (E_SUP_SCALE_Y == scale)
	{
		node->setScaleY(SUP_SCALE_Y);
	}
	else if (E_SUP_SCALE_XY == scale)
	{
		node->setScale(SUP_SCALE_X, SUP_SCALE_Y);
	}
}

bool SupLayout::isSameDay(time_t t1, time_t t2) {
	if (t1 == 0) {
		return false;
	}

	int before_year, before_yday;
	int next_year, next_yday;

	tm* before = localtime(&t1);

	before_year = before->tm_year;
	before_yday = before->tm_yday;

	tm* next = localtime(&t2);

	next_year = next->tm_year;
	next_yday = next->tm_yday;

	return (before_year == next_year) && (before_yday == next_yday);
}