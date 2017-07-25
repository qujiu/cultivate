#include "define.h"
#include "ItemFactory.h"
#include "ItemWidget.h"

SINGLETON_DEFINE_INST(ItemFactory, Ref);

ItemFactory::ItemFactory()
{

}


ItemFactory::~ItemFactory()
{

}


ItemBase* ItemFactory::Create(EGameItemType eType, ImageView* pImage)
{
	ItemBase* pItemBase = NULL;

	switch (eType)
	{
	case EItem_Null:
		break;
	case EItem_zhentou:
	case EItem_beizi:
	case EItem_wanju:
	case EItem_zhiniaoku:
	case EItem_naizui:
		pItemBase = ItemWanJu::createInst(eType, pImage);
		break;
	case EItem_huasa:
		pItemBase = ItemHuasa::createInst(eType, pImage);
		break;
	case EItem_yuhua:
		pItemBase = ItemYuhua::createInst(eType, pImage);
		break;
	case	EItem_xiaobear:
	case	EItem_muma:
	case EItem_tantanqiu :
		pItemBase = ItemCommonToy::createInst(eType, pImage);
		break;
	case	EItem_qitong:
		pItemBase = ItemWidget::createInst(eType, pImage);
		break;

	case	EItem_qiqiu1:
	case	EItem_qiqiu2:
	case	EItem_qiqiu3:
		pItemBase = ItemQiqiu::createInst(eType, pImage);
		break;

	case EItem_shaoziG:
		pItemBase = ItemFood::createInst(eType, pImage);
		break;
	case	EItem_yifu:
	case	EItem_xiezi:
	case	EItem_maozi:
	case	EItem_kuzi:
	case	EItem_xiuzi:
	case	EItem_yashua:
		pItemBase = ItemReplace::createInst(eType, pImage);
		break;
	case  EItem_shaoziN:
	case EItem_YaShua:
	case EItem_Yabei:
	case EItem_maojin:
		pItemBase = ItemWidget::createInst(eType, pImage);
	default:
		pItemBase = ItemWidget::createInst(eType, pImage);
		break;
	}

	CC_ASSERT(pItemBase);
	return pItemBase;
}