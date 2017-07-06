#pragma once
#include "Dungeon.h"
/**
 * @class CDungeon_Start
 * @brief ��Ϸ��������
 * 
 *	ʵ����Ϸ�����Ļ���
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
	int m_DotMatId;
	clock_t  m_Clock_PreUpdae;
	Mat m_Mat_BG,m_Mat_BG_Loading;
	Mat m_Mat_Dot[24];

	void __Merge(Mat& a, Mat& b, int x, int y, int h);
};

