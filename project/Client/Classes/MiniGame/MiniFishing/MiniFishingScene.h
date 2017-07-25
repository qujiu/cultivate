#ifndef __MINI__FISHING_SCENE_H__
#define __MINI__FISHING_SCENE_H__


#include "cocos2d.h" 
#include "../MiniGamePublic.h" 
#include "../MiniBaseLayer.h"


enum FISH_ID {
	FISH1,
	FISH2,
	FISH3,
	FISH4,
	FISH5,
	FISH6,
	FISH7,
	FISH8,
	FISH9,
};

enum FISH_BONUS_TYPE {
	FISH_COIN,
	FISH_ATTACK,
	FISH_SUPPLY,
};

enum FISH_DIRECTION
{
	FISH_LEFT,
	FISH_RIGHT,
};

class Fish :public Sprite
{
	CC_SYNTHESIZE(FISH_ID, _fishID, FishID);
	CC_SYNTHESIZE(FISH_DIRECTION, _fishDir, Direction);
	CC_SYNTHESIZE(bool, _isFinishMove, IsFinishMove);
public:

	Fish();
	~Fish();

	static Fish *create(const std::string& name, FISH_ID id);
	CREATE_FUNC(Fish);

};

class MiniFishingScene : public MiniBaseLayer
{
public:
	MiniFishingScene();
	~MiniFishingScene();

	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniFishingScene);

	bool onTouchBegan(Touch* touch, Event  *event);

	void createUI();

	void preLoadResource();
	void unloadResource();


	void startGame();
	void refresh();
	//void showGameOver();
	//void pauseGame(Ref* ref, Widget::TouchEventType type);
	//void resumeGame(Ref* ref, Widget::TouchEventType type);
	//void restartGame(Ref* ref, Widget::TouchEventType type);
	//void quitGame(Ref* ref, Widget::TouchEventType type);
	//void returnGame(Ref* ref, Widget::TouchEventType type);

	void cunDownTick(float dt);
	void tick(float dt);
	void createWaveFish(float dt);
	void removePoolFish(Ref *pSender);
	void removeFish(Ref *pSender);
	void onFishFinishAction(Ref *pSender);

	void onAddCoinCallback(Ref *pSender);
	void onAddTimeCallback(Ref *pSender, void*   data);
	void onSubTimeCallback(Ref *pSender, void*   data);

	void restartGame();
	void pauseMiniGame();
	void resumeMiniGame();

private:

	/*Widget *_rootWidget;
	Widget *_pauseBoard;
	Widget *_gameOverBoard;
*/
	TextAtlas *_labTime;
	TextAtlas *_labCoin;

	int _timeCount; 
	int _cutdownCount;

	//GAME_STATE _state;
	 
	Sprite *_boad;
	ui::Scale9Sprite *_rope;
	Sprite *_hook;

	Point _ropePoint1;
	Point _ropePoint2;
	float _ropeLenght;

	int _waveCount;
 

	int _soundID;

	float _lastFishY;
	float _lastFishHeight;
	bool _bIsGameOver;

	//bool _isPauseGame;
};


#endif // __MINI__FISHING_SCENE_H__
