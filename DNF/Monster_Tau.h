#pragma once
#include "Monster.h"
/**
 * @class CMonSter_Tau
 * @brief ţͷ��
 * 
 *
 */
class CMonster_Tau :
	public CMonster
{
public:
	static Mat s_Mat_Body[32], s_Mat_Body_Mask[32], s_Mat_Avator;	/**<  ��Դͼ*/
public:
	
	/**
	* @brief ���캯��
	*
	* ���ù��������ͳ�������ָ��
	* @param  CStage * stage	�������ڳ�������ָ��
	* @param  int x	x����
	* @param  int y	y����
	* @param  int z	z����
	* @return
	*/
	 CMonster_Tau(CStage* stage, int x, int y, int z);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CMonster_Tau();

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
	 * @brief ���ع����ж�����
	 * 
	 * 
	 * @return  Rect  
	 */
	 Rect GetAttackRect();
	
	/**
	 * @brief �����˺�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetDamage();
	
	/**
	 * @brief ���ػ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetArmor();
	
	/**
	 * @brief ����ͷ��
	 * 
	 * 
	 * @return  cv::Mat  
	 */
	 Mat GetAvator() { return s_Mat_Avator; };
	
	/**
	 * @brief ��������
	 * 
	 * 
	 * @return  cv::String  
	 */
	 String GetName() { return String("Lv5 Ngau Tau Monster"); }


	 
	 /**
	  * @brief ������һ��ʹ�ó�ײ���ܵ�ʱ��
	  * 
	  * 
	  * @param  clock_t t
	  * @return  void  
	  */
	  void SetPreHit(clock_t t);
	
	/**
	 * @brief ������һ��ʹ�ó�ײ���ܵ�ʱ��
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreHit() { return m_PreHit; }

	
	/**
	 * @brief ������һ��ʹ�ú�м��ܵ�ʱ��
	 * 
	 * 
	 * @param  clock_t t
	 * @return  void  
	 */
	 void SetPreRoar(clock_t t) { m_PreRoar = t; }
	
	/**
	 * @brief ������һ��ʹ�ú�м��ܵ�ʱ��
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreRoar() { return m_PreRoar; }
private:
	
	/**
	 * @brief ��ʼ��ͼƬ��Դƫ��
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitOffset();
	 Point m_Offset_LeftBottom[32], m_Offset_LeftBottom_Left[32]; /**<  ��ɫ��ӦͼƬ���½�ƫ��*/
	 clock_t m_PreHit; /**<  ��һ��ʹ�ó�ײ���ܵ�ʱ��*/
	 clock_t m_PreRoar; /**<  ��һ��ʹ�ú�е�ʱ��*/
};