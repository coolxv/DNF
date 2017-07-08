#include "AnimationEffect.h"
#include "Stage.h"
#include "CharacterState.h"
#include "Dungeon.h"
#include "Dungeon_Home.h"
#include "Dungeon_SelectDungeon.h"
#include "Dungeon_Rolland.h"
#include "Dungeon_RollandDeep.h"

CAnimationEffect::CAnimationEffect()
{
	m_Complete = false;
}


CAnimationEffect::~CAnimationEffect()
{
}

bool CAnimationEffect::GetComplete()
{
	return m_Complete;
}

Mat CPhysicalAttackAnimation::s_Mat_Slash[][3] =
{
	imread("./ImagePacks2/Animation/slashlarge1.img/0.png",-1),
	imread("./ImagePacks2/Animation/slashlarge1.img/1.png",-1),
	imread("./ImagePacks2/Animation/slashlarge1.img/2.png",-1),
	imread("./ImagePacks2/Animation/slashlarge2.img/0.png",-1),
	imread("./ImagePacks2/Animation/slashlarge2.img/1.png",-1),
	imread("./ImagePacks2/Animation/slashlarge2.img/2.png",-1)	,
	imread("./ImagePacks2/Animation/slashlarge3.img/0.png",-1),
	imread("./ImagePacks2/Animation/slashlarge3.img/1.png",-1),
	imread("./ImagePacks2/Animation/slashlarge3.img/2.png",-1)
};
Mat CPhysicalAttackAnimation::s_Mat_Slash_Mask[][3] =
{
	imread("./ImagePacks2/Animation/slashlarge1.img/0.png",0),
	imread("./ImagePacks2/Animation/slashlarge1.img/1.png",0),
	imread("./ImagePacks2/Animation/slashlarge1.img/2.png",0),
	imread("./ImagePacks2/Animation/slashlarge2.img/0.png",0),
	imread("./ImagePacks2/Animation/slashlarge2.img/1.png",0),
	imread("./ImagePacks2/Animation/slashlarge2.img/2.png",0),
	imread("./ImagePacks2/Animation/slashlarge3.img/0.png",0),
	imread("./ImagePacks2/Animation/slashlarge3.img/1.png",0),
	imread("./ImagePacks2/Animation/slashlarge3.img/2.png",0)
};

//************************************
// Method:    CPhysicalAttackAnimation
// FullName:  CPhysicalAttackAnimation::CPhysicalAttackAnimation
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: Point3i point 绝对坐标
// Parameter: int type [0~2]，3种类型
//************************************
CPhysicalAttackAnimation::CPhysicalAttackAnimation(Point3i point, int type)
{

	m_Type = type;
	m_Point_Coor = point;
	m_Complete = false;
	//m_Clock_PreRender = clock();
	m_MatId = 0;

}

CPhysicalAttackAnimation::~CPhysicalAttackAnimation()
{
}

void CPhysicalAttackAnimation::DoRender(Mat& mat, int viewX)
{
	if (m_Complete)  return;
	m_Complete = m_MatId == 2;
	//计算相对坐标
	int xx = (int)m_Point_Coor.x - viewX;
	int yy = (int)m_Point_Coor.y + CStage::s_OffsetY - (int)m_Point_Coor.z;
	//不在视图内不需要绘制
	if (xx >= CStage::s_ViewWidth || xx + s_Mat_Slash_Mask[m_Type][m_MatId].cols <= 0)
		return;
	Mat tmp, tmp_;
	if (xx < 0)
	{
		tmp = s_Mat_Slash[m_Type][m_MatId].colRange(abs(xx), s_Mat_Slash[m_Type][m_MatId].cols - 1);
		tmp_ = s_Mat_Slash_Mask[m_Type][m_MatId].colRange(abs(xx), s_Mat_Slash_Mask[m_Type][m_MatId].cols - 1);
		xx = 0;
	}
	else if (xx + s_Mat_Slash_Mask[m_Type][m_MatId].cols >= CStage::s_ViewWidth)
	{
		tmp = s_Mat_Slash[m_Type][m_MatId].colRange(0, CStage::s_ViewWidth - xx - 1);
		tmp_ = s_Mat_Slash_Mask[m_Type][m_MatId].colRange(0, CStage::s_ViewWidth - xx - 1);
	}
	else if (yy + s_Mat_Slash[m_Type][m_MatId].rows >= CStage::s_ViewHeight + CStage::s_OffsetY)
	{
		tmp = s_Mat_Slash[m_Type][m_MatId].rowRange(0, CStage::s_ViewHeight + CStage::s_OffsetY - yy - 1);
		tmp_ = s_Mat_Slash_Mask[m_Type][m_MatId].rowRange(0, CStage::s_ViewHeight + CStage::s_OffsetY - yy - 1);
	}
	else
	{
		tmp = s_Mat_Slash[m_Type][m_MatId];
		tmp_ = s_Mat_Slash_Mask[m_Type][m_MatId];
	}
	if (xx + tmp.cols >= mat.cols || yy + tmp.rows >= mat.rows)return;
	Mat ROI = mat(Rect(xx, yy, tmp.cols, tmp.rows));
	tmp.copyTo(ROI, tmp_);
	if (clock() - m_Clock_Update > 80)
	{
		m_Clock_Update = clock();
		m_MatId++;
	}
}


