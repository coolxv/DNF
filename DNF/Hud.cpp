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
	m_Mat_Hud = imread("./ImagePacks2/BaseUI/mainhud.png", -1);
	m_Mat_Hud_Mask = imread("./ImagePacks2/BaseUI/mainhud.png", 0);
	m_Mat_Hp = imread("./ImagePacks2/BaseUI/hp.png", -1);
	m_Mat_Hp_Mask = imread("./ImagePacks2/BaseUI/hp.png", 0);
	m_Mat_Hp_w = imread("./ImagePacks2/BaseUI/hp_w.png", -1);
	m_Mat_Mp = imread("./ImagePacks2/BaseUI/mp.png", -1);
	m_Mat_Mp_Mask = imread("./ImagePacks2/BaseUI/mp.png", 0);
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

