#ifndef __GAME_ITEM_Factory_H__
#define __GAME_ITEM_Factory_H__

#include "ItemBase.h"

class ItemFactory : public sup::Singleton<ItemFactory, Ref>
{
public:
	ItemFactory();
	virtual ~ItemFactory();
	ItemBase* Create(EGameItemType eType, ImageView* pImage);

private:
	SINGLETON_FRIEND_SUB(ItemFactory, Ref);

};

#endif