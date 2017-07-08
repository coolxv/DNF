#include "Monster_Goblin_State.h"
#include "CharacterState.h"

//-----------------------------------------------------------------------------------------------

void CMonster_Goblin_StandingState::InitState()
{
	m_MatId = 0;
	m_Clock_PreUpdate = clock();
}

void CMonster_Goblin_StandingState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	//被攻击
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
		m_Monster->SetState(new CMonster_Goblin_BeAttackedState(m_Monster));
	else if (cur - m_Clock_PreUpdate > CObjectBase::GetRandNum(500, 1000) )
	{
		m_Monster->SetState(new CMonster_Goblin_RunningState(m_Monster));
	}
}

//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------


CMonster_Goblin_BeAttackedState::CMonster_Goblin_BeAttackedState(CMonster* monster)
	: CMonster_BeAttackedState(monster)
{
	m_MatId1 = 5;
	m_MatId2 = 8;
	m_MaxAttack = 5;
	m_weight = 3;
	//int m_MatId1, m_MatId2; //前三张和后三张
	//int m_MaxAttack; //打几下强制落地
	//int m_weight; //越轻被击飞的越远  范围[0,5]
}

void CMonster_Goblin_BeAttackedState::SwitchStanding()
{
	m_Monster->SetState(new CMonster_Goblin_StandingState(m_Monster));
}

//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------

void CMonster_Goblin_RunningState::InitState()
{
	m_MatId = 11; //11~16
	m_Clock_PreUpdate = clock();
	m_Clock_PreRun = clock();
}

void CMonster_Goblin_RunningState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
		m_Monster->SetState(new CMonster_Goblin_BeAttackedState(m_Monster));
	else
	{
		if (cur - m_Clock_PreUpdate > 200)
		{
			int dx = character->GetX() - m_Monster->GetX();
			int dy = character->GetY() - m_Monster->GetY();

			if (sqrt(dx*dx + dy*dy) > 20)
				//if(dx!=0&&dy!=0)
			{
					m_Monster->Move(dx > 0 ? DIR_RIGHT : DIR_LEFT, sqrt(2));
					m_Monster->Move(dy > 0 ? DIR_DOWN : DIR_UP, sqrt(2));
			}
			else
			{
				m_Monster->SetState(new CMonster_Goblin_AttackingState(m_Monster));
				//m_Monster->SetState(new CMonster_Goblin_StandingState(m_Monster));
			}
			m_Clock_PreUpdate = cur;
			m_MatId++;
			if (m_MatId == 17)
				m_MatId = 11;
		}
	}
	//-----------------------------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------------------------

void CMonster_Goblin_AttackingState::InitState()
{
	m_MatId = 1;	//1~4
	m_Clock_PreUpdate = 0;
}

void CMonster_Goblin_AttackingState::Update()
{
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect character_bodyrect = character->GetRectXY();
	Rect attackrect = m_Monster->GetAttackRect();
	Rect  intersection = character_bodyrect&attackrect;
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > m_Monster->GetNAttackSpeed())
	{
		if (intersection.area() != 0 && m_MatId == 3)
		{
			if (typeid(*character->GetCurState()) != typeid(CharacterBeAttackState))
				character->SetState(&s_BeAttacked);
			character->DoHandleInput(EVENT_BEATTACK);
			m_Monster->GetStage()->AddScore(-(m_Monster->GetDamage() - character->GetArmor()));
			character->SetHp(character->GetHp() -( m_Monster->GetDamage() - character->GetArmor()));
		}
		m_MatId++;
		if (m_MatId == 5)
		{
			m_Monster->SetState(new CMonster_Goblin_StandingState(m_Monster));
		}
		m_Clock_PreUpdate = cur;
	}
}

//-----------------------------------------------------------------------------------------------

