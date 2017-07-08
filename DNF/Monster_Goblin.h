#pragma once
#include "Monster.h"

/**
 * @class CMonster_Goblin
 * @brief �粼��
 * 
 *
 */
class CMonster_Goblin :
	public CMonster
{
public:
	static Mat s_Mat_Body[17],s_Mat_Body_Mask[17] , s_Mat_Avator; /**<  ��Դͼ */
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
	 CMonster_Goblin(CStage* stage, int x, int y, int z);
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CMonster_Goblin();

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
	 * @brief ���ع����ж�����
	 * 
	 * 
	 * @return  Rect  
	 */
	 Rect GetAttackRect();
	
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
	 String GetName() { return String("Lv1 Goblin"); }
private:
	
	/**
	 * @brief ����ͼƬ��ԴƯ��
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitOffset();
	 Point m_Offset_LeftBottom[17], m_Offset_LeftBottom_Left[17]; /**<  ��ɫ��ӦͼƬ���½�ƫ��*/
};

