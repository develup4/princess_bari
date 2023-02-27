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
	int foothold[5][3]; //[�ö󰥼��ִ¶� INDEX][0 : ����, 1: ������, 2 : ����]

	Map(HINSTANCE hInst);
	~Map();
	HBITMAP GetBitmap();
	int GetScrollX();
	int GetScrollY();
	void ScrollX(int sx);
	void ScrollY(int sy);
};

#endif