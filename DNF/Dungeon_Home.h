#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_Home
 * @brief ��Ϸ"����"���³�
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
	static Mat s_Mat_BG, s_Mat_Gate, s_Mat_Gate_Mask; /**<  ����Դͼ */
	static Mat s_Mat_Seria[10], s_Mat_Seria_Mask[10];	/**< ��������Դͼ */
	clock_t m_clock_SeriaRender;	/**<  ʵ�������Ƕ����ļ�ʱ�� */
	int m_SeriaMatId;	/**<  ��ǰ���������ǵ���Դͼ��� */
};
