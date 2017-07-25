#include "MiniFindCatScene.h" 
#include "../MiniGamePublic.h"
#include "../Miniutils/MiniGTools.h"
#include "../MiniGame.h" 
#define BOX_LAYER_Z    10 
 
Box::Box()
{
	_state = BOXSTATE::BOX_EMPTY;
	_target = 0;
	_isSelected = false;
}
Box::~Box()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

Box *Box::create(const std::string& name, BOXSTATE state)
{
	Box *armature = new (std::nothrow) Box();
	if (armature && armature->init(name))
	{
		armature->setState(state);
		armature->autorelease();

		return armature;
	}
	CC_SAFE_DELETE(armature);
	return nullptr;
}

void Box::playInitAnimation(){
	getAnimation()->stop();

	if (_state == BOXSTATE::BOX_CAT){
		getAnimation()->playWithIndex(FINDCAT_ANI_OPENCATBOX);
	}
	else {
		getAnimation()->playWithIndex(FINDCAT_ANI_OPENEMPTYBOX);
	}
}

void Box::playOpenAnimation(float delay/*=0*/)
{
	if (delay == 0){
		getAnimation()->stop();

		if (_state == BOXSTATE::BOX_CAT){
			getAnimation()->playWithIndex(FINDCAT_ANI_SHOWCATBOX);
		}
		else {
			getAnimation()->playWithIndex(FINDCAT_ANI_SHOWEMPTYBOX);
		}
	}
	else {
		auto delaytime = DelayTime::create(delay);
		auto call = CallFunc::create([&](){
			getAnimation()->stop();

			if (_state == BOXSTATE::BOX_CAT){
				getAnimation()->playWithIndex(FINDCAT_ANI_SHOWCATBOX);
			}
			else {
				getAnimation()->playWithIndex(FINDCAT_ANI_SHOWEMPTYBOX);
			}
		});
		runAction(Sequence::create(delaytime, call, NULL));
	}
}


void Box::playOpenWrongAnimation(float delay/*=0*/)
{
	if (delay == 0){
		getAnimation()->stop();
		getAnimation()->playWithIndex(FINDCAT_ANI_SHOWWRONGBOX);
	}
	else {
		auto delaytime = DelayTime::create(delay);
		auto call = CallFunc::create([&](){
			getAnimation()->stop();
			getAnimation()->playWithIndex(FINDCAT_ANI_SHOWWRONGBOX);
		});
		runAction(Sequence::create(delaytime, call, NULL));
	}
}


Rect Box::collisionRect()
{
	Point origin = getPosition();// this->getParent()->convertToWorldSpace(getPosition());
	return  Rect(origin.x - getContentSize().width / 2, origin.y - getContentSize().height / 2, getContentSize().width, getContentSize().height);
}

 

Point _points[4] = { Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0) };
int _zOrers[4] = { 2, 2, 1, 1 };
//int _scales[4] = { 1, 1, 0.8, 0.8 };
int _checkSeq[4] = { 0, 1, 2, 3 };;//{ 0,3,2,1 };

typedef struct _FindCateData{
	int id;
	int maxBoxs;
	int moveCount;
	float interval;
	int coin;
} FindCateData;

/*关卡的数据
波次/箱子数量/交换次数/交换的时间/奖励金币
*/

FindCateData catLevelDatas[] = {
	{ 1, 2, 1, 0.75 , 1 },
	{ 2, 2, 2, 0.75, 1 },
	{ 3, 2, 3, 0.75, 1 },
	{ 4, 2, 3, 0.75, 2},
	{ 5, 2, 4, 0.75, 2 },
	{ 6, 3, 4, 0.5, 2 },
	{ 7, 3, 4, 0.5, 3 },
	{ 8, 3, 5, 0.5, 3 },
	{ 9, 3, 5, 0.5, 3 },
	{ 10, 3, 5, 0.5, 3 },
	{ 11, 3, 5, 0.5, 3 },
	{ 12, 3, 5, 0.5, 3 },
	{ 13, 3, 5, 0.5, 3 },
	{ 14, 3, 6, 0.5, 3 },
	{ 15, 3, 6, 0.5, 3 },
	{ 16, 4, 6, 0.3, 4 },
	{ 17, 4, 6, 0.3, 4 },
	{ 18, 4, 6, 0.3, 4 },
	{ 19, 4, 7, 0.3, 4 },
	{ 20, 4, 7, 0.3, 4 },
	{ 21, 4, 7, 0.3, 4 },
	{ 22, 4, 7, 0.3, 4 },
	{ 23, 4, 7, 0.3, 4 },
	{ 24, 4, 7, 0.3, 4 },
	{ 25, 4, 7, 0.3, 4 },
	{ 26, 4, 8, 0.3, 4 },
	{ 27, 4, 8, 0.3, 4 },
	{ 28, 4, 8, 0.3, 4 },
	{ 29, 4, 8, 0.3, 4 },
	{ 30, 4, 8, 0.3, 5 },
};

