#ifndef __SUP_SDK_H__
#define __SUP_SDK_H__


#include "cocos2d.h"
#include "Common/Common.h"

using namespace std;
using namespace cocos2d;

class SupSDK :public sup::Singleton<SupSDK, Ref>
{
private:
	SINGLETON_FRIEND_SUB(SupSDK, Ref);
	SupSDK(void);
	~SupSDK(void);

	std::string getcurrTime();
public:
	void share();
	void comment();
	void shareToEmail(char* file);
	void shareToFacebook();
	std::string getCaptureImgPath();
	void More();
	void watchVideo();
	bool getVideoVisable();

	void showBannerAD();
	void hideBannerAD();
	void showFullAD();
	void showPopAD();
	void gamePause();
	void gameAgain();
	void ExitAD();
	void FlushCapturePicture(char* file);

	bool CanShowOptAD();
	void showOptAD(int x, int y, int w, int h);//动态icon
	void hideOptAD();
	void showParentsMail();

	bool isFindGooglePlay();
	void purchaseItem(string  sku);
	bool canPlayVideo();
	void playVideo();
	bool palywang();
	bool isBillingSetupOK();

	bool HaveNativeAd();
	void ShowNativeAd();
	void ShowNativeAdForLoading();
	void HideNativeAd();
	void ShowUmEvent(string  eventid);


	bool HaveDevAd();
	void ClickDevAd();
	void showfacebook();

	void showPopADBegin(bool is_force);
	void showPopADEnd(bool is_force);//true强制进入广告
	bool IsNativeWithPop();

	bool getfacebooktype();

	void showOffer();//显示积分墙
	bool static gettype();//什么奖励0积分墙1任务
	bool getgift();//是否奖励
	bool CanPopAdShow();//

	bool CheckPopAdShow();//判断
	void ResetPopAdLimit();//重置初始值
	void RecordPopAdCall();//计数器;

	void Tick(float  dt);
	float pop_ad_limit_time_;//当前时间
	int pop_ad_limit_num_;//当前次数
	bool can_pop_ad_show_;//当前是否展示
	bool ShowNativeAdWithRect(int x, int y, int w, int h, int isShowBgColor);
	void showNativeWithRect(Rect rect, int type);

	int pop_more_dot_time_;
	bool  can_more_dot;
	int pop_coins_dot_time_;
	bool   can_coins_dot;

	void TickMore(float  dt);
	void updateMoredot();
	void TickCoins(float dt);
	void updatecoinsdot();
	void playVideoGift();
	bool CanVideoGift();
	bool can_Video_show;
	void TickVideo(float  dt);

};

#endif