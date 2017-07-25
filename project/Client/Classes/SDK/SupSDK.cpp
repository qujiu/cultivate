#include "SupSDK.h"
#include "GameType.h"
#include "BabyCare.h"
#include "../GUI/Form/MessageBox.h"
#include "../GUI/Form/UILuckyForm.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#define __SUP_ANDROID__

#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Game7SDK.h"
#define __SUP_IOS__
#endif  //


SINGLETON_DEFINE_INST(SupSDK, Ref);

SupSDK::SupSDK()
{
	ResetPopAdLimit();

	pop_more_dot_time_ = 0;
	can_more_dot = false;

	pop_coins_dot_time_ = 0;
	can_coins_dot = false;
	can_Video_show = false;

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SupSDK::Tick), this, 1, false);

}

SupSDK::~SupSDK()
{
}

bool SupSDK::getVideoVisable()
{

#ifdef __SUP_ANDROID__ 
	//JniMethodInfo info;

	//bool isHaved = false;
	//isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getInstance", "()Lcom/dragon/partysalon/PartySalon;");
	//if(isHaved)
	//{
	//	jobject instance = info.env->CallStaticObjectMethod(info.classID, info.methodID); 
	//	
	//	jmethodID setAmount_method = info.env->GetMethodID(info.classID, "isVideoAvailable", "()Z");

	//	jboolean ret = info.env->CallBooleanMethod(instance, setAmount_method);
	//	isHaved = ret == JNI_TRUE;
	//} 
	//return isHaved;
	//
#endif
	return true;
}


void SupSDK::watchVideo()
{
#ifdef __SUP_ANDROID__ 
	//JniMethodInfo info;

	//bool isHaved = false;
	//isHaved = JniHelper::getStaticMethodInfo(info, "com/dragon/partysalon/PartySalon", "getInstance", "()Lcom/dragon/partysalon/PartySalon;");
	////LOG("watchVideo isHaved = %s", isHaved?"true":"false");
	//if(isHaved)
	//{
	//	jobject instance = info.env->CallStaticObjectMethod(info.classID, info.methodID); 
	//	
	//	jmethodID setAmount_method = info.env->GetMethodID(info.classID, "showVideoAd", "()V");

	//	info.env->CallVoidMethod(instance, setAmount_method);
	//	
	//}
	////LOG("watchVideo begin");
#endif
}

void SupSDK::More()
{
	SupSDK::instance()->ShowUmEvent(MORE_UM);

#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;
	CCLog("SupJni::share()");
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "More", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif

#ifdef __SUP_IOS__
	Game7SDK::showMoreApp();
#endif
}

void SupSDK::showBannerAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showBannerAD", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::hideBannerAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "hideBannerAD", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}


void SupSDK::share()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "share", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif

#ifdef __SUP_IOS__
	Game7SDK::shareByScreenShots("screenshot");//閫氳繃鎴睆鍒嗕韩
#endif
}

void SupSDK::comment()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "comment", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif

#ifdef __SUP_IOS__
	Game7SDK::showIRate();
#endif
}

void SupSDK::shareToEmail(char* file)
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "sendEmail", "(Ljava/lang/String;)V");

	if (isHaved)
	{
		jstring rtn = 0;
		rtn = (info.env)->NewStringUTF(file);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, rtn);
	}

#endif

#ifdef __SUP_IOS__

	NSString *subject = @"mailto:?&subject=Hello, this is my new photos !";

	NSString* imgPath = [[NSString alloc] initWithUTF8String:file];
	UIImage *image = [[UIImage alloc] initWithContentsOfFile:imgPath];
	NSData *imageData = [NSData dataWithData : UIImageJPEGRepresentation(image, 0.5)];
	NSString *imageBase64 = [imageData base64EncodedStringWithOptions : 0];
	NSString *body = [NSString stringWithFormat : @"&body=I like this app, now share with you,https://itunes.apple.com/us/app/fruits-break/id918063794?mt=8!<br><img src='data:image/png;base64,%@'>", imageBase64];

	NSString *email = [NSString stringWithFormat : @"%@%@", subject, body];
	email = [email stringByAddingPercentEscapesUsingEncoding : NSUTF8StringEncoding];

	[[UIApplication sharedApplication] openURL:[NSURL URLWithString : email]];
