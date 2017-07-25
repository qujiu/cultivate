
#ifndef __MINI_GAME_PUBLIC_H__
#define __MINI_GAME_PUBLIC_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocostudio/CCActionManagerEx.h" 
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h" 


USING_NS_CC;
USING_NS_CC_EXT;


using namespace cocos2d;
using namespace std;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;


enum  MINI_FORM_SHOW_SPEED {
	MINI_FAST,
	MINI_MIDDLE,
	MINI_SLOW,
};

enum GAME_STATE{
	GAME_INIT,
	GAME_READY,
	GAME_RUN,
	GAME_ANIMATION,
	GAME_PAUSE,
	GAME_DIE,
	GAME_OVER,
};

//#define HitMouse_Index   0 
//#define FindCat_Index    1
//#define Fishing_Index    2

enum MINI_GAME_NAME{
	MINI_GAME_HITMOUSE,
	MINI_GAME_FINDCAT,
	MINI_GAME_FISHING,
};

#define MINI_POP_DELAY		1.0f
#define HAS_RUN_MINIGAME	"HAS_RUN_MINIGAME"

typedef struct _GameController{
	const char *game_name;
	const char *game_icon;
	const char *game_desc;
	const char *game_title;
	const char *game_preview;
	const int  game_target_score;
} GameController;

static GameController miniGameNames[] = {
	{ "HitMouse", "Minigames/HitMouse/mini_game_hitmouse.png", "", "Minigames/HitMouse/ui_name_hitmouse.png", "Minigames/HitMouse/mini_preview_hitmouse.png", 40 },
	{ "FindCat", "Minigames/FindCat/mini_game_findcat.png", "", "Minigames/FindCat/ui_name_findcat.png", "Minigames/FindCat/mini_preview_findcat.png", 20 },
	{ "Fishing", "Minigames/Fishing/mini_game_fishingt.png", "", "Minigames/Fishing/ui_name_fishing.png", "Minigames/Fishing/mini_preview_fishing.png", 35 },
};

static int miniGamesCount = sizeof(miniGameNames) / sizeof(miniGameNames[0]);
static GameController *currentController = nullptr;



#endif // __MINI_GAME_PUBLIC_H__