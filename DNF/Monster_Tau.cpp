#include "Monster_Tau.h"
#include "Monster_Tau_State.h"

Mat CMonSter_Tau::s_Mat_Body[] = 
{
	imread("./ImagePacks2/Monster/tau/0.png", -1),
	imread("./ImagePacks2/Monster/tau/1.png", -1),
	imread("./ImagePacks2/Monster/tau/2.png", -1),
	imread("./ImagePacks2/Monster/tau/3.png", -1),
	imread("./ImagePacks2/Monster/tau/4.png", -1),
	imread("./ImagePacks2/Monster/tau/5.png", -1),
	imread("./ImagePacks2/Monster/tau/6.png", -1),
	imread("./ImagePacks2/Monster/tau/7.png", -1),
	imread("./ImagePacks2/Monster/tau/8.png", -1),
	imread("./ImagePacks2/Monster/tau/9.png", -1),
	imread("./ImagePacks2/Monster/tau/10.png", -1),
	imread("./ImagePacks2/Monster/tau/11.png", -1),
	imread("./ImagePacks2/Monster/tau/12.png", -1),
	imread("./ImagePacks2/Monster/tau/13.png", -1),
	imread("./ImagePacks2/Monster/tau/14.png", -1),
	imread("./ImagePacks2/Monster/tau/15.png", -1),
	imread("./ImagePacks2/Monster/tau/16.png", -1),
	imread("./ImagePacks2/Monster/tau/17.png", -1),
	imread("./ImagePacks2/Monster/tau/18.png", -1),
	imread("./ImagePacks2/Monster/tau/19.png", -1),
	imread("./ImagePacks2/Monster/tau/20.png", -1),
	imread("./ImagePacks2/Monster/tau/21.png", -1),
	imread("./ImagePacks2/Monster/tau/22.png", -1),
	imread("./ImagePacks2/Monster/tau/23.png", -1),
	imread("./ImagePacks2/Monster/tau/24.png", -1),
	imread("./ImagePacks2/Monster/tau/25.png", -1),
	imread("./ImagePacks2/Monster/tau/26.png", -1),
	imread("./ImagePacks2/Monster/tau/27.png", -1),
	imread("./ImagePacks2/Monster/tau/28.png", -1),
	imread("./ImagePacks2/Monster/tau/29.png", -1),
	imread("./ImagePacks2/Monster/tau/30.png", -1),
	imread("./ImagePacks2/Monster/tau/31.png", -1)
};

Mat CMonSter_Tau::s_Mat_Body_Mask[] = 
{
	imread("./ImagePacks2/Monster/tau/0.png", 0),
	imread("./ImagePacks2/Monster/tau/1.png", 0),
	imread("./ImagePacks2/Monster/tau/2.png", 0),
	imread("./ImagePacks2/Monster/tau/3.png", 0),
	imread("./ImagePacks2/Monster/tau/4.png", 0),
	imread("./ImagePacks2/Monster/tau/5.png", 0),
	imread("./ImagePacks2/Monster/tau/6.png", 0),
	imread("./ImagePacks2/Monster/tau/7.png", 0),
	imread("./ImagePacks2/Monster/tau/8.png", 0),
	imread("./ImagePacks2/Monster/tau/9.png", 0),
	imread("./ImagePacks2/Monster/tau/10.png", 0),
	imread("./ImagePacks2/Monster/tau/11.png", 0),
	imread("./ImagePacks2/Monster/tau/12.png", 0),
	imread("./ImagePacks2/Monster/tau/13.png", 0),
	imread("./ImagePacks2/Monster/tau/14.png", 0),
	imread("./ImagePacks2/Monster/tau/15.png", 0),
	imread("./ImagePacks2/Monster/tau/16.png", 0),
	imread("./ImagePacks2/Monster/tau/17.png", 0),
	imread("./ImagePacks2/Monster/tau/18.png", 0),
	imread("./ImagePacks2/Monster/tau/19.png", 0),
	imread("./ImagePacks2/Monster/tau/20.png", 0),
	imread("./ImagePacks2/Monster/tau/21.png", 0),
	imread("./ImagePacks2/Monster/tau/22.png", 0),
	imread("./ImagePacks2/Monster/tau/23.png", 0),
	imread("./ImagePacks2/Monster/tau/24.png", 0),
	imread("./ImagePacks2/Monster/tau/25.png", 0),
	imread("./ImagePacks2/Monster/tau/26.png", 0),
	imread("./ImagePacks2/Monster/tau/27.png", 0),
	imread("./ImagePacks2/Monster/tau/28.png", 0),
	imread("./ImagePacks2/Monster/tau/29.png", 0),
	imread("./ImagePacks2/Monster/tau/30.png", 0),
	imread("./ImagePacks2/Monster/tau/31.png", 0)
};