#endif

}

void SupSDK::shareToFacebook()
{
#ifdef __SUP_ANDROID__ 
	//JniMethodInfo info;

	//bool isHaved = false;
	//isHaved = JniHelper::getStaticMethodInfo(info, "com/dragon/partysalon/PartySalon", "shareToFacebook", "()V");
	//LOG("shareToFacebook isHaved = %s", isHaved?"true":"false");
	//if(isHaved)
	//{
	//	info.env->CallStaticVoidMethod(info.classID, info.methodID);
	//}
	//LOG("shareToFacebook isHaved = %s, end", isHaved?"true":"false");
#endif
}


std::string SupSDK::getCaptureImgPath()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getCaptureImgPath", "()Ljava/lang/String;");
	if (isHaved)
	{
		jstring jstr = (jstring)info.env->CallStaticObjectMethod(info.classID, info.methodID); //
		if (jstr != NULL){
			char*   rtn = NULL;
			jclass   clsstring = info.env->FindClass("java/lang/String");
			jstring   strencode = info.env->NewStringUTF("utf-8");
			jmethodID   mid = info.env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
			jbyteArray   barr = (jbyteArray)info.env->CallObjectMethod(jstr, mid, strencode);
			jsize   alen = info.env->GetArrayLength(barr);
			jbyte*   ba = info.env->GetByteArrayElements(barr, JNI_FALSE);
			if (alen > 0)
			{
				rtn = (char*)malloc(alen + 1);         //new   char[alen+1];  
				memcpy(rtn, ba, alen);
				rtn[alen] = 0;
			}
			info.env->ReleaseByteArrayElements(barr, ba, 0);
			std::string stemp(rtn);
			free(rtn);
			return stemp;
		}
	}
	return "";
#endif

#ifdef __SUP_IOS__
	std::string fileName = "dollsalon" + getcurrTime() + ".jpg";
	return FileUtils::getInstance()->getWritablePath() + fileName;
#endif
	const char* ss = "/Fashion Star Doll Salon.jpg";
	return ss;
}

void SupSDK::showFullAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showFullAD", "()V");
	//LOG("showFullAD isHaved = %s", isHaved?"true":"false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::showPopAD()
{

	pop_ad_limit_time_ = 0.0f;

#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showPopAD", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
	if (BabyCare::instance()->getCurrSceneID() != EScene_Select)
	{
		if (!HaveNativeAd())
		{
			SupSDK::showBannerAD();
		}
		else{
			SupSDK::hideBannerAD();
		}
	}
#ifdef __SUP_IOS__
	Game7SDK::showInterstitialAD();
#endif
}

void SupSDK::gamePause()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "gamePause", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::gameAgain()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "gameAgain", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::ExitAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;
	CCLog("PSDataLevel::ExitAD()");
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "ExitAD", "()V");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::FlushCapturePicture(char* file)
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "flushCameraEnviroment", "(Ljava/lang/String;)V");
	CCLog("FlushCapturePicture isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		jstring rtn = 0;
		rtn = (info.env)->NewStringUTF(file);
		info.env->CallStaticVoidMethod(info.classID, info.methodID, rtn);
	}
	CCLog("FlushCapturePicture isHaved = %s, end", isHaved ? "true" : "false");
#endif

#ifdef __SUP_IOS__
	//[(AppController*)[UIApplication sharedApplication].delegate screenShot:file];
	NSString* imgPath = [[NSString alloc] initWithUTF8String:file];
	UIImage *image = [[UIImage alloc] initWithContentsOfFile:imgPath];

	// 保存图片到相册, 这里会提示用户授权，不需要保存的话，可以取消
	UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);

	// 获取Documents目录
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex : 0];
	NSString *savedImagePath = [documentsDirectory stringByAppendingPathComponent : @"temScreenShot.png"];

	// 保存image到Documents目录
	NSData *imageData = UIImagePNGRepresentation(image);
	[imageData writeToFile : savedImagePath atomically : YES];
