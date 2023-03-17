#include "Monster.h"
#include <stdlib.h>

Monster::Monster(HINSTANCE hInst, int foothold[][3])
{
	int rnd = rand() % 10;
	if(rnd < 5)
	{
		x = rand() % (foothold[rnd][2] - foothold[rnd][1]) + foothold[rnd][1];
		y = foothold[rnd][0];
	}
	else
	{
		x = rand() % 1000 + 500;
		y = 0;
	}
	mhp = 100;
	hp = mhp;
	att = 5;
	state = Move;
	rand() % 2 ? direction = RIGHT : direction = LEFT;
	index = 0;

	//right Stop, Move, Stun, Dead, Combo1, Combo2, Jump, Fall  left Stop, Move, Stun, Dead, Combo1, Combo2, Jump, Fall
	//        0     1     2     3     4        5      6    7           8     9    10    11     12      13      14   15

	numberOfSprite[1] = 3; numberOfSprite[2] = 2; numberOfSprite[4] = 3;
	hMotion[1] = (HBITMAP)::LoadImage(hInst, TEXT("MobRightMove.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[2] = (HBITMAP)::LoadImage(hInst, TEXT("MobRightStun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[4] = (HBITMAP)::LoadImage(hInst, TEXT("MobRightAttack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[9] = (HBITMAP)::LoadImage(hInst, TEXT("MobLeftMove.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[10] = (HBITMAP)::LoadImage(hInst, TEXT("MobLeftStun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[12] = (HBITMAP)::LoadImage(hInst, TEXT("MobLeftAttack.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMonsterHpGage = (HBITMAP)::LoadImage(hInst, TEXT("MobHpGage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

Monster::~Monster()
{
	DeleteObject(hMonsterHpGage);
	DeleteObject(hMotion[1]);
	DeleteObject(hMotion[2]);
	DeleteObject(hMotion[4]);
	DeleteObject(hMotion[9]);
	DeleteObject(hMotion[10]);
	DeleteObject(hMotion[12]);
}

HBITMAP Monster::GetMonsterHpGage()
{
	return hMonsterHpGage;
}