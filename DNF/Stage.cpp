#include "Stage.h"
#include "OtherObject.h"
#include "Monster.h"
Mat CStage::s_Mat_Monster_Hphud = imread("./ImagePacks2/BaseUI/monster_hphud.png", -1);
Mat CStage::s_Mat_Monster_Hphud_ = imread("./ImagePacks2/BaseUI/monster_hphud_.png", -1);
Mat CStage::s_Mat_Monster_Hp[] =
{
	imread("./ImagePacks2/BaseUI/monster_hp0.png", -1),
	imread("./ImagePacks2/BaseUI/monster_hp1.png", -1),
	imread("./ImagePacks2/BaseUI/monster_hp2.png", -1),
	imread("./ImagePacks2/BaseUI/monster_hp3.png", -1),
	imread("./ImagePacks2/BaseUI/monster_hp4.png", -1)
};
Mat CStage::s_Mat_Monster_Hp_Mask[] =
{
	imread("./ImagePacks2/BaseUI/monster_hp0.png", 0),
	imread("./ImagePacks2/BaseUI/monster_hp1.png", 0),
	imread("./ImagePacks2/BaseUI/monster_hp2.png", 0),
	imread("./ImagePacks2/BaseUI/monster_hp3.png", 0),
	imread("./ImagePacks2/BaseUI/monster_hp4.png", 0)
};

Mat CStage::s_Mat_BossMonster_Hphud = imread("./ImagePacks2/BaseUI/monster_bosshphud.png", -1);
Mat CStage::s_Mat_BossMonster_Hphud_ = imread("./ImagePacks2/BaseUI/monster_bosshphud_.png", -1);
Mat CStage::s_Mat_BossMonster_Hp[] =
{
	imread("./ImagePacks2/BaseUI/monster_bosshp0.png", -1),
	imread("./ImagePacks2/BaseUI/monster_bosshp1.png", -1),
	imread("./ImagePacks2/BaseUI/monster_bosshp2.png", -1),
	imread("./ImagePacks2/BaseUI/monster_bosshp3.png", -1),
	imread("./ImagePacks2/BaseUI/monster_bosshp4.png", -1)
};
Mat CStage::s_Mat_BossMonster_Hp_Mask[] =
{
	imread("./ImagePacks2/BaseUI/monster_bosshp0.png", 0),
	imread("./ImagePacks2/BaseUI/monster_bosshp1.png", 0),
	imread("./ImagePacks2/BaseUI/monster_bosshp2.png", 0),
	imread("./ImagePacks2/BaseUI/monster_bosshp3.png", 0),
	imread("./ImagePacks2/BaseUI/monster_bosshp4.png", 0)
};

Mat CStage::s_Mat_HpNumber[11] = 
{
	imread("./ImagePacks2/Animation/number3/0.png", -1),
	imread("./ImagePacks2/Animation/number3/1.png", -1),
	imread("./ImagePacks2/Animation/number3/2.png", -1),
	imread("./ImagePacks2/Animation/number3/3.png", -1),
	imread("./ImagePacks2/Animation/number3/4.png", -1),
	imread("./ImagePacks2/Animation/number3/5.png", -1),
	imread("./ImagePacks2/Animation/number3/6.png", -1),
	imread("./ImagePacks2/Animation/number3/7.png", -1),
	imread("./ImagePacks2/Animation/number3/8.png", -1),
	imread("./ImagePacks2/Animation/number3/9.png", -1),
	imread("./ImagePacks2/Animation/number3/10.png", -1)
};

void CStage::QuitStage()
{
	for (auto it = m_OtherObjects.begin(); it != m_OtherObjects.end(); it++)
	{
		delete (*it);
	}
	m_OtherObjects.clear();
}

CStage::CStage()
{
	m_TargetMonster = NULL;
	m_TargetMonsterHp = 0;
	m_TargetMonsterHp_Animation = 0;
}


void CStage::Render(Mat& mat)
{
	mat = MatMergeTransparentImage(m_mat_MidBG.colRange(m_ViewX, m_ViewX + s_ViewWidth), m_mat_FarBG.colRange(m_ViewX_far, m_ViewX_far + s_ViewWidth));
	std::vector<CObjectBase*> v(m_OtherObjects.begin(), m_OtherObjects.end());
	v.insert(v.begin(), m_Monsters.begin(), m_Monsters.end());
	v.push_back(m_Character);
	sort(v.begin(), v.end(), &CObjectBase::Cmp);
	for (auto it = v.begin(); it != v.end(); it++)
	{
		(*it)->DoRender(mat, m_ViewX);
	}

	if (m_TargetMonster)
	{
		__ShowMonsterHp(mat, m_TargetMonster->GetHp(), m_TargetMonster->GetHp_Animation(), 300, m_isTargetMonsterBoss);
	}
	else
	{
		__ShowMonsterHp(mat, m_TargetMonsterHp, m_TargetMonsterHp_Animation, 300, m_isTargetMonsterBoss);
	}
}