#endif
}

std::string SupSDK::getcurrTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	struct tm* time;
	gettimeofday(&now, NULL);
	time = localtime(&now.tv_sec);
	int year = time->tm_year + 1900;
	char date[32] = { 0 };
	sprintf(date, "%d%02d%02d%02d%02d%02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday, (int)time->tm_hour, (int)time->tm_min, (int)time->tm_sec);

	return StringUtils::format("%s", date);
#endif
	return NULL;
}

bool SupSDK::CanShowOptAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "canShowOptAD", "()Z");
	CCLog("---CanShowOptAD isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		return info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif
	return false;
}

void SupSDK::showOptAD(int x, int y, int w, int h)
{

	auto glview = Director::getInstance()->getOpenGLView();
	Size screenSize = glview->getFrameSize();
	Size winSzie = Director::getInstance()->getWinSize();

	float GAME_DESTINY_X = screenSize.width / winSzie.width;
	float GAME_DESTINY_Y = screenSize.height / winSzie.height;

#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;
	int newX = x * GAME_DESTINY_X;
	int newY = y *GAME_DESTINY_Y;
	int newW = w * GAME_DESTINY_X;
	int newH = h*GAME_DESTINY_Y;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showOptAD", "(IIII)V");
	CCLog("ShowOptAD isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID, newX, newY, newW, newH);

	}
#endif
}

void SupSDK::hideOptAD()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "hideOptAD", "()V");
	CCLog("HideOptAD isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::showParentsMail()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showParentsMail", "()V");
	CCLog("HideOptAD isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}
bool SupSDK::palywang(){

	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "palywang", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif 
	return result;
}

bool SupSDK::getgift(){

	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getlift", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif 
	return result;
}

bool  SupSDK::gettype(){

	int result = 0;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = 0;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "giftype", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif 
	return result;
}
void SupSDK::playVideo(){

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (pPlayer->getStoreis() == true)
	{

		if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//游戏中
		{
			__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			pPlayer->setStoreis(false);



		}
		if (BabyCare::instance()->getCurrSceneID() == EScene_Select)//选择房间界面
		{
			__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			pPlayer->setStoreis(false);

			if (pPlayer->getAchieveis() == true)
			{
				NotificationCenter::getInstance()->postNotification(REMOVE_UIAchievement);//移除成就界面
				pPlayer->setAchieveis(false);
			}
			if (pPlayer->getHomeis() == true)
			{
				NotificationCenter::getInstance()->postNotification(REMOVE_HOME);//移除选择房子界面
				pPlayer->setHomeis(false);
			}


		}

		if (BabyCare::instance()->getCurrSceneID() == EScene_Home)//主界面
		{
			pPlayer->setisglob(GAME_GLOB);

			//__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//=对话框

			//showMessageBoxID("Item9");
			pPlayer->setCurrGold(pPlayer->getCurrGold() + GAME_GLOB);
			pPlayer->saveTotalGoldSum();
			pPlayer->setStoreis(false);

		}
		{


			UserDefault::getInstance()->setIntegerForKey(PLAY_UNVIDEO_NUM, UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM) - 1);
			if (UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM) < 0)
			{
				UserDefault::getInstance()->setIntegerForKey(PLAY_UNVIDEO_NUM, 0);
			}
			UserDefault::getInstance()->flush();
		}
	}
	else
	{

		/*UILuckyForm* pForm = UILuckyForm::createInst();
		Director::getInstance()->getRunningScene()->addChild(pForm, 20);*/
		NotificationCenter::getInstance()->postNotification("ENotify_Finish_WatchVideo");

	}

#endif 

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "playRewardVideo", "()V");
	log("playRewardVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif 
	can_Video_show = true;

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SupSDK::TickVideo), this, 120, false);
}
bool SupSDK::getfacebooktype(){

	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = false;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getfacebooktype", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif 
	return result;
}

