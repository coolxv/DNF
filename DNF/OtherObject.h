#pragma once
#include  "Stage.h"
#include "Dungeon.h"
#include "ObjectBase.h"
#include "Monster.h"
using namespace cv;
class COtherObject
	:public CObjectBase
{
public:
	COtherObject();
	virtual ~COtherObject();
	virtual bool Update(CStage& stage, CDungeon* dungeon) { return true; };
	virtual void DoRender(Mat& mat, int viewX) = 0;

	bool GetComplete() { return m_Complete; }

protected:
	clock_t m_Clock_PreRender;
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask; //用于显示
	bool m_Complete;
};



class Gate :
	public COtherObject
{
public:
	static Mat s_Mat_Gate0[4][4], s_Mat_Gate0_Mask[4][4]; 
	enum GATE_POSITION //门的位置
	{
		LEFT_GATE, RIGHT_GATE, TOP_GATE, BOTTOM_GATE
	};
	enum GATE_TYPE
	{
		CLOSE_GATE,OPEN_GATE,BOOS_GATE,NORMAL_GATE
	};
public:
	Gate(int position, int x, int y,CStage* stage);
	~Gate();
	bool Update(CStage& stage,CDungeon* dungeon);
	void DoRender(Mat& mat,  int viewX);

public:
	void Init() {};
	clock_t m_Clock_GateTimer;
	int m_GateTYpe;
	int m_GatePosition;
	int m_MatId; //闪烁效果
};

class Tree :
	public COtherObject
{
public:
	static Mat s_Mat_Tree0[1], s_Mat_Tree0_Mask[1];
	static int s_Tree_SetOffX[1],s_Tree_SetOffY[1];
public:
	Tree(int x, int y,int type);
	~Tree();
	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	void Init();
	int m_TreeType;
};


class ThrowStone
	:public COtherObject
{
public:
	static Mat s_Mat_ThrowStone[4], s_Mat_ThrowStone_Mask[4];

	ThrowStone(int x,int y,int z,int dir,int power);
	~ThrowStone() {};

	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	int m_Power;
	int m_MatId;
	int m_Dir;
};

struct _Meat
{
	Point3i Pos;
	Point3i Speed;
	int Type;
	_Meat() {}
	_Meat(Point3i p, Point3i sp, int t) :Pos(p), Speed(sp), Type(t) {}
};

class Meat
	:public COtherObject
{
public:
	static Mat s_Mat_Meat[1][4], s_Mat_Meat_Mask[1][4];
	Meat(CMonster* monster, int type);
	~Meat() {};

	void DoRender(Mat& mat, int viewX);
private:
	std::vector<_Meat> m_Meats;
	int m_MeatType;
	clock_t m_Clock_PreUpdate;
	clock_t m_Clock_Fell;
};

