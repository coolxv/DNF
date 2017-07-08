#pragma once
#include "Dungeon.h"
#include "Dungeon_Rolland.h"
#include "Dungeon_Home.h"
#include "Dungeon_SelectDungeon.h"
#include "Dungeon_Start.h"
#include "Dungeon_Comics.h"
#include "Dungeon_Maze.h"
#include "OtherObject.h"
#include "AnimationEffect.h"
#include "Hud.h"
#define FRAMES_PER_SECOND  100
#define FRAMES_TIME ( 1000 / FRAMES_PER_SECOND )

/**
 * @class CGame
 * @brief Game������
 * 
 *����������Ϸ������
 */
class CGame
{
public:
	/** @brief  ��Ϸ״̬ */
	enum GAMESTATE
	{
		GAMESTATE_HOME,	/**<	������ */
		GAMESTATE_INDUNGEON,	/**<  ���³��� */
		GAMESTATE_SELECTDUNGEON	/**<  ѡ����³��� */
	};
private:
	bool m_IsRunning; /**<  ������Ϸ�Ƿ����� */
	void HandleInput(); /**< �������룺��Щ��������������ڽ����豸�����̣���꣬��Ϸ�������ȵȣ������� */
	void Update();	/**<  ϵͳ���£�update������������������Է��ģ��Ը�����ϵͳ���и��£��Ծ�����ǰ����Ϸ״̬ */
	void Render(); /**<  ��Ⱦ��render������������Ϸ����������Ⱦ�� */
	CCharacter* m_Character = NULL;/**<  ��ɫ����ָ��*/
	CDungeon* m_CurDungeon = NULL;	/**<  ��ǰ��ɫ���ڵĵ��³�*/
	CHud* m_Hud = NULL;	/**<  �·��Ľ�ɫ����Ѫ������ͼ */
	Mat m_Mat_Game;	/**<  ������ʾ��Ϸ�����Mat */
	std::vector<CAnimationEffect*> m_AnimationEffects; /**<  ��ʾ�еĶ�������*/
	int m_GameState;	/**<  ��Ϸ״̬ */
public:
	CGame();
	~CGame();
	
	/**
	 * @brief ��Ϸ��ѭ��
	 * 
	 * 
	 * @return  void  
	 */
	 void Run();

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
};

