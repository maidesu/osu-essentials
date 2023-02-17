#include "Application.hpp"

namespace osuessentials {

Application::Application(HINSTANCE hInstance, HWND hWindow) :
    hInst(hInstance),
    hWnd(hWindow),
    nid()
{
    features.push_back(std::make_unique<PriorityFeature>());
    //features.push_back(std::make_unique<SubmitFeature>());
}

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

    CheckMenuItem(hMenu, IDM_PRIORITY, features[0].get()->isEnabled() ? MF_CHECKED : MF_UNCHECKED);
    // to be implemented
    EnableMenuItem(hMenu, IDM_SUBMIT, MF_GRAYED);
    //CheckMenuItem(hMenu, IDM_SUBMIT, features[1].get()->isEnabled() ? MF_CHECKED : MF_UNCHECKED);

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
