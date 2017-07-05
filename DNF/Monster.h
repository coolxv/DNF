#pragma once
#include "ObjectBase.h"
#include "Stage.h"
class CMonster_State;
class CMonster
	:public CObjectBase
{
public:
	CMonster();
	virtual ~CMonster();
	virtual void DoRender(Mat& mat, int viewX) = 0;
	virtual void Update();
	virtual Rect GetAttackRect() = 0;
	virtual int GetDamage() = 0;
	virtual int GetArmor() = 0;	
	virtual Mat GetAvator() = 0;
	virtual String GetName() = 0;

	void Move(int dir, double multiple = 1.0);
	void SetMoveDirection(int dir);

	void SetState(CMonster_State* state);
	CMonster_State* GetCurState() { return m_State; };
	CStage* GetStage();

	bool SetX(int x);
	bool SetY(int y);
	bool SetZ(int z);

	void SetGravity(int gravity);
	void SetHp(int hp);
	void SetHp_Animation(int h);
	void SetDead(bool dead);
	void SetJumpDir(int dir,int speed);
	void SetZSpeed(int speed) { m_ZSpeed = speed; }
	void SetMatId(int id) { m_MatId = id; }
	void SetIsBoss(bool is) { m_isBoss = is; }
	void SetJumpSpeed(int sp) { m_JumpSpeed = sp; }

	int GetGravity() { return m_Gravity; }
	int GetHp() { return m_Hp; }
	int GetHp_Animation() { return m_Hp_Animation; }
	bool GetDead() { return m_IsDead; }
	int GetJumpDir() { return m_JumpDir; }
	int GetZSpeed() { return m_ZSpeed; }
	int GetMatId() { return m_MatId; }
	int GetOrientation() { return m_Orientation; }
	int GetMoveDirection() { return m_MoveDirection; }
	int GetMoveSpeed() { return m_MoveSpeed; }
	int GetNAttackSpeed() { return m_NAttackSpeed; }
	int GetAttackFrequency() { return m_AttackFrequency; }
	bool GetIsBoss() { return m_isBoss; }
	int GetJumpSpeed() { return m_JumpSpeed; }
protected:
	int m_MoveSpeed; //移动速度
	int m_JumpSpeed = 0;
	bool m_IsDead = false;
	int m_NAttackSpeed; //攻速
	int m_AttackFrequency; //攻击频率

	int m_Hp;
	int m_Hp_Animation; //实现流血动画效果
	CMonster_State* m_State = NULL;
	CStage* m_Stage;
	int m_TotalHp;
	int m_MatId;
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask;
	bool m_isBoss;
};
