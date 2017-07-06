#include "Hud.h"
#include <string>


CHud::CHud()
{
}


CHud::~CHud()
{
}

void CHud::Render(Mat& mat)
{
	__MergeMat(mat, m_Mat_Hud, m_Mat_Hud_Mask, 50);
	if (m_hp_percentage_animation >= m_hp_percentage_cur+5)
		__ShowHpAnimation(mat);
	else
		__ShowHp(mat, m_Character->GetHp() * 100 / m_Character->GetTotalHp());

	if(m_Hp_onMouse)
		putText(mat, format("%d/%d", m_Character->GetHp(), m_Character->GetTotalHp()), Point(10, 550), CV_FONT_HERSHEY_PLAIN
			, 0.6, Scalar(255, 255, 255), 1);
	clock_t cur = clock();
	//------------------绘制技能栏--------------
	if (cur - m_Character->GetPreEffectZ() >= COOLDOWN_Z)
		m_Mat_EffectZ.copyTo(mat(Rect(378, 503 + 49, m_Mat_EffectZ.cols, m_Mat_EffectZ.rows)), m_Mat_EffectZ_Mask);
	else
	{
		double p = (cur*1.0 - m_Character->GetPreEffectZ()) / COOLDOWN_Z;
		Mat mask = m_Mat_EffectMask.rowRange(0, p * 28);
		m_Mat_EffectZ_Cool.copyTo(mat(Rect(378, 503 + 49, m_Mat_EffectZ_Cool.cols, m_Mat_EffectZ_Cool.rows)), m_Mat_EffectZ_Cool_Mask);
		Mat roi = mat(Rect(378, 503 + 49 + 28 - 28 * p, mask.cols, mask.rows));
		addWeighted(mask, 0.8, roi, 1, 0, roi);
	}

	if (cur - m_Character->GetPreEffectA() >= COOLDOWN_A)
		m_Mat_EffectA.copyTo(mat(Rect(408, 503 + 49, m_Mat_EffectA.cols, m_Mat_EffectA.rows)), m_Mat_EffectA_Mask);
	else
	{
		double p = (cur*1.0 - m_Character->GetPreEffectA()) / COOLDOWN_A;
		Mat mask = m_Mat_EffectMask.rowRange(0, p * 28);
		m_Mat_EffectA_Cool.copyTo(mat(Rect(408, 503 + 49, m_Mat_EffectA_Cool.cols, m_Mat_EffectA_Cool.rows)), m_Mat_EffectA_Cool_Mask);
		Mat roi = mat(Rect(408, 503 + 49 + 28 - 28 * p, mask.cols, mask.rows));
		addWeighted(mask, 0.8, roi, 1, 0, roi);
	}

	if (cur - m_Character->GetPreEffectS() >= COOLDOWN_S)
		m_Mat_EffectS.copyTo(mat(Rect(438, 503 + 49, m_Mat_EffectS.cols, m_Mat_EffectS.rows)), m_Mat_EffectS_Mask);
	else
	{
		double p = (cur*1.0 - m_Character->GetPreEffectS()) / COOLDOWN_S;
		Mat mask = m_Mat_EffectMask.rowRange(0, p * 28);
		m_Mat_EffectS_Cool.copyTo(mat(Rect(438, 503 + 49, m_Mat_EffectS_Cool.cols, m_Mat_EffectS_Cool.rows)), m_Mat_EffectS_Cool_Mask);
		Mat roi = mat(Rect(438, 503 + 49 + 28 - 28 * p, mask.cols, mask.rows));
		addWeighted(mask, 0.8, roi, 1, 0, roi);
	}

	if (cur - m_Character->GetPreEffectD() >= COOLDOWN_D)
		m_Mat_EffectD.copyTo(mat(Rect(468, 503 + 49, m_Mat_EffectD.cols, m_Mat_EffectD.rows)), m_Mat_EffectD_Mask);
	else
	{
		double p = (cur*1.0 - m_Character->GetPreEffectD()) / COOLDOWN_D;
		Mat mask = m_Mat_EffectMask.rowRange(0,p*28);
		m_Mat_EffectD_Cool.copyTo(mat(Rect(468, 503 + 49, m_Mat_EffectD_Cool.cols, m_Mat_EffectD_Cool.rows)), m_Mat_EffectD_Cool_Mask);
		Mat roi = mat(Rect(468,503 + 49 +28- 28 * p,mask.cols,mask.rows));
		addWeighted(mask, 0.8, roi, 1, 0, roi);
	}
	//------------------绘制fps--------------
	m_FPSCount++;
	if (cur - m_Clock_PreRender >= 1000) //1s计算一次平均帧率
	{
		m_fps = m_FPSCount / ((cur - m_Clock_PreRender) / 1000);
		m_Clock_PreRender = cur;
		m_FPSCount = 0;
	}
	putText(mat, format("FPS:%d", m_fps), Point(320, 30), CV_FONT_HERSHEY_PLAIN
		, 1, Scalar(255, 255, 255), 1);
}