bool SupSDK::CanVideoGift()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "canPlayVideoGift", "()Z");
	CCLog("---canPlayVideoGift isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		return info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif
	return true;

}

void SupSDK::playVideoGift()
{
	//#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (pPlayer->getStoreis() == true)
	{




		if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//游戏中
		{
			__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			pPlayer->setStoreis(false);



		}
		if (BabyCare::instance()->getCurrSceneID() == EScene_Select)//选择房间界面
		{
			__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			pPlayer->setStoreis(false);

			if (pPlayer->getAchieveis() == true)
			{
				NotificationCenter::getInstance()->postNotification(REMOVE_UIAchievement);//移除成就界面
				pPlayer->setAchieveis(false);
			}
			if (pPlayer->getHomeis() == true)
			{
				NotificationCenter::getInstance()->postNotification(REMOVE_HOME);//移除选择房子界面
				pPlayer->setHomeis(false);
			}


		}

		if (BabyCare::instance()->getCurrSceneID() == EScene_Home)//主界面
		{
			pPlayer->setisglob(GAME_GLOB);

			//__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
			NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//=对话框

			//showMessageBoxID("Item9");
			pPlayer->setCurrGold(pPlayer->getCurrGold() + GAME_GLOB);
			pPlayer->saveTotalGoldSum();
			pPlayer->setStoreis(false);

		}
		{



		}
	}
	else
	{

		/*UILuckyForm* pForm = UILuckyForm::createInst();
		Director::getInstance()->getRunningScene()->addChild(pForm, 20);*/
		NotificationCenter::getInstance()->postNotification("ENotify_Finish_WatchVideo");

	}

	//#endif 
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "playVideoGift", "()V");
	CCLog("---playVideoGift isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
	can_Video_show = true;

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SupSDK::TickVideo), this, 120, false);

}



bool SupSDK::canPlayVideo(){

	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "canPlayVideo", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif 
	return result;
}

bool SupSDK::isFindGooglePlay()
{
	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "checkPlayServices", "()Z");
	log("canPlayVideo isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	result = true;
#endif
	return result;
}

bool SupSDK::isBillingSetupOK()
{
	bool result = false;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	result = true;
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo info;
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "checkBillEnvironment", "()Z");
	log("checkBillEnvironment isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		result = info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	result = true;
#endif
	return result;

}