Mat CAwakeDEffectAnimation::s_Mat_Draw[] =
{
	imread("./ImagePacks2/Animation/effect/0.png",-1),
	imread("./ImagePacks2/Animation/effect/1.png",-1),
	imread("./ImagePacks2/Animation/effect/2.png",-1),
	imread("./ImagePacks2/Animation/effect/3.png",-1),
	imread("./ImagePacks2/Animation/effect/4.png",-1),
	imread("./ImagePacks2/Animation/effect/5.png",-1),
	imread("./ImagePacks2/Animation/effect/6.png",-1),
	imread("./ImagePacks2/Animation/effect/7.png",-1),
	imread("./ImagePacks2/Animation/effect/8.png",-1),
	imread("./ImagePacks2/Animation/effect/9.png",-1),
	imread("./ImagePacks2/Animation/effect/10.png",-1),
	imread("./ImagePacks2/Animation/effect/11.png",-1),
	imread("./ImagePacks2/Animation/effect/12.png",-1),
	imread("./ImagePacks2/Animation/effect/13.png",-1),
	imread("./ImagePacks2/Animation/effect/14.png",-1),
	imread("./ImagePacks2/Animation/effect/15.png",-1),
	imread("./ImagePacks2/Animation/effect/16.png",-1),
	imread("./ImagePacks2/Animation/effect/17.png",-1),
	imread("./ImagePacks2/Animation/effect/18.png",-1),
	imread("./ImagePacks2/Animation/effect/19.png",-1),
	imread("./ImagePacks2/Animation/effect/20.png",-1),
	imread("./ImagePacks2/Animation/effect/21.png",-1),
	imread("./ImagePacks2/Animation/effect/22.png",-1),
	imread("./ImagePacks2/Animation/effect/23.png",-1),
	imread("./ImagePacks2/Animation/effect/24.png",-1),
	imread("./ImagePacks2/Animation/effect/25.png",-1),
	imread("./ImagePacks2/Animation/effect/26.png",-1),
	imread("./ImagePacks2/Animation/effect/27.png",-1),
	imread("./ImagePacks2/Animation/effect/28.png",-1),
	imread("./ImagePacks2/Animation/effect/29.png",-1)
};

CAwakeDEffectAnimation::CAwakeDEffectAnimation(int pos)
{
	m_MatId = 0;
	m_Complete = false;
	m_pos = pos;
	mask = Mat(553, 640, CV_8UC4, Scalar(50, 50, 50, 0));

}


void CAwakeDEffectAnimation::DoRender(Mat& mat, int viewX)
{
	if (m_Complete) return;
	m_Complete = m_MatId == 29;
	addWeighted(mask, 1 - m_MatId / 29, mat(Rect(0, 0, 640, mat.rows)), 1, 0, mat(Rect(0, 0, 640, mat.rows)));
	//Mat ROI = mat(Rect(0, 250, 640, 294));
	//s_Mat_Draw[m_MatId].copyTo(ROI, s_Mat_Draw_Mask[m_MatId]);
	//imshow("Text", s_Mat_Draw[m_MatId]);
	if (m_pos == DIR_LEFT)
	{
		for (int i = 0; i < s_Mat_Draw[m_MatId].rows; i++)
		{
			uchar* RowData_ = mat.ptr<uchar>(i + 250); //行
			uchar * RowData = s_Mat_Draw[m_MatId].ptr<uchar>(i);
			for (int j = 0; j < s_Mat_Draw[m_MatId].cols; j++)
			{
				int k = j * 4;
				if (RowData[k + 3] > 230)
				{
					RowData_[k] = RowData[k];
					RowData_[k + 1] = RowData[k + 1];
					RowData_[k + 2] = RowData[k + 2];
					RowData_[k + 3] = 0;
				}
			}
		}
	}
	else
	{
		Mat tmp = s_Mat_Draw[m_MatId].clone();
		flip(tmp, tmp, 1);
		for (int i = 0; i < s_Mat_Draw[m_MatId].rows; i++)
		{
			uchar* RowData_ = mat.ptr<uchar>(i + 250); //行
			uchar * RowData = tmp.ptr<uchar>(i);
			for (int j = 0; j < tmp.cols; j++)
			{
				int k = j * 4;
				if (RowData[k + 3] > 230)
				{
					RowData_[k] = RowData[k];
					RowData_[k + 1] = RowData[k + 1];
					RowData_[k + 2] = RowData[k + 2];
					RowData_[k + 3] = 0;
				}
			}
		}
	}

	if (clock() - m_Clock_Update > 100)
	{
		m_Clock_Update = clock();
		m_MatId++;
	}
}



