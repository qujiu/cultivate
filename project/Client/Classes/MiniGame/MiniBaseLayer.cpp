#include "MiniBaseLayer.h"
#include "Miniutils/MiniGTools.h"
#include "MiniGame.h"
#include "../BabyCare.h"

MiniBaseLayer::MiniBaseLayer()
:_defaultMusicVolumn(1)
, _defaultEffectVolumn(1)
, _scores(0)
, _viewStatus(0)
, _currentGameIndex(MINI_GAME_HITMOUSE)
, _bIsCompleteTarget(false)
, _rootWidget(NULL)
, _pauseWidget(NULL)
, _gameOverWidget(NULL)
, _bIsPauseGame(false)
, _bIsPause(false)
, _arrs(NULL)
{
	_arrs = __Array::create();
	_arrs->retain();
}

MiniBaseLayer::~MiniBaseLayer()
{
	_arrs->removeAllObjects();
	_arrs->release();
}

void MiniBaseLayer::onEnter()
{
	Layer::onEnter();
	setKeyboardEnabled(true);
}

void MiniBaseLayer::onExit()
{
	Layer::onExit();
	setKeyboardEnabled(false);
}

void MiniBaseLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)  //返回
	{
		if (_viewStatus == View_Status_Game){
			showPausePanel();
		}
		else if (_viewStatus == View_Status_Pause){
			resumeGame();
		}
		else if (_viewStatus == View_Status_GameOver){
			quitGame();
		}
	}
#endif
}

void MiniBaseLayer::delayShowNode(Node *node, float delay, MINI_FORM_SHOW_SPEED speed){
	node->stopAllActions();
	node->setScale(0);
	float _duration = 0.1;
	if (speed == MINI_FAST){
		_duration = 0.05f;
	}
	else if (speed == MINI_MIDDLE){
		_duration = 0.1f;
	}
	else if (speed == MINI_SLOW){
		_duration = 0.15f;
	}

	auto delay1 = DelayTime::create(delay);
	auto scale1 = ScaleTo::create(_duration, 1.3f);
	auto scale2 = ScaleTo::create(_duration, 0.9f);
	auto scale3 = ScaleTo::create(_duration, 1.0f);

	auto seq = Sequence::create(delay1, scale1, scale2, scale3, NULL);
	node->runAction(seq);
}

//void MiniBaseLayer::showPopAd()
//{
//	MiniGTools::getInstance()->showPopAd(MINI_POP_DELAY);
//}

void MiniBaseLayer::pauseMiniGame()
{
	_bIsPause = true;
	_defaultMusicVolumn = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	_defaultEffectVolumn = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0);

	this->pauseSchedulerAndActions();
	for (int i = 0; i < _arrs->count(); i++){
		Node *node = (Node*)_arrs->getObjectAtIndex(i);
		node->pauseSchedulerAndActions();
	}

	_viewStatus = View_Status_Pause;
}

void MiniBaseLayer::resumeMiniGame()
{
	_bIsPause = false;

	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_defaultMusicVolumn);
	SimpleAudioEngine::getInstance()->setEffectsVolume(_defaultEffectVolumn);

	this->resumeSchedulerAndActions();
	for (int i = 0; i < _arrs->count(); i++){
		Node *node = (Node*)_arrs->getObjectAtIndex(i);
		node->resumeSchedulerAndActions();
	}

	_viewStatus = View_Status_Game;

	MiniGTools::getInstance()->hideNativeAd();
}

