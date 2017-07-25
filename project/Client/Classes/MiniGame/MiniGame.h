#ifndef __MINI_GAME_H__
#define __MINI_GAME_H__


#include "cocos2d.h" 
#include "MiniGamePublic.h" 
#include "Miniutils/MiniGTools.h"

class MiniGame : public Layer
{

public: 
	enum MiniGameState {
		MiniGame_State_Fail,
		MiniGame_State_Success,
		MiniGame_State_NotPlay,
	};

public:
	MiniGame();
	~MiniGame();

	static Scene* loadMiniGame(bool isInit = false);
	static Scene* createScene(); 

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init( );

	CREATE_FUNC(MiniGame);

	virtual void onEnter();
	virtual void onExit();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void createUI();

public:
	void onListItemClick(Ref *pSender, ui::Widget::TouchEventType type);
	void onQuitMiniGameClick(Ref *pSender, ui::Widget::TouchEventType type);

private:   
	TextAtlas *_labelCoin; 
};


#endif // __MINI_GAME_H__