Mat CAwakeSEffectAnimation::s_Mat_DrawS[] =
{
	imread("./ImagePacks2/Animation/effect2/0.png",-1),
	imread("./ImagePacks2/Animation/effect2/1.png",-1),
	imread("./ImagePacks2/Animation/effect2/2.png",-1),
	imread("./ImagePacks2/Animation/effect2/3.png",-1),
	imread("./ImagePacks2/Animation/effect2/4.png",-1),
	imread("./ImagePacks2/Animation/effect2/5.png",-1),
	imread("./ImagePacks2/Animation/effect2/6.png",-1),
	imread("./ImagePacks2/Animation/effect2/7.png",-1),
	imread("./ImagePacks2/Animation/effect2/8.png",-1),
	imread("./ImagePacks2/Animation/effect2/9.png",-1),
	imread("./ImagePacks2/Animation/effect2/10.png",-1),
	imread("./ImagePacks2/Animation/effect2/11.png",-1),
	imread("./ImagePacks2/Animation/effect2/12.png",-1),
	imread("./ImagePacks2/Animation/effect2/13.png",-1),
	imread("./ImagePacks2/Animation/effect2/14.png",-1),
	imread("./ImagePacks2/Animation/effect2/15.png",-1),
	imread("./ImagePacks2/Animation/effect2/16.png",-1),
	imread("./ImagePacks2/Animation/effect2/17.png",-1),
	imread("./ImagePacks2/Animation/effect2/18.png",-1),
	imread("./ImagePacks2/Animation/effect2/19.png",-1),
	imread("./ImagePacks2/Animation/effect2/20.png",-1),
	imread("./ImagePacks2/Animation/effect2/21.png",-1),
	imread("./ImagePacks2/Animation/effect2/22.png",-1),
	imread("./ImagePacks2/Animation/effect2/23.png",-1),
	imread("./ImagePacks2/Animation/effect2/24.png",-1),
	imread("./ImagePacks2/Animation/effect2/25.png",-1),
	imread("./ImagePacks2/Animation/effect2/26.png",-1),
	imread("./ImagePacks2/Animation/effect2/27.png",-1),
	imread("./ImagePacks2/Animation/effect2/28.png",-1),
	imread("./ImagePacks2/Animation/effect2/29.png",-1),
	imread("./ImagePacks2/Animation/effect2/30.png",-1),
	imread("./ImagePacks2/Animation/effect2/31.png",-1),
	imread("./ImagePacks2/Animation/effect2/32.png",-1),
	imread("./ImagePacks2/Animation/effect2/33.png",-1),
	imread("./ImagePacks2/Animation/effect2/34.png",-1)
};


CAwakeSEffectAnimation::CAwakeSEffectAnimation(int pos)
{
	m_MatId = 0;
	m_Complete = false;
	m_pos = pos;
	mask = Mat(553, 640, CV_8UC4, Scalar(50, 50, 50, 0));
}



