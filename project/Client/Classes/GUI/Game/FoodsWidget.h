#ifndef __GAME_FOODSWIDGET_H__
#define __GAME_FOODSWIDGET_H__

#include "define.h"
#include "GUI/Form.h"
#include "GameType.h"
#include "Common/Common.h"
#include "Entity/Item.h"
#include "Entity/MonsterWidget.h"
#include "cocostudio/CCArmature.h"
#include "Entity/EntityMgr.h"

class FoodsWidget : public Node
{
public:
	FoodsWidget();
	virtual ~FoodsWidget();

	void init(Layout* pLayout, EFoodsType eType);
public:
	inline ImageView* getImage(){ return m_pImage; };
	inline Layout* getLayout(){ return m_pLayou; };
	inline Foods* getFoods(){ return m_pFoods; };
	SUP_RW_REF_PROPERTY_PREFIX_DEF(private, Vec2, m_vInitialPos, InitialPos, Vec2);
private:
	ImageView* m_pImage;
	TextAtlas* m_pPrice;
	EFoodsType m_eID;
	Layout* m_pLayou;
	Foods* m_pFoods;
};

#endif