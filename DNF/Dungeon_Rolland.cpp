#include "Dungeon_Rolland.h"
#include "Dungeon_Home.h"
#include "RollandStage.h"
#include "Stage.h"



CDungeon_Rolland::CDungeon_Rolland()
{
	m_Quit = false;
	m_NextDungeon = NULL;
}

CDungeon_Rolland::~CDungeon_Rolland()
{
	//Stages在基类虚析构函数中已释放
}


void CDungeon_Rolland::Update()
{
	m_CurStage->Update(this);
	m_Character->UpdateState();
	if (m_CurStage->IsBossRoom() && m_CurStage->IsClearance() && m_IsClearance == false)
	{
		m_IsClearance = true;
		int ms = clock() - m_clock_statr;
		int score = m_score - ms;
		int min = (ms / 60000);
		ms -= min * 60000;
		int sec = ms / 1000;
		ms -= sec * 1000;
		int lsec = ms * 60 / 1000;
		m_Character->GetAnimationEffects()->push_back(
			new CResultAnimation(score>=0?score:0, 0, 236783462, min, sec, lsec, min,sec, lsec, this));
	}

}

void CDungeon_Rolland::DoInitDungeon()
{
	//初始化副本场景
	CStage* p = new RollandStage0();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
	m_Stages.push_back(p);

	p = new RollandStage1();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
	m_Stages.push_back(p);

	p = new RollandStage2();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
	m_Stages.push_back(p);

	p = new RollandStage3();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
	m_Stages.push_back(p);

	p = new RollandStage4();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
	m_Stages.push_back(p);

	p = new RollandStage5();
	p->SetCharacter(m_Character);
	p->SetScorePointer(&m_score);
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

	m_Character->SetViewSize(CStage::s_ViewWidth, CStage::s_ViewHeight, CStage::s_OffsetY);
	m_Character->SetX(180);
	m_Character->SetY(10);
	m_Character->SetZ(0);
}