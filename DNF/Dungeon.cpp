#include "Dungeon.h"
#include "RollandStage.h"
#include "Monster.h"
#include "Monster_State.h"
#include "CharacterState.h"

CDungeon::CDungeon()
{
}


CDungeon::~CDungeon()
{
}

void CDungeon::SwitchStage(CStage * stage)
{
	m_CurStage = stage;
	stage->InitStage();
}

void CDungeon::DoHandleInput(int input)
{
	m_CurStage->HandleInput(input);
	//mCharacter->handleInput(input);
}

void CDungeon::Update()
{
	m_CurStage->Update(this);
	m_Character->UpdateState();

}

void CDungeon::DoRender(Mat & mat)
{
	m_CurStage->Render(mat);
}


Dungeon_Rolland::Dungeon_Rolland()
{

}

Dungeon_Rolland::~Dungeon_Rolland()
{
	for (auto it = m_Stages.begin(); it != m_Stages.end(); it++)
	{
		delete (*it);
	}
}

void Dungeon_Rolland::DoInitDungeon()
{
	//初始化副本场景
	CStage* p = new RollandStage0();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p);

	p = new RollandStage1();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p); 

	p = new RollandStage2();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p);

	p = new RollandStage3();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p);

	p = new RollandStage4();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p);

	p = new RollandStage5();
	p->SetCharacter(m_Character);
	m_Stages.push_back(p);

	//0: 1,2
	//1: 0
	//2: 0,3,4
	//3: 2,5
	//4: 2,5
	//5: 3,4
	//设置场景的连接
	m_Stages[0]->SetNextStage(CStage::NEXT_STAGE(NULL, m_Stages[2], NULL, m_Stages[1]));
	m_Stages[1]->SetNextStage(CStage::NEXT_STAGE(NULL, NULL, m_Stages[0], NULL));
	m_Stages[2]->SetNextStage(CStage::NEXT_STAGE(m_Stages[0], m_Stages[4], NULL, m_Stages[3]));
	m_Stages[3]->SetNextStage(CStage::NEXT_STAGE(NULL, m_Stages[5], m_Stages[2], NULL));
	m_Stages[4]->SetNextStage(CStage::NEXT_STAGE(m_Stages[2], NULL, NULL, m_Stages[5]));
	m_Stages[5]->SetNextStage(CStage::NEXT_STAGE(m_Stages[3], NULL, m_Stages[4], 0));
	
	m_Stages.at(0)->InitStage(); //设置初始场景
	m_CurStage = m_Stages.at(0);

	m_Character->SetX(180);
	m_Character->SetY(10);
	m_Character->SetZ(0);
}
