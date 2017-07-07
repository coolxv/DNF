#include "CharacterState.h"
#include <cmath>
#include "AnimationEffect.h"

CCharacterState::CCharacterState() :m_MatId(0), m_MatId_Add(1)
{
	m_Clock_PreUpdate = clock();
}

CCharacterState::~CCharacterState()
{
}

void CharacterWalkintState::DoHandleInput(CCharacter& character, int input)
{
	clock_t cur = clock();
	switch (input)
	{
	case KEY_MOVE_LEFT:
		m_Clock_PreKey = cur;
		character.SetMoveDirection(DIR_LEFT);
		break;
	case KEY_MOVE_RIGHT:
		character.SetMoveDirection(DIR_RIGHT);
		m_Clock_PreKey = cur;
		break;
	case KEY_MOVE_UP:
		character.SetMoveDirection(DIR_UP);
		m_Clock_PreKey = cur;
		break;
	case KEY_MOVE_DOWN:
		character.SetMoveDirection(DIR_DOWN);
		m_Clock_PreKey = cur;
		break;
	case KEY_ATTACK:
		character.SetState(&s_NAttacking);
		break;
	case KEY_EFFECTS:
		character.GetAnimationEffects()->push_back(new CAwakeSEffectAnimation(character.GetOrientation()));
		character.SetState(&s_SEffecting);
		break;
	case KEY_JUMP:
		character.SetState(&s_Jumping);
		break;
	case KEY_JUMPBACK:
		character.SetJumpDir(character.GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT);
		character.SetState(&s_Jumping);
		break;
	case KEY_EFFECTZ:
		character.SetState(&s_Effecting);
		break;
	}
}

void CharacterWalkintState::UpdateState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreKey > 80)
	{
		character.SetState(&s_Standing);
	}
	else if (cur - m_Clock_PreKey > 40 && cur - m_Clock_PreKey < 80&&cur-m_Clock_StartWalk<300)
	{
		character.SetState(&s_Running);
	}
	else
	{
		if (cur-m_Clock_PreWalk>10)
		{
			character.Move(character.GetMoveDirection(), 0.5);
			m_Clock_PreWalk = cur;
		}
	}

	if (cur - m_Clock_PreUpdate > 100)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 22)
			m_MatId = 13;
		else
			m_MatId++;
	}
}

void CharacterWalkintState::InitState(CCharacter& character)
{
	character.SetAttacking(false);
	m_MatId = 13; //13~22
	m_Clock_PreKey = clock();
	m_Clock_PreUpdate = 0;
	m_Clock_PreWalk = 0;
	m_Clock_StartWalk = clock();
}

CharacterRunningState::CharacterRunningState()
{
}

CharacterRunningState::~CharacterRunningState()
{
}

void CharacterRunningState::DoHandleInput(CCharacter & character, int input)
{
	clock_t cur = clock();
	switch (input)
	{
	case KEY_MOVE_RIGHT:
		m_Clock_PreKey = cur;
		character.SetMoveDirection(DIR_RIGHT);
		break;
	case KEY_MOVE_LEFT:
		character.SetMoveDirection(DIR_LEFT);
		m_Clock_PreKey = cur;
		break;
	case KEY_MOVE_UP:
		character.SetMoveDirection(DIR_UP);
		m_Clock_PreKey = cur;
		break;
	case KEY_MOVE_DOWN:
		character.SetMoveDirection(DIR_DOWN);
		m_Clock_PreKey = cur;
		break;
	case KEY_ATTACK:		//攻击
		character.SetState(&s_NAttacking);
		break;
	case KEY_JUMP: //跳跃
		character.SetJumpDir(character.GetMoveDirection());
		character.SetState(&s_Jumping);
		break;
	case KEY_JUMPBACK: //后跳
		character.SetJumpDir(character.GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT);
		character.SetState(&s_Jumping);
		break;
	}
}

