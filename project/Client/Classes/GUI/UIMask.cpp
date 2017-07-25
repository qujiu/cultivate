//
//  UIMask.cpp
//  game
//
//  Created by QW on 15/12/17.
//
//

#include "UIMask.h"



void UIMask::creatinit(){



	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = CC_CALLBACK_2(UIMask::TouchBegan, this);
	myListener->onTouchMoved = CC_CALLBACK_2(UIMask::TouchMoved, this);
	myListener->onTouchEnded = CC_CALLBACK_2(UIMask::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);

}

void UIMask::creatlist(){


}


void UIMask::creatui(){


}

void UIMask::slideCallbacka(Ref* sender, Control::EventType controlEvent)
{




}




void UIMask::cols(CCNode *obj){
	this->removeFromParentAndCleanup(true);
}



bool UIMask::TouchBegan(Touch* touch, Event* event){
	return true;
}

void  UIMask::TouchMoved(Touch* touch, Event* event){}

void  UIMask::TouchEnded(Touch* touch, Event* event){

}

UIMask* UIMask::create(int _buildid) {
	UIMask *dlg = new UIMask();
	if (dlg && dlg->init(_buildid)) {
		dlg->autorelease();

		return dlg;
	}

	CC_SAFE_DELETE(dlg);
	return NULL;
}

bool UIMask::init(int _buildid) {
	//////////////////////////////
	// 1. super init first

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0))) {

		return false;
	}
	this->buildid = _buildid;
	this->creatinit();
	return true;
}
UIMask::UIMask(void)
{
}


UIMask::~UIMask(void)
{
}