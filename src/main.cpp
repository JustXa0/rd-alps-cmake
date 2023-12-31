// rd-alps.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "main.h"

#define MAX_LOADSTRING 100
#define IDM_MY_SELECTION 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name  
HWND hCursorPosLabel = NULL;                    // label for cursor window
bool isDragging = false;                        // boolean for dragging function
POINT dragStartPos;                             // point for storing start
bool isHovering = false;                        // boolean for storing hovering
bool checked = true;                            // boolean for storing checks
bool con = false;                               // boolean for storing console status

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RDALPS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RDALPS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RDALPS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RDALPS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);




    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    ShowWindow(hCursorPosLabel, nCmdShow);
    UpdateWindow(hCursorPosLabel);

    


    return TRUE;
}




//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {

        HMENU hMenu = CreateMenu();
        HMENU hSubMenu = CreatePopupMenu();


        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Developer Settings");
        AppendMenu(hSubMenu, MF_STRING, IDM_MY_SELECTION, L"Disable Cursor Position");
        CheckMenuItem(hSubMenu, IDM_MY_SELECTION, MF_UNCHECKED);

        SetMenu(hWnd, hMenu);

    }
    break;
    // case WM_COMMAND:
    // {
    //     int wmId = LOWORD(wParam);
    //     // Parse the menu selections:
    //     switch (wmId)
    //     {
    //     case IDM_ABOUT:
    //         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
    //         break;
    //     case IDM_EXIT:
    //         DestroyWindow(hWnd);
    //         break;
    //     case IDM_MY_SELECTION:
    //     {
    //         HMENU hMenu = GetMenu(hWnd);
    //         HMENU hSubMenu = GetSubMenu(hMenu, 0);
    //         if (checked)
    //         {
    //             ModifyMenuW(hSubMenu, IDM_MY_SELECTION, MF_BYCOMMAND | MF_CHECKED, IDM_MY_SELECTION, L"Disable Cursor Position");
    //             checked = false;
    //             ShowWindow(hCursorPosLabel, SW_SHOW);
    //         }
    //         else {
    //             ModifyMenuW(hSubMenu, IDM_MY_SELECTION, MF_BYCOMMAND | MF_UNCHECKED, IDM_MY_SELECTION, L"Enable Cursor Position");
    //             checked = true;
    //             ShowWindow(hCursorPosLabel, SW_HIDE);
    //         }
    //     }
    //     break;
    //     default:
    //         return DefWindowProc(hWnd, message, wParam, lParam);
    //     }
    // }
    // break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Calculate the cursor position
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        RECT rec;

        SetRect(&rec, 10, 10, 100, 100);

        // Format the cursor position text
        std::wstring cursorPosStr = L"X: " + std::to_wstring(cursorPos.x) + L", Y: " + std::to_wstring(cursorPos.y);

        // Update the cursor position text in the label control
        SetWindowText(hCursorPosLabel, cursorPosStr.c_str());

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_NCPAINT:
    {
        // Force the non-client area (including the border) to be repainted
        DefWindowProc(hWnd, WM_NCPAINT, wParam, lParam);

        // Repaint the client area to ensure the cursor position display is visible
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOUSEMOVE:
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);

        RECT windowRect;
        GetClientRect(hCursorPosLabel, &windowRect);

        std::wstring cursorPosStr = L"X: " + std::to_wstring(cursorPos.x) + L", Y: " + std::to_wstring(cursorPos.y);
        SetWindowText(hCursorPosLabel, cursorPosStr.c_str());
        if (con)
        {
            std::wcout << L"X: " + std::to_wstring(cursorPos.x) + L", Y: " + std::to_wstring(cursorPos.y) << std::endl;
        }
    }
    break;

    case WM_SIZE:
    {
        // Adjust the tooltip position and size
        RECT rect;
        GetClientRect(hWnd, &rect);
        int tooltipWidth = 200;
        int tooltipHeight = 20;
        int labelX = rect.left + 10;
        int labelY = rect.bottom - tooltipHeight - 10;

        // Set the tooltip window position and size
        SetWindowPos(hCursorPosLabel, NULL, labelX, labelY, tooltipWidth, tooltipHeight, SWP_SHOWWINDOW);
    }
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }        break;
    }
    return (INT_PTR)FALSE;
}




// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         return -1;
//     }

//     // Create a GLFW window
//     GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
//     if (!window) 
//     {
//         glfwTerminate();
//         return -1;
//     }
//     else
//     {
//         Logger::getInstance().log_i("Hello World!");
//     }

//     //Monitor::Monitor();
//     //GPU::GPU();
//     //Encoder encoder;

//     // Main loop
//     while (!glfwWindowShouldClose(window)) {
//         // Poll for and process events

//         glClear(GL_COLOR_BUFFER_BIT);

//         glfwSwapBuffers(window);

//         glfwPollEvents();
//     }

//     // Cleanup and exit
//     //encoder.~Encoder();
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }
