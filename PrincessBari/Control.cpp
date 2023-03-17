#include "Control.h"
#include <mmsystem.h>
#define RIGHT 0
#define LEFT 8
#define BARISPRITEWIDTH 400
#define BARISPRITEHEIGHT 200
#define MOBSPRITEWIDTH 200
#define MOBSPRITEHEIGHT 100
enum {Stop, Move, Stun, Dead, Combo1, Combo2, Jump, Fall};

int bariStep = 0;
int mobStep[NUMBEROFMONSTERS];

Control::Control(HINSTANCE g_hInst, HWND hWnd)
{
	m_hInst = g_hInst;
	m_hWnd = hWnd;
	bari = new Bari(m_hInst);
	map = new Map(m_hInst);
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		mob[i] = new Monster(m_hInst, map->foothold);
		mobStep[i] = 0;
	}
	PlaySound(TEXT("BGM.wav"), NULL, SND_ASYNC | SND_LOOP);
}

Control::~Control()
{
	delete bari;
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		delete mob[i];
	}
	delete map;
}

void Control::Input()
{
	if (bari->GetState() == Stop || bari->GetState() == Move)
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			bari->ChangeDirection(RIGHT);
			bari->ChangeState(Move);
			bari->IncreaseIndex();
			bari->ChangeX(20);
			map->ScrollX(20);
			switch(bari->GetY())
			{
			case 1:
				if(!((bari->GetX() > map->foothold[0][1] && bari->GetX() < map->foothold[0][2]) || (bari->GetX() > map->foothold[1][1] && bari->GetX() < map->foothold[1][2]) || (bari->GetX() > map->foothold[2][1] && bari->GetX() < map->foothold[2][2]))) bari->ChangeState(Fall);
				break;
			case 2:
				if(!((bari->GetX() > map->foothold[3][1] && bari->GetX() < map->foothold[3][2]) || (bari->GetX() > map->foothold[4][1] && bari->GetX() < map->foothold[4][2]))) bari->ChangeState(Fall);
				break;
			}
		}
		else if(GetAsyncKeyState(VK_LEFT))
		{
			bari->ChangeDirection(LEFT);
			bari->ChangeState(Move);
			bari->IncreaseIndex();
			bari->ChangeX(-20);
			map->ScrollX(-20);
			switch(bari->GetY())
			{
			case 1:
				if(!((bari->GetX() > map->foothold[0][1] && bari->GetX() < map->foothold[0][2]) || (bari->GetX() > map->foothold[1][1] && bari->GetX() < map->foothold[1][2]) || (bari->GetX() > map->foothold[2][1] && bari->GetX() < map->foothold[2][2]))) bari->ChangeState(Fall);
				break;
			case 2:
				if(!((bari->GetX() > map->foothold[3][1] && bari->GetX() < map->foothold[3][2]) || (bari->GetX() > map->foothold[4][1] && bari->GetX() < map->foothold[4][2]))) bari->ChangeState(Fall);
				break;
			}
		}
		else if(GetAsyncKeyState(VK_UP))
		{
			bari->ChangeState(Jump);
		}
		else if(GetAsyncKeyState('Z'))
		{
			bari->ChangeState(Combo1);
		}
		else
		{
			bari->ChangeState(Stop);
			bari->IncreaseIndex();
		}
	}
	else if(bari->GetState() == Stun)
	{
		bariStep++;
		if (bariStep == 2) bari->IncreaseIndex();
		if (bariStep == 4) bari->IncreaseIndex();
		if (bariStep == 16)
		{
			bari->ChangeState(Stop);
			bariStep = 0;
		}
	}
	else if(bari->GetState() == Jump)
	{
		if (bariStep < 7)
		{
			map->ScrollY(-25);
			bariStep++;
		}
		else
		{
			if (bariStep == 7) bari->IncreaseIndex();
			for (int i = 0; i < 5; i++)
			{
				if (map->foothold[i][0] == bari->GetY() + 1 && bari->GetX() > map->foothold[i][1] && bari->GetX() < map->foothold[i][2])
				{
					bari->ChangeY(1);
					bari->ChangeState(Stop);
					map->ScrollY(-25); //아래에서 한번 더 스크롤되므로
					bariStep = -1;
					break;
				}
			}
			map->ScrollY(25);
			bariStep++;
			if (bariStep > 13)
			{
				bari->ChangeState(Stop);
				bariStep = 0;
			}
		}
	}
	else if(bari->GetState() == Combo1)
	{
		bari->IncreaseIndex();
		bariStep++;
		if (bariStep > bari->GetNumberOfSprite())
		{
			for (int i = 0; i < NUMBEROFMONSTERS; i++)
			{
				if (((bari->GetX() - mob[i]->GetX() > 0 && bari->GetX() - mob[i]->GetX() < 100 && bari->GetDirection() == LEFT) || (mob[i]->GetX() - bari->GetX() > 0 && mob[i]->GetX() - bari->GetX() < 100 && bari->GetDirection() == RIGHT)) && bari->GetY() == mob[i]->GetY() && mob[i]->GetState() != Dead && mob[i]->GetState() != Stun)
				{
					mob[i]->ChangeState(Stun);
					mob[i]->HpMinus(bari->GetAtt());
					if (mob[i]->GetHp() < 1)
					{
						mob[i]->ChangeState(Dead);
						bari->ExpUp(NEEDEDEXPFORLEVELUP / 5);
					}
					if (bari->GetDirection() == mob[i]->GetDirection()) mob[i]->GetDirection() ? mob[i]->ChangeDirection(RIGHT) : mob[i]->ChangeDirection(LEFT);
				}
			}
			bari->ChangeState(Stop);
			if (GetAsyncKeyState('Z'))
			{
				bari->ChangeState(Combo2);
			}
			bariStep = 0;
		}
	}
	else if(bari->GetState() == Combo2)
	{
		if (bariStep < bari->GetNumberOfSprite() - 1)
		{
			bari->IncreaseIndex();
			bariStep++;
		}
		else
		{
			if (bariStep == bari->GetNumberOfSprite() - 1)
			{
				for (int i = 0; i < NUMBEROFMONSTERS; i++)
				{
					if (((bari->GetX() - mob[i]->GetX() > 0 && bari->GetX() - mob[i]->GetX() < 175 && bari->GetDirection() == LEFT) || (mob[i]->GetX() - bari->GetX() > 0 && mob[i]->GetX() - bari->GetX() < 175 && bari->GetDirection() == RIGHT)) && bari->GetY() == mob[i]->GetY() && mob[i]->GetState() != Dead && mob[i]->GetState() != Stun)
					{
						mob[i]->ChangeState(Stun);
						mob[i]->HpMinus(bari->GetAtt());
						if (mob[i]->GetHp() < 1)
						{
							mob[i]->ChangeState(Dead);
							bari->ExpUp(NEEDEDEXPFORLEVELUP / 5);
						}
						if (bari->GetDirection() == mob[i]->GetDirection()) mob[i]->GetDirection() ? mob[i]->ChangeDirection(RIGHT) : mob[i]->ChangeDirection(LEFT);
					}
				}
			}
			bariStep++;
			if (bariStep > bari->GetNumberOfSprite() + 10) //이미 스턴상태라서 맞지않은 몬스터가 이 시간동안 깨어나 때릴 수 있다. 시간을 늘리면 마비시간이 늘어나 난이도 증가
			{
				bari->ChangeState(Stop);
				bariStep = 0;
			}
		}
	}
	else if(bari->GetState() == Fall)
	{
		if (bariStep < 7)
		{
			map->ScrollY(25);
			bariStep++;
		}
		else
		{
			bari->ChangeY(-1);
			bari->ChangeState(Stop);
			bariStep = 0;
		}
	}
	else
	{
		bariStep++;
		if (bariStep > 100)
		{
			PostQuitMessage(0);
		}
	}
}

