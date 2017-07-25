#include "MiniHitMouseScene.h" 
#include "../MiniGamePublic.h"
#include "../Miniutils/MiniGTools.h"
#include "../MiniGame.h"


#define LEVELTIME  60*2 
#define MOVETIME   6.0f
#define MOVETIME1  MOVETIME/2
#define MOVETIME2  MOVETIME/4
#define WAVEINTERVAL 4
#pragma mark MouseData

Mouse::Mouse()
{
	_mouseType = MOUSE::MOUSE_1;
	_state = MOUSESTATE::MOUSE_RUN;
}

Mouse::~Mouse()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

Mouse *Mouse::create(const std::string& name, MOUSE _mouse)
{
	Mouse *armature = new (std::nothrow) Mouse();
	if (armature && armature->init(name))
	{
		armature->setMouse(_mouse);
		armature->autorelease();
		return armature;
	}
	CC_SAFE_DELETE(armature);
	return nullptr;
}

void Mouse::playRunAnimation()
{
	getAnimation()->stop();


	if (_mouseType == MOUSE::MOUSE_1)
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseYellow_Run);
	}
	else if (_mouseType == MOUSE::MOUSE_2)
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseBlue_Run);
	}
	else
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseRed_Run);
	}

	getAnimation()->setMovementEventCallFunc(nullptr);
}

void Mouse::playDieAnimation()
{
	getAnimation()->stop();

	if (_mouseType == MOUSE::MOUSE_1)
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseYellow_DIE);
	}
	else if (_mouseType == MOUSE::MOUSE_2)
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseBlue_DIE);
	}
	else
	{
		getAnimation()->playWithIndex(HitMouse_ANI_MouseRed_DIE);
	}

	getAnimation()->setMovementEventCallFunc(nullptr);

}


Rect Mouse::collisionRect()
{
	Point origin = getPosition();// this->getParent()->convertToWorldSpace(getPosition());
	return  Rect(origin.x - getContentSize().width / 4, origin.y - getContentSize().height*0.3, getContentSize().width / 2, getContentSize().height*0.5);
}

#pragma mark GameScene

MiniHitMouseScene::MiniHitMouseScene()
{
	preLoadResource();

	_currentGameIndex = MINI_GAME_HITMOUSE;

	LINE_HEIGHT = 0;
	_waveCount = 0;

	_point1 = 0;
	_point2 = 0;
	_point3 = 0;
	_point4 = 0;

	_collision1 = Rect(0, 0, 0, 0);
	_collision2 = Rect(0, 0, 0, 0);
	_collision3 = Rect(0, 0, 0, 0);
	_collision4 = Rect(0, 0, 0, 0);

	_timeCount = 0; 
	_cutdownCount = 0;
	_currentRoad = -1;
	_state = GAME_INIT;

	//_pauseBoard = NULL;
	//_gameOverBoard = NULL;

	//_arrs = __Array::create();
	//_arrs->retain();

	_arrPoints = __Array::create();
	_arrPoints->retain();

	_particleBatch1 = NULL;
	_particleBatch2 = NULL;

	_isPauseGame = false;
}


MiniHitMouseScene::~MiniHitMouseScene()
{
	//if (_pauseBoard)
	//{
	//	_pauseBoard->removeFromParentAndCleanup(true);
	//	_pauseBoard->release();
	//}
	//if (_gameOverBoard)
	//{
	//	_gameOverBoard->removeFromParentAndCleanup(true);
	//	_gameOverBoard->release();
	//}

	//_arrs->removeAllObjects();
	//_arrs->release();
	_arrPoints->removeAllObjects();
	_arrPoints->release();

	unloadResource();
	MiniGTools::stopAllSound(); 
}



Scene* MiniHitMouseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniHitMouseScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MiniHitMouseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	createUI();

	return true;
}

void MiniHitMouseScene::preLoadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minigames/HitMouse/hitmouse.plist"); 
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Minigames/HitMouse/HitMouseAni.json");
}

void MiniHitMouseScene::unloadResource()
{
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/HitMouse/hitmouse.plist");
	//ArmatureDataManager::getInstance()->removeArmatureFileInfo("Minigames/HitMouse/HitMouseAni.json");

	//Director::getInstance()->getScheduler()->schedule([&](float dt){
	//	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	//}, this, 0.02f, 0, 0, false, "SCHEDULE_CLEAR");
}

