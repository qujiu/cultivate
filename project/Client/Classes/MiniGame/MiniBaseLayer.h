#ifndef __MINI_BASE_LAYER_H__
#define __MINI_BASE_LAYER_H__


#include "cocos2d.h" 
#include "MiniGamePublic.h"

using namespace cocos2d;

#define HitMouse_Index   0 
#define FindCat_Index    1
#define Fishing_Index    2


class MiniBaseLayer : public Layer
{
public:
	enum VIEW_STATUS
	{
		View_Status_Game,
		View_Status_Pause,
		View_Status_GameOver,
	};

public:
	MiniBaseLayer();
	~MiniBaseLayer();

	virtual void onEnter();
	virtual void onExit();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void showPausePanel();
	virtual void showGameOverPanel();
	virtual void resumeGame();
	virtual void restartGame();
	virtual void quitGame();
	virtual void refresh();

	virtual void pauseMiniGame();
	virtual void resumeMiniGame();

	void delayShowNode(Node *node, float delay, MINI_FORM_SHOW_SPEED speed = MINI_MIDDLE);

	//void showPopAd();

protected:
	float _defaultMusicVolumn;
	float _defaultEffectVolumn;

	int _scores;
	int _viewStatus;
	bool _bIsCompleteTarget;
	bool _bIsPause;
	int _currentGameIndex;

	bool _bIsPauseGame;
	Widget *_rootWidget;
	Widget *_pauseWidget;
	Widget *_gameOverWidget;
	__Array *_arrs;

	Point _pauseButtonPos;

	GAME_STATE _state;

};


#endif // __MINI_BASE_LAYER_H__