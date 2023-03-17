#ifndef _CONTROL_H_
#define _CONTROL_H_
#define NUMBEROFMONSTERS 20
#include "Bari.h"
#include "Monster.h"
#include "Map.h"

class Control
{
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;

	//OBJECT
	Bari* bari; //동적바인딩을 고려한 상속이었다면 Character*형으로 선언하여 다형성을 이용가능
	Monster* mob[NUMBEROFMONSTERS];
	Map* map;
public:
	Control(HINSTANCE g_hInst, HWND hWnd);
	~Control();
	void Input();
	void AI();
	void Render();
};

#endif