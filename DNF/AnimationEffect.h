#pragma once
#include "stdafx.h"
class CDungeon;

/**
 * @class CAnimationEffect
 * @brief ��Ϸ�����еĶ���Ч��
 * 
 *
 */
class CAnimationEffect
{
public:
	CAnimationEffect();
	virtual ~CAnimationEffect();

	/**
	 * @brief ���ƺ���
	 * 
	 * �ڲ���mat�ϻ�������������ƺ����������า��ʵ��
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void  
	 */
	 virtual void DoRender(Mat& mat, int viewX) = 0;

	/**
	 * @brief ���ص�ǰ�����Ƿ��ѽ���
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetComplete();
	
	/**
	 * @brief ���ص�����
	 * 
	 * 
	 * @param  int Event	����¼�����
	 * @param  int x	���x����
	 * @param  int y	���y����
	 * @param  int flags	�����ק�¼���������������¼�
	 * @param  void * param	
	 * @return  void  
	 */
	 virtual void onMouse(int Event, int x, int y, int flags, void* param) {};
protected:
	bool m_Complete;	/**<  ��ǵ�ǰ�����Ƿ��ѽ��� */
	int m_MatId;	/**<  ��һ֡��Ҫ���Ƶ�ͼƬ��� */
	clock_t m_Clock_Update;	/**<  ��һ�θ��µ�ʱ�� */
};

/**
 * @class CPhysicalAttackAnimation
 * @brief ��ɫ������Ч����
 * 
 *
 */
class CPhysicalAttackAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_Slash[3][3], s_Mat_Slash_Mask[3][3];	/**<  ������Ч��Դͼ */
	
	/**
	 * @brief ���캯��
	 * 
	 * ָ�����������
	 * @param  Point3i point	������ʾ�ľ�������
	 * @param  int type		������Ч�����ͣ�0~3
	 * @return
	 */
	 CPhysicalAttackAnimation(Point3i point,int type);
	
	/**
	 * @brief ��������
	 * 
	 * 
	 * @return    
	 */
	 ~CPhysicalAttackAnimation();
	
	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);
private:
	Point3d m_Point_Coor;	/**<  ������ʾ�ľ������� */
	int m_Type;	/**<  ��������������*/
};

/**
 * @class CAwakeDEffectAnimation
 * @brief D���ܵĶ�����Ч
 * 
 *
 */
class CAwakeDEffectAnimation
	:public CAnimationEffect
{
public:
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @param  int pos	��ʾ�ķ���DIR_LEFT��DIR_RIGHT
	 * @return    
	 */
	 CAwakeDEffectAnimation(int pos);
	
	/**
	 * @brief ��������
	 * 
	 * 
	 * @return    
	 */
	 ~CAwakeDEffectAnimation() {};
	
	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);
private:
	static Mat s_Mat_Draw[30];	/**< ��Դͼ */
	Mat mask;	/**<  ����ʵ�ֶ������ɰ� */
	int m_pos;	/**<  ������ʾ�ķ��� */
};

/**
 * @class CAwakeSEffectAnimation
 * @brief S���ܵĶ�����Ч
 * 
 *
 */
class CAwakeSEffectAnimation
	:public CAnimationEffect
{
public:
	
	/**
	* @brief ���캯��
	*
	*
	* @param  int pos	��ʾ�ķ���DIR_LEFT��DIR_RIGHT
	* @return
	*/
	 CAwakeSEffectAnimation(int pos);
	
	/**
	 * @brief ��������
	 * 
	 * 
	 * @return    
	 */
	 ~CAwakeSEffectAnimation() {};
	
	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	 void DoRender(Mat& mat, int viewX);

private:
	static Mat s_Mat_DrawS[35];	/**<  ��Դͼ */
	Mat mask;	/**<  ����ʵ�ֶ������ɰ� */
	int m_pos;	 /**<  ������ʾ�ķ��� */
};

/**
 * @class CNumberAnimation
 * @brief �˺����ֶ�����Ч
 * 
 *
 */
class CNumberAnimation
	:public CAnimationEffect
{
public:
	
	/**
	 * @brief ���캯��
	 * 
	 * ָ�����֣�λ�ã���ʽ
	 * @param  long long num	Ҫ��ʾ������
	 * @param  Point3i p	���ֵľ�����ά����
	 * @param  int style	���ֵ���ʽ
	 * @return    
	 */
	 CNumberAnimation(long long num,Point3i p,int style);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CNumberAnimation() {};
	
	/**
	* @brief ���ƺ���
	*
	* �ڲ���mat�ϻ�������
	* @param  Mat & mat �ص�mat
	* @param  int viewX	��ǰ��Ϸ����ľ�������
	* @return  void
	*/
	 void DoRender(Mat& mat, int viewX);
private:
	static Mat s_Mat_Number[3][10];	/**<  ��Դͼ */
	int m_StayTime;	/**<  �˺�������Ҫͣ��ʱ�� */
	int m_NumStyle;	/**<  ������������ 0~3 */
	int m_Zspeed;	/**< ���� */
	clock_t m_Clock_stay;	/**< �˺�����ͣ����ʱ */
	Point3i m_Pos;	/**<  ������ʼλ�� */
	Point3i m_CurPos;	/**<  ��ǰ������λ�� */
	int m_length;	/**<  ���ֵ�λ�� */
	std::vector<int> m_v_num;	/**< �洢ÿһλ���� */
};

