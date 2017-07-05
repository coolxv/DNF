#pragma once
#include "ObjectBase.h"
#include "AnimationEffect.h"

#define BODYIMGS 222

using namespace cv;
class CCharacterState;
class CGame;
class CCharacter
	:public CObjectBase
{
public:
	struct POINT
	{
		int x, y;
		POINT():x(0),y(0) {}
		POINT(int a, int b) :x(a), y(b) {}
	};
public:
	static const int s_NAttackSpeed = CHARACTER_ATTACKSPEED; //攻速
	static const int s_JumpN = 27;//跳跃力
	static const int s_Gravity = -1;
private:
	CCharacterState* m_State;
	int m_HP;
	int m_TotalHp;
	int m_MP;
	int m_MoveSpeed; //移动速度
	Mat m_Mat_Body[222], m_Mat_Body_Mask[222];
	Mat m_Mat_LBody[222], m_Mat_LBody_Mask[222];
	POINT m_Offset_LeftBottom[223], m_Offset_LeftBottom_Left[223]; //角色对应图片左下角偏移
	int m_StageWidth;  //当前所在场景的最大宽度	
	int m_ViewWidth, m_ViewHeight, m_OffsetY;
	bool m_IsAttacking = false;
	bool m_isBackJumping = false;
	std::vector<CAnimationEffect*>* m_Vector_AnimationEffects;
public:
	CCharacter();
	~CCharacter();
	CCharacterState* GetCurState() { return m_State; };
	void SetState(CCharacterState* p);
	std::vector<CAnimationEffect*>* GetAnimationEffects() { return m_Vector_AnimationEffects; }
	void SetAnimationEffectsVector(std::vector<CAnimationEffect*>* v) { m_Vector_AnimationEffects = v; }
	void DoRender(Mat& mat,int viewX);
	void DoHandleInput(int input);
	void UpdateState();
	void Move(int dir, double multiple = 1.0);
	int GetDamage(int effect, bool& crit);
	int GetArmor();
private:
	void __InitRec();
public://get/set
	int GetHp() { return m_HP; };
	int GetGravity() { return m_Gravity; };
	int GetZSpeed() { return m_ZSpeed; };
	int GetOrientation() { return m_Orientation; };
	int GetMoveDirection() { return m_MoveDirection; };
	int GetMovespeed() { return m_MoveSpeed; };
	int GetJumpDir() { return m_JumpDir; };
	Rect GetAttackRect();
	bool GetAttacking() { return m_IsAttacking; };
	bool GetBackJumping() { return m_isBackJumping; }
	int GetTotalHp() { return m_TotalHp; };
	int GetCurEffect(); //获取角色当前使用的技能

	void SetIsBackJumpint(bool is) { m_isBackJumping = is; }
	void SetAttacking(bool is) { m_IsAttacking = is; };
	bool SetX(int x) ;
	bool SetY(int y) ;
	bool SetZ(int z) ;
	void SetGravity(int gravity) { m_Gravity = gravity; };
	void SetZSpeed(int speed) { m_ZSpeed = speed; };
	void SetMovespeed(int speed) { m_MoveSpeed = speed; };
	void SetJumpDir(int dir) { m_JumpDir = dir; };
	void SetMoveDirection(int dir);
	void SetStageWidth(int width) { m_StageWidth = width; }
	void SetViewSize(int width, int height, int offsety) { m_ViewWidth = width; m_ViewHeight = height; m_OffsetY = offsety; }
	void SetHp(int hp);
};

