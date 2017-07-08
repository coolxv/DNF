#pragma once
#include "Stage.h"

class Gate;

/**
 * @class CStage_Rolland
 * @brief "洛兰"的场景基类
 * 
 *
 */
class CStage_Rolland :
	public CStage
{
public:
	static int RollandStageWidths[6];	/**<  6个场景的宽度*/
public:
	
	/**
	 * @brief 初始化场景
	 *
	 * 用于生成怪物，门，树
	 * @return  void  
	 */
	 virtual void InitStage() {};

	
	/**
	 * @brief 构造
	 * 
	 * 
	 * @return    
	 */
	 CStage_Rolland();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~CStage_Rolland() {}; //stage的析构函数已经是 virtual的了

	 clock_t m_Clock_GateTimer; /**<  用来实现延时进门，-1表示当前不在门附近*/
	 Gate* m_LeftGate, *m_RightGate, *m_TopGate, *m_BottomGate;	/**<  4个方向的门的对象指针*/
};

/**
 * @class RollandStage0
 * @brief "洛兰"场景0
 * 
 *
 */
class RollandStage0 :
	public CStage_Rolland
{
public:
	void InitStage();

	RollandStage0() { SetStageWidth(RollandStageWidths[0]); };
	~RollandStage0() {};
};

/**
* @class RollandStage1
* @brief "洛兰"场景1
*
*
*/
class RollandStage1 :
	public CStage_Rolland
{
public:
	void InitStage();
	
	RollandStage1() { SetStageWidth(RollandStageWidths[1]); };
	~RollandStage1() {};
};

/**
* @class RollandStage2
* @brief "洛兰"场景2
*
*
*/
class RollandStage2 :
	public CStage_Rolland
{
public:
	void InitStage();

	RollandStage2() { SetStageWidth(RollandStageWidths[2]); };
	~RollandStage2() {};

};

/**
* @class RollandStage3
* @brief "洛兰"场景3
*
*
*/
class RollandStage3 :
	public CStage_Rolland
{
public:
	void InitStage();

	RollandStage3() { SetStageWidth(RollandStageWidths[3]); };
	~RollandStage3() {};
};

/**
* @class RollandStage4
* @brief "洛兰"场景4
*
*
*/
class RollandStage4 :
	public CStage_Rolland
{
public:
	void InitStage();

	RollandStage4() { SetStageWidth(RollandStageWidths[4]); };
	~RollandStage4() {};
};

/**
* @class RollandStage5
* @brief "洛兰"场景5
*
*
*/
class RollandStage5 :
	public CStage_Rolland
{
public:
	void InitStage();

	RollandStage5();
	~RollandStage5() {};
};