int _levelDataCounts = sizeof(catLevelDatas) / sizeof(catLevelDatas[0]);

MiniFindCatScene::MiniFindCatScene()
{

	_currentGameIndex = MINI_GAME_FINDCAT;
	/*_rootWidget = NULL;*/
	//_pauseBoard = NULL;
	//_gameOverBoard = NULL;
	_labCoin = NULL;


	_state = GAME_INIT;

	_cutdownCount = 0;
	_roundCount = 1;
	//_coins = 0;
	_cSwapeCount = 0;
	_isFindingCat = false;
	_firstBoxIndex = 0;
  
	_BOX_MAX = 2;
	_BOX_SWAP_INTERVAL = 1.0f;
	_BOX_SWAP_COUNT = 1;

	_box1 = NULL;
	_box2 = NULL;
	_boxLayer = NULL;

	//_isPauseGame = false;
	preLoadResource();
}


MiniFindCatScene::~MiniFindCatScene()
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
	MiniGTools::stopAllSound();
}


Scene* MiniFindCatScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniFindCatScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MiniFindCatScene::init()
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

void MiniFindCatScene::preLoadResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minigames/FindCat/FindCatAni.plist");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Minigames/FindCat/FindCatAni.json");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minigames/CommonUI/topui.plist");
}
void MiniFindCatScene::unloadResource()
{
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/FindCat/FindCatAni.plist");
	//ArmatureDataManager::getInstance()->removeArmatureFileInfo("Minigames/FindCat/FindCatAni.json");
	//Director::getInstance()->getScheduler()->schedule([&](float dt){
	//	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	//}, this, 0.02f, 0, 0, false, "SCHEDULE_CLEAR");
}

void MiniFindCatScene::createUI()
{
	 

	//载入GUI
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_FindCat.json");
	addChild(bg, 0);

	_rootWidget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Game");

	//根据屏幕重新定位控件
	Widget *_widget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Top");
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


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bg");
	_widget->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	_widget->setScale(SCREEN_WIDTH / _widget->getContentSize().width, SCREEN_HEIGHT / _widget->getContentSize().height);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Img_Bar_Mask");
 
	//标签控件
	_labRound = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Round");
	_labCoin = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Coin");
	_labRound->setString("0");
	_labCoin->setString("1");

	_boxLayer = LayerColor::create(Color4B(0, 0, 0, 0));
	_boxLayer->setCascadeOpacityEnabled(false); 
	addChild(_boxLayer, BOX_LAYER_Z);
 
	TextAtlas *_labTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(bg, "Label_Target");
	_labTarget->setString(__String::createWithFormat("%d", miniGameNames[FindCat_Index].game_target_score)->getCString());

	//初始化坐标
	/*
	3	2
	1	4
	*/
	_points[0] = Point(SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.2);
	_points[1] = Point(SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.55);
	_points[2] = Point(SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.55);
	_points[3] = Point(SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.2);

	//创建暂停和结算
	


	//{
	//	_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
	//	_gameOverBoard->retain();

	//	Widget *_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
	//	_widget->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::returnGame, this));
	//	_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
	//	_widget->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::restartGame, this));
	//	_widget = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
	//	_widget->setPositionX(SCREEN_WIDTH / 2);


	//	TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
	//	_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[FindCat_Index].game_target_score)->getCString());

	//}

	//注册全局touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniFindCatScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	startGame();
}


