#pragma once
#include "Monster.h"

/**
 * @class CMonster_State
 * @brief 怪物状态基类
 * 
 *
 */
class CMonster_State
{
public:
	virtual void Update() {};
	virtual void InitState() {};

	
	/**
	 * @brief 返回当前绘制的资源图序号
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; };

	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @param  CMonster * monster	怪物对象指针
	 * @return    
	 */
	 CMonster_State(CMonster* monster);;
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 virtual ~CMonster_State() {};

protected:
	CMonster* m_Monster;	/**<  怪物对象指针*/
	int m_MatId;  /**<  资源的id*/
	clock_t m_Clock_PreUpdate; /**<  上一次更新的时间*/
	int m_AttackCnt;	/**<  被打计次*/
};

/**
 * @class CMonster_BeAttackedState
 * @brief 怪物被攻击状态
 * 
 *三种怪物被攻击状态都由都使用这个类实现
 */
class CMonster_BeAttackedState
	:public CMonster_State
{
public:
	CMonster_BeAttackedState(CMonster* monster):CMonster_State(monster) {};
	virtual void Update();
	virtual void InitState();
	
	/**
	 * @brief 切换为站立状态
	 * 
	 * 由子类实现
	 * @return  void  
	 */
	 virtual void SwitchStanding() = 0;
protected:
	int m_MatId1, m_MatId2; /**<  前三张和后三张资源图序号*/
	int m_MaxAttack; /**<  打几下强制落地*/
	int m_weight; /**<  怪物重量 越轻被击飞的越远  范围[0,5]*/
	int m_Clock_PreBeAttacked; /**<  上一次被攻击计时*/
};


