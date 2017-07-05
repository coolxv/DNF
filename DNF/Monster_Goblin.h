#pragma once
#include "Monster.h"
class CMonster_Goblin :
	public CMonster
{
public:
	static Mat s_Mat_Body[17],s_Mat_Body_Mask[17] , s_Mat_Avator;;
public:
	CMonster_Goblin(CStage* stage, int x, int y, int z);
	~CMonster_Goblin();

	void DoRender(Mat& mat, int viewX);
	int GetDamage();
	int GetArmor();
	Rect GetAttackRect();
	Mat GetAvator() { return s_Mat_Avator; };
	String GetName() { return String("Lv1 Goblin"); }
private:
	void __InitOffset();
	Point m_Offset_LeftBottom[17], m_Offset_LeftBottom_Left[17]; //½ÇÉ«¶ÔÓ¦Í¼Æ¬×óÏÂ½ÇÆ«ÒÆ
};

