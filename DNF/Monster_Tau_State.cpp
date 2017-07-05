#include "Monster_Tau_State.h"
#include "Monster_Tau.h"
#include "CharacterState.h"
#include "OtherObject.h"


void CMonster_Tau_StandingState::InitState()
{
	m_MatId = 0;
	m_Clock_PreUpdate = clock();
}

void CMonster_Tau_StandingState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	//±»¹¥»÷
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
	{
		m_Monster->SetState(new CMonster_Tau_BeAttackedState(m_Monster));
	}
	else if (cur - m_Clock_PreUpdate > 1500)
	{
		m_Monster->SetState(new CMonster_Tau_RunningState(m_Monster));
	}
}

void CMonster_Tau_RunningState::InitState()
{
	m_MatId = 21; //21~27
	m_Clock_PreUpdate = clock();
}

void CMonster_Tau_RunningState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	if ((MonsterBodyRect&AttackRect).area() != 0 && character->GetAttacking())
	{
		m_Monster->SetState(new CMonster_Tau_BeAttackedState(m_Monster));
	}
	else
	{
		if (cur - m_Clock_PreUpdate > 200)
		{
			int dx = character->GetX() - m_Monster->GetX();
			int dy = character->GetY() - m_Monster->GetY();

			//m_Monster->SetState(new CMonster_Tau_Roar(m_Monster));

			if (abs(dy) < character->GetThick() / 2 && CObjectBase::GetRandNum(1, 10) < 4)
			{
				m_Monster->SetState(new CMonster_Tau_HittingState(m_Monster));
				return;
			}
			else if (abs(dy) > 30 || abs(dx) > 150)
			{
				m_Monster->Move(dx > 0 ? DIR_RIGHT : DIR_LEFT, sqrt(2));
				m_Monster->Move(dy > 0 ? DIR_DOWN : DIR_UP, sqrt(2));
			}
			else
			{
				if (CObjectBase::GetRandNum(1, 10) < 4)
				{
					m_Monster->SetState(new CMonster_Tau_Roar(m_Monster));
				}
				else
				{
					m_Monster->SetState(new CMonster_Tau_AttackingState(m_Monster));
				}
			}
			m_Clock_PreUpdate = cur;
			m_MatId++;
			if (m_MatId == 28)
				m_MatId = 21;
		}
	}
}

void CMonster_Tau_AttackingState::InitState()
{

	m_Monster->SetMoveDirection((m_Monster->GetStage()->GetCharacter()->GetX() - m_Monster->GetX() > 0) ?
		DIR_RIGHT : DIR_LEFT);
	m_MatId = 1; //1~6
	m_Clock_PreUpdate = clock();
}

void CMonster_Tau_AttackingState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	Rect intersection = (MonsterBodyRect&AttackRect);
	if (intersection.area() != 0 && character->GetAttacking())
	{
		//m_Monster->SetState(new CMonster_Tau_BeAttackedState(m_Monster));
		int charactMatId = character->GetCurState()->GetMatId();
		if (m_beattackId != charactMatId)
		{
			m_beattackId = charactMatId;

			int damage = -INF;
			bool crit = false; //±©»÷

			damage = character->GetDamage(character->GetCurEffect(), crit);

			Point3i point3 = Point3i(intersection.x + intersection.width / 2,
				intersection.y + intersection.height / 2,
				m_Monster->GetHeight());
			CPhysicalAttackAnimation* PhyAttackAnimation =
				new CPhysicalAttackAnimation(point3, 0);
			character->GetAnimationEffects()->push_back(PhyAttackAnimation);

			damage -= +m_Monster->GetArmor();
			m_Monster->SetHp(m_Monster->GetHp() );
			character->GetAnimationEffects()->push_back(
				new CNumberAnimation(damage, Point3i(m_Monster->GetX(), m_Monster->GetY(), m_Monster->GetHeight() * 2),
					crit ? 1 : 0));
		}
		
	}

	if (cur - m_Clock_PreUpdate > m_Monster->GetNAttackSpeed())
	{
		m_MatId++;
		Rect characterBodyRect = character->GetRectXY();
		Rect AttackRect = m_Monster->GetAttackRect();
		if (m_MatId == 7)
		{
			m_Monster->SetState(new CMonster_Tau_StandingState(m_Monster));
		}
		else if (m_MatId == 4 && (characterBodyRect&AttackRect).area() != 0)
		{
			if (typeid(*character->GetCurState()) != typeid(CharacterBeAttackState))
				character->SetState(&s_BeAttacked);
			character->DoHandleInput(EVENT_BEATTACK);
			character->DoHandleInput(EVENT_BEATTACK);
			character->DoHandleInput(EVENT_BEATTACK);

			character->SetHp(character->GetHp() - m_Monster->GetDamage()+character->GetArmor());
		}
		m_Clock_PreUpdate = cur;
	}
}

