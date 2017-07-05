#pragma once
#include "Monster.h"
class CMonster_BossGoblin :
	public CMonster
{
public:
	static Mat s_Mat_Body[17], s_Mat_Body_Mask[17],s_Mat_Avator;
	CMonster_BossGoblin(CStage* stage, int x, int y, int z);
	virtual ~CMonster_BossGoblin();
	void DoRender(Mat& mat, int viewX);

	Rect GetAttackRect();
	int GetDamage();
	int GetArmor();
	Mat GetAvator() { return s_Mat_Avator; };
	String GetName() { return String("Lv3 Throwing Goblin"); }
private:
	void __InitOffset();
	Point m_Offset_LeftBottom[17], m_Offset_LeftBottom_Left[17]; //½ÇÉ«¶ÔÓ¦Í¼Æ¬×óÏÂ½ÇÆ«ÒÆ
};

