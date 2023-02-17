#include "FindProcess.hpp"

#include <tlhelp32.h>
#include <string>

namespace osuessentials::util {

DWORD GetProcessIdByName(const char* processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) { return 0; }

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    std::string processNameStr(processName);
    std::wstring processNameWStr(processNameStr.begin(), processNameStr.end());

    if (Process32First(hSnapshot, &entry))
    {
        do
        {
            std::wstring entryWStr(entry.szExeFile);

            if (entryWStr.compare(processNameWStr) == 0)
            {
                CloseHandle(hSnapshot);
                return entry.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &entry));
    }

    CloseHandle(hSnapshot);

    return 0;
}

} // namespace osuessentials
