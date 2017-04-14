//
// Modified by Caily on 14/4/2017.
//


#include <Windows.h>

#include "NtSupport.h"

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	DWORD dwCurrentProcessId = *((DWORD*)lParam);
	DWORD dwProcessId = 0;

	GetWindowThreadProcessId(hWnd, &dwProcessId);

	if (dwProcessId == dwCurrentProcessId && NULL == GetParent(hWnd)) {
		*((HWND*)lParam) = hWnd;
		return false;
	}

	return true;
}

HWND GetMainWindow() {
	DWORD PID = GetCurrentProcessId();

	if (!EnumWindows(EnumWindowsProc, (LPARAM)&PID)) {
		return (HWND)PID;
	}

	return NULL;
}

bool GetPrivileges() {
	// ȡ�õ�ǰ���̵�[Token](��ʶ)���
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	// ȷ���ܹرվ��
	HANDLE handle(hToken);

	// ȡ�ùر�ϵͳ��[LUID](����Ψһ�ı�ʶ��)ֵ
	TOKEN_PRIVILEGES stTokenPrivilege;
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &stTokenPrivilege.Privileges[0].Luid))
		return false;

	// ������Ȩ�����Ԫ�ظ���
	stTokenPrivilege.PrivilegeCount = 1;

	// ����[LUID]������ֵ
	stTokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Ϊ��ǰ����ȡ��DEBUGȨ��
	if (!AdjustTokenPrivileges(hToken, FALSE, &stTokenPrivilege, 0, NULL, NULL))
		return false;

	return true;
}

extern "C" __declspec(dllexport) BOOL ClearWeChatMutex(DWORD PID) {
	CNtSupport nt(SYSTEM_INFORMATION_CLASS::SystemHandleInformation);
	return nt.QueryAndCloseHandle(PID, L"Mutant", L"_WeChat_App_Instance_Identity_Mutex_Name");
}


extern "C" __declspec(dllexport) BOOL GetWeChatID(DWORD PID) {
	CNtSupport nt(SYSTEM_INFORMATION_CLASS::SystemHandleInformation);
	LPWSTR buffer = nt.GetMutantByPartWords(PID, L"_WeChat_Win_User_Identity_Mutex_Name");

	if (true == OpenClipboard(GetMainWindow())) {

		//��ռ�����  
		EmptyClipboard();

		//��ѡ�е��ַ����ŵ�ȫ���ڴ���  
		HGLOBAL hGol = GlobalAlloc(GMEM_MOVEABLE, 2014 * sizeof(WCHAR));

		//������ʱ����õ���ȫ���ڴ棬��ֹ���ݱ�����  
		LPWSTR lpStrcpy = (LPWSTR)GlobalLock(hGol);
		memcpy(lpStrcpy, buffer, 100 * sizeof(WCHAR));

		//���������ü���������  
		GlobalUnlock(hGol);
		SetClipboardData(CF_UNICODETEXT, hGol);

		//�رռ�����  
		CloseClipboard();
	}

	return true;
}

BOOL WINAPI DllMain(
	IN HANDLE hModule,
	IN DWORD ul_reasion_for_call,
	IN LPVOID lpReserved) {
	GetPrivileges();

	switch (ul_reasion_for_call)
	{
		/** the dll file has been loaded by other executable file */
		case DLL_PROCESS_ATTACH:
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		/** the dll file has been unloaded by other executable file */
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}



