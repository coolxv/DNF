#include "Dungeon_Rolland.h"
#include "Dungeon_Home.h"
#include "Stage_Rolland.h"
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



	//设置场景的连接
	m_Stages[0]->SetNextStage(NEXT_STAGE(NULL, m_Stages[2], NULL, m_Stages[1]));
	m_Stages[1]->SetNextStage(NEXT_STAGE(NULL, NULL, m_Stages[0], NULL));
	m_Stages[2]->SetNextStage(NEXT_STAGE(m_Stages[0], m_Stages[4], NULL, m_Stages[3]));
	m_Stages[3]->SetNextStage(NEXT_STAGE(NULL, m_Stages[5], m_Stages[2], NULL));
	m_Stages[4]->SetNextStage(NEXT_STAGE(m_Stages[2], NULL, NULL, m_Stages[5]));
	m_Stages[5]->SetNextStage(NEXT_STAGE(m_Stages[3], NULL, m_Stages[4], 0));

	m_Stages.at(0)->InitStage(); //设置初始场景
	m_CurStage = m_Stages.at(0);

	m_Character->SetViewSize(CStage::s_ViewWidth, CStage::s_ViewHeight, CStage::s_OffsetY);
	m_Character->SetX(180);
	m_Character->SetY(10);
	m_Character->SetZ(0);

	m_Clock_Start = clock();
	m_Mat_MinMapBG = imread("./ImagePacks2/Map/0/mapbg.png", -1);
	m_Mat_MinMapBG_Mask = imread("./ImagePacks2/Map/0/mapbg.png", 0);
	m_Mat_MinMap_Character = imread("./ImagePacks2/Map/0/character.png", -1);
	m_Mat_MinMap_Character_Mask = imread("./ImagePacks2/Map/0/character.png", 0);
	m_Mat_MinMap_Boos = imread("./ImagePacks2/Map/0/boos.png", -1);
	m_Mat_MinMap_Boos_Mask = imread("./ImagePacks2/Map/0/boos.png", 0);
	m_Mat_MinMap_Unknown[0] = imread("./ImagePacks2/Map/0/unknown.png", -1);
	m_Mat_MinMap_Unknown[1] = imread("./ImagePacks2/Map/0/unknownb.png", -1);
	for (int i = 0; i < 6; i++)
	{
		m_Mat_MinMap[i] = imread(format("./ImagePacks2/Map/0/%d.png", i), -1);
	}
	m_MinMapPos[0] = Point(550, 47);
	m_MinMapPos[1] = Point(550 + 18, 47);
	m_MinMapPos[2] = Point(550, 47 + 18);
	m_MinMapPos[3] = Point(550 + 18, 47 + 18);
	m_MinMapPos[4] = Point(550, 47 + 18 * 2);
	m_MinMapPos[5] = Point(550 + 18, 47 + 18 * 2);

	//	---------------
	//|          |           |
	//|    0    |     1    |
	//|          |           |
	//|----------------
	//|          |           | 
	//|    2    |     3    | 
	//|          |           | 
	//|----------------
	//|          |           |
	//|    4    |     5    |
	//|          |           |
	//----------------
}

void CDungeon_Rolland::DoRender(Mat& mat)
{
	if (clock() - m_Clock_Start < 3000)
	{
		s_Mat_DungeonLoading.copyTo(mat);
		return;
	}
	m_CurStage->Render(mat);

	//绘制小地图
	if (!m_ShowMinMap)return;
	m_Mat_MinMapBG.copyTo(mat(Rect(498, 10, m_Mat_MinMapBG.cols, m_Mat_MinMapBG.rows)), m_Mat_MinMapBG_Mask);
	clock_t cur = clock();
	for (int i = 0; i < 6; i++)
	{
		if (m_Stages.at(i)->IsClearance() || m_CurStage == m_Stages.at(i))
		{
			m_Mat_MinMap[i].copyTo(mat(Rect(m_MinMapPos[i], m_MinMapPos[i] + Point(18, 18))));
			if (m_Stages.at(i)->IsClearance() && m_CurStage == m_Stages.at(i))
			{
				NEXT_STAGE next = m_CurStage->GetNextStage();
				if (next.bottom && !next.bottom->IsClearance())
					m_Mat_MinMap_Unknown[(cur / 1000) % 2]
					.copyTo(mat(Rect(m_MinMapPos[i].x, m_MinMapPos[i].y + 18 , 18, 18)), m_Mat_MinMap_Unknown[(cur / 1000) % 2]);

				if (next.top && !next.top->IsClearance())
					m_Mat_MinMap_Unknown[(cur / 1000) % 2]
					.copyTo(mat(Rect(m_MinMapPos[i].x, m_MinMapPos[i].y - 18 , 18, 18)), m_Mat_MinMap_Unknown[(cur / 1000) % 2]);

				if (next.left && !next.left->IsClearance())
					m_Mat_MinMap_Unknown[(cur / 1000) % 2]
					.copyTo(mat(Rect(m_MinMapPos[i].x - 18 , m_MinMapPos[i].y , 18, 18)), m_Mat_MinMap_Unknown[(cur / 1000) % 2]);

				if (next.right && !next.right->IsClearance())
					m_Mat_MinMap_Unknown[(cur / 1000) % 2]
					.copyTo(mat(Rect(m_MinMapPos[i].x + 18 , m_MinMapPos[i].y, 18, 18)), m_Mat_MinMap_Unknown[(cur / 1000) % 2]);
			}
		}
		if(m_CurStage == m_Stages.at(i))
			m_Mat_MinMap_Character.copyTo(mat(Rect(m_MinMapPos[i].x+6, m_MinMapPos[i].y+3, 6,12)), m_Mat_MinMap_Character_Mask);
		if (m_Stages.at(i)->IsBossRoom())
			_Merge(mat, m_Mat_MinMap_Boos, m_MinMapPos[i].x + 1, m_MinMapPos[i].y+2, 50);
			//m_Mat_MinMap_Boos.copyTo(mat(Rect(m_MinMapPos[i].x + 1, m_MinMapPos[i].y + 2, 16, 14)), m_Mat_MinMap_Boos_Mask);
	}
}
