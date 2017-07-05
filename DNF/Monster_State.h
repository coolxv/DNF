#pragma once
#include "Monster.h"
class CMonster_State
{
public:
	virtual void Update() {};
	virtual void InitState() {};

	int GetMatId() { return m_MatId; };

	CMonster_State(CMonster* monster) { m_Monster = monster; m_AttackCnt = 0; };
	virtual ~CMonster_State() {};

protected:
	CMonster* m_Monster;
	int m_MatId; //资源的id
	int m_MatId_Add;
	clock_t m_Clock_PreUpdate; //上一次刷新
	clock_t m_Clock_PreRun;
	int m_AttackCnt;
};

class CMonster_BeAttackedState
	:public CMonster_State
{
public:
	CMonster_BeAttackedState(CMonster* monster):CMonster_State(monster) {};
	virtual void Update();
	virtual void InitState();
	virtual void SwitchStanding() = 0;
protected:
	int m_MatId1, m_MatId2; //前三张和后三张
	int m_MaxAttack; //打几下强制落地
	int m_weight; //越轻被击飞的越远  范围[0,5]

	int m_Clock_PreBeAttacked;
};


