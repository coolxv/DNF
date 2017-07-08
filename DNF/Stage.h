#pragma once
#include "Character.h"
#include "Dungeon.h"
using namespace cv;

class COtherObject;
class CMonster;

/** @brief  ���ڵĳ���*/
struct NEXT_STAGE
{
	CStage* top, *bottom, *left, *right;
	NEXT_STAGE() :top(NULL), bottom(NULL), left(NULL), right(NULL) {}
	NEXT_STAGE(CStage* t, CStage* b, CStage* l, CStage* r) :top(t), bottom(b), left(l), right(r) {}
};

/**
 * @class CStage
 * @brief ���������䣩����
 * 
 *
 */
class CStage
{
public:
	static Mat s_Mat_Monster_Hphud, s_Mat_Monster_Hphud_, s_Mat_Monster_Hp[5], s_Mat_Monster_Hp_Mask[5];	/**<  Ѫ����Դ*/
	static Mat s_Mat_BossMonster_Hphud, s_Mat_BossMonster_Hphud_, s_Mat_BossMonster_Hp[5], s_Mat_BossMonster_Hp_Mask[5];	/**<  Ѫ����Դ*/
	static Mat s_Mat_HpNumber[11];	/**<  ����Ѫ����Դ*/
public:
	static const int s_OffsetY = 360;	/**<  ���ƶ���Χ�����Ϸ�����y��ƫ��*/
	static const int s_ViewHeight = 190;	/**<  ��Ϸ����߶�*/
	static const int s_ViewWidth = 640;	/**<  ��Ϸ������*/
public:
	
	/**
	 * @brief ��ʼ������
	 * 
	 * �����า�� ,������Դ�ĳ�ʼ������������� ÿ�ν���ó�����Ҫ����һ��
	 * @return  void  
	 */
	 virtual void InitStage() {};  
	
	/**
	 * @brief �뿪��ǰ�������ã������ͷ���Դ
	 * 
	 * 
	 * @return  void  
	 */
	 virtual void QuitStage() ; 
	CStage() ;
	virtual ~CStage();
	void HandleInput(int input);
	virtual void Render(Mat& mat);
	virtual void Update(CDungeon* dungeon); 

	
	/**
	 * @brief ���ػ���ľ�������
	 * 
	 * 
	 * @return  int  
	 */
	 int GetViewX() { return m_ViewX; };
	
	/**
	 * @brief ���û�������
	 * 
	 * 
	 * @param  int x
	 * @return  void  
	 */
	 void SetViewX(int x);
	
	/**
	 * @brief �������ڳ���
	 * 
	 * 
	 * @param  NEXT_STAGE n	���ڳ���
	 * @return  void  
	 */
	 void SetNextStage(NEXT_STAGE n) { m_NextStage = n; }
	
	/**
	 * @brief ���ص�ǰ���������ڳ���
	 * 
	 * 
	 * @return  NEXT_STAGE  
	 */
	 NEXT_STAGE GetNextStage() { return m_NextStage; }
	
	/**
	 * @brief ���ý�ɫ����ָ��
	 * 
	 * 
	 * @param  CCharacter * p
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* p) { m_Character = p; }
	
	/**
	 * @brief ���õ�ǰ���³����۵���ָ��
	 * 
	 * 
	 * @param  int * p
	 * @return  void  
	 */
	 void SetScorePointer(int* p) {m_DungeonScorePointer = p;}
	
	/**
	 * @brief ��������ָ��
	 * 
	 * 
	 * @param  int add
	 * @return  void  
	 */
	 void AddScore(int add) { (*m_DungeonScorePointer) += add; }

	
	/**
	 * @brief ���ؽ�ɫ����ָ��
	 * 
	 * 
	 * @return  CCharacter*  
	 */
	 CCharacter* GetCharacter() { return m_Character; }

	
	/**
	 * @brief ���س������
	 * 
	 * 
	 * @return  int  
	 */
	 int GetStageWidth() { return m_StageWidth; }
	
