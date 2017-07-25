#include "MiniFishingScene.h" 
#include "../MiniGamePublic.h"
#include "../Miniutils/MiniGTools.h"
#include "../MiniGame.h"

#pragma mark MiniFishingGame

#define LEVELTIME  60*2
#define MOVETIME   3.0f

#define WATER_LINE			680 
#define ROPE_LENGTH			100
#define ROPE_ROTATION		5.0/2
#define ROPE_MAX			700
#define ROPE_ATTACK_TIME	3.0
#define ROPE_WITHDRAW_TIME	5.0

#define HOOK_ATTACK_TAG		1000
#define HOOK_REDRAW_TAG		1001

#define WAVE_FISH_INTERVAL		2
#define ANI_ZENGYI			"ANI_ZENGYI"
#define ANI_JIANYI			"ANI_JIANYI"

//======================================================================================
Fish::Fish()
{
	_fishID = FISH1;
	_fishDir = FISH_LEFT;
	_isFinishMove = false;
}

Fish::~Fish()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

Fish *Fish::create(const std::string& name, FISH_ID id)
{
	Fish *fish = new (std::nothrow) Fish();
	if (fish && fish->initWithSpriteFrameName(name))
	{
		fish->setFishID(id);
		fish->autorelease();

		return fish;
	}
	CC_SAFE_DELETE(fish);
	return nullptr;
}

//======================================================================================

typedef struct _FishData{
	FISH_ID				 _type;
	string				 _spriteFile;
	float				 _speed;
	FISH_BONUS_TYPE		 _bonusType;
	int					 _bonus;
	Point				 _anchorBeFired;
	float				 _rotationBeFired;
	float				 _withDrawSpeed;

} FishData;
 
//EDIT BY SUBO
FishData fishLevelDatas[] = {
	{ FISH1, "fishing_ani_fiah_01.png", 8 * 1.5f, FISH_COIN, 2, Point(0.1, 0.3), 90.0f, 1.0f },
	{ FISH2, "fishing_ani_fiah_02.png", 10 * 1.5f, FISH_COIN, 1, Point(0.1, 0.3), 90.0f, 1.0f },
	{ FISH3, "fishing_ani_fiah_03.png", 6 * 1.5f, FISH_COIN, 2, Point(0.4, 0.9), 0.0f, 1.0f },
	{ FISH4, "fishing_ani_fiah_04.png", 8 * 1.5f, FISH_ATTACK, 5, Point(0.1, 0.2), 90.0f, 1.0f },
	{ FISH5, "fishing_ani_fiah_05.png", 5 * 1.5f, FISH_ATTACK, 10, Point(0.1, 0.2), 90.0f, 1.0f },
	{ FISH6, "fishing_ani_fiah_06.png", 7 * 1.5f, FISH_SUPPLY, 5, Point(0.1, 0.2), 90.0f, 1.0f },
	{ FISH7, "fishing_ani_fiah_07.png", 5 * 1.5f, FISH_SUPPLY, 10, Point(0.1, 0.2), 90.0f, 1.0f },
	{ FISH8, "fishing_ani_fiah_08.png", 4 * 1.5f, FISH_COIN, 3, Point(0.4, 0.9), 0.0f, 1.0f },
	{ FISH9, "fishing_ani_fiah_09.png", 3 * 1.5f, FISH_COIN, 7, Point(0.1, 0.4), 90.0f, 2.0f },
};


int _fishDataCounts = sizeof(fishLevelDatas) / sizeof(fishLevelDatas[0]);


//======================================================================================

MiniFishingScene::MiniFishingScene()
{
	_currentGameIndex = MINI_GAME_FISHING;

	//_rootWidget = NULL;
	/*_pauseBoard = NULL;
	_gameOverBoard = NULL;*/
	_labTime = NULL;
	_labCoin = NULL;

	_timeCount = 0;
	//_coins = 0;
	_cutdownCount = 0;
	_waveCount = 0;
	_state = GAME_INIT;
	_soundID = -1;
	_lastFishY = 0;
	_lastFishHeight = 0;
	//_isPauseGame = false;
	_bIsGameOver = false;

	//_arrs = __Array::create();
	//_arrs->retain();

	preLoadResource();
}

