#pragma once
#include "Dungeon.h"

class CDungeon_Home :
	public CDungeon
{
public:
	static Mat s_Mat_BG, s_Mat_Gate, s_Mat_Gate_Mask;
	static Mat s_Mat_Seria[10], s_Mat_Seria_Mask[10];
public:
	CDungeon_Home();
	~CDungeon_Home();

	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	clock_t m_clock_SeriaRender;
	int m_SeriaMatId;
};
