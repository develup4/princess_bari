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
	Bari* bari; //�������ε��� ����� ����̾��ٸ� Character*������ �����Ͽ� �������� �̿밡��
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