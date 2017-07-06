#pragma once
#include "stdafx.h"
class CDungeon;
class CAnimationEffect
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();
	virtual void DoRender(Mat& mat, int viewX) = 0;
	bool GetComplete() { return m_Complete; }
	virtual void onMouse(int Event, int x, int y, int flags, void* param) {};
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

class CResultAnimation
	:public CAnimationEffect
{
private:
	enum __SELECT
	{
		RETURN, CONTINUE, OTHERDUNGEON, NONE
	};
public:
	static Mat s_Mat_panel,s_Mat_time_text,s_Mat_score_text1, s_Mat_score_text2, s_Mat_score_text3,s_Mat_exp_text;
	static Mat s_Mat_min, s_Mat_sec;
	static Mat s_Mat_Number[10],s_Mat_ScoreRank[9];

	static Mat s_Mat_SelectBG,s_Mat_Return[2],s_Mat_Other[2],s_Mat_Continue[2];
	CResultAnimation(int score,int score_rank,int exp,int min,int sec,int lsec
		,int min_record,int sec_record,int lsec_record,CDungeon* cur_dungeon);
	~CResultAnimation();
	void DoRender(Mat& mat, int viewX);

	void onMouse(int Event, int x, int y, int flags, void* param);
private:
	void __Merge(Mat& a, Mat& b, int x, int y, int h);
	void __ShowNumber(Mat& bg, int x, int y, int num);
	void __ShowTime(Mat& bg, int x, int y, int min, int sec, int lsec);
	int m_Score;
	int m_Score_Rank;
	int m_Exp;
	int m_Min, m_Sec, m_LSec;
	int m_Min_Record, m_Sec_Record, m_LSec_Record;
	bool m_IsSelecting;
	int m_selected;
	Rect m_rect_return,m_rect_other,m_rect_continue;
	CDungeon* m_CurDungeon;
	clock_t m_StartTime;
};
