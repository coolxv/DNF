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
	virtual void Update() {};
	virtual void DoRender(Mat& mat);
	virtual void DoInitDungeon() {};
	virtual void HandleMouse(int Event, int x, int y, int flags, void* param) {};
	virtual int GetViewX();

	void SwitchStage(CStage* stage);
	void SetCharacter(CCharacter* character) { m_Character = character; };
	CStage* GetCurStage() { return m_CurStage; }

	bool GetIsQuit() { return m_Quit; }
	CDungeon* GetNextDungeon() { return m_NextDungeon; };
protected:
	CCharacter* m_Character = NULL;
	CStage* m_CurStage = NULL;
	std::vector<CStage*> m_Stages;
	bool m_Quit = false;
	CDungeon* m_NextDungeon=NULL;
};



class Dungeon_Rolland :
	public CDungeon
{
public:
	Dungeon_Rolland();
	~Dungeon_Rolland(); 
	void Update();
	void DoInitDungeon();
};

class Dungeon_Home :
	public CDungeon
{
public:
	static Mat s_Mat_BG,s_Mat_Gate,s_Mat_Gate_Mask;
	static Mat s_Mat_Seria[10], s_Mat_Seria_Mask[10];
public:
	Dungeon_Home();
	~Dungeon_Home();

	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	clock_t m_clock_SeriaRender;
	int m_SeriaMatId;
};


class Dungeon_SelectDungeon :
	public CDungeon
{
	enum DUNGEON
	{
		DUNGEON_ROLLAND, DUNGEON_ROLLANDDEEP, DUNGEON_NONE
	};
public:
	static Mat s_Mat_BG;
	static Mat s_Mat_DungeonPix[2], s_Mat_DungeonPix_Select[2];
	static int s_PixPos[2][2];
	static int s_SelectPixPos[2][2];
public:
	Dungeon_SelectDungeon();
	~Dungeon_SelectDungeon();


	void HandleMouse(int Event, int x, int y, int flags, void* param);
	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void DoInitDungeon();

private:
	void __RenderDungeonPix(Mat& mat,int dungeon,bool select);
	int m_SelectedDungeon = DUNGEON_NONE; //当前被选中的
};