MiniFishingScene::~MiniFishingScene()
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

	unloadResource();
	 
	/*if (_soundID > 0){
		MiniGTools::stopEffect(_soundID);
		_soundID = -1;
	}*/
	MiniGTools::stopAllSound();
}


Scene* MiniFishingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniFishingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MiniFishingScene::init()
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

void MiniFishingScene::preLoadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minigames/Fishing/Fishing.plist"); 

	MiniGTools::addAnimation("fish_ani_zengyi_", ANI_ZENGYI);
	MiniGTools::addAnimation("fish_ani_jianyi_", ANI_JIANYI);
}

void MiniFishingScene::unloadResource()
{
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/Fishing/Fishing.plist");

	//Director::getInstance()->getScheduler()->schedule([&](float dt){
	//	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	//}, this, 0.02f, 0, 0, false, "SCHEDULE_CLEAR");
}
 
void MiniFishingScene::createUI()
{
	//载入GUI
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Fishing.json");
	addChild(bg, 0);

	//根据屏幕重新定位控件

	Widget *_widget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Top");
	_widget->setPositionY(SCREEN_HEIGHT - _widget->getContentSize().height);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Img_Bar_Bg");
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Button_Pause");
	_widget->setPositionX(SCREEN_WIDTH - _widget->getContentSize().width / 2  );
	_widget->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			showPausePanel();
		}
	});
	_pauseButtonPos = MiniGTools::getInstance()->toWorldPoint(_widget);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Sea");
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);
	float seaHeight = _widget->getContentSize().height;


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Sky");
	_widget->setScale(SCREEN_WIDTH / _widget->getContentSize().width, (SCREEN_HEIGHT - seaHeight + 40) / _widget->getContentSize().height);
	_widget->setPositionY(SCREEN_HEIGHT);

	//创建船身
	_boad = Sprite::createWithSpriteFrameName("fishing_ani_chuang.png");
	_boad->setAnchorPoint(Point(0, 0));
	bg->addChild(_boad, 2);
	_boad->setPosition(Point(SCREEN_WIDTH / 2, WATER_LINE - 10));

	//标签控件
	_labTime = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Time");
	_labCoin = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Coin");


	TextAtlas *_labTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Target");
	_labTarget->setString(__String::createWithFormat("%d", miniGameNames[Fishing_Index].game_target_score)->getCString());

	//创建暂停和结算
	/*{
		_pauseBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
		_pauseBoard->retain();

		Widget *_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Restart");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::restartGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Quit");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::quitGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Close");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::resumeGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
		_widget->setPositionX(SCREEN_WIDTH / 2);
	}

	{
		_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
		_gameOverBoard->retain();

		Widget *_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::returnGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::restartGame, this));
		_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
		_widget->setPositionX(SCREEN_WIDTH / 2);


		TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
		_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[Fishing_Index].game_target_score)->getCString());

	}*/

	//注册全局touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniFishingScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//创建气泡粒子
	ParticleSystem* m_emitter = ParticleSystemQuad::create("Minigames/Fishing/effect_diaoyu_paopao.plist");
	ParticleBatchNode *_particleBatch = ParticleBatchNode::createWithTexture(m_emitter->getTexture());
	bg->addChild(_particleBatch, 10);
	_particleBatch->addChild(m_emitter);
	m_emitter->setPosition(Point(SCREEN_WIDTH*0.5, 0));

	//创建绳子和钩子
	Sprite *rope = Sprite::create("Minigames/Fishing/fishrope.png");
	Rect ropeRect = Rect(0, 0, rope->getContentSize().width, rope->getContentSize().height);
	Rect capRect = Rect(1, 0, 6, 2);
	_rope = ui::Scale9Sprite::create("Minigames/Fishing/fishrope.png", ropeRect, capRect);
	_rope->setContentSize(Size(ROPE_LENGTH, 2));
	_rope->setAnchorPoint(Point(0, 0.5));
	_rope->getSprite()->getTexture()->setAliasTexParameters();
	addChild(_rope, 10);

	_ropeLenght = ROPE_LENGTH;

	_ropePoint1 = Point(_boad->getPositionX() + 5, _boad->getPositionY() + 165);
	_ropePoint2 = Point(_boad->getPositionX() + 188, _boad->getPositionY() + 88);


	_rope->setPosition(_ropePoint1);
	_rope->setColor(Color3B::BLACK);
	_rope->setRotation(90);

	auto rotate1 = RotateTo::create(ROPE_ROTATION, 135);
	auto rotate2 = RotateTo::create(ROPE_ROTATION, 45);
	auto seq = Sequence::createWithTwoActions(rotate1, rotate2);
	_rope->runAction(RepeatForever::create(seq));

	_hook = Sprite::createWithSpriteFrameName("fishing_ani_hook.png");
	_hook->setAnchorPoint(Point(0.5, 1));
	_hook->setRotation(-90);
	_hook->setPosition(CCP_SPRITE(1, 0.5, _rope));
	_rope->addChild(_hook);

	this->schedule(schedule_selector(MiniFishingScene::tick));//边界检测与碰撞检测

	startGame();

}