void CAwakeSEffectAnimation::DoRender(Mat& mat, int viewX)
{
	if (m_Complete) return;
	m_Complete = m_MatId == 34;
	addWeighted(mask, 1 - m_MatId / 34.0, mat(Rect(0, 0, mat.cols, mat.rows)), 1, 0, mat(Rect(0, 0, mat.cols, mat.rows)));
	//Mat ROI = mat(Rect(0, 250, 640, 294));
	//s_Mat_Draw[m_MatId].copyTo(ROI, s_Mat_Draw_Mask[m_MatId]);
	//imshow("Text", s_Mat_Draw[m_MatId]);
	if (m_pos == DIR_LEFT)
	{
		for (int i = 0; i < s_Mat_DrawS[m_MatId].rows; i++)
		{
			uchar* RowData_ = mat.ptr<uchar>(i +180); //行
			uchar * RowData = s_Mat_DrawS[m_MatId].ptr<uchar>(i);
			for (int j = 0; j < s_Mat_DrawS[m_MatId].cols; j++)
			{
				int k = j * 4;
				if (RowData[k + 3] > 230)
				{
					RowData_[k] = RowData[k];
					RowData_[k + 1] = RowData[k + 1];
					RowData_[k + 2] = RowData[k + 2];
					RowData_[k + 3] = 0;
				}
			}
		}
	}
	else
	{
		Mat tmp = s_Mat_DrawS[m_MatId].clone();
		flip(tmp, tmp, 1);
		for (int i = 0; i < s_Mat_DrawS[m_MatId].rows; i++)
		{
			uchar* RowData_ = mat.ptr<uchar>(i + 180); //行
			uchar * RowData = tmp.ptr<uchar>(i);
			for (int j = 0; j < tmp.cols; j++)
			{
				int k = j * 4;
				if (RowData[k + 3] > 230)
				{
					RowData_[k] = RowData[k];
					RowData_[k + 1] = RowData[k + 1];
					RowData_[k + 2] = RowData[k + 2];
					RowData_[k + 3] = 0;
				}
			}
		}
	}

	if (clock() - m_Clock_Update > 100)
	{
		m_Clock_Update = clock();
		m_MatId++;
	}
}


Mat CNumberAnimation::s_Mat_Number[][10] =
{
	imread("./ImagePacks2/Animation/number0/0.png",-1),
	imread("./ImagePacks2/Animation/number0/1.png",-1),
	imread("./ImagePacks2/Animation/number0/2.png",-1),
	imread("./ImagePacks2/Animation/number0/3.png",-1),
	imread("./ImagePacks2/Animation/number0/4.png",-1),
	imread("./ImagePacks2/Animation/number0/5.png",-1),
	imread("./ImagePacks2/Animation/number0/6.png",-1),
	imread("./ImagePacks2/Animation/number0/7.png",-1),
	imread("./ImagePacks2/Animation/number0/8.png",-1),
	imread("./ImagePacks2/Animation/number0/9.png",-1),

	imread("./ImagePacks2/Animation/number1/0.png",-1),
	imread("./ImagePacks2/Animation/number1/1.png",-1),
	imread("./ImagePacks2/Animation/number1/2.png",-1),
	imread("./ImagePacks2/Animation/number1/3.png",-1),
	imread("./ImagePacks2/Animation/number1/4.png",-1),
	imread("./ImagePacks2/Animation/number1/5.png",-1),
	imread("./ImagePacks2/Animation/number1/6.png",-1),
	imread("./ImagePacks2/Animation/number1/7.png",-1),
	imread("./ImagePacks2/Animation/number1/8.png",-1),
	imread("./ImagePacks2/Animation/number1/9.png",-1),

	imread("./ImagePacks2/Animation/number2/0.png",-1),
	imread("./ImagePacks2/Animation/number2/1.png",-1),
	imread("./ImagePacks2/Animation/number2/2.png",-1),
	imread("./ImagePacks2/Animation/number2/3.png",-1),
	imread("./ImagePacks2/Animation/number2/4.png",-1),
	imread("./ImagePacks2/Animation/number2/5.png",-1),
	imread("./ImagePacks2/Animation/number2/6.png",-1),
	imread("./ImagePacks2/Animation/number2/7.png",-1),
	imread("./ImagePacks2/Animation/number2/8.png",-1),
	imread("./ImagePacks2/Animation/number2/9.png",-1)
};
CNumberAnimation::CNumberAnimation(long long num, Point3i p,int style)
	:m_Pos(p), m_CurPos(p)
{ 
	m_NumStyle = style;
	m_Clock_Update = 0;
	m_Clock_stay = 0;
	while (num)
	{
		m_v_num.push_back(num % 10);
		num /= 10;
	}
	m_length = (int)m_v_num.size();

	switch (style)
	{
	case 0:
		m_Zspeed = 15;
		m_StayTime = 300; //停留时间
		break;
	case 1:
		m_Zspeed = 18;
		m_StayTime = 350; //停留时间
		break;
	case 2:
		m_Zspeed = 18;
		m_StayTime = 400;
	default:
		m_Zspeed = 15;
		m_StayTime = 300; //停留时间
		break;
	}
}

