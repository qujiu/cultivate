#ifndef __BABYCARE__
#define __BABYCARE__

#include "Common/common.h"
#include "define.h"
#include "Entity/EntityMgr.h"
//#include "Entity/SupCocoex.h"

enum ESceneID
{
	EScene_None,
	EScene_Logo,
	EScene_Home,
	EScene_Select,
	EScene_Game,
	EScene_Max
};


class BabyCare : public sup::Singleton<BabyCare>
{
private:
	SINGLETON_FRIEND_SUB(BabyCare);
	BabyCare();
	virtual ~BabyCare();

public:
	void onGameInit();
	void onStatusChanged(ESceneID id);
	void removeUnusedTextures();

	void SetResultCallback_None();
	void gotoMinigame();

	inline Scene* getCurrScene(){ return m_pCurrScene; };
public:
	SUP_R_PROPERTY_DEF(private, ESceneID, m_eCurrSceneID, getCurrSceneID);
	SUP_RW_PROPERTY_PREFIX_DEF(private, ESceneID, m_eFrontSceneID, FrontSceneID, ESceneID);
private:
	void onStartGame();

private:
	Scene* m_pCurrScene;
};

#endif