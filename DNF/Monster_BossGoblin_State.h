#pragma once
#include "Monster_State.h"

/**
 * @class CMonster_BossGoblin_StandingState
 * @brief 投掷哥布林站立状态
 * 
 *
 */
class CMonster_BossGoblin_StandingState
	:public CMonster_State
{
public:
	CMonster_BossGoblin_StandingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_BossGoblin_StandingState() {};
	void InitState();
	void Update();
};


/**
 * @class CMonster_BossGoblin_RunningState
 * @brief 投掷哥布林奔跑状态
 * 
 *
 */
class CMonster_BossGoblin_RunningState
	:public CMonster_State
{

public:
	CMonster_BossGoblin_RunningState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_BossGoblin_RunningState() {};
	void InitState();
	void Update();


};

/**
 * @class CMonster_BossGoblin_BeAttackedState
 * @brief 投掷哥布林被攻击状态
 * 
 *不重写基类Update方法，只设定怪物的属性值
 */
class CMonster_BossGoblin_BeAttackedState
	:public CMonster_BeAttackedState
{
public:
	CMonster_BossGoblin_BeAttackedState(CMonster* monster);
	~CMonster_BossGoblin_BeAttackedState() {};

	/**
	* @brief 切换为站立状态
	*
	*
	* @return  void
	*/
	void SwitchStanding();
};

/**
 * @class CMonster_BossGoblin_AttackingState
 * @brief 投掷哥布林攻击状态
 * 
 *
 */
class CMonster_BossGoblin_AttackingState
	:public CMonster_State
{
public:
	CMonster_BossGoblin_AttackingState(CMonster* monster) : CMonster_State(monster) {};
	~CMonster_BossGoblin_AttackingState() {};
	void InitState();
	void Update();
};