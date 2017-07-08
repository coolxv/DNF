#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_Comics
 * @brief 游戏开始漫画漫画
 * 
 *
 */
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
	Mat m_Mat_Comics[11];	/**<  漫画资源图 */
	Mat m_Mat_NextBtn[2], m_Mat_PreBtn[2], m_Mat_EndBtn[2];	/**<  按钮资源图 */
	Rect m_PreBtnRect, m_NextBtnRect, m_EndBtnRect;	/**<  按钮判定矩阵 */
	int m_MouseSelect;	/**< 当前鼠标选中的按钮 */
	int m_Pages;	/**<  当前漫画显示的页数 */
};