void MiniHitMouseScene::createUI()
{
	//载入GUI
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_HitMouse.json");
	addChild(bg, 0);

	_rootWidget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Game");

	//根据屏幕重新定位控件

	//顶部控件

	Widget * _widget = NULL;

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Top");
	_widget->setPositionY(SCREEN_HEIGHT - _widget->getContentSize().height);

	_widget = (Widget*)Helper::seekWidgetByName(_rootWidget, "Img_Bar_Bg");
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Button_Pause");
	_widget->setPositionX(SCREEN_WIDTH - _widget->getContentSize().width / 2 );
	_widget->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			showPausePanel();
		}
	});
	_pauseButtonPos = MiniGTools::getInstance()->toWorldPoint(_widget);



	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_House");
	_widget->setPositionX(SCREEN_WIDTH / 2);
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bg");
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);

	LINE_HEIGHT = _widget->getContentSize().height;


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_House");
	_widget->setPositionY(SCREEN_HEIGHT);
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);
	_widget->setScaleY((SCREEN_HEIGHT - LINE_HEIGHT) / _widget->getContentSize().height);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Line");
	_widget->setPositionX(SCREEN_WIDTH / 2);
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Board");
	_widget->setPositionX(SCREEN_WIDTH / 2);

	//创建主角
	_cat = Armature::create("HitMouseAni");
	_cat->setPosition(SCREEN_WIDTH / 2, LINE_HEIGHT + 10);
	addChild(_cat, 8);
	_cat->getAnimation()->playWithIndex(MOUSE_ANIMATION::HitMouse_ANI_CAT_WAIT);


	//计算控制点和控制区域 
	LINE_WIDTH = _widget->getContentSize().width / 4;
	_point1 = _widget->getPositionX() - LINE_WIDTH * 2;
	_point2 = _point1 + LINE_WIDTH;
	_point3 = _point2 + LINE_WIDTH;
	_point4 = _point3 + LINE_WIDTH;
	_point5 = _point4 + LINE_WIDTH;

	_middle1 = _point1 + LINE_WIDTH / 2;
	_middle2 = _point2 + LINE_WIDTH / 2;
	_middle3 = _point3 + LINE_WIDTH / 2;
	_middle4 = _point4 + LINE_WIDTH / 2;

	_collision1 = Rect(_point1, 540, LINE_WIDTH, 100);
	_collision2 = Rect(_point2, 540, LINE_WIDTH, 100);
	_collision3 = Rect(_point3, 540, LINE_WIDTH, 100);
	_collision4 = Rect(_point4, 540, LINE_WIDTH, 100);


	//获取控制对象
	_labTime = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Time");
	_labCoin = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Coin");

	TextAtlas *_labTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Target");
	_labTarget->setString(__String::createWithFormat("%d", miniGameNames[HitMouse_Index].game_target_score)->getCString());

	//创建暂停和结算
	/*{
		_pauseBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
		_pauseBoard->retain();


		Widget *_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Restart");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::restartGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Quit");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::quitGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Close");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::resumeGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
		_widget->setPositionX(SCREEN_WIDTH / 2);
	}

	{
		_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
		_gameOverBoard->retain();

		Widget *_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::returnGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::restartGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
		_widget->setPositionX(SCREEN_WIDTH / 2);


		TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
		_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[HitMouse_Index].game_target_score)->getCString());
	}*/

	//创建粒子batchnode

	ParticleSystem* m_emitter = ParticleSystemQuad::create("Minigames/HitMouse/effect_dalaoshu_bao_add.plist");
	_particleBatch1 = ParticleBatchNode::createWithTexture(m_emitter->getTexture());
	addChild(_particleBatch1, 9);

	m_emitter = ParticleSystemQuad::create("Minigames/HitMouse/effect_dalaoshu_star.plist");
	_particleBatch2 = ParticleBatchNode::createWithTexture(m_emitter->getTexture());
	addChild(_particleBatch2, 9);


	//注册全局touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniHitMouseScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	startGame();
}


//倒计时
void MiniHitMouseScene::tick(float dt)
{
	_timeCount = MAX(_timeCount--, 0);
	refresh();
	if (_timeCount == 0) {
		unschedule(schedule_selector(MiniHitMouseScene::tick));
		unschedule(schedule_selector(MiniHitMouseScene::createMouseWave));
		//showGameOver();
		showGameOverPanel(); 
	}
}

