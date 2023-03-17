#include "Map.h"

Map::Map(HINSTANCE hInst)
{
	hMAP = (HBITMAP)::LoadImage(hInst, TEXT("Map.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	sx = 200;
	sy = 580;
	foothold[0][0] = 1; foothold[0][1] = 320; foothold[0][2] = 700;
	foothold[1][0] = 1; foothold[1][1] = 880; foothold[1][2] = 1280;
	foothold[2][0] = 1; foothold[2][1] = 1400; foothold[2][2] = 1610;
	foothold[3][0] = 2; foothold[3][1] = 1200; foothold[3][2] = 1600;
	foothold[4][0] = 2; foothold[4][1] = 460; foothold[4][2] = 1040;
}

Map::~Map()
{
	DeleteObject(hMAP);
}

HBITMAP Map::GetBitmap()
{
	return hMAP;
}

int Map::GetScrollX()
{
	return sx;
}

int Map::GetScrollY()
{
	return sy;
}

void Map::ScrollX(int amount)
{
	sx += amount;
	if (sx < 0) sx = 0;
	if (sx > 1280) sx = 1280;
}

void Map::ScrollY(int amount)
{
	sy += amount;
}