void SupSDK::purchaseItem(string  sku)
{




#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	NotificationCenter::getInstance()->postNotification(NOT_BUY_SUCCESS);
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (isBillingSetupOK())
	{
		JniMethodInfo info;
		bool isHaved = false;
		isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "purchaseItem", "(Ljava/lang/String;)V");
		log("HideOptAD isHaved = %s", isHaved ? "true" : "false");
		if (isHaved)
		{
			jstring jstr = 0;
			jstr = (info.env)->NewStringUTF(sku.c_str());
			log(" SupSDK::purchaseItem=%s", sku.c_str());
			info.env->CallStaticVoidMethod(info.classID, info.methodID, jstr);
		}
	}
	else
	{
		//弹出无法付费的msgBox
		NotificationCenter::getInstance()->postNotification(NOT_BUY_TIMEOUT);
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	void Java_org_cocos2dx_cpp_AppActivity_purchaseItemComplete(JNIEnv* env, jobject thiz, jint requestID, jstring requestMsg) {
		//PurchaseLayer::SharedPurchaseLayer()->PurchaseItemCallback((EPurchaseCode)requestID, cocos2d::JniHelper::jstring2string(requestMsg));
		int  type = requestID;
		string key = cocos2d::JniHelper::jstring2string(requestMsg);
		log("*************[ purchaseItemComplete   requestID=%d,   key=%s  ] ***********", requestID, key.c_str());
		if (type == 0){
			NotificationCenter::getInstance()->postNotification(NOT_BUY_SUCCESS);
		}
		else {
			NotificationCenter::getInstance()->postNotification(NOT_BUY_FAILED);
		}
		log("*******NotificationCenter::getInstance()->postNotification******");
	}


	void Java_org_cocos2dx_cpp_AppActivity_finishgift(JNIEnv* env, jobject thiz, jint requestID){
		int  golb = requestID;
		Player* pPlayer = EntityMgr::instance()->pPlayer();
		bool type = SupSDK::gettype();
		if (type == true)//true积分墙   falsefacebook任务
		{

			Player* pPlayer = EntityMgr::instance()->pPlayer();

			if (SceneManager::instance()->getCurrSceneID() == EScene_Game)//游戏中
			{
				__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)golb);//金币奖励动画



			}
			if (SceneManager::instance()->getCurrSceneID() == EScene_Select)//选择房间界面
			{
				__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)golb);//金币奖励动画


			}

			if (SceneManager::instance()->getCurrSceneID() == EScene_Home)//主界面
			{
				pPlayer->setisglob(golb);

				NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//=对话框

				//showMessageBoxID("Item9");
				pPlayer->setCurrGold(pPlayer->getCurrGold() + golb);
				pPlayer->saveTotalGoldSum();

			}
		}
		else{
			if (!UserDefault::getInstance()->getBoolForKey(FACEBOOK_GIFT))
			{
				pPlayer->getfacebookgift(golb);

			}

		}

		log("*******finishgift******");

	}


	void Java_org_cocos2dx_cpp_AppActivity_finishWatchView(JNIEnv* env, jobject thiz) {


		Player* pPlayer = EntityMgr::instance()->pPlayer();

		if (pPlayer->getStoreis() == true)
		{


			if (SceneManager::instance()->getCurrSceneID() == EScene_Game)//游戏中
			{
				__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
				pPlayer->setStoreis(false);



			}
			if (SceneManager::instance()->getCurrSceneID() == EScene_Select)//选择房间界面
			{
				__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)GAME_GLOB);//金币奖励动画
				pPlayer->setStoreis(false);

				if (pPlayer->getAchieveis() == true)
				{
					NotificationCenter::getInstance()->postNotification(REMOVE_UIAchievement);//移除成就界面
					pPlayer->setAchieveis(false);
				}

				if (pPlayer->getHomeis() == true)
				{
					NotificationCenter::getInstance()->postNotification(REMOVE_HOME);//移除选择房子界面
					pPlayer->setHomeis(false);
				}
			}

			if (SceneManager::instance()->getCurrSceneID() == EScene_Home)//主界面
			{
				pPlayer->setisglob(GAME_GLOB);

				NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//=对话框

				//showMessageBoxID("Item9");
				pPlayer->setCurrGold(pPlayer->getCurrGold() + GAME_GLOB);
				pPlayer->saveTotalGoldSum();
				pPlayer->setStoreis(false);

			}
			{


				UserDefault::getInstance()->setIntegerForKey(PLAY_UNVIDEO_NUM, UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM) - 1);
				if (UserDefault::getInstance()->getIntegerForKey(PLAY_UNVIDEO_NUM) < 0)
				{
					UserDefault::getInstance()->setIntegerForKey(PLAY_UNVIDEO_NUM, 0);
				}
				UserDefault::getInstance()->flush();
			}

		}
		else
		{
			NotificationCenter::getInstance()->postNotification(ENotify_Finish_WatchVideo);

			/*UILuckyForm* pForm = UILuckyForm::createInst();
			Director::getInstance()->getRunningScene()->addChild(pForm, 20);*/
		}
		log("*******NotificationCenter::getInstance()->postNotification_ finishWatchView******");
	}
}

#endif



bool SupSDK::HaveNativeAd()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "isNativeLoaded", "()Z");
	CCLog("----HaveNativeAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		return info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif

	return false;
}
void SupSDK::ShowUmEvent(string eventid){
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "censusEventTimes", "(Ljava/lang/String;)V");
	CCLog("---ShowUmEvent isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		jstring jstr = 0;
		jstr = (info.env)->NewStringUTF(eventid.c_str());
		log(" SupSDK::purchaseItem=%s", eventid.c_str());
		info.env->CallStaticVoidMethod(info.classID, info.methodID, jstr);
	}
