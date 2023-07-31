#pragma once

#include <windows.h>

class startup
{
    public:
        
    startup(HWND hWnd, HINSTANCE hInst, HWND& hLabel);

    private:
    HWND CreateCursorPosLabel(HWND hWnd, HINSTANCE hInst);

};

