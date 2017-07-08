#pragma once
#include "Character.h"
#include "Dungeon.h"
using namespace cv;

class COtherObject;
class CMonster;

/** @brief  相邻的场景*/
struct NEXT_STAGE
{
	CStage* top, *bottom, *left, *right;
	NEXT_STAGE() :top(NULL), bottom(NULL), left(NULL), right(NULL) {}
	NEXT_STAGE(CStage* t, CStage* b, CStage* l, CStage* r) :top(t), bottom(b), left(l), right(r) {}
};

/**
 * @class CStage
 * @brief 场景（房间）基类
 * 
 *
 */
class CStage
{
public:
	static Mat s_Mat_Monster_Hphud, s_Mat_Monster_Hphud_, s_Mat_Monster_Hp[5], s_Mat_Monster_Hp_Mask[5];	/**<  血条资源*/
	static Mat s_Mat_BossMonster_Hphud, s_Mat_BossMonster_Hphud_, s_Mat_BossMonster_Hp[5], s_Mat_BossMonster_Hp_Mask[5];	/**<  血条资源*/
	static Mat s_Mat_HpNumber[11];	/**<  怪物血条资源*/
public:
	static const int s_OffsetY = 360;	/**<  可移动范围相对游戏画面的y轴偏移*/
	static const int s_ViewHeight = 190;	/**<  游戏画面高度*/
	static const int s_ViewWidth = 640;	/**<  游戏画面宽度*/
public:
	
	/**
	 * @brief 初始化场景
	 * 
	 * 由子类覆盖 ,进行资源的初始化和物体的载入 每次进入该场景需要调用一次
	 * @return  void  
	 */
	 virtual void InitStage() {};  
	
	/**
	 * @brief 离开当前场景调用，用于释放资源
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
	 * @brief 返回画面的绝对坐标
	 * 
	 * 
	 * @return  int  
	 */
	 int GetViewX() { return m_ViewX; };
	
	/**
	 * @brief 设置画面坐标
	 * 
	 * 
	 * @param  int x
	 * @return  void  
	 */
	 void SetViewX(int x);
	
	/**
	 * @brief 设置相邻场景
	 * 
	 * 
	 * @param  NEXT_STAGE n	相邻场景
	 * @return  void  
	 */
	 void SetNextStage(NEXT_STAGE n) { m_NextStage = n; }
	
	/**
	 * @brief 返回当前场景的相邻场景
	 * 
	 * 
	 * @return  NEXT_STAGE  
	 */
	 NEXT_STAGE GetNextStage() { return m_NextStage; }
	
	/**
	 * @brief 设置角色对象指针
	 * 
	 * 
	 * @param  CCharacter * p
	 * @return  void  
	 */
	 void SetCharacter(CCharacter* p) { m_Character = p; }
	
	/**
	 * @brief 设置当前地下城评价点数指针
	 * 
	 * 
	 * @param  int * p
	 * @return  void  
	 */
	 void SetScorePointer(int* p) {m_DungeonScorePointer = p;}
	
	/**
	 * @brief 增加评价指数
	 * 
	 * 
	 * @param  int add
	 * @return  void  
	 */
	 void AddScore(int add) { (*m_DungeonScorePointer) += add; }

	
	/**
	 * @brief 返回角色对象指针
	 * 
	 * 
	 * @return  CCharacter*  
	 */
	 CCharacter* GetCharacter() { return m_Character; }

	
	/**
	 * @brief 返回场景宽度
	 * 
	 * 
	 * @return  int  
	 */
	 int GetStageWidth() { return m_StageWidth; }
	
	/**
	 * @brief 设置场景宽度
	 * 
	 * 
	 * @param  int width
	 * @return  void  
	 */
	 void SetStageWidth(int width);

	 std::vector<COtherObject*> m_OtherObjects;	/**<  当前场景的其他物品容器*/
	 std::vector<CMonster*> m_Monsters;	/**<  当前场景内的全部怪物*/
	
	/**
	 * @brief 返回当前场景是否是boss场景
	 * 
	 * 
	 * @return  bool  
	 */
	 bool IsBossRoom() { return m_IsBossRoom; }		
	
	/**
	 * @brief 返回当前场景是否已清理完成
	 * 
	 * 
	 * @return  bool  
	 */
	 bool IsClearance() { return m_IsClearance; }

	
	/**
	 * @brief 返回当前角色所攻击的怪物对象的指针
	 * 
	 * 
	 * @return  CMonster*  
	 */
	 CMonster* GetTargetMonster() { return m_TargetMonster; }
	
	/**
	 * @brief 设置当前角色所攻击的怪物对象的指针
	 * 
	 * 
	 * @param  CMonster * p
	 * @return  void  
	 */
	 void SetTargetMonster(CMonster* p) { m_TargetMonster = p; }
protected:
	
	/**
	 * @brief 绘制怪物血条
	 * 
	 * 
	 * @param  Mat & mat	背景
	 * @param  int hp_cur	当前血量
	 * @param  int hp_animation	动画血量
	 * @param  int width	宽度
	 * @param  bool isboss	是否是boss
	 * @return  void  
	 */
	 void __ShowMonsterHp(Mat& mat, int hp_cur, int hp_animation, int width,bool isboss);
	
	/**
	 * @brief 将srcImage中透明的地方用dstImage合并
	 * 
	 * 
	 * @param  Mat & srcImage	原图片
	 * @param  Mat & dstImagePtr	添加图片
	 * @return  cv::Mat	返回处理好的Mat
	 */
	 Mat MatMergeTransparentImage(Mat& srcImage, Mat& dstImagePtr);
	 Mat m_mat_MidBG, m_mat_MidBG_Mask; /**<  中景资源*/
	 Mat m_mat_FarBG, m_mat_FarBG_Mask; /**<  远景资源*/

	 int m_ViewX; /**<  场景需要被显示的起始x*/
	 int m_ViewX_far; /**<  远景需要被显示的起始x*/
	 int m_StageWidth;	/**<  当前场景的宽度*/
	 bool m_IsClearance; /**<  当前场景是否已通关*/
	 bool m_IsBossRoom; /**<  当前场景是否是boos房间*/
	 CCharacter* m_Character = NULL;	/**<  角色对象指针*/
	 NEXT_STAGE m_NextStage;	/**<  相邻的场景*/

	 CMonster* m_TargetMonster;	/**<  角色当前攻击的对象*/
	 int m_TargetMonsterHp, m_TargetMonsterHp_Animation;	/**<  角色当前攻击的对象的血量*/
	 Mat m_Mat_TargetMonsterAvator;	/**<  角色当前攻击的对象的头像*/
	 String m_TargetMonsterName;	/**<  角色当前攻击的对象名称*/
	 bool m_isTargetMonsterBoss;	/**<  角色当前攻击的对象是否为boss*/
	 int*  m_DungeonScorePointer;	/**<  评价点数的指针*/
};

