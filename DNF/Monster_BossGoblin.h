#pragma once
#include "Monster.h"
/**
 * @class CMonster_BossGoblin
 * @brief 投掷哥布林
 * 
 *
 */
class CMonster_BossGoblin :
	public CMonster
{
public:
	static Mat s_Mat_Body[17], s_Mat_Body_Mask[17],s_Mat_Avator; /**<  资源图*/
	
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
	  CMonster_BossGoblin(CStage* stage, int x, int y, int z);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 virtual ~CMonster_BossGoblin();
	
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
	 * @brief 返回名字
	 * 
	 * 
	 * @return  cv::String  
	 */
	 String GetName() { return String("Lv3 Throwing Goblin"); }
private:
	
	/**
	 * @brief 初始化资源图片偏移
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitOffset();
	 Point m_Offset_LeftBottom[17], m_Offset_LeftBottom_Left[17]; /**<  角色对应图片左下角偏移 */
};

