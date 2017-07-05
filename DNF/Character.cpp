#include "Character.h"
#include "Stage.h"
#include "CharacterState.h"

CCharacter::CCharacter()
{
	__InitRec();
	m_State = &s_Standing;
	m_Gravity = 0;
	m_ZSpeed = 0;
	m_MoveDirection = DIR_NONE;
	m_MoveSpeed = CHARACTER_MOVESPEED;
	m_JumpDir = DIR_NONE;	
	m_Thick = 25;
	m_Width = 35;
	m_Height = 115;
	
	m_HP = CHARACTER_HP;
	m_TotalHp = CHARACTER_HP;
}


CCharacter::~CCharacter()
{
}

void CCharacter::SetState(CCharacterState * p)
{
	m_State = p;
	if (p)
	{
		m_State->InitState(*this);
	}
}

void CCharacter::DoRender(Mat& mat, int viewX)
{
	Mat body = m_Orientation == DIR_RIGHT ? m_Mat_Body[m_State->GetMatId()] : m_Mat_LBody[m_State->GetMatId()];
	Mat body_mask = m_Orientation == DIR_RIGHT ? m_Mat_Body_Mask[m_State->GetMatId()] : m_Mat_LBody_Mask[m_State->GetMatId()]; //当前角色的资源图
	int tx = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x;
	int ty = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y;
	Mat ROI;
	int xx = m_X - viewX - tx; //相对坐标
	int yy = m_Y - ty - m_Z / 2 + CStage::s_OffsetY;
	_Draw(mat, viewX, CStage::s_ViewWidth,CStage::s_ViewHeight, CStage::s_OffsetY, xx, yy, body, body_mask);
}

void CCharacter::DoHandleInput(int input)
{
	m_State->DoHandleInput(*this, input);
}

void CCharacter::UpdateState()
{

	//----------------------重力-----------------------
	if (m_Gravity != 0)
	{
		if (m_ZSpeed != 0)
		{
			if (m_Z + m_ZSpeed < 0)
				SetZ(0);
			else
				SetZ(m_Z + m_ZSpeed);
		}
		m_ZSpeed += m_Gravity;
	}

	m_State->UpdateState(*this);
}

void CCharacter::Move(int dir, double multiple)
{
	int m = (int)(m_MoveSpeed*multiple);
	SetMoveDirection(dir);
	switch (dir)
	{
	case DIR_UP:
		/*if (mY - mMovespeed*multiple >= 0)*/
		SetY(m_Y - m / 2);
		break;
	case DIR_DOWN:
		/*if (mY + mMovespeed*multiple < Stage::viewHeight)*/
		SetY(m_Y + m / 2);
		break;
	case DIR_RIGHT:
		/*if (mX + mMovespeed*multiple < Stage::viewWidth * 2 - 122)*/
		SetX(m_X + m);
		break;
	case DIR_LEFT:
		/*if (mX - mMovespeed*multiple >= 0)*/
		SetX(m_X - m);
		break;
	}
}

int CCharacter::GetDamage(int type,bool& crit)
{
	double p = 1.0;
	switch (type)
	{
	case EFFECTX:
		p = CHARACTER_EFFECT_POWER_J;
		break;
	case EFFECTZ:
		p = CHARACTER_EFFECT_POWER_H;
		break;
	case EFFECTS:
		p = CHARACTER_EFFECT_POWER_U1;
	case EFFECTS2:
		p = CHARACTER_EFFECT_POWER_U2;
		break;
	}
	if (GetRandNum(1, 100) < CHARACTER_CRIT) //暴击
	{
		crit = true;
		p *= 2;
	}
	return (int)(p*GetRandNum(CHARACTER_ATTACKPOWER,CHARACTER_ATTACKPOWER_));
}

int CCharacter::GetArmor()
{
	return CHARACTER_ARMOR;
}

Rect CCharacter::GetAttackRect()
{
	Mat mMat = m_Orientation == DIR_RIGHT ? m_Mat_Body[m_State->GetMatId()] : m_Mat_LBody[m_State->GetMatId()];
	int tx = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x;
	int ty = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y;
	if(m_Orientation==DIR_RIGHT)
		return  Rect(tx >= 8 ?m_X-tx :m_X , m_Y - m_Thick , mMat.cols, m_Thick);
	else
	{
		if (abs(tx) <= 5)
			Rect(m_X - tx, m_Y - m_Thick, m_X  + mMat.cols, m_Thick);
		return Rect(m_X-tx, m_Y - m_Thick, mMat.cols , m_Thick);
	}
	//return Rect(mX , mY - mThick - mZ / 2 , mMat.cols - tx, mThick);
}


int CCharacter::GetCurEffect()
{
	int id = m_State->GetMatId();

	if ((id == 50 || id == 55 || id == 61))
	{
		return EFFECTX;
	}
	else if (id == 66)	//上挑
	{
		return EFFECTZ;
	}
	else if (id == 75) //u技能第一段
	{
		return EFFECTS;
	}
	else if (id == 94) //u技能第二段
	{
		return EFFECTS2;
	}

	return NONE;
}

