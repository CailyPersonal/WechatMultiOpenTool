#include "NtSupport.h"

#define OUTPUTINFORMATION

#ifdef OUTPUTINFORMATION
#include <iostream>
#endif // OUTPUTINFORMATION



CNtSupport::CNtSupport(SYSTEM_INFORMATION_CLASS SystemInformationClass){

	_SystemInformationClass = SystemInformationClass;

	// Get function (NtQuerySystemInformation) address from "ntdll.dll".
	NtQuerySystemInformation = (_NtQuerySystemInformation)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQuerySystemInformation");

	// Get function (NtQueryObject) address from "ntdll.dll".
	NtQueryObject = (_NtQueryObject)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryObject");

}

bool CNtSupport::QueryAndCloseHandle(DWORD PID, wchar_t* TYPE, wchar_t* VALUE) {

	size_t HandleInformationSize = 0x1000; // 4k
	PSYSTEM_HANDLE_INFORMATION pSystemHandleInformation = NULL;
	pSystemHandleInformation = (PSYSTEM_HANDLE_INFORMATION)malloc(HandleInformationSize);

	NTSTATUS NtStatus;

	/*
	 * An unusual aspect of calling NtQuerySystemInformation with SystemHandleInformation
	 * is that if you supply a buffer which is too small, it returns
	 * STATUS_INFO_LENGTH_MISMATCH (0xc0000004) instead of giving you the correct buffer
	 * size in ReturnLength. This means you will have to guess the buffer size. A common
	 * technique is to call NtQuerySystemInformation in a loop until it succeeds with
	 * STATUS_SUCCESS (0), reallocating and doubling the buffer size each time it fails
	 * with STATUS_INFO_LENGTH_MISMATCH.
	*/
	do {
		NtStatus = NtQuerySystemInformation(_SystemInformationClass, pSystemHandleInformation, HandleInformationSize, NULL);

		if (NtStatus == STATUS_INFO_LENGTH_MISMATCH) {

			HandleInformationSize *= 2;
			pSystemHandleInformation = (PSYSTEM_HANDLE_INFORMATION)realloc(pSystemHandleInformation, HandleInformationSize);

		}
		else {
			break;
		}
	} while (TRUE);

	HANDLE hDuplicatedHandle(NULL);
	HANDLE hSource(NULL);
	HANDLE hDestination(NULL);

	for (ULONG index = 0; index < pSystemHandleInformation->HandleCount; index++) {

		PSYSTEM_HANDLE_TABLE_ENTRY_INFO pSystemHandleTableEntryInfo = &pSystemHandleInformation->Handles[index];

		if (PID == pSystemHandleTableEntryInfo->ProcessId) {

			// Copy handle first.
			hSource = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
			hDestination = GetCurrentProcess();

			if (NULL == hSource || NULL == hDestination) {
				continue;
			}

			if (FALSE == DuplicateHandle(
				hSource,
				(HANDLE)pSystemHandleTableEntryInfo->Handle,
				hDestination,
				&hDuplicatedHandle,
				0,
				FALSE,
				DUPLICATE_SAME_ACCESS)) {
				continue;
			}


			POBJECT_TYPE_INFORMATION pObjectTypeInformation = (POBJECT_TYPE_INFORMATION)malloc(ONEPAGESIZE);
			POBJECT_TYPE_INFORMATION pObjectNameInformation = (POBJECT_TYPE_INFORMATION)malloc(ONEPAGESIZE);
			ULONG ReturnLength = 0;

			/* Query the object type. */

			NtStatus = NtQueryObject(
				hDuplicatedHandle,
				OBJECT_INFORMATION_CLASS::ObjectTypeInformation,
				pObjectTypeInformation,
				ONEPAGESIZE,
				&ReturnLength);
			if (!NT_SUCCESS(NtStatus)) {
				CloseHandle(hDuplicatedHandle);
				continue;
			}

			NtStatus = NtQueryObject(
				hDuplicatedHandle,
				OBJECT_INFORMATION_CLASS::ObjectNameInformation,
				pObjectNameInformation,
				ONEPAGESIZE,
				&ReturnLength);
			if (!NT_SUCCESS(NtStatus)) {
				CloseHandle(hDuplicatedHandle);
				continue;
			}

#ifdef OUTPUTINFORMATION
			OutputDebugStringA("Information from WeChatJailbreak.dll");
			OutputDebugStringW(pObjectNameInformation->TypeName.Buffer);
			OutputDebugStringW(pObjectTypeInformation->TypeName.Buffer);
#endif // OUTPUTINFORMATION

			if (!wcscmp(TYPE, (wchar_t *)pObjectTypeInformation->TypeName.Buffer)
				&&pObjectNameInformation->TypeName.Buffer
				&&wcsstr((wchar_t *)pObjectNameInformation->TypeName.Buffer, VALUE)) {

				CloseHandle(hDuplicatedHandle);
				DuplicateHandle(
					hSource, 
					(HANDLE)pSystemHandleTableEntryInfo->Handle, 
					hDestination,
					&hDuplicatedHandle,
					0,
					FALSE,
					DUPLICATE_CLOSE_SOURCE);
				return CloseHandle(hDuplicatedHandle);
			}

			CloseHandle(hDuplicatedHandle);
		}
	}

	return FALSE;
}

