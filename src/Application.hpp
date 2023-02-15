#pragma once

#include <windows.h>

#include "../resource/resource.h"

namespace osuessentials {

class Application
{
public:
    Application(HINSTANCE hInstance, HWND hWindow) :
        hInst(hInstance),
        hWnd(hWindow),
        nid()
    {}

    bool Init();
    void ShowShortcutMenu();
    void OnQuit();

    HINSTANCE hInst;
    HWND hWnd;

private:
    NOTIFYICONDATA nid;
};

} // namespace osuessentials
