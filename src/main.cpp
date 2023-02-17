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

INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    HWND hWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);
    if (!hWindow) { return 1; }

    Application app(hInstance, hWindow);

    if (!app.Init())
    {
        return 1;
    }

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Application* pApp = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (message)
    {
        case IDD_MESSAGE:
            switch (lParam)
            {
                case WM_RBUTTONDOWN:
                case WM_CONTEXTMENU:
                    if (pApp) {
                        pApp->ShowShortcutMenu();
                    }
                    break;
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDM_PRIORITY:
                    if (pApp)
                    {
                        pApp->ToggleFeature<PriorityFeature>();
                    }
                    break;

                case IDM_SUBMIT:
                    if (pApp)
                    {
                        pApp->ToggleFeature<SubmitFeature>();
                    }
                    break;

                case IDM_EXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            if (pApp) {
                pApp->OnQuit();
            }
            PostQuitMessage(0);
            break;

        default:
            // Default processing of messages not handled already
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
