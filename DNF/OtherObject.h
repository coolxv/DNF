#pragma once
#include  "Stage.h"
#include "Dungeon.h"
#include "ObjectBase.h"
#include "Monster.h"
using namespace cv;

/**
 * @class COtherObject
 * @brief ��Ϸ�е������������
 * 
 *��Ϸ�г�ȥ��ɫ���������������������ľ����
 */
class COtherObject
	:public CObjectBase
{
public:
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 COtherObject();
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 virtual ~COtherObject();
	
	/**
	 * @brief ����״̬
	 * 
	 * 
	 * @param  CStage & stage	��ǰ�������ڵĳ���
	 * @param  CDungeon * dungeon	��ǰ�������ڵĵ��³�
	 * @return  bool  
	 */
	 virtual bool Update(CStage& stage, CDungeon* dungeon) { return true; };

	 /**
	 * @brief ������ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	virtual void DoRender(Mat& mat, int viewX) = 0;

	
	/**
	 * @brief ���ص�ǰ�����Ƿ���Ҫ������
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetComplete() { return m_Complete; }

protected:
	clock_t m_Clock_PreRender;	/**<  ������һ�θ��»��Ƶ�ʱ��*/
	Mat m_Mat_RenderMat, m_Mat_RenderMat_Mask; /**<  ��Դͼ*/
	bool m_Complete;/**<  ���������Ƿ����*/
};



/**
 * @class Gate
 * @brief ��
 * 
 *�������л��õ�����
 */
class Gate :
	public COtherObject
{
public:
	static Mat s_Mat_Gate0[4][4], s_Mat_Gate0_Mask[4][4];	/**<  4���������Դͼ*/

	/** @brief �ŵ�λ�� */
	enum GATE_POSITION
	{
		LEFT_GATE, RIGHT_GATE, TOP_GATE, BOTTOM_GATE
	};

	/** @brief  �ŵ�����*/
	enum GATE_TYPE
	{
		CLOSE_GATE,	/**<  �ر�*/
		OPEN_GATE,	/**<  ����*/
		BOOS_GATE,	/**<  boss*/
		NORMAL_GATE	/**<  ��ͨ������boss�ŵ���˸Ч��*/
	};
public:
	
	/**
	 * @brief �ŵĹ��캯��
	 * 
	 * �趨�ŵĲ���
	 * @param  int position	�ŵ�λ��
	 * @param  int x	����
	 * @param  int y	����
	 * @param  CStage *	stage	�����ڵĳ���
	 * @return    
	 */
	 Gate(int position, int x, int y,CStage* stage);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~Gate();
	bool Update(CStage& stage,CDungeon* dungeon);
	void DoRender(Mat& mat,  int viewX);

public:
	clock_t m_Clock_GateTimer;	/**< ��һ�ο����ŵ�ʱ�� */
	int m_GateTYpe;	/**<  �ŵ�����*/
	int m_GatePosition;	/**<  �ŵ�λ��*/
	int m_MatId;/**<  ��˸Ч��*/
};

/**
 * @class Tree
 * @brief ��
 * 
 *
 */
class Tree :
	public COtherObject
{
public:
	static Mat s_Mat_Tree0[1], s_Mat_Tree0_Mask[1];	/**<  ������Դͼ*/
	static int s_Tree_SetOffX[1],s_Tree_SetOffY[1];	/**< ��������ƫ�� */
public:
	
	/**
	 * @brief ���Ĺ��캯��
	 * 
	 * 
	 * @param  int x	����
	 * @param  int y	����
	 * @param  int type	 ����
	 * @return    
	 */
	 Tree(int x, int y,int type);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~Tree();
	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	int m_TreeType;	/**<  ��������*/
};

/**
 * @class ThrowStone
 * @brief Ͷ���粼���ӳ�ȥ��ʯͷ
 * 
 *
 */
class ThrowStone
	:public COtherObject
{
public:
	static Mat s_Mat_ThrowStone[4], s_Mat_ThrowStone_Mask[4];	/**<  ��Դͼ*/

	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @param  int x	����x
	 * @param  int y	����y
	 * @param  int z	����z
	 * @param  int dir	�˶�����
	 * @param  int power	�˺�
	 * @return    
	 */
	 ThrowStone(int x,int y,int z,int dir,int power);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~ThrowStone() {};

	bool Update(CStage& stage, CDungeon* dungeon);
	void DoRender(Mat& mat, int viewX);

private:
	int m_Power;	/**<  �˺�*/
	int m_MatId;	/**<  ���Ƶ���Դͼ���*/
	int m_Dir;		/**<  �˶�����*/
};

/** @brief  ���*/
struct _Meat
{
	Point3i Pos;	/**<  ��ʼ����*/
	Point3i Speed;	/**<  xyz����ٶ�*/
	int Type;	/**<  ����*/
	_Meat() {}
	_Meat(Point3i p, Point3i sp, int t) :Pos(p), Speed(sp), Type(t) {}
};

/**
 * @class Meat
 * @brief �����������
 * 
 *
 */
class Meat
	:public COtherObject
{
public:
	static Mat s_Mat_Meat[2][4], s_Mat_Meat_Mask[2][4];	/**<  ��Դͼ*/
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @param  CMonster * monster	����Ķ���ָ��
	 * @param  int type		��������
	 * @return	
	 */
	 Meat(CMonster* monster, int type);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~Meat() {};

	void DoRender(Mat& mat, int viewX);
private:
	std::vector<_Meat> m_Meats;	/**<  �������*/
	int m_MeatType;	/**<  �������*/
	clock_t m_Clock_PreUpdate;	/**<  ��һ�θ��»��Ƶ�ʱ��*/
	clock_t m_Clock_Fell;	/**<  ���ȫ����ص�ʱ��*/
};

