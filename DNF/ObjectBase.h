#pragma once
#include "stdafx.h"

using namespace cv;
class CObjectBase
{

public:
	virtual void DoRender(Mat& mat, int viewX) = 0;
	Rect GetRectXY() { return Rect(m_X, m_Y - m_Thick, m_Width, m_Thick); } //��ȡ��xy���ͶӰ
	Rect GetRectXZ() { return Rect(m_X, m_Y - m_Height - m_Z / 2, m_Width, m_Height); }
	CObjectBase();
	~CObjectBase();

protected:
	int m_Thick; //y���ϵĺ��
	int m_Width; //x
	int m_Height; //z
	int m_X, m_Y, m_Z; //�������½ǵ�����

	int m_Gravity; //���� ��������Ϊ��
				   //ʵ�ִ��������Ծ
	int m_ZSpeed; //z���ٶ� ��������Ϊ��
	int m_JumpDir; //��Ծ����
	int m_MoveDirection; //�ƶ�����
	int m_Orientation = DIR_RIGHT; //����

public:
	static void Render(Mat& bg, int viewX, int viewWidth, int viewHeight, int offsetY, int x, int y, Mat& mat, Mat& mat_mask);

	static bool Cmp(const CObjectBase* a, const CObjectBase* b)
	{
		return a->m_Y - a->m_Thick < b->m_Y - b->m_Thick;
	}
	static int GetRandNum(int a, int b)
	{
		return   (rand() % (b - a+1) + a);
	}

	int GetX() { return m_X; }
	int GetY() { return m_Y; }
	int GetZ() { return m_Z; }
	int GetThick() { return m_Thick; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }
};