void CNumberAnimation::DoRender(Mat& mat, int viewX)
{
	if (m_Zspeed==0 && clock()- m_Clock_stay>m_StayTime)
	{
		m_Complete = true;
		return;
	}
	int xx = m_CurPos.x - viewX - m_length * 15 / 2;
	int yy = m_CurPos.y + CStage::s_OffsetY - m_CurPos.z / 2;
	int rows = s_Mat_Number[m_NumStyle][0].rows;
	int cols = s_Mat_Number[m_NumStyle][0].cols;
	for (int i = 0; i < m_length; i++)
	{
		for (int r = 0; r < rows; r++)
		{
			uchar* res = mat.ptr<uchar>(r + yy);
			uchar* nu = s_Mat_Number[m_NumStyle][m_v_num[m_length- i - 1]].ptr<uchar>(r);
			for (int c = 0; c < cols; c++)
			{
				int k = c * 4;
				if (nu[k + 3])
				{
					if (xx * 4 + i * (cols-3) * 4 + k < 0 || xx * 4 + i * (cols-3) * 4 + k>=4*mat.cols)break;
					res[xx * 4 + i * (cols - 3) * 4 + k] = nu[k];
					res[xx * 4 + i * (cols - 3) * 4 + k + 1] = nu[k + 1];
					res[xx * 4 + i * (cols - 3) * 4 + k + 2] = nu[k + 2];
					res[xx * 4 + i * (cols - 3) * 4 + k + 3] = nu[k + 3];
				}
			}
		}
	}
	if (clock() - m_Clock_Update > 50 &&m_Clock_stay==0)
	{
		m_CurPos.z += m_Zspeed;
		m_Zspeed--;
		if (m_Zspeed==0)
			m_Clock_stay = clock();
		m_Clock_Update = clock();
	}
}

Mat CResultAnimation::s_Mat_panel = imread("./ImagePacks2/Animation/result/panel.png", -1);
Mat CResultAnimation::s_Mat_score_text1 = imread("./ImagePacks2/Animation/result/score_text1.png", -1);
Mat CResultAnimation::s_Mat_score_text2 = imread("./ImagePacks2/Animation/result/score_text2.png", -1);
Mat CResultAnimation::s_Mat_score_text3 = imread("./ImagePacks2/Animation/result/score_text3.png", -1);
Mat CResultAnimation::s_Mat_time_text = imread("./ImagePacks2/Animation/result/time_text.png", -1);
Mat CResultAnimation::s_Mat_exp_text = imread("./ImagePacks2/Animation/result/exp_text.png", -1);
Mat CResultAnimation::s_Mat_min = imread("./ImagePacks2/Animation/result/min.png", -1);
Mat CResultAnimation::s_Mat_sec = imread("./ImagePacks2/Animation/result/sec.png", -1);
Mat CResultAnimation::s_Mat_SelectBG = imread("./ImagePacks2/Animation/result/select.png", -1);
Mat CResultAnimation::s_Mat_Return[] = { imread("./ImagePacks2/Animation/result/return0.png",-1),imread("./ImagePacks2/Animation/result/return1.png",-1) };
Mat CResultAnimation::s_Mat_Other[] = { imread("./ImagePacks2/Animation/result/other0.png",-1),imread("./ImagePacks2/Animation/result/other1.png",-1) };
Mat CResultAnimation::s_Mat_Continue[] = { imread("./ImagePacks2/Animation/result/continue0.png",-1),imread("./ImagePacks2/Animation/result/continue1.png",-1) };

Mat CResultAnimation::s_Mat_Number[] = 
{
	imread("./ImagePacks2/Animation/result/number/0.png",-1),
	imread("./ImagePacks2/Animation/result/number/1.png",-1),
	imread("./ImagePacks2/Animation/result/number/2.png",-1),
	imread("./ImagePacks2/Animation/result/number/3.png",-1),
	imread("./ImagePacks2/Animation/result/number/4.png",-1),
	imread("./ImagePacks2/Animation/result/number/5.png",-1),
	imread("./ImagePacks2/Animation/result/number/6.png",-1),
	imread("./ImagePacks2/Animation/result/number/7.png",-1),
	imread("./ImagePacks2/Animation/result/number/8.png",-1),
	imread("./ImagePacks2/Animation/result/number/9.png",-1)
};
Mat CResultAnimation::s_Mat_ScoreRank[] =
{
	imread("./ImagePacks2/Animation/result/rank/0.png",-1),
	imread("./ImagePacks2/Animation/result/rank/1.png",-1),
	imread("./ImagePacks2/Animation/result/rank/2.png",-1),
	imread("./ImagePacks2/Animation/result/rank/3.png",-1),
	imread("./ImagePacks2/Animation/result/rank/4.png",-1),
	imread("./ImagePacks2/Animation/result/rank/5.png",-1),
	imread("./ImagePacks2/Animation/result/rank/6.png",-1),
	imread("./ImagePacks2/Animation/result/rank/7.png",-1),
	imread("./ImagePacks2/Animation/result/rank/8.png",-1)
};

