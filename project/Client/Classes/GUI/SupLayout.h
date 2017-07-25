
#ifndef __Sup_Layout_h__
#define __Sup_Layout_h__

#include "cocos2d.h"
USING_NS_CC;

#define SUP_DESIGN_W (640.0f)
#define SUP_DESIGN_H (960.0f)

//game size
extern float SUP_DEFAULT_W;
extern float SUP_DEFAULT_H;

//game scale
extern float SUP_SCALE_X;
extern float SUP_SCALE_Y;


enum SupAlignment
{
	SUP_ALIGNMENT_LB = 0,  // left bottom
	SUP_ALIGNMENT_CB = 1,  // center bottom
	SUP_ALIGNMENT_RB = 2,  // right bottom
	SUP_ALIGNMENT_LC = 3,  // left center
	SUP_ALIGNMENT_CC = 4,  // center center
	SUP_ALIGNMENT_RC = 5,  // right center
	SUP_ALIGNMENT_LT = 6,  // left top
	SUP_ALIGNMENT_CT = 7,  // center top
	SUP_ALIGNMENT_RT = 8,  // right top
};

enum ESupScale
{
	E_SUP_SCALE_N = 0,  //no scale
	E_SUP_SCALE_X = 1,  //scale x
	E_SUP_SCALE_Y = 2,  //scale y
	E_SUP_SCALE_XY = 3, //scale xy;
};

namespace SupLayout{

	void SupLayoutInit();

	float SupGetScaleX();
	float SupGetScaleY();
	float SupGetCenterX();
	float SupGetCenterY();
	cocos2d::Point SupGetCenterXY();

	cocos2d::Point SupGetScreenPoint(float x, float y, SupAlignment alignment);
	cocos2d::Point SupGetScreenPoint(const cocos2d::Point& point, SupAlignment alignment);

	//void SupSetScale(Node* node, ESupScale scale = E_SUP_SCALE_N);

	bool isSameDay(time_t t1, time_t t2);
	void setRelativePos(Node* node, float x, float y, SupAlignment alignment, ESupScale scale = E_SUP_SCALE_N);
	void setRelativePos(Node* node, const cocos2d::Point& point, SupAlignment alignment, ESupScale scale = E_SUP_SCALE_N);
}



#endif // __Sup_Layout_h__