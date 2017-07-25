
/*
** implement MonsterList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#include "Monster.h"
#include "ResManager/ConfigDataCenter.h"
#include "EntityMgr.h"
/////////////////////////////////////////////////////////////////////////////

Monster::Monster(const JsonValue &value)
{
	setMSceneID((EGameRoom)value["SceneID"].GetInt());
	setMType((EGameMonsterType)value["Type"].GetInt());
	setMID(value["ID"].GetInt());
	setMPicture(value["Picture"].GetString());
	setMPos(sup::SupUtils::toPoint(value["Pos"].GetString()));
	setMVisible((bool)value["Visible"].GetInt());
	setDoneNum(value["DoneNum"].GetInt());
	setMFlag(value["Flag"].GetInt());
	setMRotation(value["Rotation"].GetInt());
	setMAniID(value["AniID"].GetInt());
	setZorder(value["Zorder"].GetInt());
	setValid(value["Valid"].GetInt());
	setNextID(value["NextID"].GetInt());
	setNextType(value["NextTpye"].GetInt());
	setMParticle(value["Particle"].GetInt());
	setMItemType(sup::SupUtils::SplitStringToInt(value["ItemType"].GetString()));
}

Monster::~Monster()
{

}


//////////////////////////////////////////////////////////////////////////////
MonsterList::MonsterList()
{

}


MonsterList::~MonsterList()
{
	releaseMonsterList();
}

void MonsterList::initMonsterList()
{
	initMonsterList(ConfigDataCenter::instance()->monster(0));
}

void MonsterList::initMonsterList(const JsonValue &value)
{
    for (unsigned int i = 0; i < value.Size(); i++)
    {
		const JsonValue &monsterValue = value[i];
		int sceneID = monsterValue["SceneID"].GetInt();
		MonsterSceneIter pSceneIter = m_Monsters.find((EGameRoom)sceneID);
		if (pSceneIter == m_Monsters.end())
		{
			m_Monsters.insert(make_pair((EGameRoom)sceneID, new MonsterType));
			pSceneIter = m_Monsters.find((EGameRoom)sceneID);
		}

		MonsterType* pMonsterType = pSceneIter->second;
		int type = monsterValue["Type"].GetInt();
		MonsterTypeIter pIter = pMonsterType->find((EGameMonsterType)type);
		if (pIter == pMonsterType->end())
		{
			pMonsterType->insert(make_pair((EGameMonsterType)monsterValue["Type"].GetInt(), new Monsters));
			pIter = pMonsterType->find((EGameMonsterType)type);
			
		}
		pIter->second->push_back(new Monster(monsterValue));

    }
}

void MonsterList::releaseMonsterList()
{
	for (MonsterSceneIter pIter = m_Monsters.begin(); pIter != m_Monsters.end(); ++pIter)
    {
		for (MonsterTypeIter pTypeIter = pIter->second->begin(); pTypeIter != pIter->second->end();  ++pTypeIter)
		{
			for (MonstersIter pMonstersIter = pTypeIter->second->begin(); pMonstersIter != pTypeIter->second->end();)
			{
				MonstersIter pTempIter = pMonstersIter++;
				delete *pTempIter;
				*pTempIter = NULL;
				pTypeIter->second->erase(pTempIter);
			}
			delete pTypeIter->second;
		}
		pIter->second->clear();
		delete pIter->second;
    }
	m_Monsters.clear();
}

MonsterList::MonsterType* MonsterList::getMonsterType(EGameRoom sceneID)
{
	auto pIter = m_Monsters.find(sceneID);
	if (m_Monsters.end() != pIter)
	{
		return pIter->second;
	}
	return NULL;
}

MonsterList::Monsters* MonsterList::getMonsters(EGameRoom secenID, EGameMonsterType tpye)
{
	MonsterSceneIter pIterScene = m_Monsters.find(secenID);
	if (m_Monsters.end() != pIterScene)
	{
		MonsterTypeIter pMonsters = (pIterScene->second)->find(tpye);
		if ( (pIterScene->second)->end() != pMonsters)
		{
			return pMonsters->second;
		}
	}
	return NULL;
}

Monster* MonsterList::getMonster(EGameRoom secenID, EGameMonsterType typeID, int MonsterID)
{
	MonsterSceneIter pIterScene = m_Monsters.find(secenID);
	if (m_Monsters.end() != pIterScene)
	{
		MonsterTypeIter pMonsters = (pIterScene->second)->find(typeID);
		if ((pIterScene->second)->end() != pMonsters)
		{
			for (MonstersIter pIter = (pMonsters->second)->begin(); pIter != (pMonsters->second)->end();)
			{
				if (MonsterID == (*pIter)->getMID())
				{
					return *pIter;
				}
				++pIter;
			}
		}
	}
	return NULL;
}

void MonsterList::removeMonster(EGameRoom secenID, EGameMonsterType typeID, int MonsterID)
{
	MonsterType* pType = getMonsterType(secenID);
	if (NULL != pType)
	{
		Monsters* pMonsters = getMonsters(secenID, typeID);
		if (NULL != pMonsters)
		{
			for (MonstersIter pIter = pMonsters->begin(); pIter != pMonsters->end();)
			{
				if (MonsterID == (*pIter)->getMID())
				{
					MonstersIter pTempIter = pIter++;
					delete *pTempIter;
					*pTempIter = NULL;
					pMonsters->erase(pTempIter);
					continue;
				}
				++pIter;
			}
			if (pMonsters->size() <= 0)
			{
				delete pMonsters;
				pMonsters = NULL;
				pType->erase( pType->find(typeID) );
			}
		}

		if (pType->size() <= 0)
		{
			delete pType;
			pType = NULL;
			m_Monsters.erase(m_Monsters.find(secenID));
		}
	}
}

void MonsterList::removeMonster(Monster* pMonster)
{
	removeMonster(pMonster->getMSceneID(), pMonster->getMType(), pMonster->getMID());
}