CResultAnimation::CResultAnimation(int score, int score_rank, int exp, int min, int sec, int lsec
	, int min_record, int sec_record, int lsec_record, CDungeon* cur_dungeon)
	:m_Score(score), m_Score_Rank(score_rank), m_Exp(exp), m_Min(min), m_Sec(sec), m_LSec(lsec)
	,m_Min_Record(min_record),m_Sec_Record(sec_record),m_LSec_Record(lsec_record),m_CurDungeon(cur_dungeon)
{
	m_StartTime = clock();
	m_IsSelecting =false;
	m_selected = NONE;
	m_rect_return = Rect(Point2i(482, 176), Point2i(543, 192));
	m_rect_other = Rect(Point2i(461, 146), Point2i(571, 162));
	m_rect_continue = Rect(Point2i(482, 115), Point2i(543, 131));
}

CResultAnimation::~CResultAnimation()
{

}


void CResultAnimation::DoRender(Mat& bg, int viewX)
{
	int cur = clock() - m_StartTime;
	if (cur > 3500)
	{
		//加载 "是否继续" 界面
		m_IsSelecting = true;
		__Merge(bg, s_Mat_SelectBG, 430, 60, 250);

		__Merge(bg,m_selected==CONTINUE? s_Mat_Continue[1]: s_Mat_Continue[0], 480, 115, 50);
		__Merge(bg, m_selected == OTHERDUNGEON ? s_Mat_Other[1]: s_Mat_Other[0], 460, 145, 50);
		__Merge(bg, m_selected == RETURN ? s_Mat_Return[1]: s_Mat_Return[0], 480, 175, 50);
	}
	else if (cur > 3000)
	{
		cur -= 3000;
		//+ (cur*1.0 / 500)*(bg.cols - 456)
		__Merge(bg, s_Mat_score_text1, 456 + (int)((cur*1.0 / 500)*(bg.cols - 456)), 65, 100);
		__Merge(bg, s_Mat_score_text2, 390 + (int)((cur*1.0 / 500)*(bg.cols - 390)), 140, 50);
		__Merge(bg, s_Mat_score_text3, 390 + (int)((cur*1.0 / 500)*(bg.cols - 390)), 310, 50);
		__Merge(bg, s_Mat_time_text, 390 + (int)((cur*1.0 / 500)*(bg.cols - 390)), 348, 50);
		__Merge(bg, s_Mat_ScoreRank[m_Score_Rank], 416 + (int)((cur*1.0 / 500)*(bg.cols - 416)), 160, 50);
		__Merge(bg, s_Mat_exp_text, 408 + (int)((cur*1.0 / 500)*(bg.cols - 408)), 432, 200);
	}
	else
	{
		if (cur >= 400)
			addWeighted(s_Mat_panel, 0.5, bg(Rect(370, 120, 250, 360)), 0.5, 0, bg(Rect(370, 120, 250, 360)));
		else
			addWeighted(s_Mat_panel, (cur*1.0) / 400 / 2, bg(Rect(370, 120, 250, 360)), 0.5, 0, bg(Rect(370, 120, 250, 360)));

		////---------------------"成绩" 动画 文字456,65------------------------
		if (cur >= 400)
			__Merge(bg, s_Mat_score_text1, 456, 65, 100);
		else
			__Merge(bg, s_Mat_score_text1, bg.cols - (int)((cur) / 400.0 * (bg.cols - 456)), 65, 100);

		//------------------600~1000 "评分"文字动画-----------------------
		if (cur > 1000)
			__Merge(bg, s_Mat_score_text2, 390, 140, 50);
		else if (cur > 600)
			__Merge(bg, s_Mat_score_text2, bg.cols - (int)((cur - 600) / 400.0 * (bg.cols - 390)), 140, 50);

		//------------------650~1050 "评分点数"文字动画-----------------------
		if (cur > 1050)
			__Merge(bg, s_Mat_score_text3, 390, 310, 50);
		else if (cur > 650)
			__Merge(bg, s_Mat_score_text3, bg.cols - (int)((cur - 650) / 400.0 * (bg.cols - 390)), 310, 50);

		//------------------700~1100 "通过时间"文字动画-----------------------
		if (cur > 1100)
			__Merge(bg, s_Mat_time_text, 390, 348, 50);
		else if (cur > 700)
			__Merge(bg, s_Mat_time_text, bg.cols - (int)((cur - 700) / 400.0 * (bg.cols - 390)), 348, 50);


		//------------------900~1300 评分等级动画----------------------- 416,160
		if (cur > 1300)
			__Merge(bg, s_Mat_ScoreRank[m_Score_Rank], 416, 160, 50);
		else if (cur > 900)
			__Merge(bg, s_Mat_ScoreRank[m_Score_Rank], bg.cols - (int)((cur - 900) / 400.0 * (bg.cols - 416)), 160, 50);


		//------------------1400~1800 "总经验"文字 动画  408,432
		if (cur > 1800)
			__Merge(bg, s_Mat_exp_text, 408, 432, 200);
		else if (cur > 1400)
			__Merge(bg, s_Mat_exp_text, bg.cols - (int)((cur - 1400) / 400.0 * (bg.cols - 408)), 432, 200);

		//------------------1200~1600 评价点数数字动画  530,333
		if (cur > 1600)
			__ShowNumber(bg, 558, 308, m_Score);
		else if (cur > 1200)
			__ShowNumber(bg, 558, 345 - (int)((cur - 1200) / 400.0 * (345 - 308)), m_Score);

		//------------------1300~1700 通关时间 475,350
		if (cur > 1700)
			__ShowTime(bg, 455, 345, m_Min, m_Sec, m_LSec);
		else if (cur > 1300)
			__ShowTime(bg, 455, 365 - (int)((cur - 1300) / 400.0 * (365 - 345)), m_Min, m_Sec, m_LSec);

		//------------------1300~1700 最佳纪录
		if (cur > 1700)
			__ShowTime(bg, 455, 368, m_Min_Record, m_Sec_Record, m_LSec_Record);
		else if (cur > 1300)
			__ShowTime(bg, 455, 388 - (int)((cur - 1300) / 400.0 * (388 - 368)), m_Min_Record, m_Sec_Record, m_LSec_Record);

		//------------------1800~2400 总经验数字动画  550,425
		if (cur > 2200)
			__ShowNumber(bg, 560, 435, m_Exp);
		else if (cur > 1800)
			__ShowNumber(bg, 560, 475 - (int)((cur - 1800) / 400.0 * (475 - 435)), m_Exp);
	}
}

