#ifndef __MINI_LOADING_LAYER_H__
#define __MINI_LOADING_LAYER_H__


#include "cocos2d.h" 
#include "MiniGamePublic.h" 
#include "Miniutils/MiniGTools.h"

class MiniLoadingLayer : public Layer
{
public:

	CC_SYNTHESIZE(int, _gameIndex, GameIndex);

	MiniLoadingLayer();
	~MiniLoadingLayer();

	static Scene* createScene( );

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniLoadingLayer);

	virtual void onEnter();
	virtual void onExit();
	void createUI();
	void tick(float dt);
public:
	void onFinishLoadingCallbakc( );
private: 
	int _count;
	vector<ImageView*>	 _vecDots;
};


#endif // __MINI_LOADING_LAYER_H__