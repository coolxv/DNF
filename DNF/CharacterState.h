#pragma once
#include "Character.h"
class CCharacterState
{
public:
	virtual void DoHandleInput(CCharacter& character, int input) {}
	virtual void UpdateState(CCharacter& character) {}
	virtual void InitState(CCharacter& character) {};

	int GetMatId() { return m_MatId; };

	CCharacterState();
	~CCharacterState();

protected:
	int m_MatId; //��Դ��id
	int m_MatId_Add;
	clock_t m_Clock_PreUpdate; //��һ��ˢ��
	clock_t m_Clock_PreKey; //��¼��һ�ΰ���ʱ��
};

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
	clock_t m_Clock_StartWalk;
	clock_t m_Clock_PreWalk;
};

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
	clock_t m_clock_PreRun;
};

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
	int m_AnimationCount = 0; //����1�ƴΣ� ����1����3�βŲ��Ŷ���2
};

class CharacterNormalAttackingState :
	public CCharacterState
{
public:

	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
};

class CharacterJumpingState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
private:
	clock_t m_Clock_PreJumpMove;
};

class CharacterBeAttackState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
private:
	int m_cnt;
	bool m_Fell;
};

class CharacterZEffectingState :
	public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
};

class CharacterSEffectingState
	:public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);

};

class CharacterDEffectingState
	:public CCharacterState
{
public:
	void DoHandleInput(CCharacter& character, int input);
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);

};

class CharacterDeadState
	:public CCharacterState
{
public:
	void UpdateState(CCharacter& character);
	void InitState(CCharacter& character);
};

static CharacterRunningState s_Running;
static CharacterWalkintState s_Walking;
static CharacterStandingState s_Standing;
static CharacterNormalAttackingState s_NAttacking;
static CharacterJumpingState s_Jumping;
static CharacterZEffectingState s_Effecting;
static CharacterBeAttackState s_BeAttacked;
static CharacterSEffectingState s_SEffecting;
static CharacterDEffectingState s_DEffecting;
static CharacterDeadState s_Dead;