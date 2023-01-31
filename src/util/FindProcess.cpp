#include "FindProcess.hpp"

namespace OsuEssentials {

DWORD GetProcessIdByName(const char* processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe))
    {
        do
        {
            if (strcmp((char*)pe.szExeFile, processName) == 0)
            {
                CloseHandle(hSnapshot);
                return pe.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return 0;
}

} // namespace OsuEssentials
