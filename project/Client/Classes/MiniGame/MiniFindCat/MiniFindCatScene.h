#ifndef __MINI__FIND_CAT_SCENE_H__
#define __MINI__FIND_CAT_SCENE_H__


#include "cocos2d.h" 
#include "../MiniGamePublic.h" 
#include "../MiniBaseLayer.h"

enum BOXSTATE {
	BOX_CAT,
	BOX_EMPTY,
};

enum BOX_ANIMATION{
	FINDCAT_ANI_OPENCATBOX =0,
	FINDCAT_ANI_OPENEMPTYBOX,
	FINDCAT_ANI_CATANI,
	FINDCAT_ANI_OPENWRONGBOX,
	FINDCAT_ANI_SHOWCATBOX,
	FINDCAT_ANI_SHOWEMPTYBOX,
	FINDCAT_ANI_SHOWWRONGBOX,
};


class Box : public Armature
{
	CC_SYNTHESIZE(BOXSTATE, _state, State);
	CC_SYNTHESIZE(int, _target, Target);
	CC_SYNTHESIZE(bool, _isSelected, Selected);
public:
	Box();
	~Box();

	static Box *create(const std::string& name, BOXSTATE state);

	void playInitAnimation();
	void playOpenAnimation(float delay = 0);
	void playOpenWrongAnimation(float delay = 0);
	void showFinishOpenAnimation(float delay = 0);
	Rect collisionRect();
};

class MiniFindCatScene : public  MiniBaseLayer
{
public:
	MiniFindCatScene();
	~MiniFindCatScene();

	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniFindCatScene);

	bool onTouchBegan(Touch* touch, Event  *event);

	void createUI();

	void preLoadResource();
	void unloadResource();

	void createBoxWave();
	void refresh();
	void randomSwapeBox();


	void startGame();
	//void showGameOver();
	//void pauseGame(Ref* ref, Widget::TouchEventType type);
	//void resumeGame(Ref* ref, Widget::TouchEventType type);
	//void restartGame(Ref* ref, Widget::TouchEventType type);
	//void quitGame(Ref* ref, Widget::TouchEventType type);
	//void returnGame(Ref* ref, Widget::TouchEventType type);

	void restartGame();
	void pauseMiniGame();
	void resumeMiniGame();


	Box *getBoxByIndex(int index);
private:

	//Widget *_rootWidget;
	//Widget *_pauseBoard;
	//Widget *_gameOverBoard;

	TextAtlas *_labRound;
	TextAtlas *_labCoin;

	int _cutdownCount;
	int _roundCount;
	//int _coins;

	//GAME_STATE _state;

	//__Array *_arrs;

	int  _BOX_MAX;
	float _BOX_SWAP_INTERVAL;
	int _BOX_SWAP_COUNT;

	int _cSwapeCount;

	bool _isFindingCat;
	int _firstBoxIndex;
	Box *_box1;
	Box *_box2;

	LayerColor *_boxLayer;
  
	//bool _isPauseGame;
};


#endif // __FIND_CAT_SCENE_H__