void CharacterRunningState::UpdateState(CCharacter & character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreKey > 100)
	{
		//100ms没有按方向键之后切换成站立状态
		character.SetState(&s_Standing);
	}
	else
	{
		if (cur - m_clock_PreRun > 10)
		{
			character.Move(character.GetMoveDirection());
		}
	}
	if (cur - m_Clock_PreUpdate > 70)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 158)
			m_MatId = 151;
		else
			m_MatId++;
	}
}

void CharacterRunningState::InitState(CCharacter& character)
{
	character.SetAttacking(false);
	character.SetIsBackJumpint(false);
	m_MatId = 151;
	m_MatId_Add = 1;
	character.Move(character.GetMoveDirection());
	m_Clock_PreKey = clock();
	m_Clock_PreUpdate = clock();
	m_clock_PreRun = clock();
}

CharacterStandingState::CharacterStandingState()
{
}

CharacterStandingState::~CharacterStandingState()
{
}

void CharacterStandingState::DoHandleInput(CCharacter & character, int input)
{
	switch (input)
	{
	case KEY_MOVE_LEFT:
		character.SetMoveDirection(DIR_LEFT);
		character.SetState(&s_Walking);
		break;
	case KEY_MOVE_RIGHT:
		character.SetMoveDirection(DIR_RIGHT);
		character.SetState(&s_Walking);
		break;
	case KEY_MOVE_UP:
		character.SetMoveDirection(DIR_UP);
		character.SetState(&s_Walking);
		break;
	case KEY_MOVE_DOWN:
		character.SetMoveDirection(DIR_DOWN);
		character.SetState(&s_Walking);
		break;
	case KEY_ATTACK:
		character.SetState(&s_NAttacking);
		break;
	case KEY_EFFECTS:
		character.SetState(&s_SEffecting);
		break;
	case KEY_JUMP:
		character.SetState(&s_Jumping);
		break;
	case KEY_JUMPBACK:
		character.SetJumpDir(character.GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT);
		character.SetState(&s_Jumping);
		break;
	case KEY_EFFECTZ:
		character.SetState(&s_Effecting);
		break;
	case KEY_EFFECTD:
		character.SetState(&s_DEffecting);
		break;
	}
}

void CharacterStandingState::UpdateState(CCharacter & character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > 250 && character.GetZ() == 0)
	{
		if (m_MatId == 142)m_MatId = 0; //掉落完成
		m_Clock_PreUpdate = cur;
		m_MatId += m_MatId_Add;
		if (m_MatId == 4 && m_MatId_Add == 1) //伸手..
		{
			if (m_AnimationCount < 3) //没够3次
			{
				m_MatId = 3;
				m_MatId_Add = -1;
				m_AnimationCount++;
			}
			else
				m_AnimationCount = 0;
		}
		if (m_MatId == 8 && m_MatId_Add == 1)
			m_MatId_Add = -1;
		else if (m_MatId == 0 && m_MatId_Add == -1)
			m_MatId_Add = 1;
	}
}

void CharacterStandingState::InitState(CCharacter& character)
{
	character.SetAttacking(false);
	character.SetIsBackJumpint(false);
	if (character.GetZ() == 0) //在空中无法站立
		m_MatId = 0;
	else
		m_MatId = 142;
	m_MatId_Add = 1;
	m_AnimationCount = 0;
	m_Clock_PreUpdate = clock();
	character.SetZSpeed(0);
}

void CharacterNormalAttackingState::DoHandleInput(CCharacter & character, int input)
{
	clock_t cur = clock();
	switch (input)
	{
	case KEY_ATTACK:
		m_Clock_PreKey = cur;
		break;
	case KEY_JUMPBACK:

		character.SetJumpDir(character.GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT);
		character.SetState(&s_Jumping);
		break;
	case KEY_EFFECTZ:
		character.SetState(&s_Effecting);
		break;
	}
}

void CharacterNormalAttackingState::UpdateState(CCharacter & character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreKey > 500)
	{
		//600ms没有按j键之后切换成站立状态
		character.SetState(&s_Standing);
	}
	else if (cur - m_Clock_PreUpdate >CHARACTER_ATTACKSPEED)
	{
		character.Move(character.GetOrientation(), 1);
		m_Clock_PreUpdate = cur;
		if (m_MatId == 63)
			m_MatId = 48;
		else
			m_MatId++;
	}
}

