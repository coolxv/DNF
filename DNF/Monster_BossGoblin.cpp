#include "Monster_BossGoblin.h"
#include "Monster_BossGoblin_State.h"


Mat CMonster_BossGoblin::s_Mat_Body[] =
{
	imread("./ImagePacks2/Monster/goblin1/0.png",-1),
	imread("./ImagePacks2/Monster/goblin1/1.png",-1),
	imread("./ImagePacks2/Monster/goblin1/2.png",-1),
	imread("./ImagePacks2/Monster/goblin1/3.png",-1),
	imread("./ImagePacks2/Monster/goblin1/4.png",-1),
	imread("./ImagePacks2/Monster/goblin1/5.png",-1),
	imread("./ImagePacks2/Monster/goblin1/6.png",-1),
	imread("./ImagePacks2/Monster/goblin1/7.png",-1),
	imread("./ImagePacks2/Monster/goblin1/8.png",-1),
	imread("./ImagePacks2/Monster/goblin1/9.png",-1),
	imread("./ImagePacks2/Monster/goblin1/10.png",-1),
	imread("./ImagePacks2/Monster/goblin1/11.png",-1),
	imread("./ImagePacks2/Monster/goblin1/12.png",-1),
	imread("./ImagePacks2/Monster/goblin1/13.png",-1),
	imread("./ImagePacks2/Monster/goblin1/14.png",-1),
	imread("./ImagePacks2/Monster/goblin1/15.png",-1),
	imread("./ImagePacks2/Monster/goblin1/16.png",-1)
};

Mat CMonster_BossGoblin::s_Mat_Body_Mask[] =
{
	imread("./ImagePacks2/Monster/goblin1/0.png",0),
	imread("./ImagePacks2/Monster/goblin1/1.png",0),
	imread("./ImagePacks2/Monster/goblin1/2.png",0),
	imread("./ImagePacks2/Monster/goblin1/3.png",0),
	imread("./ImagePacks2/Monster/goblin1/4.png",0),
	imread("./ImagePacks2/Monster/goblin1/5.png",0),
	imread("./ImagePacks2/Monster/goblin1/6.png",0),
	imread("./ImagePacks2/Monster/goblin1/7.png",0),
	imread("./ImagePacks2/Monster/goblin1/8.png",0),
	imread("./ImagePacks2/Monster/goblin1/9.png",0),
	imread("./ImagePacks2/Monster/goblin1/10.png",0),
	imread("./ImagePacks2/Monster/goblin1/11.png",0),
	imread("./ImagePacks2/Monster/goblin1/12.png",0),
	imread("./ImagePacks2/Monster/goblin1/13.png",0),
	imread("./ImagePacks2/Monster/goblin1/14.png",0),
	imread("./ImagePacks2/Monster/goblin1/15.png",0),
	imread("./ImagePacks2/Monster/goblin1/16.png",0)
};

Mat CMonster_BossGoblin::s_Mat_Avator = imread("./ImagePacks2/Monster/goblin1/goblin1.png",-1);
CMonster_BossGoblin::CMonster_BossGoblin(CStage* stage, int x, int y, int z)
{
	m_Stage = stage;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_MatId = 0;
	m_Hp = MONSTER_BOSSGOBLIN_HP;
	m_Hp_Animation = MONSTER_BOSSGOBLIN_HP;
	m_TotalHp = MONSTER_BOSSGOBLIN_HP;
	m_Width = 50;
	m_Thick = 25;
	m_Height = 76;
	m_MoveSpeed = 15;
	m_NAttackSpeed = 100;
	SetMoveDirection(DIR_LEFT);
	SetState(new CMonster_BossGoblin_RunningState(this));
	__InitOffset();
}

CMonster_BossGoblin::~CMonster_BossGoblin()
{
}

void CMonster_BossGoblin::DoRender(Mat& mat, int viewX)
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
		flip(s_Mat_Body[m_State->GetMatId()], body,1);
		flip(s_Mat_Body_Mask[m_State->GetMatId()], body_mask,1);
	}
	
	int tx = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x;
	int ty = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y;
	Mat ROI;
	int xx = m_X - viewX - tx; //相对坐标
	int yy = m_Y - ty - m_Z / 2 + offsetY;
	if (xx >= CStage::s_ViewWidth || xx + body.cols <= 0) return;
	Render(mat, viewX, CStage::s_ViewWidth,CStage::s_ViewHeight, CStage::s_OffsetY, xx, yy, body, body_mask);
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
	////rectangle(mat, GetAttackRect()+Point(-viewX,offsetY), Scalar(0, 0, 255), 3, 8, 0);
	//ROI = mat(Rect(xx, yy, tmp.cols, tmp_.rows));
	//tmp.copyTo(ROI, tmp_);
}

Rect CMonster_BossGoblin::GetAttackRect()
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

int CMonster_BossGoblin::GetDamage()
{
	return RANDNUM(MONSTER_BOSSGOBLIN_ATTACKPOWER, MONSTER_BOSSGOBLIN_ATTACKPOWER_);
}
 

int CMonster_BossGoblin::GetArmor()
{
	return MONSTER_BOSSGOBLIN_ARMOR;
}

void CMonster_BossGoblin::__InitOffset()
{
	m_Offset_LeftBottom[0] = Point(12, 79);
	m_Offset_LeftBottom[1] = Point(13, 79);
	m_Offset_LeftBottom[2] = Point(17, 88);
	m_Offset_LeftBottom[3] = Point(9, 76);
	m_Offset_LeftBottom[4] = Point(8, 75);
	m_Offset_LeftBottom[5] = Point(13, 75);
	m_Offset_LeftBottom[6] = Point(34, 76);
	m_Offset_LeftBottom[7] = Point(65, 52);
	m_Offset_LeftBottom[8] = Point(86, 52);
	m_Offset_LeftBottom[9] = Point(92, 36);
	m_Offset_LeftBottom[10] = Point(16, 63);
	m_Offset_LeftBottom[11] = Point(18, 76);
	m_Offset_LeftBottom[12] = Point(18, 75);
	m_Offset_LeftBottom[13] = Point(17, 74);
	m_Offset_LeftBottom[14] = Point(17, 76);
	m_Offset_LeftBottom[15] = Point(17, 77);
	m_Offset_LeftBottom[16] = Point(6, 75);

	m_Offset_LeftBottom_Left[0] = Point(13, 79);
	m_Offset_LeftBottom_Left[1] = Point(22, 79);
	m_Offset_LeftBottom_Left[2] = Point(10, 88);
	m_Offset_LeftBottom_Left[3] = Point(20, 76);
	m_Offset_LeftBottom_Left[4] = Point(15, 75);
	m_Offset_LeftBottom_Left[5] = Point(6, 75);
	m_Offset_LeftBottom_Left[6] = Point(8, 76);
	m_Offset_LeftBottom_Left[7] = Point(4, 52);
	m_Offset_LeftBottom_Left[8] = Point(6, 52);
	m_Offset_LeftBottom_Left[9] = Point(8, 36);
	m_Offset_LeftBottom_Left[10] = Point(18, 63);
	m_Offset_LeftBottom_Left[11] = Point(15, 76);
	m_Offset_LeftBottom_Left[12] = Point(12, 75);
	m_Offset_LeftBottom_Left[13] = Point(4, 74);
	m_Offset_LeftBottom_Left[14] = Point(19, 76);
	m_Offset_LeftBottom_Left[15] = Point(8, 77);
	m_Offset_LeftBottom_Left[16] = Point(5, 75);
}