LPWSTR CNtSupport::GetMutantByPartWords(DWORD PID, wchar_t * VALUE) {

	size_t HandleInformationSize = 0x1000; // 4k
	PSYSTEM_HANDLE_INFORMATION pSystemHandleInformation = NULL;
	pSystemHandleInformation = (PSYSTEM_HANDLE_INFORMATION)malloc(HandleInformationSize);

	NTSTATUS NtStatus;

	/*
	* An unusual aspect of calling NtQuerySystemInformation with SystemHandleInformation
	* is that if you supply a buffer which is too small, it returns
	* STATUS_INFO_LENGTH_MISMATCH (0xc0000004) instead of giving you the correct buffer
	* size in ReturnLength. This means you will have to guess the buffer size. A common
	* technique is to call NtQuerySystemInformation in a loop until it succeeds with
	* STATUS_SUCCESS (0), reallocating and doubling the buffer size each time it fails
	* with STATUS_INFO_LENGTH_MISMATCH.
	*/
	do {
		NtStatus = NtQuerySystemInformation(_SystemInformationClass, pSystemHandleInformation, HandleInformationSize, NULL);

		if (NtStatus == STATUS_INFO_LENGTH_MISMATCH) {

			HandleInformationSize *= 2;
			pSystemHandleInformation = (PSYSTEM_HANDLE_INFORMATION)realloc(pSystemHandleInformation, HandleInformationSize);

		}
		else {
			break;
		}
	} while (TRUE);

	HANDLE hDuplicatedHandle(NULL);
	HANDLE hSource(NULL);
	HANDLE hDestination(NULL);

	for (ULONG index = 0; index < pSystemHandleInformation->HandleCount; index++) {

		PSYSTEM_HANDLE_TABLE_ENTRY_INFO pSystemHandleTableEntryInfo = &pSystemHandleInformation->Handles[index];

		if (PID == pSystemHandleTableEntryInfo->ProcessId) {

			// Copy handle first.
			hSource = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
			hDestination = GetCurrentProcess();

			if (NULL == hSource || NULL == hDestination) {
				continue;
			}

			if (FALSE == DuplicateHandle(
				hSource,
				(HANDLE)pSystemHandleTableEntryInfo->Handle,
				hDestination,
				&hDuplicatedHandle,
				0,
				FALSE,
				DUPLICATE_SAME_ACCESS)) {
				continue;
			}


			POBJECT_TYPE_INFORMATION pObjectTypeInformation = (POBJECT_TYPE_INFORMATION)malloc(ONEPAGESIZE);
			POBJECT_TYPE_INFORMATION pObjectNameInformation = (POBJECT_TYPE_INFORMATION)malloc(ONEPAGESIZE);
			ULONG ReturnLength = 0;

			/* Query the object type. */

			NtStatus = NtQueryObject(
				hDuplicatedHandle,
				OBJECT_INFORMATION_CLASS::ObjectTypeInformation,
				pObjectTypeInformation,
				ONEPAGESIZE,
				&ReturnLength);
			if (!NT_SUCCESS(NtStatus)) {
				CloseHandle(hDuplicatedHandle);
				continue;
			}

			NtStatus = NtQueryObject(
				hDuplicatedHandle,
				OBJECT_INFORMATION_CLASS::ObjectNameInformation,
				pObjectNameInformation,
				ONEPAGESIZE,
				&ReturnLength);
			if (!NT_SUCCESS(NtStatus)) {
				CloseHandle(hDuplicatedHandle);
				continue;
			}

#ifdef OUTPUTINFORMATION
			OutputDebugStringA("Information from WeChatJailbreak.dll");
			OutputDebugStringW(pObjectNameInformation->TypeName.Buffer);
			OutputDebugStringW(pObjectTypeInformation->TypeName.Buffer);
#endif // OUTPUTINFORMATION

			if (!wcscmp(L"Mutant", (wchar_t *)pObjectTypeInformation->TypeName.Buffer)
				&& pObjectNameInformation->TypeName.Buffer
				&&wcsstr((wchar_t *)pObjectNameInformation->TypeName.Buffer, VALUE)) {

				CloseHandle(hDuplicatedHandle);

				return pObjectNameInformation->TypeName.Buffer;
			}

			CloseHandle(hDuplicatedHandle);
		}
	}

	return LPWSTR();
}