void CharacterNormalAttackingState::InitState(CCharacter& character)
{
	character.SetAttacking(true);
	//48~63
	m_MatId = 48;
	m_MatId_Add = 1;
	m_Clock_PreKey = clock();
}

void CharacterJumpingState::DoHandleInput(CCharacter & character, int input)
{
	if (character.GetBackJumping())return;
	switch (input)
	{
	case KEY_MOVE_RIGHT:
		character.SetJumpDir(DIR_RIGHT);
		//character.Move(DIR_RIGHT, 2); //仅仅改变坐标，不改变动画
		break;
	case KEY_MOVE_LEFT:
		character.SetJumpDir(DIR_LEFT);
		//character.Move(DIR_LEFT, 2); //仅仅改变坐标，不改变动画
		break;
	case KEY_MOVE_UP:
		character.SetJumpDir(DIR_UP);
		//character.Move(DIR_UP, 2); //仅仅改变坐标，不改变动画
		break;
	case KEY_MOVE_DOWN:
		character.SetJumpDir(DIR_DOWN);
		//character.Move(DIR_DOWN, 2); //仅仅改变坐标，不改变动画
		break;
	}
}

void CharacterJumpingState::UpdateState(CCharacter & character)
{
	if (character.GetZ() <= 0)
	{
		character.SetZ(0);
		character.SetGravity(0);
		character.SetJumpDir(DIR_NONE);
		character.SetState(&s_Standing);
	}
	else
	{
		clock_t cur = clock();
		if (cur - m_Clock_PreJumpMove > 10)
		{
			character.Move(character.GetJumpDir(), 1);
			m_Clock_PreJumpMove = cur;
		}
		if (cur - m_Clock_PreUpdate >= 30)
		{

			//37,38 上升
			//39,40 下降
			int speed = character.GetZSpeed();
			if (speed > 0)
			{
				if (speed > character.s_JumpN * 2 / 3)
					m_MatId = 37;
				else
					m_MatId = 38;
			}
			else
			{
				if (abs(speed) > character.s_JumpN / 2)
					m_MatId = 40;
				else
					m_MatId = 39;
			}
			m_Clock_PreUpdate = cur;
		}
	}
}

void CharacterJumpingState::InitState(CCharacter& character)
{
	character.SetAttacking(false);
	if (character.GetOrientation() != character.GetJumpDir() && (character.GetJumpDir() == DIR_LEFT || character.GetJumpDir() == DIR_RIGHT))
	{
		//后跳
		clock_t cur = clock();
		if (cur - character.GetPreEffectA() >= COOLDOWN_A)
			character.SetPreEffectA(cur);
		else
		{
			character.SetState(&s_Standing);
			return;
		}
		character.SetIsBackJumpint(true);
		m_MatId = 37; //~40
		m_MatId_Add = 1;
		character.SetZSpeed(character.s_JumpN / 5 * 3);
		character.SetGravity(character.s_Gravity);
	}
	else
	{
		character.SetIsBackJumpint(false);
		m_MatId = 37; //~40
		m_MatId_Add = 1;
		character.SetZSpeed(character.s_JumpN);
		character.SetGravity(character.s_Gravity);
	}
	m_Clock_PreJumpMove = clock();
	m_Clock_PreUpdate = clock();
	m_Clock_PreKey = 0;

}

void CharacterBeAttackState::DoHandleInput(CCharacter& character, int input)
{
	//这个事件不会是键盘输入的，是怪物状态类调用的
	switch (input)
	{
	case EVENT_BEATTACK:
		/*character.SetHp(character.GetHp() - 10);*/
		m_Clock_PreKey = clock();
		m_cnt++;
		if (m_cnt >= 2)
			m_Fell = true;
		break;
	case EVENT_BEATTACK_KNOCK:  //被牛头击飞
		character.SetZSpeed(character.s_JumpN );
		character.SetGravity(character.s_Gravity);
		m_Clock_PreKey = clock();
		m_Fell = true;
		break;
	}
}

