#pragma once
#include "Stage.h"

class Gate;
class CRollandStage :
	public CStage
{
public:
	static int RollandStageWidths[6];
public:
	virtual void InitStage() {};
	void QuitStage();

	CRollandStage();
	~CRollandStage() {}; //stage�����������Ѿ��� virtual����

	clock_t m_Clock_GateTimer; //����ʵ����ʱ���ţ�-1��ʾ��ǰ�����Ÿ���
	Gate* m_LeftGate, *m_RightGate, *m_TopGate, *m_BottomGate;
};

class RollandStage0 :
	public CRollandStage
{
public:
	void InitStage();

	RollandStage0() { SetStageWidth(RollandStageWidths[0]); };
	~RollandStage0() {};
};

class RollandStage1 :
	public CRollandStage
{
public:
	void InitStage();
	
	RollandStage1() { SetStageWidth(RollandStageWidths[1]); };
	~RollandStage1() {};
};


class RollandStage2 :
	public CRollandStage
{
public:
	void InitStage();

	RollandStage2() { SetStageWidth(RollandStageWidths[2]); };
	~RollandStage2() {};

};


class RollandStage3 :
	public CRollandStage
{
public:
	void InitStage();

	RollandStage3() { SetStageWidth(RollandStageWidths[3]); };
	~RollandStage3() {};
};


class RollandStage4 :
	public CRollandStage
{
public:
	void InitStage();

	RollandStage4() { SetStageWidth(RollandStageWidths[4]); };
	~RollandStage4() {};
};


class RollandStage5 :
	public CRollandStage
{
public:
	void InitStage();

	RollandStage5();
	~RollandStage5() {};
};

