/*
** declare ToolList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __ItemTool_ENTITY_H__
#define __ItemTool_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Tool class
// -----------------------------------------------------------------------

class ItemTool
{
public:
	ItemTool(const JsonValue &value);
	virtual ~ItemTool();

public:

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_nIcon, Icon, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_nImage, Image, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nScale, Scale, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nLock, Lock, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, IsPrice, Price, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, IS_Room, Room, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strPlist, Plist, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strImage, UI_Image, string);
};

// -----------------------------------------------------------------------
// implement ToolList class
// -----------------------------------------------------------------------
class ItemToolList : public Ref
{
public:
	ItemToolList(const JsonValue &value);
	~ItemToolList();

	SUP_TYPEDEF_MAP_INSTS(int, ItemTool*, Tools);

public:
	void initToolList(const JsonValue &value);
	void releaseToolList();

	ItemTool* getItemToolByID(int ToolID);
private:
	Tools m_ToolList;
};


#endif