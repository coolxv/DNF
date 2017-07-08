#pragma once
#include  "Stage.h"
#include "Dungeon.h"
#include "ObjectBase.h"
#include "Monster.h"
using namespace cv;

/**
 * @class COtherObject
 * @brief 游戏中的其他对象基类
 * 
 *游戏中除去角色，怪物类的其他对象，如树木，门
 */
class COtherObject
	:public CObjectBase
{
public:
	
	/**
	 * @brief 构造
	 * 
	 * 
	 * @return    
	 */
	 COtherObject();
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 virtual ~COtherObject();
	
	/**
	 * @brief 更新状态
	 * 
	 * 
	 * @param  CStage & stage	当前对象所在的场景
	 * @param  CDungeon * dungeon	当前对象所在的地下城
	 * @return  bool  
	 */
	 virtual bool Update(CStage& stage, CDungeon* dungeon) { return true; };

	 /**
	 * @brief 纯虚绘制函数
	 *
	 * 在参数mat上绘制自身
	 * @param  Mat & mat 回调mat
	 * @param  int viewX	当前游戏画面的绝对坐标
	 * @return  void
	 */
	virtual void DoRender(Mat& mat, int viewX) = 0;

	
	/**
	 * @brief 返回当前对象是否需要被销毁
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetComplete() { return m_Complete; }

protected:
	clock_t m_Clock_PreRender;	/**<  返回上一次更新绘制的时间*/
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask; /**<  资源图*/
	bool m_Complete;/**<  生命周期是否结束*/
};



/**
 * @class Gate
 * @brief 门
 * 
 *场景中切换用到的门
 */
class Gate :
	public COtherObject
{
public:
	static Mat s_Mat_Gate0[4][4], s_Mat_Gate0_Mask[4][4];	/**<  4个方向的资源图*/

	/** @brief 门的位置 */
	enum GATE_POSITION
	{
		LEFT_GATE, RIGHT_GATE, TOP_GATE, BOTTOM_GATE
	};

	/** @brief  门的类型*/
	enum GATE_TYPE
	{
		CLOSE_GATE,	/**<  关闭*/
		OPEN_GATE,	/**<  开启*/
		BOOS_GATE,	/**<  boss*/
		NORMAL_GATE	/**<  普通，用于boss门的闪烁效果*/
	};
public:
	
	/**
	 * @brief 门的构造函数
	 * 
	 * 设定门的参数
	 * @param  int position	门的位置
	 * @param  int x	坐标
	 * @param  int y	坐标
	 * @param  CStage *	stage	门所在的场景
	 * @return    
	 */
	 Gate(int position, int x, int y,CStage* stage);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~Gate();
	bool Update(CStage& stage,CDungeon* dungeon);
	void DoRender(Mat& mat,  int viewX);

public:
	clock_t m_Clock_GateTimer;	/**< 上一次靠近门的时间 */
	int m_GateTYpe;	/**<  门的类型*/
	int m_GatePosition;	/**<  门的位置*/
	int m_MatId;/**<  闪烁效果*/
};

/**
 * @class Tree
 * @brief 树
 * 
 *
 */
class Tree :
	public COtherObject
{
public:
	static Mat s_Mat_Tree0[1], s_Mat_Tree0_Mask[1];	/**<  树的资源图*/
	static int s_Tree_SetOffX[1],s_Tree_SetOffY[1];	/**< 树的坐标偏移 */
public:
	
	/**
	 * @brief 树的构造函数
	 * 
	 * 
	 * @param  int x	坐标
	 * @param  int y	坐标
	 * @param  int type	 类型
	 * @return    
	 */
	 Tree(int x, int y,int type);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~Tree();
	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	int m_TreeType;	/**<  树的类型*/
};

/**
 * @class ThrowStone
 * @brief 投掷哥布林扔出去的石头
 * 
 *
 */
class ThrowStone
	:public COtherObject
{
public:
	static Mat s_Mat_ThrowStone[4], s_Mat_ThrowStone_Mask[4];	/**<  资源图*/

	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @param  int x	坐标x
	 * @param  int y	坐标y
	 * @param  int z	坐标z
	 * @param  int dir	运动方向
	 * @param  int power	伤害
	 * @return    
	 */
	 ThrowStone(int x,int y,int z,int dir,int power);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~ThrowStone() {};

	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	int m_Power;	/**<  伤害*/
	int m_MatId;	/**<  绘制的资源图序号*/
	int m_Dir;		/**<  运动方向*/
};

/** @brief  肉块*/
struct _Meat
{
	Point3i Pos;	/**<  起始坐标*/
	Point3i Speed;	/**<  xyz轴的速度*/
	int Type;	/**<  类型*/
	_Meat() {}
	_Meat(Point3i p, Point3i sp, int t) :Pos(p), Speed(sp), Type(t) {}
};

/**
 * @class Meat
 * @brief 怪物死亡肉块
 * 
 *
 */
class Meat
	:public COtherObject
{
public:
	static Mat s_Mat_Meat[2][4], s_Mat_Meat_Mask[2][4];	/**<  资源图*/
	
	/**
	 * @brief 构造函数
	 * 
	 * 
	 * @param  CMonster * monster	怪物的对象指针
	 * @param  int type		肉块的类型
	 * @return	
	 */
	 Meat(CMonster* monster, int type);
	
	/**
	 * @brief 析构
	 * 
	 * 
	 * @return    
	 */
	 ~Meat() {};

	void DoRender(Mat& mat, int viewX);
private:
	std::vector<_Meat> m_Meats;	/**<  肉块容器*/
	int m_MeatType;	/**<  肉块类型*/
	clock_t m_Clock_PreUpdate;	/**<  上一次更新绘制的时间*/
	clock_t m_Clock_Fell;	/**<  肉块全部落地的时间*/
};

