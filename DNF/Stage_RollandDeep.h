#pragma once
#include "Stage.h"

class Gate;
class CStage_RollandDeep :
	public CStage
{
public:
	static int RollandDeepStageWidths[7];
	CStage_RollandDeep();
	~CStage_RollandDeep();

	virtual void InitStage() {};
	
protected:
	Gate* _CreatGate(int dir);
	clock_t m_Clock_GateTimer; //����ʵ����ʱ���ţ�-1��ʾ��ǰ�����Ÿ���
	Gate* m_LeftGate, *m_RightGate, *m_TopGate, *m_BottomGate;
};

class RollandDeepStage0 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage0() { SetStageWidth(RollandDeepStageWidths[0]); };
	~RollandDeepStage0() {};
};

class RollandDeepStage1 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage1() { SetStageWidth(RollandDeepStageWidths[1]); };
	~RollandDeepStage1() {};
};

class RollandDeepStage2 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage2() { SetStageWidth(RollandDeepStageWidths[2]); };
	~RollandDeepStage2() {};
};

class RollandDeepStage3 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage3() { SetStageWidth(RollandDeepStageWidths[3]); };
	~RollandDeepStage3() {};
};

class RollandDeepStage4 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage4() { SetStageWidth(RollandDeepStageWidths[4]); };
	~RollandDeepStage4() {};
};

class RollandDeepStage5 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage5() { SetStageWidth(RollandDeepStageWidths[5]); };
	~RollandDeepStage5() {};
};

class RollandDeepStage6 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage6() { SetStageWidth(RollandDeepStageWidths[6]); };
	~RollandDeepStage6() {};
};
