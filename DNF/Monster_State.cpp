#include "Monster_State.h"
#include "Character.h"
#include "CharacterState.h"
#include "AnimationEffect.h"
#include "OtherObject.h"


void CMonster_BeAttackedState::Update()
{
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	int charactMatId = character->GetCurState()->GetMatId();
	clock_t cur = clock();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	Rect intersection = (MonsterBodyRect&AttackRect);
	if (m_Monster->GetHp() <= 0)
	{
		m_Monster->SetDead(true);
		return;
	}
	if (m_Monster->GetZ() > 0) //空中
	{
		m_MatId = m_MatId2 - 1;
	}
	if (m_MatId >= m_MatId2 - 1 && !character->GetAttacking() || m_AttackCnt >= m_MaxAttack)
	{
		if (cur - m_Clock_PreUpdate > 300)
		{
			m_MatId++;
			m_Clock_PreUpdate = cur;
		}if (m_MatId == m_MatId2 + 3)
		{
			if (m_Monster->GetZ() > 0)
				m_MatId = m_MatId2;
			else
				SwitchStanding();
			//m_Monster->SetState(new CMonster_Goblin_StandingState(m_Monster));
			return;
		}
	}
	else if (intersection.area() != 0 && charactMatId != m_Clock_PreBeAttacked)
	{
		m_Monster->GetStage()->SetTargetMonster(m_Monster);
		m_Clock_PreBeAttacked = charactMatId;
		//50 55 61 普通攻击
		int damage = -INF;
		bool crit = false; //暴击
		if (character->GetCurEffect() == EFFECTX) //普通攻击
		{
			if (RANDNUM(1, 100) < 5)
			{
				SwitchStanding();
				return;
			}
			m_AttackCnt++;
			damage = character->GetDamage('j', crit);
			m_Clock_PreUpdate = cur;
			m_MatId++;
			if (charactMatId == 50) //第一下
				m_MatId = m_MatId1;
			m_Monster->Move(character->GetOrientation());
			m_Monster->SetMoveDirection(character->GetOrientation() ? 0 : 1);
			if (m_MatId == m_MatId2 - 1)//第三下击飞
			{
				m_Monster->SetJumpDir((m_Monster->GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT), 5 - m_weight); //1~5
				m_Monster->SetZSpeed(21 - m_weight); //10~15
				m_Monster->SetGravity(-1);
			}

			if (m_Monster->GetZ() > 0)
				m_MatId = m_MatId2 - 1;
			int animationType = (charactMatId - 50) / 5;
			Point3i point3 = Point3i(intersection.x + intersection.width / 2,
				intersection.y + intersection.height / 2,
				m_Monster->GetHeight() / 2);
			CPhysicalAttackAnimation* PhyAttackAnimation =
				new CPhysicalAttackAnimation(point3, animationType);
			character->GetAnimationEffects()->push_back(PhyAttackAnimation);
		}
		
		else if (character->GetCurEffect() == EFFECTZ) //上挑
		{
			damage = character->GetDamage(EFFECTZ,crit);
			m_AttackCnt++;
			m_Monster->SetMoveDirection(character->GetOrientation() ? 0 : 1);
			m_Monster->SetJumpDir((m_Monster->GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT), 1);
			m_Monster->SetZSpeed(20);
			m_Monster->SetGravity(-1);
			Point3i point3 = Point3i(intersection.x + intersection.width / 2,
				intersection.y + intersection.height / 2,
				m_Monster->GetHeight());
			CPhysicalAttackAnimation* PhyAttackAnimation =
				new CPhysicalAttackAnimation(point3, 0);
			character->GetAnimationEffects()->push_back(PhyAttackAnimation);
		}
		else if(character->GetCurEffect() == EFFECTS) //u技能第一段
		{
			damage = character->GetDamage(EFFECTS, crit);
			m_AttackCnt++;
			m_Monster->SetMoveDirection(character->GetOrientation() ? 0 : 1);
			m_Monster->SetJumpDir((m_Monster->GetOrientation() == DIR_LEFT ? DIR_LEFT : DIR_RIGHT), 6 - m_weight);
			m_Monster->SetZSpeed(20 - m_weight);
			m_Monster->SetGravity(-1);
			Point3i point3 = Point3i(intersection.x + intersection.width / 2,
				intersection.y + intersection.height / 2,
				m_Monster->GetHeight());
			CPhysicalAttackAnimation* PhyAttackAnimation =
				new CPhysicalAttackAnimation(point3, 0);
			character->GetAnimationEffects()->push_back(PhyAttackAnimation);
		}
		else if (character->GetCurEffect() == EFFECTS2)  //u技能第二段
		{
			damage = character->GetDamage(EFFECTS2, crit);
			m_AttackCnt++;
			m_Monster->SetMoveDirection(character->GetOrientation() ? 0 : 1);
			m_Monster->SetJumpDir((m_Monster->GetOrientation() == DIR_LEFT ? DIR_RIGHT : DIR_LEFT), 30 - m_weight);
			m_Monster->SetZSpeed(20 - m_weight);
			m_Monster->SetGravity(-1);
			Point3i point3 = Point3i(intersection.x + intersection.width / 2,
				intersection.y + intersection.height / 2,
				m_Monster->GetHeight());
			CPhysicalAttackAnimation* PhyAttackAnimation =
				new CPhysicalAttackAnimation(point3, 0);
			character->GetAnimationEffects()->push_back(PhyAttackAnimation);
		}
		if (damage != -INF)
		{
			damage -= m_Monster->GetArmor();
			m_Monster->SetHp(m_Monster->GetHp() - damage);
			character->GetAnimationEffects()->push_back(
				new CNumberAnimation(damage, Point3i(m_Monster->GetX(), m_Monster->GetY(), m_Monster->GetHeight()*2),
					crit?1:0));
		}
	}

	if (cur - m_Clock_PreUpdate > 500 && m_MatId < m_MatId2 - 1)
	{
		SwitchStanding();
		//m_Monster->SetState(new CMonster_Goblin_StandingState(m_Monster));
	}
}

void CMonster_BeAttackedState::InitState()
{
	m_AttackCnt = 0;
	m_MatId = m_MatId1;
	m_Clock_PreUpdate = clock();
	m_Clock_PreBeAttacked = clock();
}

CMonster_State::CMonster_State(CMonster* monster)
{
	m_Monster = monster; m_AttackCnt = 0;
}
