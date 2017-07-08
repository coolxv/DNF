#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_Home
 * @brief 游戏"城镇"地下城
 * 
 *
 */
class CDungeon_Home :
	public CDungeon
{
public:
	CDungeon_Home();
	~CDungeon_Home();

	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	static Mat s_Mat_BG, s_Mat_Gate, s_Mat_Gate_Mask; /**<  门资源图 */
	static Mat s_Mat_Seria[10], s_Mat_Seria_Mask[10];	/**< 赛利亚资源图 */
	clock_t m_clock_SeriaRender;	/**<  实现赛利亚动画的计时器 */
	int m_SeriaMatId;	/**<  当前绘制赛利亚的资源图序号 */
};
