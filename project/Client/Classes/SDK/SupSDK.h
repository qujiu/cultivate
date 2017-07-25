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
	void showOptAD(int x, int y, int w, int h);//��̬icon
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
	void showPopADEnd(bool is_force);//trueǿ�ƽ�����
	bool IsNativeWithPop();

	bool getfacebooktype();

	void showOffer();//��ʾ����ǽ
	bool static gettype();//ʲô����0����ǽ1����
	bool getgift();//�Ƿ���
	bool CanPopAdShow();//

	bool CheckPopAdShow();//�ж�
	void ResetPopAdLimit();//���ó�ʼֵ
	void RecordPopAdCall();//������;

	void Tick(float  dt);
	float pop_ad_limit_time_;//��ǰʱ��
	int pop_ad_limit_num_;//��ǰ����
	bool can_pop_ad_show_;//��ǰ�Ƿ�չʾ
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