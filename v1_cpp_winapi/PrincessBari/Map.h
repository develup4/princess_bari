#ifndef _MAP_H_
#define _MAP_H_
#include <windows.h>

class Map
{
private:
	HBITMAP hMAP;
	int sx;
	int sy;

public:
	int foothold[5][3]; //[올라갈수있는땅 INDEX][0 : 높이, 1: 시작점, 2 : 끝점]

	Map(HINSTANCE hInst);
	~Map();
	HBITMAP GetBitmap();
	int GetScrollX();
	int GetScrollY();
	void ScrollX(int sx);
	void ScrollY(int sy);
};

#endif