//创建怪物
void MiniHitMouseScene::createMouseWave(float dt)
{
	int _mouseCount = 1;
	//老鼠大波来的数目减少为2~3个；每隔6秒小爆发一下 
	if (_waveCount>0 && _waveCount % 4 == 0) {
		_mouseCount = rand() % 2 == 0 ? 1 : 2;
	}

	_arrPoints->removeAllObjects();

	for (int i = 0; i < _mouseCount; i++)
	{
		//老鼠1  60%， 老鼠2  30%， 老鼠3 10%
		int randMouse = rand() % 100;
		MOUSE mouseType = MOUSE::MOUSE_1;

		//	前3回合只出现小地鼠，其余回合按照每只地鼠的出现几率随机出现。
		if (_waveCount>3){
			if (randMouse < 50){
				mouseType = MOUSE::MOUSE_1;
			}
			else if (randMouse < 80){
				mouseType = MOUSE::MOUSE_2;
			}
			else {
				mouseType = MOUSE::MOUSE_3;
			}
		}

		int randmoMouse = rand() % 3;

		Mouse *mouse = Mouse::create("HitMouseAni", (MOUSE)mouseType);
		mouse->playRunAnimation();
		int r = rand_0_1() * 100;

		bool isOk = false;
		int randmoRoad = 0;

		while (!isOk){
			randmoRoad = rand() % 4;
			bool isFindSame = false;
			for (int i = 0; i < _arrPoints->count(); i++)
			{
				__Integer *pos = (__Integer*)_arrPoints->getObjectAtIndex(i);
				if (pos->getValue() == randmoRoad)
				{
					isFindSame = true;
					break;
				}
			}
			if (!isFindSame)
			{
				_arrPoints->addObject(Integer::create(randmoRoad));
				isOk = true;
			}
		}
		switch (randmoRoad)
		{
		case 0: {
					mouse->setPosition(Point(_middle1, -100));
		}
			break;
		case 1: {
					mouse->setPosition(Point(_middle2, -100));
		}
			break;
		case 2: {
					mouse->setPosition(Point(_middle3, -100));
		}
			break;
		case 3: {
					mouse->setPosition(Point(_middle4, -100));
		}
			break;
		}

		//出发增加一个延时时间，当一次出现3个老鼠的时候，让老鼠出现的时间有差别
		float _delayTime = 0;
		if (i>0){
			_delayTime = ((rand() % 100) / 100.0f) + 0.2;
		}
		_rootWidget->addChild(mouse, 3);


		//根据老鼠类型产生不同的动作
		auto delaytime = DelayTime::create(_delayTime);
		if (mouseType == MOUSE::MOUSE_1)
		{
			//正常速度,直行

			auto move = MoveBy::create(MOVETIME, Vec2(0, LINE_HEIGHT + 150));
			auto callback = CallFuncN::create(CC_CALLBACK_1(MiniHitMouseScene::onMouseFinishAction, this));
			auto seq = Sequence::create(delaytime, move, callback, NULL);
			mouse->runAction(seq);
		}
		else if (mouseType == MOUSE::MOUSE_2)
		{
			//1.5倍速度，高度超过1半，随机换行

			float randomHeight1 = LINE_HEIGHT / 2 + rand() % (int)(LINE_HEIGHT / 4);
			float randomHeight2 = LINE_HEIGHT + 150 - randomHeight1;

			int randChangeRoad = (rand() % 2) == 0 ? -1 : 1;

			if (randmoRoad == 0){
				randChangeRoad = 1;
			}
			else if (randmoRoad == 3){
				randChangeRoad = -1;
			}

			int nextRoad = randmoRoad + randChangeRoad;

			auto move1 = MoveBy::create(MOVETIME1 * (randomHeight1 / (LINE_HEIGHT + 150)), Vec2(0, randomHeight1));
			auto move2 = MoveBy::create(MOVETIME1 * (LINE_WIDTH / (LINE_HEIGHT + 150)), Vec2(LINE_WIDTH * randChangeRoad, 0));
			auto move3 = MoveBy::create(MOVETIME1 * (randomHeight2 / (LINE_HEIGHT + 150)), Vec2(0, randomHeight2));
			auto callback = CallFuncN::create(CC_CALLBACK_1(MiniHitMouseScene::onMouseFinishAction, this));
			auto seq = Sequence::create(delaytime, move1, move2, move3, callback, NULL);

			mouse->runAction(seq);
		}
		else {
			//速度2.5倍 ，直行
			auto move = MoveBy::create(MOVETIME2, Vec2(0, LINE_HEIGHT + 150));
			auto callback = CallFuncN::create(CC_CALLBACK_1(MiniHitMouseScene::onMouseFinishAction, this));
			auto seq = Sequence::create(delaytime, move, callback, NULL);
			mouse->runAction(seq);
		}


		//添加到数组
		_arrs->addObject(mouse);
	}

	_waveCount++;
}

