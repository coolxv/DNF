#include "OtherObject.h"
#include "CharacterState.h"



COtherObject::COtherObject()
{
	m_Complete = false;
}


COtherObject::~COtherObject()
{
}

//门 的资源的初始化
Mat Gate::s_Mat_Gate0[][4] =
{
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left0.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left1.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left2.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left3.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right0.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right1.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right2.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right3.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top0.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top1.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top2.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top3.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom0.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom1.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom2.png", -1),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom3.png", -1),
};


Mat Gate::s_Mat_Gate0_Mask[][4] =
{
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left0.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left1.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left2.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_left3.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right0.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right1.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right2.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_right3.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top0.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top1.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top2.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_top3.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom0.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom1.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom2.png", 0),
	imread("./ImagePacks2/Object/granflorissidegate.img/gate_bottom3.png", 0),
};


Gate::Gate(int position, int x, int y, CStage* stage) :m_GatePosition(position), m_Clock_GateTimer(-1)
{
	int thick[4] = { 80,80,55,0 };	//左右上下
	m_Thick = thick[position];
	m_Clock_PreRender = clock();
	m_X = x;
	m_Y = y;
	m_Complete = false;
	if (stage->IsClearance())
	{
		switch (position)
		{
		case LEFT_GATE:
			if (stage->GetNextStage().left->IsClearance())
				if (stage->GetNextStage().left->IsBossRoom())
					m_GateTYpe = BOOS_GATE;
				else
					m_GateTYpe = OPEN_GATE;
			else
				m_GateTYpe = CLOSE_GATE;
			break;

		case RIGHT_GATE:
			if (stage->GetNextStage().right->IsClearance())
				if (stage->GetNextStage().right->IsBossRoom())
					m_GateTYpe = BOOS_GATE;
				else
					m_GateTYpe = OPEN_GATE;
			else
				m_GateTYpe = CLOSE_GATE;
			break;

		case TOP_GATE:
			if (stage->GetNextStage().top->IsClearance())
				if (stage->GetNextStage().top->IsBossRoom())
					m_GateTYpe = BOOS_GATE;
				else
					m_GateTYpe = OPEN_GATE;
			else
				m_GateTYpe = CLOSE_GATE;
			break;

		case BOTTOM_GATE:
			if (stage->GetNextStage().bottom->IsClearance())
				if (stage->GetNextStage().bottom->IsBossRoom())
					m_GateTYpe = BOOS_GATE;
				else
					m_GateTYpe = OPEN_GATE;
			else
				m_GateTYpe = CLOSE_GATE;
			break;
		}
		m_MatId = m_GateTYpe;
	}
	else
	{
		m_MatId = CLOSE_GATE;
		m_GateTYpe = CLOSE_GATE;
	}
}

Gate::~Gate()
{
}


void Gate::DoRender(Mat& mat, int viewX)
{
	if (m_GateTYpe == BOOS_GATE || m_GateTYpe == OPEN_GATE)
	{
		clock_t cur = clock();
		if (cur - m_Clock_PreRender > 800)
		{
			m_Clock_PreRender = cur;
			if (m_MatId != NORMAL_GATE)
			{
				m_MatId = NORMAL_GATE;
			}
			else
			{
				m_MatId = m_GateTYpe;
			}
		}
	}
	m_Mat_RenderMat = s_Mat_Gate0[m_GatePosition][m_MatId];
	m_Mat_RenderMat_Mask = s_Mat_Gate0_Mask[m_GatePosition][m_MatId];
	if (m_X + m_Mat_RenderMat.cols > viewX && m_X < viewX + CStage::s_ViewWidth)
	{
		int x = m_X - viewX, y = m_Y + CStage::s_OffsetY - m_Mat_RenderMat.rows; //相对坐标
		if (m_X < viewX) //只显示部分
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(viewX - m_X, m_Mat_RenderMat.cols - 1);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(viewX - m_X, m_Mat_RenderMat_Mask.cols - 1);
			x = 0;
		}
		else if (m_X + m_Mat_RenderMat.cols>viewX + CStage::s_ViewWidth)
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(0, viewX + CStage::s_ViewWidth - m_X);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(0, viewX + CStage::s_ViewWidth - m_X);
		}
		Mat ROI = mat(Rect(x, y, m_Mat_RenderMat.cols, m_Mat_RenderMat.rows));
		m_Mat_RenderMat.copyTo(ROI, m_Mat_RenderMat_Mask);
	}
}

