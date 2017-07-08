#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Dungeon.h"
/**
 * @class CHud
 * @brief Ѫ��������ʾ��
 * 
 *
 */
class CHud
{
public:
	CHud();
	~CHud();

	void Render(Mat& mat);
	void Update();
	void HandleInput(char key);
	void HandleMouse(int Event, int x, int y, int flags, void* param);

	
	/**
	 * @brief ��ʼ����Դͼ
	 * 
	 * 
	 * @return  void  
	 */
	 void Initial();
	
	/**
	 * @brief ���ý�ɫ����ָ��
	 * 
	 * 
	 * @param  CCharacter * character ��ɫ����ָ��
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* character);
	
	/**
	 * @brief ���ý�ɫ��ǰ���ڵ��³Ƕ���ָ��
	 * 
	 * 
	 * @param  CDungeon * dungeon ���³Ƕ���ָ��
	 * @return  void  
	 */
	 void SetDungeon(CDungeon* dungeon) { m_Dungeon = dungeon; }

	
	 /**
	 * @brief ��a��b����ϲ�
	 *
	 *
	 * @param  Mat & a
	 * @param  Mat & b
	 * @param  Mat & b_ b���ɰ�
	 * @param  int div ������
	 * @return  void
	 */
	 void __VerticalMergeMat(Mat& a, Mat& b, Mat& b_, int div);
	
	/**
	 * @brief ��������Ѫ��
	 * 
	 * 
	 * @param  Mat & mat ������ͼ
	 * @param  int hp_percentage	��ǰѪ�����ٷֱȣ�
	 * @return  void  
	 */
	 void __ShowHp(Mat& mat,int hp_percentage);
	
	/**
	 * @brief ��������Ѫ������
	 * 
	 * 
	 * @param  Mat & mat ��ͼ
	 * @return  void  
	 */
	 void __ShowHpAnimation(Mat& mat);

	
	 /**
	 * @brief ������������
	 *
	 *
	 * @param  Mat & mat ������ͼ
	 * @param  int hp_percentage	��ǰ�������ٷֱȣ�
	 * @return  void
	 */
	 void __ShowMp(Mat& mat, int mp_percentage);

	 /**
	 * @brief ����������������
	 *
	 *
	 * @param  Mat & mat ��ͼ
	 * @return  void
	 */
	void __ShowMpAnimation(Mat& mat);

private:
	int m_hp_percentage_cur;	/**<  ��ɫѪ���ٷֱ� */
	int m_hp_percentage_animation;	/**<  ��ɫѪ��������ʾ���İٷֱ� */
	int m_mp_percentage_cur;	/**<  ��ɫ����ֵ�ٷֱ� */
	int m_mp_percentage_animation;	/**<  ��ɫ����ֵ������ʾ���İٷֱ� */

	CCharacter* m_Character;	/**<  ��ɫ����ָ�� */
	CDungeon* m_Dungeon;	/**<  ���³Ƕ���ָ�� */

	Mat m_Mat_Hud,m_Mat_Hud_Mask; /**<  ������Դ */
	Mat m_Mat_Hp,m_Mat_Hp_Mask,m_Mat_Hp_w;	/**<  Ѫ����Դ*/
	Mat m_Mat_Mp,m_Mat_Mp_Mask;	/**<  ������Դ */
	Mat m_Mat_EffectA, m_Mat_EffectA_Mask, m_Mat_EffectA_Cool, m_Mat_EffectA_Cool_Mask;	/**<  ����Aͼ��*/
	Mat m_Mat_EffectS, m_Mat_EffectS_Mask, m_Mat_EffectS_Cool, m_Mat_EffectS_Cool_Mask;	/**<  ����Sͼ��*/
	Mat m_Mat_EffectD, m_Mat_EffectD_Mask, m_Mat_EffectD_Cool, m_Mat_EffectD_Cool_Mask;	/**<  ����Dͼ��*/
	Mat m_Mat_EffectZ, m_Mat_EffectZ_Mask, m_Mat_EffectZ_Cool, m_Mat_EffectZ_Cool_Mask;	/**<  ����Zͼ��*/
	Mat m_Mat_EffectMask;

	bool m_Hp_onMouse; /**<  ��ǰ����Ƿ���Ѫ����*/

	int m_RenderCount; /**<  ���ƼƴΣ�������ʾfps */
	int m_fps;	/**<  ƽ��fps */
	clock_t m_Clock_PreRender;	/**< ��һ��ˢ����ʾ��ʱ�� */
};

