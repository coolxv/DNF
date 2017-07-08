#include "Dungeon_Start.h"
#include "Dungeon_Home.h"
#include "Dungeon_Comics.h"


CDungeon_Start::CDungeon_Start()
{

}


CDungeon_Start::~CDungeon_Start()
{
}

void CDungeon_Start::DoHandleInput(int input)
{
}

void CDungeon_Start::Update()
{
	clock_t cur = clock();
	if (cur - m_Clock_Start > 6000)
	{
		m_Quit = true;
		m_NextDungeon = new CDungeon_Comics();
	}
	if (cur  - m_Clock_PreUpdae > 100 && cur-m_Clock_Start<3000)
	{
		m_Clock_PreUpdae = clock();
		if (m_DotMatId == 23)
			m_DotMatId = 0;
		else
			m_DotMatId++;
	}
}

void CDungeon_Start::DoRender(Mat& mat)
{
	if(clock()-m_Clock_Start>3000)
		m_Mat_BG_Loading.copyTo(mat);
	else
		m_Mat_BG.copyTo(mat);

	__Merge(mat,m_Mat_Dot[m_DotMatId], 371, 457, 50);
}

void CDungeon_Start::DoInitDungeon()
{
	m_Quit = false;
	m_NextDungeon = NULL;
	m_Clock_Start = clock();
	m_Clock_PreUpdae = 0;

	m_Mat_BG = imread("./ImagePacks2/Map/start/bg.png", -1);
	m_Mat_BG_Loading = imread("./ImagePacks2/Map/start/bg_loading.png", -1);
	for (int i = 0; i < 24; i++)
	{
		m_Mat_Dot[i] = imread(format("./ImagePacks2/Map/start/dot/%d.png",i), -1);
	}
	m_DotMatId = 0;
}

void CDungeon_Start::HandleMouse(int Event, int x, int y, int flags, void* param)
{
}

void CDungeon_Start::__Merge(Mat& a, Mat& b, int x, int y, int h)
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
			if (bdata[k + 3] > h &&bdata[k + 2] >  h &&bdata[k + 1] >  h &&bdata[k ] >  h)
			{
				adata[x * 4 + k] = bdata[k];
				adata[x * 4 + k + 1] = bdata[k + 1];
				adata[x * 4 + k + 2] = bdata[k + 2];
				adata[x * 4 + k + 3] = bdata[k + 3];
			}
		}
	}
}
