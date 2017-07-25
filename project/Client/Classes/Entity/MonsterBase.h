#ifndef  _MONSTERWIDGET_H_
#define  _MONSTERWIDGET_H_

#include "define.h"
#include "GUI/Form.h"
#include "Entity/Monster.h"
#include "cocostudio/CCArmature.h"
#include "Custom/GraphicsBoard.h"
#include "Entity/EntityMgr.h"

class ItemBase;

class MonsterBase : public BaseControl
{
public:
	CREATE_(MonsterBase, Monster* pMonster)
		_INST(MonsterBase, pMonster)
	virtual bool init();
	MonsterBase(Monster* pMonster);
	virtual ~MonsterBase();
public:
	inline Monster* getMonster()const{ return m_pMonster; };
	inline ImageView* getImage()const{ return m_pImage; };
	inline int getDoneNum()const { return m_nDoneNum; };
	virtual void onHitStart(ItemBase* pItemWidget, EGameItemHitProcessId eID, bool bTurn = false);
	void onHitComplete();
	virtual void onComplete();
	virtual void initMonsterStatus();
	virtual bool getCurrMonsterGraphicsNotZeroPixel();
	virtual void RefreshMonster(bool bVisual);
	virtual void Removes();
	void runTwinkle(bool bFlag);
	void runAnimation(bool bFlag);
	void runParticle(bool bFlag);
	void removeParticle();
	bool getMonsterVisual();
	virtual bool DrawBoard(const Vec2& pos);
	virtual void SetBrushOrEraser(bool flag);
	virtual void ChangeGraphicsBoard(int native_res_id, bool brush_or_eraser);
	virtual void ChangeMonsterImage(int native_res_id);

protected:
	Monster* m_pMonster;
	ItemBase* m_pItemWidget;
	ImageView* m_pImage;
	ImageView* m_pTip;
	int m_nDoneNum;
	bool m_bTurn;  //标记怪物清理后道具是否移动位置;
	bool m_bTouchFlag;
	bool m_bRemove;
	Vec2 m_touchLastPos; //记录点击怪物的坐标;
	ParticleSystemQuad* m_pParticle;
	Armature* m_pArmature;
public:
	bool m_bVisual;
	int m_iFinishTag;
};


#endif // ! _MONSTERWIDGET_H_
