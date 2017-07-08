#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Dungeon.h"
/**
 * @class CHud
 * @brief 血条技能显示栏
 * 
 *
 */
class CHud
{
public:
	CHud();
	~CHud();

	void Render(Mat& mat);
	void Update();
	void HandleInput(char key);
	void HandleMouse(int Event, int x, int y, int flags, void* param);

	
	/**
	 * @brief 初始化资源图
	 * 
	 * 
	 * @return  void  
	 */
	 void Initial();
	
	/**
	 * @brief 设置角色对象指针
	 * 
	 * 
	 * @param  CCharacter * character 角色对象指针
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* character);
	
	/**
	 * @brief 设置角色当前所在地下城对象指针
	 * 
	 * 
	 * @param  CDungeon * dungeon 地下城对象指针
	 * @return  void  
	 */
	 void SetDungeon(CDungeon* dungeon) { m_Dungeon = dungeon; }

	
	 /**
	 * @brief 将a，b纵向合并
	 *
	 *
	 * @param  Mat & a
	 * @param  Mat & b
	 * @param  Mat & b_ b的蒙板
	 * @param  int div 纵向间距
	 * @return  void
	 */
	 void __VerticalMergeMat(Mat& a, Mat& b, Mat& b_, int div);
	
	/**
	 * @brief 绘制人物血条
	 * 
	 * 
	 * @param  Mat & mat 背景底图
	 * @param  int hp_percentage	当前血量（百分比）
	 * @return  void  
	 */
	 void __ShowHp(Mat& mat,int hp_percentage);
	
	/**
	 * @brief 绘制人物血条动画
	 * 
	 * 
	 * @param  Mat & mat 底图
	 * @return  void  
	 */
	 void __ShowHpAnimation(Mat& mat);

	
	 /**
	 * @brief 绘制人物蓝条
	 *
	 *
	 * @param  Mat & mat 背景底图
	 * @param  int hp_percentage	当前蓝量（百分比）
	 * @return  void
	 */
	 void __ShowMp(Mat& mat, int mp_percentage);

	 /**
	 * @brief 绘制人物蓝条动画
	 *
	 *
	 * @param  Mat & mat 底图
	 * @return  void
	 */
	void __ShowMpAnimation(Mat& mat);

private:
	int m_hp_percentage_cur;	/**<  角色血量百分比 */
	int m_hp_percentage_animation;	/**<  角色血量动画显示到的百分比 */
	int m_mp_percentage_cur;	/**<  角色法力值百分比 */
	int m_mp_percentage_animation;	/**<  角色法力值动画显示到的百分比 */

	CCharacter* m_Character;	/**<  角色对象指针 */
	CDungeon* m_Dungeon;	/**<  地下城对象指针 */

	Mat m_Mat_Hud,m_Mat_Hud_Mask; /**<  界面资源 */
	Mat m_Mat_Hp,m_Mat_Hp_Mask,m_Mat_Hp_w;	/**<  血条资源*/
	Mat m_Mat_Mp,m_Mat_Mp_Mask;	/**<  蓝条资源 */
	Mat m_Mat_EffectA, m_Mat_EffectA_Mask, m_Mat_EffectA_Cool, m_Mat_EffectA_Cool_Mask;	/**<  技能A图标*/
	Mat m_Mat_EffectS, m_Mat_EffectS_Mask, m_Mat_EffectS_Cool, m_Mat_EffectS_Cool_Mask;	/**<  技能S图标*/
	Mat m_Mat_EffectD, m_Mat_EffectD_Mask, m_Mat_EffectD_Cool, m_Mat_EffectD_Cool_Mask;	/**<  技能D图标*/
	Mat m_Mat_EffectZ, m_Mat_EffectZ_Mask, m_Mat_EffectZ_Cool, m_Mat_EffectZ_Cool_Mask;	/**<  技能Z图标*/
	Mat m_Mat_EffectMask;

	bool m_Hp_onMouse; /**<  当前鼠标是否在血条上*/

	int m_RenderCount; /**<  绘制计次，用于显示fps */
	int m_fps;	/**<  平均fps */
	clock_t m_Clock_PreRender;	/**< 上一次刷新显示的时间 */
};

