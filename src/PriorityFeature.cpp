#include "PriorityFeature.hpp"

#include <windows.h>

#include "util/FindProcess.hpp"

namespace osuessentials {

bool PriorityFeature::TurnOn()
{
    stopFlag = false;
    thread = std::thread(&PriorityFeature::SetHighPriority, this);

    return true;
}

bool PriorityFeature::TurnOff()
{
    stopFlag = true;
    thread.join();

    return true;
}

void PriorityFeature::SetHighPriority()
{
    DWORD dwError = NULL;
    HANDLE hOsu = NULL;

    while (!stopFlag)
    {
        hOsu = OpenProcess(PROCESS_SET_INFORMATION, FALSE, GetProcessIdByName("osu!.exe"));

        if (hOsu == NULL) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        if (!SetPriorityClass(hOsu, HIGH_PRIORITY_CLASS))
        {
            dwError = GetLastError();
            CloseHandle(hOsu);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
		}

        CloseHandle(hOsu);
        std::this_thread::sleep_for(std::chrono::seconds(2));

    } while (!stopFlag);
}

} //namespace osuessentials