//点击屏幕事件
bool MiniFindCatScene::onTouchBegan(Touch* touch, Event  *event)
{
	if (_state != GAME_RUN){
		return false;
	}
	else {
		auto location = touch->getLocation();

		bool _isClickBox = false;
		//计算是否点中箱子
		for (int i = 0; i < 4; i++){
			Box *b = getBoxByIndex(_checkSeq[i]);
			//CCLOG("i=%d ,  index=%d  , box is  =%s ", i, _checkSeq[i], b==NULL ?" NULL" : " OBJECT");
			if (b && b->collisionRect().containsPoint(location)){
				_state = GAME_READY;
				_isClickBox = true;
				b->setSelected(true);

				//播放动画
				if (b->getState() == BOXSTATE::BOX_EMPTY){
					b->playOpenWrongAnimation();
				}
				else {
					b->playOpenAnimation();
				}

				if (b->getState() == BOXSTATE::BOX_CAT){
					_isFindingCat = true;


					MiniGTools::playEffect(EFFECT_CATMIAO);


					int _round = MIN(_roundCount - 1-1, _levelDataCounts - 1);
					FindCateData data = catLevelDatas[_round];

					//胜利获得两个金币
					for (int i = 0; i < data.coin; i++){

						Sprite *coin = Sprite::create("Minigames/Common/ui_minigame_floor_stars.png");
							//Sprite::createWithSpriteFrameName("ani_cat_coin.png");
						coin->setPosition(b->getPosition());
						this->addChild(coin, 10);
						coin->setVisible(false);

						auto delay0 = DelayTime::create(0.5f);
						auto show = Show::create();
						auto soundCall = CallFunc::create([&](){
							MiniGTools::playEffect(EFFECT_COIN2);
						});

						float randomX = rand() % 100 - 50;
						float randomY = rand() % 60 - 30;
						float randomHeight = rand() % 60 - 30;
						auto jump = JumpBy::create(0.3f, Vec2(randomX, -100 + randomY), 100 + randomHeight, 1);
						auto delay1 = DelayTime::create(0.3f);

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
						auto seq = Sequence::create(delay0, show, soundCall, jump, delay1, spawn, call, remove, NULL);

						coin->runAction(seq);
					}
				}
				else {
					MiniGTools::playEffect(EFFECT_JUNK);
				}
				break;
			}
		}

		//点中箱子就判断失败和胜利，没有点中箱子，继续点
		if (_isClickBox){
			//没有找到箱子，其他的箱子要延迟显示一下。找到了正确的，其他箱子不用显示，所以不用做处理
			if (!_isFindingCat){
				for (int i = 0; i < _arrs->count(); i++){
					Box *b = (Box*)_arrs->getObjectAtIndex(i);
					if (!b->getSelected()){
						b->playOpenAnimation(0.5);

					}
				}
			}
			_state = GAME_READY;

			//找到了，延迟2s继续开始。找错了，延迟2s显示gameover
			auto delay = DelayTime::create(2.0f);
			auto call = CallFunc::create([&](){
				if (_isFindingCat){
					createBoxWave();
				}
				else { 
					showGameOverPanel();
				}
			});

			auto seq = Sequence::createWithTwoActions(delay, call);
			runAction(seq);
		}
	}
	return true;
}

void  MiniFindCatScene::refresh()
{
	_labRound->setString(IntToChar(_roundCount));
	_labCoin->setString(IntToChar(_scores));
}

void MiniFindCatScene::startGame()
{
	//初始化变量
	_cutdownCount = 0;
	_roundCount = 1;
	_scores = 0;
	_state = GAME_READY;
	refresh();

	{
		//给动画背景增加两个箱子，好看一点
		Layer *layer = Layer::create();
		addChild(layer, 9, 1000);

		Box *box = Box::create("FindCatAni", BOXSTATE::BOX_EMPTY);
		box->setPosition(Point(SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.4));
		layer->addChild(box);
		Box *box2 = Box::create("FindCatAni", BOXSTATE::BOX_EMPTY);
		box2->setPosition(Point(SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.4));
		layer->addChild(box2);
	}

	//开场动画
	auto call = CallFunc::create([&](){

		Sprite *num = NULL;
		if (_cutdownCount == 0){
			num = Sprite::create("Minigames/Common/countdown_03.png");
			MiniGTools::playEffect(EFFECT_321);
			MiniGTools::playBgMusic(EFFECT_CAT_BG, true);
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
			this->removeChildByTag(1000); 
			createBoxWave();
		}
	});
	auto seq = Sequence::create(call, delayTime, call1, NULL);
	auto rep = Repeat::create(seq, 4);
	runAction(rep);


	//createBoxWave();
}

