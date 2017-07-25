#ifndef __GAME_Monster_Factory_H__
#define __GAME_Monster_Factory_H__

#include "MonsterBase.h"

class MonsterFactory : public sup::Singleton<MonsterFactory, Ref>
{
public:
	MonsterFactory();
	virtual ~MonsterFactory();
	MonsterBase* Create(Monster* pMonster);

private:
	SINGLETON_FRIEND_SUB(MonsterFactory, Ref);

};

#endif