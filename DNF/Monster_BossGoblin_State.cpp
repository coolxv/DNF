#include "Monster_BossGoblin_State.h"
#include "CharacterState.h"
#include "OtherObject.h"

void CMonster_BossGoblin_StandingState::InitState()
{
	m_MatId = 0;
	m_Clock_PreUpdate = clock();
}

void CMonster_BossGoblin_StandingState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	//被攻击
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
	{
		m_Monster->SetState(new CMonster_BossGoblin_BeAttackedState(m_Monster));
	}
	else if (cur - m_Clock_PreUpdate > CObjectBase::GetRandNum(1000, 2000))
	{
		m_Monster->SetMoveDirection(((rand() % (4)) + 0));
		m_Monster->SetState(new CMonster_BossGoblin_RunningState(m_Monster));
	}
}

void CMonster_BossGoblin_RunningState::InitState()
{
	m_MatId = 11; //11~16
	m_Clock_PreUpdate = clock();
	m_Clock_PreRun = clock();
}

void CMonster_BossGoblin_RunningState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
		m_Monster->SetState(new CMonster_BossGoblin_BeAttackedState(m_Monster));
	else
	{
		if (cur - m_Clock_PreUpdate > 200)
		{
			int dx = character->GetX() - m_Monster->GetX();
			int dy = character->GetY() - m_Monster->GetY();
			if (abs(dy) < 15 && (m_Monster->GetX() <= 18 || m_Monster->GetX() >= m_Monster->GetStage()->GetStageWidth() - 51))
			{
				m_Monster->SetState(new CMonster_BossGoblin_AttackingState(m_Monster));
				return;
			}
			else if (abs(dy) > 15 || abs(dx) < 180)
			{
				if (CObjectBase::GetRandNum(1, 10) < 9)
				{
					m_Monster->Move(dx > 0 ? DIR_LEFT : DIR_RIGHT, sqrt(2));
					m_Monster->Move(dy > 0 ? DIR_DOWN : DIR_UP, sqrt(2));
				}
				else
				{
					m_Monster->SetState(new CMonster_BossGoblin_StandingState(m_Monster));
				}
			}
			else
			{
				m_Monster->SetState(new CMonster_BossGoblin_AttackingState(m_Monster));
			}
			m_Clock_PreUpdate = cur;
			m_MatId++;
			if (m_MatId == 17)
				m_MatId = 11;
		}
	}
}

void CMonster_BossGoblin_AttackingState::InitState()
{
	m_MatId = 1;	//1~4
	m_Clock_PreUpdate = clock();
}

void CMonster_BossGoblin_AttackingState::Update()
{
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	int dx = character->GetX() - m_Monster->GetX();
	int dy = character->GetY() - m_Monster->GetY();
	m_Monster->SetMoveDirection((dx > 0) ? DIR_RIGHT : DIR_LEFT);
	clock_t cur = clock();
	if (cur - m_Clock_PreUpdate > m_Monster->GetNAttackSpeed())
	{
		m_MatId++;
		if (m_MatId == 5)
		{
			m_Monster->SetState(new CMonster_BossGoblin_StandingState(m_Monster));
		}
		else if (m_MatId == 2) //生成石头
		{
			ThrowStone* stone = new ThrowStone(m_Monster->GetX(), m_Monster->GetY(), m_Monster->GetHeight() * 3 / 2,
				m_Monster->GetMoveDirection(),m_Monster->GetDamage() + character->GetArmor());
			m_Monster->GetStage()->m_OtherObjects.push_back(stone);
		}
		m_Clock_PreUpdate = cur;
	}
}

CMonster_BossGoblin_BeAttackedState::CMonster_BossGoblin_BeAttackedState(CMonster* monster)
	:CMonster_BeAttackedState(monster)
{
	m_MatId1 = 5;
	m_MatId2 = 8;
	m_MaxAttack = 5;
	m_weight = 3;
}


void CMonster_BossGoblin_BeAttackedState::CMonster_BossGoblin_BeAttackedState::SwitchStanding()
{
	m_Monster->SetState(new CMonster_BossGoblin_StandingState(m_Monster));
}