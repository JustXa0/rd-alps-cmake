#pragma once
#include <Windows.h>
#include <cwchar>

class integerWriter
{
private:
	HDC hdc;
	HWND hWnd;

public:
	void intWrite(int num, int R, int G, int B);
	void intWrite(int num, int R, int G, int B, int x, int y);
	integerWriter(HDC uHdc, HWND uHWnd);

};

