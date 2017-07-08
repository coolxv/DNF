#pragma once
#include "Dungeon.h"



class CDungeon_Rolland :
	public CDungeon
{
public:
	CDungeon_Rolland();
	~CDungeon_Rolland();
	void DoInitDungeon();

	void DoRender(Mat& mat);


private:
	Mat m_Mat_DungeonLoading;
	Mat m_Mat_MinMapBG,m_Mat_MinMapBG_Mask;
	Mat m_Mat_MinMap[6];
	Mat m_Mat_MinMap_Character, m_Mat_MinMap_Character_Mask;
	Mat m_Mat_MinMap_Boos, m_Mat_MinMap_Boos_Mask;
	Mat m_Mat_MinMap_Unknown[2];
	Point m_MinMapPos[6];
};
