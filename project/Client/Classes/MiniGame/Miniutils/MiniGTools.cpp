//
//  MiniGTools.m
//  CastleDefender
//
//  Created by infi on 12-12-25.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#include "MiniGTools.h"  

typedef struct _MusicEffect{
	string				 iosFile;
	string				 androidFile;
	int					 fileType;
} MusicEffect;


MusicEffect musicDatas[] = {
	{ "Minigames/Sound/catmiaomiao.mp3", "Minigames/Sound/catmiaomiao.ogg", 0 },
	{ "Minigames/Sound/coin1.mp3", "Minigames/Sound/coin1.ogg", 0 },
	{ "Minigames/Sound/coin2.mp3", "Minigames/Sound/coin2.ogg", 0 },
	{ "Minigames/Sound/decreasetime.mp3", "Minigames/Sound/decreasetime.ogg", 0 },
	{ "Minigames/Sound/increasetime.mp3", "Minigames/Sound/increasetime.ogg", 0 },
	{ "Minigames/Sound/escape.mp3", "Minigames/Sound/escape.ogg", 0 },
	{ "Minigames/Sound/hit1.mp3", "Minigames/Sound/hit1.ogg", 0 },
	{ "Minigames/Sound/hit2.mp3", "Minigames/Sound/hit2.ogg", 0 },
	{ "Minigames/Sound/hit3.mp3", "Minigames/Sound/hit3.ogg", 0 },
	{ "Minigames/Sound/hit4.mp3", "Minigames/Sound/hit4.ogg", 0 },
	{ "Minigames/Sound/hitmouse.mp3", "Minigames/Sound/hitmouse.ogg", 0 },
	{ "Minigames/Sound/rope.mp3", "Minigames/Sound/rope.ogg", 1 },
	{ "Minigames/Sound/button.mp3", "Minigames/Sound/button.ogg", 0 },
	{ "Minigames/Sound/321.mp3", "Minigames/Sound/321.ogg", 0 },
	{ "Minigames/Sound/go.mp3", "Minigames/Sound/go.ogg", 0 },
	{ "Minigames/Sound/damage.mp3", "Minigames/Sound/damage.ogg", 0 },
	{ "Minigames/Sound/junk.mp3", "Minigames/Sound/junk.ogg", 0 },
	{ "Minigames/Sound/catbg.mp3", "Minigames/Sound/catbg.ogg", 1 },
	{ "Minigames/Sound/fishbg.mp3", "Minigames/Sound/fishbg.ogg", 1 },
	{ "Minigames/Sound/mousebg.mp3", "Minigames/Sound/mousebg.ogg", 1 },
	{ "Minigames/Sound/gamewin.mp3", "Minigames/Sound/gamewin.ogg", 1 },
	{ "Minigames/Sound/gameover.mp3", "Minigames/Sound/gameover.ogg", 1 }, 
};
 
MiniGTools::MiniGTools()
 
{
	_isSoundEnabledCallback = nullptr;//是否开启声音
	_isNativeAdLoadedCallback = nullptr;//是否原生广告准备好
	_onShowNativeAdCallback = nullptr;//显示nativeAD
	_onHideNativeAdCallback = nullptr;//隐藏nativeAD
	_onShowLoadingNativeAdCallback = nullptr;//显示loading用nativeAd
	_isPopAdLoadedCallback = nullptr;// 是否已经插屏广告准备好

	_onShowPopAdLoad1Callback = nullptr;//显示位置1插屏
	_onShowPopAdLoad2Callback = nullptr;//显示位置2插屏 
	_onEndShowPopAd2 = nullptr;//位置2插屏结束回调

	_onShowPopAdLoadCallback = nullptr;//显示通用插屏
	_onHidePopAdLoadCallback = nullptr;//隐藏通用插屏

	_onShowBannerAdCallback = nullptr;//显示Banner
	_onHideBannerAdCallback = nullptr; //显示Banner

	_isRejectPopAndNativeCallback = nullptr;//是否原生与插屏 互斥
	_isShowRandomPopAvailableCallback = nullptr;//是否可以显示随机的插屏 
}
  

MiniGTools::~MiniGTools()
{

}

static MiniGTools *_tools = nullptr;

MiniGTools* MiniGTools::getInstance() {
	if (!_tools)
	{
		_tools = new (std::nothrow) MiniGTools(); 
	}
	return _tools;
}


string  MiniGTools::intToTime(int time) {
	//刷新时间
	int second = time % 60;

	std::string secondStr;
	std::stringstream secStr;
	secStr << second;
	if (second < 10) {
		secondStr = "0";
	}

	secondStr += secStr.str();

	int minuteCount = time / 60;
	int minute = minuteCount % 60;

	std::string minuteStr;
	std::stringstream minStr;
	minStr << minute;
	//if (minute < 10) {
	//	minuteStr = "0";
	//}
	minuteStr += minStr.str();

	std::string timeString;
	timeString += minuteStr;
	timeString += ":";
	timeString += secondStr;

	return timeString;
}