void MiniBaseLayer::showPausePanel(){
	pauseMiniGame();

	_bIsPauseGame = true;
	_viewStatus = View_Status_Pause;


	if (_pauseWidget){
		_pauseWidget->removeFromParent();
		_pauseWidget = NULL;
	}


	//-------------广告配置： 随机插屏， 判断是否可以显示插屏------------------------
	bool bIsReject = false, bIsShowPop = false, bIsShowNative = false;
	if (MiniGTools::getInstance()->isShowRandomPopAvailable()) {
		bIsReject = MiniGTools::getInstance()->isRejectPopAndNative();
		if (!bIsReject) {
			bIsShowPop = true;
			bIsShowNative = MiniGTools::getInstance()->isNativeAdLoaded();
		}
		else{
			bIsShowPop = true;
			bIsShowNative = false;
		}
	} 
	else {
		bIsShowPop = false;
		bIsShowNative = MiniGTools::getInstance()->isNativeAdLoaded();;
	}
	 
	//------------------------------------------------------------------------

	_pauseWidget = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_Pause.json");
	Widget *center = (Widget*)Helper::seekWidgetByName(_pauseWidget, "Img_Center");
	center->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	Layout *content = (Layout*)Helper::seekWidgetByName(_pauseWidget, "Panel_Board");
	content->setCascadeOpacityEnabled(false);
	Layout *top = (Layout*)Helper::seekWidgetByName(content, "Panel_Board_Top");
	Layout *bottom = (Layout*)Helper::seekWidgetByName(content, "Panel_Board_Bottom");


	
	
	{
		/*content->setBackGroundColorOpacity(100);
		top->setBackGroundColorOpacity(50);
		bottom->setBackGroundColorOpacity(50);*/

		Vec2 p1 = content->getPosition();
		Vec2 p2 = MiniGTools::getInstance()->toWorldPoint(content);
		log("=========== GameOver =============p1.x=%f  ,p1.y=%f  ,p2.x=%f ,p2.y=%f    ==================", p1.x, p1.y, p2.x, p2.y);
	}

	log("===========   bIsShowNative=%d ,  bIsShowNative=%d   ,  ==================", bIsShowPop, bIsShowNative);

	if (bIsShowNative){
		top->setPositionY(content->getContentSize().height);
		bottom->setPositionY(-bottom->getContentSize().height);
	}

	Widget *imgTitle = (Widget*)Helper::seekWidgetByName(content, "Img_Title");
	Button *btnRestart = (Button*)Helper::seekWidgetByName(content, "Button_Restart");
	btnRestart->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			restartGame();
		}
	});
	Button *btnQuit = (Button*)Helper::seekWidgetByName(content, "Button_Quit");
	btnQuit->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			quitGame();
		}
	});
	log("btnQuitx%f,btnQuity%f", btnQuit->getPositionX(), btnQuit->getPositionY());
	Button *btnResume = (Button*)Helper::seekWidgetByName(content, "Button_Close");
	btnResume->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			resumeGame();
		}
	});

	btnResume->setPosition(btnResume->getParent()->convertToNodeSpace(_pauseButtonPos));

	if (bIsShowPop) {
		//显示位置1插屏
		MiniGTools::getInstance()->showPop1();
	}

	delayShowNode(imgTitle, 0.2f);
	delayShowNode(btnRestart, 0.6f);
	delayShowNode(btnQuit, 0.6f);
	delayShowNode(btnResume, 0.8f);

	Director::getInstance()->getRunningScene()->addChild(_pauseWidget);

	auto delay = DelayTime::create(0.5f);
	auto call = CallFuncN::create([this, bIsShowPop, bIsShowNative](Ref *ref){
		Widget *widget = (Widget*)ref; 

		if (bIsShowNative){
			//是否显示原生
			MiniGTools::getInstance()->showNativeAd(widget,1);
		}
		if (bIsShowPop) {
			//显示位置2插屏
			MiniGTools::getInstance()->showPop2AndConfirm();
		}
	});
	auto seq = Sequence::create(delay, call, NULL);
	content->runAction(seq);

}


