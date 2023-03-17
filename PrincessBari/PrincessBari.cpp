#include "Control.h"

#define WINWIDTH 640
#define WINHEIGHT 480

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CheckFPS(HWND hWnd);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("바리공주의 전설");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	g_hInst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, WINWIDTH, WINHEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	//CONTROL CLASS
	Control ctrl(g_hInst, hWnd);

	ShowWindow(hWnd, nCmdShow);
	while(1)
	{ 
		MSG msg; 
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//FPS출력
			CheckFPS(hWnd);

			//게임루프파트
			ctrl.Input();
			ctrl.AI();
			ctrl.Render();
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CheckFPS(HWND hWnd) 
{ 
	static DWORD dwTick = 0;
	static DWORD dwFPS = 0;
	TCHAR szTemp[128];

	dwFPS++;
	if (GetTickCount() - dwTick > 1000) 
	{ 
		dwTick = GetTickCount(); 
		wsprintf(szTemp, TEXT("바리공주의 전설 (FPS : %d)"), dwFPS); 
		SetWindowText(hWnd, szTemp);
		dwFPS = 0; 
		return;
	} 
} 