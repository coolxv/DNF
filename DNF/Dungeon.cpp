#include "Dungeon.h"
#include "RollandStage.h"
#include "Monster.h"
#include "Monster_State.h"
#include "CharacterState.h"
#include "ObjectBase.h"

CDungeon::CDungeon()
{
}


CDungeon::~CDungeon()
{
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


Dungeon_Rolland::Dungeon_Rolland()
{
	m_Quit = false;
	m_NextDungeon = NULL;
}

Dungeon_Rolland::~Dungeon_Rolland()
{
	for (auto it = m_Stages.begin(); it != m_Stages.end(); it++)
	{
		delete (*it);
	}
}


void Dungeon_Rolland::Update()
{
	m_CurStage->Update(this);
	m_Character->UpdateState();
	if (m_CurStage->IsBossRoom() && m_CurStage->IsClearance()&&m_Quit==false)
	{
		m_Quit = true;
		m_NextDungeon = new Dungeon_Home();
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

	m_Character->SetViewSize(CStage::s_ViewWidth, CStage::s_ViewHeight, CStage::s_OffsetY);
	m_Character->SetX(180);
	m_Character->SetY(10);
	m_Character->SetZ(0);
}





//-------------------------------------------------------赛利亚起始场景-----------------------------------------------------
Mat Dungeon_Home::s_Mat_BG = imread("./ImagePacks2/Map/home/home.png", -1);
Mat Dungeon_Home::s_Mat_Gate = imread("./ImagePacks2/Map/home/gate.png", -1);
Mat Dungeon_Home::s_Mat_Gate_Mask = imread("./ImagePacks2/Map/home/gate.png", 0);
Mat Dungeon_Home::s_Mat_Seria[] =
{
	imread("./ImagePacks2/Seria/0.png",-1),
	imread("./ImagePacks2/Seria/1.png",-1),
	imread("./ImagePacks2/Seria/2.png",-1),
	imread("./ImagePacks2/Seria/3.png",-1),
	imread("./ImagePacks2/Seria/4.png",-1),
	imread("./ImagePacks2/Seria/5.png",-1),
	imread("./ImagePacks2/Seria/6.png",-1),
	imread("./ImagePacks2/Seria/7.png",-1),
	imread("./ImagePacks2/Seria/8.png",-1),
	imread("./ImagePacks2/Seria/9.png",-1)
};
Mat Dungeon_Home::s_Mat_Seria_Mask[] =
{
	imread("./ImagePacks2/Seria/0.png",0),
	imread("./ImagePacks2/Seria/1.png",0),
	imread("./ImagePacks2/Seria/2.png",0),
	imread("./ImagePacks2/Seria/3.png",0),
	imread("./ImagePacks2/Seria/4.png",0),
	imread("./ImagePacks2/Seria/5.png",0),
	imread("./ImagePacks2/Seria/6.png",0),
	imread("./ImagePacks2/Seria/7.png",0),
	imread("./ImagePacks2/Seria/8.png",0),
	imread("./ImagePacks2/Seria/9.png",0)
};
Dungeon_Home::Dungeon_Home()
{

	m_Quit = false;
	m_NextDungeon = NULL;
}
Dungeon_Home::~Dungeon_Home()
{
}

void Dungeon_Home::DoInitDungeon()
{
	m_Character->SetStageWidth(954);
	m_Character->SetViewSize(954,190,360);
	m_Character->SetX(450);
	m_Character->SetY(100);
	m_Character->SetZ(0);

	m_clock_SeriaRender = 0;
	m_SeriaMatId = 0;
}

void Dungeon_Home::DoHandleInput(int input)
{
	switch (input)
	{
	case KEY_MOVE_UP:
	case KEY_MOVE_DOWN:
	case KEY_MOVE_LEFT:
	case KEY_MOVE_RIGHT:
		m_Character->DoHandleInput(input);
		break;
	}
}


void Dungeon_Home::Update()
{
	m_Character->UpdateState();
	int cx = m_Character->GetX();
	int cy = m_Character->GetY();
	if ((cx >= 330 || cx <= 580) && cy == 180 && m_Quit == false)
	{
		m_Quit = true;
		m_NextDungeon = new Dungeon_SelectDungeon();
	}
	//330 580 y180
	if (clock() - m_clock_SeriaRender > 1000)
	{
		m_clock_SeriaRender = clock();
		if (m_SeriaMatId == 9)
			m_SeriaMatId = 0;
		else
			m_SeriaMatId++;
	}
}

void Dungeon_Home::DoRender(Mat& mat)
{
	s_Mat_BG.copyTo(mat);
	s_Mat_Seria[m_SeriaMatId].copyTo(mat(Rect(424,205,80,170)),s_Mat_Seria_Mask[m_SeriaMatId]);
	m_Character->DoRender(mat, 0);
	s_Mat_Gate.copyTo(mat(Rect(358, 459, s_Mat_Gate.cols, s_Mat_Gate.rows)), s_Mat_Gate_Mask);
	//358 459
}


//----------------------------------------------副本选择界面-------------------------------------------------
Mat Dungeon_SelectDungeon::s_Mat_BG = imread("./ImagePacks2/Map/select/bg.png", -1);

Mat Dungeon_SelectDungeon::s_Mat_DungeonPix[] = 
{
	imread("./ImagePacks2/Map/select/rolland0.png", -1),
	imread("./ImagePacks2/Map/select/rollanddeep0.png", -1)
};

Mat Dungeon_SelectDungeon::s_Mat_DungeonPix_Select[] =
{
	imread("./ImagePacks2/Map/select/rolland1.png", -1),
	imread("./ImagePacks2/Map/select/rollanddeep1.png", -1)
};

int Dungeon_SelectDungeon::s_PixPos[][2] = { 207,372 ,357,165};
int Dungeon_SelectDungeon::s_SelectPixPos[][2] = { 180,376,334,162 };
Dungeon_SelectDungeon::Dungeon_SelectDungeon()
{
	m_Quit = false;
	m_NextDungeon = NULL;
}

Dungeon_SelectDungeon::~Dungeon_SelectDungeon()
{

}


void Dungeon_SelectDungeon::HandleMouse(int Event, int x, int y, int flags, void* param)
{
	printf("%d %d,%d\n",Event,x,y);
	switch (Event)
	{
	case CV_EVENT_LBUTTONUP:
		if (x >= 210 && y >= 378 && x <= 210 + 150 && y <= 378 + 68)
			m_SelectedDungeon = DUNGEON_ROLLAND;
		if (x >= 360 && y >= 170 && x <= 360 + 150 && y <= 170 + 68)
			m_SelectedDungeon = DUNGEON_ROLLANDDEEP;
		
		
		break;
	}
	
}

void Dungeon_SelectDungeon::DoHandleInput(int input)
{
	switch (input)
	{
	case KEY_SPACE:
		if (m_SelectedDungeon == DUNGEON_ROLLAND)
		{
			m_Quit = true;
			m_NextDungeon = new Dungeon_Rolland();
			return;
		}
		break;
	}
}

void Dungeon_SelectDungeon::Update()
{

}

void Dungeon_SelectDungeon::DoRender(Mat& mat)
{
	s_Mat_BG.copyTo(mat);
	__RenderDungeonPix(mat, DUNGEON_ROLLAND, m_SelectedDungeon == DUNGEON_ROLLAND);
	__RenderDungeonPix(mat, DUNGEON_ROLLANDDEEP, m_SelectedDungeon == DUNGEON_ROLLANDDEEP);
}

void Dungeon_SelectDungeon::DoInitDungeon()
{

}

void Dungeon_SelectDungeon::__RenderDungeonPix(Mat& mat,int dungeon, bool select)
{
	Mat pix =select?s_Mat_DungeonPix_Select[dungeon]: s_Mat_DungeonPix[dungeon];
	int xx = select ? s_SelectPixPos[dungeon][0] : s_PixPos[dungeon][0];
	int yy = select ? s_SelectPixPos[dungeon][1] : s_PixPos[dungeon][1];
	for (int i = 0; i < pix.rows; i++)
	{
		uchar* pixdata = pix.ptr<uchar>(i);
		uchar* matdata = mat.ptr<uchar>(i+yy);
		for (int j = 0; j < pix.cols; j++)
		{
			int k = 4 * j;
			if (pixdata[k + 3] > 50)
			{
				matdata[xx * 4 + k] = pixdata[k];
				matdata[xx * 4 + k+1] = pixdata[k+1];
				matdata[xx * 4 + k+2] = pixdata[k+2];
				matdata[xx * 4 + k+3] = pixdata[k+3];
			}
		}
	}
}