bool CCharacter::SetX(int x)
{
	if (x >= 10 && x <= m_StageWidth - 50)
	{
		m_X = x;
		return true;
	}
	return false;
}
bool CCharacter::SetY(int y)
{
	if (y >= 10 && y <= CStage::s_ViewHeight - 10)
	{
		m_Y = y;
		return true;
	}
	return false;
}
bool CCharacter::SetZ(int z)
{
	if (z >= 0)
	{
		m_Z = z;
		return true;
	}
	return false;
}


void CCharacter::SetMoveDirection(int dir)
{
	m_MoveDirection = dir;
	if ((dir == DIR_LEFT || dir == DIR_RIGHT) && !m_isBackJumping) //后跳的时候不改变朝向
		m_Orientation = dir;
}

void CCharacter::SetHp(int hp)
{
	if (hp <= 0)
		m_HP = m_TotalHp;
	else if (hp>m_TotalHp)
		m_HP = m_TotalHp;
	else
		m_HP = hp;
}

void CCharacter::__InitRec()
{
	for (int i = 0; i < BODYIMGS; i++)
	{
		m_Mat_Body_Mask[i] = imread(format("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/right/%d.png", i), 0);
		m_Mat_Body[i] = imread(format("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/right/%d.png", i), -1);
		m_Mat_LBody_Mask[i] = imread(format("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/left/%d.png", i), 0);
		m_Mat_LBody[i] = imread(format("./ImagePacks2/Character_swordman_atequipment_avatar_skin/sg_body80000.img/left/%d.png", i), -1);
	}

	m_Offset_LeftBottom_Left[0] = { 65, 114 };
	m_Offset_LeftBottom_Left[1] = { 65, 114 };
	m_Offset_LeftBottom_Left[2] = { 65, 114 };
	m_Offset_LeftBottom_Left[3] = { 65, 114 };
	m_Offset_LeftBottom_Left[4] = { 65, 114 };
	m_Offset_LeftBottom_Left[5] = { 65, 114 };
	m_Offset_LeftBottom_Left[6] = { 65, 114 };
	m_Offset_LeftBottom_Left[7] = { 65, 114 };
	m_Offset_LeftBottom_Left[8] = { 65, 114 };
	m_Offset_LeftBottom_Left[9] = { 58, 113 };
	m_Offset_LeftBottom_Left[10] = { 58, 113 };
	m_Offset_LeftBottom_Left[11] = { 58, 113 };
	m_Offset_LeftBottom_Left[12] = { 58, 113 };
	m_Offset_LeftBottom_Left[13] = { 81, 112 };
	m_Offset_LeftBottom_Left[14] = { 73, 110 };
	m_Offset_LeftBottom_Left[15] = { 64, 110 };
	m_Offset_LeftBottom_Left[16] = { 67, 110 };
	m_Offset_LeftBottom_Left[17] = { 77, 110 };
	m_Offset_LeftBottom_Left[18] = { 90, 110 };
	m_Offset_LeftBottom_Left[19] = { 95, 108 };
	m_Offset_LeftBottom_Left[20] = { 91, 111 };
	m_Offset_LeftBottom_Left[21] = { 87, 113 };
	m_Offset_LeftBottom_Left[22] = { 87, 113 };
	m_Offset_LeftBottom_Left[23] = { 30, 94 };
	m_Offset_LeftBottom_Left[24] = { 29, 94 };
	m_Offset_LeftBottom_Left[25] = { 4, 92 };
	m_Offset_LeftBottom_Left[26] = { 30, 91 };
	m_Offset_LeftBottom_Left[27] = { 28, 91 };
	m_Offset_LeftBottom_Left[28] = { 0, 91 };
	m_Offset_LeftBottom_Left[29] = { 24, 97 };
	m_Offset_LeftBottom_Left[30] = { 4, 90 };
	m_Offset_LeftBottom_Left[31] = { 10, 82 };
	m_Offset_LeftBottom_Left[32] = { 12, 71 };
	m_Offset_LeftBottom_Left[33] = { 123, 107 };
	m_Offset_LeftBottom_Left[34] = { 94, 109 };
	m_Offset_LeftBottom_Left[35] = { 7, 105 };
	m_Offset_LeftBottom_Left[36] = { 45, 97 };
	m_Offset_LeftBottom_Left[37] = { 30, 140 };
	m_Offset_LeftBottom_Left[38] = { 38, 124 };
	m_Offset_LeftBottom_Left[39] = { 62, 122 };
	m_Offset_LeftBottom_Left[40] = { 65, 124 };
	m_Offset_LeftBottom_Left[41] = { 46, 97 };
	m_Offset_LeftBottom_Left[42] = { 67, 95 };
	m_Offset_LeftBottom_Left[43] = { 12, 91 };
	m_Offset_LeftBottom_Left[44] = { 116, 170 };
	m_Offset_LeftBottom_Left[45] = { 76, 155 };
	m_Offset_LeftBottom_Left[46] = { 16, 175 };
	m_Offset_LeftBottom_Left[47] = { 27, 158 };
	m_Offset_LeftBottom_Left[48] = { 49, 105 };
	m_Offset_LeftBottom_Left[49] = { 6, 95 };
	m_Offset_LeftBottom_Left[50] = { 119, 132 };
	m_Offset_LeftBottom_Left[51] = { 116, 151 };
	m_Offset_LeftBottom_Left[52] = { 87, 146 };
	m_Offset_LeftBottom_Left[53] = { 20, 143 };
	m_Offset_LeftBottom_Left[54] = { 26, 127 };
	m_Offset_LeftBottom_Left[55] = { 103, 101 };
	m_Offset_LeftBottom_Left[56] = { 73, 102 };
	m_Offset_LeftBottom_Left[57] = { 40, 100 };
	m_Offset_LeftBottom_Left[58] = { 6, 102 };
	m_Offset_LeftBottom_Left[59] = { 0, 126 };
	m_Offset_LeftBottom_Left[60] = { 4, 151 };
	m_Offset_LeftBottom_Left[61] = { 106, 122 };
	m_Offset_LeftBottom_Left[62] = { 97, 65 };
	m_Offset_LeftBottom_Left[63] = { 85, 61 };
	m_Offset_LeftBottom_Left[64] = { 54, 108 };
	m_Offset_LeftBottom_Left[65] = { 11, 89 };
	m_Offset_LeftBottom_Left[66] = { 123, 111 };
	m_Offset_LeftBottom_Left[67] = { 114, 113 };
	m_Offset_LeftBottom_Left[68] = { 107, 103 };
	m_Offset_LeftBottom_Left[69] = { 36, 152 };
	m_Offset_LeftBottom_Left[70] = { 118, 86 };
	m_Offset_LeftBottom_Left[71] = { 8, 70 };
	m_Offset_LeftBottom_Left[72] = { 8, 70 };
	m_Offset_LeftBottom_Left[73] = { 12, 94 };

	m_Offset_LeftBottom_Left[74] = { 12, 90 };
	m_Offset_LeftBottom_Left[75] = { 57, 156 };
	m_Offset_LeftBottom_Left[76] = { 4, 159 };
	/*m_Offset_LeftBottom_Left[74] = { 11, 117 };
	m_Offset_LeftBottom_Left[75] = { 64, 161 };
	m_Offset_LeftBottom_Left[76] = { 0, 159 };*/

	m_Offset_LeftBottom_Left[77] = { 6, 150 };
	m_Offset_LeftBottom_Left[78] = { 100, 184 };
	m_Offset_LeftBottom_Left[79] = { 85, 192 };
	m_Offset_LeftBottom_Left[80] = { 40, 196 };
	m_Offset_LeftBottom_Left[81] = { 0, 112 };
	m_Offset_LeftBottom_Left[82] = { 0, 130 };
	m_Offset_LeftBottom_Left[83] = { 5, 132 };
	m_Offset_LeftBottom_Left[84] = { 6, 116 };
	m_Offset_LeftBottom_Left[85] = { 127, 158 };
	m_Offset_LeftBottom_Left[86] = { 115, 80 };
	m_Offset_LeftBottom_Left[87] = { 80, 78 };
	m_Offset_LeftBottom_Left[88] = { 134, 154 };
	m_Offset_LeftBottom_Left[89] = { 111, 55 };
	m_Offset_LeftBottom_Left[90] = { 112, 56 };

	m_Offset_LeftBottom_Left[91] = { 0, 110 };
	m_Offset_LeftBottom_Left[92] = { 4, 126 };
	m_Offset_LeftBottom_Left[93] = { 4, 132 };
	m_Offset_LeftBottom_Left[94] = { 99, 134 };
	m_Offset_LeftBottom_Left[95] = { 8, 110 };
	m_Offset_LeftBottom_Left[96] = { 6, 111 };

	//m_Offset_LeftBottom_Left[91] = { 0, 114 };
	//m_Offset_LeftBottom_Left[92] = { 110, 126 };
	//m_Offset_LeftBottom_Left[93] = { 110, 132 };
	//m_Offset_LeftBottom_Left[94] = { 119, 184 };
	//m_Offset_LeftBottom_Left[95] = { 75, 135 };
	//m_Offset_LeftBottom_Left[96] = { 74, 124 };

	m_Offset_LeftBottom_Left[97] = { 4, 95 };
	m_Offset_LeftBottom_Left[98] = { 18, 128 };
	m_Offset_LeftBottom_Left[99] = { 72, 77 };
	m_Offset_LeftBottom_Left[100] = { 109, 91 };
	m_Offset_LeftBottom_Left[101] = { 117, 89 };
	m_Offset_LeftBottom_Left[102] = { 114, 91 };
	m_Offset_LeftBottom_Left[103] = { 6, 110 };
	m_Offset_LeftBottom_Left[104] = { 46, 118 };
	m_Offset_LeftBottom_Left[105] = { 66, 93 };
	m_Offset_LeftBottom_Left[106] = { 122, 89 };
	m_Offset_LeftBottom_Left[107] = { 125, 86 };
	m_Offset_LeftBottom_Left[108] = { 125, 86 };
	m_Offset_LeftBottom_Left[109] = { 65, 110 };
	m_Offset_LeftBottom_Left[110] = { 27, 98 };
	m_Offset_LeftBottom_Left[111] = { 6, 120 };
	m_Offset_LeftBottom_Left[112] = { 14, 111 };
	m_Offset_LeftBottom_Left[113] = { 14, 121 };
	m_Offset_LeftBottom_Left[114] = { 89, 111 };
	m_Offset_LeftBottom_Left[115] = { 77, 88 };
	m_Offset_LeftBottom_Left[116] = { 23, 75 };
	m_Offset_LeftBottom_Left[117] = { 28, 73 };
	m_Offset_LeftBottom_Left[118] = { 4, 109 };
	m_Offset_LeftBottom_Left[119] = { 6, 116 };
	m_Offset_LeftBottom_Left[120] = { 5, 116 };
	m_Offset_LeftBottom_Left[121] = { 4, 135 };
	m_Offset_LeftBottom_Left[122] = { 22, 189 };
	m_Offset_LeftBottom_Left[123] = { 96, 169 };
	m_Offset_LeftBottom_Left[124] = { 117, 134 };
	m_Offset_LeftBottom_Left[125] = { 58, 110 };
	m_Offset_LeftBottom_Left[126] = { 61, 108 };
	m_Offset_LeftBottom_Left[127] = { 61, 111 };
	m_Offset_LeftBottom_Left[128] = { 63, 109 };
	m_Offset_LeftBottom_Left[129] = { 59, 111 };
	m_Offset_LeftBottom_Left[130] = { 55, 111 };
	m_Offset_LeftBottom_Left[131] = { 50, 114 };
	m_Offset_LeftBottom_Left[132] = { 62, 113 };
	m_Offset_LeftBottom_Left[133] = { 60, 114 };
	m_Offset_LeftBottom_Left[134] = { 61, 113 };
	m_Offset_LeftBottom_Left[135] = { 62, 119 };
	m_Offset_LeftBottom_Left[136] = { 57, 114 };
	m_Offset_LeftBottom_Left[137] = { 52, 111 };
	m_Offset_LeftBottom_Left[138] = { 51, 114 };
	m_Offset_LeftBottom_Left[139] = { 54, 95 };
	m_Offset_LeftBottom_Left[140] = { 54, 95 };
	m_Offset_LeftBottom_Left[141] = { 4, 113 };
	m_Offset_LeftBottom_Left[142] = { 5, 107 };
	m_Offset_LeftBottom_Left[143] = { 53, 40 };
	m_Offset_LeftBottom_Left[144] = { 66, 56 };
	m_Offset_LeftBottom_Left[145] = { 73, 100 };
	m_Offset_LeftBottom_Left[146] = { 54, 92 };
	m_Offset_LeftBottom_Left[147] = { 56, 87 };
	m_Offset_LeftBottom_Left[148] = { 54, 91 };
	m_Offset_LeftBottom_Left[149] = { 54, 92 };
	m_Offset_LeftBottom_Left[150] = { 55, 96 };
	m_Offset_LeftBottom_Left[151] = { 10, 130 };
	m_Offset_LeftBottom_Left[152] = { 10, 130 };
	m_Offset_LeftBottom_Left[153] = { 10, 130 };
	m_Offset_LeftBottom_Left[154] = { 10, 130 };
	m_Offset_LeftBottom_Left[155] = { 10, 130 };
	m_Offset_LeftBottom_Left[156] = { 10, 130 };
	m_Offset_LeftBottom_Left[157] = { 10, 130 };
	m_Offset_LeftBottom_Left[158] = { 10, 130 };
	m_Offset_LeftBottom_Left[159] = { 121, 105 };
	m_Offset_LeftBottom_Left[160] = { 156, 174 };
	m_Offset_LeftBottom_Left[161] = { 6, 168 };
	m_Offset_LeftBottom_Left[162] = { 93, 119 };
	m_Offset_LeftBottom_Left[163] = { 6, 129 };
	m_Offset_LeftBottom_Left[164] = { 12, 153 };
	m_Offset_LeftBottom_Left[165] = { 146, 176 };
	m_Offset_LeftBottom_Left[166] = { 96, 79 };
	m_Offset_LeftBottom_Left[167] = { 47, 88 };
	m_Offset_LeftBottom_Left[168] = { 140, 81 };
	m_Offset_LeftBottom_Left[169] = { 170, 72 };
	m_Offset_LeftBottom_Left[170] = { 107, 164 };
	m_Offset_LeftBottom_Left[171] = { 134, 145 };
	m_Offset_LeftBottom_Left[172] = { 134, 70 };
	m_Offset_LeftBottom_Left[173] = { 164, 70 };
	m_Offset_LeftBottom_Left[174] = { 37, 99 };
	m_Offset_LeftBottom_Left[175] = { 44, 102 };
	m_Offset_LeftBottom_Left[176] = { 51, 87 };
	m_Offset_LeftBottom_Left[177] = { 95, 79 };
	m_Offset_LeftBottom_Left[178] = { 146, 75 };
	m_Offset_LeftBottom_Left[179] = { 188, 115 };
	m_Offset_LeftBottom_Left[180] = { 183, 112 };
	m_Offset_LeftBottom_Left[181] = { 142, 119 };
	m_Offset_LeftBottom_Left[182] = { 68, 90 };
	m_Offset_LeftBottom_Left[183] = { 27, 84 };
	m_Offset_LeftBottom_Left[184] = { 28, 62 };
	m_Offset_LeftBottom_Left[185] = { 55, 102 };
	m_Offset_LeftBottom_Left[186] = { 54, 107 };
	m_Offset_LeftBottom_Left[187] = { 57, 103 };
	m_Offset_LeftBottom_Left[188] = { 56, 102 };
	m_Offset_LeftBottom_Left[189] = { 31, 106 };
	m_Offset_LeftBottom_Left[190] = { 53, 102 };
	m_Offset_LeftBottom_Left[191] = { 114, 98 };
	m_Offset_LeftBottom_Left[192] = { 118, 96 };
	m_Offset_LeftBottom_Left[193] = { 114, 97 };
	m_Offset_LeftBottom_Left[194] = { 108, 113 };
	m_Offset_LeftBottom_Left[195] = { 55, 184 };
	m_Offset_LeftBottom_Left[196] = { 39, 214 };
	m_Offset_LeftBottom_Left[197] = { 15, 161 };
	m_Offset_LeftBottom_Left[198] = { 16, 90 };
	m_Offset_LeftBottom_Left[199] = { 17, 94 };
	m_Offset_LeftBottom_Left[200] = { 46, 94 };
	m_Offset_LeftBottom_Left[201] = { 24, 94 };
	m_Offset_LeftBottom_Left[202] = { 68, 155 };
	m_Offset_LeftBottom_Left[203] = { 55, 152 };
	m_Offset_LeftBottom_Left[204] = { 0, 153 };
	m_Offset_LeftBottom_Left[205] = { 103, 100 };
	m_Offset_LeftBottom_Left[206] = { 25, 94 };
	m_Offset_LeftBottom_Left[207] = { 29, 90 };
	m_Offset_LeftBottom_Left[208] = { 27, 88 };
	m_Offset_LeftBottom_Left[209] = { 28, 87 };
	m_Offset_LeftBottom_Left[210] = { 14, 151 };
	m_Offset_LeftBottom_Left[211] = { 139, 116 };
	m_Offset_LeftBottom_Left[212] = { 6, 103 };
	m_Offset_LeftBottom_Left[213] = { 110, 144 };
	m_Offset_LeftBottom_Left[214] = { 97, 52 };
	m_Offset_LeftBottom_Left[215] = { 98, 52 };
	m_Offset_LeftBottom_Left[216] = { 97, 96 };
	m_Offset_LeftBottom_Left[217] = { 105, 177 };
	m_Offset_LeftBottom_Left[218] = { 141, 216 };
	m_Offset_LeftBottom_Left[219] = { 13, 166 };
	m_Offset_LeftBottom_Left[220] = { 17, 89 };
	m_Offset_LeftBottom_Left[221] = { 19, 92 };

	m_Offset_LeftBottom[0] = { 20, 114 };
	m_Offset_LeftBottom[1] = { 20, 114 };
	m_Offset_LeftBottom[2] = { 20, 114 };
	m_Offset_LeftBottom[3] = { 20, 114 };
	m_Offset_LeftBottom[4] = { 20, 114 };
	m_Offset_LeftBottom[5] = { 20, 114 };
	m_Offset_LeftBottom[6] = { 20, 114 };
	m_Offset_LeftBottom[7] = { 20, 114 };
	m_Offset_LeftBottom[8] = { 20, 114 };
	m_Offset_LeftBottom[9] = { 28, 113 };
	m_Offset_LeftBottom[10] = { 28, 113 };
	m_Offset_LeftBottom[11] = { 28, 113 };
	m_Offset_LeftBottom[12] = { 28, 113 };
	m_Offset_LeftBottom[13] = { 10, 112 };
	m_Offset_LeftBottom[14] = { 0, 110 };
	m_Offset_LeftBottom[15] = { 0, 113 };
	m_Offset_LeftBottom[16] = { 0, 113 };
	m_Offset_LeftBottom[17] = { 0, 113 };
	m_Offset_LeftBottom[18] = { 0, 113 };
	m_Offset_LeftBottom[19] = { 0, 111 };
	m_Offset_LeftBottom[20] = { 0, 111 };
	m_Offset_LeftBottom[21] = { 0, 113 };
	m_Offset_LeftBottom[22] = { 0, 113 };
	m_Offset_LeftBottom[23] = { 0, 94 };
	m_Offset_LeftBottom[24] = { 0, 94 };
	m_Offset_LeftBottom[25] = { 0, 92 };
	m_Offset_LeftBottom[26] = { 0, 91 };
	m_Offset_LeftBottom[27] = { 0, 91 };
	m_Offset_LeftBottom[28] = { 0, 91 };
	m_Offset_LeftBottom[29] = { 36, 97 };
	m_Offset_LeftBottom[30] = { 110, 90 };
	m_Offset_LeftBottom[31] = { 51, 86 };
	m_Offset_LeftBottom[32] = { 44, 77 };
	m_Offset_LeftBottom[33] = { 26, 107 };
	m_Offset_LeftBottom[34] = { 36, 109 };
	m_Offset_LeftBottom[35] = { 56, 108 };
	m_Offset_LeftBottom[36] = { 10, 97 };
	m_Offset_LeftBottom[37] = { 13, 140 };
	m_Offset_LeftBottom[38] = { 25, 124 };
	m_Offset_LeftBottom[39] = { 27, 122 };
	m_Offset_LeftBottom[40] = { 25, 127 };
	m_Offset_LeftBottom[41] = { 10, 97 };
	m_Offset_LeftBottom[42] = { 25, 95 };
	m_Offset_LeftBottom[43] = { 91, 90 };
	m_Offset_LeftBottom[44] = { 0, 171 };
	m_Offset_LeftBottom[45] = { 26, 151 };
	m_Offset_LeftBottom[46] = { 9, 172 };
	m_Offset_LeftBottom[47] = { 0, 159 };

	m_Offset_LeftBottom[48] = { 23, 109 };
	m_Offset_LeftBottom[49] = { 81, 99 };
	m_Offset_LeftBottom[50] = { 0, 138 };
	m_Offset_LeftBottom[51] = { 0, 151 };
	m_Offset_LeftBottom[52] = { 0, 151 };
	m_Offset_LeftBottom[53] = { 31, 146 };
	m_Offset_LeftBottom[54] = { 38, 130 };
	m_Offset_LeftBottom[55] = { 0, 104 };
	m_Offset_LeftBottom[56] = { 0, 106 };
	m_Offset_LeftBottom[57] = { 4, 105 };
	m_Offset_LeftBottom[58] = { 72, 102 };
	m_Offset_LeftBottom[59] = { 107, 129 };
	m_Offset_LeftBottom[60] = { 104, 151 };
	m_Offset_LeftBottom[61] = { 0, 123 };
	m_Offset_LeftBottom[62] = { 0, 65 };
	m_Offset_LeftBottom[63] = { 0, 66 };

	m_Offset_LeftBottom[64] = { 11, 108 };
	m_Offset_LeftBottom[65] = { 100, 82 };
	m_Offset_LeftBottom[66] = { 0, 114 };
	m_Offset_LeftBottom[67] = { 0, 113 };
	m_Offset_LeftBottom[68] = { 0, 103 };
	m_Offset_LeftBottom[69] = { 0, 150 };
	m_Offset_LeftBottom[70] = { 67, 85 };
	m_Offset_LeftBottom[71] = { 50, 71 };
	m_Offset_LeftBottom[72] = { 46, 69 };
	m_Offset_LeftBottom[73] = { 35, 94 };

	m_Offset_LeftBottom[74] = { 6, 92 };
	m_Offset_LeftBottom[75] = { 77, 161 };
	m_Offset_LeftBottom[76] = { 91, 159 };
	/*m_Offset_LeftBottom[74] = { 8, 117 };
	m_Offset_LeftBottom[75] = { 82, 161 };
	m_Offset_LeftBottom[76] = { 96, 159 };*/

	m_Offset_LeftBottom[77] = { 91, 150 };
	m_Offset_LeftBottom[78] = { 0, 192 };
	m_Offset_LeftBottom[79] = { 0, 200 };
	m_Offset_LeftBottom[80] = { 0, 200 };
	m_Offset_LeftBottom[81] = { 52, 112 };
	m_Offset_LeftBottom[82] = { 55, 130 };
	m_Offset_LeftBottom[83] = { 52, 132 };
	m_Offset_LeftBottom[84] = { 54, 116 };
	m_Offset_LeftBottom[85] = { 0, 159 };
	m_Offset_LeftBottom[86] = { 0, 79 };
	m_Offset_LeftBottom[87] = { 0, 80 };
	m_Offset_LeftBottom[88] = { 0, 150 };
	m_Offset_LeftBottom[89] = { 0, 55 };
	m_Offset_LeftBottom[90] = { 0, 56 };

	m_Offset_LeftBottom[91] = { 59, 114 };
	m_Offset_LeftBottom[92] = { 75, 126 };
	m_Offset_LeftBottom[93] = { 75, 132 };
	m_Offset_LeftBottom[94] = { 78, 134 };
	m_Offset_LeftBottom[95] = { 81, 109 };
	m_Offset_LeftBottom[96] = { 80, 109 };

	//m_Offset_LeftBottom[91] = { 63, 114 };
	//m_Offset_LeftBottom[92] = { 77, 126 };
	//m_Offset_LeftBottom[93] = { 75, 132 };
	//m_Offset_LeftBottom[94] = { 79, 184 };
	//m_Offset_LeftBottom[95] = { 83, 135 };
	//m_Offset_LeftBottom[96] = { 82, 124 };

	m_Offset_LeftBottom[97] = { 69, 96 };
	m_Offset_LeftBottom[98] = { 108, 128 };
	m_Offset_LeftBottom[99] = { 69, 84 };
	m_Offset_LeftBottom[100] = { 0, 91 };
	m_Offset_LeftBottom[101] = { 0, 96 };
	m_Offset_LeftBottom[103] = { 44, 110 };
	m_Offset_LeftBottom[104] = { 35, 118 };
	m_Offset_LeftBottom[105] = { 11, 100 };
	m_Offset_LeftBottom[106] = { 0, 100 };
	m_Offset_LeftBottom[107] = { 4, 95 };
	m_Offset_LeftBottom[108] = { 5, 95 };
	m_Offset_LeftBottom[109] = { 0, 111 };
	m_Offset_LeftBottom[110] = { 8, 99 };
	m_Offset_LeftBottom[111] = { 0, 114 };
	m_Offset_LeftBottom[112] = { 31, 108 };
	m_Offset_LeftBottom[113] = { 45, 123 };
	m_Offset_LeftBottom[114] = { 52, 111 };
	m_Offset_LeftBottom[115] = { 95, 86 };
	m_Offset_LeftBottom[116] = { 69, 76 };
	m_Offset_LeftBottom[117] = { 72, 74 };
	m_Offset_LeftBottom[118] = { 30, 105 };
	m_Offset_LeftBottom[119] = { 0, 117 };
	m_Offset_LeftBottom[120] = { 0, 115 };
	m_Offset_LeftBottom[121] = { 77, 135 };
	m_Offset_LeftBottom[122] = { 36, 190 };
	m_Offset_LeftBottom[123] = { 16, 173 };
	m_Offset_LeftBottom[124] = { 11, 134 };
	m_Offset_LeftBottom[125] = { 24, 113 };
	m_Offset_LeftBottom[126] = { 19, 114 };
	m_Offset_LeftBottom[127] = { 19, 114 };
	m_Offset_LeftBottom[128] = { 22, 113 };
	m_Offset_LeftBottom[129] = { 24, 114 };
	m_Offset_LeftBottom[130] = { 28, 114 };
	m_Offset_LeftBottom[131] = { 26, 114 };
	m_Offset_LeftBottom[132] = { 24, 110 };
	m_Offset_LeftBottom[133] = { 25, 114 };
	m_Offset_LeftBottom[134] = { 25, 113 };
	m_Offset_LeftBottom[135] = { 23, 119 };
	m_Offset_LeftBottom[136] = { 27, 111 };
	m_Offset_LeftBottom[137] = { 28, 114 };
	m_Offset_LeftBottom[138] = { 28, 114 };
	m_Offset_LeftBottom[139] = { 13, 95 };
	m_Offset_LeftBottom[140] = { 15, 101 };
	m_Offset_LeftBottom[141] = { 0, 113 };
	m_Offset_LeftBottom[142] = { 4, 105 };
	m_Offset_LeftBottom[143] = { 0, 40 };
	m_Offset_LeftBottom[144] = { 4, 57 };
	m_Offset_LeftBottom[145] = { 0, 102 };
	m_Offset_LeftBottom[146] = { 5, 97 };
	m_Offset_LeftBottom[147] = { 5, 92 };
	m_Offset_LeftBottom[148] = { 6, 91 };
	m_Offset_LeftBottom[149] = { 7, 95 };
	m_Offset_LeftBottom[150] = { 4, 100 };
	m_Offset_LeftBottom[150] = { 0 , 100 };

	m_Offset_LeftBottom[151] = { 29 , 130 };
	m_Offset_LeftBottom[152] = { 29 , 130 };
	m_Offset_LeftBottom[153] = { 29 , 130 };
	m_Offset_LeftBottom[154] = { 29 , 130 };
	m_Offset_LeftBottom[155] = { 29 , 130 };
	m_Offset_LeftBottom[156] = { 29 , 130 };
	m_Offset_LeftBottom[157] = { 29 , 130 };
	m_Offset_LeftBottom[158] = { 29 , 130 };

	m_Offset_LeftBottom[159] = { 18 , 105 };
	m_Offset_LeftBottom[160] = { 20 , 174 };
	m_Offset_LeftBottom[161] = { 7 , 168 };
	m_Offset_LeftBottom[162] = { 0 , 119 };
	m_Offset_LeftBottom[163] = { 84 , 129 };
	m_Offset_LeftBottom[164] = { 75 , 153 };
	m_Offset_LeftBottom[165] = { 4 , 177 };
	m_Offset_LeftBottom[166] = { 4 , 78 };
	m_Offset_LeftBottom[167] = { 5 , 88 };
	m_Offset_LeftBottom[168] = { 0 , 81 };
	m_Offset_LeftBottom[169] = { 4 , 74 };
	m_Offset_LeftBottom[170] = { 4 , 164 };
	m_Offset_LeftBottom[170] = { 0 , 164 };
	m_Offset_LeftBottom[171] = { 0 , 147 };
	m_Offset_LeftBottom[172] = { 0 , 67 };
	m_Offset_LeftBottom[172] = { 0 , 70 };
	m_Offset_LeftBottom[173] = { 0 , 73 };
	m_Offset_LeftBottom[174] = { 6 , 103 };
	m_Offset_LeftBottom[175] = { 4 , 106 };
	m_Offset_LeftBottom[176] = { 6 , 95 };
	m_Offset_LeftBottom[177] = { 68 , 82 };
	m_Offset_LeftBottom[178] = { 94 , 73 };
	m_Offset_LeftBottom[179] = { 76 , 116 };
	m_Offset_LeftBottom[180] = { 51 , 112 };
	m_Offset_LeftBottom[181] = { 62 , 110 };
	m_Offset_LeftBottom[182] = { 75 , 96 };
	m_Offset_LeftBottom[183] = { 72 , 87 };
	m_Offset_LeftBottom[184] = { 17 , 63 };
	m_Offset_LeftBottom[185] = { 9 , 106 };
	m_Offset_LeftBottom[186] = { 10 , 107 };
	m_Offset_LeftBottom[187] = { 10 , 105 };
	m_Offset_LeftBottom[188] = { 10 , 104 };
	m_Offset_LeftBottom[188] = { 10 , 107 };
	m_Offset_LeftBottom[189] = { 26 , 110 };
	m_Offset_LeftBottom[190] = { 12 , 106 };
	m_Offset_LeftBottom[191] = { 10 , 98 };
	m_Offset_LeftBottom[192] = { 9 , 100 };
	m_Offset_LeftBottom[193] = { 4 , 102 };
	m_Offset_LeftBottom[194] = { 0 , 113 };
	m_Offset_LeftBottom[194] = { 0 , 113 };
	m_Offset_LeftBottom[195] = { 0 , 188 };
	m_Offset_LeftBottom[196] = { 33 , 214 };
	m_Offset_LeftBottom[197] = { 101 , 166 };
	m_Offset_LeftBottom[198] = { 75 , 95 };
	m_Offset_LeftBottom[199] = { 71 , 97 };
	m_Offset_LeftBottom[200] = { 24 , 97 };
	m_Offset_LeftBottom[201] = { 82 , 96 };
	m_Offset_LeftBottom[202] = { 91 , 159 };
	m_Offset_LeftBottom[203] = { 88 , 157 };
	m_Offset_LeftBottom[204] = { 83 , 157 };
	m_Offset_LeftBottom[205] = { 4 , 105 };
	m_Offset_LeftBottom[206] = { 45 , 95 };
	m_Offset_LeftBottom[207] = { 46 , 90 };
	m_Offset_LeftBottom[208] = { 60 , 88 };
	m_Offset_LeftBottom[209] = { 60 , 90 };
	m_Offset_LeftBottom[210] = { 96 , 151 };
	m_Offset_LeftBottom[211] = { 0 , 116 };
	m_Offset_LeftBottom[212] = { 55 , 105 };
	m_Offset_LeftBottom[213] = { 6 , 149 };
	m_Offset_LeftBottom[214] = { 0 , 59 };
	m_Offset_LeftBottom[215] = { 0 , 60 };
	m_Offset_LeftBottom[216] = { 8 , 101 };
	m_Offset_LeftBottom[217] = { 0 , 177 };
	m_Offset_LeftBottom[218] = { 33 , 219 };
	m_Offset_LeftBottom[219] = { 100 , 166 };
	m_Offset_LeftBottom[220] = { 76 , 95 };
	m_Offset_LeftBottom[221] = { 70 , 97 };
}