void MiniHitMouseScene::onMouseFinishAction(Ref *pSender)
{
	//没有打到的老鼠，黄色老鼠减少时间为2秒、蓝色老鼠为5秒、红色老鼠为10秒
	Mouse *mouse = (Mouse*)pSender;

	MiniGTools::playEffect(EFFECT_ESCAPE);

	Sprite *coin = Sprite::create("Minigames/Common/mini_ui_info_time.png");
	coin->setAnchorPoint(Point(1, 0.5));
	coin->setPosition(mouse->getPosition());
	this->addChild(coin, 10);


	Sprite *time = NULL;
	if (mouse->getMouse() == MOUSE::MOUSE_1) {
		time = Sprite::createWithSpriteFrameName("ani_suzi_2s.png");
	}
	else if (mouse->getMouse() == MOUSE::MOUSE_2) {
		time = Sprite::createWithSpriteFrameName("ani_suzi_5s.png");
	}
	else if (mouse->getMouse() == MOUSE::MOUSE_3) {
		time = Sprite::createWithSpriteFrameName("ani_suzi_10s.png");
	}
	time->setAnchorPoint(Point(0, 0.5));
	time->setPosition(CCP_SPRITE(1.1, 0.5, coin));
	time->setScale(0.6f);
	coin->addChild(time);


	float randomY = rand() % 60 - 30;
	float randomHeight = rand() % 60 - 30;
	auto jump = JumpBy::create(0.3f, Vec2(0, -100 + randomY), 100 + randomHeight, 1);
	auto delay = DelayTime::create(0.3f);

	Point targetPos = _labTime->getParent()->convertToWorldSpace(_labTime->getPosition());

	auto move = MoveTo::create(0.5f, targetPos);
	auto scale = ScaleTo::create(0.5f, 0.2f);
	auto spawn = Spawn::createWithTwoActions(move, scale);

	CallFunc * call = NULL;

	if (mouse->getMouse() == MOUSE::MOUSE_1) {
		call = CallFunc::create(
			[&](){
			_timeCount = MAX(_timeCount - 2, 0);
			refresh();

			MiniGTools::playEffect(EFFECT_DECREASETIME);
		});
	}
	else if (mouse->getMouse() == MOUSE::MOUSE_2) {
		call = CallFunc::create(
			[&](){
			_timeCount = MAX(_timeCount - 5, 0);
			refresh();
			MiniGTools::playEffect(EFFECT_DECREASETIME);
		});
	}
	else if (mouse->getMouse() == MOUSE::MOUSE_3) {
		call = CallFunc::create(
			[&](){
			_timeCount = MAX(_timeCount - 10, 0);
			refresh();
			MiniGTools::playEffect(EFFECT_DECREASETIME);
		});
	}

	auto remove = RemoveSelf::create();
	auto seq = Sequence::create(jump, delay, spawn, call, remove, NULL);

	coin->runAction(seq);

	//删除对象
	removeMouse(pSender);
}

void MiniHitMouseScene::removeMouse(Ref *pSender)
{

	Mouse *mouse = (Mouse*)pSender;
	mouse->removeFromParentAndCleanup(true);

	_arrs->removeObject(mouse);
}


//点击屏幕事件
bool MiniHitMouseScene::onTouchBegan(Touch* touch, Event  *event)
{
	auto location = touch->getLocation();

	if (location.x >= _point1 && location.x <= _point5){

		if (location.x >= _point1 && location.x < _point2){
			_currentRoad = 0;
			_cat->setPositionX(_middle1);
		}
		else if (location.x >= _point2 && location.x < _point3){
			_currentRoad = 1;
			_cat->setPositionX(_middle2);
		}
		else if (location.x >= _point3 && location.x < _point4){
			_currentRoad = 2;
			_cat->setPositionX(_middle3);
		}
		else if (location.x >= _point4 && location.x <= _point5){
			_currentRoad = 3;
			_cat->setPositionX(_middle4);
		}

		hitCheck();

	}
	return true;
}