#endif


}
void SupSDK::ShowNativeAd()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showNativeAd", "()V");
	CCLog("---ShowNativeAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
	if (BabyCare::instance()->getCurrSceneID() != EScene_Select)
	{
		if (!SupSDK::HaveNativeAd())
		{
			SupSDK::showBannerAD();
		}
		else{
			SupSDK::hideBannerAD();
		}
	}
	//showBannerAD();
}

void SupSDK::ShowNativeAdForLoading()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showNativeAdForLoading", "()V");
	CCLog("---ShowNativeAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}

void SupSDK::HideNativeAd()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "hideNativeAd", "()V");
	CCLog("---HideNativeAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif



	Player* pPlayer = EntityMgr::instance()->pPlayer();
	if (pPlayer->readNoAdsStatus())
	{
		SupSDK::instance()->hideBannerAD();
	}
	else{
		if (BabyCare::instance()->getCurrSceneID() != EScene_Select && !pPlayer->getm_imgame())
		{

			SupSDK::showBannerAD();


		}
	}
}

bool SupSDK::HaveDevAd()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "isDevAdSwitch", "()Z");
	CCLog("---HaveDevAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		return info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif

	return false;
}

void SupSDK::ClickDevAd()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "devAdClick", "()V");
	CCLog("---ClickDevAd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif
}
void SupSDK::showOffer()
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	Player* pPlayer = EntityMgr::instance()->pPlayer();

	if (BabyCare::instance()->getCurrSceneID() == EScene_Game)//游戏中
	{
		__NotificationCenter::getInstance()->postNotification(GAME_ZHONG_GLOB, (Ref*)(intptr_t)100);//金币奖励动画



	}
	if (BabyCare::instance()->getCurrSceneID() == EScene_Select)//选择房间界面
	{
		__NotificationCenter::getInstance()->postNotification(NOT_GLOB_LUCKY, (Ref*)(intptr_t)100);//金币奖励动画


	}

	if (BabyCare::instance()->getCurrSceneID() == EScene_Home)//主界面
	{
		pPlayer->setisglob(100);

		NotificationCenter::getInstance()->postNotification(TANGCHU_GLOB);//=对话框

		//showMessageBoxID("Item9");
		pPlayer->setCurrGold(pPlayer->getCurrGold() + 100);
		pPlayer->saveTotalGoldSum();

	}
#endif 


	SupSDK::instance()->ShowUmEvent(OFFER_UM);


#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showOffer", "()V");
	CCLog("---showOffer isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif


}
void SupSDK::showPopADBegin(bool is_force)
{
	//if (!is_force && !CheckPopAdShow())
	//{
	//	return;
	//}
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showPAUSEAdBegin", "()V");
	CCLog("---ShowPopADBegin isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif


}

void SupSDK::showPopADEnd(bool is_force)
{

	//if (!is_force && !can_pop_ad_show_)
	//{
	//	return;
	//}
	//if (can_pop_ad_show_)
	//{
	//	ResetPopAdLimit();
	//}

#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showPAUSEAdEnd", "()V");
	CCLog("---ShowPopADEnd isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);
	}
#endif


}

bool SupSDK::IsNativeWithPop()
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "isNativeWithPop", "()Z");
	CCLog("----IsNativeWithPop isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		return info.env->CallStaticBooleanMethod(info.classID, info.methodID);
	}
#endif

	return false;
}
void  SupSDK::showfacebook()
{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Player* pPlayer = EntityMgr::instance()->pPlayer();


	if (!UserDefault::getInstance()->getBoolForKey(FACEBOOK_GIFT))
	{
		pPlayer->getfacebookgift(100);

	}

#endif

#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;

	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showfacebook", "()V");
	CCLog("----IsNativeWithPop isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID);

	}
#endif


}
bool SupSDK::CanPopAdShow()
{

	return can_pop_ad_show_;
}

