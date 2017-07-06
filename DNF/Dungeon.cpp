#include "Dungeon.h"
#include "RollandStage.h"
#include "Monster.h"
#include "Monster_State.h"
#include "CharacterState.h"
#include "ObjectBase.h"

CDungeon::CDungeon()
{
	m_Clock_Statr = clock();
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


void CDungeon::_Merge(Mat& a, Mat& b, int x, int y, int alpha)
{
	for (int i = 0; i < b.rows; i++)
	{
		if (i + y >= a.rows)break;
		uchar* adata = a.ptr(i + y);
		uchar* bdata = b.ptr(i);
		for (int j = 0; j < b.cols; j++)
		{
			int k = j * 4;
			if (x * 4 + k >= a.cols * 4)break;
			if (bdata[k + 3] > alpha)
			{
				adata[x * 4 + k] = bdata[k];
				adata[x * 4 + k + 1] = bdata[k + 1];
				adata[x * 4 + k + 2] = bdata[k + 2];
				adata[x * 4 + k + 3] = bdata[k + 3];
			}
		}
	}
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
