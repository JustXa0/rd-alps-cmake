#include "startup.h"

startup::startup(HWND hWnd, HINSTANCE hInst, HWND& hLabel)
{
    hLabel = CreateCursorPosLabel(hWnd, hInst);
}

HWND startup::CreateCursorPosLabel(HWND hWnd, HINSTANCE hInst)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    // Calculate the position for the label control at the bottom of the window
    int xPos = rect.left;
    int yPos = rect.bottom - 20;
    int width = rect.right - rect.left;
    int height = 20;

    // Create the label control with WS_VISIBLE flag set to false
    HWND hLabel = CreateWindow(L"STATIC", NULL, WS_CHILD, xPos, yPos, width, height, hWnd, NULL, hInst, NULL);

    // Set the label control's properties
    SetWindowText(hLabel, L"Cursor Position:");
    SendMessage(hLabel, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), MAKELPARAM(TRUE, 0));

    return hLabel;
}
