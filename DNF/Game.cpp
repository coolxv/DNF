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
	m_GameState = GAMESTATE_HOME;
	InitRec();

	m_Character = new CCharacter();
	m_Character->SetAnimationEffectsVector(&m_AnimationEffects);

	//m_CurDungeon = new Dungeon_Rolland();
	//m_CurDungeon = new CDungeon_Home();
	m_CurDungeon = new CDungeon_Start();
	//m_CurDungeon = new CDungeon_Comics();
	m_CurDungeon->SetCharacter(m_Character);
	m_CurDungeon->DoInitDungeon();

	m_Hud = new CHud();
	m_Hud->SetCharacter(m_Character);
	m_Hud->SetDungeon(m_CurDungeon);
	m_Hud->Initial();
}

void CGame::InitRec()
{
	m_Mat_ui = imread("./ImagePacks2/BaseUI/mainhud.png", -1);
	m_Mat_ui_mask = imread("./ImagePacks2/BaseUI/mainhud.png", 0);
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
		HandleInput();
		Update();
		Render();
		nextFrameTime += FRAMES_TIME;
		currentFrameTime = clock();
		//waitKey(1);
		if (nextFrameTime > currentFrameTime)
			waitKey(nextFrameTime - currentFrameTime);
	}
}




//将a，b合并
void CGame::__MergeMat(Mat& a, Mat& b, Mat& b_, int div)
{
	int tmp = a.rows;
	copyMakeBorder(a, a, 0, b.rows - div, 0, 0, 0);
	Mat roi(a, Rect(0, tmp - div, b.cols, b.rows));
	b.copyTo(roi, b_);
}