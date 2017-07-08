#pragma once
#include "Monster_State.h"

/**
 * @class CMonster_Goblin_StandingState
 * @brief �粼��վ��״̬
 * 
 *
 */
class CMonster_Goblin_StandingState
	:public CMonster_State
{
public:
	CMonster_Goblin_StandingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_StandingState() {};
	void InitState();
	void Update();
};

/**
* @class CMonster_Goblin_BeAttackedState
* @brief �粼�ֱ�����״̬
*
 *����д����Update������ֻ�趨���������ֵ
*/
class CMonster_Goblin_BeAttackedState
	:public CMonster_BeAttackedState
{
public:
	CMonster_Goblin_BeAttackedState(CMonster* monster);
	~CMonster_Goblin_BeAttackedState() {};

	/**
	* @brief �л�Ϊվ��״̬
	*
	*
	* @return  void
	*/
	void SwitchStanding();
};

/**
 * @class CMonster_Goblin_RunningState
 * @brief �粼�ֱ���״̬
 * 
 *
 */
class CMonster_Goblin_RunningState
	:public CMonster_State
{
public:
	CMonster_Goblin_RunningState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_RunningState() {};
	void InitState();
	void Update();
};

/**
 * @class CMonster_Goblin_AttackingState
 * @brief �粼�ֹ���״̬
 * 
 *
 */
class CMonster_Goblin_AttackingState
	:public CMonster_State
{
public:
	CMonster_Goblin_AttackingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_Goblin_AttackingState() {};
	void InitState();
	void Update();
};