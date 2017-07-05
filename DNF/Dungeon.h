#pragma once
#include "stdafx.h"
#include "Character.h"

class CStage;
class CDungeon
{
public:
	CDungeon();
	virtual ~CDungeon();

	void SwitchStage(CStage* stage);
	void DoHandleInput(int input);
	void Update();
	void DoRender(Mat& mat);
	void SetCharacter(CCharacter* character) { m_Character = character; };
	CStage* GetCurStage() { return m_CurStage; }
	virtual void DoInitDungeon() {};
protected:
	CCharacter* m_Character;
	CStage* m_CurStage;
	std::vector<CStage*> m_Stages;
};



class Dungeon_Rolland :
	public CDungeon
{
public:
	Dungeon_Rolland();
	~Dungeon_Rolland(); 
	void DoInitDungeon();
};