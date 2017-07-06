#include "Dungeon.h"
#include "RollandStage.h"
#include "Monster.h"
#include "Monster_State.h"
#include "CharacterState.h"
#include "ObjectBase.h"

CDungeon::CDungeon()
{
	m_clock_statr = clock();
	m_score = 0;
	m_IsClearance = false;
}


CDungeon::~CDungeon()
{
	for (auto it = m_Stages.begin(); it != m_Stages.end(); it++)
		delete *it;
	m_Stages.clear();
}


int CDungeon::GetViewX()
{
	if (m_CurStage)
		return m_CurStage->GetViewX();
	else
		return 0;
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


void CDungeon::DoRender(Mat & mat)
{
	m_CurStage->Render(mat);
}
