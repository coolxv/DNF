#pragma once
#include "stdafx.h"
#include "Character.h"
class CStage;

/**
 * @class CDungeon
 * @brief ���³ǻ���
 * 
 *
 */
class CDungeon
{
public:
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @return    
	 */
	 CDungeon();
	
	/**
	 * @brief ��������
	 * 
	 * �ͷŵ��³ǵ����г���
	 * @return    
	 */
	 virtual ~CDungeon();
	
	/**
	 * @brief ��������¼�
	 * 
	 * 
	 * @param  int input	��ֵ
	 * @return  void  
	 */
	 virtual void DoHandleInput(int input);
	
	/**
	 * @brief ���µ��³�״̬
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void Update();
	 
	 /**
	  * @brief ���³ǵĻ���
	  * 
	  * ��mat�ϻ���
	  * @param  Mat & mat	���Ƶ�ͼ
	  * @return  void  
	  */
	  virtual void DoRender(Mat& mat) {};
	
	/**
	 * @brief ��ʼ�����³�
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void DoInitDungeon() {};

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
	 virtual void HandleMouse(int Event, int x, int y, int flags, void* param) {};
	
	/**
	 * @brief ���ػ����������
	 * 
	 * 
	 * @return  int  
	 */
	 virtual int GetViewX();

	
	/**
	 * @brief �л�����
	 * 
	 * ���ڵ��³��г�������л�
	 * @param  CStage * stage
	 * @return  void  
	 */
	 void SwitchStage(CStage* stage);
	
	/**
	 * @brief ���ý�ɫ����ָ��
	 * 
	 * 
	 * @param  CCharacter * character
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* character) { m_Character = character; };
	
	/**
	 * @brief ��ȡ��ǰ��������ָ��
	 * 
	 * 
	 * @return  CStage*  
	 */
	 CStage* GetCurStage() { return m_CurStage; }

	
	/**
	 * @brief ���ص�ǰ���³��Ƿ�Ҫ�˳�
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetIsQuit() { return m_Quit; }
	
	/**
	 * @brief ���õ�ǰ���³��Ƿ�Ҫ�˳�
	 * 
	 * 
	 * @param  bool q
	 * @return  void  
	 */
	 void SetQuit(bool q) { m_Quit = q; }
	
	/**
	 * @brief ���õ�ǰ���³��˳�����Ҫ�л��ĵ��³Ƕ���
	 * 
	 * 
	 * @return  CDungeon*  
	 */
	 CDungeon* GetNextDungeon() { return m_NextDungeon; };
	
	/**
	 * @brief ���ص�ǰ���³��˳�����Ҫ�л��ĵ��³Ƕ���
	 * 
	 * 
	 * @param  CDungeon * next
	 * @return  void  
	 */
	 void SetNextDungeon(CDungeon* next) { m_NextDungeon = next; }

	
	/**
	 * @brief �������۵���
	 * 
	 * 
	 * @param  int add
	 * @return  void  
	 */
	 void AddScore(int add) { m_Score += add; }
protected:
	static Mat s_Mat_DungeonLoading; /**<  ���³Ǽ��ؽ�����Դͼ */
	CCharacter* m_Character = NULL;	/**<  ���Ƕ���ָ�� */
	CStage* m_CurStage = NULL;	/**<  ��ǰ��������ָ�� */
	std::vector<CStage*> m_Stages; /**<  ��ǰ���³ǵĳ������� */
	bool m_Quit = false; /**< ��ǰ���³��Ƿ���Ҫ�˳�������Game�л����� */
	bool m_IsClearance; /**<  �Ƿ���ͨ�� */
	CDungeon* m_NextDungeon=NULL;	/**<  ��ǰ���³��˳���Game��Ҫ�л�����һ�����³Ƕ��� */
	clock_t m_Clock_Start;	/**<  ���뵱ǰ���³ǵ�ʱ�� */
	clock_t m_Clock_PreHandleInput;	/**<  ��һ�δ������¼���ʱ�� */
	int m_Score;	/**<  ��ǰ���³ǵ����۵��� */
	bool m_GameOver;	/**<  ��ɫ�Ƿ���������ǰ���³ǽ��� */
	bool m_ShowMinMap;	/**<  �Ƿ���ʾ���Ͻ�С��ͼ */
	
	/**
	 * @brief �ϲ�����Mat
	 * 
	 * ��MatB�ϲ���MatA��
	 * @param  Mat & a	MatA
	 * @param  Mat & b	MatB
	 * @param  int x	MatB���Ͻ�λ��MatA������
	 * @param  int y	MatB���Ͻ�λ��MatY������
	 * @param  int alpha	���Ե�͸������ֵ
	 * @return  void  
	 */
	 void _Merge(Mat& a, Mat& b, int x, int y, int alpha);
};