bool Gate::Update(CStage& stage, CDungeon* dungeon)
{
	CCharacter* character = stage.GetCharacter();
	int cx = character->GetX();
	int cy = character->GetY();
	if (stage.IsClearance())
	{
		switch (m_GatePosition)
		{
		case RIGHT_GATE:
			if (stage.GetNextStage().right)
				m_GateTYpe = stage.GetNextStage().right->IsBossRoom() ? BOOS_GATE : OPEN_GATE;
			break;
		case LEFT_GATE:
			if (stage.GetNextStage().left)
				m_GateTYpe = stage.GetNextStage().left->IsBossRoom() ? BOOS_GATE : OPEN_GATE;
			break;
		case TOP_GATE:
			if(stage.GetNextStage().top)
				m_GateTYpe = stage.GetNextStage().top->IsBossRoom() ? BOOS_GATE : OPEN_GATE;
			break;
		case BOTTOM_GATE:
			if (stage.GetNextStage().bottom)
				m_GateTYpe = stage.GetNextStage().bottom->IsBossRoom() ? BOOS_GATE : OPEN_GATE;
			break;
		}

		if (stage.IsBossRoom())
		{
			m_GateTYpe = BOOS_GATE;
		}
	}
	else
	{
		m_GateTYpe = CLOSE_GATE;
	}

	bool gateFlag = false; //标记人物是否碰撞门
	clock_t cur = clock();
	if (m_GateTYpe != CLOSE_GATE)
		if (cx >= m_X - 20 && cx <= m_X + 80 && cy >= m_Y - 50 && cy <= m_Y + 20
			|| cx >= m_X - 10 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 20 && cy <= m_Y + 20
			|| cx >= m_X - 10 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 60 && cy <= m_Y + 10
			|| cx >= m_X + 45 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 50 && cy <= m_Y + 20)
		{
			if (m_Clock_GateTimer == -1)
			{
				m_Clock_GateTimer = cur;
				return true;
			}
			else if (cur - m_Clock_GateTimer < 1500)return true;
			switch (m_GatePosition)
			{
			case RIGHT_GATE:
				if (cx >= m_X - 20 && cx <= m_X + 80 && cy >= m_Y - 50 && cy <= m_Y + 20)
				{
					dungeon->SwitchStage(stage.GetNextStage().right);
					stage.GetCharacter()->SetX(50);
					stage.GetNextStage().right->SetViewX(stage.GetCharacter()->GetX() - CStage::s_ViewWidth / 2);

					return false;
				}
				break;
			case TOP_GATE:
				if (cx >= m_X - 10 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 20 && cy <= m_Y + 20)
				{
					dungeon->SwitchStage(stage.GetNextStage().top);
					stage.GetCharacter()->SetY(175);
					stage.GetCharacter()->SetX(stage.GetNextStage().top->GetStageWidth() / 2);
					stage.GetNextStage().top->SetViewX(stage.GetCharacter()->GetX() - CStage::s_ViewWidth / 2);
					return false;
				}
				break;
			case BOTTOM_GATE:
				if (cx >= m_X - 10 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 60 && cy <= m_Y + 10)
				{
					dungeon->SwitchStage(stage.GetNextStage().bottom);
					stage.GetCharacter()->SetX(stage.GetNextStage().bottom->GetStageWidth() / 2);
					stage.GetCharacter()->SetY(10);
					stage.GetNextStage().bottom->SetViewX(stage.GetCharacter()->GetX() - CStage::s_ViewWidth / 2);
					return false;
				}
				break;
			case LEFT_GATE:
				if (cx >= m_X + 45 && cx <= m_X + m_Mat_RenderMat.cols + 10 && cy >= m_Y - 50 && cy <= m_Y + 20)
				{
					dungeon->SwitchStage(stage.GetNextStage().left);
					stage.GetCharacter()->SetX(stage.GetNextStage().left->GetStageWidth() -80);
					stage.GetNextStage().left->SetViewX(stage.GetCharacter()->GetX() - CStage::s_ViewWidth / 2);
					return false;
				}
				break;
			}
		}
		else
		{
			m_Clock_GateTimer = -1;
			return true;
		}
	return true;
}

