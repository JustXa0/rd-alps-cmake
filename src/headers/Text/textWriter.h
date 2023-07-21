#pragma once
#include <Windows.h>
#include <string>

class textWriter
{
private:
	HDC hdc;
	HWND hWnd;


public:
	void write(std::string text, int R, int G, int B);
	void write(std::string text, int R, int G, int B, int x, int y);
	void write(std::wstring text, int R, int G, int B, int x, int y);
	textWriter(HDC, HWND);
};

