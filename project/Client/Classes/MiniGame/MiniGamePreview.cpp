#include "MiniGamePreview.h"
#include "Miniutils/MiniGTools.h"
#include "MiniGame.h"
#include "MiniLoadingLayer.h"
#include "MiniFindCat/MiniFindCatScene.h"
#include "MiniFishing/MiniFishingScene.h"
#include "MiniHitMouse/MiniHitMouseScene.h"

MiniGamePreview::MiniGamePreview()
{
	_gameIndex = 0;
}


MiniGamePreview::~MiniGamePreview()
{
}


Scene* MiniGamePreview::createScene( int  index)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniGamePreview::create();
	layer->setGameIndex(index);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MiniGamePreview::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	 
	return true;
}

void MiniGamePreview::onEnter()
{
	Layer::onEnter();
	createUI();
	setKeyboardEnabled(true);
}

void MiniGamePreview::onExit()
{
	Layer::onExit();
	setKeyboardEnabled(false);
}


void MiniGamePreview::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)  //返回
	{ 
		setKeyboardEnabled(false);
		Director::getInstance()->replaceScene(MiniGame::createScene());
	}
#endif
}

void MiniGamePreview::createUI()
{
	//载入plist
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_UI_Select.json"); 
	addChild(bg);

	//根据屏幕重新定位控件
	//顶部控件
	Widget * _widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bg");
	_widget->setAnchorPoint(Point::ZERO);
	_widget->setPosition(Point::ZERO);
	_widget->setScale(SCREEN_WIDTH / _widget->getContentSize().width, SCREEN_HEIGHT / _widget->getContentSize().height);

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Top");
	_widget->setPositionY(SCREEN_HEIGHT - _widget->getContentSize().height);

	float _barHeight = ((ImageView*)_widget)->getCustomSize().height;

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Button_Start");
	_widget->setPositionX(SCREEN_WIDTH - _widget->getContentSize().width / 2 - 10);
	_widget->addTouchEventListener(CC_CALLBACK_2(MiniGamePreview::onStartGameClick, this));

	//Image_Bar
	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bar");
	_widget->setPosition(Point(0, SCREEN_HEIGHT - _widget->getContentSize().height  ));
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width);
	 
	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Preview");
	_widget->setPositionX(SCREEN_WIDTH / 2 );
	_widget->setPositionY(SCREEN_HEIGHT/2 - _barHeight/2);

	//游戏预览
	string preview = miniGameNames[_gameIndex].game_preview;
	ImageView *_icon = (ImageView*)Helper::seekWidgetByName(bg, "Image_Game");
	_icon->loadTexture(preview.c_str());

	//游戏标题
	ImageView *_title = (ImageView*)Helper::seekWidgetByName(bg, "Image_Name_Title");

	string gameTitle = miniGameNames[_gameIndex].game_title;
	_title->loadTexture(gameTitle.c_str());
	 
}
 

void MiniGamePreview::onStartGameClick(Ref *pSender, ui::Widget::TouchEventType type){

	Button *btn = (Button*)pSender;
	if (type == Widget::TouchEventType::ENDED){
		MiniGTools::playEffect(EFFECT_BUTTON); 
		if (_gameIndex < miniGamesCount){
			GameController  target = miniGameNames[_gameIndex];
			/*auto layer = target.callback();*/

			Layer *layer = NULL;
			if (_gameIndex == MINI_GAME_HITMOUSE) {
				layer = MiniHitMouseScene::create();
			}
			else if (_gameIndex == MINI_GAME_FINDCAT) {
				layer = MiniFindCatScene::create();
			}
			else if (_gameIndex == MINI_GAME_FISHING) {
				layer = MiniFishingScene::create();
			}

			if (layer)
			{
				//预载入资源
				MiniGTools::preloadAllEffect();

				CCUserDefault::getInstance()->setBoolForKey(HAS_RUN_MINIGAME, true);

				//切换资源
				auto scene = Scene::create();
				scene->addChild(layer);
				Director::getInstance()->replaceScene(scene);
			}
		}

		//Director::getInstance()->replaceScene(MiniLoadingLayer::createScene(_gameIndex));

		//if ( _gameIndex < miniGamesCount){ 
		//	GameController  target = miniGameNames[_gameIndex];
		//	auto layer = target.callback();
		//	if (layer)
		//	{
		//		btn->setTouchEnabled(false);
		//		//预载入资源
		//		MiniGTools::preloadAllEffect();

		//		//切换资源
		//		auto scene = Scene::create();
		//		scene->addChild(layer);
		//		Director::getInstance()->replaceScene(scene);
		//	}
		//}
	}
}

