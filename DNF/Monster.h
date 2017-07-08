#pragma once
#include "ObjectBase.h"
#include "Stage.h"
class CMonster_State;

/**
 * @class CMonster
 * @brief 怪物基类
 * 
 *
 */
class CMonster
	:public CObjectBase
{
public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @return    
	 */
	 CMonster();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 virtual ~CMonster();
	
	 /**
	 * @brief 纯虚绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	 virtual void DoRender(Mat& mat, int viewX) = 0;
	
	/**
	 * @brief 更新状态
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void Update();
	
	/**
	 * @brief 返回攻击判定矩阵
	 * 
	 * 
	 * @return  Rect  
	 */
	 virtual Rect GetAttackRect() = 0;
	
	/**
	 * @brief 计算怪物伤害
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetDamage() = 0;
	
	/**
	 * @brief 返回怪物护甲
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetArmor() = 0;	
	
	/**
	 * @brief 返回怪物头像
	 * 
	 * 
	 * @return  cv::Mat  
	 */
	 virtual Mat GetAvator() = 0;
	
	/**
	 * @brief 返回怪物名称
	 * 
	 * 
	 * @return  cv::String  
	 */
	 virtual String GetName() = 0;

	
	/**
	 * @brief 移动
	 * 
	 * 
	 * @param  int dir	方向
	 * @param  double multiple	距离（移动距离的multiple倍）
	 * @return  void  
	 */
	 void Move(int dir, double multiple = 1.0);
	
	/**
	 * @brief 设置怪物移动方向
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetMoveDirection(int dir);

	
	/**
	 * @brief 切换怪物状态
	 * 
	 * 
	 * @param  CMonster_State * state	需要切换的状态对象指针
	 * @return  void  
	 */
	 void SetState(CMonster_State* state);
	
	/**
	 * @brief 返回怪物当前的状态
	 * 
	 * 
	 * @return  CMonster_State*  
	 */
	 CMonster_State* GetCurState() { return m_State; };
	
	/**
	 * @brief 返回怪物当前所在场景的对象指针
	 * 
	 * 
	 * @return  CStage*  
	 */
	 CStage* GetStage();

	/**
	 * @brief 设置怪物x坐标
	 * 
	 * 
	 * @param  int x
	 * @return  bool  x坐标非法返回false
	 */
	 bool SetX(int x);

	 /**
	 * @brief 设置怪物y坐标
	 *
	 *
	 * @param  int x
	 * @return  bool  x坐标非法返回false
	 */
	bool SetY(int y);

	/**
	* @brief 设置怪物z坐标
	*
	*
	* @param  int x
	* @return  bool  x坐标非法返回false
	*/
	bool SetZ(int z);

	
	/**
	 * @brief 设置怪物的重力
	 * 
	 * 
	 * @param  int gravity	重力
	 * @return  void  
	 */
	 void SetGravity(int gravity);
	
	/**
	 * @brief 设置怪物当前生命值
	 * 
	 * 
	 * @param  int hp	生命值
	 * @return  void  
	 */
	 void SetHp(int hp);
	
	/**
	 * @brief 设置怪物血条动画的生命值
	 * 
	 * 用于实现延迟流血动画
	 * @param  int h 血量
	 * @return  void  
	 */
	 void SetHp_Animation(int h);
	
	/**
	 * @brief 设置怪物是否死亡
	 * 
	 * 
	 * @param  bool dead
	 * @return  void  
	 */
	 void SetDead(bool dead);
	
	/**
	 * @brief 设置怪物跳跃方向和速度
	 * 
	 * 
	 * @param  int dir	方向
	 * @param  int speed	速度
	 * @return  void  
	 */
	 void SetJumpDir(int dir,int speed);
	
	/**
	 * @brief 设置怪物z轴速度
	 * 
	 * 
	 * @param  int speed	速度
	 * @return  void  
	 */
	 void SetZSpeed(int speed) { m_ZSpeed = speed; }
	
	/**
	 * @brief	设置怪物当前绘制的资源序号
	 * 
	 * 
	 * @param  int id		资源序号
	 * @return  void  
	 */
	 void SetMatId(int id) { m_MatId = id; }
	
	/**
	 * @brief 设置怪物是否为boss
	 * 
	 * 
	 * @param  bool is 是否为boss
	 * @return  void  
	 */
	 void SetIsBoss(bool is) { m_isBoss = is; }
	
	/**
	 * @brief 设置怪物跳跃速度
	 * 
	 * 
	 * @param  int sp
	 * @return  void  
	 */
	 void SetJumpSpeed(int sp) { m_JumpSpeed = sp; }

	
	/**
	 * @brief 返回怪物重力
	 * 
	 * 
	 * @return  int  
	 */
	 int GetGravity() { return m_Gravity; }
	
	/**
	 * @brief 返回怪物当前生命值
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp() { return m_Hp; }
	
	/**
	 * @brief 返回怪物血条动画生命值
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp_Animation() { return m_Hp_Animation; }
	
	/**
	 * @brief 返回怪物是否死亡
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetDead() { return m_IsDead; }
	
	/**
	 * @brief 返回怪物跳跃方向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpDir() { return m_JumpDir; }
	
	/**
	 * @brief 返回怪物z轴速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZSpeed() { return m_ZSpeed; }
	
	/**
	 * @brief 返回怪物当前绘制的资源序号
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMatId() { return m_MatId; }
	
	/**
	 * @brief 返回怪物当前的朝向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetOrientation() { return m_Orientation; }
	
	/**
	 * @brief 返回怪物的移动方向
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveDirection() { return m_MoveDirection; }
	
	/**
	 * @brief 返回怪物的移动速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveSpeed() { return m_MoveSpeed; }
	
	/**
	 * @brief 返回怪物的攻击速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetNAttackSpeed() { return m_NAttackSpeed; }
	
	/**
	 * @brief 返回怪物的攻击频率
	 * 
	 * 
	 * @return  int  
	 */
	 int GetAttackFrequency() { return m_AttackFrequency; }
	
	/**
	 * @brief	返回该怪物是否为boss
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetIsBoss() { return m_isBoss; }
	
	/**
	 * @brief 返回跳跃速度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpSpeed() { return m_JumpSpeed; }
protected:
	int m_MoveSpeed; /**<  移动速度*/
	int m_JumpSpeed ;	/**<  跳跃速度*/
	bool m_IsDead = false; /**<  是否死亡*/
	int m_NAttackSpeed;  /**<  攻速 */
	int m_AttackFrequency; /**<  攻击频率 */

	int m_Hp; /**<  生命值 */
	int m_Hp_Animation; /**< 生命动画 实现流血动画效果 */
	CMonster_State* m_State = NULL;	/**<  怪物当前状态 */
	CStage* m_Stage;	/**<  怪物所在场景对象指针 */
	int m_TotalHp;	/**< 怪物的最大生命值 */
	int m_MatId;/**<  怪物当前绘制资源序号 */
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask;/**<  怪物资源图*/
	bool m_isBoss;/**<  怪物是否为boss*/
};
