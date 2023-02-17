#include "Application.hpp"

namespace osuessentials {

Application::Application(HINSTANCE hInstance, HWND hWindow) :
    hInst(hInstance),
    hWnd(hWindow),
    nid()
{
    // Push features here
    features.push_back(std::make_unique<PriorityFeature>());
    features.push_back(std::make_unique<SubmitFeature>());
}

bool Application::Init()
{
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    // Initialize Notify icon
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uID = NOTIFY_ID;
    nid.hWnd = hWnd;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
    nid.uCallbackMessage = IDD_MESSAGE;

    // Add Notify icon
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Good to have on by default
    this->ToggleFeature<PriorityFeature>();

    return true;
}

void Application::ShowShortcutMenu()
{
    HMENU hMenu, hMenuPopup;
    POINT pt;

    hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDD_DIALOG));

    // Update checkboxes
    CheckMenuItem(hMenu, IDM_PRIORITY, isEnabledFeature<PriorityFeature>() ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu, IDM_SUBMIT, isEnabledFeature<SubmitFeature>()  ? MF_CHECKED : MF_UNCHECKED);

    hMenuPopup = GetSubMenu(hMenu, 0);

    GetCursorPos(&pt);
    SetForegroundWindow(hWnd);

    TrackPopupMenuEx(hMenuPopup, TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, hWnd, NULL);

    DestroyMenu(hMenu);
}

void Application::OnQuit()
{
    // Remove Notify icon
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

} // namespace osuessentials
