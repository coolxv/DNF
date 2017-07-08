#pragma once
#include "Dungeon.h"


/**
 * @class CDungeon_Rolland
 * @brief "����"���³�
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
	Mat m_Mat_DungeonLoading;	/**<  ���³Ǽ��ؽ�����Դͼ */
	Mat m_Mat_MinMapBG,m_Mat_MinMapBG_Mask; /**<  ���Ͻ�С��ͼ������Դͼ */
	Mat m_Mat_MinMap[6];	 /**<  ���Ͻ�С��ͼ��Դͼ */
	Mat m_Mat_MinMap_Character, m_Mat_MinMap_Character_Mask; /**<  ���Ͻ�С��ͼ��Դͼ */
	Mat m_Mat_MinMap_Boos, m_Mat_MinMap_Boos_Mask; /**<  ���Ͻ�С��ͼ��Դͼ */
	Mat m_Mat_MinMap_Unknown[2]; /**<  ���Ͻ�С��ͼ��Դͼ */
	Point m_MinMapPos[6]; /**<  ���Ͻ�С��ͼ��ÿ����������� */
};
