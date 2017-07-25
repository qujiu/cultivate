/*
** declare ToolList of my client
** author: zhangchao;
** date: 2014.10.10
*/

#ifndef __Tool_ENTITY_H__
#define __Tool_ENTITY_H__

#include "cocos2d.h"
#include "Common/Common.h"
#include "ResManager/ConfigDataCenter.h"
#include "GameType.h"
USING_NS_CC;

// -----------------------------------------------------------------------
// implement Tool class
// -----------------------------------------------------------------------

class Tool
{
public:
	Tool(const JsonValue &value);
	virtual ~Tool();

public:

public:
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nID, ID, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nScene, Nscene, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, m_nIsType, IsType, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, int, IsMultiple, IsMultiple, int);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, vector<int>, m_vecIconResID, IconResID, vector<int>);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strPanelName, PanelName, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strSkin, ItemSkin, string);
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, string, m_strAttachment, ItemAttachment, string);

};

// -----------------------------------------------------------------------
// implement ToolList class
// -----------------------------------------------------------------------
class ToolList : public Ref
{
public:
	ToolList(const JsonValue &value);
	~ToolList();

	SUP_TYPEDEF_MAP_INSTS(int, Tool*, Tools);

public:	
	void initToolList(const JsonValue &value);
	void releaseToolList();
    
	Tool* getToolByID(int ToolID);
private:
	Tools m_ToolList;
}; 


#endif