void MiniFindCatScene::createBoxWave()
{
	//this->removeChildByTag(1000);


	CCLOG("=====FindCatGame::createBoxWave=====");
 
	//删除箱子
	if (_arrs->count()>0)
	{
		for (int i = _arrs->count() - 1; i >= 0; i--){
			Box *box = (Box*)_arrs->getObjectAtIndex(i);
			if (box->getParent()){
				box->removeFromParent();
				_arrs->removeObject(box);
			}
		}
	}
	_arrs->removeAllObjects();


	//当波数超过预定数量后，无限循环
	int _round = MIN(_roundCount - 1, _levelDataCounts - 1);
	FindCateData data = catLevelDatas[_round];

	_BOX_MAX = data.maxBoxs;
	_BOX_SWAP_INTERVAL = data.interval;
	_BOX_SWAP_COUNT = data.moveCount;;

	//初始化坐标
	if (_BOX_MAX == 2){
		_points[0] = Point(SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.4);
		_points[1] = Point(SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.4);
		_boxLayer->runAction(ScaleTo::create(0.2f, 1.0f));
	}
	else if (_BOX_MAX == 3){
		_points[0] = Point(SCREEN_WIDTH*0.25, SCREEN_HEIGHT*0.2);
		_points[1] = Point(SCREEN_WIDTH*0.75, SCREEN_HEIGHT*0.2);
		_points[2] = Point(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.6);
		_boxLayer->runAction(ScaleTo::create(0.2f, 0.9f));
	}
	else if (_BOX_MAX == 4){
		_points[0] = Point(SCREEN_WIDTH*0.2, SCREEN_HEIGHT*0.2);
		_points[1] = Point(SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.2);
		_points[2] = Point(SCREEN_WIDTH*0.2, SCREEN_HEIGHT*0.6);
		_points[3] = Point(SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.6);
		_boxLayer->runAction(ScaleTo::create(0.2f, 0.8f));
	}

	int _randmoCat = rand() % _BOX_MAX;
	_firstBoxIndex = _randmoCat;
	for (int i = 0; i < _BOX_MAX; i++){
		BOXSTATE state = _randmoCat == i ? BOXSTATE::BOX_CAT : BOXSTATE::BOX_EMPTY;

		Box *box = Box::create("FindCatAni", state);
		box->setPosition(_points[i]);
		box->setTarget(i);
		_boxLayer->addChild(box, BOX_LAYER_Z); 
		box->setLocalZOrder(_zOrers[i]);
		_arrs->addObject(box);

	}

	//修改状态，touch要失效
	_state = GAME_READY;
	_isFindingCat = false;
	_cSwapeCount = 0;

	FINDCAT_ANI_OPENCATBOX;
	//播放动画,这里分开处理，可以便于中间加入出场动画
	for (int i = 0; i < _arrs->count(); i++){
		Box *box = (Box*)_arrs->getObjectAtIndex(i);
		box->playInitAnimation(); 
	}

	 
	//延迟2s开始交换动作
	auto delay = DelayTime::create(2.0f);
	auto call = CallFunc::create(
		[&](){
		randomSwapeBox();
	});
	auto seq = Sequence::create(delay, call, NULL);
	runAction(seq);

	_roundCount++;
}

