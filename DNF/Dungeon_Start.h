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
	clock_t  m_Clock_PreUpdae;	/**<  ��һ�θ��»��Ƶ�ʱ�� */
	Mat m_Mat_BG,m_Mat_BG_Loading;	/**<  ������Դͼ */
	Mat m_Mat_Dot[24];	/**<  ��ת��������Դͼ */
	int m_DotMatId;	/**<  ѡ�񶯻�����Դ��� */

	
	/**
	* @brief �ϲ�����Mat
	*
	*
	* @param  Mat & a	Mata
	* @param  Mat & b	Matb
	* @param  int x b�ϲ���a�����Ͻ�����x
	* @param  int y	b�ϲ���a�����Ͻ�����y
	* @param  int h	��Ҫ���Ե�͸����
	* @return  void
	*/
	 void __Merge(Mat& a, Mat& b, int x, int y, int h);
};

