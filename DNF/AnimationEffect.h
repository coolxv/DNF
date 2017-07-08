#pragma once
#include "stdafx.h"
class CDungeon;

/**
 * @class CAnimationEffect
 * @brief 游戏中所有的动画效果
 * 
 *
 */
class CAnimationEffect
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();

	/**
	 * @brief 绘制函数
	 * 
	 * 在参数mat上绘制自身。纯虚绘制函数，由子类覆盖实现
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void  
	 */
	 virtual void DoRender(Mat& mat, int viewX) = 0;

	/**
	 * @brief 返回当前动画是否已结束
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetComplete();
	
	/**
	 * @brief 鼠标回调函数
	 * 
	 * 
	 * @param  int Event	鼠标事件类型
	 * @param  int x	鼠标x坐标
	 * @param  int y	鼠标y坐标
	 * @param  int flags	鼠标拖拽事件，键盘鼠标联合事件
	 * @param  void * param	
	 * @return  void  
	 */
	 virtual void onMouse(int Event, int x, int y, int flags, void* param) {};
protected:
	bool m_Complete;	/**<  标记当前动画是否已结束 */
	int m_MatId;	/**<  这一帧需要绘制的图片序号 */
	clock_t m_Clock_Update;	/**<  上一次更新的时间 */
};

/**
 * @class CPhysicalAttackAnimation
 * @brief 角色攻击特效动画
 * 
 *
 */
class CPhysicalAttackAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_Slash[3][3], s_Mat_Slash_Mask[3][3];	/**<  攻击特效资源图 */
	
	/**
	 * @brief 构造函数
	 * 
	 * 指定坐标和类型
	 * @param  Point3i point	动画显示的绝对坐标
	 * @param  int type		攻击特效的类型，0~3
	 * @return
	 */
	 CPhysicalAttackAnimation(Point3i point,int type);
	
	/**
	 * @brief 析构函数
	 * 
	 * 
	 * @return    
	 */
	 ~CPhysicalAttackAnimation();
	
	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);
private:
	Point3d m_Point_Coor;	/**<  动画显示的绝对坐标 */
	int m_Type;	/**<  攻击动画的类型*/
};

/**
 * @class CAwakeDEffectAnimation
 * @brief D技能的动画特效
 * 
 *
 */
class CAwakeDEffectAnimation
	:public CAnimationEffect
{
public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @param  int pos	显示的方向，DIR_LEFT、DIR_RIGHT
	 * @return    
	 */
	 CAwakeDEffectAnimation(int pos);
	
	/**
	 * @brief 析构函数
	 * 
	 * 
	 * @return    
	 */
	 ~CAwakeDEffectAnimation() {};
	
	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);
private:
	static Mat s_Mat_Draw[30];	/**< 资源图 */
	Mat mask;	/**<  用于实现动画的蒙板 */
	int m_pos;	/**<  动画显示的方向 */
};

/**
 * @class CAwakeSEffectAnimation
 * @brief S技能的动画特效
 * 
 *
 */
class CAwakeSEffectAnimation
	:public CAnimationEffect
{
public:
	
	/**
	* @brief 构造函数
	*
	*
	* @param  int pos	显示的方向，DIR_LEFT、DIR_RIGHT
	* @return
	*/
	 CAwakeSEffectAnimation(int pos);
	
	/**
	 * @brief 析构函数
	 * 
	 * 
	 * @return    
	 */
	 ~CAwakeSEffectAnimation() {};
	
	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);

private:
	static Mat s_Mat_DrawS[35];	/**<  资源图 */
	Mat mask;	/**<  用于实现动画的蒙板 */
	int m_pos;	 /**<  动画显示的方向 */
};

/**
 * @class CNumberAnimation
 * @brief 伤害数字动画特效
 * 
 *
 */
class CNumberAnimation
	:public CAnimationEffect
{
public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 指定数字，位置，样式
	 * @param  long long num	要显示的数字
	 * @param  Point3i p	数字的绝对三维坐标
	 * @param  int style	数字的样式
	 * @return    
	 */
	 CNumberAnimation(long long num,Point3i p,int style);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CNumberAnimation() {};
	
	/**
	* @brief 绘制函数
	*
	* 在参数mat上绘制自身
	* @param  Mat & mat 回调mat
	* @param  int viewX	当前游戏画面的绝对坐标
	* @return  void
	*/
	 void DoRender(Mat& mat, int viewX);
private:
	static Mat s_Mat_Number[3][10];	/**<  资源图 */
	int m_StayTime;	/**<  伤害数字需要停留时间 */
	int m_NumStyle;	/**<  数字字体类型 0~3 */
	int m_Zspeed;	/**< 动画 */
	clock_t m_Clock_stay;	/**< 伤害数字停留计时 */
	Point3i m_Pos;	/**<  动画起始位置 */
	Point3i m_CurPos;	/**<  当前动画的位置 */
	int m_length;	/**<  数字的位数 */
	std::vector<int> m_v_num;	/**< 存储每一位数字 */
};

