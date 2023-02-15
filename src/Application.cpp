#include "Application.hpp"

namespace osuessentials {

bool Application::Init(HINSTANCE hInstance)
{
    hInst = hInstance;
    hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProc);

    if (!hWnd) { return false; }

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uID = NOTIFY_ID;
    nid.hWnd = hWnd;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
    nid.uCallbackMessage = IDD_MESSAGE;

    Shell_NotifyIcon(NIM_ADD, &nid);

    //ShowWindow(hWnd, SW_SHOW);
    //UpdateWindow(hWnd);

    return true;
}

void Application::ShowShortcutMenu()
{
    HMENU hMenu, hMenuPopup;
    POINT pt;

    hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDD_DIALOG));
    hMenuPopup = GetSubMenu(hMenu, 0);

    GetCursorPos(&pt);
    SetForegroundWindow(hWnd);

    TrackPopupMenuEx(hMenuPopup, TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, hWnd, NULL);

    DestroyMenu(hMenu);
}

INT_PTR CALLBACK Application::DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case IDD_MESSAGE:
            switch (lParam)
            {
                case WM_RBUTTONDOWN:
                case WM_CONTEXTMENU:
                    ShowShortcutMenu();
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
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

} // namespace osuessentials
