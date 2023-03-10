#include "Application.hpp"

#include <shlobj_core.h>

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

    // Register hotkeys
    RegisterHotKey(hWnd, IDC_HOTKEY_PRIORITY, MOD_ALT, 'P');
    RegisterHotKey(hWnd, IDC_HOTKEY_SUBMIT, MOD_ALT, 'S');
    RegisterHotKey(hWnd, IDC_HOTKEY_EXIT, MOD_ALT, 'Q');

    return true;
}

void Application::ShowShortcutMenu()
{
    HMENU hMenu, hMenuPopup;
    POINT pt;

    hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDD_DIALOG));

    // Update checkboxes
    CheckMenuItem(hMenu, IDM_PRIORITY, isEnabledFeature<PriorityFeature>() ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu, IDM_SUBMIT, isEnabledFeature<SubmitFeature>() ? MF_CHECKED : MF_UNCHECKED);
    EnableMenuItem(hMenu, IDM_SUBMIT, deniedAdmin ? MF_GRAYED : MF_ENABLED);

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

bool Application::RequireAdmin()
{
    if (IsUserAnAdmin()) { return true; }

    WCHAR path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);

    SHELLEXECUTEINFO info = { sizeof(SHELLEXECUTEINFO) };
    info.lpVerb = L"runas";
    info.lpFile = path;
    info.nShow = SW_NORMAL;

    if (!ShellExecuteEx(&info)) {
        this->deniedAdmin = true;

        return false;
    }

    // Should not return success as the current process is still not privileged, instead terminate the instance
    PostMessage(hWnd, WM_CLOSE, 0, 0);
    return false;
}

} // namespace osuessentials
