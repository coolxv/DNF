#pragma once
#include "Monster.h"
/**
 * @class CMonSter_Tau
 * @brief 牛头怪
 * 
 *
 */
class CMonster_Tau :
	public CMonster
{
public:
	static Mat s_Mat_Body[32], s_Mat_Body_Mask[32], s_Mat_Avator;	/**<  资源图*/
public:
	
	/**
	* @brief 构造函数
	*
	* 设置怪物的坐标和场景对象指针
	* @param  CStage * stage	怪物所在场景对象指针
	* @param  int x	x坐标
	* @param  int y	y坐标
	* @param  int z	z坐标
	* @return
	*/
	 CMonster_Tau(CStage* stage, int x, int y, int z);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CMonster_Tau();

	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	void DoRender(Mat& mat, int viewX);

	
	/**
	 * @brief 返回攻击判定矩阵
	 * 
	 * 
	 * @return  Rect  
	 */
	 Rect GetAttackRect();
	
	/**
	 * @brief 计算伤害
	 * 
	 * 
	 * @return  int  
	 */
	 int GetDamage();
	
	/**
	 * @brief 返回护甲
	 * 
	 * 
	 * @return  int  
	 */
	 int GetArmor();
	
	/**
	 * @brief 返回头像
	 * 
	 * 
	 * @return  cv::Mat  
	 */
	 Mat GetAvator() { return s_Mat_Avator; };
	
	/**
	 * @brief 返回名称
	 * 
	 * 
	 * @return  cv::String  
	 */
	 String GetName() { return String("Lv5 Ngau Tau Monster"); }


	 
	 /**
	  * @brief 设置上一次使用冲撞技能的时间
	  * 
	  * 
	  * @param  clock_t t
	  * @return  void  
	  */
	  void SetPreHit(clock_t t);
	
	/**
	 * @brief 返回上一次使用冲撞技能的时间
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreHit() { return m_PreHit; }

	
	/**
	 * @brief 设置上一次使用吼叫技能的时间
	 * 
	 * 
	 * @param  clock_t t
	 * @return  void  
	 */
	 void SetPreRoar(clock_t t) { m_PreRoar = t; }
	
	/**
	 * @brief 防护上一次使用吼叫技能的时间
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreRoar() { return m_PreRoar; }
private:
	
	/**
	 * @brief 初始化图片资源偏移
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitOffset();
	 Point m_Offset_LeftBottom[32], m_Offset_LeftBottom_Left[32]; /**<  角色对应图片左下角偏移*/
	 clock_t m_PreHit; /**<  上一次使用冲撞技能的时间*/
	 clock_t m_PreRoar; /**<  上一次使用吼叫的时间*/
};