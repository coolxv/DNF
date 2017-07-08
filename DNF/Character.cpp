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
	m_isBackJumping = false;
	m_IsAttacking = false;
	m_Dead = false;
	m_Thick = 25;
	m_Width = 35;
	m_Height = 115;
	
	m_HP = CHARACTER_HP;
	m_MP = CHARACTER_MP;

	m_PreReplyHpMp = 0;

	m_PreEffect_A = 0;
	m_PreEffect_Z = 0;
	m_PreEffect_S = 0;
	m_PreEffect_D = 0;
}


CCharacter::~CCharacter()
{
}


CCharacterState* CCharacter::GetCurState()
{
	return m_State;
}

void CCharacter::SetState(CCharacterState * p)
{
	if (m_Dead && typeid(*p) != typeid(CharacterStandingState))
	{
		return;
	}
	else if (p)
	{
		m_State = p;
		m_State->InitState(*this);
	}
}


void CCharacter::SetAnimationEffectsVector(std::vector<CAnimationEffect*>* v)
{
	m_Vector_AnimationEffects = v;
}

std::vector<CAnimationEffect*>* CCharacter::GetAnimationEffects()
{
	return m_Vector_AnimationEffects;
}

void CCharacter::DoRender(Mat& mat, int viewX)
{
	Mat body = m_Orientation == DIR_RIGHT ? m_Mat_Body[m_State->GetMatId()] : m_Mat_LBody[m_State->GetMatId()];
	Mat body_mask = m_Orientation == DIR_RIGHT ? m_Mat_Body_Mask[m_State->GetMatId()] : m_Mat_LBody_Mask[m_State->GetMatId()]; //当前角色的资源图
	int tx = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].x : m_Offset_LeftBottom_Left[m_State->GetMatId()].x;
	int ty = m_Orientation == DIR_RIGHT ? m_Offset_LeftBottom[m_State->GetMatId()].y : m_Offset_LeftBottom_Left[m_State->GetMatId()].y;
	Mat ROI;
	int xx = m_X - viewX - tx; //相对坐标
	int yy = m_Y - ty - m_Z / 2 + m_OffsetY;
	Render(mat, viewX, m_ViewWidth,m_ViewHeight, m_OffsetY, xx, yy, body, body_mask);
}

void CCharacter::DoHandleInput(int input)
{
	m_State->DoHandleInput(*this, input);
}

void CCharacter::UpdateState()
{
	clock_t cur = clock();
	if (cur - m_PreReplyHpMp >= 5000 && m_Dead==false)
	{
		SetHp(m_HP+ CHARACTER_HP * 5 / 100);
		SetMp(m_MP + CHARACTER_MP * 5 / 100);
		m_PreReplyHpMp = cur;
	}
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
		p = CHARACTER_EFFECT_POWER_X;
		break;
	case EFFECTZ:
		p = CHARACTER_EFFECT_POWER_Z;
		break;
	case EFFECTS:
		p = CHARACTER_EFFECT_POWER_S1;
	case EFFECTS2:
		p = CHARACTER_EFFECT_POWER_S2;
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
	if (x >= 10 && x <= m_StageWidth -m_Width)
	{
		m_X = x;
		return true;
	}
	return false;
}
bool CCharacter::SetY(int y)
{
	if (y >= 10 && y <= m_ViewHeight- 10)
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
	{
		m_HP = 0;
		SetState(&s_Dead);
	}
	else if (hp>CHARACTER_HP)
		m_HP = CHARACTER_HP;
	else
		m_HP = hp;
}


