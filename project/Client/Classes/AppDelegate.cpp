#include "AppDelegate.h"
#include "BabyCare.h"
#include "GUI/SupLayout.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("BabyCare", cocos2d::Rect(0, 0, 640, 960));
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0 / 60);

	cocos2d::Size winSize = director->getWinSize();

	if (winSize.width / winSize.height > SUP_DESIGN_W / SUP_DESIGN_H) {
		SUP_DEFAULT_W = winSize.width / winSize.height*SUP_DESIGN_H;;
		SUP_DEFAULT_H = SUP_DESIGN_H;

	}
	else
	{
		SUP_DEFAULT_W = SUP_DESIGN_W;
		SUP_DEFAULT_H = winSize.height / winSize.width*SUP_DESIGN_W;
	}

	SUP_SCALE_X = SUP_DEFAULT_W / SUP_DESIGN_W;
	SUP_SCALE_Y = SUP_DEFAULT_H / SUP_DESIGN_H;

	glview->setDesignResolutionSize(SUP_DEFAULT_W, SUP_DEFAULT_H, ResolutionPolicy::SHOW_ALL);

	BabyCare::instance()->onGameInit();
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