void MiniFindCatScene::randomSwapeBox()
{

	//计算新的box交换
	int _target1 = rand() % _BOX_MAX;
	if (_cSwapeCount == 0){
		_target1 = _firstBoxIndex; //保证每次生成对象，有猫的盒子先交换一次。防止随机后没有Cat交换的情况出现。
	}

	int _target2 = _target1;
	while (_target2 == _target1){
		_target2 = rand() % _BOX_MAX;
	}

	Box *box1 = getBoxByIndex(_target1);
	Box *box2 = getBoxByIndex(_target2);

	//确保box放到正确位置上
	if (box1->getNumberOfRunningActions()>0){
		box1->stopAllActions();
		box1->setPosition(_points[box1->getTarget()]);
		box1->setLocalZOrder(_zOrers[box1->getTarget()]);

	}
	if (box2->getNumberOfRunningActions()>0){
		box2->stopAllActions();
		box2->setPosition(_points[box2->getTarget()]);
		box2->setLocalZOrder(_zOrers[box2->getTarget()]);
	}

	if (box1 && box2){

		_cSwapeCount++;

		box1->setTarget(_target2);
		box2->setTarget(_target1);

		auto  move1 = MoveTo::create(_BOX_SWAP_INTERVAL, _points[_target2]);
		auto  call1 = CallFunc::create(
			[&](){
			/*box1->setLocalZOrder(_zOrers[box1->getTarget()]);*/
		});
		auto seq1 = Sequence::createWithTwoActions(move1, call1);
		box1->runAction(seq1);
		box1->setLocalZOrder(_zOrers[box1->getTarget()]);


		auto move2 = MoveTo::create(_BOX_SWAP_INTERVAL, _points[_target1]);
		auto call2 = CallFunc::create(
			[&](){
			/*box2->setLocalZOrder(_zOrers[box2->getTarget()]);*/
		});
		auto seq2 = Sequence::createWithTwoActions(move2, call2);
		box2->runAction(seq2);
		box2->setLocalZOrder(_zOrers[box2->getTarget()]);


		auto delay = DelayTime::create(_BOX_SWAP_INTERVAL);
		auto call = CallFunc::create(
			[&](){
			CCLOG("_cSwapeCount=%d  ,_BOX_SWAP_COUNT=%d  ", _cSwapeCount, _BOX_SWAP_COUNT);
			if (_cSwapeCount >= _BOX_SWAP_COUNT){
				CCLOG("swape finished");
				_state = GAME_RUN;

				for (int i = 0; i < _arrs->count(); i++){
					Box *box = (Box*)_arrs->getObjectAtIndex(i);
					auto scale1 = ScaleTo::create(0.2f, 1.1f);
					auto scale2 = ScaleTo::create(0.2f, 1.0f);
					auto seq = Sequence::create(scale1, scale2, NULL);
					box->runAction(seq);
				}
			}
			else {
				randomSwapeBox();
			}
		});
		auto seq = Sequence::create(delay, call, NULL);
		runAction(seq);

	}
	else {
		CCLOG("error ，target is null");
	}
}

Box *MiniFindCatScene::getBoxByIndex(int index)
{
	Box *box = NULL;
	for (int i = 0; i < _arrs->count(); i++)
	{
		Box *b = (Box*)_arrs->getObjectAtIndex(i);
		if (b->getTarget() == index){
			box = b;
			break;
		}
	}
	return box;
}


void MiniFindCatScene::restartGame()
{
	MiniBaseLayer::restartGame();
	Director::getInstance()->replaceScene(MiniFindCatScene::createScene());
}

void MiniFindCatScene::pauseMiniGame()
{
	MiniBaseLayer::pauseMiniGame();
}

void MiniFindCatScene::resumeMiniGame()
{
	MiniBaseLayer::resumeMiniGame();
}



