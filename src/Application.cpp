#include "Application.hpp"

namespace osuessentials {

bool Application::Init()
{
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

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

void Application::OnQuit()
{
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

} // namespace osuessentials