bool SupSDK::CheckPopAdShow()
{
	if (pop_ad_limit_time_ >= 30.0 /*|| pop_ad_limit_num_ > 1*/)
	{
		can_pop_ad_show_ = true;

	}
	else
	{
		RecordPopAdCall();
		can_pop_ad_show_ = false;
	}
	return can_pop_ad_show_;
}

void SupSDK::ResetPopAdLimit()
{
	can_pop_ad_show_ = false;
	pop_ad_limit_time_ = 0.0f;
	pop_ad_limit_num_ = 0;
}
void SupSDK::RecordPopAdCall()
{
	pop_ad_limit_num_ += 1;

}
void SupSDK::Tick(float  dt)
{

	pop_ad_limit_time_ += dt;
	if (pop_ad_limit_time_ > 1000){
		pop_ad_limit_time_ = 1000;
	}
	log("pop_ad_limit_time_%f", pop_ad_limit_time_);

}
void SupSDK::TickMore(float  dt)
{
	can_more_dot = true;
	pop_more_dot_time_ += dt;
	if (pop_more_dot_time_ > 300){
		can_more_dot = false;
		pop_more_dot_time_ = 0;
		NotificationCenter::getInstance()->postNotification(NOT_MORE_DOT_VISIT);

		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SupSDK::TickMore), this);
	}
	log("pop_More_dot_time_%d can_more_dot %d", pop_more_dot_time_, can_more_dot);

}
void SupSDK::updateMoredot()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SupSDK::TickMore), this, 1, false);

}

void SupSDK::TickCoins(float  dt)
{
	can_coins_dot = true;
	pop_coins_dot_time_ += dt;
	if (pop_coins_dot_time_ > 300){
		can_coins_dot = false;
		pop_coins_dot_time_ = 0;
		NotificationCenter::getInstance()->postNotification(NOT_COINS_DOT_VISIT);

		CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SupSDK::TickCoins), this);
	}
	log("pop_Coins_dot_time_%f", pop_coins_dot_time_);

}
void SupSDK::updatecoinsdot()
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SupSDK::TickCoins), this, 1, false);

}
void SupSDK::showNativeWithRect(Rect rect, int type) {
	//auto director = Director::getInstance();

	auto glview = Director::getInstance()->getOpenGLView();
	Size screenSize = glview->getFrameSize();
	Size winSzie = Director::getInstance()->getWinSize();
	//type 1 暂停 0结算

	float GAME_DESTINY_X = screenSize.width / winSzie.width;
	float GAME_DESTINY_Y = screenSize.height / winSzie.height;
	log("typetypetype%d", type);

	SupSDK::instance()->ShowNativeAdWithRect(rect.origin.x*GAME_DESTINY_X, rect.origin.y* GAME_DESTINY_Y, rect.size.width* GAME_DESTINY_X, rect.size.height* GAME_DESTINY_Y, type);
}

bool SupSDK::ShowNativeAdWithRect(int x, int y, int w, int h, int isShowBgColor)
{
#ifdef __SUP_ANDROID__ 
	JniMethodInfo info;
	int newX = x;
	int newY = y;
	int newW = w;
	int newH = h;
	int isShow = isShowBgColor;
	log("=ShowNativeAdWithRect======x1=%f,y1=%f,w1=%f,h1=%f", x, y, w, h);
	log("=ShowNativeAdWithRect======x=%d,y=%d,w=%d,h=%d", newX, newY, newW, newH);
	bool isHaved = false;
	isHaved = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "showNativeAdWithRect", "(IIIII)V");
	CCLog("---showNativeAdWithRect isHaved = %s", isHaved ? "true" : "false");
	if (isHaved)
	{
		info.env->CallStaticVoidMethod(info.classID, info.methodID, newX, newY, newW, newH, isShow);
	}
#endif	 


	return false;
}

void SupSDK::TickVideo(float  dt)
{

	can_Video_show = false;

	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SupSDK::TickVideo), this);

}