/**
 * @class CResultAnimation
 * @brief 通关结算界面动画
 * 
 *
 */
class CResultAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_panel,s_Mat_time_text,s_Mat_score_text1, s_Mat_score_text2, s_Mat_score_text3,s_Mat_exp_text;	/**< 资源图 */
	static Mat s_Mat_min, s_Mat_sec;	/**< 资源图 */
	static Mat s_Mat_Number[10],s_Mat_ScoreRank[9]; /**< 资源图 */
	static Mat s_Mat_SelectBG,s_Mat_Return[2],s_Mat_Other[2],s_Mat_Continue[2];	/**< 资源图 */
	
	/**
	 * @brief 结算动画构造函数
	 * 
	 * 指定结算界面的所有参数
	 * @param  int score	评价点数
	 * @param  int score_rank	评价等级
	 * @param  int exp	获得经验
	 * @param  int min	通关所用分钟
	 * @param  int sec	通关所用秒数
	 * @param  int lsec	通关所用厘秒
	 * @param  int min_record	通关记录，分钟
	 * @param  int sec_record	通关记录，秒
	 * @param  int lsec_record	通关记录，厘秒
	 * @param  CDungeon * cur_dungeon	当前副本对象指针
	 * @return    
	 */
	 CResultAnimation(int score,int score_rank,int exp,int min,int sec,int lsec
		,int min_record,int sec_record,int lsec_record,CDungeon* cur_dungeon);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CResultAnimation();

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
	* @brief 鼠标回调函数
	*
	*
	* @param  int Event	鼠标事件类型
	* @param  int x	鼠标x坐标
	* @param  int y	鼠标y坐标
	* @param  int flags	鼠标拖拽事件，键盘鼠标联合事件
	* @param  void * param
	* @return  void
	*/
	void onMouse(int Event, int x, int y, int flags, void* param);
private:
	/** @brief 当前鼠标选中的选项 */
	enum __SELECT
	{
		RETURN,	/**< 返回城镇 */
		CONTINUE,	/**<  再次挑战 */
		OTHERDUNGEON,	/**<  选择其他地下城 */
		NONE	/**<  未选中任何选项 */
	};
	
	/**
	 * @brief 合并两个Mat
	 * 
	 * 
	 * @param  Mat & a	Mata
	 * @param  Mat & b	Matb
	 * @param  int x b合并到a的左上角坐标x
	 * @param  int y	b合并到a的左上角坐标y
	 * @param  int h	需要忽略的透明度
	 * @return  void  
	 */
	 void __Merge(Mat& a, Mat& b, int x, int y, int h);
	
	/**
	 * @brief 显示数字
	 * 
	 * 用于显示评价点数，经验的数值
	 * @param  Mat & bg	背景底图
	 * @param  int x	相对坐标x
	 * @param  int y	相对坐标y
	 * @param  int num		需要显示的数字
	 * @return  void  
	 */
	 void __ShowNumber(Mat& bg, int x, int y, int num);
	
	/**
	 * @brief	显示时间
	 * 
	 * 用于显示通关时间，通关记录时间
	 * @param  Mat & bg	背景地图
	 * @param  int x	相对坐标x
	 * @param  int y	相对坐标y
	 * @param  int min	分
	 * @param  int sec	秒
	 * @param  int lsec	厘秒
	 * @return  void  
	 */
	 void __ShowTime(Mat& bg, int x, int y, int min, int sec, int lsec);
	 int m_Score;	/**<  评价点数 */
	 int m_Score_Rank;	/**<  评价等级 */
	 int m_Exp;	/**<  经验 */
	 int m_Min, m_Sec, m_LSec;		/**< 通关时间 */
	 int m_Min_Record, m_Sec_Record, m_LSec_Record;	/**<  通关记录 */
	 bool m_IsSelecting; /**< 当前是否可以选择 */
	 int m_selected;	/**<  当前选择的选项 */
	 Rect m_rect_return,m_rect_other,m_rect_continue;	/**<  选项的位置判定矩阵 */
	 CDungeon* m_CurDungeon;	/**<  当前所在地下城的对象指针 */
	 clock_t m_StartTime;	/**<  动画开始时间 */
};

/**
 * @class CGameOverAnimation
 * @brief 角色死亡倒计时动画
 * 
 *	以倒计时的形式
 */
class CGameOverAnimation
	:public CAnimationEffect
{

public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @param  CDungeon * dungeon	当前所在地下城的对象指针
	 * @return    
	 */
	 CGameOverAnimation(CDungeon* dungeon);
	
	/**
	 * @brief 析构函数
	 * 
	 * 
	 * @return    
	 */
	 ~CGameOverAnimation() {};

	 /**
	 * @brief 绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	void DoRender(Mat& mat, int viewX);
private:
	Mat m_Mat_Number[10],m_Mat_Number_Mask[10];		/**<  资源图 */
	clock_t m_AnimationStart;	/**< 动画开始时间 */
	CDungeon* m_Dungeon;	/**< 当前所在地下城的对象指针 */
};