#include "Dungeon_Home.h"
#include "Dungeon_SelectDungeon.h"



//-------------------------------------------------------赛利亚起始场景-----------------------------------------------------
Mat CDungeon_Home::s_Mat_BG = imread("./ImagePacks2/Map/home/home.png", -1);
Mat CDungeon_Home::s_Mat_Gate = imread("./ImagePacks2/Map/home/gate.png", -1);
Mat CDungeon_Home::s_Mat_Gate_Mask = imread("./ImagePacks2/Map/home/gate.png", 0);
Mat CDungeon_Home::s_Mat_Seria[] =
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
Mat CDungeon_Home::s_Mat_Seria_Mask[] =
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
CDungeon_Home::CDungeon_Home()
{

	m_Quit = false;
	m_NextDungeon = NULL;
}
CDungeon_Home::~CDungeon_Home()
{
}

void CDungeon_Home::DoInitDungeon()
{
	m_Character->SetStageWidth(954);
	m_Character->SetViewSize(954, 190, 360);
	m_Character->SetX(450);
	m_Character->SetY(100);
	m_Character->SetZ(0);

	m_clock_SeriaRender = 0;
	m_SeriaMatId = 0;
}

void CDungeon_Home::DoHandleInput(int input)
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


void CDungeon_Home::Update()
{
	m_Character->UpdateState();
	int cx = m_Character->GetX();
	int cy = m_Character->GetY();
	if ((cx >= 330 || cx <= 580) && cy == 180 && m_Quit == false)
	{
		m_Quit = true;
		m_NextDungeon = new CDungeon_SelectDungeon();
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

void CDungeon_Home::DoRender(Mat& mat)
{
	s_Mat_BG.copyTo(mat);
	s_Mat_Seria[m_SeriaMatId].copyTo(mat(Rect(424, 205, 80, 170)), s_Mat_Seria_Mask[m_SeriaMatId]);
	m_Character->DoRender(mat, 0);
	s_Mat_Gate.copyTo(mat(Rect(358, 459, s_Mat_Gate.cols, s_Mat_Gate.rows)), s_Mat_Gate_Mask);
	//358 459
}