bool  MiniGTools::addAnimation(string filePrefix, string aniName, int aniNum)
{
	Animation *ani = NULL;
	Vector<SpriteFrame*> v;
	for (int i = 1; i < aniNum; i++){
		__String *fileName = __String::createWithFormat("%s%02d.png", filePrefix.c_str(), i);
		if (!SpriteFrameCache::getInstance()->spriteFrameByName(fileName->getCString())) {
			break;
		}
		v.pushBack(SpriteFrameCache::getInstance()->spriteFrameByName(fileName->getCString() ));
	}
	if (v.size()>0){
		ani = Animation::createWithSpriteFrames(v,0.1);
		if (ani){
			AnimationCache::getInstance()->addAnimation(ani, aniName.c_str());
		}
	}
	return  ani == NULL ? false : true;
}

void MiniGTools::removeAnimation(string aniName){
	if (AnimationCache::getInstance()->getAnimation(aniName.c_str())){
		AnimationCache::getInstance()->removeAnimationByName(aniName.c_str());
	}
}
 
int MiniGTools::playEffect(EFFECT_MUSIC key, bool loop)
{
	//if (!UserDefault::getInstance()->getBoolForKey("IS_SOUND_ON")){
	//	return 0;
	//}

	if (!MiniGTools::getInstance()->isSoundEnabled()){
		return 0;
	}

	MusicEffect data = musicDatas[key];
	int _soundID;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID  ) 
	_soundID= SimpleAudioEngine::getInstance()->playEffect(data.androidFile.c_str(),loop);
#else  
	_soundID = SimpleAudioEngine::getInstance()->playEffect(data.iosFile.c_str(), loop);
#endif
	log("GTools::playEffect SoundId=%d  , key=%d", _soundID, key);
	return _soundID;

}

void  MiniGTools::stopEffect(int soundID)
{
	SimpleAudioEngine::getInstance()->stopEffect(soundID);
}

void MiniGTools::playBgMusic(EFFECT_MUSIC key, bool loop)
{
	/*if (!UserDefault::getInstance()->getBoolForKey("IS_SOUND_ON")){
		return;
	}*/


	if (!MiniGTools::getInstance()->isSoundEnabled()){
		return  ;
	}

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	MusicEffect data = musicDatas[key];
 
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic(data.androidFile.c_str());
	SimpleAudioEngine::getInstance()->playBackgroundMusic(data.androidFile.c_str(), loop);
#else 
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic(data.iosFile.c_str());
	SimpleAudioEngine::getInstance()->playBackgroundMusic(data.iosFile.c_str() , loop);
#endif

}

void MiniGTools::stopBgMusic(bool releaseData)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(releaseData);
}

void MiniGTools::preloadAllEffect()
{
	 
	int _counts = sizeof(musicDatas) / sizeof(musicDatas[0]);

	for (int i = 0; i < _counts; i++){
		MusicEffect effect = musicDatas[i];
		if (effect.fileType == 0){
			//effect
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			SimpleAudioEngine::getInstance()->preloadEffect(effect.androidFile.c_str());
#else 
			SimpleAudioEngine::getInstance()->preloadEffect(effect.iosFile.c_str());
#endif
		}
		else{
			//music
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic(effect.androidFile.c_str());
#else 
			SimpleAudioEngine::getInstance()->preloadBackgroundMusic(effect.iosFile.c_str());
#endif			
		}
	}
}

void MiniGTools::unloadAllEffect()
{
	int _counts = sizeof(musicDatas) / sizeof(musicDatas[0]);
	for (int i = 0; i < _counts; i++){
		MusicEffect effect = musicDatas[i];
		if (effect.fileType == 0){
			//effect
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			SimpleAudioEngine::getInstance()->unloadEffect(effect.androidFile.c_str());
#else 
			SimpleAudioEngine::getInstance()->unloadEffect(effect.iosFile.c_str());
#endif
		}
	}
}

void	MiniGTools::stopAllSound()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
 

