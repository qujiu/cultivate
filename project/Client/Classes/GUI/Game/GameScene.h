#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "define.h"
#include "GUI/Form.h"
#include "GUI/Form/BabyControl.h"
#include "../Form/MenuControl.h"


class GameScene : public Scene
{
public:
	static GameScene* create();
	bool init();

	GameScene(void);
	virtual ~GameScene(void);
	
	void GameUIInit();
public:
	Form* m_pGameForm;
	Form* m_pBgForm;
public:
	Form* getGameForm();
	Form* getBgForm();
	MenuControl* m_pMenuControl;
	BabyControl* m_PlayerLayer;
};




#endif