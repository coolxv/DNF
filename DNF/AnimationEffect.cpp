#include "AnimationEffect.h"
#include "Stage.h"


CAnimationEffect::CAnimationEffect()
{
	m_Complete = false;
}


CAnimationEffect::~CAnimationEffect()
{
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
	Mat ROI = mat(Rect(xx, yy, tmp.cols, tmp.rows));
	tmp.copyTo(ROI, tmp_);
	if (clock() - m_Clock_PreRender > 80)
	{
		m_Clock_PreRender = clock();
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

	if (clock() - m_Clock_PreRender > 100)
	{
		m_Clock_PreRender = clock();
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

	if (clock() - m_Clock_PreRender > 100)
	{
		m_Clock_PreRender = clock();
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
	m_Clock_PreRender = 0;
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
	if (clock() - m_Clock_PreRender > 50 &&m_Clock_stay==0)
	{
		m_CurPos.z += m_Zspeed;
		m_Zspeed--;
		if (m_Zspeed==0)
			m_Clock_stay = clock();
		m_Clock_PreRender = clock();
	}
}