void MiniHitMouseScene::hitCheck()
{
	//播放动画
	_cat->getAnimation()->playWithIndex(HitMouse_ANI_CAT_HIT);

	if (_currentRoad <0)
	{
		return;
	}

	//检测碰撞
	if (_arrs->count() > 0){
		for (int i = _arrs->count() - 1; i >= 0; i--)
		{
			Mouse* mouse = (Mouse*)_arrs->getObjectAtIndex(i);

			if (mouse->getState() == MOUSESTATE::MOUSE_RUN){
				Rect rect1, rect2;

				switch (_currentRoad)
				{
				case 0:
					rect1 = _collision1;
					break;
				case 1:
					rect1 = _collision2;
					break;
				case 2:
					rect1 = _collision3;
					break;
				case 3:
					rect1 = _collision4;
					break;

				}

				rect2 = mouse->collisionRect();
				if (rect1.intersectsRect(rect2)){
					//老鼠碰撞，播放特效与声音
					mouse->stopAllActions();
					mouse->setState(MOUSESTATE::MOUSE_DIE);
					mouse->playDieAnimation();
					mouse->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(MiniHitMouseScene::movementCallback));

					MiniGTools::playEffect(EFFECT_HITMOUSE);

					//读取粒子效果
					{
						ParticleSystem* m_emitter1 = ParticleSystemQuad::create("Minigames/HitMouse/effect_dalaoshu_bao_add.plist");
						_particleBatch1->addChild(m_emitter1);
						m_emitter1->setAutoRemoveOnFinish(true);
						m_emitter1->setPosition(mouse->getPosition());

						ParticleSystem* m_emitter2 = ParticleSystemQuad::create("Minigames/HitMouse/effect_dalaoshu_star.plist");
						_particleBatch2->addChild(m_emitter2); //_particleBatch2
						m_emitter2->setAutoRemoveOnFinish(true);
						m_emitter2->setPosition(mouse->getPosition());
					}

					//产生金币

					int _coinsCount = 1;
					if (mouse->getMouse() == MOUSE::MOUSE_2)
					{
						_coinsCount = 2;
					}
					else  if (mouse->getMouse() == MOUSE::MOUSE_3)
					{
						_coinsCount = 3;
					}

					MiniGTools::playEffect(EFFECT_COIN2);


					for (int i = 0; i < _coinsCount; i++){

						Sprite *coin = Sprite::create("Minigames/Common/ui_minigame_floor_stars.png"); 
						//Sprite::createWithSpriteFrameName("cat_coin.png");
						coin->setPosition(mouse->getPosition());
						this->addChild(coin, 10);


						float randomX = rand() % 100 - 50;
						float randomY = rand() % 60 - 30;
						float randomHeight = rand() % 60 - 30;
						auto jump = JumpBy::create(0.3f, Vec2(randomX, -100 + randomY), 100 + randomHeight, 1);
						auto delay = DelayTime::create(0.3f);

						Point targetPos = _labCoin->getParent()->convertToWorldSpace(_labCoin->getPosition());

						auto move = MoveTo::create(0.5f, targetPos);
						auto scale = ScaleTo::create(0.5f, 0.2f);
						auto spawn = Spawn::createWithTwoActions(move, scale);

						auto call = CallFunc::create(
							[&](){
							if (_state != GAME_OVER){
								_scores++;
								refresh();
								MiniGTools::playEffect(EFFECT_COIN1);
							}
						});

						auto remove = RemoveSelf::create();
						auto seq = Sequence::create(jump, delay, spawn, call, remove, NULL);

						coin->runAction(seq);
					}
				}
				else {
					if (_currentRoad == 0){
						MiniGTools::playEffect(EFFECT_HIT1);
					}
					else if (_currentRoad == 1){
						MiniGTools::playEffect(EFFECT_HIT2);
					}
					else if (_currentRoad == 2){
						MiniGTools::playEffect(EFFECT_HIT3);
					}
					else if (_currentRoad == 3){
						MiniGTools::playEffect(EFFECT_HIT4);
					}
				}
			}
		}
	}
}

