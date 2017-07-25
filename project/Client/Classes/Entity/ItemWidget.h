#ifndef _ITEM_WIDGET_H_
#define _ITEM_WIDGET_H_

#include "Entity/Item.h"
#include "define.h"
#include "GameType.h"
#include "Common/Common.h"
#include "MonsterWidget.h"
#include "GUI/Form.h"
#include "ItemBase.h"

class ItemWidget : public ItemBase
{
public:
	CREATE_(ItemWidget, EGameItemType type, ImageView* pImage)
		_INST(ItemWidget, type, pImage)
		ItemWidget(EGameItemType type, ImageView* pImage);
	virtual ~ItemWidget();
	virtual bool init();
protected:
	virtual bool onTriggerMonster();
	void TouchBegin();
	void TouchEnd();
};

class ItemFood : public ItemBase
{
public:
	CREATE_(ItemFood, EGameItemType type, ImageView* pImage)
		_INST(ItemFood, type, pImage)

		ItemFood(EGameItemType type, ImageView* pImage);
	virtual ~ItemFood();
	virtual bool init();
protected:
	virtual bool onTriggerMonster();
	void TouchEnd();
private:
};

class ItemReplace : public ItemBase
{
public:
	CREATE_(ItemReplace, EGameItemType type, ImageView* pImage)
		_INST(ItemReplace, type, pImage)
		ItemReplace(EGameItemType type, ImageView* pImage);
	virtual ~ItemReplace();
	virtual bool init();
protected:
	void TouchBegin();
	void TouchMove();
	void TouchEnd();
	void RefreshItemAndMonsterImage(int iID, const char* skin, const char* attachment);
};

class ItemCommonToy: public ItemBase
{
public:
	CREATE_(ItemCommonToy, EGameItemType type, ImageView* pImage)
		_INST(ItemCommonToy, type, pImage)
		ItemCommonToy(EGameItemType type, ImageView* pImage);
	virtual ~ItemCommonToy();
	virtual bool init();
protected:
	void TouchBegin();
	void TouchMove();
	void TouchEnd();
	virtual bool onTriggerMonster();
};

class ItemQiqiu : public ItemBase
{
public:
	CREATE_(ItemQiqiu, EGameItemType type, ImageView* pImage)
		_INST(ItemQiqiu, type, pImage)
		ItemQiqiu(EGameItemType type, ImageView* pImage);
	virtual ~ItemQiqiu();
	virtual bool init();
protected:
	void TouchEnd();
	virtual bool onTriggerMonster();
};

class ItemYuhua : public ItemBase
{
public:
	CREATE_(ItemYuhua, EGameItemType type, ImageView* pImage)
		_INST(ItemYuhua, type, pImage)

		ItemYuhua(EGameItemType type, ImageView* pImage);
	virtual ~ItemYuhua();
	virtual bool init();
protected:
	virtual bool onTriggerMonster();
	void TouchEnd();
private:
};

class ItemHuasa : public ItemBase
{
public:
	CREATE_(ItemHuasa, EGameItemType type, ImageView* pImage)
		_INST(ItemHuasa, type, pImage)

		ItemHuasa(EGameItemType type, ImageView* pImage);
	virtual ~ItemHuasa();
	virtual bool init();
protected:
	virtual bool onTriggerMonster();
	void TouchBegin();
	void TouchMove();
	void TouchEnd();

public:
	void AppearImageAction(bool isAppear);
	void ItemShowImg();
};

class ItemWanJu : public ItemBase
{
public:
	CREATE_(ItemWanJu, EGameItemType type, ImageView* pImage)
		_INST(ItemWanJu, type, pImage)

		ItemWanJu(EGameItemType type, ImageView* pImage);
	virtual ~ItemWanJu();
	virtual bool init();
protected:
	void TouchBegin();
	void TouchMove();
	void TouchEnd();
	void RefreshToolImage(EGameItemType iID);
};
#endif