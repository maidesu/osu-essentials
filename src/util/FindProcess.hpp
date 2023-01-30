#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace RuntimeTools {

	DWORD GetProcessIdByName(const char* processName);

} // namespace RuntimeTools