void CResultAnimation::onMouse(int Event, int x, int y, int flags, void* param)
{
	Point2i point(x,y);
	if (m_IsSelecting)
	{
		switch (Event)
		{
		case CV_EVENT_MOUSEMOVE:
			if (m_rect_return.contains(point))
				m_selected = RETURN;
			else if (m_rect_other.contains(point))
				m_selected = OTHERDUNGEON;
			else if (m_rect_continue.contains(point))
				m_selected = CONTINUE;
			else
				m_selected = NONE;
			break;
		case CV_EVENT_LBUTTONUP:
			if (m_selected == RETURN)
			{
				m_CurDungeon->SetNextDungeon(new CDungeon_Home());
				m_CurDungeon->SetQuit(true);
				m_Complete = true;
			}
			else if (m_selected == OTHERDUNGEON)
			{
				m_CurDungeon->SetNextDungeon(new CDungeon_SelectDungeon());
				m_CurDungeon->SetQuit(true);
				m_Complete = true;
			}
			else if (m_selected == CONTINUE)
				{
					if(typeid(*m_CurDungeon) == typeid(CDungeon_RollandDeep))
						m_CurDungeon->SetNextDungeon(new CDungeon_RollandDeep());
					else if (typeid(*m_CurDungeon) == typeid(CDungeon_Rolland))
						m_CurDungeon->SetNextDungeon(new CDungeon_Rolland());
					m_CurDungeon->SetQuit(true);
					m_Complete = true;
				}
			break;
		}
	}
}

