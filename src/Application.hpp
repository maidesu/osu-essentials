#pragma once

#include <vector>
#include <memory>
#include <windows.h>

#include "PriorityFeature.hpp"
#include "../resource/resource.h"

namespace osuessentials {

class Application
{
public:
    Application(HINSTANCE hInstance, HWND hWindow);

    bool Init();
    void ShowShortcutMenu();
    void OnQuit();

    HINSTANCE hInst;
    HWND hWnd;

private:
    NOTIFYICONDATA nid;
    std::vector<std::unique_ptr<Feature>> features;
};

} // namespace osuessentials
