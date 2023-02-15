#pragma once

#include <windows.h>

#include "../resource/resource.h"

namespace osuessentials {

class Application
{
public:
    static bool Init(HINSTANCE hInstance);
    static void ShowShortcutMenu();
    static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static HINSTANCE hInst;
    static HWND hWnd;
    static NOTIFYICONDATA nid;
};

} // namespace osuessentials
