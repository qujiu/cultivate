/*
** declare entity manager
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __ENTITY_MGR__
#define __ENTITY_MGR__

#include "Common/common.h"
#include "Player.h"
#include "define.h"

class Player;
class EntityMgr : public sup::Singleton<EntityMgr, Ref>
{
private:
	SINGLETON_FRIEND_SUB(EntityMgr, Ref);
	EntityMgr();
	~EntityMgr();
	
public:
	Player* createPlayer();
	void clearPlayer();
	Player* pPlayer() const
	{
		return m_pPlayer;
	}

private:
	Player *m_pPlayer;
};


// -----------------------------------------------------------------------
// entities
// -----------------------------------------------------------------------


#endif