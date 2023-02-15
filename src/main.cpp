#define WIN32_LEAN_AND_MEAN
#define MAX_LOADSTRING 100

#include <sdkddkver.h>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <shellapi.h>

#include "Application.hpp"
#include "../resource/resource.h"

using namespace osuessentials;

HINSTANCE Application::hInst = NULL;
HWND Application::hWnd = NULL;
NOTIFYICONDATA Application::nid = (NOTIFYICONDATA)NULL;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    if (!Application::Init(hInstance))
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
