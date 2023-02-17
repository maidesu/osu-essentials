#pragma once

#include <vector>
#include <memory>
#include <windows.h>

#include "PriorityFeature.hpp"
#include "SubmitFeature.hpp"
#include "../resource/resource.h"

namespace osuessentials {

class Application
{
public:
    Application(HINSTANCE hInstance, HWND hWindow);

    bool Init();
    void ShowShortcutMenu();
    void OnQuit();

    template <class T>
    void ToggleFeature() {
        for (const std::unique_ptr<Feature>& feature : features)
        {
            if (dynamic_cast<T*>(feature.get()) != nullptr) {
                feature.get()->Toggle();
            }
        }
    }

    template <class T>
    bool isEnabledFeature() {
        for (const std::unique_ptr<Feature>& feature : features)
        {
            if (dynamic_cast<T*>(feature.get()) != nullptr) {
                return feature.get()->isEnabled();
            }
        }

        return false;
    }

    HINSTANCE hInst;
    HWND hWnd;

private:
    NOTIFYICONDATA nid;
    std::vector<std::unique_ptr<Feature>> features;
};

} // namespace osuessentials
