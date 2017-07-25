#include "MiniLoadingLayer.h"
//#include "HelloWorldScene.h"
#include "MiniGamePreview.h"
#include "Miniutils/MiniGTools.h"
#include "MiniGame.h"

#define LOADING_TIME 3

MiniLoadingLayer::MiniLoadingLayer()
:_count(0)
{
}


MiniLoadingLayer::~MiniLoadingLayer()
{
}


Scene* MiniLoadingLayer::createScene( )
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MiniLoadingLayer::create(); 
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
 
// on "init" you need to initialize your instance
bool MiniLoadingLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void MiniLoadingLayer::onEnter()
{
	Layer::onEnter();
	createUI(); 
}

void MiniLoadingLayer::onExit()
{
	Layer::onExit(); 
	_vecDots.clear();
}

void MiniLoadingLayer::createUI()
{ 
	//载入plist
	auto bg = GUIReader::getInstance()->widgetFromJsonFile("Minigames/Mini_UI_Loading.json");
	addChild(bg);

	ImageView *_imgBg = (ImageView*)Helper::seekWidgetByName(bg, "Image_Bg");
	_imgBg->setAnchorPoint(Point::ZERO);
	_imgBg->setPosition(Point::ZERO);
	_imgBg->setScale(SCREEN_WIDTH / _imgBg->getContentSize().width, SCREEN_HEIGHT / _imgBg->getContentSize().height); 
	 
	//游戏标题
	//------------------------广告设置--调用原生广告------------------------
	ImageView *_imgLogo = (ImageView*)Helper::seekWidgetByName(bg, "Image_Loading");
	if (MiniGTools::getInstance()->isNativeAdLoaded()){
		_imgLogo->setPosition(Point(SCREEN_WIDTH/2 ,SCREEN_HEIGHT/4 ));
		MiniGTools::getInstance()->showLoadingNativeAd();
	}
	else {
		_imgLogo->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));		
	}

	for (int i = 0; i < 3; i++){
		string name = __String::createWithFormat("Image_Loading_Dot%d", i + 1)->getCString();
		ImageView *_imgDot = (ImageView*)Helper::seekWidgetByName(bg, name.c_str());
		_vecDots.push_back(_imgDot);
		_imgDot->setVisible(false);
	}	
	 
	auto delay = DelayTime::create(LOADING_TIME);
	auto call = CallFunc::create(CC_CALLBACK_0(MiniLoadingLayer::onFinishLoadingCallbakc, this));
	auto seq = Sequence::create(delay, call, NULL);
	runAction(seq);
	 
	schedule(schedule_selector(MiniLoadingLayer::tick),0.2f); 
}

void MiniLoadingLayer::tick(float dt ){
	int  step = _count % 4;
	for (int i = 0; i < 3; i++){
		ImageView* imgDot = _vecDots[i];
		if (i <= (step - 1)){
			imgDot->setVisible(true);
		}
		else {
			imgDot->setVisible(false);
		}
	}
	_count++;
}

void MiniLoadingLayer::onFinishLoadingCallbakc( )
{
	unschedule(schedule_selector(MiniLoadingLayer::tick));
	MiniGTools::getInstance()->hideNativeAd();

	//切换资源
	Director::getInstance()->replaceScene(MiniGame::createScene());
 
}

