#include "Dungeon_SelectDungeon.h"
#include "Dungeon_Rolland.h"
#include "Dungeon_RollandDeep.h"

//----------------------------------------------副本选择界面-------------------------------------------------
Mat CDungeon_SelectDungeon::s_Mat_BG = imread("./ImagePacks2/Map/select/bg.png", -1);

Mat CDungeon_SelectDungeon::s_Mat_DungeonPix[] =
{
	imread("./ImagePacks2/Map/select/rolland0.png", -1),
	imread("./ImagePacks2/Map/select/rollanddeep0.png", -1)
};

Mat CDungeon_SelectDungeon::s_Mat_DungeonPix_Select[] =
{
	imread("./ImagePacks2/Map/select/rolland1.png", -1),
	imread("./ImagePacks2/Map/select/rollanddeep1.png", -1)
};

int CDungeon_SelectDungeon::s_PixPos[][2] = { 207,372 ,357,165 };
int CDungeon_SelectDungeon::s_SelectPixPos[][2] = { 180,376,334,162 };
CDungeon_SelectDungeon::CDungeon_SelectDungeon()
{
	m_Quit = false;
	m_NextDungeon = NULL;
}

CDungeon_SelectDungeon::~CDungeon_SelectDungeon()
{

}


void CDungeon_SelectDungeon::HandleMouse(int Event, int x, int y, int flags, void* param)
{
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

void CDungeon_SelectDungeon::DoHandleInput(int input)
{
	switch (input)
	{
	case KEY_SPACE:
		if (m_SelectedDungeon == DUNGEON_ROLLAND)
		{
			m_Quit = true;
			m_NextDungeon = new CDungeon_Rolland();
			return;
		}
		else if (m_SelectedDungeon == DUNGEON_ROLLANDDEEP)
		{
			m_Quit = true;
			m_NextDungeon = new CDungeon_RollandDeep();
			return;
		}
		break;
	}
}

void CDungeon_SelectDungeon::Update()
{

}

void CDungeon_SelectDungeon::DoRender(Mat& mat)
{
	s_Mat_BG.copyTo(mat);
	__RenderDungeonPix(mat, DUNGEON_ROLLAND, m_SelectedDungeon == DUNGEON_ROLLAND);
	__RenderDungeonPix(mat, DUNGEON_ROLLANDDEEP, m_SelectedDungeon == DUNGEON_ROLLANDDEEP);
}

void CDungeon_SelectDungeon::DoInitDungeon()
{

}

void CDungeon_SelectDungeon::__RenderDungeonPix(Mat& mat, int dungeon, bool select)
{
	Mat pix = select ? s_Mat_DungeonPix_Select[dungeon] : s_Mat_DungeonPix[dungeon];
	int xx = select ? s_SelectPixPos[dungeon][0] : s_PixPos[dungeon][0];
	int yy = select ? s_SelectPixPos[dungeon][1] : s_PixPos[dungeon][1];
	for (int i = 0; i < pix.rows; i++)
	{
		uchar* pixdata = pix.ptr<uchar>(i);
		uchar* matdata = mat.ptr<uchar>(i + yy);
		for (int j = 0; j < pix.cols; j++)
		{
			int k = 4 * j;
			if (pixdata[k + 3] > 50)
			{
				matdata[xx * 4 + k] = pixdata[k];
				matdata[xx * 4 + k + 1] = pixdata[k + 1];
				matdata[xx * 4 + k + 2] = pixdata[k + 2];
				matdata[xx * 4 + k + 3] = pixdata[k + 3];
			}
		}
	}
}
