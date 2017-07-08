#pragma once
#include "Stage.h"

class Gate;

/**
 * @class CStage_RollandDeep
 * @brief "洛兰深处"的场景基类
 * 
 *
 */
class CStage_RollandDeep :
	public CStage
{
public:
	static int RollandDeepStageWidths[7];/**<  7个场景的宽度*/
	
	/**
	 * @brief 构造
	 * 
	 * 
	 * @return    
	 */
	 CStage_RollandDeep();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CStage_RollandDeep();

	
	/**
	 * @brief 场景的初始化
	 * 
	 * 用于生成怪物，门，树
	 * @return  void  
	 */
	 virtual void InitStage() {};
	
protected:
	
	/**
	 * @brief 创建指定位置的门
	 * 
	 * 
	 * @param  int dir
	 * @return  Gate*  
	 */
	 Gate* _CreatGate(int dir);
	 clock_t m_Clock_GateTimer; /**<  用来实现延时进门，-1表示当前不在门附近*/
	 Gate* m_LeftGate, *m_RightGate, *m_TopGate, *m_BottomGate;	/**<  4个位置的门的对象指针*/
};

/**
 * @class RollandDeepStage0
 * @brief "洛兰深处"场景0
 * 
 *
 */
class RollandDeepStage0 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage0() { SetStageWidth(RollandDeepStageWidths[0]); };
	~RollandDeepStage0() {};
};

/**
* @class RollandDeepStage1
* @brief "洛兰深处"场景1
*
*
*/
class RollandDeepStage1 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage1() { SetStageWidth(RollandDeepStageWidths[1]); };
	~RollandDeepStage1() {};
};

/**
* @class RollandDeepStage2
* @brief "洛兰深处"场景2
*
*
*/
class RollandDeepStage2 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage2() { SetStageWidth(RollandDeepStageWidths[2]); m_IsBossRoom = true; };
	~RollandDeepStage2() {};
};

/**
* @class RollandDeepStage3
* @brief "洛兰深处"场景3
*
*
*/
class RollandDeepStage3 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage3() { SetStageWidth(RollandDeepStageWidths[3]); };
	~RollandDeepStage3() {};
};

/**
* @class RollandDeepStage4
* @brief "洛兰深处"场景4
*
*
*/
class RollandDeepStage4 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage4() { SetStageWidth(RollandDeepStageWidths[4]); };
	~RollandDeepStage4() {};
};

/**
* @class RollandDeepStage5
* @brief "洛兰深处"场景5
*
*
*/
class RollandDeepStage5 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage5() { SetStageWidth(RollandDeepStageWidths[5]); };
	~RollandDeepStage5() {};
};

/**
* @class RollandDeepStage6
* @brief "洛兰深处"场景6
*
*
*/
class RollandDeepStage6 :
	public CStage_RollandDeep
{
public:
	void InitStage();

	RollandDeepStage6() { SetStageWidth(RollandDeepStageWidths[6]); };
	~RollandDeepStage6() {};
};
