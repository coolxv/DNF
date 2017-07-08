#pragma once
#include "Character.h"

/**
 * @class CCharacterState
 * @brief 角色状态基类
 * 
 *声明一些状态接口，实现状态委托
 */
class CCharacterState
{
public:
	
	/**
	 * @brief 处理键盘输入
	 * 
	 * 主要用于状态的切换
	 * @param  CCharacter & character	角色对象指针
	 * @param  int input	键值
	 * @return  void  
	 */
	virtual void DoHandleInput(CCharacter& character, int input) = 0;
	
	/**
	 * @brief 更新状态
	 * 
	 * 主要用于更新角色绘制
	 * @param  CCharacter & character 角色对象指针
	 * @return  void  
	 */
	 virtual void UpdateState(CCharacter& character) = 0;
	 
	 /**
	  * @brief 初始化状态
	  * 
	  * 
	  * @param  CCharacter & character	角色对象指针
	  * @return  void  
	  */
	 virtual void InitState(CCharacter& character) = 0;

	
	/**
	 * @brief 返回当前需要绘制的资源图的序号
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; };

	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @return    
	 */
	 CCharacterState();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CCharacterState();

protected:
	int m_MatId; /**<  资源图序号 */
	int m_MatId_Add;	/**<  每次更新资源图序号的增量 */
	clock_t m_Clock_PreUpdate; /**<  上一次更新状态的时间 */
	clock_t m_Clock_PreKey; /**<  上一次处理按键输入的时间 */
};

/**
 * @class CharacterWalkintState
 * @brief 角色行走状态
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
	clock_t m_Clock_StartWalk;	/**<  开始行走的时间 */
	clock_t m_Clock_PreWalk;	/**<  上一次行走的时间 */
};

/**
 * @class CharacterRunningState
 * @brief 角色奔跑状态
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
	clock_t m_clock_PreRun;	/**<  上一次奔跑改变位置的时间 */
};

/**
 * @class CharacterStandingState
 * @brief 角色站立状态
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
	int m_AnimationCount = 0; /**< 动画1计次， 动画1播放3次才播放动画2 */
};

/**
 * @class CharacterNormalAttackingState
 * @brief 角色普通攻击状态
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
 * @brief 角色跳跃状态
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
	clock_t m_Clock_PreJumpMove; /**<  上一次在跳跃中移动的时间 */
};

/**
 * @class CharacterBeAttackState
 * @brief 角色被攻击状态
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
	int m_cnt;		/**<  被攻击计次 */
	bool m_Fell;		/**< 角色是否倒地 */
};

/**
 * @class CharacterZEffectingState
 * @brief 角色z技能状态
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
 * @brief 角色s技能状态
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
* @brief 角色d技能状态
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
 * @brief 角色死亡状态
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

static CharacterRunningState s_Running;	/**<  奔跑状态 */
static CharacterWalkintState s_Walking;		/**<  行走状态 */
static CharacterStandingState s_Standing;	/**<  站立状态 */
static CharacterNormalAttackingState s_NAttacking;	/**<  普通攻击状态 */
static CharacterJumpingState s_Jumping;	/**<  跳跃状态 */
static CharacterZEffectingState s_Effecting;	/**< z技能状态 */
static CharacterBeAttackState s_BeAttacked;	/**<  被攻击状态 */
static CharacterSEffectingState s_SEffecting;	/**<  s技能状态 */
static CharacterDEffectingState s_DEffecting;	/**<  d技能状态 */
static CharacterDeadState s_Dead;	/**<  死亡状态*/