void MiniHitMouseScene::movementCallback(Armature * armature, MovementEventType type, const char *  name)
{
	if (type == COMPLETE)
	{
		CCLOG("finishAniName=%s", name);
		removeMouse(armature);
	}
}

void  MiniHitMouseScene::refresh()
{
	//刷新时间
	_labTime->setString(MiniGTools::intToTime(_timeCount));

	//刷新金钱
	_labCoin->setString(IntToChar(_scores));  
}

void MiniHitMouseScene::startGame()
{
	//初始化变量
	_currentRoad = -1;
	_waveCount = 0;
	_timeCount = LEVELTIME;
	_scores = 0;
	_cutdownCount = 0;
	refresh();
	_state = GAME_INIT;

	//开场动画
	auto call = CallFunc::create([&](){

		Sprite *num = NULL;
		if (_cutdownCount == 0){
			num = Sprite::create("Minigames/Common/countdown_03.png");
			MiniGTools::playEffect(EFFECT_321);
			MiniGTools::playBgMusic(EFFECT_MOUSE_BG, true);
		}
		else if (_cutdownCount == 1){
			num = Sprite::create("Minigames/Common/countdown_02.png");
			MiniGTools::playEffect(EFFECT_321);
		}
		else if (_cutdownCount == 2){
			num = Sprite::create("Minigames/Common/countdown_01.png");
			MiniGTools::playEffect(EFFECT_321);
		}
		else if (_cutdownCount == 3){
			num = Sprite::create("Minigames/Common/countdown_go.png");
			MiniGTools::playEffect(EFFECT_GO);
			_state = GAME_RUN;
		}
		num->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		num->setScale(4);
		addChild(num, 10);

		auto scale = ScaleTo::create(0.5f, 1.0f);
		auto fadein = FadeOut::create(0.5f);
		auto spawn = Spawn::createWithTwoActions(scale, fadein);
		auto remove = RemoveSelf::create();
		num->runAction(Sequence::create(scale, fadein, spawn, remove, NULL));
	});
	auto delayTime = DelayTime::create(0.6f);
	auto call1 = CallFunc::create([&](){
		_cutdownCount++; 
		if (_cutdownCount >= 4){
			//防止重复计数器
			unschedule(schedule_selector(MiniHitMouseScene::tick));
			unschedule(schedule_selector(MiniHitMouseScene::createMouseWave));
			//开始计数器
			this->schedule(schedule_selector(MiniHitMouseScene::tick), 1.0f);
			this->schedule(schedule_selector(MiniHitMouseScene::createMouseWave), WAVEINTERVAL);
			this->createMouseWave(0);;

		}
	});
	auto seq = Sequence::create(call, delayTime, call1, NULL);
	auto rep = Repeat::create(seq, 4);
	runAction(rep); 
}


void MiniHitMouseScene::restartGame()
{
	MiniBaseLayer::restartGame();
	Director::getInstance()->replaceScene(MiniHitMouseScene::createScene());
}

void MiniHitMouseScene::pauseMiniGame()
{
	MiniBaseLayer::pauseMiniGame();
}

void MiniHitMouseScene::resumeMiniGame()
{
	MiniBaseLayer::resumeMiniGame();
}