void CCharacter::SetMp(int mp)
{
	if (mp <= 0)
		m_MP = CHARACTER_MP;
	else if (mp > CHARACTER_MP)
		m_MP = CHARACTER_MP;
	else
		m_MP = mp;
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

	m_Offset_LeftBottom_Left[0] = Point(65, 114);	m_Offset_LeftBottom_Left[1] = Point(65, 114);	m_Offset_LeftBottom_Left[2] = Point(65, 114);	m_Offset_LeftBottom_Left[3] = Point(65, 114);	m_Offset_LeftBottom_Left[4] = Point(65, 114);	m_Offset_LeftBottom_Left[5] = Point(65, 114);	m_Offset_LeftBottom_Left[6] = Point(65, 114);	m_Offset_LeftBottom_Left[7] = Point(65, 114);	m_Offset_LeftBottom_Left[8] = Point(65, 114);	m_Offset_LeftBottom_Left[9] = Point(58, 113);	m_Offset_LeftBottom_Left[10] = Point(58, 113);	m_Offset_LeftBottom_Left[11] = Point(58, 113);	m_Offset_LeftBottom_Left[12] = Point(58, 113);	m_Offset_LeftBottom_Left[13] = Point(81, 112);	m_Offset_LeftBottom_Left[14] = Point(73, 110);	m_Offset_LeftBottom_Left[15] = Point(64, 110);	m_Offset_LeftBottom_Left[16] = Point(67, 110);	m_Offset_LeftBottom_Left[17] = Point(77, 110);	m_Offset_LeftBottom_Left[18] = Point(90, 110);	m_Offset_LeftBottom_Left[19] = Point(95, 108);	m_Offset_LeftBottom_Left[20] = Point(91, 111);	m_Offset_LeftBottom_Left[21] = Point(87, 113);	m_Offset_LeftBottom_Left[22] = Point(87, 113);	m_Offset_LeftBottom_Left[23] = Point(30, 94);	m_Offset_LeftBottom_Left[24] = Point(29, 94);	m_Offset_LeftBottom_Left[25] = Point(4, 92);	m_Offset_LeftBottom_Left[26] = Point(30, 91);	m_Offset_LeftBottom_Left[27] = Point(28, 91);	m_Offset_LeftBottom_Left[28] = Point(0, 91);	m_Offset_LeftBottom_Left[29] = Point(24, 97);	m_Offset_LeftBottom_Left[30] = Point(4, 90);	m_Offset_LeftBottom_Left[31] = Point(10, 82);	m_Offset_LeftBottom_Left[32] = Point(12, 71);	m_Offset_LeftBottom_Left[33] = Point(123, 107);	m_Offset_LeftBottom_Left[34] = Point(94, 109);	m_Offset_LeftBottom_Left[35] = Point(7, 105);	m_Offset_LeftBottom_Left[36] = Point(45, 97);	m_Offset_LeftBottom_Left[37] = Point(30, 140);	m_Offset_LeftBottom_Left[38] = Point(38, 124);	m_Offset_LeftBottom_Left[39] = Point(62, 122);	m_Offset_LeftBottom_Left[40] = Point(65, 124);	m_Offset_LeftBottom_Left[41] = Point(46, 97);	m_Offset_LeftBottom_Left[42] = Point(67, 95);	m_Offset_LeftBottom_Left[43] = Point(12, 91);	m_Offset_LeftBottom_Left[44] = Point(116, 170);	m_Offset_LeftBottom_Left[45] = Point(76, 155);	m_Offset_LeftBottom_Left[46] = Point(16, 175);	m_Offset_LeftBottom_Left[47] = Point(27, 158);	m_Offset_LeftBottom_Left[48] = Point(49, 105);	m_Offset_LeftBottom_Left[49] = Point(6, 95);	m_Offset_LeftBottom_Left[50] = Point(119, 132);	m_Offset_LeftBottom_Left[51] = Point(116, 151);	m_Offset_LeftBottom_Left[52] = Point(87, 146);	m_Offset_LeftBottom_Left[53] = Point(20, 143);	m_Offset_LeftBottom_Left[54] = Point(26, 127);	m_Offset_LeftBottom_Left[55] = Point(103, 101);	m_Offset_LeftBottom_Left[56] = Point(73, 102);	m_Offset_LeftBottom_Left[57] = Point(40, 100);	m_Offset_LeftBottom_Left[58] = Point(6, 102);	m_Offset_LeftBottom_Left[59] = Point(0, 126);	m_Offset_LeftBottom_Left[60] = Point(4, 151);	m_Offset_LeftBottom_Left[61] = Point(106, 122);	m_Offset_LeftBottom_Left[62] = Point(97, 65);	m_Offset_LeftBottom_Left[63] = Point(85, 61);	m_Offset_LeftBottom_Left[64] = Point(54, 108);	m_Offset_LeftBottom_Left[65] = Point(11, 89);	m_Offset_LeftBottom_Left[66] = Point(123, 111);	m_Offset_LeftBottom_Left[67] = Point(114, 113);	m_Offset_LeftBottom_Left[68] = Point(107, 103);	m_Offset_LeftBottom_Left[69] = Point(36, 152);	m_Offset_LeftBottom_Left[70] = Point(118, 86);	m_Offset_LeftBottom_Left[71] = Point(8, 70);	m_Offset_LeftBottom_Left[72] = Point(8, 70);	m_Offset_LeftBottom_Left[73] = Point(12, 94);
	m_Offset_LeftBottom_Left[74] = Point(12, 90);	m_Offset_LeftBottom_Left[75] = Point(57, 156);	m_Offset_LeftBottom_Left[76] = Point(4, 159);	/*m_Offset_LeftBottom_Left[74] = Point( 11, 117 );	m_Offset_LeftBottom_Left[75] = Point( 64, 161 );	m_Offset_LeftBottom_Left[76] = Point( 0, 159 };*/

	m_Offset_LeftBottom_Left[77] = Point(6, 150);	m_Offset_LeftBottom_Left[78] = Point(100, 184);	m_Offset_LeftBottom_Left[79] = Point(85, 192);	m_Offset_LeftBottom_Left[80] = Point(40, 196);	m_Offset_LeftBottom_Left[81] = Point(0, 112);	m_Offset_LeftBottom_Left[82] = Point(0, 130);	m_Offset_LeftBottom_Left[83] = Point(5, 132);	m_Offset_LeftBottom_Left[84] = Point(6, 116);	m_Offset_LeftBottom_Left[85] = Point(127, 158);	m_Offset_LeftBottom_Left[86] = Point(115, 80);	m_Offset_LeftBottom_Left[87] = Point(80, 78);	m_Offset_LeftBottom_Left[88] = Point(134, 154);	m_Offset_LeftBottom_Left[89] = Point(111, 55);	m_Offset_LeftBottom_Left[90] = Point(112, 56);
	m_Offset_LeftBottom_Left[91] = Point(0, 110);	m_Offset_LeftBottom_Left[92] = Point(4, 126);	m_Offset_LeftBottom_Left[93] = Point(4, 132);	m_Offset_LeftBottom_Left[94] = Point(99, 134);	m_Offset_LeftBottom_Left[95] = Point(8, 110);	m_Offset_LeftBottom_Left[96] = Point(6, 111);
	//m_Offset_LeftBottom_Left[91] = Point( 0, 114 );	//m_Offset_LeftBottom_Left[92] = Point( 110, 126 );	//m_Offset_LeftBottom_Left[93] = Point( 110, 132 );	//m_Offset_LeftBottom_Left[94] = Point( 119, 184 );	//m_Offset_LeftBottom_Left[95] = Point( 75, 135 );	//m_Offset_LeftBottom_Left[96] = Point( 74, 124 );
	m_Offset_LeftBottom_Left[97] = Point(4, 95);	m_Offset_LeftBottom_Left[98] = Point(18, 128);	m_Offset_LeftBottom_Left[99] = Point(72, 77);	m_Offset_LeftBottom_Left[100] = Point(109, 91);	m_Offset_LeftBottom_Left[101] = Point(117, 89);	m_Offset_LeftBottom_Left[102] = Point(114, 91);	m_Offset_LeftBottom_Left[103] = Point(6, 110);	m_Offset_LeftBottom_Left[104] = Point(46, 118);	m_Offset_LeftBottom_Left[105] = Point(66, 93);	m_Offset_LeftBottom_Left[106] = Point(122, 89);	m_Offset_LeftBottom_Left[107] = Point(125, 86);	m_Offset_LeftBottom_Left[108] = Point(125, 86);	m_Offset_LeftBottom_Left[109] = Point(65, 110);	m_Offset_LeftBottom_Left[110] = Point(27, 98);	m_Offset_LeftBottom_Left[111] = Point(6, 120);	m_Offset_LeftBottom_Left[112] = Point(14, 111);	m_Offset_LeftBottom_Left[113] = Point(14, 121);	m_Offset_LeftBottom_Left[114] = Point(89, 111);	m_Offset_LeftBottom_Left[115] = Point(77, 88);	m_Offset_LeftBottom_Left[116] = Point(23, 75);	m_Offset_LeftBottom_Left[117] = Point(28, 73);	m_Offset_LeftBottom_Left[118] = Point(4, 109);	m_Offset_LeftBottom_Left[119] = Point(6, 116);	m_Offset_LeftBottom_Left[120] = Point(5, 116);	m_Offset_LeftBottom_Left[121] = Point(4, 135);	m_Offset_LeftBottom_Left[122] = Point(22, 189);	m_Offset_LeftBottom_Left[123] = Point(96, 169);	m_Offset_LeftBottom_Left[124] = Point(117, 134);	m_Offset_LeftBottom_Left[125] = Point(58, 110);	m_Offset_LeftBottom_Left[126] = Point(61, 108);	m_Offset_LeftBottom_Left[127] = Point(61, 111);	m_Offset_LeftBottom_Left[128] = Point(63, 109);	m_Offset_LeftBottom_Left[129] = Point(59, 111);	m_Offset_LeftBottom_Left[130] = Point(55, 111);	m_Offset_LeftBottom_Left[131] = Point(50, 114);	m_Offset_LeftBottom_Left[132] = Point(62, 113);	m_Offset_LeftBottom_Left[133] = Point(60, 114);	m_Offset_LeftBottom_Left[134] = Point(61, 113);	m_Offset_LeftBottom_Left[135] = Point(62, 119);	m_Offset_LeftBottom_Left[136] = Point(57, 114);	m_Offset_LeftBottom_Left[137] = Point(52, 111);	m_Offset_LeftBottom_Left[138] = Point(51, 114);	m_Offset_LeftBottom_Left[139] = Point(54, 95);	m_Offset_LeftBottom_Left[140] = Point(54, 95);	m_Offset_LeftBottom_Left[141] = Point(4, 113);	m_Offset_LeftBottom_Left[142] = Point(5, 107);	m_Offset_LeftBottom_Left[143] = Point(53, 40);	m_Offset_LeftBottom_Left[144] = Point(66, 56);	m_Offset_LeftBottom_Left[145] = Point(73, 100);	m_Offset_LeftBottom_Left[146] = Point(54, 92);	m_Offset_LeftBottom_Left[147] = Point(56, 87);	m_Offset_LeftBottom_Left[148] = Point(54, 91);	m_Offset_LeftBottom_Left[149] = Point(54, 92);	m_Offset_LeftBottom_Left[150] = Point(55, 96);	m_Offset_LeftBottom_Left[151] = Point(10, 130);	m_Offset_LeftBottom_Left[152] = Point(10, 130);	m_Offset_LeftBottom_Left[153] = Point(10, 130);	m_Offset_LeftBottom_Left[154] = Point(10, 130);	m_Offset_LeftBottom_Left[155] = Point(10, 130);	m_Offset_LeftBottom_Left[156] = Point(10, 130);	m_Offset_LeftBottom_Left[157] = Point(10, 130);	m_Offset_LeftBottom_Left[158] = Point(10, 130);	m_Offset_LeftBottom_Left[159] = Point(121, 105);	m_Offset_LeftBottom_Left[160] = Point(156, 174);	m_Offset_LeftBottom_Left[161] = Point(6, 168);	m_Offset_LeftBottom_Left[162] = Point(93, 119);	m_Offset_LeftBottom_Left[163] = Point(6, 129);	m_Offset_LeftBottom_Left[164] = Point(12, 153);	m_Offset_LeftBottom_Left[165] = Point(146, 176);	m_Offset_LeftBottom_Left[166] = Point(96, 79);	m_Offset_LeftBottom_Left[167] = Point(47, 88);	m_Offset_LeftBottom_Left[168] = Point(140, 81);	m_Offset_LeftBottom_Left[169] = Point(170, 72);	m_Offset_LeftBottom_Left[170] = Point(107, 164);	m_Offset_LeftBottom_Left[171] = Point(134, 145);	m_Offset_LeftBottom_Left[172] = Point(134, 70);	m_Offset_LeftBottom_Left[173] = Point(164, 70);	m_Offset_LeftBottom_Left[174] = Point(37, 99);	m_Offset_LeftBottom_Left[175] = Point(44, 102);	m_Offset_LeftBottom_Left[176] = Point(51, 87);	m_Offset_LeftBottom_Left[177] = Point(95, 79);	m_Offset_LeftBottom_Left[178] = Point(146, 75);	m_Offset_LeftBottom_Left[179] = Point(188, 115);	m_Offset_LeftBottom_Left[180] = Point(183, 112);	m_Offset_LeftBottom_Left[181] = Point(142, 119);	m_Offset_LeftBottom_Left[182] = Point(68, 90);	m_Offset_LeftBottom_Left[183] = Point(27, 84);	m_Offset_LeftBottom_Left[184] = Point(28, 62);	m_Offset_LeftBottom_Left[185] = Point(55, 102);	m_Offset_LeftBottom_Left[186] = Point(54, 107);	m_Offset_LeftBottom_Left[187] = Point(57, 103);	m_Offset_LeftBottom_Left[188] = Point(56, 102);	m_Offset_LeftBottom_Left[189] = Point(31, 106);	m_Offset_LeftBottom_Left[190] = Point(53, 102);	m_Offset_LeftBottom_Left[191] = Point(114, 98);	m_Offset_LeftBottom_Left[192] = Point(118, 96);	m_Offset_LeftBottom_Left[193] = Point(114, 97);	m_Offset_LeftBottom_Left[194] = Point(108, 113);	m_Offset_LeftBottom_Left[195] = Point(55, 184);	m_Offset_LeftBottom_Left[196] = Point(39, 214);	m_Offset_LeftBottom_Left[197] = Point(15, 161);	m_Offset_LeftBottom_Left[198] = Point(16, 90);	m_Offset_LeftBottom_Left[199] = Point(17, 94);	m_Offset_LeftBottom_Left[200] = Point(46, 94);	m_Offset_LeftBottom_Left[201] = Point(24, 94);	m_Offset_LeftBottom_Left[202] = Point(68, 155);	m_Offset_LeftBottom_Left[203] = Point(55, 152);	m_Offset_LeftBottom_Left[204] = Point(0, 153);	m_Offset_LeftBottom_Left[205] = Point(103, 100);	m_Offset_LeftBottom_Left[206] = Point(25, 94);	m_Offset_LeftBottom_Left[207] = Point(29, 90);	m_Offset_LeftBottom_Left[208] = Point(27, 88);	m_Offset_LeftBottom_Left[209] = Point(28, 87);	m_Offset_LeftBottom_Left[210] = Point(14, 151);	m_Offset_LeftBottom_Left[211] = Point(139, 116);	m_Offset_LeftBottom_Left[212] = Point(6, 103);	m_Offset_LeftBottom_Left[213] = Point(110, 144);	m_Offset_LeftBottom_Left[214] = Point(97, 52);	m_Offset_LeftBottom_Left[215] = Point(98, 52);	m_Offset_LeftBottom_Left[216] = Point(97, 96);	m_Offset_LeftBottom_Left[217] = Point(105, 177);	m_Offset_LeftBottom_Left[218] = Point(141, 216);	m_Offset_LeftBottom_Left[219] = Point(13, 166);	m_Offset_LeftBottom_Left[220] = Point(17, 89);	m_Offset_LeftBottom_Left[221] = Point(19, 92);
	m_Offset_LeftBottom[0] = Point(20, 114);	m_Offset_LeftBottom[1] = Point(20, 114);	m_Offset_LeftBottom[2] = Point(20, 114);	m_Offset_LeftBottom[3] = Point(20, 114);	m_Offset_LeftBottom[4] = Point(20, 114);	m_Offset_LeftBottom[5] = Point(20, 114);	m_Offset_LeftBottom[6] = Point(20, 114);	m_Offset_LeftBottom[7] = Point(20, 114);	m_Offset_LeftBottom[8] = Point(20, 114);	m_Offset_LeftBottom[9] = Point(28, 113);	m_Offset_LeftBottom[10] = Point(28, 113);	m_Offset_LeftBottom[11] = Point(28, 113);	m_Offset_LeftBottom[12] = Point(28, 113);	m_Offset_LeftBottom[13] = Point(10, 112);	m_Offset_LeftBottom[14] = Point(0, 110);	m_Offset_LeftBottom[15] = Point(0, 113);	m_Offset_LeftBottom[16] = Point(0, 113);	m_Offset_LeftBottom[17] = Point(0, 113);	m_Offset_LeftBottom[18] = Point(0, 113);	m_Offset_LeftBottom[19] = Point(0, 111);	m_Offset_LeftBottom[20] = Point(0, 111);	m_Offset_LeftBottom[21] = Point(0, 113);	m_Offset_LeftBottom[22] = Point(0, 113);	m_Offset_LeftBottom[23] = Point(0, 94);	m_Offset_LeftBottom[24] = Point(0, 94);	m_Offset_LeftBottom[25] = Point(0, 92);	m_Offset_LeftBottom[26] = Point(0, 91);	m_Offset_LeftBottom[27] = Point(0, 91);	m_Offset_LeftBottom[28] = Point(0, 91);	m_Offset_LeftBottom[29] = Point(36, 97);	m_Offset_LeftBottom[30] = Point(110, 90);	m_Offset_LeftBottom[31] = Point(51, 86);	m_Offset_LeftBottom[32] = Point(44, 77);	m_Offset_LeftBottom[33] = Point(26, 107);	m_Offset_LeftBottom[34] = Point(36, 109);	m_Offset_LeftBottom[35] = Point(56, 108);	m_Offset_LeftBottom[36] = Point(10, 97);	m_Offset_LeftBottom[37] = Point(13, 140);	m_Offset_LeftBottom[38] = Point(25, 124);	m_Offset_LeftBottom[39] = Point(27, 122);	m_Offset_LeftBottom[40] = Point(25, 127);	m_Offset_LeftBottom[41] = Point(10, 97);	m_Offset_LeftBottom[42] = Point(25, 95);	m_Offset_LeftBottom[43] = Point(91, 90);	m_Offset_LeftBottom[44] = Point(0, 171);	m_Offset_LeftBottom[45] = Point(26, 151);	m_Offset_LeftBottom[46] = Point(9, 172);	m_Offset_LeftBottom[47] = Point(0, 159);
	m_Offset_LeftBottom[48] = Point(23, 109);	m_Offset_LeftBottom[49] = Point(81, 99);	m_Offset_LeftBottom[50] = Point(0, 138);	m_Offset_LeftBottom[51] = Point(0, 151);	m_Offset_LeftBottom[52] = Point(0, 151);	m_Offset_LeftBottom[53] = Point(31, 146);	m_Offset_LeftBottom[54] = Point(38, 130);	m_Offset_LeftBottom[55] = Point(0, 104);	m_Offset_LeftBottom[56] = Point(0, 106);	m_Offset_LeftBottom[57] = Point(4, 105);	m_Offset_LeftBottom[58] = Point(72, 102);	m_Offset_LeftBottom[59] = Point(107, 129);	m_Offset_LeftBottom[60] = Point(104, 151);	m_Offset_LeftBottom[61] = Point(0, 123);	m_Offset_LeftBottom[62] = Point(0, 65);	m_Offset_LeftBottom[63] = Point(0, 66);
	m_Offset_LeftBottom[64] = Point(11, 108);	m_Offset_LeftBottom[65] = Point(100, 82);	m_Offset_LeftBottom[66] = Point(0, 114);	m_Offset_LeftBottom[67] = Point(0, 113);	m_Offset_LeftBottom[68] = Point(0, 103);	m_Offset_LeftBottom[69] = Point(0, 150);	m_Offset_LeftBottom[70] = Point(67, 85);	m_Offset_LeftBottom[71] = Point(50, 71);	m_Offset_LeftBottom[72] = Point(46, 69);	m_Offset_LeftBottom[73] = Point(35, 94);
	m_Offset_LeftBottom[74] = Point(6, 92);	m_Offset_LeftBottom[75] = Point(77, 161);	m_Offset_LeftBottom[76] = Point(91, 159);	/*m_Offset_LeftBottom[74] = Point( 8, 117 );	m_Offset_LeftBottom[75] = Point( 82, 161 );	m_Offset_LeftBottom[76] = Point( 96, 159 };*/

	m_Offset_LeftBottom[77] = Point(91, 150);	m_Offset_LeftBottom[78] = Point(0, 192);	m_Offset_LeftBottom[79] = Point(0, 200);	m_Offset_LeftBottom[80] = Point(0, 200);	m_Offset_LeftBottom[81] = Point(52, 112);	m_Offset_LeftBottom[82] = Point(55, 130);	m_Offset_LeftBottom[83] = Point(52, 132);	m_Offset_LeftBottom[84] = Point(54, 116);	m_Offset_LeftBottom[85] = Point(0, 159);	m_Offset_LeftBottom[86] = Point(0, 79);	m_Offset_LeftBottom[87] = Point(0, 80);	m_Offset_LeftBottom[88] = Point(0, 150);	m_Offset_LeftBottom[89] = Point(0, 55);	m_Offset_LeftBottom[90] = Point(0, 56);
	m_Offset_LeftBottom[91] = Point(59, 114);	m_Offset_LeftBottom[92] = Point(75, 126);	m_Offset_LeftBottom[93] = Point(75, 132);	m_Offset_LeftBottom[94] = Point(78, 134);	m_Offset_LeftBottom[95] = Point(81, 109);	m_Offset_LeftBottom[96] = Point(80, 109);
	//m_Offset_LeftBottom[91] = Point( 63, 114 );	//m_Offset_LeftBottom[92] = Point( 77, 126 );	//m_Offset_LeftBottom[93] = Point( 75, 132 );	//m_Offset_LeftBottom[94] = Point( 79, 184 );	//m_Offset_LeftBottom[95] = Point( 83, 135 );	//m_Offset_LeftBottom[96] = Point( 82, 124 );
	m_Offset_LeftBottom[97] = Point(69, 96);	m_Offset_LeftBottom[98] = Point(108, 128);	m_Offset_LeftBottom[99] = Point(69, 84);	m_Offset_LeftBottom[100] = Point(0, 91);	m_Offset_LeftBottom[101] = Point(0, 96);	m_Offset_LeftBottom[103] = Point(44, 110);	m_Offset_LeftBottom[104] = Point(35, 118);	m_Offset_LeftBottom[105] = Point(11, 100);	m_Offset_LeftBottom[106] = Point(0, 100);	m_Offset_LeftBottom[107] = Point(4, 95);	m_Offset_LeftBottom[108] = Point(5, 95);	m_Offset_LeftBottom[109] = Point(0, 111);	m_Offset_LeftBottom[110] = Point(8, 99);	m_Offset_LeftBottom[111] = Point(0, 114);	m_Offset_LeftBottom[112] = Point(31, 108);	m_Offset_LeftBottom[113] = Point(45, 123);	m_Offset_LeftBottom[114] = Point(52, 111);	m_Offset_LeftBottom[115] = Point(95, 86);	m_Offset_LeftBottom[116] = Point(69, 76);	m_Offset_LeftBottom[117] = Point(72, 74);	m_Offset_LeftBottom[118] = Point(30, 105);	m_Offset_LeftBottom[119] = Point(0, 117);	m_Offset_LeftBottom[120] = Point(0, 115);	m_Offset_LeftBottom[121] = Point(77, 135);	m_Offset_LeftBottom[122] = Point(36, 190);	m_Offset_LeftBottom[123] = Point(16, 173);	m_Offset_LeftBottom[124] = Point(11, 134);	m_Offset_LeftBottom[125] = Point(24, 113);	m_Offset_LeftBottom[126] = Point(19, 114);	m_Offset_LeftBottom[127] = Point(19, 114);	m_Offset_LeftBottom[128] = Point(22, 113);	m_Offset_LeftBottom[129] = Point(24, 114);	m_Offset_LeftBottom[130] = Point(28, 114);	m_Offset_LeftBottom[131] = Point(26, 114);	m_Offset_LeftBottom[132] = Point(24, 110);	m_Offset_LeftBottom[133] = Point(25, 114);	m_Offset_LeftBottom[134] = Point(25, 113);	m_Offset_LeftBottom[135] = Point(23, 119);	m_Offset_LeftBottom[136] = Point(27, 111);	m_Offset_LeftBottom[137] = Point(28, 114);	m_Offset_LeftBottom[138] = Point(28, 114);	m_Offset_LeftBottom[139] = Point(13, 95);	m_Offset_LeftBottom[140] = Point(15, 101);	m_Offset_LeftBottom[141] = Point(0, 113);	m_Offset_LeftBottom[142] = Point(4, 105);	m_Offset_LeftBottom[143] = Point(0, 40);	m_Offset_LeftBottom[144] = Point(4, 57);	m_Offset_LeftBottom[145] = Point(0, 102);	m_Offset_LeftBottom[146] = Point(5, 97);	m_Offset_LeftBottom[147] = Point(5, 92);	m_Offset_LeftBottom[148] = Point(6, 91);	m_Offset_LeftBottom[149] = Point(7, 95);	m_Offset_LeftBottom[150] = Point(4, 100);	m_Offset_LeftBottom[150] = Point(0, 100);
	m_Offset_LeftBottom[151] = Point(29, 130);	m_Offset_LeftBottom[152] = Point(29, 130);	m_Offset_LeftBottom[153] = Point(29, 130);	m_Offset_LeftBottom[154] = Point(29, 130);	m_Offset_LeftBottom[155] = Point(29, 130);	m_Offset_LeftBottom[156] = Point(29, 130);	m_Offset_LeftBottom[157] = Point(29, 130);	m_Offset_LeftBottom[158] = Point(29, 130);
	m_Offset_LeftBottom[159] = Point(18, 105);	m_Offset_LeftBottom[160] = Point(20, 174);	m_Offset_LeftBottom[161] = Point(7, 168);	m_Offset_LeftBottom[162] = Point(0, 119);	m_Offset_LeftBottom[163] = Point(84, 129);	m_Offset_LeftBottom[164] = Point(75, 153);	m_Offset_LeftBottom[165] = Point(4, 177);	m_Offset_LeftBottom[166] = Point(4, 78);	m_Offset_LeftBottom[167] = Point(5, 88);	m_Offset_LeftBottom[168] = Point(0, 81);	m_Offset_LeftBottom[169] = Point(4, 74);	m_Offset_LeftBottom[170] = Point(4, 164);	m_Offset_LeftBottom[170] = Point(0, 164);	m_Offset_LeftBottom[171] = Point(0, 147);	m_Offset_LeftBottom[172] = Point(0, 67);	m_Offset_LeftBottom[172] = Point(0, 70);	m_Offset_LeftBottom[173] = Point(0, 73);	m_Offset_LeftBottom[174] = Point(6, 103);	m_Offset_LeftBottom[175] = Point(4, 106);	m_Offset_LeftBottom[176] = Point(6, 95);	m_Offset_LeftBottom[177] = Point(68, 82);	m_Offset_LeftBottom[178] = Point(94, 73);	m_Offset_LeftBottom[179] = Point(76, 116);	m_Offset_LeftBottom[180] = Point(51, 112);	m_Offset_LeftBottom[181] = Point(62, 110);	m_Offset_LeftBottom[182] = Point(75, 96);	m_Offset_LeftBottom[183] = Point(72, 87);	m_Offset_LeftBottom[184] = Point(17, 63);	m_Offset_LeftBottom[185] = Point(9, 106);	m_Offset_LeftBottom[186] = Point(10, 107);	m_Offset_LeftBottom[187] = Point(10, 105);	m_Offset_LeftBottom[188] = Point(10, 104);	m_Offset_LeftBottom[188] = Point(10, 107);	m_Offset_LeftBottom[189] = Point(26, 110);	m_Offset_LeftBottom[190] = Point(12, 106);	m_Offset_LeftBottom[191] = Point(10, 98);	m_Offset_LeftBottom[192] = Point(9, 100);	m_Offset_LeftBottom[193] = Point(4, 102);	m_Offset_LeftBottom[194] = Point(0, 113);	m_Offset_LeftBottom[194] = Point(0, 113);	m_Offset_LeftBottom[195] = Point(0, 188);	m_Offset_LeftBottom[196] = Point(33, 214);	m_Offset_LeftBottom[197] = Point(101, 166);	m_Offset_LeftBottom[198] = Point(75, 95);	m_Offset_LeftBottom[199] = Point(71, 97);	m_Offset_LeftBottom[200] = Point(24, 97);	m_Offset_LeftBottom[201] = Point(82, 96);	m_Offset_LeftBottom[202] = Point(91, 159);	m_Offset_LeftBottom[203] = Point(88, 157);	m_Offset_LeftBottom[204] = Point(83, 157);	m_Offset_LeftBottom[205] = Point(4, 105);	m_Offset_LeftBottom[206] = Point(45, 95);	m_Offset_LeftBottom[207] = Point(46, 90);	m_Offset_LeftBottom[208] = Point(60, 88);	m_Offset_LeftBottom[209] = Point(60, 90);	m_Offset_LeftBottom[210] = Point(96, 151);	m_Offset_LeftBottom[211] = Point(0, 116);	m_Offset_LeftBottom[212] = Point(55, 105);	m_Offset_LeftBottom[213] = Point(6, 149);	m_Offset_LeftBottom[214] = Point(0, 59);	m_Offset_LeftBottom[215] = Point(0, 60);	m_Offset_LeftBottom[216] = Point(8, 101);	m_Offset_LeftBottom[217] = Point(0, 177);	m_Offset_LeftBottom[218] = Point(33, 219);	m_Offset_LeftBottom[219] = Point(100, 166);	m_Offset_LeftBottom[220] = Point(76, 95);	m_Offset_LeftBottom[221] = Point(70, 97);
}
