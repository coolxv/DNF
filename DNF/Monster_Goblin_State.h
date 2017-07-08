#pragma once
#include "Monster_State.h"

/**
 * @class CMonster_Goblin_StandingState
 * @brief 哥布林站立状态
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
* @brief 哥布林被攻击状态
*
 *不重写基类Update方法，只设定怪物的属性值
*/
class CMonster_Goblin_BeAttackedState
	:public CMonster_BeAttackedState
{
public:
	CMonster_Goblin_BeAttackedState(CMonster* monster);
	~CMonster_Goblin_BeAttackedState() {};

	/**
	* @brief 切换为站立状态
	*
	*
	* @return  void
	*/
	void SwitchStanding();
};

/**
 * @class CMonster_Goblin_RunningState
 * @brief 哥布林奔跑状态
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
 * @brief 哥布林攻击状态
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