void MiniBaseLayer::showGameOverPanel(){

	if (_gameOverWidget){
		_gameOverWidget->removeFromParent();
		_gameOverWidget = NULL;
	}

	_state = GAME_OVER;
	_viewStatus = View_Status_GameOver;

	refresh();


	//-------------广告配置：  判断是否显示原生与插屏------------------------
	bool bIsReject = false, bIsShowPop = false, bIsShowNative = false;
	bIsReject = MiniGTools::getInstance()->isRejectPopAndNative();
	if (!bIsReject) {
		bIsShowPop = true;
		bIsShowNative = MiniGTools::getInstance()->isNativeAdLoaded();
	}
	else{
		bIsShowPop = true;
		bIsShowNative = false;
	}
	//------------------------------------------------------------------------

	_gameOverWidget = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_Game_GameOver.json");
	Widget *center = (Widget*)Helper::seekWidgetByName(_gameOverWidget, "Img_Center");
	center->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	Layout *content = (Layout*)Helper::seekWidgetByName(_gameOverWidget, "Panel_Board");
	content->setCascadeOpacityEnabled(false);
	Layout *top = (Layout*)Helper::seekWidgetByName(content, "Panel_Board_Top");
	Layout *bottom = (Layout*)Helper::seekWidgetByName(content, "Panel_Board_Bottom");

	{
		/*content->setBackGroundColorOpacity(100);
		top->setBackGroundColorOpacity(50);
		bottom->setBackGroundColorOpacity(50);*/

		Vec2 p1 = content->getPosition();
		Vec2 p2 = MiniGTools::getInstance()->toWorldPoint(content);
		log("=========== GameOver =============p1.x=%f  ,p1.y=%f  ,p2.x=%f ,p2.y=%f    ==================", p1.x,p1.y,p2.x,p2.y);
	}

	log("===========   bIsShowPop=%d ,  bIsShowNative=%d   ,  ==================", bIsShowPop, bIsShowNative);


	if (bIsShowNative){
		top->setPositionY(content->getContentSize().height);
		bottom->setPositionY(-bottom->getContentSize().height);
	}

	//是否完成目标任务
	bool _bIsSuccess = false;
	if (_scores >= miniGameNames[_currentGameIndex].game_target_score){
		_bIsSuccess = true;
	}

	if (_bIsSuccess){
		MiniGTools::playEffect(EFFECT_GAME_WIN);
	}
	else {
		MiniGTools::playEffect(EFFECT_GAME_OVER);
	}
	 
	Widget *imgTitle = NULL;
	Widget *imgTitleSuccess = (Widget*)Helper::seekWidgetByName(content, "Img_Success_Title");
	Widget *imgTitleFailure = (Widget*)Helper::seekWidgetByName(content, "Img_Fail_Title");
	if (_bIsSuccess){
		imgTitle = imgTitleSuccess;
		imgTitleSuccess->setVisible(true);
		imgTitleFailure->setVisible(false);
	}
	else {
		imgTitle = imgTitleFailure;
		imgTitleSuccess->setVisible(false);
		imgTitleFailure->setVisible(true);
	}

	Widget *imgBoardBg = (Widget*)Helper::seekWidgetByName(content, "Img_Board_Bg");
	Widget *widgetItem1 = (Widget*)Helper::seekWidgetByName(content, "Img_Bonus");
	TextAtlas *widgetItem2 = (TextAtlas*)Helper::seekWidgetByName(content, "Label_Ticket_1");
	TextAtlas *widgetItem3 = (TextAtlas*)Helper::seekWidgetByName(content, "Label_Ticket_2");
	Widget *widgetItem4 = (Widget*)Helper::seekWidgetByName(content, "Img_Target");
	TextAtlas *widgetItem5 = (TextAtlas*)Helper::seekWidgetByName(content, "Label_Ticket_3");

	widgetItem2->setString(IntToChar(_scores));
	widgetItem3->setString(IntToChar(_scores));
	widgetItem5->setString(IntToChar(miniGameNames[_currentGameIndex].game_target_score));

	Widget *widgetScore = NULL;
	if (_bIsSuccess){
		widgetScore = widgetItem2;
		widgetItem2->setVisible(true);
		widgetItem3->setVisible(false);
	}
	else {
		widgetScore = widgetItem3;
		widgetItem2->setVisible(false);
		widgetItem3->setVisible(true);
	}

	Button *btnRestart = (Button*)Helper::seekWidgetByName(content, "Button_Retry");
	btnRestart->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			restartGame();
		}
	});
	Button *btnQuit = (Button*)Helper::seekWidgetByName(content, "Button_Quit");
	btnQuit->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED){
			MiniGTools::playEffect(EFFECT_BUTTON);
			quitGame();
		}
	});
	log("QQQQbtnQuitx%f,btnQuity%f", btnQuit->getPositionX(), btnQuit->getPositionY());

	if (_bIsSuccess){
		btnRestart->setVisible(false);
		btnQuit->setPositionX(content->getContentSize().width / 2);
	}

	if (bIsShowPop) {
		//显示位置1插屏
		MiniGTools::getInstance()->showPop1();
	}

	delayShowNode(imgTitle, 0.2f);
	delayShowNode(imgBoardBg, 0.2f);
	delayShowNode(widgetItem1, 0.6f);
	delayShowNode(widgetScore, 0.7f);
	delayShowNode(widgetItem4, 0.8f);
	delayShowNode(widgetItem5, 0.9f);
	delayShowNode(btnRestart, 1.0f);
	delayShowNode(btnQuit, 1.0f);

	Director::getInstance()->getRunningScene()->addChild(_gameOverWidget);
	 
	auto delay = DelayTime::create(0.5f);
	auto call = CallFuncN::create([this, bIsShowPop,bIsShowNative](Ref *ref){
		Widget *widget = (Widget*)ref;
		Vec2 p = MiniGTools::getInstance()->toWorldPoint(widget);

		if (bIsShowNative){
			//是否显示原生
			MiniGTools::getInstance()->showNativeAd(widget,0);
		} 
		if (bIsShowPop) {
			//显示位置2插屏
			MiniGTools::getInstance()->showPop2();
		}		
	});
	auto seq = Sequence::create(delay, call, NULL);
	content->runAction(seq);
}

void MiniBaseLayer::resumeGame(){
	resumeMiniGame();
	_pauseWidget->removeFromParent();
	_pauseWidget = NULL;
}


void MiniBaseLayer::restartGame(){
	if (_bIsPause) {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_defaultMusicVolumn);
		SimpleAudioEngine::getInstance()->setEffectsVolume(_defaultEffectVolumn);
	}
	MiniGTools::getInstance()->hideNativeAd();
}

void MiniBaseLayer::quitGame(){
	if (_bIsPause) {
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_defaultMusicVolumn);
		SimpleAudioEngine::getInstance()->setEffectsVolume(_defaultEffectVolumn);
	}
	MiniGTools::getInstance()->hideNativeAd();

	setKeyboardEnabled(false);

	if (_scores >= miniGameNames[_currentGameIndex].game_target_score) {
		MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Success);

		
	}
	else {
		Director::getInstance()->replaceScene(MiniGame::loadMiniGame());
	}
}

void MiniBaseLayer::refresh()
{

}

