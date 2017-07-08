#pragma once
#include "Dungeon.h"
#include "Dungeon_Rolland.h"
#include "Dungeon_Home.h"
#include "Dungeon_SelectDungeon.h"
#include "Dungeon_Start.h"
#include "Dungeon_Comics.h"
#include "Dungeon_Maze.h"
#include "OtherObject.h"
#include "AnimationEffect.h"
#include "Hud.h"
#define FRAMES_PER_SECOND  100
#define FRAMES_TIME ( 1000 / FRAMES_PER_SECOND )

/**
 * @class CGame
 * @brief Game控制类
 * 
 *控制整个游戏的流程
 */
class CGame
{
public:
	/** @brief  游戏状态 */
	enum GAMESTATE
	{
		GAMESTATE_HOME,	/**<	城镇中 */
		GAMESTATE_INDUNGEON,	/**<  地下城中 */
		GAMESTATE_SELECTDUNGEON	/**<  选择地下城中 */
	};
private:
	bool m_IsRunning; /**<  控制游戏是否运行 */
	void HandleInput(); /**< 处理输入：这些输入包括，来自于交互设备（键盘，鼠标，游戏控制器等等）的输入 */
	void Update();	/**<  系统更新（update）：（根据输入或者自发的）对各个子系统进行更新，以决定当前的游戏状态 */
	void Render(); /**<  渲染（render）：对整个游戏场景进行渲染。 */
	CCharacter* m_Character = NULL;/**<  角色对象指针*/
	CDungeon* m_CurDungeon = NULL;	/**<  当前角色所在的地下城*/
	CHud* m_Hud = NULL;	/**<  下方的角色技能血条栏视图 */
	Mat m_Mat_Game;	/**<  用于显示游戏画面的Mat */
	std::vector<CAnimationEffect*> m_AnimationEffects; /**<  显示中的动画容器*/
	int m_GameState;	/**<  游戏状态 */
public:
	CGame();
	~CGame();
	
	/**
	 * @brief 游戏主循环
	 * 
	 * 
	 * @return  void  
	 */
	 void Run();

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
};

