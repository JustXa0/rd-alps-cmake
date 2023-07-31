#include "integerWriter.h"



void integerWriter::intWrite(int num, int R, int G, int B)
{

    // Set the text color and background color
    SetTextColor(hdc, RGB(R, G, B));
    // Transparent background

// Format the integer into a string
    wchar_t buffer[10];
    swprintf_s(buffer, L"%d", num);

    // Calculate the position for displaying the integer
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int x = (clientRect.right - clientRect.left) / 2; // Center horizontally
    int y = (clientRect.bottom - clientRect.top) / 2; // Center vertically

    // Draw the integer on the screen
    DrawTextW(hdc, buffer, -1, &clientRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}


void integerWriter::intWrite(int num, int R, int G, int B, int x, int y)
{
    SetTextColor(hdc, RGB(R, G, B));
    SetBkMode(hdc, TRANSPARENT);

    wchar_t buffer[10];
    swprintf_s(buffer, L"%d", num);

    TextOutW(hdc, x, y, buffer, lstrlenW(buffer));
}

integerWriter::integerWriter(HDC uHdc, HWND uHWnd)
{
    hdc = uHdc;
    hWnd = uHWnd;
}