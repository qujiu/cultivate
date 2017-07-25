#include "define.h"
#include "MonsterFactory.h"
#include "MonsterWidget.h"

SINGLETON_DEFINE_INST(MonsterFactory, Ref);

MonsterFactory::MonsterFactory()
{

}

MonsterFactory::~MonsterFactory()
{

}

MonsterBase* MonsterFactory::Create(Monster* pMonster)
{
	MonsterBase* pMonsterBase = NULL;

	switch (pMonster->getMType())
	{
	case EMonster_Null:
		break;
	case EMonster_PaoMo:
		pMonsterBase = MonsterPaomo::createInst(pMonster);
		break;
	case EMonster_KouShui:
		pMonsterBase = MonsterGeneral::createInst(pMonster);
		break;
	default:
		pMonsterBase = MonsterGeneral::createInst(pMonster);
		break;
	}

	CC_ASSERT(pMonsterBase);

	return pMonsterBase;
}