void Control::AI()
{
	//게임오버 체크
	int deadCount = 0;
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		if(mob[i]->GetState() == Dead) deadCount++;
		if(deadCount == NUMBEROFMONSTERS) PostQuitMessage(0);
	}

	//인공지능
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		if (mob[i]->GetState() == Stun)
		{
			mobStep[i]++;
			if (mobStep[i] == 2) mob[i]->IncreaseIndex();
			if (mobStep[i] == 20) //스턴 후 마비시간
			{
				mob[i]->ChangeState(Move);
				mobStep[i] = 0;
			}
		}
		else if(mob[i]->GetState() == Dead){}
		else
		{
			if (bari->GetX() - mob[i]->GetX() > -50 && bari->GetX() - mob[i]->GetX() < 50 && bari->GetY() == mob[i]->GetY())
			{
				//공격
				if(bari->GetState() != Stun && bari->GetState() != Dead && bari->GetState() != Jump && bari->GetState() != Fall)
				{
					if (mobStep[i] < 10) //공격전 뜸들이는 시간, 짧으면 난이도 증가
					{
						mobStep[i]++;
					} 
					else
					{
						mob[i]->ChangeState(Combo1);
						mob[i]->IncreaseIndex();
						mobStep[i]++;
						if (mobStep[i] > 12)
						{
							bari->ChangeState(Stun);
							bari->HpMinus(mob[i]->GetAtt());
							if (bari->GetHp() < 1) bari->ChangeState(Dead);
							if (mob[i]->GetDirection() == bari->GetDirection()) bari->GetDirection() ? bari->ChangeDirection(RIGHT) : bari->ChangeDirection(LEFT);
							mobStep[i] = 0;
						}
					}
				}
			}
			else if(bari->GetX() - mob[i]->GetX() > -320 && bari->GetX() - mob[i]->GetX() < 320 && bari->GetY() == mob[i]->GetY() &&
				((mob[i]->GetX() > map->foothold[0][1] && mob[i]->GetX() < map->foothold[0][2] && bari->GetX() > map->foothold[0][1] && bari->GetX() < map->foothold[0][2] && mob[i]->GetY() == map->foothold[0][0]) ||
				(mob[i]->GetX() > map->foothold[1][1] && mob[i]->GetX() < map->foothold[1][2] && bari->GetX() > map->foothold[1][1] && bari->GetX() < map->foothold[1][2] && mob[i]->GetY() == map->foothold[1][0]) ||
				(mob[i]->GetX() > map->foothold[2][1] && mob[i]->GetX() < map->foothold[2][2] && bari->GetX() > map->foothold[2][1] && bari->GetX() < map->foothold[2][2] && mob[i]->GetY() == map->foothold[2][0]) ||
				(mob[i]->GetX() > map->foothold[3][1] && mob[i]->GetX() < map->foothold[3][2] && bari->GetX() > map->foothold[3][1] && bari->GetX() < map->foothold[3][2] && mob[i]->GetY() == map->foothold[3][0]) ||
				(mob[i]->GetX() > map->foothold[4][1] && mob[i]->GetX() < map->foothold[4][2] && bari->GetX() > map->foothold[4][1] && bari->GetX() < map->foothold[4][2] && mob[i]->GetY() == map->foothold[4][0]) || mob[i]->GetY() == 0))
			{
				//접근
					bari->GetX() > mob[i]->GetX() ? mob[i]->ChangeDirection(RIGHT) : mob[i]->ChangeDirection(LEFT);
					mob[i]->ChangeState(Move);
					mob[i]->IncreaseIndex();
					mob[i]->ChangeX(mob[i]->GetDirection() ? -7 : 7); //접근시에는 왕복시보다 빠르게 움직이게 해놨음
			}
			else
			{
				//왕복
				mob[i]->ChangeState(Move);
				mob[i]->IncreaseIndex();
				mob[i]->ChangeX(mob[i]->GetDirection() ? -5 : 5);
				switch(mob[i]->GetY())
				{
				case 0:
					if(mob[i]->GetX() < 320) mob[i]->ChangeDirection(RIGHT);
					if(mob[i]->GetX() > 1600) mob[i]->ChangeDirection(LEFT);
					break;
				case 1:
					if(mob[i]->GetX() > map->foothold[0][1] && mob[i]->GetX() < map->foothold[0][2])
					{
						if(mob[i]->GetX() < map->foothold[0][1] + 20) mob[i]->ChangeDirection(RIGHT);
						if(mob[i]->GetX() > map->foothold[0][2] - 20) mob[i]->ChangeDirection(LEFT);
					}
					else if(mob[i]->GetX() > map->foothold[1][1] && mob[i]->GetX() < map->foothold[1][2])
					{
						if(mob[i]->GetX() < map->foothold[1][1] + 20) mob[i]->ChangeDirection(RIGHT);
						if(mob[i]->GetX() > map->foothold[1][2] - 20) mob[i]->ChangeDirection(LEFT);
					}
					else if(mob[i]->GetX() > map->foothold[2][1] && mob[i]->GetX() < map->foothold[2][2])
					{
						if(mob[i]->GetX() < map->foothold[2][1] + 20) mob[i]->ChangeDirection(RIGHT);
						if(mob[i]->GetX() > map->foothold[2][2] - 20) mob[i]->ChangeDirection(LEFT);
					}
					break;
				case 2:
					if(mob[i]->GetX() > map->foothold[3][1] && mob[i]->GetX() < map->foothold[3][2])
					{
						if(mob[i]->GetX() < map->foothold[3][1] + 20) mob[i]->ChangeDirection(RIGHT);
						if(mob[i]->GetX() > map->foothold[3][2] - 20) mob[i]->ChangeDirection(LEFT);
					}
					else if(mob[i]->GetX() > map->foothold[4][1] && mob[i]->GetX() < map->foothold[4][2])
					{
						if(mob[i]->GetX() < map->foothold[4][1] + 20) mob[i]->ChangeDirection(RIGHT);
						if(mob[i]->GetX() > map->foothold[4][2] - 20) mob[i]->ChangeDirection(LEFT);
					}
					break;
				}
			}
		}
	}
}

