#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_SelectDungeon
 * @brief 选择地下城界面
 * 
 *
 */
class CDungeon_SelectDungeon :
	public CDungeon
{
	/** @brief  可以选择的地下城 */
	enum DUNGEON
	{
		DUNGEON_ROLLAND,	/**<  洛兰 */
		DUNGEON_ROLLANDDEEP,	/**<  洛兰深处 */
		DUNGEON_MAZE,	/**<  迷宫 */
		DUNGEON_NONE	/**<  未选中任何地下城 */
	};
public:
	static Mat s_Mat_BG; /**<  背景资源图 */
	static Mat s_Mat_DungeonPix[3], s_Mat_DungeonPix_Select[3];	/**<  地下城图标资源图 */
	static int s_PixPos[3][2];	/**<  地下城图标坐标 */
	static int s_SelectPixPos[3][2];	/**<  选中后的地下城图标坐标 */
public:
	CDungeon_SelectDungeon();
	~CDungeon_SelectDungeon();


	void HandleMouse(int Event, int x, int y, int flags, void* param);
	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	
	/**
	 * @brief 绘制可选地下城图标
	 * 
	 * 
	 * @param  Mat & mat	背景底图
	 * @param  int dungeon	需要被绘制的地下城
	 * @param  bool select	该地下城是否被选中
	 * @return  void  
	 */
	 void __RenderDungeonPix(Mat& mat, int dungeon, bool select);
	 int m_SelectedDungeon = DUNGEON_NONE; /**<  当前被选中的 */
};
