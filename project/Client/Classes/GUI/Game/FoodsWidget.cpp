#include "FoodsWidget.h"
#include "BabyCare.h"
#include "../UIManager.h"

FoodsWidget::FoodsWidget()
{

}

FoodsWidget::~FoodsWidget()
{

}

void FoodsWidget::init(Layout* pLayout, EFoodsType eType)
{
	m_eID = eType;
	m_pLayou = pLayout;
	m_pFoods = EntityMgr::instance()->pPlayer()->getFoodsList()->getFoodsByID(m_eID);

	m_pImage = dynamic_cast<ImageView*>(pLayout->getChildByName("Image_shuiguo"));
	m_pImage->loadTexture(m_pFoods->getImg(), Widget::TextureResType::LOCAL);

	m_pPrice = dynamic_cast<TextAtlas*>(pLayout->getChildByName("AtlasLabel_1"));
	m_pPrice->setString(sup::SupString::int2String(m_pFoods->getPrice()));
	setInitialPos(m_pImage->getPosition());
}