//
//void MiniHitMouseScene::showGameOver()
//{
//	if (_gameOverBoard){
//		_gameOverBoard->removeFromParent();
//		_gameOverBoard = NULL;
//	}
//
//	_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
//
//	Widget *_btnQuit = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
//	_btnQuit->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::returnGame, this));
//	Widget *_btnRestart = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
//	_btnRestart->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::restartGame, this));
//	Widget *_imgBoard = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
//	_imgBoard->setPositionX(SCREEN_WIDTH / 2);
//
//	TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
//	_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[HitMouse_Index].game_target_score)->getCString());
//
//	bool _bIsSuccess = false;
//	if (_coins >= miniGameNames[HitMouse_Index].game_target_score){
//		_bIsSuccess = true;
//	}
//	TextAtlas * _labelScore1 = (TextAtlas*)Helper::seekWidgetByName(_gameOverBoard, "Label_Ticket_1");
//	TextAtlas * _labelScore2 = (TextAtlas*)Helper::seekWidgetByName(_gameOverBoard, "Label_Ticket_2");
//	Sprite *_imgTitle1 = (Sprite*)Helper::seekWidgetByName(_gameOverBoard, "Img_Success_Title");
//	Sprite *_imgTitle2 = (Sprite*)Helper::seekWidgetByName(_gameOverBoard, "Img_Fail_Title");
//	if (_bIsSuccess){
//		MiniGTools::playEffect(EFFECT_GAME_WIN);
//
//		_labelScore1->setVisible(true);
//		_labelScore2->setVisible(false);
//		_imgTitle1->setVisible(true);
//		_imgTitle2->setVisible(false);
//
//		_btnRestart->setVisible(false);
//		_btnQuit->setPositionX(_imgBoard->getContentSize().width / 2);
//	}
//	else {
//		MiniGTools::playEffect(EFFECT_GAME_OVER);
//
//		_labelScore1->setVisible(false);
//		_labelScore2->setVisible(true);
//		_imgTitle1->setVisible(false);
//		_imgTitle2->setVisible(true);
//	}
//	_labelScore1->setString(__String::createWithFormat("%d", _coins)->getCString());
//	_labelScore2->setString(__String::createWithFormat("%d", _coins)->getCString());
//	 
//	 
//
//	ImageView * bg = (ImageView*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
//	if (MiniGTools::getInstance()->isNativeAdLoaded()) {
//		bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT*0.5 + bg->getContentSize().height / 2 ));
//		MiniGTools::getInstance()->showNativeAd();
//	}
//	else {
//		bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
//	}
//
//	_state = GAME_OVER;
//	_viewStatus = View_Status_GameOver;
//	addChild(_gameOverBoard, 11);
//	playShowGameOverAnimation(_gameOverBoard);
//}
//
//void MiniHitMouseScene::pauseGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
// 
//		if (_isPauseGame)
//		{
//			return;
//		}
//		_isPauseGame = true;
//
//		MiniGTools::playEffect(EFFECT_BUTTON);
//
//
//		if (_pauseBoard){
//			_pauseBoard->removeFromParent();
//			_pauseBoard = NULL;
//		}
//		_pauseBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
//
//		Widget *_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Restart");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::restartGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Quit");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::quitGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Close");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniHitMouseScene::resumeGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		_widget->setPositionX(SCREEN_WIDTH / 2);
//
//
//
//
//		//暂停
//		//Director::getInstance()->pause();
//		pauseMiniGame();
//
//		//if (MiniGTools::getInstance()->isPopAdLoaded()){
//		//	MiniGTools::getInstance()->showPopAd();
//		//}
//
//		//弹出窗口
//		addChild(_pauseBoard, 11);
//
//		ImageView * bg = (ImageView*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		if (MiniGTools::getInstance()->isNativeAdLoaded()) {
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + bg->getContentSize().height / 2));
//			MiniGTools::getInstance()->showNativeAd();
//		}
//		else {
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
//		}
//	}
//}
//
//
//void MiniHitMouseScene::resumeGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		resumeMiniGame();
//		_pauseBoard->removeFromParent();
//		_pauseBoard = NULL;
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//void MiniHitMouseScene::restartGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//
//	/*	if (_pauseBoard->getParent())
//		{
//			_pauseBoard->removeFromParent();
//		}
//		if (_gameOverBoard->getParent())
//		{
//			_gameOverBoard->removeFromParent();
//		}*/
//
//		//Director::getInstance()->resume();
//
//		resumeMiniGame();
//
//		for (int i = _arrs->count() - 1; i >= 0; i--){
//			Mouse *m = (Mouse*)_arrs->getObjectAtIndex(i);
//			removeMouse(m);
//		}
//		//startGame();
//
//		Director::getInstance()->replaceScene(MiniHitMouseScene::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//
//void MiniHitMouseScene::quitGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		MiniGTools::getInstance()->stopAllSound();
//		//Director::getInstance()->resume();
//
//		resumeMiniGame();
//		Director::getInstance()->replaceScene(MiniGame::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//void MiniHitMouseScene::returnGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		//Director::getInstance()->resume();
//		resumeMiniGame();
//
//		MiniGTools::stopBgMusic();
//
//		if (_coins >= miniGameNames[HitMouse_Index].game_target_score){
//			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Success);
//		}
//		else {
//			Director::getInstance()->replaceScene(MiniGame::createScene());
//		}
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