/**
 * @class CResultAnimation
 * @brief ͨ�ؽ�����涯��
 * 
 *
 */
class CResultAnimation
	:public CAnimationEffect
{
public:
	static Mat s_Mat_panel,s_Mat_time_text,s_Mat_score_text1, s_Mat_score_text2, s_Mat_score_text3,s_Mat_exp_text;	/**< ��Դͼ */
	static Mat s_Mat_min, s_Mat_sec;	/**< ��Դͼ */
	static Mat s_Mat_Number[10],s_Mat_ScoreRank[9]; /**< ��Դͼ */
	static Mat s_Mat_SelectBG,s_Mat_Return[2],s_Mat_Other[2],s_Mat_Continue[2];	/**< ��Դͼ */
	
	/**
	 * @brief ���㶯�����캯��
	 * 
	 * ָ�������������в���
	 * @param  int score	���۵���
	 * @param  int score_rank	���۵ȼ�
	 * @param  int exp	��þ���
	 * @param  int min	ͨ�����÷���
	 * @param  int sec	ͨ����������
	 * @param  int lsec	ͨ����������
	 * @param  int min_record	ͨ�ؼ�¼������
	 * @param  int sec_record	ͨ�ؼ�¼����
	 * @param  int lsec_record	ͨ�ؼ�¼������
	 * @param  CDungeon * cur_dungeon	��ǰ��������ָ��
	 * @return    
	 */
	 CResultAnimation(int score,int score_rank,int exp,int min,int sec,int lsec
		,int min_record,int sec_record,int lsec_record,CDungeon* cur_dungeon);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CResultAnimation();

	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	void DoRender(Mat& mat, int viewX);

	/**
	* @brief ���ص�����
	*
	*
	* @param  int Event	����¼�����
	* @param  int x	���x����
	* @param  int y	���y����
	* @param  int flags	�����ק�¼���������������¼�
	* @param  void * param
	* @return  void
	*/
	void onMouse(int Event, int x, int y, int flags, void* param);
private:
	/** @brief ��ǰ���ѡ�е�ѡ�� */
	enum __SELECT
	{
		RETURN,	/**< ���س��� */
		CONTINUE,	/**<  �ٴ���ս */
		OTHERDUNGEON,	/**<  ѡ���������³� */
		NONE	/**<  δѡ���κ�ѡ�� */
	};
	
	/**
	 * @brief �ϲ�����Mat
	 * 
	 * 
	 * @param  Mat & a	Mata
	 * @param  Mat & b	Matb
	 * @param  int x b�ϲ���a�����Ͻ�����x
	 * @param  int y	b�ϲ���a�����Ͻ�����y
	 * @param  int h	��Ҫ���Ե�͸����
	 * @return  void  
	 */
	 void __Merge(Mat& a, Mat& b, int x, int y, int h);
	
	/**
	 * @brief ��ʾ����
	 * 
	 * ������ʾ���۵������������ֵ
	 * @param  Mat & bg	������ͼ
	 * @param  int x	�������x
	 * @param  int y	�������y
	 * @param  int num		��Ҫ��ʾ������
	 * @return  void  
	 */
	 void __ShowNumber(Mat& bg, int x, int y, int num);
	
	/**
	 * @brief	��ʾʱ��
	 * 
	 * ������ʾͨ��ʱ�䣬ͨ�ؼ�¼ʱ��
	 * @param  Mat & bg	������ͼ
	 * @param  int x	�������x
	 * @param  int y	�������y
	 * @param  int min	��
	 * @param  int sec	��
	 * @param  int lsec	����
	 * @return  void  
	 */
	 void __ShowTime(Mat& bg, int x, int y, int min, int sec, int lsec);
	 int m_Score;	/**<  ���۵��� */
	 int m_Score_Rank;	/**<  ���۵ȼ� */
	 int m_Exp;	/**<  ���� */
	 int m_Min, m_Sec, m_LSec;		/**< ͨ��ʱ�� */
	 int m_Min_Record, m_Sec_Record, m_LSec_Record;	/**<  ͨ�ؼ�¼ */
	 bool m_IsSelecting; /**< ��ǰ�Ƿ����ѡ�� */
	 int m_selected;	/**<  ��ǰѡ���ѡ�� */
	 Rect m_rect_return,m_rect_other,m_rect_continue;	/**<  ѡ���λ���ж����� */
	 CDungeon* m_CurDungeon;	/**<  ��ǰ���ڵ��³ǵĶ���ָ�� */
	 clock_t m_StartTime;	/**<  ������ʼʱ�� */
};

/**
 * @class CGameOverAnimation
 * @brief ��ɫ��������ʱ����
 * 
 *	�Ե���ʱ����ʽ
 */
class CGameOverAnimation
	:public CAnimationEffect
{

public:
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @param  CDungeon * dungeon	��ǰ���ڵ��³ǵĶ���ָ��
	 * @return    
	 */
	 CGameOverAnimation(CDungeon* dungeon);
	
	/**
	 * @brief ��������
	 * 
	 * 
	 * @return    
	 */
	 ~CGameOverAnimation() {};

	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	void DoRender(Mat& mat, int viewX);
private:
	Mat m_Mat_Number[10],m_Mat_Number_Mask[10];		/**<  ��Դͼ */
	clock_t m_AnimationStart;	/**< ������ʼʱ�� */
	CDungeon* m_Dungeon;	/**< ��ǰ���ڵ��³ǵĶ���ָ�� */
};