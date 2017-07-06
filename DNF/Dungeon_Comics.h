#pragma once
#include "Dungeon.h"
class CDungeon_Comics :
	public CDungeon
{
public:
	CDungeon_Comics();
	~CDungeon_Comics();


	void DoHandleInput(int input);


	void Update();


	void DoRender(Mat& mat);


	void DoInitDungeon();


	void HandleMouse(int Event, int x, int y, int flags, void* param);

private:
	Mat m_Mat_Comics[11];
	Mat m_Mat_NextBtn[2], m_Mat_PreBtn[2], m_Mat_EndBtn[2];
	Rect m_PreBtnRect, m_NextBtnRect, m_EndBtnRect;
	int m_MouseSelect;
	int m_Pages;
};