//
//void MiniFindCatScene::showGameOver()
//{
//	if (_gameOverBoard){
//		_gameOverBoard->removeFromParent();
//		_gameOverBoard = NULL;
//	}
//
//	_gameOverBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json"); 
//
//	Widget *_btnQuit = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Quit");
//	_btnQuit->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::returnGame, this));
//	Widget *_btnRestart = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Button_Restart");
//	_btnRestart->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::restartGame, this));
//	Widget *_imgBoard = (Widget*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
//	_imgBoard->setPositionX(SCREEN_WIDTH / 2);
//
//	TextAtlas *_labGameOverTarget = (TextAtlas*)(Widget*)Helper::seekWidgetByName(_gameOverBoard, "Label_Target");
//	_labGameOverTarget->setString(__String::createWithFormat("%d", miniGameNames[FindCat_Index].game_target_score)->getCString());
//  
//	bool _bIsSuccess = false;
//	if (_coins>= miniGameNames[FindCat_Index].game_target_score){
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
//		_btnQuit->setPositionX(_imgBoard->getContentSize().width/2);
//	}
//	else {
//		MiniGTools::playEffect(EFFECT_GAME_OVER);
//		_labelScore1->setVisible(false);
//		_labelScore2->setVisible(true);
//		_imgTitle1->setVisible(false);
//		_imgTitle2->setVisible(true);
//	}
//	_labelScore1->setString(__String::createWithFormat("%d", _coins)->getCString());
//	_labelScore2->setString(__String::createWithFormat("%d", _coins)->getCString());
//	  
//
//	ImageView * bg = (ImageView*)Helper::seekWidgetByName(_gameOverBoard, "Image_Dashboard");
//	if (MiniGTools::getInstance()->isNativeAdLoaded()) {		
//		bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT*0.5 + bg->getContentSize().height/2 )); 
//		MiniGTools::getInstance()->showNativeAd();
//	}
//	else {
//		bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
//	}
//
//	_state = GAME_OVER;  
//	_viewStatus =  View_Status_GameOver;
//	addChild(_gameOverBoard, 11);
//	playShowGameOverAnimation(_gameOverBoard);
//
//}
//
//void MiniFindCatScene::pauseGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		if (_isPauseGame)
//		{
//			return;
//		}
//		_isPauseGame = true;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//
//		if (_pauseBoard){
//			_pauseBoard->removeFromParent();
//			_pauseBoard = NULL;
//		}
//		_pauseBoard = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
//
//		Widget *_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Restart");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::restartGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Quit");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::quitGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Button_Close");
//		_widget->addTouchEventListener(CC_CALLBACK_2(MiniFindCatScene::resumeGame, this));
//		_widget = (Widget*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		_widget->setPositionX(SCREEN_WIDTH / 2);
//	 
//		//暂停
//		pauseMiniGame();
//
//		//if (MiniGTools::getInstance()->isPopAdLoaded()){
//		//	MiniGTools::getInstance()->showPopAd();
//		//}
//
//		ImageView * bg = (ImageView*)Helper::seekWidgetByName(_pauseBoard, "Image_Dashboard");
//		if (MiniGTools::getInstance()->isNativeAdLoaded()) { 
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + bg->getContentSize().height/2));
//			MiniGTools::getInstance()->showNativeAd();
//		}
//		else {
//			bg->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2));
//		}
//
//		//弹出窗口
//		addChild(_pauseBoard, 11); 
//	}
//}
//
//
//void MiniFindCatScene::resumeGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON); 
//		resumeMiniGame();
//		_pauseBoard->removeFromParent();
//		_pauseBoard = NULL;
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//void MiniFindCatScene::restartGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		/*if (_pauseBoard->getParent())
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
//		Director::getInstance()->replaceScene(MiniFindCatScene::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//
//void MiniFindCatScene::quitGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		_isPauseGame = false;
//		MiniGTools::playEffect(EFFECT_BUTTON);
//
//		MiniGTools::getInstance()->stopAllSound();
//
//		resumeMiniGame();
//		Director::getInstance()->replaceScene(MiniGame::createScene());
//
//		MiniGTools::getInstance()->hideNativeAd();
//	}
//}
//
//void MiniFindCatScene::returnGame(Ref* ref, Widget::TouchEventType type)
//{
//	if (type == Widget::TouchEventType::ENDED)
//	{
//		MiniGTools::playEffect(EFFECT_BUTTON);
//		/*Director::getInstance()->resume();*/
//		resumeMiniGame();
//
//		MiniGTools::stopBgMusic();
//		 
//		MiniGTools::getInstance()->hideNativeAd();
//
//		if (_coins >= miniGameNames[FindCat_Index].game_target_score){
//			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Success);
//		}
//		else {
//			Director::getInstance()->replaceScene(MiniGame::createScene());
//		}
//	}
//}
//
//
