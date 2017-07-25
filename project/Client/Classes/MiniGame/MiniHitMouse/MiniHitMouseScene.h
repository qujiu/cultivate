#ifndef __HIT_MOUSE_SCENE_H__
#define __HIT_MOUSE_SCENE_H__


#include "cocos2d.h" 
#include "../MiniGamePublic.h" 
#include "../MiniBaseLayer.h"


enum MOUSE {
	MOUSE_1,
	MOUSE_2,
	MOUSE_3,
};

enum MOUSESTATE {
	MOUSE_RUN,
	MOUSE_DIE,
};

class Mouse : public Armature
{
	CC_SYNTHESIZE(MOUSE, _mouseType, Mouse);
	CC_SYNTHESIZE(MOUSESTATE, _state, State);
public:
	Mouse();
	~Mouse();

	static Mouse *create(const std::string& name, MOUSE _mouse);

	void playRunAnimation();
	void playDieAnimation();

	Rect collisionRect();
};

enum MOUSE_ANIMATION{
	HitMouse_ANI_CAT_HIT,
	HitMouse_ANI_CAT_WAIT,
	HitMouse_ANI_MouseBlue_Run,
	HitMouse_ANI_MouseBlue_DIE,
	HitMouse_ANI_MouseRed_Run,
	HitMouse_ANI_MouseRed_DIE,
	HitMouse_ANI_MouseYellow_Run,
	HitMouse_ANI_MouseYellow_DIE,
};

class MiniHitMouseScene : public MiniBaseLayer
{
public:
	MiniHitMouseScene();
	~MiniHitMouseScene();

	static Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(MiniHitMouseScene);

	bool onTouchBegan(Touch* touch, Event  *event);

	void createUI();

	void preLoadResource();
	void unloadResource();


	void tick(float dt);
	void createMouseWave(float dt);
	void removeMouse(Ref *pSender);
	void onMouseFinishAction(Ref *pSender);

	void hitCheck();

	void refresh();
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
	 
	void movementCallback(Armature * armature, MovementEventType type, const char * name);
private:

	/*Widget *_rootWidget;
	Widget *_pauseBoard;
	Widget *_gameOverBoard;*/

	TextAtlas *_labTime;
	TextAtlas *_labCoin;

	float LINE_HEIGHT;
	float LINE_WIDTH;


	float _point1;
	float _point2;
	float _point3;
	float _point4;
	float _point5;

	float _middle1;
	float _middle2;
	float _middle3;
	float _middle4;

	Rect _collision1;
	Rect _collision2;
	Rect _collision3;
	Rect _collision4;

	int _waveCount;
	int _cutdownCount;
	int _currentRoad;

	int _timeCount;
	//int _coins;

	//__Array *_arrs;
	__Array *_arrPoints;

	Armature *_cat;

	ParticleBatchNode *_particleBatch1;
	ParticleBatchNode *_particleBatch2;

	GAME_STATE _state;

	bool _isPauseGame;
};



#endif // __HIT_MOUSE_SCENE_H__