#include "Bari.h"

Bari::Bari(HINSTANCE hInst)
{
	x = 520;
	y = 0;
	mhp = 100;
	hp = mhp;
	att = 10;
	level = 1;
	exp = 0;
	state = Move;
	direction = RIGHT;
	index = 0;

	//right Stop, Move, Stun, Dead, Combo1, Combo2, Jump, Fall  left Stop, Move, Stun, Dead, Combo1, Combo2, Jump, Fall
	//        0     1     2     3     4        5      6    7           8     9    10    11     12      13      14   15

	numberOfSprite[0] = 4; numberOfSprite[1] = 6; numberOfSprite[2] = 3; numberOfSprite[3] = 1; numberOfSprite[4] = 5; numberOfSprite[5] = 8; numberOfSprite[6] = 2;
	hMotion[0] = (HBITMAP)::LoadImage(hInst, TEXT("RightStop.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[1] = (HBITMAP)::LoadImage(hInst, TEXT("RightMove.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[2] = (HBITMAP)::LoadImage(hInst, TEXT("RightStun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[3] = (HBITMAP)::LoadImage(hInst, TEXT("RightDead.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[4] = (HBITMAP)::LoadImage(hInst, TEXT("RightCombo1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[5] = (HBITMAP)::LoadImage(hInst, TEXT("RightCombo2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[6] = (HBITMAP)::LoadImage(hInst, TEXT("RightJump.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[7] = (HBITMAP)::LoadImage(hInst, TEXT("RightFall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[8] = (HBITMAP)::LoadImage(hInst, TEXT("LeftStop.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[9] = (HBITMAP)::LoadImage(hInst, TEXT("LeftMove.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[10] = (HBITMAP)::LoadImage(hInst, TEXT("LeftStun.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[11] = (HBITMAP)::LoadImage(hInst, TEXT("LeftDead.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[12] = (HBITMAP)::LoadImage(hInst, TEXT("LeftCombo1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[13] = (HBITMAP)::LoadImage(hInst, TEXT("LeftCombo2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[14] = (HBITMAP)::LoadImage(hInst, TEXT("LeftJump.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hMotion[15] = (HBITMAP)::LoadImage(hInst, TEXT("LeftFall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hHpGage = (HBITMAP)::LoadImage(hInst, TEXT("HpGage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBariHpGage = (HBITMAP)::LoadImage(hInst, TEXT("BariHpGage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

Bari::~Bari()
{
	DeleteObject(hHpGage);
	DeleteObject(hBariHpGage);
	for (int i = 0; i < NUMBEROFMOTION; i++)
	{
		DeleteObject(hMotion[i]);
	}
}

int Bari::GetLevel()
{
	return level;
}

int Bari::GetExp()
{
	return exp;
}

void Bari::ExpUp( int amount )
{
	exp += amount;
	if (exp > NEEDEDEXPFORLEVELUP)
	{
		level++;
		mhp *= 1.2;
		hp = mhp;
		att *= 1.2;
		exp = 0;
	}
}

HBITMAP Bari::GetBariHpGage()
{
	return hBariHpGage;
}