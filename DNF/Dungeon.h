#pragma once
#include "stdafx.h"
#include "Character.h"
class CStage;

/**
 * @class CDungeon
 * @brief 地下城基类
 * 
 *
 */
class CDungeon
{
public:
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @return    
	 */
	 CDungeon();
	
	/**
	 * @brief 析构函数
	 * 
	 * 释放地下城的所有场景
	 * @return    
	 */
	 virtual ~CDungeon();
	
	/**
	 * @brief 处理键盘事件
	 * 
	 * 
	 * @param  int input	键值
	 * @return  void  
	 */
	 virtual void DoHandleInput(int input);
	
	/**
	 * @brief 更新地下城状态
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void Update();
	 
	 /**
	  * @brief 地下城的绘制
	  * 
	  * 在mat上绘制
	  * @param  Mat & mat	绘制底图
	  * @return  void  
	  */
	  virtual void DoRender(Mat& mat) {};
	
	/**
	 * @brief 初始化地下城
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void DoInitDungeon() {};

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
	 virtual void HandleMouse(int Event, int x, int y, int flags, void* param) {};
	
	/**
	 * @brief 返回画面绝对坐标
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetViewX();

	
	/**
	 * @brief 切换场景
	 * 
	 * 用于地下城中场景间的切换
	 * @param  CStage * stage
	 * @return  void  
	 */
	 void SwitchStage(CStage* stage);
	
	/**
	 * @brief 设置角色对象指针
	 * 
	 * 
	 * @param  CCharacter * character
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* character) { m_Character = character; };
	
	/**
	 * @brief 获取当前场景对象指针
	 * 
	 * 
	 * @return  CStage*  
	 */
	 CStage* GetCurStage() { return m_CurStage; }

	
	/**
	 * @brief 返回当前地下城是否要退出
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetIsQuit() { return m_Quit; }
	
	/**
	 * @brief 设置当前地下城是否要退出
	 * 
	 * 
	 * @param  bool q
	 * @return  void  
	 */
	 void SetQuit(bool q) { m_Quit = q; }
	
	/**
	 * @brief 设置当前地下城退出后需要切换的地下城对象
	 * 
	 * 
	 * @return  CDungeon*  
	 */
	 CDungeon* GetNextDungeon() { return m_NextDungeon; };
	
	/**
	 * @brief 返回当前地下城退出后需要切换的地下城对象
	 * 
	 * 
	 * @param  CDungeon * next
	 * @return  void  
	 */
	 void SetNextDungeon(CDungeon* next) { m_NextDungeon = next; }

	
	/**
	 * @brief 增加评价点数
	 * 
	 * 
	 * @param  int add
	 * @return  void  
	 */
	 void AddScore(int add) { m_Score += add; }
protected:
	static Mat s_Mat_DungeonLoading; /**<  地下城加载界面资源图 */
	CCharacter* m_Character = NULL;	/**<  主角对象指针 */
	CStage* m_CurStage = NULL;	/**<  当前场景对象指针 */
	std::vector<CStage*> m_Stages; /**<  当前地下城的场景容器 */
	bool m_Quit = false; /**< 当前地下城是否需要退出，用于Game切换副本 */
	bool m_IsClearance; /**<  是否已通关 */
	CDungeon* m_NextDungeon=NULL;	/**<  当前地下城退出后Game需要切换的下一个地下城对象 */
	clock_t m_Clock_Start;	/**<  进入当前地下城的时间 */
	clock_t m_Clock_PreHandleInput;	/**<  上一次处理按键事件的时间 */
	int m_Score;	/**<  当前地下城的评价点数 */
	bool m_GameOver;	/**<  角色是否死亡，当前地下城结束 */
	bool m_ShowMinMap;	/**<  是否显示右上角小地图 */
	
	/**
	 * @brief 合并两个Mat
	 * 
	 * 将MatB合并到MatA上
	 * @param  Mat & a	MatA
	 * @param  Mat & b	MatB
	 * @param  int x	MatB左上角位于MatA的坐标
	 * @param  int y	MatB左上角位于MatY的坐标
	 * @param  int alpha	忽略的透明度阈值
	 * @return  void  
	 */
	 void _Merge(Mat& a, Mat& b, int x, int y, int alpha);
};
