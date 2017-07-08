#pragma once
#include "Character.h"

/**
 * @class CCharacterState
 * @brief ��ɫ״̬����
 * 
 *����һЩ״̬�ӿڣ�ʵ��״̬ί��
 */
class CCharacterState
{
public:
	
	/**
	 * @brief �����������
	 * 
	 * ��Ҫ����״̬���л�
	 * @param  CCharacter & character	��ɫ����ָ��
	 * @param  int input	��ֵ
	 * @return  void  
	 */
	virtual void DoHandleInput(CCharacter& character, int input) = 0;
	
	/**
	 * @brief ����״̬
	 * 
	 * ��Ҫ���ڸ��½�ɫ����
	 * @param  CCharacter & character ��ɫ����ָ��
	 * @return  void  
	 */
	 virtual void UpdateState(CCharacter& character) = 0;
	 
	 /**
	  * @brief ��ʼ��״̬
	  * 
	  * 
	  * @param  CCharacter & character	��ɫ����ָ��
	  * @return  void  
	  */
	 virtual void InitState(CCharacter& character) = 0;

	
	/**
	 * @brief ���ص�ǰ��Ҫ���Ƶ���Դͼ�����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; };

	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @return    
	 */
	 CCharacterState();
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CCharacterState();

protected:
	int m_MatId; /**<  ��Դͼ��� */
	int m_MatId_Add;	/**<  ÿ�θ�����Դͼ��ŵ����� */
	clock_t m_Clock_PreUpdate; /**<  ��һ�θ���״̬��ʱ�� */
	clock_t m_Clock_PreKey; /**<  ��һ�δ����������ʱ�� */
};

/**
 * @class CharacterWalkintState
 * @brief ��ɫ����״̬
 * 
 *
 */
class CharacterWalkintState :
	public CCharacterState
{
public:
	CharacterWalkintState() {};
	~CharacterWalkintState() {};

	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);

private:
	clock_t m_Clock_StartWalk;	/**<  ��ʼ���ߵ�ʱ�� */
	clock_t m_Clock_PreWalk;	/**<  ��һ�����ߵ�ʱ�� */
};

/**
 * @class CharacterRunningState
 * @brief ��ɫ����״̬
 * 
 *
 */
class CharacterRunningState :
	public CCharacterState
{
public:
	CharacterRunningState();
	~CharacterRunningState();

	void DoHandleInput(CCharacter& character, int input) ;
	void UpdateState(CCharacter& character) ;
	void InitState(CCharacter& character);
private:
	clock_t m_clock_PreRun;	/**<  ��һ�α��ܸı�λ�õ�ʱ�� */
};

/**
 * @class CharacterStandingState
 * @brief ��ɫվ��״̬
 * 
 *
 */
class CharacterStandingState :
	public CCharacterState
{
public:
	CharacterStandingState();
	~CharacterStandingState();

	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character); 
	void InitState(CCharacter& character);
private:
	int m_AnimationCount = 0; /**< ����1�ƴΣ� ����1����3�βŲ��Ŷ���2 */
};

/**
 * @class CharacterNormalAttackingState
 * @brief ��ɫ��ͨ����״̬
 * 
 *
 */
class CharacterNormalAttackingState :
	public CCharacterState
{
public:

	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
};

/**
 * @class CharacterJumpingState
 * @brief ��ɫ��Ծ״̬
 * 
 *
 */
class CharacterJumpingState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
private:
	clock_t m_Clock_PreJumpMove; /**<  ��һ������Ծ���ƶ���ʱ�� */
};

/**
 * @class CharacterBeAttackState
 * @brief ��ɫ������״̬
 * 
 *
 */
class CharacterBeAttackState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
private:
	int m_cnt;		/**<  �������ƴ� */
	bool m_Fell;		/**< ��ɫ�Ƿ񵹵� */
};

/**
 * @class CharacterZEffectingState
 * @brief ��ɫz����״̬
 * 
 *
 */
class CharacterZEffectingState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
};

/**
 * @class CharacterSEffectingState
 * @brief ��ɫs����״̬
 * 
 *
 */
class CharacterSEffectingState
	:public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);

};

/**
* @class CharacterDEffectingState
* @brief ��ɫd����״̬
*
*
*/
class CharacterDEffectingState
	:public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);

};

/**
 * @class CharacterDeadState
 * @brief ��ɫ����״̬
 * 
 *
 */
class CharacterDeadState
	:public CCharacterState
{
public:
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
	void DoHandleInput(CCharacter& character, int input);
};

static CharacterRunningState s_Running;	/**<  ����״̬ */
static CharacterWalkintState s_Walking;		/**<  ����״̬ */
static CharacterStandingState s_Standing;	/**<  վ��״̬ */
static CharacterNormalAttackingState s_NAttacking;	/**<  ��ͨ����״̬ */
static CharacterJumpingState s_Jumping;	/**<  ��Ծ״̬ */
static CharacterZEffectingState s_Effecting;	/**< z����״̬ */
static CharacterBeAttackState s_BeAttacked;	/**<  ������״̬ */
static CharacterSEffectingState s_SEffecting;	/**<  s����״̬ */
static CharacterDEffectingState s_DEffecting;	/**<  d����״̬ */
static CharacterDeadState s_Dead;	/**<  ����״̬*/