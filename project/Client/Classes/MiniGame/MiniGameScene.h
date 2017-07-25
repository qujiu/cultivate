#ifndef __MINIGAME_SCENE_H__
#define __MINIGAME_SCENE_H__


#include "cocos2d.h"
#include "MiniGamePublic.h"
 
 

//class HelloWorld : public cocos2d::Layer
//{
//public:
//

class MiniGameScene : public Layer
{
public:
	MiniGameScene();
	~MiniGameScene();

	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniGameScene);

private:



};


#endif // __MINIGAME_SCENE_H__