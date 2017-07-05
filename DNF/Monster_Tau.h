#pragma once
#include "Monster.h"
class CMonSter_Tau :
	public CMonster
{
public:
	static Mat s_Mat_Body[32], s_Mat_Body_Mask[32], s_Mat_Avator;
public:
	CMonSter_Tau(CStage* stage, int x, int y, int z);
	~CMonSter_Tau();

	void DoRender(Mat& mat, int viewX);

	Rect GetAttackRect();
	int GetDamage();
	int GetArmor();
	Mat GetAvator() { return s_Mat_Avator; };
	String GetName() { return String("Lv5 Ngau Tau Monster"); }

	void SetPreHit(clock_t t) { m_PreHit = t; }
	clock_t GetPreHit() { return m_PreHit; }

	void SetPreRoar(clock_t t) { m_PreRoar = t; }
	clock_t GetPreRoar() { return m_PreRoar; }
private:
	void __InitOffset();
	Point m_Offset_LeftBottom[32], m_Offset_LeftBottom_Left[32]; //角色对应图片左下角偏移
	clock_t m_PreHit; //上一次使用冲撞技能的时间
	clock_t m_PreRoar; //上一次使用吼叫的时间
};