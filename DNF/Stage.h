#pragma once
#include "Character.h"
#include "Dungeon.h"
using namespace cv;

class COtherObject;
class CMonster;
class CStage
{
public:
	struct NEXT_STAGE
	{
		CStage* top, *bottom, *left, *right;
		NEXT_STAGE() :top(NULL), bottom(NULL), left(NULL), right(NULL) {}
		NEXT_STAGE(CStage* t, CStage* b, CStage* l, CStage* r) :top(t), bottom(b), left(l), right(r) {}
	};
	static Mat s_Mat_Monster_Hphud, s_Mat_Monster_Hphud_, s_Mat_Monster_Hp[5], s_Mat_Monster_Hp_Mask[5];
	static Mat s_Mat_BossMonster_Hphud, s_Mat_BossMonster_Hphud_, s_Mat_BossMonster_Hp[5], s_Mat_BossMonster_Hp_Mask[5];
	static Mat s_Mat_HpNumber[11];
public:
	static const int s_OffsetY = 360;
	static const int s_ViewHeight = 190;
	static const int s_ViewWidth = 640;
public:
	virtual void InitStage() {};  //�����า�� ,������Դ�ĳ�ʼ������������� ÿ�ν���ó�����Ҫ����һ��
	virtual void QuitStage() {}; //�뿪��ǰ���ã������ͷ���Դ
	CStage() ;
	virtual ~CStage() {};
	void Render(Mat& mat);
	void HandleInput(int input);
	virtual void Update(CDungeon* dungeon); 

	int GetViewX() { return m_ViewX; };
	void SetViewX(int x);
	void SetNextStage(NEXT_STAGE n) { m_NextStage = n; }
	NEXT_STAGE GetNextStage() { return m_NextStage; }
	void SetCharacter(CCharacter* p) { m_Character = p; }
	void SetScorePointer(int* p) {m_DungeonScorePointer = p;}
	void AddScore(int add) { (*m_DungeonScorePointer) += add; }

	CCharacter* GetCharacter() { return m_Character; }

	int GetStageWidth() { return m_StageWidth; }
	void SetStageWidth(int width);

	std::vector<COtherObject*> m_OtherObjects;
	std::vector<CMonster*> m_Monsters;
	bool IsBossRoom() { return m_IsBossRoom; }
	bool IsClearance() { return m_IsClearance; }

	CMonster* GetTargetMonster() { return m_TargetMonster; }
	void SetTargetMonster(CMonster* p) { m_TargetMonster = p; }
protected:
	void __ShowMonsterHp(Mat& mat, int hp_cur, int hp_animation, int width,bool isboss);
	Mat MatMergeTransparentImage(Mat& srcImage, Mat& dstImagePtr);
	Mat m_mat_MidBG, m_mat_MidBG_Mask; //�о�
	Mat m_mat_FarBG, m_mat_FarBG_Mask; //Զ��
	Mat m_Mat_BG;

	int m_ViewX; //������Ҫ����ʾ����ʼx
	int m_ViewX_far; //Զ��
	int m_StageWidth;
	bool m_IsClearance; //��ǰ�����Ƿ���ͨ��
	bool m_IsBossRoom; //��ǰ�����Ƿ���boos����
	CCharacter* m_Character = NULL;
	NEXT_STAGE m_NextStage;

	CMonster* m_TargetMonster;
	int m_TargetMonsterHp, m_TargetMonsterHp_Animation;
	Mat m_Mat_TargetMonsterAvator;
	String m_TargetMonsterName;
	bool m_isTargetMonsterBoss;
	int*  m_DungeonScorePointer;
	//Font m_Font_MonsterHpHud;
};

