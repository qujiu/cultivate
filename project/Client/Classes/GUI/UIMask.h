//
//  UIMask.h
//  game
//
//  Created by QW on 15/12/17.
//
//

#ifndef UIMask_h
#define UIMask_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace  cocos2d;

using namespace cocos2d::extension;

using namespace std;
class UIMask : public LayerColor
{
public:
	UIMask(void);
	~UIMask(void);
	//UIRecruiting *lary;
	bool   init(int _buildid);
	void creatinit();
	bool close_tf;

	int  buildid;


	static UIMask *create(int _buildid);
	bool TouchBegan(Touch* touch, Event* event);
	void  TouchMoved(Touch* touch, Event* event);
	void  TouchEnded(Touch* touch, Event* event);
	void slideCallbacka(Ref* sender, Control::EventType controlEvent);

	Label *Label_count;
	void cols(CCNode *obj);
	void creatlist();
	void creatui();

	//CREATE_FUNC(UIAdventure);
};
#endif /* UIMask_h */
