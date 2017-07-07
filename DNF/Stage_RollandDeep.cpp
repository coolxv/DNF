#include "Stage_RollandDeep.h"
#include "OtherObject.h"
#include "Monster.h"
#include "Monster_BossGoblin.h"
#include "Monster_Goblin.h"
#include "Monster_Tau.h"


int CStage_RollandDeep::RollandDeepStageWidths[] = { 1280,640,1280,1280,1280,640,1280 };
CStage_RollandDeep::CStage_RollandDeep()
{
	m_mat_MidBG = imread("./ImagePacks2/Map/1/01mid1.png", -1);
	m_mat_MidBG_Mask = imread("./ImagePacks2/Map/1/01mid1.png", 0);
	m_mat_FarBG = imread("./ImagePacks2/Map/1/01far1.png", -1);
	m_mat_FarBG_Mask = imread("./ImagePacks2/Map/1/01far1.png", 0);

	m_Clock_GateTimer = -1;
	m_ViewX = 0;
	m_ViewX_far = 0;
	m_IsClearance = false;
	m_IsBossRoom = false;
}


CStage_RollandDeep::~CStage_RollandDeep()
{
}


Gate* CStage_RollandDeep::_CreatGate(int dir)
{
	switch (dir)
	{
	case DIR_UP:
		return new Gate(Gate::TOP_GATE, m_StageWidth / 2 - 86, 5, this);
		break;
	case DIR_DOWN:
		return new Gate(Gate::BOTTOM_GATE, m_StageWidth / 2 - 86, s_ViewHeight - 1, this);
		break;
	case DIR_LEFT:
		return new Gate(Gate::LEFT_GATE, -45, 100, this);
		break;
	case DIR_RIGHT:
		return new Gate(Gate::RIGHT_GATE, m_StageWidth - 100, 100, this);
		break;
	}
	return NULL;
}

void RollandDeepStage0::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[0]);
	//生成树

	//生成门
	m_RightGate = _CreatGate(DIR_RIGHT);
	m_OtherObjects.push_back(m_RightGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}

void RollandDeepStage1::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[1]);
	//生成门
	m_LeftGate = _CreatGate(DIR_LEFT);
	m_TopGate = _CreatGate(DIR_UP);
	m_OtherObjects.push_back(m_LeftGate);
	m_OtherObjects.push_back(m_TopGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandDeepStage2::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[2]);
	//生成门
	m_RightGate = _CreatGate(DIR_RIGHT);
	m_OtherObjects.push_back(m_RightGate);
	m_IsBossRoom = true;
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonSter_Tau(this, 300, 100, 0);
		mp->SetIsBoss(true);
		m_Monsters.push_back(mp);
	}
}


void RollandDeepStage3::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[3]);
	//生成门
	m_TopGate = _CreatGate(DIR_UP);
	m_BottomGate = _CreatGate(DIR_DOWN);
	m_LeftGate = _CreatGate(DIR_LEFT);
	m_RightGate = _CreatGate(DIR_RIGHT);
	m_OtherObjects.push_back(m_TopGate);
	m_OtherObjects.push_back(m_BottomGate);
	m_OtherObjects.push_back(m_LeftGate);
	m_OtherObjects.push_back(m_RightGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandDeepStage4::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[4]);
	//生成门
	m_LeftGate = _CreatGate(DIR_LEFT);
	m_OtherObjects.push_back(m_LeftGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandDeepStage5::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[5]);
	//生成门
	m_RightGate = _CreatGate(DIR_RIGHT);
	m_OtherObjects.push_back(m_RightGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}


void RollandDeepStage6::InitStage()
{
	SetStageWidth(RollandDeepStageWidths[6]);
	//生成门
	m_LeftGate = _CreatGate(DIR_LEFT);
	m_BottomGate = _CreatGate(DIR_DOWN);
	m_OtherObjects.push_back(m_LeftGate);
	m_OtherObjects.push_back(m_BottomGate);
	//生成怪物
	if (!IsClearance())
	{
		CMonster* mp = new CMonster_Goblin(this, 300, 100, 0);
		m_Monsters.push_back(mp);
	}
}