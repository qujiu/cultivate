/*
** declare entity manager
** author: zhangchao;
** date: 2014.10.10
*/

#include "EntityMgr.h"


SINGLETON_DEFINE_INST(EntityMgr, Ref);

EntityMgr::EntityMgr()
: m_pPlayer(NULL)
{

}

EntityMgr::~EntityMgr()
{
	if (m_pPlayer)
		delete m_pPlayer;
}

Player *EntityMgr::createPlayer()
{
	if (!m_pPlayer)
	{
		m_pPlayer = new Player();
		m_pPlayer->init();
	}
	return m_pPlayer;
}

void EntityMgr::clearPlayer()
{
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
}
