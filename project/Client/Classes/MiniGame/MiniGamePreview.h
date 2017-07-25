#ifndef __MINI_GAME_PREVIEW_H__
#define __MINI_GAME_PREVIEW_H__
 


#include "cocos2d.h" 
#include "MiniGamePublic.h" 


class MiniGamePreview : public Layer
{
	CC_SYNTHESIZE(int,_gameIndex, GameIndex);
public:
	MiniGamePreview();
	~MiniGamePreview();

	static Scene* createScene(int  index);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniGamePreview);


	virtual void onEnter();
	virtual void onExit();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	 
	void createUI();

public:
	void onStartGameClick(Ref *pSender, ui::Widget::TouchEventType type); 

private:
	 
};


#endif // __MINI_GAME_PREVIEW_H__