void Control::Render()
{
	TCHAR information[128];
	RECT rect;
	HDC hDC, hMemDC, hMap, hBari, hHpGage, hBariHpGage, hMobHpGage, hMob[NUMBEROFMONSTERS];
	HBITMAP OldBit, hBit;
	hBit = NULL;
	GetClientRect(m_hWnd, &rect);
	hDC = GetDC(m_hWnd);
	if(hBit == NULL) hBit = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
	hMemDC = CreateCompatibleDC(hDC);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	FillRect(hMemDC, &rect, GetSysColorBrush(COLOR_WINDOW));

	//오브젝트들을 찍는 부분
	hMap = CreateCompatibleDC(hDC);
	SelectObject(hMap, map->GetBitmap());
	BitBlt(hMemDC, 0, 0, rect.right, rect.bottom, hMap, map->GetScrollX(), map->GetScrollY(), SRCCOPY);
	DeleteDC(hMap);

	hHpGage = CreateCompatibleDC(hDC);
	SelectObject(hHpGage, bari->GetHpGage());
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		if (mob[i]->GetState() != Dead)
		{
			BitBlt(hMemDC, mob[i]->GetX() - map->GetScrollX() - 30, 1060 - map->GetScrollY() - ((mob[i]->GetY() + 1) * 175), 57, 5, hHpGage, 0, 0, SRCCOPY);
		}
	}
	BitBlt(hMemDC, 311 - bari->GetDirection() * 6, 286, 57, 5, hHpGage, 0, 0, SRCCOPY);
	DeleteDC(hHpGage);

	hMobHpGage = CreateCompatibleDC(hDC);
	SelectObject(hMobHpGage, mob[0]->GetMonsterHpGage());
	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		if (mob[i]->GetState() != Dead)
		{
			BitBlt(hMemDC, mob[i]->GetX() - map->GetScrollX() - 29, 1060 - map->GetScrollY() - ((mob[i]->GetY() + 1) * 175) + 1, (int)(55 * mob[i]->GetHp() / mob[i]->GetMhp()), 3, hMobHpGage, 0, 0, SRCCOPY);
		}
	}
	DeleteDC(hMobHpGage);

	hBariHpGage = CreateCompatibleDC(hDC);
	SelectObject(hBariHpGage, bari->GetBariHpGage());
	BitBlt(hMemDC, 312 - bari->GetDirection() * 6, 287, (int)(55 * bari->GetHp() / bari->GetMhp()), 3, hBariHpGage, 0, 0, SRCCOPY);
	DeleteDC(hBariHpGage);

	for (int i = 0; i < NUMBEROFMONSTERS; i++)
	{
		if (mob[i]->GetState() != Dead)
		{
			hMob[i] = CreateCompatibleDC(hDC);
			SelectObject(hMob[i], mob[i]->GetBitmap());
			TransparentBlt(hMemDC, mob[i]->GetX() - map->GetScrollX() - 100, 1060 - map->GetScrollY() - ((mob[i]->GetY() + 1) * 175) - 15, MOBSPRITEWIDTH, MOBSPRITEHEIGHT, hMob[i], mob[i]->GetIndex() * MOBSPRITEWIDTH, 0, MOBSPRITEWIDTH, MOBSPRITEHEIGHT, RGB(250, 16, 16));
			DeleteDC(hMob[i]);
		}
	}

	hBari = CreateCompatibleDC(hDC);
	SelectObject(hBari, bari->GetBitmap());
	TransparentBlt(hMemDC, 120, 200, BARISPRITEWIDTH, BARISPRITEHEIGHT, hBari, bari->GetIndex() * BARISPRITEWIDTH, 0, BARISPRITEWIDTH, BARISPRITEHEIGHT, RGB(250, 16, 16));
	DeleteDC(hBari);
	
	//캐릭터 정보 출력
	wsprintf(information, TEXT("   LEVEL : %d   MHP : %d   HP : %d   ATT : %d   EXP : %d   "), bari->GetLevel(), bari->GetMhp(), bari->GetHp(), bari->GetAtt(), bari->GetExp());
	TextOut(hMemDC, 250, 5, information, lstrlen(information));

	Sleep(40); //프레임수 출력되는것보고 조정하자. 다음 게임부터는 프레임 스키핑기법을 이용할것

	BitBlt(hDC, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, OldBit);
	DeleteObject(hBit);
	DeleteDC(hMemDC);
	ReleaseDC(m_hWnd, hDC);
	InvalidateRect(m_hWnd, NULL, FALSE);
}