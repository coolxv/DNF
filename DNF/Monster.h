#pragma once
#include "ObjectBase.h"
#include "Stage.h"
class CMonster_State;

/**
 * @class CMonster
 * @brief �������
 * 
 *
 */
class CMonster
	:public CObjectBase
{
public:
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @return    
	 */
	 CMonster();
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 virtual ~CMonster();
	
	 /**
	 * @brief ������ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	 virtual void DoRender(Mat& mat, int viewX) = 0;
	
	/**
	 * @brief ����״̬
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void Update();
	
	/**
	 * @brief ���ع����ж�����
	 * 
	 * 
	 * @return  Rect  
	 */
	 virtual Rect GetAttackRect() = 0;
	
	/**
	 * @brief ��������˺�
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetDamage() = 0;
	
	/**
	 * @brief ���ع��ﻤ��
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetArmor() = 0;	
	
	/**
	 * @brief ���ع���ͷ��
	 * 
	 * 
	 * @return  cv::Mat  
	 */
	 virtual Mat GetAvator() = 0;
	
	/**
	 * @brief ���ع�������
	 * 
	 * 
	 * @return  cv::String  
	 */
	 virtual String GetName() = 0;

	
	/**
	 * @brief �ƶ�
	 * 
	 * 
	 * @param  int dir	����
	 * @param  double multiple	���루�ƶ������multiple����
	 * @return  void  
	 */
	 void Move(int dir, double multiple = 1.0);
	
	/**
	 * @brief ���ù����ƶ�����
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetMoveDirection(int dir);

	
	/**
	 * @brief �л�����״̬
	 * 
	 * 
	 * @param  CMonster_State * state	��Ҫ�л���״̬����ָ��
	 * @return  void  
	 */
	 void SetState(CMonster_State* state);
	
	/**
	 * @brief ���ع��ﵱǰ��״̬
	 * 
	 * 
	 * @return  CMonster_State*  
	 */
	 CMonster_State* GetCurState() { return m_State; };
	
	/**
	 * @brief ���ع��ﵱǰ���ڳ����Ķ���ָ��
	 * 
	 * 
	 * @return  CStage*  
	 */
	 CStage* GetStage();

	/**
	 * @brief ���ù���x����
	 * 
	 * 
	 * @param  int x
	 * @return  bool  x����Ƿ�����false
	 */
	 bool SetX(int x);

	 /**
	 * @brief ���ù���y����
	 *
	 *
	 * @param  int x
	 * @return  bool  x����Ƿ�����false
	 */
	bool SetY(int y);

	/**
	* @brief ���ù���z����
	*
	*
	* @param  int x
	* @return  bool  x����Ƿ�����false
	*/
	bool SetZ(int z);

	
	/**
	 * @brief ���ù��������
	 * 
	 * 
	 * @param  int gravity	����
	 * @return  void  
	 */
	 void SetGravity(int gravity);
	
	/**
	 * @brief ���ù��ﵱǰ����ֵ
	 * 
	 * 
	 * @param  int hp	����ֵ
	 * @return  void  
	 */
	 void SetHp(int hp);
	
	/**
	 * @brief ���ù���Ѫ������������ֵ
	 * 
	 * ����ʵ���ӳ���Ѫ����
	 * @param  int h Ѫ��
	 * @return  void  
	 */
	 void SetHp_Animation(int h);
	
	/**
	 * @brief ���ù����Ƿ�����
	 * 
	 * 
	 * @param  bool dead
	 * @return  void  
	 */
	 void SetDead(bool dead);
	
	/**
	 * @brief ���ù�����Ծ������ٶ�
	 * 
	 * 
	 * @param  int dir	����
	 * @param  int speed	�ٶ�
	 * @return  void  
	 */
	 void SetJumpDir(int dir,int speed);
	
	/**
	 * @brief ���ù���z���ٶ�
	 * 
	 * 
	 * @param  int speed	�ٶ�
	 * @return  void  
	 */
	 void SetZSpeed(int speed) { m_ZSpeed = speed; }
	
	/**
	 * @brief	���ù��ﵱǰ���Ƶ���Դ���
	 * 
	 * 
	 * @param  int id		��Դ���
	 * @return  void  
	 */
	 void SetMatId(int id) { m_MatId = id; }
	
	/**
	 * @brief ���ù����Ƿ�Ϊboss
	 * 
	 * 
	 * @param  bool is �Ƿ�Ϊboss
	 * @return  void  
	 */
	 void SetIsBoss(bool is) { m_isBoss = is; }
	
	/**
	 * @brief ���ù�����Ծ�ٶ�
	 * 
	 * 
	 * @param  int sp
	 * @return  void  
	 */
	 void SetJumpSpeed(int sp) { m_JumpSpeed = sp; }

	
	/**
	 * @brief ���ع�������
	 * 
	 * 
	 * @return  int  
	 */
	 int GetGravity() { return m_Gravity; }
	
	/**
	 * @brief ���ع��ﵱǰ����ֵ
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp() { return m_Hp; }
	
	/**
	 * @brief ���ع���Ѫ����������ֵ
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp_Animation() { return m_Hp_Animation; }
	
	/**
	 * @brief ���ع����Ƿ�����
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetDead() { return m_IsDead; }
	
	/**
	 * @brief ���ع�����Ծ����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpDir() { return m_JumpDir; }
	
	/**
	 * @brief ���ع���z���ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZSpeed() { return m_ZSpeed; }
	
	/**
	 * @brief ���ع��ﵱǰ���Ƶ���Դ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; }
	
	/**
	 * @brief ���ع��ﵱǰ�ĳ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetOrientation() { return m_Orientation; }
	
	/**
	 * @brief ���ع�����ƶ�����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveDirection() { return m_MoveDirection; }
	
	/**
	 * @brief ���ع�����ƶ��ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveSpeed() { return m_MoveSpeed; }
	
	/**
	 * @brief ���ع���Ĺ����ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetNAttackSpeed() { return m_NAttackSpeed; }
	
	/**
	 * @brief ���ع���Ĺ���Ƶ��
	 * 
	 * 
	 * @return  int  
	 */
	 int GetAttackFrequency() { return m_AttackFrequency; }
	
	/**
	 * @brief	���ظù����Ƿ�Ϊboss
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetIsBoss() { return m_isBoss; }
	
	/**
	 * @brief ������Ծ�ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpSpeed() { return m_JumpSpeed; }
protected:
	int m_MoveSpeed; /**<  �ƶ��ٶ�*/
	int m_JumpSpeed ;	/**<  ��Ծ�ٶ�*/
	bool m_IsDead = false; /**<  �Ƿ�����*/
	int m_NAttackSpeed;  /**<  ���� */
	int m_AttackFrequency; /**<  ����Ƶ�� */

	int m_Hp; /**<  ����ֵ */
	int m_Hp_Animation; /**< �������� ʵ����Ѫ����Ч�� */
	CMonster_State* m_State = NULL;	/**<  ���ﵱǰ״̬ */
	CStage* m_Stage;	/**<  �������ڳ�������ָ�� */
	int m_TotalHp;	/**< ������������ֵ */
	int m_MatId;/**<  ���ﵱǰ������Դ��� */
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask;/**<  ������Դͼ*/
	bool m_isBoss;/**<  �����Ƿ�Ϊboss*/
};
