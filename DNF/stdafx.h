// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<Windows.h>
#include<iostream>
#include<vector>
#include<time.h>
#define INF 0x4fffffff
#define RANDNUM(a,b)  (rand() % (b - a+1) + a); 

#define KEY_MOVE_RIGHT 0x27
#define KEY_MOVE_LEFT 0x25	
#define KEY_MOVE_UP 0x26
#define KEY_MOVE_DOWN 0x28
#define KEY_ATTACK 'X'
#define KEY_JUMP 'C'
#define KEY_JUMPBACK 'A'
#define KEY_EFFECTD 'D'
#define KEY_EFFECTZ 'Z' //上挑
#define KEY_EFFECTS 'S' 

#define EVENT_BEATTACK 8573
#define EVENT_BEATTACK_Knock 8574


#define HUD_MONSTER_HPMAXWIDTH 10000

#define MONSTER_GOBLIN_HP 2000000
#define MONSTER_GOBLIN_ATTACKPOWER 2000
#define MONSTER_GOBLIN_ATTACKPOWER_ 2200
#define MONSTER_GOBLIN_ARMOR 400


#define MONSTER_BOSSGOBLIN_HP 40000
#define MONSTER_BOSSGOBLIN_ATTACKPOWER 3500
#define MONSTER_BOSSGOBLIN_ATTACKPOWER_ 4000
#define MONSTER_BOSSGOBLIN_ARMOR -8000

#define MONSTER_TAU_HP 80000
#define MONSTER_TAU_ATTACKPOWER 8000
#define MONSTER_TAU_ATTACKPOWER_ 10000
#define MONSTER_TAU_ARMOR 600

#define CHARACTER_HP 40000
#define CHARACTER_ATTACKPOWER 2000
#define CHARACTER_ATTACKPOWER_ 2400 //攻击力范围2000~2200
#define CHARACTER_ARMOR 300
#define CHARACTER_ATTACKSPEED 60 //攻击间隔时间
#define CHARACTER_MOVESPEED 4
#define CHARACTER_CRIT 30

#define CHARACTER_EFFECT_POWER_J 1
#define CHARACTER_EFFECT_POWER_H 1.5
#define CHARACTER_EFFECT_POWER_U1 2
#define CHARACTER_EFFECT_POWER_U2 2.5
using namespace cv;


enum DIRECTION
{
	DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_NONE
};

enum CHARACTEREFFECT
{
	EFFECTX,EFFECTZ, EFFECTS, EFFECTS2,NONE
};

// TODO: 在此处引用程序需要的其他头文件
