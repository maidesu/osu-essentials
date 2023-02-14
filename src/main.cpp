#define WIN32_LEAN_AND_MEAN
#define MAX_LOADSTRING 100

#include <sdkddkver.h>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <shellapi.h>

#include "../resource/resource.h"


HINSTANCE hInst;
NOTIFYICONDATA nid;

BOOL                InitInstance(HINSTANCE);
INT_PTR CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

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

    return (int)msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance)
{
   hInst = hInstance;

   HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);

   if (!hWnd)
   {
      return false;
   }

   nid.cbSize = sizeof(NOTIFYICONDATA);
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

INT_PTR CALLBACK DialogProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case IDD_MESSAGE:
            switch (lParam)
            {
                case WM_RBUTTONDOWN:
                case WM_CONTEXTMENU:
                    HMENU hMenu, hMenuPopup;
                    POINT pt;

                    hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDD_DIALOG));
                    hMenuPopup = GetSubMenu(hMenu, 0);

                    GetCursorPos(&pt);
                    SetForegroundWindow(hWnd);

                    TrackPopupMenuEx(hMenuPopup, TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, hWnd, NULL);
 
                    DestroyMenu(hMenu);
                    break;
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDM_EXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            Shell_NotifyIcon(NIM_DELETE, &nid);
            PostQuitMessage(0);
            break;

        default:
            // Default processing of messages not handled already
            return DefWindowProc(hWnd, Message, wParam, lParam);
    }

    return 0;
}
