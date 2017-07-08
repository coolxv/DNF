#pragma once
#include "stdafx.h"

using namespace cv;

/**
 * @class CObjectBase
 * @brief 对象基类
 * 
 *游戏中所有对象的基类
 */
class CObjectBase
{

public:
	virtual void DoRender(Mat& mat, int viewX) = 0;
	
	/**
	 * @brief 获取在xy面的投影
	 * 
	 * 
	 * @return  Rect  返回投影矩形
	 */
	 Rect GetRectXY(); 
	
	/**
	 * @brief 获取在xz面的投影
	 * 
	 * 
	 * @return  Rect  返回投影矩形
	 */
	 Rect GetRectXZ();
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @return    
	 */
	 CObjectBase();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CObjectBase();

protected:
	int m_Thick; /**<  y轴上的厚度*/
	int m_Width; /**<  在x轴上的宽度*/
	int m_Height; /**<  在z轴上的高度*/
	int m_X, m_Y, m_Z; /**<  人物左下角的坐标*/

	int m_Gravity; /**<  重力 方向向上为正*/
	int m_ZSpeed; /**<  z轴速度 方向向上为正*/
	int m_JumpDir; /**<  跳跃方向*/
	int m_MoveDirection; /**<  移动方向*/
	int m_Orientation = DIR_RIGHT; /**<  朝向*/

public:
	static void Render(Mat& bg, int viewX, int viewWidth, int viewHeight, int offsetY, int x, int y, Mat& mat, Mat& mat_mask);

	
	/**
	 * @brief 比较函数
	 * 
	 * 用于比较对象绘制顺序
	 * @param  const CObjectBase * a
	 * @param  const CObjectBase * b
	 * @return  bool  
	 */
	 static bool Cmp(const CObjectBase* a, const CObjectBase* b)
	{
		return a->m_Y - a->m_Thick < b->m_Y - b->m_Thick;
	}
	
	/**
	 * @brief 生成一个[a,b]范围的随机数
	 * 
	 * 
	 * @param  int a
	 * @param  int b
	 * @return  int  
	 */
	 static int GetRandNum(int a, int b)
	{
		return   (rand() % (b - a+1) + a);
	}

	
	/**
	 * @brief 返回x坐标
	 * 
	 * 
	 * @return  int  
	 */
	 int GetX() { return m_X; }
	
	/**
	 * @brief 返回y坐标
	 * 
	 * 
	 * @return  int  
	 */
	 int GetY() { return m_Y; }
	
	/**
	 * @brief 返回z坐标
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZ() { return m_Z; }
	
	/**
	 * @brief 返回厚度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetThick() { return m_Thick; }
	
	/**
	 * @brief 返回宽度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetWidth() { return m_Width; }
	
	/**
	 * @brief 返回高度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHeight() { return m_Height; }
};