void MiniFishingScene::createWaveFish(float dt){

	int fishCount = 1;

	// 大波来的数目减少为2~3个；每隔6秒小爆发一下 
	if (_waveCount>0 && _waveCount % 3 == 0) {
		fishCount = rand() % 2 == 0 ? 2 : 3;
	}

	for (int i = 0; i < fishCount; i++){

		//随机产生鱼
		int  _fishRand = rand() % 100;
		FISH_ID  _fishID = FISH1;
		if (_fishRand >= 0 && _fishRand < 10){
			_fishID = FISH1;
		}
		else  if (_fishRand >= 10 && _fishRand < 30){
			_fishID = FISH2;
		}
		else  if (_fishRand >= 30 && _fishRand < 40){
			_fishID = FISH3;
		}
		else  if (_fishRand >= 40 && _fishRand < 50){
			_fishID = FISH4;
		}
		else  if (_fishRand >= 50 && _fishRand < 55){
			_fishID = FISH5;
		}
		else  if (_fishRand >= 55 && _fishRand < 70){
			_fishID = FISH6;
		}
		else  if (_fishRand >= 70 && _fishRand < 80){
			_fishID = FISH7;
		}
		else  if (_fishRand >= 80 && _fishRand < 95){
			_fishID = FISH8;
		}
		else  if (_fishRand >= 95 && _fishRand <= 100){
			_fishID = FISH9;
		}
		else {
			return;
		}

		//创建鱼
		FishData data = fishLevelDatas[_fishID];
		Fish *fish = (Fish*)Fish::create(data._spriteFile.c_str(), _fishID);
		addChild(fish, 5);


		//特殊鱼的特效添加
		if (data._bonusType == FISH_ATTACK || data._bonusType == FISH_SUPPLY){
			string aniName = "";
			Point effectPos;
			if (data._bonusType == FISH_ATTACK){
				aniName = ANI_JIANYI;
				effectPos = CCP_SPRITE(0.7, 0.44, fish);
			}
			else{
				aniName = ANI_ZENGYI;
				effectPos = CCP_SPRITE(0.5, 0.5, fish);
			}

			if (AnimationCache::getInstance()->getAnimation(aniName)) {
				Sprite *effect = Sprite::create();

				effect->setPosition(effectPos);
				fish->addChild(effect);

				auto animation = AnimationCache::getInstance()->getAnimation(aniName);
				auto ani = Animate::create(animation);
				auto rep = RepeatForever::create(ani);
				effect->runAction(rep);
			}
		}

		//获得高度 
		int _randHeight = (WATER_LINE - fish->getContentSize().height - 50 -100 ); //要减去波浪的高度50,再减去广告高度 100
		float _randY = rand() % _randHeight + fish->getContentSize().height / 2  + 100 ;
		float _dynamicHeight = _lastFishHeight + fish->getContentSize().height / 2;
		while (fabs(_randY - _lastFishY)<_dynamicHeight)
		{
			_randY = rand() % _randHeight + fish->getContentSize().height / 2 +100;
		}
		//记录当前鱼的高度和 身高
		_lastFishY = _randY;
		_lastFishHeight = fish->getContentSize().height / 2;

		//移动距离
		float _moveWidth = SCREEN_WIDTH + fish->getContentSize().width;

		//获得产生方向
		int  _dir = rand() % 10;
		if (_dir < 5) {
			fish->setDirection(FISH_LEFT);
			fish->setPosition(Point(SCREEN_WIDTH + fish->getContentSize().width / 2, _randY));
		}
		else {
			fish->setDirection(FISH_RIGHT);
			fish->setScaleX(-1);
			fish->setPosition(Point(-fish->getContentSize().width / 2, _randY));
		}
		//移动的距离
		_moveWidth = _moveWidth * (fish->getDirection() == FISH_LEFT ? -1 : 1);

		float _delayTime = 0;
		if (i>0){
			_delayTime = ((rand() % 30) / 100.0f) + 0.1;
		}

		//根据Fish类型产生不同的动作
		auto delaytime = DelayTime::create(_delayTime);

		auto move = MoveBy::create(data._speed, Point(_moveWidth, 0));
		auto callback = CallFuncN::create(CC_CALLBACK_1(MiniFishingScene::onFishFinishAction, this));
		Sequence * seq = Sequence::create(delaytime, move, callback, NULL);
		fish->runAction(seq);

		//将鱼加入到数组
		_arrs->addObject(fish);
	}
	_waveCount++;
}


