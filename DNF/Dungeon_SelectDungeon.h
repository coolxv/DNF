#pragma once
#include "Dungeon.h"

class CDungeon_SelectDungeon :
	public CDungeon
{
	enum DUNGEON
	{
		DUNGEON_ROLLAND, DUNGEON_ROLLANDDEEP, DUNGEON_MAZE,DUNGEON_NONE
	};
public:
	static Mat s_Mat_BG;
	static Mat s_Mat_DungeonPix[3], s_Mat_DungeonPix_Select[3];
	static int s_PixPos[3][2];
	static int s_SelectPixPos[3][2];
public:
	CDungeon_SelectDungeon();
	~CDungeon_SelectDungeon();


	void HandleMouse(int Event, int x, int y, int flags, void* param);
	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	void __RenderDungeonPix(Mat& mat, int dungeon, bool select);
	int m_SelectedDungeon = DUNGEON_NONE; //当前被选中的
};
