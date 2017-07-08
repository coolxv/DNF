#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_Start
 * @brief 游戏启动界面
 * 
 *	实现游戏启动的绘制
 */
class CDungeon_Start :
	public CDungeon
{
public:
	CDungeon_Start();
	~CDungeon_Start();

	virtual void DoHandleInput(int input);


	virtual void Update();


	virtual void DoRender(Mat& mat);


	virtual void DoInitDungeon();


	virtual void HandleMouse(int Event, int x, int y, int flags, void* param);

private:
	clock_t  m_Clock_PreUpdae;	/**<  上一次更新绘制的时间 */
	Mat m_Mat_BG,m_Mat_BG_Loading;	/**<  背景资源图 */
	Mat m_Mat_Dot[24];	/**<  旋转动画的资源图 */
	int m_DotMatId;	/**<  选择动画的资源序号 */

	
	/**
	* @brief 合并两个Mat
	*
	*
	* @param  Mat & a	Mata
	* @param  Mat & b	Matb
	* @param  int x b合并到a的左上角坐标x
	* @param  int y	b合并到a的左上角坐标y
	* @param  int h	需要忽略的透明度
	* @return  void
	*/
	 void __Merge(Mat& a, Mat& b, int x, int y, int h);
};

