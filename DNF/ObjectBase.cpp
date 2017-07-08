#include "ObjectBase.h"


Rect CObjectBase::GetRectXY()
{
	return Rect(m_X, m_Y - m_Thick, m_Width, m_Thick);
}


Rect CObjectBase::GetRectXZ()
{
	return Rect(m_X, m_Y - m_Height - m_Z / 2, m_Width, m_Height);
}

CObjectBase::CObjectBase()
{
}

CObjectBase::~CObjectBase()
{
}


void CObjectBase::Render(Mat& bg, int viewX,int viewWidth,int viewHeight,int offsetY, int x, int y, Mat& mat, Mat& mat_mask)
{
	int xx = x; //相对坐标
	int yy = y;
	Mat tmp = mat, tmp_ = mat_mask;
	//处理人物武器会有一部分在屏幕外面的情况
	if (xx + tmp.cols <0 || xx >= bg.cols || yy + mat.rows <= 0 || yy>bg.rows)return;
	if (xx < 0)
	{
		tmp = mat.colRange(abs(xx), mat.cols - 1);
		tmp_ = mat_mask.colRange(abs(xx), mat_mask.cols - 1);
		xx = 0;
	}
	if (xx + mat.cols >= viewWidth)
	{
		tmp = mat.colRange(0, viewWidth - xx - 1);
		tmp_ = mat_mask.colRange(0, viewWidth - xx - 1);
	}
	if (yy + mat.rows >= viewHeight + offsetY)
	{
		tmp = mat.rowRange(0, viewHeight + offsetY - yy - 1);
		tmp_ = mat_mask.rowRange(0, viewHeight + offsetY - yy - 1);
	}
	if (yy <= 0)
	{
		tmp = mat.rowRange(abs(yy), mat.rows-1);
		tmp_ = mat_mask.rowRange(abs(yy), mat_mask.rows  - 1);
		yy = 0;
	}
	//rectangle(mat, GetRectXY()+Point(-viewX,offsetY), Scalar(0, 0, 255), 3, 8, 0);
	Mat ROI = bg(Rect(xx, yy, tmp.cols, tmp_.rows));
	tmp.copyTo(ROI, tmp_);
}
