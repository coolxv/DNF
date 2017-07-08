#include "Game.h"
#include <windows.h>


void CGame::HandleInput()
	{
	char key = 0;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_CurDungeon->DoHandleInput(VK_UP);
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_CurDungeon->DoHandleInput(VK_DOWN);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_CurDungeon->DoHandleInput(VK_LEFT);
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_CurDungeon->DoHandleInput(VK_RIGHT);
	if (GetAsyncKeyState(KEY_ATTACK) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_ATTACK);
	if (GetAsyncKeyState(KEY_JUMP) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_JUMP);
	if (GetAsyncKeyState(KEY_JUMPBACK) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_JUMPBACK);
	if (GetAsyncKeyState(KEY_EFFECTZ) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_EFFECTZ);
	if (GetAsyncKeyState(KEY_EFFECTS) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_EFFECTS);
	if (GetAsyncKeyState(KEY_EFFECTD) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_EFFECTD);
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_CurDungeon->DoHandleInput(KEY_SPACE);
	if (GetAsyncKeyState('B') & 0x8000)
		m_CurDungeon->DoHandleInput('B');
	if (GetAsyncKeyState('N') & 0x8000)
		m_CurDungeon->DoHandleInput('N');
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		m_IsRunning = false;
}

void CGame::Update()
{
	if (m_CurDungeon->GetIsQuit())
	{
		//切换副本
		CDungeon* next = m_CurDungeon->GetNextDungeon();
		if (typeid(*next) == typeid(CDungeon_Home) || typeid(*next) == typeid(CDungeon_Comics)|| typeid(*next) == typeid(CDungeon_Start))
			m_GameState = GAMESTATE_HOME;
		else if (typeid(*next) == typeid(CDungeon_SelectDungeon))
			m_GameState = GAMESTATE_SELECTDUNGEON;
		else 
			m_GameState = GAMESTATE_INDUNGEON;
		delete m_CurDungeon; //释放内存
		for (auto it = m_AnimationEffects.begin(); it != m_AnimationEffects.end();it++)
		{
			delete *it;
		}
		m_AnimationEffects.clear();
		next->SetCharacter(m_Character);
		next->DoInitDungeon();
		m_CurDungeon = next;
	}
	m_CurDungeon->Update();
	m_Hud->Update();
	//mStage->updatestate();
	//mCharacter->updatestate();
}

void CGame::Render()
{
	m_CurDungeon->DoRender(m_Mat_Game);
	//mStage->render(mat_game,mCharacter);  //人物的绘制会在Stage中的render调用绘制


	int viewX = m_CurDungeon->GetViewX();

	for (auto it = m_AnimationEffects.begin(); it != m_AnimationEffects.end();)
	{
		if ((*it)->GetComplete())
		{
			delete *it;
			it = m_AnimationEffects.erase(it);
		}
		else
		{
			(*it)->DoRender(m_Mat_Game, viewX);
			it++;
		}
	}
	if(m_GameState == GAMESTATE_INDUNGEON)
		m_Hud->Render(m_Mat_Game);
	imshow("DNF",m_Mat_Game);
	waitKey(1);
}

CGame::CGame()
{

	srand(unsigned(time(NULL)));
	m_GameState = GAMESTATE_HOME;
	m_Character = new CCharacter();
	m_Character->SetAnimationEffectsVector(&m_AnimationEffects);

	m_CurDungeon = new CDungeon_Start();
	m_CurDungeon->SetCharacter(m_Character);
	m_CurDungeon->DoInitDungeon();

	m_Hud = new CHud();
	m_Hud->SetCharacter(m_Character);
	m_Hud->SetDungeon(m_CurDungeon);
	m_Hud->Initial();
}

void CGame::onMouse(int Event, int x, int y, int flags, void* param)
{
	if(GAMESTATE_INDUNGEON)
		m_Hud->HandleMouse(Event, x, y, flags, param);
	for (auto it = m_AnimationEffects.begin(); it != m_AnimationEffects.end(); it++)
		(*it)->onMouse(Event, x, y, flags, param);
	m_CurDungeon->HandleMouse(Event, x, y, flags, param);
}

CGame::~CGame()
{
	if (m_Character)
		delete m_Character;
	if (m_CurDungeon)
		delete m_CurDungeon;
	if (m_Hud)
		delete m_Hud;

	for (auto it = m_AnimationEffects.begin(); it != m_AnimationEffects.end(); it++)
		delete *it;
	m_AnimationEffects.clear();
}


void CGame::Run()
{
	clock_t nextFrameTime = clock();
	clock_t currentFrameTime = nextFrameTime;
	m_IsRunning = true;
	while (m_IsRunning)
	{
		HandleInput();	//处理键盘输入
		Update();			//更新游戏状态
		Render();			//绘制游戏画面
		nextFrameTime += FRAMES_TIME;
		currentFrameTime = clock();
		if (nextFrameTime > currentFrameTime)
			waitKey(nextFrameTime - currentFrameTime);
	}
	PlaySound(NULL, NULL, NULL);
}