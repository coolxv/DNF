#pragma once
#include "Dungeon.h"
#include "Dungeon_Home.h"
#include "Dungeon_SelectDungeon.h"
#include "Dungeon_Start.h"
#include "Dungeon_Comics.h"
#include "OtherObject.h"
#include "AnimationEffect.h"
#include "Hud.h"

#define FRAMES_PER_SECOND  100
#define FRAMES_TIME ( 1000 / FRAMES_PER_SECOND )
class CGame
{
public:
	enum GAMESTATE
	{
		GAMESTATE_HOME,GAMESTATE_INDUNGEON,GAMESTATE_SELECTDUNGEON
	};
private:
	bool m_IsRunning;
	void HandleInput(); //处理输入：这些输入包括，来自于交互设备（键盘，鼠标，游戏控制器等等）的输入
	void Update();	//系统更新（update）：（根据输入或者自发的）对各个子系统进行更新，以决定当前的游戏状态
	void Render(); //渲染（render）：对整个游戏场景进行渲染。
	void __MergeMat(Mat& a, Mat& b, Mat& b_, int div);
	CCharacter* m_Character = NULL;
	CDungeon* m_CurDungeon = NULL;
	CHud* m_Hud = NULL;
	//Dungeon* dungeon_rolland;

	Mat m_Mat_ui;
	Mat m_Mat_ui_mask;
	Mat m_Mat_Game;
	
	std::vector<CAnimationEffect*> m_AnimationEffects;
	
	int m_GameState;
public:
	CGame();
	~CGame();
	void Run();
	void InitRec();

	void onMouse(int Event, int x, int y, int flags, void* param);
};

