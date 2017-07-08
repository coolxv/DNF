#pragma once
#include "ObjectBase.h"
#include "AnimationEffect.h"

/** @brief  角色资源图数量 */
#define BODYIMGS 222

using namespace cv;
class CCharacterState;
class CGame;

/**
 * @class CCharacter
 * @brief 主角类
 * 
 *角色的各种属性，方法
 */
class CCharacter
	:public CObjectBase
{
private:
	int m_HP; /**<  当前的生命值 */
	int m_MP; /**<  当前的法力值 */
	bool m_Dead;	/**<  角色是否死亡 */
	int m_MoveSpeed; /**<  移动速度 */
	int m_StageWidth;  /**<  当前所在场景的最大宽度	 */
	bool m_IsAttacking;		/**<  角色当前是否在攻击 */
	bool m_isBackJumping;	/**<  是否在后跳 */
	clock_t m_PreReplyHpMp;	/**<  上一次回复的时间 */
	CCharacterState* m_State;	/**<  角色当前的状态 */
	int m_ViewWidth, m_ViewHeight, m_OffsetY;	 /**<  */
	Mat m_Mat_Body[222], m_Mat_Body_Mask[222];	/**<  角色资源图 */
	Mat m_Mat_LBody[222], m_Mat_LBody_Mask[222];	/**<  角色资源图 */
	std::vector<CAnimationEffect*>* m_Vector_AnimationEffects; /**<  动画特效容器 */
	Point m_Offset_LeftBottom[223], m_Offset_LeftBottom_Left[223]; /**<  资源图漂移量 */
	clock_t m_PreEffect_Z, m_PreEffect_A, m_PreEffect_S, m_PreEffect_D;	/**<  上一次使用技能的时间 */
public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @return    
	 */
	 CCharacter();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CCharacter();
	
	/**
	 * @brief 返回角色当前的状态
	 * 
	 * 
	 * @return  CCharacterState*  
	 */
	 CCharacterState* GetCurState();;
	
	/**
	 * @brief 切换状态
	 * 
	 * 
	 * @param  CCharacterState * p 需要切换的状态
	 * @return  void  
	 */
	 void SetState(CCharacterState* p);
	
	/**
	 * @brief 设置动画容器对象
	 * 
	 * 用于角色技能动画
	 * @param  std::vector<CAnimationEffect * > * v 容器指针
	 * @return  void  
	 */
	 void SetAnimationEffectsVector(std::vector<CAnimationEffect*>* v);
	
	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	 void DoRender(Mat& mat,int viewX);
	
	/**
	 * @brief 处理键盘输入事件
	 * 
	 * 
	 * @param  int input	键值
	 * @return  void  
	 */
	 void DoHandleInput(int input);
	
	/**
	 * @brief 更新角色状态属性
	 * 
	 * 
	 * @return  void  
	 */
	 void UpdateState();
	
	/**
	 * @brief 角色移动
	 * 
	 * 
	 * @param  int dir 移动方向
	 * @param  double multiple	移动距离（移动速度的multiple倍）
	 * @return  void  
	 */
	 void Move(int dir, double multiple = 1.0);
	
	/**
	 * @brief 计算伤害值
	 * 
	 * 
	 * @param  int effect 技能
	 * @param  bool & crit	是否暴击回调参数
	 * @return  int  返回伤害值
	 */
	 int GetDamage(int effect, bool& crit);
	
	/**
	 * @brief 返回角色的护甲
	 * 
	 * 
	 * @return  int  
	 */
	 int GetArmor();
	
	/**
	 * @brief 返回动画容器对象指针
	 * 
	 * 
	 * @return  std::vector<CAnimationEffect*>*  
	 */
	 std::vector<CAnimationEffect*>* GetAnimationEffects();

	static const int s_JumpN = 27; /**< 跳跃力 */
	static const int s_Gravity = -1;		/**<  重力 */
private:
	
	/**
	 * @brief 初始化资源
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitRec();
public://get/set
	
	/**
	 * @brief 返回角色是否死亡
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetDead() { return m_Dead; }
	
	/**
	 * @brief 返回角色生命值
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp() { return m_HP; };
	
	/**
	 * @brief 返回角色法力值
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMp() { return m_MP; }
	
	/**
	 * @brief 返回角色的重力
	 * 
	 * 
	 * @return  int  
	 */
	 int GetGravity() { return m_Gravity; };
	
	/**
	 * @brief 返回角色的z轴速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZSpeed() { return m_ZSpeed; };
	
	/**
	 * @brief 返回角色朝向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetOrientation() { return m_Orientation; };
	
	/**
	 * @brief 返回角色移动方向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveDirection() { return m_MoveDirection; };
	
	/**
	 * @brief 返回角色移动速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMovespeed() { return m_MoveSpeed; };
	
	/**
	 * @brief 返回角色跳跃方向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpDir() { return m_JumpDir; };
	
	/**
	 * @brief 返回角色攻击碰撞矩形
	 * 
	 * 
	 * @return  Rect  
	 */
	 Rect GetAttackRect();
	
	/**
	 * @brief 返回角色是否在攻击
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetAttacking() { return m_IsAttacking; };
	
	/**
	 * @brief 返回角色是否在后跳
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetBackJumping() { return m_isBackJumping; }
	
	/**
	 * @brief 返回角色当前使用的技能
	 * 
	 * 
	 * @return  int  
	 */
	 int GetCurEffect(); //获取角色当前使用的技能
	
	/**
	 * @brief 返回上一次使用A技能的时间
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreEffectA() { return m_PreEffect_A; }

	 /**
	 * @brief 返回上一次使用S技能的时间
	 *
	 *
	 * @return  clock_t
	 */
	clock_t GetPreEffectS() { return m_PreEffect_S; }

	/**
	* @brief 返回上一次使用D技能的时间
	*
	*
	* @return  clock_t
	*/
	clock_t GetPreEffectD() { return m_PreEffect_D; }

	/**
	* @brief 返回上一次使用Z技能的时间
	*
	*
	* @return  clock_t
	*/
	clock_t GetPreEffectZ() { return m_PreEffect_Z; }

	/**
	 * @brief 设置上一次使用Z技能的时间
	 * 
	 * 
	 * @param  clock_t a
	 * @return  void  
	 */
	 void SetPreEffectA(clock_t a) { m_PreEffect_A = a; }

	 /**
	 * @brief 设置上一次使用S技能的时间
	 *
	 *
	 * @param  clock_t a
	 * @return  void
	 */
	void SetPreEffectS(clock_t s) { m_PreEffect_S = s; }

	/**
	* @brief 设置上一次使用D技能的时间
	*
	*
	* @param  clock_t s
	* @return  void
	*/
	void SetPreEffectD(clock_t d) { m_PreEffect_D = d; }

	/**
	* @brief 设置上一次使用Z技能的时间
	*
	*
	* @param  clock_t d
	* @return  void
	*/
	void SetPreEffectZ(clock_t z) { m_PreEffect_Z = z; }

	/**
	* @brief 设置上一次使用后跳的时间
	*
	*
	* @param  clock_t z
	* @return  void
	*/
	void SetIsBackJumpint(bool is) { m_isBackJumping = is; }

	/**
	 * @brief 设置角色当前是否在攻击
	 * 
	 * 
	 * @param  bool is
	 * @return  void  
	 */
	 void SetAttacking(bool is) { m_IsAttacking = is; };

	/**
	* @brief 设置角色的重力值
	*
	*
	* @param  int gravity 重力
	* @return  void
	*/
	void SetGravity(int gravity) { m_Gravity = gravity; };

	/**
	 * @brief 设置角色的z轴速度
	 * 
	 * 
	 * @param  int speed
	 * @return  void  
	 */
	 void SetZSpeed(int speed) { m_ZSpeed = speed; };
	
	/**
	 * @brief 设置角色的移动速度
	 * 
	 * 
	 * @param  int speed
	 * @return  void  
	 */
	 void SetMovespeed(int speed) { m_MoveSpeed = speed; };
	
	/**
	 * @brief 设置角色的跳跃方向
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetJumpDir(int dir) { m_JumpDir = dir; };
	
	/**
	 * @brief 设置角色的移动方向
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetMoveDirection(int dir);
	
	/**
	 * @brief 设置角色所在场景的宽度
	 * 
	 * 
	 * @param  int width
	 * @return  void  
	 */
	 void SetStageWidth(int width) { m_StageWidth = width; }
	
	/**
	 * @brief 设置角色的所在画面的参数
	 * 
	 * 
	 * @param  int width 宽度
	 * @param  int height	高度
	 * @param  int offsety	y轴偏移
	 * @return  void  
	 */
	 void SetViewSize(int width, int height, int offsety) { m_ViewWidth = width; m_ViewHeight = height; m_OffsetY = offsety; }
	
	/**
	 * @brief 设置角色是否死亡
	 * 
	 * 
	 * @param  bool is
	 * @return  void  
	 */
	 void SetDead(bool is) { m_Dead = is; }
	
	/**
	 * @brief 设置角色x坐标
	 * 
	 * 
	 * @param  int x
	 * @return  bool  
	 */
	 bool SetX(int x);
	
	/**
	 * @brief 设置角色y坐标
	 * 
	 * 
	 * @param  int y
	 * @return  bool  
	 */
	 bool SetY(int y);
	
	/**
	 * @brief 设置角色z坐标
	 * 
	 * 
	 * @param  int z
	 * @return  bool  
	 */
	 bool SetZ(int z);
	
	/**
	 * @brief 设置角色生命值
	 * 
	 * 
	 * @param  int hp
	 * @return  void  
	 */
	 void SetHp(int hp);
	
	/**
	 * @brief 设置角色法力值
	 * 
	 * 
	 * @param  int mp
	 * @return  void  
	 */
	 void SetMp(int mp);
};