void MiniFishingScene::removePoolFish(Ref *pSender)
{
	Fish *fish = (Fish*)pSender;
	fish->removeFromParentAndCleanup(true);

	_arrs->removeObject(fish);
}

void MiniFishingScene::removeFish(Ref *pSender)
{
	Fish *fish = (Fish*)pSender;
	fish->removeFromParentAndCleanup(true);
}

void MiniFishingScene::onFishFinishAction(Ref *pSender)
{
	Fish *fish = (Fish*)pSender;
	fish->setIsFinishMove(true);
	fish->setVisible(false);
}

void MiniFishingScene::onAddCoinCallback(Ref *pSender){
	if (_state != GAME_OVER){
		_scores++;
		refresh();
		MiniGTools::playEffect(EFFECT_COIN1);
	} 
}

void MiniFishingScene::onAddTimeCallback(Ref *pSender, void* data){
	if (_state != GAME_OVER){
		int time = (int)data;
		_timeCount = MIN(_timeCount + time, LEVELTIME);
		refresh();
		MiniGTools::playEffect(EFFECT_INCREASETIME);
	} 
}

void MiniFishingScene::onSubTimeCallback(Ref *pSender, void* data){
	if (_state != GAME_OVER){
		int time = (int)data;
		_timeCount = MAX(_timeCount - time, 0);
		refresh();
		MiniGTools::playEffect(EFFECT_DECREASETIME);
	}
}


