#pragma once
#include "Dungeon.h"
class CDungeon_RollandDeep :
	public CDungeon
{
public:
	CDungeon_RollandDeep();
	~CDungeon_RollandDeep();

	void DoInitDungeon();


	void DoRender(Mat& mat);
};

