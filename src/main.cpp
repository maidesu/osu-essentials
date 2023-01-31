#define WIN32_LEAN_AND_MEAN
#define MAX_LOADSTRING 100

#include <assert.h>
#include <sdkddkver.h>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <shellapi.h>

#include "../resource/resource.h"


HINSTANCE hInst;
NOTIFYICONDATA nid;
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // TODO: Place code here.

    //LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadString(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);

    if (!InitInstance(hInstance))
    {
        return 1;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDD_DIALOG));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

/*ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDD_DIALOG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}*/


BOOL InitInstance(HINSTANCE hInstance)
{
   hInst = hInstance;

   HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);

   if (!hWnd)
   {
      return false;
   }

   nid.cbSize = sizeof(nid);
   nid.uID = NOTIFY_ID;
   nid.hWnd = hWnd;
   nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
   nid.uCallbackMessage = IDD_MESSAGE;

   Shell_NotifyIcon(NIM_ADD, &nid);

   //ShowWindow(hWnd, SW_SHOW);
   //UpdateWindow(hWnd);

   return true;
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
/*LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}*/


INT_PTR CALLBACK DialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case IDD_MESSAGE:
        switch (lParam)
        {
        case WM_LBUTTONDBLCLK:
            ShowWindow(hWnd, SW_RESTORE);
            break;

        case WM_RBUTTONDOWN:
        case WM_CONTEXTMENU:
            HMENU hMenu, hMenuPopup;

            POINT pt;
            GetCursorPos(&pt);

            hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDD_DIALOG));
            hMenuPopup = GetSubMenu(hMenu, 0);


            /*hMenuPopup = CreatePopupMenu();
            MENUITEMINFO menuItemInfo;
            ZeroMemory(&menuItemInfo, sizeof(menuItemInfo));
            menuItemInfo.cbSize = sizeof(menuItemInfo);
            menuItemInfo.fMask = MIIM_ID | MIIM_TYPE;
            menuItemInfo.fType = MFT_STRING;
            menuItemInfo.wID = 669;
            menuItemInfo.dwTypeData = (LPWSTR)L"Exit";
            menuItemInfo.cch = wcslen(menuItemInfo.dwTypeData);
            InsertMenuItem(hMenuPopup, 0, TRUE, &menuItemInfo);

            HDC hDC = GetDC(hWnd);
            assert(hDC != NULL);

            HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            assert(hFont != NULL);*/

            //HDC hDC = GetDC(hWnd);
            //SetTextAlign(hDC, TA_CENTER);

            SetForegroundWindow(hWnd);

            TrackPopupMenuEx(hMenuPopup, TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, hWnd, NULL);

            DestroyMenu(hMenuPopup);
            DestroyMenu(hMenu);
        }
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_EXIT:
            Shell_NotifyIcon(NIM_DELETE, &nid);
            DestroyWindow(hWnd);
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &nid);
        DestroyWindow(hWnd);
        break;
    }

    return true;
}