void MiniFishingScene::tick(float dt){
	//根据钩子位置，定位绳子长短 
	_rope->setContentSize(Size(_hook->getPositionX(), _rope->getContentSize().height));

	if (_state == GAME_RUN || _state == GAME_ANIMATION) {

		//计算钩子的中点
		float _hookLength = _rope->getContentSize().width + _hook->getContentSize().height / 2;
		float radians = CC_DEGREES_TO_RADIANS(_rope->getRotation());
		Point endPoint = _ropePoint1 + Point(cos(radians) * _hookLength, -sinf(radians) * _hookLength);

		if (_state == GAME_RUN)
		{
			//判断是否出界			
			if (_hook->getActionByTag(HOOK_ATTACK_TAG)){
				if (endPoint.x <= 0 || endPoint.x >= SCREEN_WIDTH){
					_hook->stopActionByTag(HOOK_ATTACK_TAG);

					auto move = MoveTo::create(ROPE_WITHDRAW_TIME * ((_rope->getContentSize().width - ROPE_LENGTH) / ROPE_MAX),
						Point(ROPE_LENGTH, _rope->getContentSize().height / 2));
					auto call = CallFunc::create([&](){
						Director::getInstance()->getActionManager()->resumeTarget(_rope);
						_state = GAME_READY;

						MiniGTools::stopEffect(_soundID);
						_soundID = -1;
					});
					Sequence *seq = Sequence::createWithTwoActions(move, call);
					seq->setTag(HOOK_REDRAW_TAG);
					_hook->runAction(seq);

					if (_soundID >= 0){
						MiniGTools::stopEffect(_soundID);
					}
					_soundID = MiniGTools::playEffect(EFFECT_ROPE, true);
				}
			}

			//判断是否碰撞
			Rect _hookRect = Rect(endPoint.x - _hook->getContentSize().height / 2, endPoint.y - _hook->getContentSize().height / 2, _hook->getContentSize().height, _hook->getContentSize().height);

			for (int i = (_arrs->count() - 1); i >= 0; i--){
				Fish *fish = (Fish*)_arrs->getObjectAtIndex(i);

				Rect _fishRect = Rect(fish->getPositionX() - fish->getContentSize().height / 2,
					fish->getPositionY() - fish->getContentSize().height / 2,
					fish->getContentSize().height,
					fish->getContentSize().height);

				if (_hook->getChildrenCount() == 0 && _hookRect.intersectsRect(_fishRect)){

					//根据鱼类型产生不同的效果
					FishData fishData = fishLevelDatas[fish->getFishID()];

					//让鱼挂到钩子上
					//fish->retain();
					fish->removeFromParent();
					fish->setPosition(CCP_SPRITE(0, 0.5, _hook));
					fish->setAnchorPoint(fishData._anchorBeFired);
					fish->setScaleX(1);
					fish->setRotation(fishData._rotationBeFired);

					_hook->addChild(fish);
					//fish->release();
					_arrs->removeObject(fish);


					if (fish->getChildrenCount() > 0){
						fish->removeAllChildren();
					}

					//收货鱼
					_hook->stopAllActions();

					auto move = MoveTo::create(ROPE_WITHDRAW_TIME * fishData._withDrawSpeed  * ((_rope->getContentSize().width - ROPE_LENGTH) / ROPE_MAX),
						Point(ROPE_LENGTH, _rope->getContentSize().height / 2));
					auto call = CallFunc::create([&](){
						if (_hook->getChildrenCount() > 0){
							Fish *fish = (Fish*)(_hook->getChildren().at(0));
							if (fish){
								Point worldPos = _hook->convertToWorldSpace(fish->getPosition());

								fish->retain();
								fish->removeFromParent();
								fish->setPosition(worldPos);
								addChild(fish, 5);


								//根据鱼类型产生不同的效果
								FishData data = fishLevelDatas[fish->getFishID()];
								if (data._bonusType == FISH_COIN) {

									MiniGTools::playEffect(EFFECT_COIN2);

									//奖励1-3个金币
									for (int i = 0; i < data._bonus; i++){

										Sprite *coin = Sprite::create("Minigames/Common/ui_minigame_floor_stars.png");
										coin->setPosition(fish->getPosition());
										this->addChild(coin, 10);
										coin->setVisible(false);

										auto delay0 = DelayTime::create(0.2f);
										auto show = Show::create();

										float randomX = rand() % 100 - 50;
										float randomY = rand() % 60 - 30;
										float randomHeight = rand() % 60 - 30;
										auto jump = JumpBy::create(0.3f, Vec2(randomX, -100 + randomY), 100 + randomHeight, 1);
										auto delay1 = DelayTime::create(0.3f);

										Point targetPos = _labCoin->getParent()->convertToWorldSpace(_labCoin->getPosition());

										auto move = MoveTo::create(0.5f, targetPos);
										auto scale = ScaleTo::create(0.5f, 0.2f);
										auto spawn = Spawn::createWithTwoActions(move, scale);
										auto call = CallFuncN::create(CC_CALLBACK_1(MiniFishingScene::onAddCoinCallback, this));

										auto remove = RemoveSelf::create();
										auto seq = Sequence::create(delay0, show, jump, delay1, spawn, call, remove, NULL);

										coin->runAction(seq);
									}
								}
								else if (data._bonusType == FISH_ATTACK) {
									//攻击，掉时间

									{
										auto effect = Sprite::createWithSpriteFrameName("fish_attack_effect.png");
										addChild(effect, 10);
										effect->setPosition(CCP_SCREEN(0.5, 0.5));
										effect->setScale(SCREEN_WIDTH / effect->getContentSize().width, SCREEN_HEIGHT / effect->getContentSize().height);
										auto fadeout = FadeOut::create(0.1f);
										auto fadein = FadeIn::create(0.1f);
										auto seq = Sequence::create(fadeout, fadein, NULL);
										auto rep = Repeat::create(seq, 3);
										auto remove = RemoveSelf::create();
										auto seq2 = Sequence::create(rep, remove, NULL);
										effect->runAction(seq2);


										//播放音效
										MiniGTools::playEffect(EFFECT_DAMAGE);
									}

									Sprite *timeicon = Sprite::create("Minigames/Common/mini_ui_info_time.png");
									timeicon->setPosition(fish->getPosition());
									this->addChild(timeicon, 10);
									timeicon->setVisible(false);

									Sprite *time = NULL;
									if (data._bonus == 5) {
										time = Sprite::createWithSpriteFrameName("fish_sub_5s.png");
									}
									else  {
										time = Sprite::createWithSpriteFrameName("fish_sub_10s.png");
									}
									time->setAnchorPoint(Point(0, 0.5));
									time->setPosition(CCP_SPRITE(1.1, 0.5, timeicon));
									time->setScale(0.6f);
									timeicon->addChild(time);

									auto delay0 = DelayTime::create(0.2f);
									auto show = Show::create();

									float randomX = 0;
									float randomY = rand() % 60 - 30;
									float randomHeight = rand() % 60 - 30;
									auto jump = JumpBy::create(0.3f, Vec2(randomX, -100 + randomY), 100 + randomHeight, 1);
									auto delay1 = DelayTime::create(0.3f);

									Point targetPos = _labTime->getParent()->convertToWorldSpace(_labTime->getPosition());

									auto move = MoveTo::create(0.5f, targetPos);
									auto scale = ScaleTo::create(0.5f, 0.2f);
									auto spawn = Spawn::createWithTwoActions(move, scale);
									auto call = CallFuncN::create(CC_CALLBACK_1(MiniFishingScene::onSubTimeCallback, this, (void*)data._bonus));

									auto remove = RemoveSelf::create();
									auto seq = Sequence::create(delay0, show, jump, delay1, spawn, call, remove, NULL);

									timeicon->runAction(seq);
								}
								else if (data._bonusType == FISH_SUPPLY) {
									//补给 ,增加时间

									Sprite *timeicon = Sprite::create("Minigames/Common/mini_ui_info_time.png");
									timeicon->setPosition(fish->getPosition());
									this->addChild(timeicon, 10);
									timeicon->setVisible(false);


									Sprite *time = NULL;
									if (data._bonus == 5) {
										time = Sprite::createWithSpriteFrameName("fish_add_5s.png");
									}
									else  {
										time = Sprite::createWithSpriteFrameName("fish_add_10s.png");
									}
									time->setAnchorPoint(Point(0, 0.5));
									time->setPosition(CCP_SPRITE(1.1, 0.5, timeicon));
									time->setScale(0.6f);
									timeicon->addChild(time);

									auto delay0 = DelayTime::create(0.2f);
									auto show = Show::create();

									float randomX = 0;
									float randomY = rand() % 60 - 30;
									float randomHeight = rand() % 60 - 30;
									auto jump = JumpBy::create(0.3f, Vec2(randomX, -100 + randomY), 100 + randomHeight, 1);
									auto delay1 = DelayTime::create(0.3f);

									Point targetPos = _labTime->getParent()->convertToWorldSpace(_labTime->getPosition());

									auto move = MoveTo::create(0.5f, targetPos);
									auto scale = ScaleTo::create(0.5f, 0.2f);
									auto spawn = Spawn::createWithTwoActions(move, scale);

									auto call = CallFuncN::create(CC_CALLBACK_1(MiniFishingScene::onAddTimeCallback, this, (void*)data._bonus));

									auto remove = RemoveSelf::create();
									auto seq = Sequence::create(delay0, show, jump, delay1, spawn, call, remove, NULL);

									timeicon->runAction(seq);
								}

								//让鱼落到箱子里面
								auto jump = JumpTo::create(1.0f, _ropePoint2, 200, 1);
								auto scale = ScaleTo::create(1.0f, 0);
								auto rotate = RotateBy::create(1.0, 360);
								auto rep = RepeatForever::create(rotate);
								auto spawn = Spawn::create(jump, scale, rep, NULL);
								auto call = CallFuncN::create(CC_CALLBACK_1(MiniFishingScene::removeFish, this));
								auto seq = Sequence::create(spawn, call, NULL);
								fish->runAction(seq);
								fish->release();

							}
						}

						Director::getInstance()->getActionManager()->resumeTarget(_rope);
						_state = GAME_READY;

						MiniGTools::stopEffect(_soundID);
						_soundID = -1;
					});
					Sequence *seq = Sequence::createWithTwoActions(move, call);
					seq->setTag(HOOK_REDRAW_TAG);

					_hook->runAction(seq);

					//播放绳子音效
					if (_soundID >= 0){
						log("_soundid stop step20 =%d", _soundID);
						MiniGTools::stopEffect(_soundID);
					}
					_soundID = MiniGTools::playEffect(EFFECT_ROPE, true);
					log("_soundid  2 =%d", _soundID);
				}
			}
		}
	}


	for (int i = (_arrs->count() - 1); i >= 0; i--){
		Fish *fish = (Fish*)_arrs->getObjectAtIndex(i);
		if (fish->getIsFinishMove()){
			removePoolFish(fish);
		}
	}
}

void MiniFishingScene::cunDownTick(float dt)
{
	_timeCount = MAX(_timeCount--, 0);
	refresh();
	if (_timeCount == 0) {
		unschedule(schedule_selector(MiniFishingScene::createWaveFish));
		unschedule(schedule_selector(MiniFishingScene::cunDownTick));
		//showGameOver();
		showGameOverPanel();
	}
}

//点击屏幕事件
bool MiniFishingScene::onTouchBegan(Touch* touch, Event  *event)
{
	if (_state != GAME_READY){
		return false;
	}

	Director::getInstance()->getActionManager()->pauseTarget(_rope);
	_state = GAME_RUN;

	auto move1 = MoveTo::create(ROPE_ATTACK_TIME, Point(ROPE_LENGTH + ROPE_MAX, _rope->getContentSize().height / 2));
	auto move2 = MoveTo::create(ROPE_ATTACK_TIME, Point(ROPE_LENGTH, _rope->getContentSize().height / 2));
	auto call = CallFunc::create([&](){
		Director::getInstance()->getActionManager()->resumeTarget(_rope);
		_state = GAME_READY;
	});
	Sequence *seq = Sequence::create(move1, move2, call, NULL);
	seq->setTag(HOOK_ATTACK_TAG);
	_hook->runAction(seq);

	return true;
}

void MiniFishingScene::startGame()
{
	//初始化变量
	_timeCount = LEVELTIME;
	_scores = 0;
	_state = GAME_INIT;
	_cutdownCount = 0;
	_waveCount = 0;

	refresh();

	//开场动画
	auto call = CallFunc::create([&](){

		Sprite *num = NULL;
		if (_cutdownCount == 0){
			num = Sprite::create("Minigames/Common/countdown_03.png");
			MiniGTools::playEffect(EFFECT_321);
			MiniGTools::playBgMusic(EFFECT_FISH_BG, true);
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
			_state = GAME_READY;
		}
	});
	auto seq = Sequence::create(call, delayTime, call1, NULL);
	auto rep = Repeat::create(seq, 4);
	runAction(rep);

	//防止重复计数器
	unschedule(schedule_selector(MiniFishingScene::createWaveFish));
	unschedule(schedule_selector(MiniFishingScene::cunDownTick));
	//重新执行计数器

	this->schedule(schedule_selector(MiniFishingScene::createWaveFish), WAVE_FISH_INTERVAL);//1s产生一批怪物
	this->schedule(schedule_selector(MiniFishingScene::cunDownTick), 1); //显示关卡时间

}

void MiniFishingScene::refresh()
{
	//刷新时间
	_labTime->setString(MiniGTools::intToTime(_timeCount));
	_labCoin->setString(IntToChar(_scores));
}


void MiniFishingScene::restartGame()
{
	MiniBaseLayer::restartGame();
	Director::getInstance()->replaceScene(MiniFishingScene::createScene());
}

void MiniFishingScene::pauseMiniGame()
{
	MiniBaseLayer::pauseMiniGame();
	_rope->pauseSchedulerAndActions();
	_hook->pauseSchedulerAndActions();
}

void MiniFishingScene::resumeMiniGame()
{
	MiniBaseLayer::resumeMiniGame();
	//if (_hook->getChildrenCount() == 0){
	if (_hook->getNumberOfRunningActions() == 0){
		_rope->resumeSchedulerAndActions();
	}
	else {
		_hook->resumeSchedulerAndActions();
	}
}


//void MiniFishingScene::showGameOver()
//{
//	if (_gameOverBoard){
//		_gameOverBoard->removeFromParent();
//		_gameOverBoard = NULL;
//	}
//
//	_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
//
//	Widget *_btnQuit = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
//	_btnQuit->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::returnGame, this));
//	Widget *_btnRestart = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
//	_btnRestart->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::restartGame, this));
//	Widget *_imgBoard = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
//	_imgBoard->setPositionX(SCREEN_WIDTH / 2);
//
//	TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
//	_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[Fishing_Index].game_target_score)->getCString());
//
//
//
//
//
//	bool _bIsSuccess = false;
//	if (_coins >= miniGameNames[Fishing_Index].game_target_score){
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
//		bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT*0.5 + bg->getContentSize().height / 2));
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
//void MiniFishingScene::pauseGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		if (_isPauseGame)
//		{
//			return;
//		}
//		_isPauseGame = true;
//
//		MiniGTools::playEffect(EFFECT_BUTTON);
//
//		if (_pauseBoard){
//			_pauseBoard->removeFromParent();
//			_pauseBoard = NULL;
//		}
//		_pauseBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
//
//		Widget *_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Restart");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::restartGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Quit");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::quitGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Close");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFishingScene::resumeGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		_widget->setPositionX(SCREEN_WIDTH / 2);
//
//
//
//
//		//暂停
//		Director::getInstance()->pause();
//
//		//if (MiniGTools::getInstance()->isPopAdLoaded()){
//		//	MiniGTools::getInstance()->showPopAd();
//		//}
//
//
//		ImageView * bg = (ImageView*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		if (MiniGTools::getInstance()->isNativeAdLoaded()) {
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + bg->getContentSize().height / 2));
//			MiniGTools::getInstance()->showNativeAd();
//		}
//		else {
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
//		}
//
//		//弹出窗口
//		addChild(_pauseBoard, 11);
//	}
//}
//
//
//void MiniFishingScene::resumeGame(Ref* ref, Widget::TouchEventType type)
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
//void MiniFishingScene::restartGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		//if (_pauseBoard->getParent())
//		//{
//		//	_pauseBoard->removeFromParent();
//		//}
//		//if (_gameOverBoard->getParent())
//		//{
//		//	_gameOverBoard->removeFromParent();
//		//}
//
//		/*Director::getInstance()->resume();*/
//		resumeMiniGame();
//
//		Director::getInstance()->replaceScene(MiniFishingScene::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//
//	}
//}
//
//
//void MiniFishingScene::quitGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		MiniGTools::getInstance()->stopAllSound();
//		//Director::getInstance()->resume();
//		resumeMiniGame();
//		Director::getInstance()->replaceScene(MiniGame::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//
//void MiniFishingScene::returnGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		//Director::getInstance()->resume();
//		resumeMiniGame();
//		MiniGTools::stopBgMusic();
//		SimpleAudioEngine::getInstance()->stopAllEffects();
//
//		if (_coins >= miniGameNames[Fishing_Index].game_target_score){
//			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Success);
//		}
//		else {
//			Director::getInstance()->replaceScene(MiniGame::createScene());
//		}
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
