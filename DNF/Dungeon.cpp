#include "Dungeon.h"
#include "Stage_Rolland.h"
#include "Monster.h"
#include "Monster_State.h"
#include "CharacterState.h"
#include "ObjectBase.h"

CDungeon::CDungeon()
{
	m_Clock_Statr = clock();
	m_GameOver = false;
	m_score = 0;
	m_IsClearance = false;
	if(m_Character)
		m_Character->SetState(&s_Standing);
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

void CDungeon::Update()
{
	if(!m_GameOver)
		m_CurStage->Update(this);
	m_Character->UpdateState();
	if (m_CurStage->IsBossRoom() && m_CurStage->IsClearance() && m_IsClearance == false)
	{
		m_IsClearance = true;
		int ms = clock() - m_Clock_Statr;
		int score = m_score - ms;
		int min = (ms / 60000);
		ms -= min * 60000;
		int sec = ms / 1000;
		ms -= sec * 1000;
		int lsec = ms * 60 / 1000;
		m_Character->GetAnimationEffects()->push_back(
			new CResultAnimation(score >= 0 ? score :RANDNUM(0,8), RANDNUM(10000,100000), 
				score, min, sec, lsec, min, sec, lsec, this));
	}
	if (m_Character->GetDead()&& !m_GameOver)
	{
		m_GameOver = true;
		m_Character->GetAnimationEffects()->push_back(new CGameOverAnimation(this));
	}
}