	/**
	 * @brief ���ó������
	 * 
	 * 
	 * @param  int width
	 * @return  void  
	 */
	 void SetStageWidth(int width);

	 std::vector<COtherObject*> m_OtherObjects;	/**<  ��ǰ������������Ʒ����*/
	 std::vector<CMonster*> m_Monsters;	/**<  ��ǰ�����ڵ�ȫ������*/
	
	/**
	 * @brief ���ص�ǰ�����Ƿ���boss����
	 * 
	 * 
	 * @return  bool  
	 */
	 bool IsBossRoom() { return m_IsBossRoom; }		
	
	/**
	 * @brief ���ص�ǰ�����Ƿ����������
	 * 
	 * 
	 * @return  bool  
	 */
	 bool IsClearance() { return m_IsClearance; }

	
	/**
	 * @brief ���ص�ǰ��ɫ�������Ĺ�������ָ��
	 * 
	 * 
	 * @return  CMonster*  
	 */
	 CMonster* GetTargetMonster() { return m_TargetMonster; }
	
	/**
	 * @brief ���õ�ǰ��ɫ�������Ĺ�������ָ��
	 * 
	 * 
	 * @param  CMonster * p
	 * @return  void  
	 */
	 void SetTargetMonster(CMonster* p) { m_TargetMonster = p; }
protected:
	
	/**
	 * @brief ���ƹ���Ѫ��
	 * 
	 * 
	 * @param  Mat & mat	����
	 * @param  int hp_cur	��ǰѪ��
	 * @param  int hp_animation	����Ѫ��
	 * @param  int width	���
	 * @param  bool isboss	�Ƿ���boss
	 * @return  void  
	 */
	 void __ShowMonsterHp(Mat& mat, int hp_cur, int hp_animation, int width,bool isboss);
	
	/**
	 * @brief ��srcImage��͸���ĵط���dstImage�ϲ�
	 * 
	 * 
	 * @param  Mat & srcImage	ԭͼƬ
	 * @param  Mat & dstImagePtr	���ͼƬ
	 * @return  cv::Mat	���ش���õ�Mat
	 */
	 Mat MatMergeTransparentImage(Mat& srcImage, Mat& dstImagePtr);
	 Mat m_mat_MidBG, m_mat_MidBG_Mask; /**<  �о���Դ*/
	 Mat m_mat_FarBG, m_mat_FarBG_Mask; /**<  Զ����Դ*/

	 int m_ViewX; /**<  ������Ҫ����ʾ����ʼx*/
	 int m_ViewX_far; /**<  Զ����Ҫ����ʾ����ʼx*/
	 int m_StageWidth;	/**<  ��ǰ�����Ŀ��*/
	 bool m_IsClearance; /**<  ��ǰ�����Ƿ���ͨ��*/
	 bool m_IsBossRoom; /**<  ��ǰ�����Ƿ���boos����*/
	 CCharacter* m_Character = NULL;	/**<  ��ɫ����ָ��*/
	 NEXT_STAGE m_NextStage;	/**<  ���ڵĳ���*/

	 CMonster* m_TargetMonster;	/**<  ��ɫ��ǰ�����Ķ���*/
	 int m_TargetMonsterHp, m_TargetMonsterHp_Animation;	/**<  ��ɫ��ǰ�����Ķ����Ѫ��*/
	 Mat m_Mat_TargetMonsterAvator;	/**<  ��ɫ��ǰ�����Ķ����ͷ��*/
	 String m_TargetMonsterName;	/**<  ��ɫ��ǰ�����Ķ�������*/
	 bool m_isTargetMonsterBoss;	/**<  ��ɫ��ǰ�����Ķ����Ƿ�Ϊboss*/
	 int*  m_DungeonScorePointer;	/**<  ���۵�����ָ��*/
};

