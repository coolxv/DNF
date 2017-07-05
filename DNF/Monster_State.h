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
	int m_MatId; //��Դ��id
	int m_MatId_Add;
	clock_t m_Clock_PreUpdate; //��һ��ˢ��
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
	int m_MatId1, m_MatId2; //ǰ���źͺ�����
	int m_MaxAttack; //����ǿ�����
	int m_weight; //Խ�ᱻ���ɵ�ԽԶ  ��Χ[0,5]

	int m_Clock_PreBeAttacked;
};