Mat Tree::s_Mat_Tree0[] =
{
	imread("./ImagePacks2/Object/tree/tree1.png",-1)
};
Mat Tree::s_Mat_Tree0_Mask[] =
{
	imread("./ImagePacks2/Object/tree/tree1.png",0)
};
int Tree::s_Tree_SetOffX[] = { -20 };
int Tree::s_Tree_SetOffY[] = { 25 };

Tree::Tree(int x, int y,int type)
{
	m_Thick = 20;
	m_Width = 60;
	m_Height = 190;
	m_X = x;
	m_Y = y;
	m_Z = 0;
	m_TreeType = type;
	m_Complete = false;
}

Tree::~Tree()
{
}

void Tree::Init()
{
	m_Thick = 20;
	m_Width = 60;
	m_Height = 190;
}

bool Tree::Update(CStage & stage, CDungeon * dungeon)
{
	CCharacter* character = stage.GetCharacter();
	int cx = character->GetX();
	int cy = character->GetY();
	Rect character_rect = character->GetRectXY();
	Rect tree_rect = GetRectXY();
	if ((character_rect&tree_rect).area() != 0) //有交集
	{
		character->Move(character->GetMoveDirection(), -1);
	}
	return true;
}

void Tree::DoRender(Mat & mat, int viewX)
{
	m_Mat_RenderMat = s_Mat_Tree0[m_TreeType];
	m_Mat_RenderMat_Mask = s_Mat_Tree0_Mask[m_TreeType];
	if (m_X + m_Mat_RenderMat.cols + Tree::s_Tree_SetOffX[m_TreeType] > viewX && m_X + Tree::s_Tree_SetOffX[m_TreeType]< viewX + CStage::s_ViewWidth)
	{
		int x = m_X - viewX+ Tree::s_Tree_SetOffX[m_TreeType], y = m_Y + CStage::s_OffsetY - m_Mat_RenderMat.rows + Tree::s_Tree_SetOffY[m_TreeType]; //相对坐标
		if (x<0 ) //只显示部分
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(abs(x), m_Mat_RenderMat.cols - 1);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(abs(x), m_Mat_RenderMat_Mask.cols - 1);
			x = 0;
		}
		else if (x + m_Mat_RenderMat.cols> CStage::s_ViewWidth)
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(0,  CStage::s_ViewWidth - x-1);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(0, CStage::s_ViewWidth - x - 1);
		}
		Mat ROI = mat(Rect(x, y, m_Mat_RenderMat.cols, m_Mat_RenderMat.rows));
		m_Mat_RenderMat.copyTo(ROI, m_Mat_RenderMat_Mask);
	}
}

Mat ThrowStone::s_Mat_ThrowStone[] =
{
	imread("./ImagePacks2/Object/throwstone/0.png",-1),
	imread("./ImagePacks2/Object/throwstone/1.png",-1),
	imread("./ImagePacks2/Object/throwstone/2.png",-1),
	imread("./ImagePacks2/Object/throwstone/3.png",-1)
};
Mat ThrowStone::s_Mat_ThrowStone_Mask[] =
{
	imread("./ImagePacks2/Object/throwstone/0.png",0),
	imread("./ImagePacks2/Object/throwstone/1.png",0),
	imread("./ImagePacks2/Object/throwstone/2.png",0),
	imread("./ImagePacks2/Object/throwstone/3.png",0)
};

