#include "Monster.h"
#include "Monster_State.h"
#include "OtherObject.h"
#include "Monster_Tau.h"
#include "CharacterState.h"

CMonster::CMonster()
{
	m_IsDead = false;
	m_isBoss = false; 
	m_JumpSpeed = 0;
}


CMonster::~CMonster()
{
	if (m_State)
	{
		delete m_State;
	}
}
void CMonster::SetState(CMonster_State* state)
{
	if (m_State)
	{
		delete m_State;
	}
	m_State = state;
	m_State->InitState();
	m_State->Update();
}

void CMonster::Move(int dir, double multiple)
{

	int m = (int)(m_MoveSpeed*multiple);
	SetMoveDirection(dir);
	switch (dir)
	{
	case DIR_UP:
		/*if (mY - mMovespeed*multiple >= 0)*/
		SetY(m_Y - m / 2);
		break;
	case DIR_DOWN:
		/*if (mY + mMovespeed*multiple < Stage::viewHeight)*/
		SetY(m_Y + m / 2);
		break;
	case DIR_RIGHT:
		/*if (mX + mMovespeed*multiple < Stage::viewWidth * 2 - 122)*/
		SetX(m_X + m);
		break;
	case DIR_LEFT:
		/*if (mX - mMovespeed*multiple >= 0)*/
		SetX(m_X - m);
		break;
	}
}

void CMonster::SetMoveDirection(int dir)
{
	m_MoveDirection = dir;
	if ((dir == DIR_LEFT || dir == DIR_RIGHT))
		m_Orientation = dir;
}



CStage* CMonster::GetStage()
{
	return m_Stage;
}

bool CMonster::SetX(int x)
{
	if (x >= 10 && x <= m_Stage->GetStageWidth() - 40)
	{
		m_X = x;
		return true;
	}
	else
	{
		
		return false;
	}
	
}
bool CMonster::SetY(int y)
{
	if (y >= 5 && y <= CStage::s_ViewHeight - 10)
	{
		m_Y = y;
		return true;
	}
	else
	{
		y = 10;
		return false;
	}
	
}
bool CMonster::SetZ(int z)
{
	if (z >= 0)
	{
		m_Z = z;
		return true;
	}
	else
	{
		z = 0;
		return false;
	}
}

void CMonster::SetGravity(int gravity)
{
	m_Gravity = gravity; 
}

void CMonster::SetHp(int hp)
{
	if (hp < 0)
		m_Hp = 0;
	else if (hp>m_TotalHp)
		m_Hp = m_TotalHp;
	else
	{
		m_Stage->AddScore(m_Hp-hp); //角色造成的伤害
		m_Hp = hp;
	}
	if (m_Hp <= 0)
	{
		SetDead(true);
	}
}

void CMonster::SetHp_Animation(int h)
{
	if (h < m_Hp)
		m_Hp_Animation = m_Hp;
	else
		m_Hp_Animation = h;
}

void CMonster::SetDead(bool dead)
{
	m_IsDead = dead;
	if (dead)
	{
		if(typeid(*this) == typeid(CMonster_Tau))
			m_Stage->m_OtherObjects.push_back(new Meat(this, 1));
		else
			m_Stage->m_OtherObjects.push_back(new Meat(this, 0));
	}
}

void CMonster::SetJumpDir(int dir,int speed = 1)
{
	m_JumpDir = dir;
	m_JumpSpeed = speed;
	if (speed < 0)
		m_JumpSpeed = 0;
}

void CMonster::Update()
{
	if (m_Gravity != 0)
	{
		if (m_ZSpeed != 0)
		{
			if (m_Z + m_ZSpeed < 0)
			{
				SetZ(0);
				m_Gravity = 0;
				m_ZSpeed = 0;
				m_JumpDir = DIR_NONE;
			}
			else
				SetZ(m_Z + m_ZSpeed);
		}
		if (m_JumpDir != DIR_NONE)
		{
			SetX(m_X + (m_JumpDir == DIR_RIGHT ? 1 : -1)*m_JumpSpeed);
		
		}
		m_ZSpeed += m_Gravity;
	}


	if (m_State)
	{
		m_State->Update();
	}
	if (m_Stage->GetCharacter()->GetCurState()->GetMatId() == 138)
	{
		bool iscrit =false;
		int damage = m_Stage->GetCharacter()->GetDamage(EFFECTD, iscrit) - GetArmor();
		m_Stage->GetCharacter()->GetAnimationEffects()->push_back(
			new CNumberAnimation(damage, Point3i(GetX(), GetY(), GetHeight() * 2),iscrit ? 1 : 0));
		SetHp(GetHp()-damage);
		//m_Stage->AddScore(m_Hp);
		//SetDead(true);
	}
}