void CHud::__ShowHp(Mat& mat, int hp_percentage)
{
	int row =(int) ((1 - hp_percentage*1.0 / 100) * m_Mat_Hp.rows);
	Mat bottom = m_Mat_Hp.rowRange(row, m_Mat_Hp.rows);
	Mat bottom_ = m_Mat_Hp_Mask.rowRange(row, m_Mat_Hp_Mask.rows);
	bottom.copyTo(mat(Rect(12,503+14+row,bottom.cols,bottom.rows)),bottom_);
}


void CHud::__ShowHpAnimation(Mat& mat)
{
	int k = 1;
	int row1 = (100 - (m_hp_percentage_animation))* m_Mat_Hp.rows / 100;
	int row2 = (100 - m_hp_percentage_cur) * m_Mat_Hp.rows / 100;
	Mat top = m_Mat_Hp_w.rowRange(row1, row2);

	Mat bottom = m_Mat_Hp.rowRange(row2 , m_Mat_Hp.rows);
	Mat bottom_ = m_Mat_Hp_Mask.rowRange(row2 , m_Mat_Hp_Mask.rows);
	bottom.copyTo(mat(Rect(12, 503 + 14 + row2 , bottom.cols, bottom.rows)), bottom_);
	Mat ROI = mat(Rect(12, 503 + 14 + row1 + k, top.cols, top.rows));
	addWeighted(top, 1-(row1*1.0/row2), ROI, 1, 0, ROI);
}


void CHud::Update()
{
	m_hp_percentage_cur = m_Character->GetHp() * 100 / m_Character->GetTotalHp();
	m_hp_percentage_animation -= 1;
	if (m_hp_percentage_animation < m_hp_percentage_cur)
		m_hp_percentage_animation = m_hp_percentage_cur;
}

void CHud::HandleInput(char key)
{

}

void CHud::HandleMouse(int Event, int x, int y, int flags, void* param)
{
	switch (Event)
	{
	case 0:
		m_Hp_onMouse = sqrt((x - 40)*(x - 40) + (y - 545)*(y - 545)) <= 28.0;
		break;
	}
}

void CHud::Initial()
{
	m_fps = 0;
	m_FPSCount = 0;
	m_Clock_PreRender = clock();
	m_Mat_Hud = imread("./ImagePacks2/BaseUI/mainhud.png", -1);
	m_Mat_Hud_Mask = imread("./ImagePacks2/BaseUI/mainhud.png", 0);
	m_Mat_Hp = imread("./ImagePacks2/BaseUI/hp.png", -1);
	m_Mat_Hp_Mask = imread("./ImagePacks2/BaseUI/hp.png", 0);
	m_Mat_Hp_w = imread("./ImagePacks2/BaseUI/hp_w.png", -1);
	m_Mat_Mp = imread("./ImagePacks2/BaseUI/mp.png", -1);
	m_Mat_Mp_Mask = imread("./ImagePacks2/BaseUI/mp.png", 0);

	m_Mat_EffectZ = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/z.png", -1);
	m_Mat_EffectZ_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/z.png", 0);
	m_Mat_EffectZ_Cool = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/zc.png", -1);
	m_Mat_EffectZ_Cool_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/zc.png", 0);

	m_Mat_EffectA = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/a.png", -1);
	m_Mat_EffectA_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/a.png", 0);
	m_Mat_EffectA_Cool = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/ac.png", -1);
	m_Mat_EffectA_Cool_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/ac.png", 0);

	m_Mat_EffectS = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/s.png", -1);
	m_Mat_EffectS_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/s.png", 0);
	m_Mat_EffectS_Cool = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/sc.png", -1);
	m_Mat_EffectS_Cool_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/sc.png", 0);

	m_Mat_EffectD = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/d.png", -1);
	m_Mat_EffectD_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/d.png", 0);
	m_Mat_EffectD_Cool = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/dc.png", -1);
	m_Mat_EffectD_Cool_Mask = imread("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/effect/dc.png", 0);

	m_Mat_EffectMask = Mat(28,28,CV_8UC4,Scalar(60,60,60,0));
}


void CHud::SetCharacter(CCharacter* character)
{
	m_Character = character;
	m_hp_percentage_cur = m_Character->GetHp()*100/ m_Character->GetTotalHp();
	m_hp_percentage_animation = m_hp_percentage_cur;
}

void CHud::__MergeMat(Mat& a, Mat& b, Mat& b_, int div)
{
	int tmp = a.rows;
	copyMakeBorder(a, a, 0, b.rows - div, 0, 0, 0);
	Mat roi(a, Rect(0, tmp - div, b.cols, b.rows));
	b.copyTo(roi, b_);
}

