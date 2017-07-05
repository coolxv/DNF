#pragma once
#include "stdafx.h"

using namespace cv;
class CObjectBase
{

public:
	virtual void DoRender(Mat& mat, int viewX) = 0;
	Rect GetRectXY() { return Rect(m_X, m_Y - m_Thick, m_Width, m_Thick); } //获取在xy面的投影
	Rect GetRectXZ() { return Rect(m_X, m_Y - m_Height - m_Z / 2, m_Width, m_Height); }
	CObjectBase();
	~CObjectBase();

protected:
	int m_Thick; //y轴上的厚度
	int m_Width; //x
	int m_Height; //z
	int m_X, m_Y, m_Z; //人物左下角的坐标

	int m_Gravity; //重力 方向向上为正
				   //实现带方向的跳跃
	int m_ZSpeed; //z轴速度 方向向上为正
	int m_JumpDir; //跳跃方向
	int m_MoveDirection; //移动方向
	int m_Orientation = DIR_RIGHT; //朝向

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