void CharacterBeAttackState::UpdateState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreKey > 500 && !m_Fell) //没被打
	{
		character.SetState(&s_Standing);
	}

	if (m_Fell && cur - m_Clock_PreUpdate > 300) //起身动画
	{
		m_Clock_PreUpdate = cur;
		m_MatId++;
		if (m_MatId == 144 && character.GetZ() > 0) //在空中不能起身..
			m_MatId = 143;
		if (m_MatId == 146)
			character.SetState(&s_Standing);
	}
}

void CharacterBeAttackState::InitState(CCharacter& character)
{
	character.SetAttacking(false);
	m_cnt = 0;
	m_Fell = false;
	m_Clock_PreUpdate = clock();
	m_Clock_PreKey = clock();
	m_MatId = 140; //140 第一下，	141~145倒下+起身
	if (character.GetZ() > 0)  //在跳跃中被攻击直接倒地
	{
		character.SetZSpeed(character.GetZSpeed() / 2); //减速
		m_Fell = true;
		m_MatId = 142;
	}
}

void CharacterSEffectingState::DoHandleInput(CCharacter& character, int input)
{

}

void CharacterSEffectingState::UpdateState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > 100)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 96)
			character.SetState(&s_Standing);
		else
		{
			if (m_MatId == 76)
				m_MatId = 91;
			else
				m_MatId++;
		}
	}
}

void CharacterSEffectingState::InitState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - character.GetPreEffectS() >= COOLDOWN_S && character.GetMp() >= CHARACTER_EFFECT_MP_S) 
		character.SetPreEffectS(cur);
	else
	{
		character.SetState(&s_Standing);
		return;
	}

	character.SetMp(character.GetMp() - CHARACTER_EFFECT_MP_S);
	character.GetAnimationEffects()->push_back(new CAwakeSEffectAnimation(character.GetOrientation()));
	m_MatId = 74;
	character.SetAttacking(true);
}

void CharacterZEffectingState::DoHandleInput(CCharacter & character, int input)
{

}

void CharacterZEffectingState::UpdateState(CCharacter & character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > 100)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 68)
			character.SetState(&s_Standing);
		else
		{
			m_MatId++;
			character.Move(character.GetOrientation(),1.5);
		}
	}
}

void CharacterZEffectingState::InitState(CCharacter & character)
{
	clock_t cur = clock();
	if (cur - character.GetPreEffectZ() >= COOLDOWN_Z && character.GetMp() >= CHARACTER_EFFECT_MP_Z)
		character.SetPreEffectZ(cur);
	else
	{
		character.SetState(&s_Standing);
		return;
	}
	//64~68
	character.SetMp(character.GetMp() - CHARACTER_EFFECT_MP_Z);
	m_MatId = 64;
	character.SetAttacking(true);
}


void CharacterDEffectingState::DoHandleInput(CCharacter& character, int input)
{

}

void CharacterDEffectingState::UpdateState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > 100)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 138)
			character.SetState(&s_Standing);
		else
		{
			m_MatId++;
		}
	}
}

void CharacterDEffectingState::InitState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - character.GetPreEffectD() >= COOLDOWN_D && character.GetMp()>= CHARACTER_EFFECT_MP_D)
		character.SetPreEffectD(cur);
	else
	{
		character.SetState(&s_Standing);
		return;
	}
	character.SetMp(character.GetMp() - CHARACTER_EFFECT_MP_D);
	character.GetAnimationEffects()->push_back(new CAwakeDEffectAnimation(character.GetOrientation()));
	m_MatId = 121; //121~138
	character.SetAttacking(true);
}


void CharacterDeadState::UpdateState(CCharacter& character)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > 150)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId < 143)
			m_MatId++;
	}
}

void CharacterDeadState::InitState(CCharacter& character)
{
	m_MatId = 139;	//139~143
	m_Clock_PreUpdate = clock();

	character.SetDead(true);
	character.SetHp(0);
}