Mat CMonSter_Tau::s_Mat_Avator= imread("./ImagePacks2/Monster/tau/tau.png", -1);

CMonSter_Tau::CMonSter_Tau(CStage* stage, int x, int y, int z)
{
	m_Stage = stage;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_MatId = 0;
	m_Hp = MONSTER_TAU_HP; 
	m_Hp_Animation = MONSTER_TAU_HP;
	m_TotalHp = MONSTER_TAU_HP;
	m_Width = 120;
	m_Thick = 45;
	m_Height = 150;
	m_MoveSpeed = 20;
	m_NAttackSpeed = 500;

	m_PreHit = clock();
	m_PreRoar = clock();
	//SetState(new Monster_Goblin_StandingState(this));
	SetMoveDirection(DIR_LEFT);
	SetState(new CMonster_Tau_StandingState(this));
	__InitOffset();
}

CMonSter_Tau::~CMonSter_Tau()
{
}

void CMonSter_Tau::DoRender(Mat& mat, int viewX)
{
	int offsetY = CStage::s_OffsetY;
	Mat body, body_mask;
	if (m_Orientation == DIR_RIGHT)
	{
		body = s_Mat_Body[m_State->GetMatId()];
		body_mask = s_Mat_Body_Mask[m_State->GetMatId()];
	}
	else
	{
		flip(s_Mat_Body[m_State->GetMatId()], body, 1);
		flip(s_Mat_Body_Mask[m_State->GetMatId()], body_mask, 1);
	}

	int tx = (m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x);
	int ty = (m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y);
	Mat ROI;
	int xx = m_X - viewX - tx; //相对坐标
	int yy = m_Y - ty - m_Z / 2 + offsetY;
	if (xx >= CStage::s_ViewWidth || xx + body.cols <= 0) return;
	Render(mat, viewX, CStage::s_ViewWidth,  CStage::s_ViewHeight ,CStage::s_OffsetY, xx, yy, body, body_mask);
	//Mat tmp = body, tmp_ = body_mask;
	////处理人物会有一部分在屏幕外面的情况
	//if (xx < 0)
	//{
	//	tmp = body.colRange(abs(xx), body.cols - 1);
	//	tmp_ = body_mask.colRange(abs(xx), body_mask.cols - 1);
	//	xx = 0;
	//}
	//if (xx + body.cols >= CStage::s_ViewWidth)
	//{
	//	tmp = body.colRange(0, CStage::s_ViewWidth - xx - 1);
	//	tmp_ = body_mask.colRange(0, CStage::s_ViewWidth - xx - 1);
	//}
	//if (yy + body.rows >= CStage::s_ViewHeight + offsetY)
	//{
	//	tmp = body.rowRange(0, CStage::s_ViewHeight + offsetY - yy - 1);
	//	tmp_ = body_mask.rowRange(0, CStage::s_ViewHeight + offsetY - yy - 1);
	//}
	////rectangle(mat, GetAttackRect() + Point(-viewX, offsetY), Scalar(0, 0, 255), 3, 8, 0);
	//ROI = mat(Rect(xx, yy, tmp.cols, tmp_.rows));
	//tmp.copyTo(ROI, tmp_);
}

Rect CMonSter_Tau::GetAttackRect()
{
	Mat mMat = s_Mat_Body[m_State->GetMatId()];
	int tx = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x;
	int ty = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y;
	if (m_Orientation == DIR_RIGHT)
		return  Rect(tx >= 8 ? m_X - tx : m_X, m_Y - m_Thick, mMat.cols, m_Thick);
	else
	{
		if (abs(tx) <= 5)
			Rect(m_X - tx, m_Y - m_Thick, m_X + mMat.cols, m_Thick);
		return Rect(m_X - tx, m_Y - m_Thick, mMat.cols, m_Thick);
	}
	//return Rect(mX , mY - mThick - mZ / 2 , mMat.cols - tx, mThick);
}

int CMonSter_Tau::GetDamage()
{
	return RANDNUM(MONSTER_TAU_ATTACKPOWER, MONSTER_TAU_ATTACKPOWER_);
}

int CMonSter_Tau::GetArmor()
{
	return MONSTER_TAU_ARMOR;
}

