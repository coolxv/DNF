#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Dungeon.h"
class CHud
{
public:
	CHud();
	~CHud();

	void Render(Mat& mat);
	void Update();
	void HandleInput(char key);
	void HandleMouse(int Event, int x, int y, int flags, void* param);

	void Initial();
	void SetCharacter(CCharacter* character);
	void SetDungeon(CDungeon* dungeon) { m_Dungeon = dungeon; }

	void __MergeMat(Mat& a, Mat& b, Mat& b_, int div);
	void __ShowHp(Mat& mat,int hp_percentage);
	void __ShowHpAnimation(Mat& mat);

private:
	int m_hp_percentage_cur;
	int m_hp_percentage_animation;

	CCharacter* m_Character;
	CDungeon* m_Dungeon;

	Mat m_Mat_Hud,m_Mat_Hud_Mask;
	Mat m_Mat_Hp,m_Mat_Hp_Mask,m_Mat_Hp_w;
	Mat m_Mat_Mp,m_Mat_Mp_Mask;
	Mat m_Mat_EffectA, m_Mat_EffectA_Mask, m_Mat_EffectA_Cool, m_Mat_EffectA_Cool_Mask;
	Mat m_Mat_EffectS, m_Mat_EffectS_Mask, m_Mat_EffectS_Cool, m_Mat_EffectS_Cool_Mask;
	Mat m_Mat_EffectD, m_Mat_EffectD_Mask, m_Mat_EffectD_Cool, m_Mat_EffectD_Cool_Mask;
	Mat m_Mat_EffectZ, m_Mat_EffectZ_Mask, m_Mat_EffectZ_Cool, m_Mat_EffectZ_Cool_Mask;
	Mat m_Mat_EffectMask;


	bool m_Hp_onMouse;

	int m_FPSCount;
	int m_fps;
	clock_t m_Clock_PreRender;
};

