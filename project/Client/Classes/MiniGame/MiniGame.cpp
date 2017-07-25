#include "MiniGame.h"
//#include "HelloWorldScene.h"
#include "MiniGamePreview.h"
#include "Miniutils/MiniGTools.h"
#include "MiniLoadingLayer.h"


#define ITEMS_PER_ROW 3

MiniGame::MiniGame()
{
}


MiniGame::~MiniGame()
{
}


Scene* MiniGame::loadMiniGame(bool isInit)
{
	if (isInit) {
		CCUserDefault::getInstance()->setBoolForKey(HAS_RUN_MINIGAME, false);
		CCUserDefault::getInstance()->flush();
	}

	// return the scene
	return MiniLoadingLayer::createScene();
}

Scene* MiniGame::createScene()
{ 
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MiniGame::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	createUI();

	//------------------------广告设置--调用插屏------------------------
	MiniGTools::getInstance()->showNormalPopAd(); 
	MiniGTools::getInstance()->showBannerAd(); 
	return true;
}


void MiniGame::onEnter()
{
	Layer::onEnter();
	setKeyboardEnabled(true);
}

void MiniGame::onExit()
{
	Layer::onExit();
	setKeyboardEnabled(false);
}


void MiniGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)  //返回
	{
		setKeyboardEnabled(false);
		if (CCUserDefault::getInstance()->getBoolForKey(HAS_RUN_MINIGAME)) {
			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Fail);
		}
		else {
			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_NotPlay);
		}
		 
	}
#endif
}


void MiniGame::createUI()
{ 
	//载入plist
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_UI_List.json");  
	addChild(bg);
 

	//根据屏幕重新定位控件
	//顶部控件
	Widget * _widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bg");
	_widget->setAnchorPoint(Point::ZERO);
	_widget->setPosition(Point::ZERO);
	_widget->setScale(SCREEN_WIDTH / _widget->getContentSize().width, SCREEN_HEIGHT / _widget->getContentSize().height); 

	//金币框子
	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_CoinBg");
	_widget->setVisible(false);

	_labelCoin = (TextAtlas*)Helper::seekWidgetByName(bg, "Atlas_Coin"); 


	_widget = (Widget*)Helper::seekWidgetByName(bg, "Panel_Top");
	_widget->setPositionY(SCREEN_HEIGHT - _widget->getContentSize().height  );

	float _barHeight = ((ImageView*)_widget)->getCustomSize().height;

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Button_Close");
	_widget->setPositionX(SCREEN_WIDTH - _widget->getContentSize().width / 2 - 10);
	_widget->addTouchEventListener(CC_CALLBACK_2(MiniGame::onQuitMiniGameClick, this));

	_widget = (Widget*)Helper::seekWidgetByName(bg, "Img_Title");
	_widget->setPositionX(SCREEN_WIDTH / 2);

	//Image_Bar
	_widget = (Widget*)Helper::seekWidgetByName(bg, "Image_Bar");
	_widget->setPosition(Point(0, SCREEN_HEIGHT - _widget->getContentSize().height ));
	_widget->setScaleX(SCREEN_WIDTH / _widget->getContentSize().width );
	 
	_widget = (Widget*)Helper::seekWidgetByName(bg, "ListView_Items");
	_widget->setContentSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT - _barHeight));

	Layout *_row = (Layout*)Helper::seekWidgetByName(_widget, "Panel_Row");
	_row->retain();
	_widget->removeChild(_row);


	//动态创建list元素

	int rows = ceil(miniGamesCount / 2.0);
	for (int i = 0; i < ITEMS_PER_ROW; i++){
		Layout *_item = (Layout*)_row->clone();
		((ListView*)_widget)->pushBackCustomItem(_item);
		for (int j = 0; j < ITEMS_PER_ROW; j++)
		{
			__String *itemName = __String::createWithFormat("Item_%d", j + 1);
			ImageView *btn = (ImageView*)Helper::seekWidgetByName(_item, itemName->getCString()); 

			if ((i * ITEMS_PER_ROW + j) < miniGamesCount){ 
				string icon = miniGameNames[i*ITEMS_PER_ROW + j].game_icon;
				btn->loadTexture(icon.c_str()); 
				if (j == 0){
					btn->setPositionX( SCREEN_WIDTH*0.2  );
				}
				else  if (j == 1){
					btn->setPositionX(SCREEN_WIDTH*0.5);
				}
				else if (j == 2){
					btn->setPositionX(SCREEN_WIDTH*0.8);
				}

				btn->addTouchEventListener(CC_CALLBACK_2(MiniGame::onListItemClick, this));
				btn->setTag(i* ITEMS_PER_ROW + j);
			}
			else {
				_item->removeChild(btn);
			}
		} 
	}
	_row->release();	


}
 
void MiniGame::onListItemClick(Ref *pSender, ui::Widget::TouchEventType type){
 
	Button *btn = (Button*)pSender;
	switch (type)
	{
		case   Widget::TouchEventType::BEGAN: 
			btn->setScale(1.1f);
			break;
		case   Widget::TouchEventType::MOVED:
			btn->setScale(1.0f);
			onListItemClick(pSender, Widget::TouchEventType::CANCELED);
			return;
			break;
		case   Widget::TouchEventType::ENDED:
		{
			MiniGTools::playEffect(EFFECT_BUTTON);
			btn->setScale(1.0f);
			Director::getInstance()->replaceScene(MiniGamePreview::createScene(btn->getTag()));
		} 
			break;
		case   Widget::TouchEventType::CANCELED:
		{
			 btn->setScale(1.0f);
		}
			break; 
	}	 
}

 
void MiniGame::onQuitMiniGameClick(Ref *pSender, ui::Widget::TouchEventType type){  
	Widget *widget = (Widget*)pSender;
	if (type == Widget::TouchEventType::ENDED)
	{
		MiniGTools::playEffect(EFFECT_BUTTON);
		setKeyboardEnabled(false);
		 
		MiniGTools::getInstance()->delayEnableWidget(widget);

		if (CCUserDefault::getInstance()->getBoolForKey(HAS_RUN_MINIGAME)) {
			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_Fail);

			
		}
		else {
			MiniGTools::getInstance()->returnGameMainScene(MiniGame::MiniGameState::MiniGame_State_NotPlay);

		
		}

		 
	}
}


