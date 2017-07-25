//
//  MiniGTools.h
//  CastleDefender
//
//  Created by infi on 12-12-25.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef __MINI_G_TOOLS_H__
#define __MINI_G_TOOLS_H__

#include "cocos2d.h" 
#include "../MiniGamePublic.h"
#include "SimpleAudioEngine.h"
 

class CMiniGTools;
  

#define SCREEN_WIDTH  (Director::getInstance()->getWinSize().width)
#define SCREEN_HEIGHT (Director::getInstance()->getWinSize().height)
#define SCREEN_SIZE   (Director::getInstance()->getWinSize())
#define VISIBLE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define ORIGIN_X       (Director::getInstance()->getVisibleOrigin().x)
#define ORIGIN_Y       (Director::getInstance()->getVisibleOrigin().y)
 
 
//快捷方法

#define SPRITE_SIZE(sprite)  (sprite->getContentSize())
#define CCP_SCREEN(x, y)  Point(SCREEN_WIDTH * x  , SCREEN_HEIGHT *  y  )
#define CCP_VISIBLE(x, y) Point(VISIBLE_WIDTH * x  , VISIBLE_HEIGHT *  y  )
#define CCP_SPRITE(x, y, sprite) Point(sprite->getContentSize().width * x , sprite->getContentSize().height * y )
#define SIZE_SPRITE(x,y,sprite)   Size( sprite->getContentSize().width*x  ,   sprite->getContentSize().height*y  )
#define G_CCP_SPRITETOWORLD( x, y,sprite) ( sprite->convertToWorldSpace( ccp(x,y)  ) )
 


#define FrameSprite(frame)  ( Sprite::createWithSpriteFrameName(frame) )
#define SpriteFile(file)  ( Sprite::create(file) )

#define IntToChar(val)  (__String::createWithFormat("%d", val )->getCString() )

enum EFFECT_MUSIC{
	EFFECT_CATMIAO,
	EFFECT_COIN1,
	EFFECT_COIN2,
	EFFECT_DECREASETIME,
	EFFECT_INCREASETIME,
	EFFECT_ESCAPE,
	EFFECT_HIT1,
	EFFECT_HIT2,
	EFFECT_HIT3,
	EFFECT_HIT4,
	EFFECT_HITMOUSE,
	EFFECT_ROPE,
	EFFECT_BUTTON,
	EFFECT_321,
	EFFECT_GO,
	EFFECT_DAMAGE,
	EFFECT_JUNK,
	EFFECT_CAT_BG,
	EFFECT_FISH_BG,
	EFFECT_MOUSE_BG,
	EFFECT_GAME_WIN,
	EFFECT_GAME_OVER,
};

 
class MiniGTools  
{
	MiniGTools();
	~MiniGTools();
public:
	static MiniGTools* getInstance();
	static void purgeInstance(); 
public: 

	typedef std::function<bool()> ccAvailableCallback;
	typedef std::function<void()> ccGameControlCallback;
	typedef std::function<void(Rect rect,int type)> ccNativeAdShowCallback;

	ccAvailableCallback		 _isSoundEnabledCallback;//是否开启声音
	ccAvailableCallback		 _isNativeAdLoadedCallback;//是否原生广告准备好
	ccNativeAdShowCallback	 _onShowNativeAdCallback;//显示nativeAD
	ccGameControlCallback	 _onHideNativeAdCallback;//隐藏nativeAD
	ccGameControlCallback	 _onShowLoadingNativeAdCallback;//显示loading用nativeAd
	ccAvailableCallback		 _isPopAdLoadedCallback;// 是否已经插屏广告准备好

	ccGameControlCallback	 _onShowPopAdLoad1Callback;//显示位置1插屏
	ccGameControlCallback	 _onShowPopAdLoad2Callback;//显示位置2插屏 
	ccGameControlCallback    _onEndShowPopAd2; //位置2插屏结束回调

	ccGameControlCallback	 _onShowPopAdLoadCallback;//显示通用插屏
	ccGameControlCallback	 _onHidePopAdLoadCallback;//隐藏通用插屏

	ccGameControlCallback	 _onShowBannerAdCallback;//显示Banner
	ccGameControlCallback	 _onHideBannerAdCallback; //显示Banner

	ccAvailableCallback		_isRejectPopAndNativeCallback;//是否原生与插屏 互斥
	ccAvailableCallback		_isShowRandomPopAvailableCallback;//是否可以显示随机的插屏 

public:
	static string	 intToTime(int time);
	static bool		 addAnimation(string filePrefix, string aniName, int aniNum = 99);
	static void      removeAnimation(string aniName);
	static int		 playEffect(EFFECT_MUSIC key, bool loop=false); 
	static void		 stopEffect(int soundID);
	static void		 playBgMusic(EFFECT_MUSIC key, bool loop=false);
	static void		 stopBgMusic(bool releaseData = false);
	static void		 preloadAllEffect();
	static void		 unloadAllEffect();
	static void		 stopAllSound(); 
	void returnGameMainScene(int state);
	 
	bool isSoundEnabled();
	bool isNativeAdLoaded();
	void showNativeAd(Node *node,int type);
	void showLoadingNativeAd();
	void hideNativeAd();

	bool isPopAdLoaded();
	void showPopAd(float delay);

	//正常插屏
	void showNormalPopAd();
	//插屏位置1
	void showPop1();
	//插屏位置2
	void showPop2();
 
	//插屏位置2并且通知客户端
	void showPop2AndConfirm();
	//隐藏插屏
	void hidePopAd();

	void showBannerAd();
	void hideBannerAd();
	 
	//插屏与原生是否互斥
	bool isRejectPopAndNative();//
	bool isShowRandomPopAvailable(); 
	 
	void delayEnableWidget(Widget *widget);

	Rect toWorldRect(Node*  node);
	Point toWorldPoint(Node* node);

	void SetResultCallback(const std::function<void(int)>& func);
private: 
	std::function<void(int)> game_result_callback_;
};


#endif

