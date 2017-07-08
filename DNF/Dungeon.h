#pragma once
#include "stdafx.h"
#include "Character.h"

class CStage;
class CDungeon
{
public:
	CDungeon();
	virtual ~CDungeon();

	virtual void DoHandleInput(int input);
	virtual void Update();
	virtual void DoRender(Mat& mat) {};
	virtual void DoInitDungeon() {};
	virtual void HandleMouse(int Event, int x, int y, int flags, void* param) {};
	virtual int GetViewX();

	void SwitchStage(CStage* stage);
	void SetCharacter(CCharacter* character) { m_Character = character; };
	CStage* GetCurStage() { return m_CurStage; }

	bool GetIsQuit() { return m_Quit; }
	void SetQuit(bool q) { m_Quit = q; }
	CDungeon* GetNextDungeon() { return m_NextDungeon; };
	void SetNextDungeon(CDungeon* next) { m_NextDungeon = next; }

	void AddScore(int add) { m_score += add; }
protected:
	static Mat s_Mat_DungeonLoading;
	CCharacter* m_Character = NULL;
	CStage* m_CurStage = NULL;
	std::vector<CStage*> m_Stages;
	bool m_Quit = false; //当前副本是否需要退出，用于Game切换副本
	bool m_IsClearance; //是否已通过
	CDungeon* m_NextDungeon=NULL;
	clock_t m_Clock_Start;
	clock_t m_Clock_PreHandleInput;
	int m_score;
	bool m_GameOver;
	bool m_ShowMinMap;
	void _Merge(Mat& a, Mat& b, int x, int y, int alpha);
};
