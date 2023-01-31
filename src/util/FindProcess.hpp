#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace OsuEssentials {

	DWORD GetProcessIdByName(const char* processName);

} // namespace OsuEssentials
