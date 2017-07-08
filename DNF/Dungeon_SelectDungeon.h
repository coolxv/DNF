#pragma once
#include "Dungeon.h"

/**
 * @class CDungeon_SelectDungeon
 * @brief ѡ����³ǽ���
 * 
 *
 */
class CDungeon_SelectDungeon :
	public CDungeon
{
	/** @brief  ����ѡ��ĵ��³� */
	enum DUNGEON
	{
		DUNGEON_ROLLAND,	/**<  ���� */
		DUNGEON_ROLLANDDEEP,	/**<  ����� */
		DUNGEON_MAZE,	/**<  �Թ� */
		DUNGEON_NONE	/**<  δѡ���κε��³� */
	};
public:
	static Mat s_Mat_BG; /**<  ������Դͼ */
	static Mat s_Mat_DungeonPix[3], s_Mat_DungeonPix_Select[3];	/**<  ���³�ͼ����Դͼ */
	static int s_PixPos[3][2];	/**<  ���³�ͼ������ */
	static int s_SelectPixPos[3][2];	/**<  ѡ�к�ĵ��³�ͼ������ */
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
	 * @brief ���ƿ�ѡ���³�ͼ��
	 * 
	 * 
	 * @param  Mat & mat	������ͼ
	 * @param  int dungeon	��Ҫ�����Ƶĵ��³�
	 * @param  bool select	�õ��³��Ƿ�ѡ��
	 * @return  void  
	 */
	 void __RenderDungeonPix(Mat& mat, int dungeon, bool select);
	 int m_SelectedDungeon = DUNGEON_NONE; /**<  ��ǰ��ѡ�е� */
};
