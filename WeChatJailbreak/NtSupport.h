#pragma once

#include <Windows.h>

#include "Defines.h"


class CNtSupport {

public:

private:

	_NtQuerySystemInformation NtQuerySystemInformation;
	_NtQueryObject NtQueryObject;
	SYSTEM_INFORMATION_CLASS _SystemInformationClass;

public:
	CNtSupport(SYSTEM_INFORMATION_CLASS SystemInformationClass);

	bool QueryAndCloseHandle(DWORD PID, wchar_t* TYPE, wchar_t* VALUE);

	LPWSTR GetMutantByPartWords(DWORD PID, wchar_t* VALUE);
};