#pragma once
#include "Monster.h"

/**
 * @class CMonster_State
 * @brief ����״̬����
 * 
 *
 */
class CMonster_State
{
public:
	virtual void Update() {};
	virtual void InitState() {};

	
	/**
	 * @brief ���ص�ǰ���Ƶ���Դͼ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; };

	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @param  CMonster * monster	�������ָ��
	 * @return    
	 */
	 CMonster_State(CMonster* monster);;
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 virtual ~CMonster_State() {};

protected:
	CMonster* m_Monster;	/**<  �������ָ��*/
	int m_MatId;  /**<  ��Դ��id*/
	clock_t m_Clock_PreUpdate; /**<  ��һ�θ��µ�ʱ��*/
	int m_AttackCnt;	/**<  ����ƴ�*/
};

/**
 * @class CMonster_BeAttackedState
 * @brief ���ﱻ����״̬
 * 
 *���ֹ��ﱻ����״̬���ɶ�ʹ�������ʵ��
 */
class CMonster_BeAttackedState
	:public CMonster_State
{
public:
	CMonster_BeAttackedState(CMonster* monster):CMonster_State(monster) {};
	virtual void Update();
	virtual void InitState();
	
	/**
	 * @brief �л�Ϊվ��״̬
	 * 
	 * ������ʵ��
	 * @return  void  
	 */
	 virtual void SwitchStanding() = 0;
protected:
	int m_MatId1, m_MatId2; /**<  ǰ���źͺ�������Դͼ���*/
	int m_MaxAttack; /**<  ����ǿ�����*/
	int m_weight; /**<  �������� Խ�ᱻ���ɵ�ԽԶ  ��Χ[0,5]*/
	int m_Clock_PreBeAttacked; /**<  ��һ�α�������ʱ*/
};


