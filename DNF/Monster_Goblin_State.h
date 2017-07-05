#pragma once
#include "Monster_State.h"

class CMonster_Goblin_StandingState
	:public CMonster_State
{
public:
	CMonster_Goblin_StandingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_StandingState() {};
	void InitState();
	void Update();
};

//////////////////////////////////////////////////////////////////////////
class CMonster_Goblin_BeAttackedState
	:public CMonster_BeAttackedState
{
public:
	CMonster_Goblin_BeAttackedState(CMonster* monster);
	~CMonster_Goblin_BeAttackedState() {};
	void SwitchStanding();
};

//////////////////////////////////////////////////////////////////////////
class CMonster_Goblin_RunningState
	:public CMonster_State
{
public:
	CMonster_Goblin_RunningState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_RunningState() {};
	void InitState();
	void Update();
};

//////////////////////////////////////////////////////////////////////////
class CMonster_Goblin_AttackingState
	:public CMonster_State
{
public:
	CMonster_Goblin_AttackingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_AttackingState() {};
	void InitState();
	void Update();

private:
	clock_t m_Clock_PreRun;
};