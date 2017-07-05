#include "RollandStage.h"
#include "OtherObject.h"
#include "Monster_Goblin.h"
#include "Monster_BossGoblin.h"
#include "Monster_Tau.h"

int CRollandStage::RollandStageWidths[] = {1280,640,1280,1280,640,1280};

void CRollandStage::QuitStage()
{
	for (auto it = m_OtherObjects.begin(); it != m_OtherObjects.end(); it++)
	{
		delete *it;
	}
	m_OtherObjects.clear();
}

CRollandStage::CRollandStage()
{
	m_mat_MidBG = imread("./ImagePacks2/Map/0/01mid1.png", -1);
	m_mat_MidBG_Mask = imread("./ImagePacks2/Map/0/01mid1.png", 0);
	m_mat_FarBG = imread("./ImagePacks2/Map/0/01far1.png", -1);
	m_mat_FarBG_Mask = imread("./ImagePacks2/Map/0/01far1.png", 0);

	m_Clock_GateTimer = -1;
	m_ViewX = 0;
	m_ViewX_far = 0;
	m_IsClearance = false;
	m_IsBossRoom = false;
}


void RollandStage0::InitStage()
{
	SetStageWidth(RollandStageWidths[0]);
	//生成树
	m_OtherObjects.push_back(new Tree(100, 10, 0));
	m_OtherObjects.push_back(new Tree(87, 30, 0));
	m_OtherObjects.push_back(new Tree(78, 50, 0));
	m_OtherObjects.push_back(new Tree(80, 70, 0));
	m_OtherObjects.push_back(new Tree(66, 90, 0));
	m_OtherObjects.push_back(new Tree(74, 110, 0));
	//生成门
	m_BottomGate = new Gate(Gate::BOTTOM_GATE, m_StageWidth / 2 -86, s_ViewHeight - 1, this);
	m_RightGate = new Gate(Gate::RIGHT_GATE, m_StageWidth - 100, 100, this);
	m_OtherObjects.push_back(m_RightGate);
	m_OtherObjects.push_back(m_BottomGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 60, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 850, 80, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 850, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 550, 80, 0);
		m_Monsters.push_back(mp);


		mp = new CMonster_BossGoblin(this, 1000, 40, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandStage1::InitStage()
{
	SetStageWidth(RollandStageWidths[1]);
	m_LeftGate = new Gate(Gate::LEFT_GATE, -45, 100, this);
	m_OtherObjects.push_back(m_LeftGate);

	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 420, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 320, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 400, 60, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 500, 80, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandStage2::InitStage()
{
	SetStageWidth(RollandStageWidths[2]);
	m_TopGate = new Gate(Gate::TOP_GATE, m_StageWidth / 2-86,5 , this);
	m_OtherObjects.push_back(m_TopGate);
	m_RightGate = new Gate(Gate::RIGHT_GATE, m_StageWidth - 100, 100, this);
	m_OtherObjects.push_back(m_RightGate);
	m_BottomGate = new Gate(Gate::BOTTOM_GATE, m_StageWidth / 2 - 86, s_ViewHeight - 1, this);
	m_OtherObjects.push_back(m_BottomGate);

	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 420, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 60, 0);
		m_Monsters.push_back(mp);
	}
}

void RollandStage3::InitStage()
{
	SetStageWidth(RollandStageWidths[3]);
	m_BottomGate = new Gate(Gate::BOTTOM_GATE, m_StageWidth / 2 - 86, s_ViewHeight - 1, this);
	m_OtherObjects.push_back(m_BottomGate);
	m_LeftGate = new Gate(Gate::LEFT_GATE, -45, 100, this);
	m_OtherObjects.push_back(m_LeftGate);
	
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 420, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 60, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 850, 80, 0);
		m_Monsters.push_back(mp);
	}
}

void RollandStage4::InitStage()
{
	SetStageWidth(RollandStageWidths[4]);
	m_TopGate = new Gate(Gate::TOP_GATE, m_StageWidth / 2 - 86, 5, this);
	m_OtherObjects.push_back(m_TopGate);
	m_RightGate = new Gate(Gate::RIGHT_GATE, m_StageWidth  - 100, 100, this);
	m_OtherObjects.push_back(m_RightGate);

	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 420, 140, 0);
		m_Monsters.push_back(mp);
	}
}

void RollandStage5::InitStage()
{
	SetStageWidth(RollandStageWidths[5]);
	m_TopGate = new Gate(Gate::TOP_GATE, m_StageWidth / 2 - 86,5 , this);
	m_OtherObjects.push_back(m_TopGate); 
	m_LeftGate = new Gate(Gate::LEFT_GATE, -45, 100, this);
	m_OtherObjects.push_back(m_LeftGate);

	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 420, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 140, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 800, 60, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_Goblin(this, 850, 80, 0);
		m_Monsters.push_back(mp);

		mp = new CMonster_BossGoblin(this, 1000, 100, 0);
		m_Monsters.push_back(mp);
		mp = new CMonster_BossGoblin(this, 800, 40, 0);
		m_Monsters.push_back(mp);
		mp = new CMonster_BossGoblin(this, 850, 80, 0);
		m_Monsters.push_back(mp);

		mp = new CMonSter_Tau(this,900,90,0);
		mp->SetIsBoss(true);
		m_Monsters.push_back(mp);
	}
}

RollandStage5::RollandStage5()
{
	SetStageWidth(RollandStageWidths[5]); 
	m_IsBossRoom = true;
}
