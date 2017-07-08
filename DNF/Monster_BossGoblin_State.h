#pragma once
#include "Monster_State.h"

/**
 * @class CMonster_BossGoblin_StandingState
 * @brief Ͷ���粼��վ��״̬
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
 * @brief Ͷ���粼�ֱ���״̬
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
 * @brief Ͷ���粼�ֱ�����״̬
 * 
 *����д����Update������ֻ�趨���������ֵ
 */
class CMonster_BossGoblin_BeAttackedState
	:public CMonster_BeAttackedState
{
public:
	CMonster_BossGoblin_BeAttackedState(CMonster* monster);
	~CMonster_BossGoblin_BeAttackedState() {};

	/**
	* @brief �л�Ϊվ��״̬
	*
	*
	* @return  void
	*/
	void SwitchStanding();
};

/**
 * @class CMonster_BossGoblin_AttackingState
 * @brief Ͷ���粼�ֹ���״̬
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