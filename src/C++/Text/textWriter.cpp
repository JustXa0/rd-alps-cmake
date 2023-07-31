#include "textWriter.h"

textWriter::textWriter(HDC uHdc, HWND uHWnd)
{
	hdc = uHdc;
	hWnd = uHWnd;
}

void textWriter::write(std::string message, int R, int G, int B)
{
	SetTextColor(hdc, RGB(R, G, B));
	SetBkMode(hdc, TRANSPARENT);
	size_t bufferSize = 0;
	mbstowcs_s(&bufferSize, nullptr, 0, message.c_str(), 0);

	// Allocate memory for the destination buffer
	wchar_t* destinationBuffer = new wchar_t[bufferSize];

	// Convert the string to wchar_t
	mbstowcs_s(nullptr, destinationBuffer, bufferSize, message.c_str(), bufferSize);

	// Use the destinationBuffer as a wchar_t variable

	// Remember to deallocate the memory when you are done


	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	int x = (clientRect.right - clientRect.left) / 2;
	int y = (clientRect.bottom - clientRect.top) / 2;

	DrawTextW(hdc, destinationBuffer, -1, &clientRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	delete[] destinationBuffer;

}

void textWriter::write(std::string message, int R, int G, int B, int x, int y)
{
	SetTextColor(hdc, RGB(R, G, B));
	SetBkMode(hdc, TRANSPARENT);
	size_t bufferSize = 0;
	mbstowcs_s(&bufferSize, nullptr, 0, message.c_str(), 0);

	wchar_t* destinationBuffer = new wchar_t[bufferSize];

	mbstowcs_s(nullptr, destinationBuffer, bufferSize, message.c_str(), bufferSize);

	TextOutW(hdc, x, y, destinationBuffer, lstrlenW(destinationBuffer));
}

void textWriter::write(std::wstring message, int R, int G, int B, int x, int y)
{
	SetTextColor(hdc, RGB(R, G, B));
	SetBkMode(hdc, TRANSPARENT);
	TextOutW(hdc, x, y, message.c_str(), static_cast<int>(message.length()));
}