CMonster_Tau_BeAttackedState::CMonster_Tau_BeAttackedState(CMonster* monster)
	:CMonster_BeAttackedState(monster)
{
	m_MatId1 = 7;
	m_MatId2 = 10;
	m_weight = 5;
	m_MaxAttack = 8;
}


void CMonster_Tau_BeAttackedState::SwitchStanding()
{
	m_Monster->SetState(new CMonster_Tau_StandingState(m_Monster));
}


//////////////////////////////////////////////////////////////////////////
void CMonster_Tau_HittingState::InitState()
{
	CMonSter_Tau* tau = (CMonSter_Tau*)m_Monster;
	if (clock() - tau->GetPreHit() < 10000)
	{
		m_Monster->SetState(new CMonster_Tau_RunningState(m_Monster));
	}
	else
	{
		tau->SetPreHit(clock());
		m_MatId = 13; //13~20
		m_Clock_PreUpdate = 0;
		m_HitFlag = false;
		CCharacter* character = m_Monster->GetStage()->GetCharacter();
		m_Monster->SetMoveDirection(character->GetX() > m_Monster->GetX() ? DIR_RIGHT : DIR_LEFT);
	}
}

void CMonster_Tau_HittingState::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();
	Rect MonsterBodyRect = m_Monster->GetRectXY();
	Rect AttackRect = character->GetAttackRect();
	Rect intersection = (MonsterBodyRect&AttackRect);

	if (cur - m_Clock_PreUpdate > 100)
	{
		m_Clock_PreUpdate = cur;
		m_MatId++;
		m_Monster->Move(m_Monster->GetMoveDirection(),1.5);
		if (m_MatId == 19)
		{
			if(m_Monster->GetX()>50 && m_Monster->GetX()<m_Monster->GetStage()->GetStageWidth()-100)
				m_MatId = 13;
			else
			{
				m_Monster->SetState(new CMonster_Tau_StandingState(m_Monster));
				return;
			}
		}
	}

	if (intersection.area() != 0 && !m_HitFlag)
	{
		m_HitFlag = true;

		if (typeid(*character->GetCurState()) != typeid(CharacterBeAttackState))
			character->SetState(&s_BeAttacked);
		character->DoHandleInput(EVENT_BEATTACK_KNOCK); //»÷·É
		character->SetHp(character->GetHp() - m_Monster->GetDamage()*2 + character->GetArmor());
	}
}

void CMonster_Tau_Roar::InitState()
{

	CMonSter_Tau* tau = (CMonSter_Tau*)m_Monster;
	if (clock() - tau->GetPreRoar() < 10000)
	{
		m_Monster->SetState(new CMonster_Tau_RunningState(m_Monster));
		return;
	}
	else
	{
		tau->SetPreRoar(clock());
		m_MatId = 28;	//28~31

		m_Clock_PreUpdate = 0;
		CCharacter* character = m_Monster->GetStage()->GetCharacter();
		m_Monster->SetMoveDirection(character->GetX() > m_Monster->GetX() ? DIR_RIGHT : DIR_LEFT);
	}
}

void CMonster_Tau_Roar::Update()
{
	clock_t cur = clock();
	CCharacter* character = m_Monster->GetStage()->GetCharacter();

	if (cur - m_Clock_PreUpdate > 500)
	{
		m_Clock_PreUpdate = cur;
		if (m_MatId == 31)
		{
			m_Monster->SetState(new CMonster_Tau_RunningState(m_Monster));
			return;
		}
		else
			m_MatId++;
	}
	
	if (m_MatId == 30 && character->GetZ()<=0
		&& sqrt(pow(m_Monster->GetX() - character->GetX(), 2) + pow(m_Monster->GetX() - character->GetX(), 2))<500)
	{
		if (typeid(*character->GetCurState()) != typeid(CharacterBeAttackState))
			character->SetState(&s_BeAttacked);
		character->DoHandleInput(EVENT_BEATTACK_KNOCK); //»÷·É
		character->SetHp(character->GetHp() - m_Monster->GetDamage() * 2 + character->GetArmor());
	}

}