void CResultAnimation::__ShowNumber(Mat& bg, int x, int y, int num)
{
	std::vector<int>v;
	while (num)
	{
		v.push_back(num % 10);
		num /= 10;
	}
	x = x - ((int)v.size() * 22 / 2);
	for (int i = 0; i < v.size(); i++)
	{
		int num = v[v.size() - i - 1];
		for (int r = 0; r < s_Mat_Number[num].rows; r++)
		{
			if (r + y >= bg.rows)break;

			uchar* bgdata = bg.ptr(r + y);
			uchar* numdata = s_Mat_Number[num].ptr(r);

			for (int c = 0; c < s_Mat_Number[num].cols; c++)
			{
				int k = c * 4;
				if (x * 4 + (s_Mat_Number[num].cols - 5) * 4 * i + k >= bg.cols * 4)break;
				if (numdata[k + 3] > 100)
				{
					bgdata[x * 4 + (s_Mat_Number[num].cols - 5) * 4 * i + k] = numdata[k];
					bgdata[x * 4 + (s_Mat_Number[num].cols - 5) * 4 * i + k + 1] = numdata[k + 1];
					bgdata[x * 4 + (s_Mat_Number[num].cols - 5) * 4 * i + k + 2] = numdata[k + 2];
					//bgdata[x * 4 + i*number[num].cols * 4 + k + 3] = numdata[k + 3];
				}
			}
		}
	}
}


void CResultAnimation::__ShowTime(Mat& bg, int x, int y, int min, int sec, int lsec)
{
	//12,11,34
	int xx = x, yy = y;
	std::vector<int>v;
	while (min)
	{
		v.push_back(min % 10);
		min /= 10;
	}
	if (v.size() == 0)v.push_back(0);
	for (int i = 0; i < v.size(); i++)
	{
		int num = v[(int)v.size() - i - 1];
		xx += s_Mat_Number[num].cols-6;
		__Merge(bg, s_Mat_Number[num], xx, y,50);
	}
	xx += 17;
	__Merge(bg, s_Mat_min, xx, y, 50);
	v.clear();

	while (sec)
	{
		v.push_back(sec % 10);
		sec /= 10;
	}
	if (v.size() == 0)v.push_back(0);
	for (int i = 0; i < v.size(); i++)
	{
		int num = v[(int)v.size() - i - 1];
		xx += s_Mat_Number[num].cols -6;
		__Merge(bg, s_Mat_Number[num], xx, y, 50);
	}
	xx += 17;
	__Merge(bg, s_Mat_sec, xx, y, 50);
	v.clear();

	while (lsec)
	{
		v.push_back(lsec % 10);
		lsec /= 10;
	}
	if (v.size() == 0)v.push_back(0);
	for (int i = 0; i < v.size(); i++)
	{
		int num = v[(int)v.size() - i - 1];
		xx += s_Mat_Number[num].cols -6;
		__Merge(bg, s_Mat_Number[num], xx, y, 50);
	}
}

void CResultAnimation::__Merge(Mat& a, Mat& b, int x, int y, int h)
{
	for (int i = 0; i < b.rows; i++)
	{
		if (i + y >= a.rows)break;
		uchar* adata = a.ptr(i + y);
		uchar* bdata = b.ptr(i);
		for (int j = 0; j < b.cols; j++)
		{
			int k = j * 4;
			if (x * 4 + k >= a.cols * 4)break;
			if (bdata[k + 3] > h)
			{
				adata[x * 4 + k] = bdata[k];
				adata[x * 4 + k + 1] = bdata[k + 1];
				adata[x * 4 + k + 2] = bdata[k + 2];
				adata[x * 4 + k + 3] = bdata[k + 3];
			}
		}
	}
}

CGameOverAnimation::CGameOverAnimation(CDungeon* dungeon)
	:m_Dungeon(dungeon)
{
	m_AnimationStart = clock();

	for (int i = 0; i < 10; i++)
	{
		m_Mat_Number[i] = imread(format("./ImagePacks2/Animation/dead/%d.png",i), -1);
		m_Mat_Number_Mask[i] = imread(format("./ImagePacks2/Animation/dead/%d.png",i), 0);
	}
}

void CGameOverAnimation::DoRender(Mat& mat, int viewX)
{
	clock_t cur = clock() - m_AnimationStart;
	if (cur >= 11000)
	{
		m_Complete = true;
		m_Dungeon->SetQuit(true);
		m_Dungeon->SetNextDungeon(new CDungeon_Home());
		m_Dungeon->GetCurStage()->GetCharacter()->SetState(&s_Standing);
		m_Dungeon->GetCurStage()->GetCharacter()->SetDead(false); 
		m_Dungeon->GetCurStage()->GetCharacter()->SetHp(CHARACTER_HP);
		return;
	}
	int sec = 9 - cur / 1000;
	if (sec < 0)sec = 0;
	m_Mat_Number[sec].copyTo(mat(Rect(286,265, 111,88)), m_Mat_Number_Mask[sec]);
}