void CStage::HandleInput(int input)
{
	int x = m_Character->GetX();
	int y = m_Character->GetY();
	int z = m_Character->GetZ();
	int viewspeed = m_Character->GetMovespeed() + 2;
	int viewspeed_ = m_Character->GetMovespeed() - 2;
	if ((x - m_ViewX) * 5 < s_ViewWidth * 2) //x-view < viewWidth*2/5
	{
		//画面向左移动
		if (m_ViewX - viewspeed >= 0)
			m_ViewX -= viewspeed, m_ViewX_far -= m_ViewX_far - viewspeed_ >= 0 ? viewspeed_ : 0;
		else
			m_ViewX = 0;
	}
	else if ((x - m_ViewX) * 5 > s_ViewWidth * 3) //x-view > viewWidth*3/5
	{
		//画面向右移动
		if (m_ViewX + viewspeed < m_StageWidth - s_ViewWidth)
			m_ViewX += viewspeed, m_ViewX_far += viewspeed_;
		else
			m_ViewX = m_StageWidth - s_ViewWidth;
	}
	m_Character->DoHandleInput(input);
}

void CStage::Update(CDungeon* dungeon)
{
	bool quit = false;
	for (auto it = m_OtherObjects.begin(); it != m_OtherObjects.end(); )
	{
		if (!(*it)->Update(*this, dungeon))
		{
			quit = true;
			break;
		}
		if ((*it)->GetComplete())
		{
			delete *it;
			it = m_OtherObjects.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (quit)
	{
		QuitStage();
	}
	bool isbossdead = false;
	for (auto it = m_Monsters.begin(); it != m_Monsters.end(); )
	{
		CMonster* mp = *it;
		mp->Update();
		int reduce = (mp->GetHp_Animation() - mp->GetHp()) / 10;
		reduce = max(reduce, HUD_MONSTER_HPMAXWIDTH / 100);
		mp->SetHp_Animation(mp->GetHp_Animation() - reduce);
		if (mp->GetDead())
		{
			if (mp->GetIsBoss())isbossdead = true;
			if (m_TargetMonster == mp)
				m_TargetMonster = NULL;
			delete mp;
			it = m_Monsters.erase(it);
		}
		else
			it++;
	}
	if (m_TargetMonster)
	{
		m_TargetMonsterHp = m_TargetMonster->GetHp();
		m_TargetMonsterHp_Animation = m_TargetMonster->GetHp_Animation();
		m_Mat_TargetMonsterAvator = m_TargetMonster->GetAvator();
		m_TargetMonsterName = m_TargetMonster->GetName();
		m_isTargetMonsterBoss = m_TargetMonster->GetIsBoss();
	}
	else if (m_TargetMonsterHp == m_TargetMonsterHp_Animation)
	{
		m_TargetMonsterHp = 0;
	}
	else
	{
		int reduce = m_TargetMonsterHp_Animation / 10;
		reduce = max(reduce, HUD_MONSTER_HPMAXWIDTH / 100);
		m_TargetMonsterHp_Animation -= reduce;
		if (m_TargetMonsterHp_Animation < 0)
			m_TargetMonsterHp_Animation = 0;
		else if (m_TargetMonsterHp_Animation < m_TargetMonsterHp)
			m_TargetMonsterHp_Animation = m_TargetMonsterHp;
	}

	if (isbossdead)
	{
		for (auto it = m_Monsters.begin(); it != m_Monsters.end();it++)
		{
			(*it)->SetDead(true);
			delete (*it);
		}
		m_Monsters.clear();
	}
	if (m_Monsters.size() == 0)
	{
		m_IsClearance = true;
		m_TargetMonsterHp = 0;
		m_TargetMonsterHp_Animation = 0;
	}
}

void CStage::SetViewX(int x)
{
	if (x < 0)
		m_ViewX = 0;
	else  if (x >= m_StageWidth - CStage::s_ViewWidth)
		m_ViewX = m_StageWidth - CStage::s_ViewWidth;
	else
		m_ViewX = x;

	m_ViewX_far = m_ViewX / 4;
}


void CStage::SetStageWidth(int width)
{
	m_StageWidth = width;
	if (m_Character)
		m_Character->SetStageWidth(width);
}

void CStage::__ShowMonsterHp(Mat& mat, int hp_cur, int hp_animation, int width, bool isboss)
{
	if (!(hp_cur + hp_animation) || hp_animation < hp_cur)return;
	Mat hud;
	if (isboss)
	{
		width += 100;
		hud = s_Mat_BossMonster_Hphud.clone().colRange(0, 32 + width + 1);
		m_Mat_TargetMonsterAvator.copyTo(hud(Rect(4, 4, m_Mat_TargetMonsterAvator.cols, m_Mat_TargetMonsterAvator.rows)));
	}
	else
	{
		hud = s_Mat_Monster_Hphud.clone().colRange(0, 28 + width + 1);
		m_Mat_TargetMonsterAvator.copyTo(hud(Rect(2, 2, m_Mat_TargetMonsterAvator.cols, m_Mat_TargetMonsterAvator.rows)));
	}
	bool flag = false;
	int hpNum = hp_animation / HUD_MONSTER_HPMAXWIDTH + (hp_animation%HUD_MONSTER_HPMAXWIDTH != 0);
	int top = (hpNum - 1) % 5;
	if (hp_cur < (hpNum - 1)*HUD_MONSTER_HPMAXWIDTH) hp_cur = (hpNum - 1)*HUD_MONSTER_HPMAXWIDTH, flag = true;

	double per1 = (hp_cur - (hpNum - 1)*HUD_MONSTER_HPMAXWIDTH)*1.0 / HUD_MONSTER_HPMAXWIDTH;
	double per2 = (hp_animation - (hpNum - 1)*HUD_MONSTER_HPMAXWIDTH)*1.0 / HUD_MONSTER_HPMAXWIDTH;

	int cols1 = (int)(width * per1);
	int cols2 = (int)(width * per2);

	if (hpNum > 1)
	{
		int second = (hpNum - 2) % 5;
		if (flag == false)
		{
			if (isboss)
				s_Mat_BossMonster_Hp[second].colRange(0, width - cols2)
				.copyTo(hud(Rect(33 + cols2, 3, width - cols2, s_Mat_BossMonster_Hp[second].rows))
					, s_Mat_BossMonster_Hp_Mask[second].colRange(0, width - cols2));
			else
				s_Mat_Monster_Hp[second].colRange(0, width - cols2)
				.copyTo(hud(Rect(29 + cols2, 17, width - cols2, s_Mat_Monster_Hp[second].rows))
					, s_Mat_Monster_Hp_Mask[second].colRange(0, width - cols2));
		}
		else
		{
			if (isboss)
				addWeighted(s_Mat_BossMonster_Hp[second].colRange(0, width - cols2), 0.7,
					hud(Rect(33 + cols2, 3, width - cols2, s_Mat_BossMonster_Hp[second].rows)), 1, 0,
					hud(Rect(33 + cols2, 3, width - cols2, s_Mat_BossMonster_Hp[second].rows)));
			else
				addWeighted(s_Mat_Monster_Hp[second].colRange(0, width - cols2), 0.7,
					hud(Rect(29 + cols2, 17, width - cols2, s_Mat_Monster_Hp[second].rows)), 1, 0,
					hud(Rect(29 + cols2, 17, width - cols2, s_Mat_Monster_Hp[second].rows)));
		}
	}

	Mat leftHp, leftHp_, rightHp, roi;
	if (isboss)
	{
		leftHp = s_Mat_BossMonster_Hp[top].colRange(0, cols1);
		leftHp_ = s_Mat_BossMonster_Hp_Mask[top].colRange(0, cols1);
		leftHp.copyTo(hud(Rect(33, 3, cols1, leftHp.rows)), leftHp_);
		rightHp = s_Mat_BossMonster_Hp[top].colRange(0, cols2 - cols1);
		roi = hud(Rect(33 + cols1, 3, rightHp.cols, rightHp.rows));
	}
	else
	{
		leftHp = s_Mat_Monster_Hp[top].colRange(0, cols1);
		leftHp_ = s_Mat_Monster_Hp_Mask[top].colRange(0, cols1);
		leftHp.copyTo(hud(Rect(29, 17, cols1, leftHp.rows)), leftHp_);
		rightHp = s_Mat_Monster_Hp[top].colRange(0, cols2 - cols1);
		roi = hud(Rect(29 + cols1, 17, rightHp.cols, rightHp.rows));
	}

	addWeighted(rightHp, 0.7, roi, 1, 0, roi);
	for (int i = 0; i < hud.rows; i++)
	{
		uchar* hud_data = hud.ptr<uchar>(i);
		uchar* bg_data = mat.ptr<uchar>(i + 60);

		for (int j = 0; j < hud.cols; j++)
		{
			int k = j * 4;
			if (hud_data[k + 3] > 120)
			{
				bg_data[30 * 4 + k + 0] = hud_data[k + 0];
				bg_data[30 * 4 + k + 1] = hud_data[k + 1];
				bg_data[30 * 4 + k + 2] = hud_data[k + 2];
				bg_data[30 * 4 + k + 3] = hud_data[k + 3];
			}
			if (i >= 15 && i <= 30 && !isboss)
			{
				uchar* right = s_Mat_Monster_Hphud_.ptr<uchar>(i - 15);
				for (int j = 0; j < 12; j++)
				{
					if (i == 30 && j == 9)break;
					bg_data[30 * 4 + hud.cols * 4 + j] = right[j];
				}
			}
			if (i <= 36 && isboss)
			{
				uchar* right = s_Mat_BossMonster_Hphud_.ptr<uchar>(i);
				for (int j = 0; j < 15; j++)
				{
					if (i >= 34 && j == 12)break;
					bg_data[30 * 4 + hud.cols * 4 + j] = right[j];
				}
			}
		}
	}
	std::vector<int> v_num;
	hpNum--;
	while (hpNum)
	{
		v_num.push_back(hpNum%10);
		hpNum /= 10;
	}
	v_num.push_back(10);
	int length = (int)v_num.size();
	int xx = 320;
	int yy = 48;
	if (isboss)
	{
		putText(mat, m_TargetMonsterName, Point(125, 84), CV_FONT_HERSHEY_PLAIN, 0.8, Scalar(255, 255, 255), 1);
		xx = 390;
		yy = 70;
	}
	else
	{
		putText(mat, m_TargetMonsterName, Point(30 + 35, 60 + 10), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1);
	}
	//血条数量数字
	if (length == 1)return;
	int rows = s_Mat_HpNumber[0].rows;
	int cols = s_Mat_HpNumber[0].cols;
	for (int i = 0; i < length; i++)
	{
		for (int r = 0; r < rows; r++)
		{
			uchar* res = mat.ptr<uchar>(r + yy);
			uchar* nu = s_Mat_HpNumber[v_num[length - i - 1]].ptr<uchar>(r);
			for (int c = 0; c < cols; c++)
			{
				int k = c * 4;
				if (nu[k + 3])
				{
					if (xx * 4 + i * (cols)* 4 + k < 0 || xx * 4 + i * (cols)* 4 + k >= 4 * mat.cols)break;
					res[xx * 4 + i * (cols)* 4 + k] = nu[k];
					res[xx * 4 + i * (cols)* 4 + k + 1] = nu[k + 1];
					res[xx * 4 + i * (cols)* 4 + k + 2] = nu[k + 2];
					res[xx * 4 + i * (cols)* 4 + k + 3] = nu[k + 3];
				}
			}
		}
	}
}


//将srcImage中透明的地方用dstImage合并
Mat CStage::MatMergeTransparentImage(Mat& srcImage, Mat& dstImagePtr)
{
	Mat result(srcImage.rows, srcImage.cols, srcImage.type());
	int div = 4;
	int rows_src = srcImage.rows;
	int rows_dst = dstImagePtr.rows;
	// 将4通道转换为1通道
	int cols_src = srcImage.cols*srcImage.channels();
	int cols_dst = dstImagePtr.cols*dstImagePtr.channels();
	for (int k = 0; k < rows_src; k++)
	{
		uchar* resultPtr = result.ptr<uchar>(k);
		uchar* scrPtr = srcImage.ptr<uchar>(k);
		uchar* dstPtr = dstImagePtr.ptr<uchar>(k < rows_dst ? k : rows_dst - 1);
		for (int j = 0; j < cols_src; j++)
		{
			if (scrPtr[j] == 0 && j < cols_dst)
				resultPtr[j] = dstPtr[j];
			else
				resultPtr[j] = scrPtr[j];
		}
	}
	return result;
}
