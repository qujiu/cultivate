
/*
** declare MonsterWidget
** author: zhang chao;
** date: 2014.10.10
*/
#ifndef __GAME_MONSTER_WIDGET_H__
#define __GAME_MONSTER_WIDGET_H__

#include "MonsterBase.h"



/////////////////////////////MonsterGeneral///////////////////////////////////////////////////////////////////////////////////
class MonsterGeneral : public MonsterBase
{
public:
	CREATE_(MonsterGeneral, Monster* pMonster)
		_INST(MonsterGeneral, pMonster)

		MonsterGeneral(Monster* pMonster);
	virtual ~MonsterGeneral();
	virtual bool init();
	void onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn = false);
	void onHitComplete();
	void onHitCompleteCallback(float delta);
	void AnimationMovementEventListener();
protected:
	ActionTimeline* m_pActionTimeline;
	Node* m_pTimelineNode;
};
///////////////////////////////MonsterGeneral end//////////////////////////////////////////////////////////////////////////////

/////////////////////////////MonsterPaomo///////////////////////////////////////////////////////////////////////////////////
class MonsterPaomo : public MonsterBase
{
public:
	CREATE_(MonsterPaomo, Monster* pMonster)
		_INST(MonsterPaomo, pMonster)

		MonsterPaomo(Monster* pMonster);
	virtual ~MonsterPaomo();
	virtual bool init();

public:
	void onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn = false);
	void RefreshMonster();
	void initMonsterStatus();
};
///////////////////////////////MonsterPaomo end//////////////////////////////////////////////////////////////////////////////

#endif