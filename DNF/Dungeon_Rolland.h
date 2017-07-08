#pragma once
#include "Dungeon.h"


/**
 * @class CDungeon_Rolland
 * @brief "洛兰"地下城
 * 
 *
 */
class CDungeon_Rolland :
	public CDungeon
{
public:
	CDungeon_Rolland();
	~CDungeon_Rolland();
	void DoInitDungeon();

	void DoRender(Mat& mat);


private:
	Mat m_Mat_DungeonLoading;	/**<  地下城加载界面资源图 */
	Mat m_Mat_MinMapBG,m_Mat_MinMapBG_Mask; /**<  右上角小地图背景资源图 */
	Mat m_Mat_MinMap[6];	 /**<  右上角小地图资源图 */
	Mat m_Mat_MinMap_Character, m_Mat_MinMap_Character_Mask; /**<  右上角小地图资源图 */
	Mat m_Mat_MinMap_Boos, m_Mat_MinMap_Boos_Mask; /**<  右上角小地图资源图 */
	Mat m_Mat_MinMap_Unknown[2]; /**<  右上角小地图资源图 */
	Point m_MinMapPos[6]; /**<  右上角小地图的每个房间的坐标 */
};