void CMonSter_Tau::__InitOffset()
{
	m_Offset_LeftBottom[0] = Point(63, 164);
	m_Offset_LeftBottom[1] = Point(52, 177);
	m_Offset_LeftBottom[2] = Point(174, 216);
	m_Offset_LeftBottom[3] = Point(143, 230);
	m_Offset_LeftBottom[4] = Point(50, 274);
	m_Offset_LeftBottom[5] = Point(51, 170);
	m_Offset_LeftBottom[6] = Point(49, 170);
	m_Offset_LeftBottom[7] = Point(50, 151);
	m_Offset_LeftBottom[8] = Point(53, 155);
	m_Offset_LeftBottom[9] = Point(112, 209);
	m_Offset_LeftBottom[10] = Point(81, 161);
	m_Offset_LeftBottom[11] = Point(125, 161);
	m_Offset_LeftBottom[12] = Point(123, 110);
	m_Offset_LeftBottom[13] = Point(113, 163);
	m_Offset_LeftBottom[14] = Point(80, 163);
	m_Offset_LeftBottom[15] = Point(90, 167);
	m_Offset_LeftBottom[16] = Point(94, 148);
	m_Offset_LeftBottom[17] = Point(83, 189);
	m_Offset_LeftBottom[18] = Point(89, 181);
	m_Offset_LeftBottom[19] = Point(53, 145);
	m_Offset_LeftBottom[20] = Point(49, 161);
	m_Offset_LeftBottom[21] = Point(50, 161);
	m_Offset_LeftBottom[22] = Point(29, 150);
	m_Offset_LeftBottom[23] = Point(47, 154);
	m_Offset_LeftBottom[24] = Point(67, 164);
	m_Offset_LeftBottom[25] = Point(65, 164);
	m_Offset_LeftBottom[26] = Point(57, 161);
	m_Offset_LeftBottom[27] = Point(54, 160);
	m_Offset_LeftBottom[28] = Point(82, 193);
	m_Offset_LeftBottom[29] = Point(53, 300 - 140);
	m_Offset_LeftBottom[30] = Point(52, 300 - 140);
	m_Offset_LeftBottom[31] = Point(49, 298 - 140);

	m_Offset_LeftBottom_Left[0] = Point(97, 164);
	m_Offset_LeftBottom_Left[1] = Point(154, 177);
	m_Offset_LeftBottom_Left[2] = Point(50, 216);
	m_Offset_LeftBottom_Left[3] = Point(49, 230);
	m_Offset_LeftBottom_Left[4] = Point(209, 274);
	m_Offset_LeftBottom_Left[5] = Point(217, 170);
	m_Offset_LeftBottom_Left[6] = Point(198, 170);
	m_Offset_LeftBottom_Left[7] = Point(110, 151);
	m_Offset_LeftBottom_Left[8] = Point(149, 155);
	m_Offset_LeftBottom_Left[9] = Point(56, 209);
	m_Offset_LeftBottom_Left[10] = Point(83, 161);
	m_Offset_LeftBottom_Left[11] = Point(90, 161);
	m_Offset_LeftBottom_Left[12] = Point(99, 110);
	m_Offset_LeftBottom_Left[13] = Point(90, 163);
	m_Offset_LeftBottom_Left[14] = Point(114, 163);
	m_Offset_LeftBottom_Left[15] = Point(115, 167);
	m_Offset_LeftBottom_Left[16] = Point(111, 148);
	m_Offset_LeftBottom_Left[17] = Point(130, 189);
	m_Offset_LeftBottom_Left[18] = Point(102, 181);
	m_Offset_LeftBottom_Left[19] = Point(121, 145);
	m_Offset_LeftBottom_Left[20] = Point(132, 161);
	m_Offset_LeftBottom_Left[21] = Point(134, 161);
	m_Offset_LeftBottom_Left[22] = Point(115, 150);
	m_Offset_LeftBottom_Left[23] = Point(119, 154);
	m_Offset_LeftBottom_Left[24] = Point(92, 164);
	m_Offset_LeftBottom_Left[25] = Point(93, 164);
	m_Offset_LeftBottom_Left[26] = Point(103, 161);
	m_Offset_LeftBottom_Left[27] = Point(124, 160);
	m_Offset_LeftBottom_Left[28] = Point(94, 193);
	m_Offset_LeftBottom_Left[29] = Point(112, 300- 140);
	m_Offset_LeftBottom_Left[30] = Point(111, 300 - 140);
	m_Offset_LeftBottom_Left[31] = Point(113, 298 -140);
}