ThrowStone::ThrowStone(int x, int y, int z,int dir,int power)
{
	m_Thick = 10;
	m_Width = 17;
	m_Height = 17;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_MatId = 0;
	m_Clock_PreRender = 0;
	m_Dir = dir;
	m_Complete = false;
	m_Power = power;
}

bool ThrowStone::Update(CStage& stage, CDungeon* dungeon)
{
	clock_t cur = clock();
	if (cur - m_Clock_PreRender > 500)
	{
		m_MatId++;
		if (m_MatId == 4)
			m_MatId = 0;
		int nx = m_X + 6 * (m_Dir == DIR_LEFT ? -1 : 1);
		if (nx  <= 5)
		{
			m_Complete = true;
			m_X = 5;
		}
		else if(nx + s_Mat_ThrowStone[m_MatId].cols >= stage.GetStageWidth())
		{
			m_Complete = true;
			m_X = stage.GetStageWidth()- s_Mat_ThrowStone[m_MatId].cols-1;
		}
		else
			m_X = nx;

		//---------------处理石头碰撞事件------------------
		CCharacter* character = stage.GetCharacter();
		Rect stonRect = GetRectXY();
		Rect bodyRect = character->GetRectXY();
		Rect intersection = stonRect&bodyRect;
		if (intersection.area() != 0 && m_Z >= character->GetZ())
		{
			//是否要切换状态
			if (typeid(*character->GetCurState()) != typeid(CharacterBeAttackState))
				character->SetState(&s_BeAttacked);

			character->SetHp(character->GetHp() - m_Power);
			character->DoHandleInput(EVENT_BEATTACK); //Attack
			m_Complete = true;
		}
	}

	return true;
}

void ThrowStone::DoRender(Mat& mat, int viewX)
{
	m_Mat_RenderMat = s_Mat_ThrowStone[m_MatId];
	m_Mat_RenderMat_Mask = s_Mat_ThrowStone_Mask[m_MatId];
	if (m_X + m_Mat_RenderMat.cols > viewX && m_X < viewX + CStage::s_ViewWidth)
	{
		int x = m_X - viewX , y = m_Y + CStage::s_OffsetY - m_Mat_RenderMat.rows -m_Z/2 ; //相对坐标
		if (x<0) //只显示部分
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(abs(x), m_Mat_RenderMat.cols - 1);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(abs(x), m_Mat_RenderMat_Mask.cols - 1);
			x = 0;
		}
		else if (x + m_Mat_RenderMat.cols> CStage::s_ViewWidth)
		{
			m_Mat_RenderMat = m_Mat_RenderMat.colRange(0, CStage::s_ViewWidth - x - 1);
			m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(0, CStage::s_ViewWidth - x - 1);
		}
		Mat ROI = mat(Rect(x, y, m_Mat_RenderMat.cols, m_Mat_RenderMat.rows));
		m_Mat_RenderMat.copyTo(ROI, m_Mat_RenderMat_Mask);
	}
}


Mat Meat::s_Mat_Meat[][4] = 
{
	imread("./ImagePacks2/Object/Meat/0/0.png",-1),
	imread("./ImagePacks2/Object/Meat/0/1.png",-1),
	imread("./ImagePacks2/Object/Meat/0/2.png",-1),
	imread("./ImagePacks2/Object/Meat/0/3.png",-1),
};
Mat Meat::s_Mat_Meat_Mask[][4] =
{
	imread("./ImagePacks2/Object/Meat/0/0.png",0),
	imread("./ImagePacks2/Object/Meat/0/1.png",0),
	imread("./ImagePacks2/Object/Meat/0/2.png",0),
	imread("./ImagePacks2/Object/Meat/0/3.png",0),
};

