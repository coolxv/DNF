#pragma once
#include "ObjectBase.h"
#include "AnimationEffect.h"

/** @brief  ��ɫ��Դͼ���� */
#define BODYIMGS 222

using namespace cv;
class CCharacterState;
class CGame;

/**
 * @class CCharacter
 * @brief ������
 * 
 *��ɫ�ĸ������ԣ�����
 */
class CCharacter
	:public CObjectBase
{
private:
	int m_HP; /**<  ��ǰ������ֵ */
	int m_MP; /**<  ��ǰ�ķ���ֵ */
	bool m_Dead;	/**<  ��ɫ�Ƿ����� */
	int m_MoveSpeed; /**<  �ƶ��ٶ� */
	int m_StageWidth;  /**<  ��ǰ���ڳ����������	 */
	bool m_IsAttacking;		/**<  ��ɫ��ǰ�Ƿ��ڹ��� */
	bool m_isBackJumping;	/**<  �Ƿ��ں��� */
	clock_t m_PreReplyHpMp;	/**<  ��һ�λظ���ʱ�� */
	CCharacterState* m_State;	/**<  ��ɫ��ǰ��״̬ */
	int m_ViewWidth, m_ViewHeight, m_OffsetY;	 /**<  */
	Mat m_Mat_Body[222], m_Mat_Body_Mask[222];	/**<  ��ɫ��Դͼ */
	Mat m_Mat_LBody[222], m_Mat_LBody_Mask[222];	/**<  ��ɫ��Դͼ */
	std::vector<CAnimationEffect*>* m_Vector_AnimationEffects; /**<  ������Ч���� */
	Point m_Offset_LeftBottom[223], m_Offset_LeftBottom_Left[223]; /**<  ��ԴͼƯ���� */
	clock_t m_PreEffect_Z, m_PreEffect_A, m_PreEffect_S, m_PreEffect_D;	/**<  ��һ��ʹ�ü��ܵ�ʱ�� */
public:
	
	/**
	 * @brief ���캯��
	 * 
	 * 
	 * @return    
	 */
	 CCharacter();
	
	/**
	 * @brief ����
	 * 
	 * 
	 * @return    
	 */
	 ~CCharacter();
	
	/**
	 * @brief ���ؽ�ɫ��ǰ��״̬
	 * 
	 * 
	 * @return  CCharacterState*  
	 */
	 CCharacterState* GetCurState();;
	
	/**
	 * @brief �л�״̬
	 * 
	 * 
	 * @param  CCharacterState * p ��Ҫ�л���״̬
	 * @return  void  
	 */
	 void SetState(CCharacterState* p);
	
	/**
	 * @brief ���ö�����������
	 * 
	 * ���ڽ�ɫ���ܶ���
	 * @param  std::vector<CAnimationEffect * > * v ����ָ��
	 * @return  void  
	 */
	 void SetAnimationEffectsVector(std::vector<CAnimationEffect*>* v);
	
	 /**
	 * @brief ���ƺ���
	 *
	 * �ڲ���mat�ϻ�������
	 * @param  Mat & mat �ص�mat
	 * @param  int viewX	��ǰ��Ϸ����ľ�������
	 * @return  void
	 */
	 void DoRender(Mat& mat,int viewX);
	
	/**
	 * @brief ������������¼�
	 * 
	 * 
	 * @param  int input	��ֵ
	 * @return  void  
	 */
	 void DoHandleInput(int input);
	
	/**
	 * @brief ���½�ɫ״̬����
	 * 
	 * 
	 * @return  void  
	 */
	 void UpdateState();
	
	/**
	 * @brief ��ɫ�ƶ�
	 * 
	 * 
	 * @param  int dir �ƶ�����
	 * @param  double multiple	�ƶ����루�ƶ��ٶȵ�multiple����
	 * @return  void  
	 */
	 void Move(int dir, double multiple = 1.0);
	
	/**
	 * @brief �����˺�ֵ
	 * 
	 * 
	 * @param  int effect ����
	 * @param  bool & crit	�Ƿ񱩻��ص�����
	 * @return  int  �����˺�ֵ
	 */
	 int GetDamage(int effect, bool& crit);
	
	/**
	 * @brief ���ؽ�ɫ�Ļ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetArmor();
	
	/**
	 * @brief ���ض�����������ָ��
	 * 
	 * 
	 * @return  std::vector<CAnimationEffect*>*  
	 */
	 std::vector<CAnimationEffect*>* GetAnimationEffects();

	static const int s_JumpN = 27; /**< ��Ծ�� */
	static const int s_Gravity = -1;		/**<  ���� */
private:
	
	/**
	 * @brief ��ʼ����Դ
	 * 
	 * 
	 * @return  void  
	 */
	 void __InitRec();
public://get/set
	
	/**
	 * @brief ���ؽ�ɫ�Ƿ�����
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetDead() { return m_Dead; }
	
	/**
	 * @brief ���ؽ�ɫ����ֵ
	 * 
	 * 
	 * @return  int  
	 */
	 int GetHp() { return m_HP; };
	
	/**
	 * @brief ���ؽ�ɫ����ֵ
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMp() { return m_MP; }
	
	/**
	 * @brief ���ؽ�ɫ������
	 * 
	 * 
	 * @return  int  
	 */
	 int GetGravity() { return m_Gravity; };
	
	/**
	 * @brief ���ؽ�ɫ��z���ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetZSpeed() { return m_ZSpeed; };
	
	/**
	 * @brief ���ؽ�ɫ����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetOrientation() { return m_Orientation; };
	
	/**
	 * @brief ���ؽ�ɫ�ƶ�����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMoveDirection() { return m_MoveDirection; };
	
	/**
	 * @brief ���ؽ�ɫ�ƶ��ٶ�
	 * 
	 * 
	 * @return  int  
	 */
	 int GetMovespeed() { return m_MoveSpeed; };
	
	/**
	 * @brief ���ؽ�ɫ��Ծ����
	 * 
	 * 
	 * @return  int  
	 */
	 int GetJumpDir() { return m_JumpDir; };
	
	/**
	 * @brief ���ؽ�ɫ������ײ����
	 * 
	 * 
	 * @return  Rect  
	 */
	 Rect GetAttackRect();
	
	/**
	 * @brief ���ؽ�ɫ�Ƿ��ڹ���
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetAttacking() { return m_IsAttacking; };
	
	/**
	 * @brief ���ؽ�ɫ�Ƿ��ں���
	 * 
	 * 
	 * @return  bool  
	 */
	 bool GetBackJumping() { return m_isBackJumping; }
	
	/**
	 * @brief ���ؽ�ɫ��ǰʹ�õļ���
	 * 
	 * 
	 * @return  int  
	 */
	 int GetCurEffect(); //��ȡ��ɫ��ǰʹ�õļ���
	
	/**
	 * @brief ������һ��ʹ��A���ܵ�ʱ��
	 * 
	 * 
	 * @return  clock_t  
	 */
	 clock_t GetPreEffectA() { return m_PreEffect_A; }

	 /**
	 * @brief ������һ��ʹ��S���ܵ�ʱ��
	 *
	 *
	 * @return  clock_t
	 */
	clock_t GetPreEffectS() { return m_PreEffect_S; }

	/**
	* @brief ������һ��ʹ��D���ܵ�ʱ��
	*
	*
	* @return  clock_t
	*/
	clock_t GetPreEffectD() { return m_PreEffect_D; }

	/**
	* @brief ������һ��ʹ��Z���ܵ�ʱ��
	*
	*
	* @return  clock_t
	*/
	clock_t GetPreEffectZ() { return m_PreEffect_Z; }

	/**
	 * @brief ������һ��ʹ��Z���ܵ�ʱ��
	 * 
	 * 
	 * @param  clock_t a
	 * @return  void  
	 */
	 void SetPreEffectA(clock_t a) { m_PreEffect_A = a; }

	 /**
	 * @brief ������һ��ʹ��S���ܵ�ʱ��
	 *
	 *
	 * @param  clock_t a
	 * @return  void
	 */
	void SetPreEffectS(clock_t s) { m_PreEffect_S = s; }

	/**
	* @brief ������һ��ʹ��D���ܵ�ʱ��
	*
	*
	* @param  clock_t s
	* @return  void
	*/
	void SetPreEffectD(clock_t d) { m_PreEffect_D = d; }

	/**
	* @brief ������һ��ʹ��Z���ܵ�ʱ��
	*
	*
	* @param  clock_t d
	* @return  void
	*/
	void SetPreEffectZ(clock_t z) { m_PreEffect_Z = z; }

	/**
	* @brief ������һ��ʹ�ú�����ʱ��
	*
	*
	* @param  clock_t z
	* @return  void
	*/
	void SetIsBackJumpint(bool is) { m_isBackJumping = is; }

	/**
	 * @brief ���ý�ɫ��ǰ�Ƿ��ڹ���
	 * 
	 * 
	 * @param  bool is
	 * @return  void  
	 */
	 void SetAttacking(bool is) { m_IsAttacking = is; };

	/**
	* @brief ���ý�ɫ������ֵ
	*
	*
	* @param  int gravity ����
	* @return  void
	*/
	void SetGravity(int gravity) { m_Gravity = gravity; };

	/**
	 * @brief ���ý�ɫ��z���ٶ�
	 * 
	 * 
	 * @param  int speed
	 * @return  void  
	 */
	 void SetZSpeed(int speed) { m_ZSpeed = speed; };
	
	/**
	 * @brief ���ý�ɫ���ƶ��ٶ�
	 * 
	 * 
	 * @param  int speed
	 * @return  void  
	 */
	 void SetMovespeed(int speed) { m_MoveSpeed = speed; };
	
	/**
	 * @brief ���ý�ɫ����Ծ����
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetJumpDir(int dir) { m_JumpDir = dir; };
	
	/**
	 * @brief ���ý�ɫ���ƶ�����
	 * 
	 * 
	 * @param  int dir
	 * @return  void  
	 */
	 void SetMoveDirection(int dir);
	
	/**
	 * @brief ���ý�ɫ���ڳ����Ŀ��
	 * 
	 * 
	 * @param  int width
	 * @return  void  
	 */
	 void SetStageWidth(int width) { m_StageWidth = width; }
	
	/**
	 * @brief ���ý�ɫ�����ڻ���Ĳ���
	 * 
	 * 
	 * @param  int width ���
	 * @param  int height	�߶�
	 * @param  int offsety	y��ƫ��
	 * @return  void  
	 */
	 void SetViewSize(int width, int height, int offsety) { m_ViewWidth = width; m_ViewHeight = height; m_OffsetY = offsety; }
	
	/**
	 * @brief ���ý�ɫ�Ƿ�����
	 * 
	 * 
	 * @param  bool is
	 * @return  void  
	 */
	 void SetDead(bool is) { m_Dead = is; }
	
	/**
	 * @brief ���ý�ɫx����
	 * 
	 * 
	 * @param  int x
	 * @return  bool  
	 */
	 bool SetX(int x);
	
	/**
	 * @brief ���ý�ɫy����
	 * 
	 * 
	 * @param  int y
	 * @return  bool  
	 */
	 bool SetY(int y);
	
	/**
	 * @brief ���ý�ɫz����
	 * 
	 * 
	 * @param  int z
	 * @return  bool  
	 */
	 bool SetZ(int z);
	
	/**
	 * @brief ���ý�ɫ����ֵ
	 * 
	 * 
	 * @param  int hp
	 * @return  void  
	 */
	 void SetHp(int hp);
	
	/**
	 * @brief ���ý�ɫ����ֵ
	 * 
	 * 
	 * @param  int mp
	 * @return  void  
	 */
	 void SetMp(int mp);
};