void MiniGTools::returnGameMainScene(int state)
{
	MiniGTools::getInstance()->stopAllSound();
	MiniGTools::getInstance()->hideBannerAd(); 
  
	{
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/FindCat/FindCatAni.plist");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("Minigames/FindCat/FindCatAni.json");

		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/Fishing/Fishing.plist");

		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Minigames/HitMouse/hitmouse.plist");
		ArmatureDataManager::getInstance()->removeArmatureFileInfo("Minigames/HitMouse/HitMouseAni.json");

		Director::getInstance()->getScheduler()->schedule([&](float dt){
			Director::getInstance()->getTextureCache()->removeUnusedTextures();
		}, this, 0.02f, 0, 0, false, "SCHEDULE_CLEAR");
	}

	if (game_result_callback_)
	{
		game_result_callback_(state);
		game_result_callback_ = nullptr;
	} 

	Director::getInstance()->popScene();
} 
 
bool MiniGTools::isSoundEnabled()
{ 
	if (_isSoundEnabledCallback == nullptr)
		return false;

	return _isSoundEnabledCallback();
}

bool MiniGTools::isNativeAdLoaded()
{  
	if (_isNativeAdLoadedCallback == nullptr)
		return false;

	return _isNativeAdLoadedCallback();
}
 
void MiniGTools::showNativeAd(Node *node,int type)
{
	if (_onShowNativeAdCallback != nullptr){
		Vec2 p = MiniGTools::getInstance()->toWorldPoint(node);
		log("p.x=%f,p.y=%f ",p.x , p.y );
		Rect rect = MiniGTools::getInstance()->toWorldRect(node);
 		_onShowNativeAdCallback(rect, type);
	}
}

void MiniGTools::showLoadingNativeAd()
{
	if (_onShowLoadingNativeAdCallback != nullptr){
		_onShowLoadingNativeAdCallback();
	}
}

void MiniGTools::hideNativeAd()
{
	if (_onHideNativeAdCallback != nullptr){
		_onHideNativeAdCallback();
	}
}

bool MiniGTools::isPopAdLoaded()
{
	if (_isPopAdLoadedCallback == nullptr){
		return false;
	}
	else {
		return _isPopAdLoadedCallback();
	}	
}

void MiniGTools::showPopAd(float delay)
{
	if (_onShowPopAdLoad1Callback != nullptr){
		_onShowPopAdLoad1Callback();
		Director::getInstance()->getScheduler()->schedule([this](float dt){
			if (_onShowPopAdLoad2Callback != nullptr){
				_onShowPopAdLoad2Callback();
			}
		}, this, delay, 0, 0, false, "SCHEDULE_CLEAR");
	}
}

void MiniGTools::showNormalPopAd()
{
	if (_onShowPopAdLoadCallback != nullptr){
		_onShowPopAdLoadCallback();
	}
} 
void MiniGTools::showPop1()
{
	if (_onShowPopAdLoad1Callback) {
		_onShowPopAdLoad1Callback();
	} 
}

void MiniGTools::showPop2()
{
	if (_onShowPopAdLoad2Callback) {
		_onShowPopAdLoad2Callback();
	} 
}
 

void MiniGTools::showPop2AndConfirm()
{
	if (_onShowPopAdLoad2Callback) {
		_onShowPopAdLoad2Callback();
	}
	if (_onEndShowPopAd2) {
		_onEndShowPopAd2();
	}
}

void MiniGTools::hidePopAd()
{
	if (_onHidePopAdLoadCallback != nullptr){
		_onHidePopAdLoadCallback();
	}
}

void MiniGTools::showBannerAd()
{
	if (_onShowBannerAdCallback != nullptr){
		_onShowBannerAdCallback();
	}
}
void MiniGTools::hideBannerAd()
{
	if (_onHideBannerAdCallback != nullptr){
		_onHideBannerAdCallback();
	}
}

 
bool MiniGTools::isRejectPopAndNative()
{
	if (_isRejectPopAndNativeCallback != nullptr){
		return _isRejectPopAndNativeCallback();
	}
	else{
		return false;
	}
}

bool MiniGTools::isShowRandomPopAvailable()
{
	if (_isShowRandomPopAvailableCallback != nullptr){
		return _isShowRandomPopAvailableCallback();
	}
	else{
		return false;
	} 
}
 
void MiniGTools::delayEnableWidget(Widget *widget)
{
	widget->setEnabled(false);
	//延迟事件响应下一次操作
	auto delay = DelayTime::create(0.5f);
	auto call = CallFunc::create([this, widget] {
		widget->setEnabled(true);
	});
	widget->runAction(Sequence::create(delay, call, NULL));
}

Rect MiniGTools::toWorldRect(Node* node)
{
	Rect rect = node->getBoundingBox();
	rect.origin = node->getParent()->convertToWorldSpace(rect.origin);
	return rect;
}

Point MiniGTools::toWorldPoint(Node* node)
{
	return node->getParent()->convertToWorldSpace(node->getPosition());
}

void MiniGTools::SetResultCallback(const std::function<void(int)>& func)
{
	game_result_callback_ = func;
}