#pragma once
#include "stdafx.h"
class CAnimationEffect
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();
	virtual void DoRender(Mat& mat, int viewX) = 0;
	bool GetComplete() { return m_Complete; }
protected:
	bool m_Complete;
	int m_MatId;
	clock_t m_Clock_PreRender;
};

class CPhysicalAttackAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_Slash[3][3], s_Mat_Slash_Mask[3][3];
	CPhysicalAttackAnimation(Point3i point,int type);
	~CPhysicalAttackAnimation();
	void DoRender(Mat& mat, int viewX);
private:
	Point3d m_Point_Coor;
	int m_Type;
};

class CAwakeDEffectAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_Draw[30];
	CAwakeDEffectAnimation(int pos);
	~CAwakeDEffectAnimation() {};
	void DoRender(Mat& mat, int viewX);

private:
	Mat mask;
	int m_pos;
};


class CAwakeSEffectAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_DrawS[35];
	CAwakeSEffectAnimation(int pos);
	~CAwakeSEffectAnimation() {};
	void DoRender(Mat& mat, int viewX);

private:
	Mat mask;
	int m_pos;
};


class CNumberAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_Number[3][10];
	CNumberAnimation(long long num,Point3i p,int style);
	~CNumberAnimation() {};
	void DoRender(Mat& mat, int viewX);
private:
	int m_StayTime;
	int m_NumStyle;
	int m_Zspeed;
	clock_t m_Clock_stay;
	Point3i m_Pos;
	Point3i m_CurPos;
	int m_length;
	std::vector<int> m_v_num;
};