Meat::Meat(CMonster* monster,int type)
{
	m_MeatType = type;
	m_X = monster->GetX();
	m_Y = monster->GetY();
	m_Z = monster->GetZ();
	m_Width = monster->GetWidth();
	m_Height = monster->GetHeight();
	m_Thick = monster->GetThick();

	m_Clock_PreUpdate = 0;
	m_Clock_Fell = 0;
	int meatNum = GetRandNum(4, 8);
	while (meatNum--)
	{
		int monster_xspeed = 0;  //死亡前的x轴速度
		if (monster->GetJumpDir() != DIR_NONE)
			monster_xspeed = monster->GetJumpSpeed()*((monster->GetJumpDir() == DIR_RIGHT) ?  1 : -1);
		int xspeed = GetRandNum(-2, 2) + monster_xspeed;
		int yspeed = GetRandNum(-1, 1);
		int zspeed = GetRandNum(20 ,20) ;
		m_Meats.push_back(_Meat(Point3i(m_X,m_Y,m_Z),Point3i(xspeed,yspeed,zspeed), GetRandNum(0, 3)));
	}
}

void Meat::DoRender(Mat& mat, int viewX)
{
	if (m_Complete)return;
	if (m_Clock_Fell&&clock() - m_Clock_Fell > 500)
	{
		m_Complete = true;
		return;
	}
	
	for (auto it = m_Meats.begin(); it != m_Meats.end(); it++)
	{
		int _x = it->Pos.x;
		int _y = it->Pos.y;
		int _z = it->Pos.z;
		m_Mat_RenderMat = s_Mat_Meat[m_MeatType][it->Type];
		m_Mat_RenderMat_Mask = s_Mat_Meat[m_MeatType][it->Type];
		if (_x + m_Mat_RenderMat.cols > viewX && _x < viewX + CStage::s_ViewWidth)
		{
			int x = _x - viewX, y = _y + CStage::s_OffsetY - m_Mat_RenderMat.rows - _z / 2; //相对坐标
			if (x<0) //只显示部分
			{
				m_Mat_RenderMat = m_Mat_RenderMat.colRange(abs(x), m_Mat_RenderMat.cols - 1);
				m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(abs(x), m_Mat_RenderMat_Mask.cols - 1);
				x = 0;
			}
			else if (x + m_Mat_RenderMat.cols> CStage::s_ViewWidth)
			{
				m_Mat_RenderMat = m_Mat_RenderMat.colRange(0, CStage::s_ViewWidth - x - 1);
				m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.colRange(0, CStage::s_ViewWidth - x - 1);
			}
			else if(y+ m_Mat_RenderMat.rows>=mat.rows)
			{
				m_Mat_RenderMat = m_Mat_RenderMat.rowRange(0, mat.rows-y-1);
				m_Mat_RenderMat_Mask = m_Mat_RenderMat_Mask.rowRange(0, mat.rows-y-1);
			}

			Mat ROI = mat(Rect(x, y, m_Mat_RenderMat.cols, m_Mat_RenderMat.rows));
			m_Mat_RenderMat.copyTo(ROI, m_Mat_RenderMat_Mask);
		}
	}
	bool flag = true;
	if (clock() - m_Clock_PreUpdate > 10 && m_Clock_Fell==0)
	{
		for (auto it = m_Meats.begin(); it != m_Meats.end(); it++)
		{
			it->Pos.x += it->Speed.x;
			it->Pos.y += it->Speed.y;
			it->Pos.z += it->Speed.z;
			if (it->Pos.z < 0)
				it->Pos.z = 0;
			if (it->Pos.z != 0)
				flag = false;
			it->Speed.z--;
		}
		m_Clock_PreUpdate = clock();
		if (flag)
		{
			m_Clock_Fell = clock();
		}
	}

}
