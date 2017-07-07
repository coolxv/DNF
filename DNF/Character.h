#pragma once
#include "ObjectBase.h"
#include "AnimationEffect.h"

#define BODYIMGS 222

using namespace cv;
class CCharacterState;
class CGame;

/**
 * @class	CCharacter
 * @brief ��Ҳ��ݵĽ�ɫ 
 * 
 *
 */
class CCharacter
	:public CObjectBase
{
private:
	struct POINT
	{
		int x, y;
		POINT() :x(0), y(0) {}
		POINT(int a, int b) :x(a), y(b) {}
	};
	CCharacterState* m_State;
	int m_HP; ///< Ѫ��
	int m_MP; /**< ���� */
	int m_MoveSpeed; //�ƶ��ٶ�
	Mat m_Mat_Body[222], m_Mat_Body_Mask[222];
	Mat m_Mat_LBody[222], m_Mat_LBody_Mask[222];
	POINT m_Offset_LeftBottom[223], m_Offset_LeftBottom_Left[223]; //��ɫ��ӦͼƬ���½�ƫ��
	int m_StageWidth;  //��ǰ���ڳ����������	
	int m_ViewWidth, m_ViewHeight, m_OffsetY;
	bool m_IsAttacking;
	bool m_isBackJumping;
	bool m_Dead;
	clock_t m_PreEffect_Z, m_PreEffect_A, m_PreEffect_S, m_PreEffect_D;
	clock_t m_PreReplyHpMp;
	std::vector<CAnimationEffect*>* m_Vector_AnimationEffects;
public:
	CCharacter();
	~CCharacter();
	CCharacterState* GetCurState();;
	void SetState(CCharacterState* p);
	std::vector<CAnimationEffect*>* GetAnimationEffects();
	void SetAnimationEffectsVector(std::vector<CAnimationEffect*>* v) { m_Vector_AnimationEffects = v; }
	void DoRender(Mat& mat,int viewX);
	void DoHandleInput(int input);
	void UpdateState();
	void Move(int dir, double multiple = 1.0);
	int GetDamage(int effect, bool& crit);
	int GetArmor();
	static const int s_JumpN = 27; /**< ��Ծ�� */
	static const int s_Gravity = -1;
private:
	void __InitRec();
public://get/set
	bool GetDead() { return m_Dead; }
	int GetHp() { return m_HP; };
	int GetMp() { return m_MP; }
	int GetGravity() { return m_Gravity; };
	int GetZSpeed() { return m_ZSpeed; };
	int GetOrientation() { return m_Orientation; };
	int GetMoveDirection() { return m_MoveDirection; };
	int GetMovespeed() { return m_MoveSpeed; };
	int GetJumpDir() { return m_JumpDir; };
	Rect GetAttackRect();
	bool GetAttacking() { return m_IsAttacking; };
	bool GetBackJumping() { return m_isBackJumping; }
	int GetCurEffect(); //��ȡ��ɫ��ǰʹ�õļ���
	clock_t GetPreEffectA() { return m_PreEffect_A; }
	clock_t GetPreEffectS() { return m_PreEffect_S; }
	clock_t GetPreEffectD() { return m_PreEffect_D; }
	clock_t GetPreEffectZ() { return m_PreEffect_Z; }

	void SetPreEffectA(clock_t a) { m_PreEffect_A = a; }
	void SetPreEffectS(clock_t s) { m_PreEffect_S = s; }
	void SetPreEffectD(clock_t d) { m_PreEffect_D = d; }
	void SetPreEffectZ(clock_t z) { m_PreEffect_Z = z; }
	void SetIsBackJumpint(bool is) { m_isBackJumping = is; }
	void SetAttacking(bool is) { m_IsAttacking = is; };
	void SetGravity(int gravity) { m_Gravity = gravity; };
	void SetZSpeed(int speed) { m_ZSpeed = speed; };
	void SetMovespeed(int speed) { m_MoveSpeed = speed; };
	void SetJumpDir(int dir) { m_JumpDir = dir; };
	void SetMoveDirection(int dir);
	void SetStageWidth(int width) { m_StageWidth = width; }
	void SetViewSize(int width, int height, int offsety) { m_ViewWidth = width; m_ViewHeight = height; m_OffsetY = offsety; }
	void SetDead(bool is) { m_Dead = is; }
	bool SetX(int x);
	bool SetY(int y);
	bool SetZ(int z);
	void SetHp(int hp);
	void SetMp(int mp);
};

