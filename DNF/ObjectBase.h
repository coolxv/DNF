#pragma once
#include "stdafx.h"

using namespace cv;

/**
 * @class CObjectBase
 * @brief �������
 * 
 *��Ϸ�����ж���Ļ���
 */
class CObjectBase
{

public:
	virtual void DoRender(Mat& mat, int viewX) = 0;
	
	/**
	 * @brief ��ȡ��xy���ͶӰ
	 * 
	 * 
	 * @return  Rect  ����ͶӰ����
	 */
	 Rect GetRectXY(); 
	
	/**
	 * @brief ��ȡ��xz���ͶӰ
	 * 
	 * 
	 * @return  Rect  ����ͶӰ����
	 */
	 Rect GetRectXZ();
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @return    
	 */
	 CObjectBase();
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CObjectBase();

protected:
	int m_Thick; /**<  y���ϵĺ��*/
	int m_Width; /**<  ��x���ϵĿ��*/
	int m_Height; /**<  ��z���ϵĸ߶�*/
	int m_X, m_Y, m_Z; /**<  �������½ǵ�����*/

	int m_Gravity; /**<  ���� ��������Ϊ��*/
	int m_ZSpeed; /**<  z���ٶ� ��������Ϊ��*/
	int m_JumpDir; /**<  ��Ծ����*/
	int m_MoveDirection; /**<  �ƶ�����*/
	int m_Orientation = DIR_RIGHT; /**<  ����*/

public:
	static void Render(Mat& bg, int viewX, int viewWidth, int viewHeight, int offsetY, int x, int y, Mat& mat, Mat& mat_mask);

	
	/**
	 * @brief �ȽϺ���
	 * 
	 * ���ڱȽ϶������˳��
	 * @param  const CObjectBase * a
	 * @param  const CObjectBase * b
	 * @return  bool  
	 */
	 static bool Cmp(const CObjectBase* a, const CObjectBase* b)
	{
		return a->m_Y - a->m_Thick < b->m_Y - b->m_Thick;
	}
	
	/**
	 * @brief ����һ��[a,b]��Χ�������
	 * 
	 * 
	 * @param  int a
	 * @param  int b
	 * @return  int  
	 */
	 static int GetRandNum(int a, int b)
	{
		return   (rand() % (b - a+1) + a);
	}

	
	/**
	 * @brief ����x����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetX() { return m_X; }
	
	/**
	 * @brief ����y����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetY() { return m_Y; }
	
	/**
	 * @brief ����z����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZ() { return m_Z; }
	
	/**
	 * @brief ���غ��
	 * 
	 * 
	 * @return  int  
	 */
	 int GetThick() { return m_Thick; }
	
	/**
	 * @brief ���ؿ��
	 * 
	 * 
	 * @return  int  
	 */
	 int GetWidth() { return m_Width; }
	
	/**
	 * @brief ���ظ߶�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHeight() { return m_Height; }
};

